#include "mysqlutil.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

bool mysqlutil::ifconnected = false;
QSqlDatabase mysqlutil::db;

mysqlutil::mysqlutil(QObject *parent) : QObject(parent)
{

}

void mysqlutil::connectToMySql(){
    db = QSqlDatabase::addDatabase("QMYSQL");  //连接的MYSQL的数据库驱动
    db.setHostName("localhost");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("dblab");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("777777");            //密码

    //测试连接

    if(!db.open())
    {
        qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        return ;
    }
    else
    {
        ifconnected = true;
        qDebug()<<"连接成功"<<"connect to mysql OK";
    }

}

Staff *  mysqlutil::getStuffWithId(QString id){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);

    qry->prepare(QString("select * from staff where id=?"));
    qry->addBindValue(id);
    qry->exec();
//    if (qry.lastError().isValid()){
//        QMessageBox::critical(parent,"错误",
//                              "stuff表查询错误，错误信息\n"+qry.lastError().text(),
//                              QMessageBox::Ok,QMessageBox::NoButton);
//        return nullptr;
//    }
    Staff * staff = nullptr;
    if (qry->next()){
        QString realId = qry->value(0).toString();
        QString realName = qry->value(1).toString();
        int realIdentity = qry->value(2).toInt();
        QString realPwd = qry->value(3).toString();
        //qDebug() << realId <<endl;
        staff = new Staff(realId,realName,realIdentity,realPwd);
    }

    return staff;
}

QList<company *> *  mysqlutil::getAllCompanyin(){
    if (!ifconnected){
        return nullptr;
    }
    QList<company *> * list = new QList<company *>();
    QSqlQuery * qry = new QSqlQuery(db);

    qry->exec("select * from companyin");
    while(qry->next()){
        QString realName = qry->value(0).toString();
        QString realAddress = qry->value(1).toString();
        QString realTel = qry->value(2).toString();
        company * temp = new company(realName,realAddress,realTel);
        list->append(temp);
    }
    return list;
}

QList<company *> *  mysqlutil::getAllCompanyout(){
    if (!ifconnected){
        return nullptr;
    }
    QList<company *> * list = new QList<company *>();
    QSqlQuery * qry = new QSqlQuery(db);

    qry->exec("select * from companyout");
    while(qry->next()){
        QString realName = qry->value(0).toString();
        QString realAddress = qry->value(1).toString();
        QString realTel = qry->value(2).toString();
        company * temp = new company(realName,realAddress,realTel);
        list->append(temp);
    }
    return list;
}

company * mysqlutil::getCompanyinWithName(QString name){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);

    qry->prepare("select * from companyin where name=?");
    qry->addBindValue(name);
    qry->exec();
    if (qry->next()){
        company * _temp = new company(qry->value(0).toString(),
                                          qry->value(1).toString(),
                                          qry->value(2).toString());
        return _temp;
    }
    return nullptr;
}

company * mysqlutil::getCompanyoutWithName(QString name){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);

    qry->prepare("select * from companyout where name=?");
    qry->addBindValue(name);
    qry->exec();
    if (qry->next()){
        company * _temp = new company(qry->value(0).toString(),
                                          qry->value(1).toString(),
                                          qry->value(2).toString());
        return _temp;
    }
    return nullptr;
}

QStringList mysqlutil::getAllProductId(){
    QStringList * list = new QStringList;
    if (!ifconnected) return *list;

    QSqlQuery * qry = new QSqlQuery(db);
    qry->exec("select id from products");
    while (qry->next()) {
        QString realId = qry->value(0).toString();
        list->append(realId);
    }
    return *list;
}

product * mysqlutil::getProductWithId(QString id){
    if (id == nullptr) return nullptr;
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);

    qry->prepare("select * from products where id=?");
    qry->addBindValue(id);
    qry->exec();
    if (qry->next()){
        product * _product = new product(qry->value(0).toString(),
                                        qry->value(1).toString(),
                                        qry->value(2).toDouble(),
                                        qry->value(3).toDouble(),
                                        qry->value(4).toInt());
        return _product;
    }
    return nullptr;
}

