#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->label_checked->setVisible(false);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_toolButton_OK_clicked()
{
    QString userName = ui->lineEdit_name->text().trimmed();
    QString pwd = ui->lineEdit_pwd->text().trimmed();
//    qDebug()<<"login";
    if(userName == "")
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请输入账号！"),QString::fromLocal8Bit("确定"));
        return;
    }
    emit login(userName, pwd);
}

void LoginDialog::on_toolButton_Cancel_clicked()
{
    if(ui->label_checked->isVisible())//登录后再次打开窗口，取消按钮只是关闭窗口
        accept();
    else   //退出程序
        exit(-1);
}

void LoginDialog::close_dialog()
{        
    emit destroy();
}

void LoginDialog::set_UI(QString UserID)
{
    ui->label_checked->setText(UserID +QString::fromLocal8Bit("已登录"));
    ui->label_checked->setVisible(true);
}
