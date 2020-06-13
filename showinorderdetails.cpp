#include "showinorderdetails.h"
#include "ui_showinorderdetails.h"
#include "company.h"
#include "mysqlutil.h"
#include "staff.h"
#include "product.h"

ShowInOrderDetails::ShowInOrderDetails(QWidget *parent,inorder * thisorder) :
    QWidget(parent),
    ui(new Ui::ShowInOrderDetails)
{
    ui->setupUi(this);
    //setup tableWidget
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (thisorder != nullptr){
        //订单号
        ui->labelOrderId->setText(thisorder->id);
        //获得采购员
        Staff * orderStaff = mysqlutil::getStuffWithId(thisorder->purchaser);
        if (orderStaff != nullptr){
            ui->labelCaigouName->setText(orderStaff->getName());
        }
        //获得生产厂商
        company * theCompany = mysqlutil::getCompanyinWithName(thisorder->manufacturer);
        if (theCompany != nullptr){
            ui->labelManufacturer->setText(theCompany->name);
            ui->labelAddress->setText(theCompany->address);
            ui->labelTel->setText(theCompany->tel);
        }
        //时间
        ui->labelDatetime->setText(thisorder->indate);
        ui->labelState->setText(thisorder->ifreview?"已审核":"未审核");
        //填表
        QList<product *> * list = mysqlutil::getProductsInOrder(thisorder->id);
        if (list != nullptr){
            for (int i = 0; i < list->size(); i++){
                //插入新的行
                int irow = ui->tableWidget->rowCount();
                ui->tableWidget->setRowCount(irow+1);
                ui->tableWidget->setItem(irow, 0, new QTableWidgetItem(list->at(i)->id));
                ui->tableWidget->setItem(irow, 1, new QTableWidgetItem(list->at(i)->name));
                ui->tableWidget->setItem(irow, 2, new QTableWidgetItem(QString::number(list->at(i)->num)));
                ui->tableWidget->setItem(irow, 3, new QTableWidgetItem(QString::number(list->at(i)->inprice)));
            }
        }
        ui->textBrowser->setText(thisorder->note);
    }
}

ShowInOrderDetails::ShowInOrderDetails(QWidget *parent,outorder * thisorder) :
    QWidget(parent),
    ui(new Ui::ShowInOrderDetails)
{
    ui->setupUi(this);
    //setup tableWidget
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (thisorder != nullptr){
        //订单号
        ui->labelOrderId->setText(thisorder->id);
        //获得销售员
        Staff * orderStaff = mysqlutil::getStuffWithId(thisorder->salesperson);
        if (orderStaff != nullptr){
            ui->labelCaigouName->setText(orderStaff->getName());
        }
        //获得收货厂商
        company * theCompany = mysqlutil::getCompanyoutWithName(thisorder->recipt);
        if (theCompany != nullptr){
            ui->labelManufacturer->setText(theCompany->name);
            ui->labelAddress->setText(theCompany->address);
            ui->labelTel->setText(theCompany->tel);
        }
        //时间
        ui->labelDatetime->setText(thisorder->outdate);
        ui->labelState->setText(thisorder->ifreview?"已审核":"未审核");
        //填表
        QList<product *> * list = mysqlutil::getProductsOutOrder(thisorder->id);
        if (list != nullptr){
            for (int i = 0; i < list->size(); i++){
                //插入新的行
                int irow = ui->tableWidget->rowCount();
                ui->tableWidget->setRowCount(irow+1);
                ui->tableWidget->setItem(irow, 0, new QTableWidgetItem(list->at(i)->id));
                ui->tableWidget->setItem(irow, 1, new QTableWidgetItem(list->at(i)->name));
                ui->tableWidget->setItem(irow, 2, new QTableWidgetItem(QString::number(list->at(i)->num)));
                ui->tableWidget->setItem(irow, 3, new QTableWidgetItem(QString::number(list->at(i)->outprice)));
            }
        }
        ui->textBrowser->setText(thisorder->notes);
    }
}

ShowInOrderDetails::~ShowInOrderDetails()
{
    delete ui;
}

void ShowInOrderDetails::inToOut(){
    ui->label1->setText("出货单:");
    ui->label2->setText("订货方:");
    ui->label3->setText("收货地址:");
    ui->label5->setText("销售员:");
}
