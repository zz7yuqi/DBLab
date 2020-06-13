#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

class product : public QObject
{
    Q_OBJECT
public:
    explicit product(QObject *parent = nullptr);
    product(QString id, QString name, int num);
    product(QString id, QString name, double outprice, double inprice, int num);
    QString id;
    QString name;
    double outprice = 0;
    double inprice = 0;
    int num;

signals:

public slots:
};

#endif // PRODUCT_H
