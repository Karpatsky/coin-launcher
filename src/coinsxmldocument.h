#ifndef COINSXMLDOCUMENT_H
#define COINSXMLDOCUMENT_H

#include <QObject>
#include <set>

#include "coin.h"

class QDomElement;

class CoinsXmlDocument : public QObject
{
    Q_OBJECT
public:
    explicit CoinsXmlDocument(QObject *parent = 0);
    void setFile(const QString& fileName);
    bool readFromXml(std::set<Coin> &coins, QString &basedir);

signals:

public slots:

private:
    QString xmlPath_;
    bool parseBaseDirElement(QString &basedir, const QDomElement &element);
    bool parseCoinsElement(std::set<Coin> &coins, const QDomElement &element);
    bool parseCoinElement(std::set<Coin> &coins, const QDomElement &element);
    bool parseCoinChildElements(Coin &coin, const QDomElement& element);
    void showWarning(QString warning);
};

#endif // COINSXMLDOCUMENT_H

