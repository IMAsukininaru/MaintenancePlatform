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
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("�������˺ţ�"),QString::fromLocal8Bit("ȷ��"));
        return;
    }
    emit login(userName, pwd);
}

void LoginDialog::on_toolButton_Cancel_clicked()
{
    if(ui->label_checked->isVisible())//��¼���ٴδ򿪴��ڣ�ȡ����ťֻ�ǹرմ���
        accept();
    else   //�˳�����
        exit(-1);
}

void LoginDialog::close_dialog()
{        
    emit destroy();
}

void LoginDialog::set_UI(QString UserID)
{
    ui->label_checked->setText(UserID +QString::fromLocal8Bit("�ѵ�¼"));
    ui->label_checked->setVisible(true);
}
