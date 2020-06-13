#ifndef ADDNEWINORDER_H
#define ADDNEWINORDER_H

#include <QWidget>
#include "staff.h"
#include <QTableWidgetItem>
namespace Ui {
class AddNewInOrder;
}

class AddNewInOrder : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewInOrder(QWidget *parent = nullptr);
    ~AddNewInOrder();
    void setusingStaff(Staff * staff);

private slots:
    void on_btnNewRow_clicked();

    void on_btnDelRow_clicked();



    void on_pushButton_clicked();

private:
    Ui::AddNewInOrder *ui;
    Staff * usingStaff;
    QStringList listForProId;
};

#endif // ADDNEWINORDER_H
