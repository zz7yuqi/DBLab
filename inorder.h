#ifndef INORDER_H
#define INORDER_H

#include <QObject>
#include <QDateTime>

class inorder : public QObject
{
    Q_OBJECT
public:
    explicit inorder(QObject *parent = nullptr);
    inorder(QString id,QString manufacturer,QString purchase,QString note,bool ifreview);
    inorder(QString id,QString manufacturer,QString purchase,QString indate,QString note,bool ifreview);
    QString id;
    QString manufacturer;
    QString purchaser;
    QString indate;
    QString note;
    bool ifreview;

signals:

public slots:
};

#endif // INORDER_H
