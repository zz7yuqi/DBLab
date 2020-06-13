#ifndef OUTORDER_H
#define OUTORDER_H

#include <QObject>

class outorder : public QObject
{
    Q_OBJECT
public:
    explicit outorder(QObject *parent = nullptr);
    outorder(QString id, QString recipt, QString salesperson, QString outdate, int ifoutofstock, QString notes,bool ifreview );
    outorder(QString id, QString recipt, QString salesperson, bool ifoutofstock, QString notes,bool ifreview );
    QString id;
    QString recipt;
    QString salesperson;
    QString outdate;
    int ifoutofstock;
    QString notes;
    bool ifreview;

signals:

public slots:
};

#endif // OUTORDER_H
