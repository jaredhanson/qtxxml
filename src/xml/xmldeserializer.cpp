#include "xmldeserializer_p.h"
#include "ixmldeserializerdelegate.h"
#include "ixmldeserializing.h"

QTX_BEGIN_NAMESPACE


XmlDeserializer::XmlDeserializer(QObject *parent /* = 0 */)
    : QObject(parent),
      d_ptr(new XmlDeserializerPrivate(this))
{
}

XmlDeserializer::~XmlDeserializer()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

void XmlDeserializer::parse()
{
    Q_D(XmlDeserializer);
    d->parse();
}

void XmlDeserializer::addData(const QByteArray & data)
{
    Q_D(XmlDeserializer);
    d->addData(data);
}

void XmlDeserializer::clear()
{
    Q_D(XmlDeserializer);
    d->clear();
}

void XmlDeserializer::setDelegate(IXmlDeserializerDelegate* delegate)
{
    Q_D(XmlDeserializer);
    d->setDelegate(delegate);
}


XmlDeserializerPrivate::XmlDeserializerPrivate(XmlDeserializer *q)
    : q_ptr(q),
      delegate(0)
{
}

XmlDeserializerPrivate::~XmlDeserializerPrivate()
{
    delegate = 0;
}

void XmlDeserializerPrivate::parse()
{
    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        switch (token)
        {
        case QXmlStreamReader::Invalid:
            processInvalid();
            break;
            
        case QXmlStreamReader::StartDocument:
            processStartDocument();
            break;
            
        case QXmlStreamReader::EndDocument:
            processEndDocument();
            break;
            
        case QXmlStreamReader::StartElement:
            processStartElement();
            break;
            
        case QXmlStreamReader::EndElement:
            processEndElement();
            break;
            
        case QXmlStreamReader::Characters:
            processCharacters();
            break;
            
        default:
            break;
        }
    }
}

void XmlDeserializerPrivate::addData(const QByteArray & data)
{
    reader.addData(data);
}

void XmlDeserializerPrivate::clear()
{
    reader.clear();
    readers.clear();
}

void XmlDeserializerPrivate::setDelegate(IXmlDeserializerDelegate* d)
{
    delegate = d;
}

void XmlDeserializerPrivate::processStartDocument()
{
}

void XmlDeserializerPrivate::processEndDocument()
{
    if (delegate) {
        Q_Q(XmlDeserializer);
        delegate->deserializeXmlEnd(q);
    }
}

void XmlDeserializerPrivate::processStartElement()
{
    Q_Q(XmlDeserializer);
    QStringRef namespaceUri = reader.namespaceUri();
    QStringRef name = reader.name();
    QXmlStreamAttributes attributes = reader.attributes();
    
    IXmlDeserializing* currObj = 0;
    IXmlDeserializing* nextObj = 0;
    
    if (readers.isEmpty()) {
        if (delegate) {
            nextObj = delegate->deserializeXmlStart(q, namespaceUri, name, attributes);
        }
    } else {
        currObj = readers.top();
        
        if (currObj) {
            nextObj = currObj->deserializeXmlStartElement(q, namespaceUri, name, attributes);
        }
    }
        
    if (!nextObj) {
        // No object is interested in parsing the current element, indicating
        // it is ignorable.  Push `0` onto the stack, the presence of which
        // will bypass calling IXmlDeserializing methods.  This bypass will be
        // in effect until all `0` placeholders have been popped from the stack,
        // and parsing returns to a non-ignorable element.
        readers.push(0);
    } else {
        // A deserializing object has been returned, signalling that it is to be
        // used to parse the current element.  Push it onto the stack, where
        // it will be accessed and have its IXmlDeserializing methods called.
        readers.push(nextObj);
        
        // The next object is different from the current object.  In practice,
        // this is typically due to a parent returning a child object for
        // parsing.  Inform this new object of any attributes, so that it can
        // fully initialize.
        if (nextObj != currObj) {
            nextObj->deserializeXmlAttributes(q, attributes);
        }
    }
}

void XmlDeserializerPrivate::processEndElement()
{
    IXmlDeserializing* obj = readers.pop();
    IXmlDeserializing* parentObj = 0;
    if (!readers.isEmpty()) {
        parentObj = readers.top();
    }
    if (!obj || !parentObj) {
        return;
    }
    
    Q_Q(XmlDeserializer);
    QStringRef namespaceUri = reader.namespaceUri();
    QStringRef name = reader.name();
    parentObj->deserializeXmlEndElement(q, namespaceUri, name);
}

void XmlDeserializerPrivate::processCharacters()
{
    IXmlDeserializing *obj = readers.top();
    if (!obj) {
        return;
    }
    
    Q_Q(XmlDeserializer);
    QStringRef text = reader.text();
    obj->deserializeXmlCharacters(q, text);
}

void XmlDeserializerPrivate::processInvalid()
{
    if (reader.error() == QXmlStreamReader::PrematureEndOfDocumentError) {
        // This error is reported when the end of an otherwise well-formed chunk
        // of XML is reached, but the chunk doesn't represent a complete XML
        // document.  In this situation, parsing can be continued by calling
        // addData() to add the next chunk of XML in an incremental manner.
        return;
    }
    
    
    if (delegate) {
        Q_Q(XmlDeserializer);
        QXmlStreamReader::Error error = reader.error();
        QString errorString = reader.errorString();
        delegate->deserializeXmlError(q, error, errorString);
    }
}


QTX_END_NAMESPACE
