/********************************************************************************
** Form generated from reading UI file 'configdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit_ip1;
    QLabel *label_2;
    QLineEdit *lineEdit_ip2;
    QLabel *label_3;
    QLineEdit *lineEdit_ip3;
    QLabel *label_4;
    QLineEdit *lineEdit_ip4;
    QLineEdit *lineEdit_port;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancel;
    QComboBox *comboBox_addr;
    QComboBox *comboBox_device;

    void setupUi(QDialog *ConfigDialog)
    {
        if (ConfigDialog->objectName().isEmpty())
            ConfigDialog->setObjectName(QStringLiteral("ConfigDialog"));
        ConfigDialog->resize(418, 254);
        label = new QLabel(ConfigDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 111, 30));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        lineEdit_ip1 = new QLineEdit(ConfigDialog);
        lineEdit_ip1->setObjectName(QStringLiteral("lineEdit_ip1"));
        lineEdit_ip1->setGeometry(QRect(150, 20, 41, 30));
        label_2 = new QLabel(ConfigDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 20, 16, 30));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        lineEdit_ip2 = new QLineEdit(ConfigDialog);
        lineEdit_ip2->setObjectName(QStringLiteral("lineEdit_ip2"));
        lineEdit_ip2->setGeometry(QRect(200, 20, 41, 30));
        label_3 = new QLabel(ConfigDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(240, 20, 16, 30));
        label_3->setFont(font1);
        lineEdit_ip3 = new QLineEdit(ConfigDialog);
        lineEdit_ip3->setObjectName(QStringLiteral("lineEdit_ip3"));
        lineEdit_ip3->setGeometry(QRect(250, 20, 41, 30));
        label_4 = new QLabel(ConfigDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(290, 20, 16, 30));
        label_4->setFont(font1);
        lineEdit_ip4 = new QLineEdit(ConfigDialog);
        lineEdit_ip4->setObjectName(QStringLiteral("lineEdit_ip4"));
        lineEdit_ip4->setGeometry(QRect(300, 20, 41, 30));
        lineEdit_port = new QLineEdit(ConfigDialog);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(150, 60, 91, 30));
        label_5 = new QLabel(ConfigDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 60, 91, 30));
        label_5->setFont(font);
        label_6 = new QLabel(ConfigDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 100, 91, 30));
        label_6->setFont(font);
        label_7 = new QLabel(ConfigDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 140, 91, 30));
        label_7->setFont(font);
        pushButton_OK = new QPushButton(ConfigDialog);
        pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(80, 200, 93, 41));
        pushButton_OK->setFont(font);
        pushButton_Cancel = new QPushButton(ConfigDialog);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(230, 200, 93, 41));
        pushButton_Cancel->setFont(font);
        comboBox_addr = new QComboBox(ConfigDialog);
        comboBox_addr->setObjectName(QStringLiteral("comboBox_addr"));
        comboBox_addr->setGeometry(QRect(150, 100, 231, 31));
        comboBox_device = new QComboBox(ConfigDialog);
        comboBox_device->setObjectName(QStringLiteral("comboBox_device"));
        comboBox_device->setGeometry(QRect(150, 140, 231, 31));

        retranslateUi(ConfigDialog);

        QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialog)
    {
        ConfigDialog->setWindowTitle(QApplication::translate("ConfigDialog", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        label->setText(QApplication::translate("ConfigDialog", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", 0));
        lineEdit_ip1->setText(QString());
        label_2->setText(QApplication::translate("ConfigDialog", ".", 0));
        lineEdit_ip2->setText(QString());
        label_3->setText(QApplication::translate("ConfigDialog", ".", 0));
        lineEdit_ip3->setText(QString());
        label_4->setText(QApplication::translate("ConfigDialog", ".", 0));
        lineEdit_ip4->setText(QString());
        lineEdit_port->setText(QString());
        label_5->setText(QApplication::translate("ConfigDialog", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        label_6->setText(QApplication::translate("ConfigDialog", "\351\241\271\347\233\256\345\220\215\347\247\260\357\274\232", 0));
        label_7->setText(QApplication::translate("ConfigDialog", "\350\256\276\345\244\207\345\220\215\347\247\260\357\274\232", 0));
        pushButton_OK->setText(QApplication::translate("ConfigDialog", "\347\241\256\345\256\232", 0));
        pushButton_Cancel->setText(QApplication::translate("ConfigDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
