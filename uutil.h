#ifndef UUTIL_H
#define UUTIL_H

#include <QObject>
#include "staff.h"

class uutil : public QObject
{
    Q_OBJECT
public:
    explicit uutil(QObject *parent = nullptr);
    static bool inorderIdisLeagal(QString str);
    static bool onlyNum(QString str);
    static void setStaff(Staff & t);
    static Staff * _staff;
signals:

public slots:
};

#endif // UUTIL_H
