#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T08:27:31
#
#-------------------------------------------------

QT       += core gui\
                 sql\
                 network

#debug: LIBS += -L"D:\PostgreSQL\9.3\lib" -lqwtd
#release£ºLIBS += -L"D:\PostgreSQL\9.3\lib" -lqwt
#INCLUDEPATH += D:\PostgreSQL\9.3\include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MaintenancePlatform
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zdjldialog.cpp \
    updatedialog.cpp \
    logindialog.cpp \
    configdialog.cpp

HEADERS  += mainwindow.h \
    zdjldialog.h \
    updatedialog.h \
    logindialog.h \
    configdialog.h

FORMS    += mainwindow.ui \
    zdjldialog.ui \
    updatedialog.ui \
    logindialog.ui \
    configdialog.ui

RESOURCES += \
    icon.qrc