bool  mysqlutil::submitInOrder(QWidget * current ,inorder * content){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);

    qry->prepare("insert\n"
                 "into inorderlist(id,manufacturer,purchaser,notes,ifreview)\n"
                 "values(?,?,?,?,?)");

    qry->addBindValue(content->id);
    qry->addBindValue(content->manufacturer);
    qry->addBindValue(content->purchaser);
    qry->addBindValue(content->note);
    qry->addBindValue(content->ifreview);
    qry->exec();
    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "进货表插入错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::submitOutOrder(QWidget * current ,outorder * content){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);

    qry->prepare("insert\n"
                 "into outorderlist(id,recipt,salesperson,ifoutofstock,notes,ifreview)\n"
                 "values(?,?,?,?,?,?)");

    qry->addBindValue(content->id);
    qry->addBindValue(content->recipt);
    qry->addBindValue(content->salesperson);
    qry->addBindValue(content->ifoutofstock);
    qry->addBindValue(content->notes);
    qry->addBindValue(content->ifreview);
    qry->exec();
    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "出货表插入错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::submitInOrderProduct(QWidget * current, QString id, QString productid, int num){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("insert\n"
                 "into productinorderlist\n"
                 "values(?,?,?)");
    //qDebug() << id << endl << productid << endl << num << endl;
    qry->addBindValue(id);
    qry->addBindValue(productid);
    qry->addBindValue(num);
    qry->exec();
    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "进货单产品表插入错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::submitOutOrderProduct(QWidget * current, QString id, QString productid, int num){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("insert\n"
                 "into productoutorderlist\n"
                 "values(?,?,?)");
    //qDebug() << id << endl << productid << endl << num << endl;
    qry->addBindValue(id);
    qry->addBindValue(productid);
    qry->addBindValue(num);
    qry->exec();
    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "出货单产品表插入错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}
QList<inorder *>* mysqlutil::getInordersWithStaffId(QString staffId, QString inorderId, QDate A, QDate B){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select * from inorderlist where purchaser=? and id like ? and indate >= ? and indate <= ?");
    qry->addBindValue(staffId);
    qry->addBindValue(inorderId+"%");
    qry->addBindValue(A);
    qry->addBindValue(B);
    //qDebug() << inorderId+"%" << endl << A.toString("yyyy-MM-dd") << endl << B.toString("yyyy-MM-dd");
    qry->exec();

    QList<inorder *>* list = new QList<inorder *>();
    while (qry->next()) {
        inorder * _temp = new inorder(qry->value(0).toString(),
                                    qry->value(1).toString(),
                                    qry->value(2).toString(),
                                    qry->value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                                    qry->value(4).toString(),
                                    qry->value(5).toBool());
        list->append(_temp);
    }
    return list;
}

QList<outorder *>* mysqlutil::getOutordersWithStaffId(QString staffId, QString outorderId, QDate A, QDate B){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select * from outorderlist where salesperson=? and id like ? and outdate >= ? and outdate <= ?");
    qry->addBindValue(staffId);
    qry->addBindValue(outorderId+"%");
    qry->addBindValue(A);
    qry->addBindValue(B);
    qry->exec();

    QList<outorder *>* list = new QList<outorder *>();
    while (qry->next()) {
        outorder * _temp = new outorder(qry->value(0).toString(),
                                    qry->value(1).toString(),
                                    qry->value(2).toString(),
                                    qry->value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                                    qry->value(4).toInt(),
                                    qry->value(5).toString(),
                                        qry->value(6).toBool());
        list->append(_temp);
    }
    return list;
}

bool mysqlutil::deleteInorderItemWithId(QWidget * current,QString inorderId){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("delete from inorderlist where id=?");
    qry->addBindValue(inorderId);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "进货单表删除错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;

}

bool mysqlutil::deleteOutorderItemWithId(QWidget * current,QString outorderId){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("delete from outorderlist where id=?");
    qry->addBindValue(outorderId);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "出货单表删除错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;

}

