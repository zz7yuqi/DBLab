#ifndef SALESMANMAINWINDOW_H
#define SALESMANMAINWINDOW_H

#include <QMainWindow>
#include "mysqlutil.h"
#include "addnewoutorder.h"
#include "checkalloutorder.h"

namespace Ui {
class SalesmanMainWindow;
}

class SalesmanMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SalesmanMainWindow(QWidget *parent = nullptr);
    ~SalesmanMainWindow();

private slots:
    void on_actionBack_triggered();
    void on_actionNewoutOrder_triggered();

    void on_actionAlloutOrder_triggered();

signals:
    void backSignal();

private:
    Ui::SalesmanMainWindow *ui;

    int nowcur = -1;   //record for different pages
    AddNewoutOrder * addNewOutOrderWidget;
    CheckAlloutOrder * checkAllOutOrder;
    void hideSonWidget();
    void refresh();
};

#endif // SALESMANMAINWINDOW_H
