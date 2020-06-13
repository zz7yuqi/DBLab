#include "updateinorder.h"
#include "ui_updateinorder.h"
#include "mysqlutil.h"
#include <QMessageBox>
#include "uutil.h"
#include <QCompleter>

UpdateinOrder::UpdateinOrder(QWidget *parent, inorder * updatingOrder) :
    QWidget(parent),
    ui(new Ui::UpdateinOrder)
{
    this->updatingOrder = updatingOrder;
    //debug
    //usingStaff = new Staff("00001","A",0,"1111");
    //debug
    ui->setupUi(this);
    //db isnt connected
    if (!mysqlutil::db.isOpen()){
        QMessageBox::critical(this, "错误", "数据库未连接");
        return;
    }
    if (updatingOrder == nullptr) return;

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
    //ui->labelCGName->setText(uutil::_staff->getName());
    owner = mysqlutil::getStuffWithId(updatingOrder->purchaser);
    ui->labelCGName->setText(owner->getName());
    //get all products' name
    listForProId = mysqlutil::getAllProductId();
    //show manufacturer
    ui->comboBox->setCurrentText(updatingOrder->manufacturer);
    //show inorderid
    ui->lineEditId->setText(updatingOrder->id);
    //填表
    QList<product *> * _list = mysqlutil::getProductsInOrder(updatingOrder->id);
    if (_list != nullptr){
        for (int i = 0; i < _list->size(); i++){
            //插入新的行
            int irow = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(irow+1);
            //set items uneditable
            QTableWidgetItem * item1 = new QTableWidgetItem(_list->at(i)->name);
            QTableWidgetItem * item3 = new QTableWidgetItem(QString::number(_list->at(i)->inprice));
            item1->setFlags(item1->flags()&(~Qt::ItemIsEditable));
            item3->setFlags(item3->flags()&(~Qt::ItemIsEditable));
            ui->tableWidget->setItem(irow,1,item1);
            ui->tableWidget->setItem(irow,3,item3);
            ui->tableWidget->setItem(irow,2, new QTableWidgetItem(QString::number(_list->at(i)->num)));

            QComboBox *comBox = new QComboBox();
            QCompleter *completer = new QCompleter(listForProId,this);

            completer->setCaseSensitivity(Qt::CaseInsensitive);
            comBox->setEditable(true);
            comBox->setCompleter(completer);
            comBox->setCurrentText(_list->at(i)->id);
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
    }
    ui->textBrowser->setText(updatingOrder->note);
}

UpdateinOrder::~UpdateinOrder()
{
    delete ui;
}


void UpdateinOrder::on_btnNewRow_clicked()
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

void UpdateinOrder::on_btnDelRow_clicked()
{
    int rowIndex = ui->tableWidget->currentRow();
    if (rowIndex != -1){
        ui->tableWidget->removeRow(rowIndex);
    }
}

void UpdateinOrder::on_pushButton_clicked()
{
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
    //修改供货产商
    if (ui->comboBox->currentText() != this->updatingOrder->manufacturer){
        if (!mysqlutil::updateInorderManufacturerWithId(this, updatingOrder->id, ui->comboBox->currentText())){
            return;
        }
    }
    //修改备注
    if (ui->textBrowser->toPlainText() != this->updatingOrder->note){
        if (!mysqlutil::updateInorderNoteWithId(this, updatingOrder->id, ui->textBrowser->toPlainText())){
            return;
        }
    }
    //修改产品列表
    if (!mysqlutil::deleteInorderPorductsWithId(this, this->updatingOrder->id)){
        return;
    }

    QString orderId = ui->lineEditId->text();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
        QWidget * idcol = ui->tableWidget->cellWidget(i,0);
        QTableWidgetItem * numcol = ui->tableWidget->item(i,2);
        int productNum = numcol->text().toInt();
        QString productId = (qobject_cast<QComboBox *>(idcol))->currentText();
        if (!mysqlutil::submitInOrderProduct(this,orderId,productId,productNum)){
            //录入失败
            QMessageBox::critical(this, "失败", "入货单产品更新失败！\n失败产品："+productId);
            //mysqlutil::deleteInorderItemWithId(this, orderId);
            return;
        }
    }

    //成功
    if (QMessageBox::information(this,"成功","入货单已成功更新，请等待审核！\n") == QMessageBox::Ok){
        return;
    }

}
