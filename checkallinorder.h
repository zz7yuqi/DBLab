#ifndef CHECKALLINORDER_H
#define CHECKALLINORDER_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class CheckAllInOrder;
}

class CheckAllInOrder : public QWidget
{
    Q_OBJECT

public:
    explicit CheckAllInOrder(QWidget *parent = nullptr);
    ~CheckAllInOrder();

private slots:
    void on_btnRefresh_clicked();

    void on_btnCheck_clicked();

    void on_btnCancel_clicked();

    void on_btnChange_clicked();

private:
    Ui::CheckAllInOrder *ui;
    void showtableWidget();
};

#endif // CHECKALLINORDER_H
