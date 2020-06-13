#include "product.h"

product::product(QObject *parent) : QObject(parent)
{

}

product::product(QString id, QString name, double outprice, double inprice, int num){
    this->id = id;
    this->name = name;
    this->outprice = outprice;
    this->inprice = inprice;
    this->num = num;
}

product::product(QString id, QString name,int num){
    this->id = id;
    this->name = name;

    this->num = num;
}
