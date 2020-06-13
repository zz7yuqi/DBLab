#ifndef CAIGOUMAINWINDOW_H
#define CAIGOUMAINWINDOW_H

#include <QMainWindow>
#include "addnewinorder.h"
#include "checkallinorder.h"
#include "staff.h"

namespace Ui {
class CaiGouMainWindow;
}

class CaiGouMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CaiGouMainWindow(QWidget *parent = nullptr);
    ~CaiGouMainWindow();
    void setusingStaff(Staff * staff);
private:
    Staff * usingStaff;
    int nowcur = -1;   //record for different pages
    AddNewInOrder * addNewInOrderWidget;
    CheckAllInOrder * checkAllInOrder;
    void hideSonWidget();
    void refresh();
private slots:
    void on_actionNewInOrder_triggered();


    void on_actionCheckAllInOrder_triggered();

    void on_actionBack_triggered();

signals:
    void backSignal();
private:
    Ui::CaiGouMainWindow *ui;
};

#endif // CAIGOUMAINWINDOW_H
