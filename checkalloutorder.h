#ifndef CHECKALLOUTORDER_H
#define CHECKALLOUTORDER_H

#include <QWidget>

namespace Ui {
class CheckAlloutOrder;
}

class CheckAlloutOrder : public QWidget
{
    Q_OBJECT

public:
    explicit CheckAlloutOrder(QWidget *parent = nullptr);
    ~CheckAlloutOrder();

private slots:
    void on_btnCheck_clicked();

    void on_btnCancel_clicked();

    void on_btnRefresh_clicked();

    void on_btnChange_clicked();

private:
    Ui::CheckAlloutOrder *ui;
    void showtableWidget();
};

#endif // CHECKALLOUTORDER_H
