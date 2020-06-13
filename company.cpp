#include "company.h"

company::company(QObject *parent) : QObject(parent)
{

}
company::company(QString name,QString address,QString tel){
    this->name = name;
    this->address = address;
    this->tel = tel;
}
