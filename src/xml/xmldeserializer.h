#ifndef QTXXML_XMLDESERIALIZER_H
#define QTXXML_XMLDESERIALIZER_H

#include "xmlglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class IXmlDeserializerDelegate;
class XmlDeserializerPrivate;

class XmlDeserializer : public QObject
{
    Q_OBJECT
    
public:
    XmlDeserializer(QObject *parent = 0);
    ~XmlDeserializer();
    
    void parse();
    void addData(const QByteArray & data);
    void clear();
    
    void setDelegate(IXmlDeserializerDelegate* delegate);
    
protected:
    XmlDeserializerPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(XmlDeserializer);
};


QTX_END_NAMESPACE

#endif // QTXXML_XMLDESERIALIZER_H
