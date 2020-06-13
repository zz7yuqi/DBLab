#-------------------------------------------------
#
# Project created by QtCreator 2020-06-08T10:18:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dblab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mysqlutil.cpp \
    staff.cpp \
    caigoumainwindow.cpp \
    addnewinorder.cpp \
    checkallinorder.cpp \
    uutil.cpp \
    product.cpp \
    inorder.cpp \
    showinorderdetails.cpp \
    salesmanmainwindow.cpp \
    addnewoutorder.cpp \
    checkalloutorder.cpp \
    company.cpp \
    outorder.cpp \
    updateinorder.cpp \
    updateoutorder.cpp \
    adminmainwindow.cpp

HEADERS += \
        mainwindow.h \
    mysqlutil.h \
    staff.h \
    caigoumainwindow.h \
    addnewinorder.h \
    checkallinorder.h \
    uutil.h \
    product.h \
    inorder.h \
    showinorderdetails.h \
    salesmanmainwindow.h \
    addnewoutorder.h \
    checkalloutorder.h \
    company.h \
    outorder.h \
    updateinorder.h \
    updateoutorder.h \
    adminmainwindow.h

FORMS += \
        mainwindow.ui \
    caigoumainwindow.ui \
    addnewinorder.ui \
    checkallinorder.ui \
    showinorderdetails.ui \
    salesmanmainwindow.ui \
    addnewoutorder.ui \
    checkalloutorder.ui \
    updateinorder.ui \
    updateoutorder.ui \
    adminmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#selfadd
QT += sql
RC_ICONS = icon.ico

