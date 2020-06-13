#ifndef ADDNEWOUTORDER_H
#define ADDNEWOUTORDER_H

#include <QWidget>

namespace Ui {
class AddNewoutOrder;
}

class AddNewoutOrder : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewoutOrder(QWidget *parent = nullptr);
    ~AddNewoutOrder();

private slots:
    void on_btnNewRow_clicked();

    void on_btnDelRow_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddNewoutOrder *ui;
    QStringList listForProId;
};

#endif // ADDNEWOUTORDER_H
