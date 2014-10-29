#include <QDomDocument>
#include <QFile>
#include <QMessageBox>

#include "coinsxmldocument.h"

CoinsXmlDocument::CoinsXmlDocument(QObject *parent) :
    QObject(parent)
{
}

void CoinsXmlDocument::setFile(const QString &fileName)
{
    xmlPath_=fileName;
}

void CoinsXmlDocument::showWarning(QString warning)
{
    QMessageBox::warning(NULL, tr("Message"), warning);
}

bool CoinsXmlDocument::readFromXml(std::set<Coin> &coins, QString& basedir)
{
    QDomDocument domDoc;
    QFile file(xmlPath_);

    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement= domDoc.documentElement();
            if(domElement.tagName() != "coinlauncher")
            {
                showWarning(tr("ERROR! Failed to find XML entry 'coinlauncher'!"));
                return false;
            }
            if(!parseBaseDirElement(basedir, domElement))
            {
                showWarning(tr("ERROR! Failed to find XML entry 'basedir'!"));
                return false;
            }
            if(!parseCoinsElement(coins, domElement))
            {
                showWarning(tr("ERROR! Failed to read data in XML element 'coins'!"));
                return false;
            }
        }
        file.close();
    }
    else
    {
        showWarning(tr("ERROR! Failed to open file:\n%1").arg(xmlPath_));
        return false;
    }
    return true;
}

bool CoinsXmlDocument::parseBaseDirElement(QString& basedir, const QDomElement& element)
{
    for(QDomNode childNode = element.firstChild(); !childNode.isNull(); childNode = childNode.nextSibling())
    {
        if(childNode.toElement().tagName() == "basedir")//one element exist only
        {
            basedir = childNode.toElement().text();
            return true;
        }
    }
    return false;
}

bool CoinsXmlDocument::parseCoinsElement(std::set<Coin> &coins, const QDomElement& element)
{
    for(QDomNode childNode = element.firstChild(); !childNode.isNull(); childNode = childNode.nextSibling())
    {
        if(childNode.toElement().tagName() == "coins")//many elements
        {
            if(!parseCoinElement(coins,childNode.toElement()))
                return false;
        }
    }
    return true;
}
bool CoinsXmlDocument::parseCoinElement(std::set<Coin> &coins, const QDomElement& element)
{
    for(QDomNode childNode = element.firstChild(); !childNode.isNull(); childNode = childNode.nextSibling())
    {
        if(childNode.toElement().tagName() == "coin")//many elements
        {
            Coin coin;
            if(!parseCoinChildElements(coin,childNode.toElement()))
                return false;
            coins.insert(coin);
        }
    }
    return true;
}
bool CoinsXmlDocument::parseCoinChildElements(Coin &coin, const QDomElement& element)
{
    for(QDomNode childNode = element.firstChild(); !childNode.isNull(); childNode = childNode.nextSibling())
    {
        QDomElement domElement = childNode.toElement();
        if(!domElement.isNull())
        {
            if(domElement.tagName() == "name")
            {
                coin.name = domElement.text().toStdString();
            }
            else if(domElement.tagName() == "binpath")
            {
                coin.binpath = domElement.text().toStdString();
            }
            else if(domElement.tagName() == "datadirpath")
            {
                coin.datadirpath = domElement.text().toStdString();
            }
        }
    }
    return true;
}

