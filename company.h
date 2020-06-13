#ifndef COMPANYIN_H
#define COMPANYIN_H

#include <QObject>

class company : public QObject
{
    Q_OBJECT
public:
    explicit company(QObject *parent = nullptr);
    company(QString name,QString address,QString tel);
    QString address;
    QString name;
    QString tel;
signals:

public slots:
};

#endif // COMPANYIN_H
