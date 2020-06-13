#include "mainwindow.h"
#include <QApplication>
#include "mysqlutil.h"
#include "caigoumainwindow.h"
#include "uutil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mysqlutil::connectToMySql();
    //uutil::_staff = new Staff("00002", "张三", 1, "1111");
    MainWindow w;
    //CaiGouMainWindow w;
    w.show();
    return a.exec();
}
