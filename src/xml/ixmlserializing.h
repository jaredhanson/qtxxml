#ifndef QTXXML_IXMLSERIALIZING_H
#define QTXXML_IXMLSERIALIZING_H

#include "xmlglobal.h"
#include <QtXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class IXmlSerializing
{
public:
    virtual ~IXmlSerializing() {};
    
    virtual void serializeXml(QXmlStreamWriter *writer) const = 0;
};


QTX_END_NAMESPACE

#endif // QTXXML_IXMLSERIALIZING_H
