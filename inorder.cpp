#include "inorder.h"

inorder::inorder(QObject *parent) : QObject(parent)
{

}
inorder::inorder(QString id,QString manufacturer,QString purchase,QString note,bool ifreview){
    this->id = id;
    this->manufacturer = manufacturer;
    this->purchaser = purchase;
    this->note = note;
    this->ifreview = ifreview;
}

inorder::inorder(QString id,QString manufacturer,QString purchase,QString indate,QString note,bool ifreview){
    this->id = id;
    this->manufacturer = manufacturer;
    this->purchaser = purchase;
    this->note = note;
    this->ifreview = ifreview;
    this->indate = indate;
}

