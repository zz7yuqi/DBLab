#include "staff.h"

QString Staff::identities[3] = {"审核员","采购员","销售员"};
Staff::Staff(QObject *parent) : QObject(parent)
{

}

Staff::Staff(QString id,QString name, int identity, QString pwd){
    this->setId(id);
    this->setName(name);
    this->setIdentity(identity);
    this->setPwd(pwd);
}

QString Staff::getId(){
    return this->id;
}
QString Staff::getName(){
    return this->name;
}
int Staff::getIdentity(){
    return this->identity;
}
QString Staff::getPwd(){
    return this->pwd;
}
void Staff::setId(QString id){
    this->id = id;
}
void Staff::setName(QString name){
    this->name = name;
}
void Staff::setIdentity(int identity){
    this->identity = identity;
}
void Staff::setPwd(QString pwd){
    this->pwd = pwd;
}
