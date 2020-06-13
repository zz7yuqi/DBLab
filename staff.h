#ifndef STAFF_H
#define STAFF_H

#include <QObject>

class Staff : public QObject
{
    Q_OBJECT
public:
    explicit Staff(QObject *parent = nullptr);
    Staff(QString id,QString name, int identity, QString pwd);
    static QString identities[];
    QString getId();
    QString getName();
    int getIdentity();
    QString getPwd();
    void setId(QString id);
    void setName(QString name);
    void setIdentity(int identity);
    void setPwd(QString pwd);
private:
    QString id;
    QString name;
    int identity;
    QString pwd;
signals:

public slots:
};

#endif // STAFF_H