inorder * mysqlutil::getInorderWithInorderID(QString id){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select * from inorderlist where id=?");
    qry->addBindValue(id);
    qry->exec();
    if (qry->next()) {
        inorder * _temp = new inorder(qry->value(0).toString(),
                                    qry->value(1).toString(),
                                    qry->value(2).toString(),
                                    qry->value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                                    qry->value(4).toString(),
                                    qry->value(5).toBool());
        return  _temp;
    }
    return nullptr;
}

outorder * mysqlutil::getOutorderWithOutorderID(QString id){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select * from outorderlist where id=?");
    qry->addBindValue(id);
    qry->exec();
    if (qry->next()) {
        outorder * _temp = new outorder(qry->value(0).toString(),
                                    qry->value(1).toString(),
                                    qry->value(2).toString(),
                                    qry->value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                                    qry->value(4).toInt(),
                                    qry->value(5).toString(),
                                    qry->value(6).toBool());
        return  _temp;
    }
    return nullptr;
}

QList<product *> * mysqlutil::getProductsInOrder(QString inorderId){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select * from productinorderlist where id=?");
    qry->addBindValue(inorderId);
    qry->exec();
    QList<product *> * list = new QList<product *>();
    while (qry->next()) {
        product * tt = mysqlutil::getProductWithId(qry->value(1).toString());
        product * tempProduct = new product(qry->value(1).toString(),
                                            tt->name,
                                            0,
                                            tt->inprice,
                                            qry->value(2).toInt());
        list->append(tempProduct);
    }
    return list;
}

QList<product *> * mysqlutil::getProductsOutOrder(QString outorderId){
    if (!ifconnected){
        return nullptr;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("select * from productoutorderlist where id=?");
    qry->addBindValue(outorderId);
    qry->exec();
    QList<product *> * list = new QList<product *>();
    while (qry->next()) {
        product * tt = mysqlutil::getProductWithId(qry->value(1).toString());
        product * tempProduct = new product(qry->value(1).toString(),
                                            tt->name,
                                            tt->outprice,
                                            tt->inprice,
                                            qry->value(2).toInt());
        list->append(tempProduct);
    }
    return list;
}

bool mysqlutil::updateInorderManufacturerWithId(QWidget * current, QString id, QString newManu){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("update inorderlist set manufacturer=? where id=?");
    qry->addBindValue(newManu);
    qry->addBindValue(id);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "入货单修改供货厂商错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::updateOutorderReciptWithId(QWidget *current, QString id, QString newRecipt){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("update outorderlist set recipt=? where id=?");
    qry->addBindValue(newRecipt);
    qry->addBindValue(id);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "出货单修改购买厂商错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::updateInorderNoteWithId(QWidget * current, QString id, QString newNote){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("update inorderlist set notes=? where id=?");
    qry->addBindValue(newNote);
    qry->addBindValue(id);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "入货单修改备注错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::updateOutorderNoteWithId(QWidget *current, QString id, QString newNote){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("update outorderlist set notes=? where id=?");
    qry->addBindValue(newNote);
    qry->addBindValue(id);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "出货单修改备注错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::deleteInorderPorductsWithId(QWidget * current, QString id){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("delete from productinorderlist where id=?");
    qry->addBindValue(id);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "入货单删除产品列表错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

bool mysqlutil::deleteOutorderPorductsWithId(QWidget *current, QString id){
    if (!ifconnected){
        return false;
    }
    QSqlQuery * qry = new QSqlQuery(db);
    qry->prepare("delete from productoutorderlist where id=?");
    qry->addBindValue(id);
    qry->exec();

    if (qry->lastError().isValid()){
        QMessageBox::critical(current,"错误",
                              "出货单删除产品列表错误，错误信息\n"+qry->lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
        return false;
    }
    return true;
}

void mysqlutil::closeConnectionToMySql(){
    db.close();
    ifconnected = false;
}

