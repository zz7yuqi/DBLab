#ifndef SHOWINORDERDETAILS_H
#define SHOWINORDERDETAILS_H

#include <QWidget>
#include "inorder.h"
#include "outorder.h"

namespace Ui {
class ShowInOrderDetails;
}

class ShowInOrderDetails : public QWidget
{
    Q_OBJECT

public:
    explicit ShowInOrderDetails(QWidget *parent = nullptr, inorder * thisorder = nullptr);
    explicit ShowInOrderDetails(QWidget *parent = nullptr, outorder * thisorder = nullptr);
    ~ShowInOrderDetails();
    void inToOut();

private:
    Ui::ShowInOrderDetails *ui;
};

#endif // SHOWINORDERDETAILS_H
