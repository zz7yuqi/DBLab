#ifndef UPDATEOUTORDER_H
#define UPDATEOUTORDER_H

#include <QWidget>
#include "outorder.h"
#include "staff.h"

namespace Ui {
class UpdateoutOrder;
}

class UpdateoutOrder : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateoutOrder(QWidget *parent = nullptr, outorder * updatingOrder = nullptr);
    ~UpdateoutOrder();

private slots:
    void on_btnNewRow_clicked();

    void on_btnDelRow_clicked();

    void on_pushbtn_clicked();

private:
    Ui::UpdateoutOrder *ui;
    QStringList listForProId;
    Staff * owner;
    outorder * updatingOrder;
};

#endif // UPDATEOUTORDER_H
