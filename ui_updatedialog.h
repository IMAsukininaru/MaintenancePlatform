/********************************************************************************
** Form generated from reading UI file 'updatedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEDIALOG_H
#define UI_UPDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UpdateDialog
{
public:
    QPushButton *pushButton_update;
    QProgressBar *progressBar;
    QPushButton *pushButton_cancel;
    QLabel *label_info;
    QPushButton *pushButton_OK;

    void setupUi(QDialog *UpdateDialog)
    {
        if (UpdateDialog->objectName().isEmpty())
            UpdateDialog->setObjectName(QStringLiteral("UpdateDialog"));
        UpdateDialog->resize(353, 183);
        pushButton_update = new QPushButton(UpdateDialog);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));
        pushButton_update->setGeometry(QRect(50, 110, 93, 31));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_update->setFont(font);
        progressBar = new QProgressBar(UpdateDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 53, 321, 31));
        progressBar->setValue(24);
        pushButton_cancel = new QPushButton(UpdateDialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(200, 110, 93, 31));
        pushButton_cancel->setFont(font);
        label_info = new QLabel(UpdateDialog);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setGeometry(QRect(20, 23, 221, 31));
        QFont font1;
        font1.setPointSize(11);
        label_info->setFont(font1);
        pushButton_OK = new QPushButton(UpdateDialog);
        pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(130, 110, 93, 31));
        pushButton_OK->setFont(font);

        retranslateUi(UpdateDialog);

        QMetaObject::connectSlotsByName(UpdateDialog);
    } // setupUi

    void retranslateUi(QDialog *UpdateDialog)
    {
        UpdateDialog->setWindowTitle(QApplication::translate("UpdateDialog", "\346\225\205\351\232\234\346\235\241\347\233\256\346\233\264\346\226\260", 0));
        pushButton_update->setText(QApplication::translate("UpdateDialog", "\346\233\264\346\226\260", 0));
        pushButton_cancel->setText(QApplication::translate("UpdateDialog", "\345\217\226\346\266\210", 0));
        label_info->setText(QApplication::translate("UpdateDialog", "\346\255\243\345\234\250\346\233\264\346\226\260\346\225\205\351\232\234\346\235\241\347\233\256\344\277\241\346\201\257\350\241\250...", 0));
        pushButton_OK->setText(QApplication::translate("UpdateDialog", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class UpdateDialog: public Ui_UpdateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEDIALOG_H
