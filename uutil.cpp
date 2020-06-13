#include "uutil.h"

Staff * uutil::_staff = new Staff();
uutil::uutil(QObject *parent) : QObject(parent)
{

}

bool uutil::inorderIdisLeagal(QString str){
    //[\-0-9a-zA-Z]*
    QString pattern("[\\-0-9a-zA-Z]+");
    QRegExp rx(pattern);

    return rx.exactMatch(str);
}

bool uutil::onlyNum(QString str){
    //[1-9][0-9]*

    QString pattern("[1-9][0-9]*");
    QRegExp rx(pattern);

    return rx.exactMatch(str);
}

void uutil::setStaff(Staff & t){
    _staff->setId(t.getId());
    _staff->setName(t.getName());
    _staff->setPwd(t.getPwd());
}
