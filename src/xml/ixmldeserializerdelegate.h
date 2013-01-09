#ifndef QTXXML_IXMLDESERIALIZERDELEGATE_H
#define QTXXML_IXMLDESERIALIZERDELEGATE_H

#include "xmlglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class IXmlDeserializing;

class IXmlDeserializerDelegate
{
public:
    virtual ~IXmlDeserializerDelegate() {};
        
    virtual IXmlDeserializing *deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes) = 0;
    virtual void deserializeXmlEnd(XmlDeserializer *deserializer) = 0;
    virtual void deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString) = 0;
};


QTX_END_NAMESPACE

#endif // QTXXML_IXMLDESERIALIZERDELEGATE_H
