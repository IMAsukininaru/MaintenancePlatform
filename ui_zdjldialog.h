/********************************************************************************
** Form generated from reading UI file 'zdjldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZDJLDIALOG_H
#define UI_ZDJLDIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ZDJLDialog
{
public:
    QTableWidget *tableWidget;
    QLabel *label_2;
    QLabel *label_3;
    QDateEdit *dateEdit_start;
    QDateEdit *dateEdit_end;
    QPushButton *pushButton_send;
    QPushButton *pushButton_cancel;
    QTextBrowser *textBrowser;
    QToolButton *toolButton_del;

    void setupUi(QDialog *ZDJLDialog)
    {
        if (ZDJLDialog->objectName().isEmpty())
            ZDJLDialog->setObjectName(QStringLiteral("ZDJLDialog"));
        ZDJLDialog->resize(1000, 702);
        tableWidget = new QTableWidget(ZDJLDialog);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 60, 961, 401));
        label_2 = new QLabel(ZDJLDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 20, 72, 15));
        label_3 = new QLabel(ZDJLDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(280, 20, 72, 15));
        dateEdit_start = new QDateEdit(ZDJLDialog);
        dateEdit_start->setObjectName(QStringLiteral("dateEdit_start"));
        dateEdit_start->setGeometry(QRect(120, 20, 110, 22));
        dateEdit_start->setProperty("showGroupSeparator", QVariant(true));
        dateEdit_start->setCurrentSection(QDateTimeEdit::DaySection);
        dateEdit_start->setCalendarPopup(true);
        dateEdit_start->setDate(QDate(2015, 11, 1));
        dateEdit_end = new QDateEdit(ZDJLDialog);
        dateEdit_end->setObjectName(QStringLiteral("dateEdit_end"));
        dateEdit_end->setGeometry(QRect(360, 20, 110, 22));
        dateEdit_end->setCurrentSection(QDateTimeEdit::DaySection);
        dateEdit_end->setCalendarPopup(true);
        dateEdit_end->setCurrentSectionIndex(2);
        dateEdit_end->setDate(QDate(2015, 11, 11));
        pushButton_send = new QPushButton(ZDJLDialog);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setGeometry(QRect(850, 560, 93, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_send->setFont(font);
        pushButton_cancel = new QPushButton(ZDJLDialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(850, 630, 93, 41));
        pushButton_cancel->setFont(font);
        textBrowser = new QTextBrowser(ZDJLDialog);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 470, 781, 211));
        toolButton_del = new QToolButton(ZDJLDialog);
        toolButton_del->setObjectName(QStringLiteral("toolButton_del"));
        toolButton_del->setGeometry(QRect(850, 490, 91, 41));
        toolButton_del->setFont(font);
        toolButton_del->setIconSize(QSize(60, 60));

        retranslateUi(ZDJLDialog);

        QMetaObject::connectSlotsByName(ZDJLDialog);
    } // setupUi

    void retranslateUi(QDialog *ZDJLDialog)
    {
        ZDJLDialog->setWindowTitle(QApplication::translate("ZDJLDialog", "\350\257\212\346\226\255\350\256\260\345\275\225\347\256\241\347\220\206", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QApplication::translate("ZDJLDialog", "\345\272\217\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QApplication::translate("ZDJLDialog", "\350\256\260\345\275\225\347\274\226\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QApplication::translate("ZDJLDialog", "\346\225\205\351\232\234\344\273\243\347\240\201", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QApplication::translate("ZDJLDialog", "\346\225\205\351\232\234\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QApplication::translate("ZDJLDialog", "\344\272\247\345\223\201\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem5->setText(QApplication::translate("ZDJLDialog", "\346\227\266\351\227\264", 0));
        label_2->setText(QApplication::translate("ZDJLDialog", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\232", 0));
        label_3->setText(QApplication::translate("ZDJLDialog", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", 0));
        pushButton_send->setText(QApplication::translate("ZDJLDialog", "\344\270\212\344\274\240", 0));
        pushButton_cancel->setText(QApplication::translate("ZDJLDialog", "\345\217\226\346\266\210", 0));
        toolButton_del->setText(QApplication::translate("ZDJLDialog", "\345\210\240\351\231\244", 0));
    } // retranslateUi

};

namespace Ui {
    class ZDJLDialog: public Ui_ZDJLDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZDJLDIALOG_H
