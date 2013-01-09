#ifndef QTXXML_IXMLDESERIALIZING_H
#define QTXXML_IXMLDESERIALIZING_H

#include "xmlglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class IXmlDeserializing
{
public:
    virtual ~IXmlDeserializing() {};
        
    virtual IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes) = 0;
    virtual void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri) = 0; 
    virtual void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes) = 0;
    virtual void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text) = 0;
};


QTX_END_NAMESPACE

#endif // QTXXML_IXMLDESERIALIZING_H
