#include "addnewinorder.h"
#include "ui_addnewinorder.h"
#include <QDebug>
#include "company.h"
#include "mysqlutil.h"
#include <QCompleter>
#include "uutil.h"
#include <QMessageBox>
#include "product.h"
#include "inorder.h"

AddNewInOrder::AddNewInOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewInOrder)
{
    //debug
    //usingStaff = new Staff("00001","A",0,"1111");
    //debug
    ui->setupUi(this);
    //db isnt connected
    if (!mysqlutil::db.isOpen()){
        QMessageBox::critical(this, "错误", "数据库未连接");
        return;
    }
    //setup tableWidget
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);   //set tableWidget noFocus
    //show company-in
    QList<company *>* list = mysqlutil::getAllCompanyin();
    if (list != nullptr){
        QStringList comboBoxStringList;
        for (int i = 0; i < list->size(); i++){
            comboBoxStringList.append(list->at(i)->name);
        }
        ui->comboBox->addItems(comboBoxStringList);
    }

    //show staff
    //qDebug() << uutil::_staff->getId();
    ui->labelCGName->setText(uutil::_staff->getName());
    //get all products' name
    listForProId = mysqlutil::getAllProductId();
}

AddNewInOrder::~AddNewInOrder()
{
    delete ui;
}

void AddNewInOrder::setusingStaff(Staff * staff){
    this->usingStaff = staff;

}

void AddNewInOrder::on_btnNewRow_clicked()
{
    int irow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(irow+1);
    //set items uneditable
    QTableWidgetItem * item1 = new QTableWidgetItem("");
    QTableWidgetItem * item3 = new QTableWidgetItem("");
    item1->setFlags(item1->flags()&(~Qt::ItemIsEditable));
    item3->setFlags(item3->flags()&(~Qt::ItemIsEditable));
    ui->tableWidget->setItem(irow,1,item1);
    ui->tableWidget->setItem(irow,3,item3);

    QComboBox *comBox = new QComboBox();
    QCompleter *completer = new QCompleter(listForProId,this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    comBox->setEditable(true);
    comBox->setCompleter(completer);
    connect(comBox,&QComboBox::currentTextChanged,this,[=](){
        //qDebug() << comBox->currentText() <<endl;
        //show product name & price
        //QString toshowName = mysqlutil::getProductNameWithId(comBox->currentText());
        product * tempProduct = mysqlutil::getProductWithId(comBox->currentText());
        if (tempProduct != nullptr){
            QTableWidgetItem * nameItem = new QTableWidgetItem(tempProduct->name);
            QTableWidgetItem * inpriceItem = new QTableWidgetItem(QString::number(tempProduct->inprice));
            nameItem->setFlags(nameItem->flags()&(~Qt::ItemIsEditable));
            inpriceItem->setFlags(inpriceItem->flags()&(~Qt::ItemIsEditable));
            ui->tableWidget->setItem(irow,1,nameItem);
            ui->tableWidget->setItem(irow,3,inpriceItem);
        }
    });
    ui->tableWidget->setCellWidget(irow,0,comBox);
}

void AddNewInOrder::on_btnDelRow_clicked()
{
    int rowIndex = ui->tableWidget->currentRow();
    if (rowIndex != -1){
        ui->tableWidget->removeRow(rowIndex);
    }

}


void AddNewInOrder::on_pushButton_clicked()
{
   //进货单号是否合法
    if (!uutil::inorderIdisLeagal(ui->lineEditId->text())){
        //非法
        QMessageBox::critical(this,"输入非法","货单号输入非法！\n请输入数字,字母或\'-\'\n且不为空");
        return;
    }
    //进货厂家非空
    if (ui->comboBox->currentText() == ""){
        QMessageBox::critical(this,"输入非法","请选择进货厂家，如没有，请求管理员新增厂家！");
        return;
    }
    //货单内容是否合法
    //只需判断id列和num列是否合法
    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
        QWidget * idcol = ui->tableWidget->cellWidget(i,0);
        QTableWidgetItem * numcol = ui->tableWidget->item(i,2);
        if (idcol == nullptr){
            QMessageBox::critical(this,"输入非法",(QString("货单内容第%1行，请输入产品编号！")).arg(i));
            return;
        }
        if (numcol == nullptr){
            QMessageBox::critical(this,"输入非法",(QString("货单内容第%1行，请输入总数！")).arg(i));
            return;
        }

        //num
        if (!uutil::onlyNum(numcol->text())){
            QMessageBox::critical(this,"输入非法",(QString("货单内容第%1行，总数输入非法！")).arg(i));
            return;
        }
        //id
        if (mysqlutil::getProductWithId((qobject_cast<QComboBox *>(idcol))->currentText()) == nullptr){
            QMessageBox::critical(this,"输入非法",(QString("货单内容第%1行，产品id不存在！")).arg(i));
            return;
        }
    }

    //提交入货单至数据库

    inorder * newOrder = new inorder(ui->lineEditId->text(), ui->comboBox->currentText(),
                     uutil::_staff->getId(), ui->textBrowser->toPlainText(), false);
    if (!mysqlutil::submitInOrder(this,newOrder)){
        //录入失败
        QMessageBox::critical(this, "失败", "入货单录入失败！");
        return;
    }

    //提交入货单内容至数据库

    QString orderId = ui->lineEditId->text();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
        QWidget * idcol = ui->tableWidget->cellWidget(i,0);
        QTableWidgetItem * numcol = ui->tableWidget->item(i,2);
        int productNum = numcol->text().toInt();
        QString productId = (qobject_cast<QComboBox *>(idcol))->currentText();
        if (!mysqlutil::submitInOrderProduct(this,orderId,productId,productNum)){
            //录入失败
            QMessageBox::critical(this, "失败", "入货单产品录入失败！\n失败产品："+productId);
            mysqlutil::deleteInorderItemWithId(this, orderId);
            return;
        }
    }

    //成功
    if (QMessageBox::information(this,"成功","入货单已成功进入数据库，请等待审核！\n") == QMessageBox::Ok){
        //清空
        ui->lineEditId->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->clearContents();
        ui->textBrowser->clear();
    }

}
