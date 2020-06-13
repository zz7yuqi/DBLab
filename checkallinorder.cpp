#include "checkallinorder.h"
#include "ui_checkallinorder.h"
#include "mysqlutil.h"
#include "uutil.h"
#include <QMessageBox>
#include "showinorderdetails.h"
#include <QDateEdit>
#include "updateinorder.h"

CheckAllInOrder::CheckAllInOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckAllInOrder)
{
    ui->setupUi(this);
    //db isnot connected
    if (!mysqlutil::db.isOpen()){
        QMessageBox::critical(this, "错误", "数据库未连接");
        return;
    }
    //设置时间
    ui->dateEditB->setDate(QDate::currentDate().addDays(1));

    //设置tabWidget
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);   //set tableWidget noFocus
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showtableWidget();

}

CheckAllInOrder::~CheckAllInOrder()
{
    delete ui;
}

void CheckAllInOrder::showtableWidget(){
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    QList<inorder *> * list = mysqlutil::getInordersWithStaffId(uutil::_staff->getId(),ui->lineEdit->text(),
                                                                ui->dateEditA->date(), ui->dateEditB->date());

    if (list == nullptr) return;
    for(int i = 0; i < list->size(); i++){
        QString orderId = list->at(i)->id;
        QString orderDate = list->at(i)->indate;
        QString orderNote = list->at(i)->note;
        QString orderState = (list->at(i)->ifreview)?"已审核":"未审核";
        //插入新的行
        int irow = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(irow+1);
        ui->tableWidget->setItem(irow, 0, new QTableWidgetItem(orderId));
        ui->tableWidget->setItem(irow, 1, new QTableWidgetItem(orderDate));
        ui->tableWidget->setItem(irow, 2, new QTableWidgetItem(orderNote));
        ui->tableWidget->setItem(irow, 3, new QTableWidgetItem(orderState));
    }
}

void CheckAllInOrder::on_btnRefresh_clicked()
{
    this->showtableWidget();
}

void CheckAllInOrder::on_btnCheck_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1){
        QMessageBox::information(this,"提醒","请选中一行后再点击此按钮！");
        return;
    }
    QString selectedInorderId = ui->tableWidget->item(currentRow,0)->text();  //获取选中的入货单编号
    inorder * tempInOrder = mysqlutil::getInorderWithInorderID(selectedInorderId);
    ShowInOrderDetails * subWidget = new ShowInOrderDetails(nullptr, tempInOrder);
    subWidget->show();

}

void CheckAllInOrder::on_btnCancel_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1){
        QMessageBox::information(this,"提醒","请选中一行后再点击此按钮！");
        return;
    }
    if (ui->tableWidget->item(currentRow, 3)->text() == "已审核"){
        QMessageBox::information(this,"提醒","已审核入货单不可撤销！");
        return;
    }
    //撤销进货单
    if (mysqlutil::deleteInorderItemWithId(this, ui->tableWidget->item(currentRow, 0)->text())){
        QMessageBox::information(this,"成功","已成功撤销！");
    }
}

void CheckAllInOrder::on_btnChange_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1){
        QMessageBox::information(this,"提醒","请选中一行后再点击此按钮！");
        return;
    }
    if (ui->tableWidget->item(currentRow, 3)->text() == "已审核"){
        QMessageBox::information(this,"提醒","已审核入货单不可修改！");
        return;
    }
    QString selectedInorderId = ui->tableWidget->item(currentRow,0)->text();  //获取选中的入货单编号
    inorder * tempInOrder = mysqlutil::getInorderWithInorderID(selectedInorderId);
    UpdateinOrder * subWidget = new UpdateinOrder(nullptr, tempInOrder);
    subWidget->show();
}
