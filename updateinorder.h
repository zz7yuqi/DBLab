#ifndef UPDATEINORDER_H
#define UPDATEINORDER_H

#include <QWidget>
#include "inorder.h"
#include "staff.h"

namespace Ui {
class UpdateinOrder;
}

class UpdateinOrder : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateinOrder(QWidget *parent = nullptr, inorder * updatingOrder = nullptr);

    ~UpdateinOrder();

private slots:
    void on_btnNewRow_clicked();

    void on_btnDelRow_clicked();

    void on_pushButton_clicked();

private:
    Ui::UpdateinOrder *ui;
    QStringList listForProId;
    Staff * owner;
    inorder * updatingOrder;
};

#endif // UPDATEINORDER_H
