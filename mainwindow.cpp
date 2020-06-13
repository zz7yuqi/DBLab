#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysqlutil.h"
#include <QMessageBox>
#include <QDebug>
#include <QRadioButton>
#include "caigoumainwindow.h"
#include "uutil.h"
#include "salesmanmainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->radioButton,&QRadioButton::toggled,this,[=](){
        if (this->ui->radioButton->isChecked()){
            this->ui->lineEditPwd->setEchoMode(QLineEdit::Password);
        }
        else this->ui->lineEditPwd->setEchoMode(QLineEdit::Normal);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLogin_clicked()
{
    QString inputId = this->ui->lineEditId->text();
    QString inputPwd = this->ui->lineEditPwd->text();
    Staff * staff = mysqlutil::getStuffWithId(inputId);  //get stuff with inputId

    if (staff == nullptr){
        //check if connected
        if (!mysqlutil::ifconnected){
            //db is not connected
            //show messages
            QMessageBox::critical(this,"错误","数据库未连接");
            return;
        }
        else{
            //illegal id
            //show messages
            QMessageBox::information(this,"information","id不存在！请重新输入");
            return;
        }
    }
    //check pwd
    if (staff->getPwd()==inputPwd){
        uutil::setStaff(*staff);
        if (QMessageBox::information(this,"info","登录成功！") == QMessageBox::Ok){
            //check identity then turn to new scene
            if (staff->getIdentity() == 0){
                qDebug()<<Staff::identities[0]<<endl;
            }
            else if (staff->getIdentity() == 1){
                //采购员
                //qDebug()<<Staff::identities[1]<<endl;

                CaiGouMainWindow * subWindow = new CaiGouMainWindow();
                //qDebug() << uutil::_staff->getId();
                connect(subWindow, &CaiGouMainWindow::backSignal, this, [=](){
                    subWindow->close();
                    this->show();
                    this->ui->lineEditPwd->clear();
                });
                this->hide();
                subWindow->show();

            }
            else if(staff->getIdentity() == 2){
                //qDebug()<<Staff::identities[2]<<endl;
                //销售
                SalesmanMainWindow * subWindow = new SalesmanMainWindow();
                connect(subWindow, &SalesmanMainWindow::backSignal, this, [=](){
                    subWindow->close();
                    this->show();
                    this->ui->lineEditPwd->clear();
                });
                this->hide();
                subWindow->show();
            }

        }

    }
}

void MainWindow::on_btnExit_clicked()
{
    qApp->quit();
}

