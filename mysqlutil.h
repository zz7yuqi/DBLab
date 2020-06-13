#ifndef MYSQLUTIL_H
#define MYSQLUTIL_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include "staff.h"
#include "company.h"
#include "product.h"
#include "inorder.h"
#include "outorder.h"

class mysqlutil : public QObject
{
    Q_OBJECT
public:
    explicit mysqlutil(QObject *parent = nullptr);
    static void connectToMySql();
    static void closeConnectionToMySql();
    static Staff * getStuffWithId(QString id);
    static QList<company *> * getAllCompanyin();
    static QList<company *> * getAllCompanyout();
    static company * getCompanyinWithName(QString name);
    static company * getCompanyoutWithName(QString name);
    static QStringList getAllProductId();
    static product * getProductWithId(QString Id);
    static bool submitInOrder(QWidget * current ,inorder * content);
    static bool submitOutOrder(QWidget * current ,outorder * content);
    static bool submitInOrderProduct(QWidget * current, QString id, QString productid, int num);
    static bool submitOutOrderProduct(QWidget * current, QString id, QString productid, int num);
    static QList<inorder *>* getInordersWithStaffId(QString staffId, QString inorderId, QDate A, QDate B);
    static QList<outorder *>* getOutordersWithStaffId(QString staffId, QString outorderId, QDate A, QDate B);
    static bool deleteInorderItemWithId(QWidget * current,QString inorderId);
    static bool deleteOutorderItemWithId(QWidget * current,QString outorderId);
    static inorder * getInorderWithInorderID(QString id);
    static outorder * getOutorderWithOutorderID(QString id);
    static QList<product *> * getProductsInOrder(QString inorderId);
    static QList<product *> * getProductsOutOrder(QString outorderId);
    static bool updateInorderManufacturerWithId(QWidget * current, QString id, QString newManu);
    static bool updateOutorderReciptWithId(QWidget * current, QString id, QString newRecipt);
    static bool updateInorderNoteWithId(QWidget * current, QString id, QString newNote);
    static bool updateOutorderNoteWithId(QWidget * current, QString id, QString newNote);
    static bool deleteInorderPorductsWithId(QWidget * current, QString id);
    static bool deleteOutorderPorductsWithId(QWidget * current, QString id);

    static QSqlDatabase db;
    static bool ifconnected;
signals:

public slots:
};

#endif // MYSQLUTIL_H
