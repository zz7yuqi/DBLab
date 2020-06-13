#include "salesmanmainwindow.h"
#include "ui_salesmanmainwindow.h"
#include <QMessageBox>


SalesmanMainWindow::SalesmanMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SalesmanMainWindow)
{
    ui->setupUi(this);
    //db isnot connected
    if (!mysqlutil::db.isOpen()){
        QMessageBox::critical(this, "错误", "数据库未连接");
        return;
    }
    refresh();
}

SalesmanMainWindow::~SalesmanMainWindow()
{
    delete ui;
}

void SalesmanMainWindow::on_actionBack_triggered()
{
    emit backSignal();
}

void SalesmanMainWindow::refresh(){
    addNewOutOrderWidget = new AddNewoutOrder(this->ui->widgetContainer);
    addNewOutOrderWidget->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);


    checkAllOutOrder = new CheckAlloutOrder(this->ui->widgetContainer);
    checkAllOutOrder->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    nowcur = 0;
    //addNewInOrderWidget->show();
    checkAllOutOrder->hide();
}


void SalesmanMainWindow::hideSonWidget(){
    switch (nowcur) {
    case 0:
        addNewOutOrderWidget->hide();
        break;
    case 1:
        checkAllOutOrder->hide();
        break;
    case 2:
        break;
    default:
        break;
    }
}

void SalesmanMainWindow::on_actionNewoutOrder_triggered()
{
    if (this->nowcur == 0) return;
    hideSonWidget();
    addNewOutOrderWidget->show();
    nowcur = 0;
}

void SalesmanMainWindow::on_actionAlloutOrder_triggered()
{
    if (this->nowcur == 1) return;
    hideSonWidget();
    checkAllOutOrder->show();
    nowcur = 1;
}
