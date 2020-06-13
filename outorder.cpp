#include "outorder.h"

outorder::outorder(QObject *parent) : QObject(parent)
{

}
outorder::outorder(QString id, QString recipt, QString salesperson, QString outdate, int ifoutofstock, QString notes,bool ifreview ){
    this->id = id;
    this->recipt = recipt;
    this->salesperson = salesperson;
    this->outdate = outdate;
    this->ifoutofstock = ifoutofstock;
    this->notes = notes;
    this->ifreview = ifreview;
}
outorder::outorder(QString id, QString recipt, QString salesperson, bool ifoutofstock, QString notes,bool ifreview ){
    this->id = id;
    this->recipt = recipt;
    this->salesperson = salesperson;
    this->ifoutofstock = ifoutofstock;
    this->notes = notes;
    this->ifreview = ifreview;
}
