/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QGraphicsView *graphicsView;
    QToolButton *toolButton_OK;
    QToolButton *toolButton_Cancel;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QLabel *label_2;
    QLineEdit *lineEdit_pwd;
    QLabel *label_checked;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(397, 222);
        QFont font;
        font.setPointSize(14);
        LoginDialog->setFont(font);
        graphicsView = new QGraphicsView(LoginDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(40, 40, 72, 72));
        graphicsView->setAutoFillBackground(true);
        graphicsView->setStyleSheet(QStringLiteral("background-image: url(:/icon/icon/login.png);"));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setFrameShadow(QFrame::Sunken);
        graphicsView->setLineWidth(0);
        toolButton_OK = new QToolButton(LoginDialog);
        toolButton_OK->setObjectName(QStringLiteral("toolButton_OK"));
        toolButton_OK->setGeometry(QRect(90, 150, 81, 41));
        QFont font1;
        font1.setPointSize(12);
        toolButton_OK->setFont(font1);
        toolButton_Cancel = new QToolButton(LoginDialog);
        toolButton_Cancel->setObjectName(QStringLiteral("toolButton_Cancel"));
        toolButton_Cancel->setGeometry(QRect(240, 150, 81, 41));
        toolButton_Cancel->setFont(font1);
        layoutWidget = new QWidget(LoginDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 40, 231, 123));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setVerticalSpacing(12);
        formLayout->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_name = new QLineEdit(layoutWidget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_name);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_pwd = new QLineEdit(layoutWidget);
        lineEdit_pwd->setObjectName(QStringLiteral("lineEdit_pwd"));
        lineEdit_pwd->setInputMethodHints(Qt::ImhHiddenText);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_pwd);

        label_checked = new QLabel(LoginDialog);
        label_checked->setObjectName(QStringLiteral("label_checked"));
        label_checked->setGeometry(QRect(140, 10, 201, 30));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_checked->setFont(font2);
        label_checked->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        label_checked->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QWidget::setTabOrder(lineEdit_name, lineEdit_pwd);
        QWidget::setTabOrder(lineEdit_pwd, toolButton_OK);
        QWidget::setTabOrder(toolButton_OK, toolButton_Cancel);
        QWidget::setTabOrder(toolButton_Cancel, graphicsView);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "\347\224\250\346\210\267\347\231\273\345\275\225", 0));
        toolButton_OK->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", 0));
        toolButton_Cancel->setText(QApplication::translate("LoginDialog", "\345\217\226\346\266\210", 0));
        label->setText(QApplication::translate("LoginDialog", "\350\264\246 \345\217\267\357\274\232", 0));
        label_2->setText(QApplication::translate("LoginDialog", "\345\257\206 \347\240\201\357\274\232", 0));
        label_checked->setText(QApplication::translate("LoginDialog", "\345\267\262\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
