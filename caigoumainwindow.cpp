#include "caigoumainwindow.h"
#include "ui_caigoumainwindow.h"
#include "mysqlutil.h"
#include <QMessageBox>

CaiGouMainWindow::CaiGouMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CaiGouMainWindow)
{
    ui->setupUi(this);
    //db isnot connected
    if (!mysqlutil::db.isOpen()){
        QMessageBox::critical(this, "错误", "数据库未连接");
        return;
    }
    refresh();
}

void CaiGouMainWindow::refresh(){
    addNewInOrderWidget = new AddNewInOrder(this->ui->widgetContainer);
    addNewInOrderWidget->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);


    checkAllInOrder = new CheckAllInOrder(this->ui->widgetContainer);
    checkAllInOrder->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    nowcur = 0;
    //addNewInOrderWidget->show();
    checkAllInOrder->hide();
}

CaiGouMainWindow::~CaiGouMainWindow()
{
    delete ui;
}

void CaiGouMainWindow::on_actionNewInOrder_triggered()
{
    if (this->nowcur == 0) return;
    hideSonWidget();
    addNewInOrderWidget->show();
    nowcur = 0;
}

void CaiGouMainWindow::on_actionCheckAllInOrder_triggered()
{
    if (this->nowcur == 1) return;
    hideSonWidget();
    checkAllInOrder->show();
    nowcur=1;
}

void CaiGouMainWindow::hideSonWidget(){
    switch (nowcur) {
    case 0:
        addNewInOrderWidget->hide();
        break;
    case 1:
        checkAllInOrder->hide();
        break;
    case 2:
        break;
    default:
        break;
    }
}

void CaiGouMainWindow::setusingStaff(Staff * staff){
    this->usingStaff = staff;
}


void CaiGouMainWindow::on_actionBack_triggered()
{
    emit backSignal();
}
