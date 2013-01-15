#ifndef QTXXML_XMLDESERIALIZER_P_H
#define QTXXML_XMLDESERIALIZER_P_H

#include "xmldeserializer.h"

QTX_BEGIN_NAMESPACE


class IXmlDeserializing;

class XmlDeserializerPrivate
{
public:
    XmlDeserializerPrivate(XmlDeserializer *q);
    virtual ~XmlDeserializerPrivate();
    
    void parse();
    void addData(const QByteArray & data);
    void clear();
    
    void setDelegate(IXmlDeserializerDelegate* delegate);
    
public:
    XmlDeserializer *q_ptr;
    Q_DECLARE_PUBLIC(XmlDeserializer);
    
    QXmlStreamReader reader;
    QStack<IXmlDeserializing *> readers;
    IXmlDeserializerDelegate *delegate;
    
private:
    void processStartDocument();
    void processEndDocument();
    void processStartElement();
    void processEndElement();
    void processCharacters();
    void processInvalid();
};


QTX_END_NAMESPACE

#endif // QTXXML_XMLDESERIALIZER_P_H
