#include "configdialog.h"
#include "ui_configdialog.h"

#include <QMessageBox>
#include <QCompleter>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_pushButton_Cancel_clicked()
{
    close();
}

void ConfigDialog::on_pushButton_OK_clicked()
{
    if(ui->lineEdit_ip1->text().trimmed() == ""||
            ui->lineEdit_ip2->text().trimmed() == ""
            ||ui->lineEdit_ip3->text().trimmed() == ""
            ||ui->lineEdit_ip4->text().trimmed() == ""
            ||ui->lineEdit_port->text().trimmed() == "")
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"),
                              QString::fromLocal8Bit("请输入服务器地址及端口号！"),
                              QString::fromLocal8Bit("确定"));
        return;
    }
    emit save(this->get_value());
}

void ConfigDialog::close_dialog()
{
    emit destroy();
}

void ConfigDialog::set_value(ConfigValue value, QStringList
                             projnames, QStringList devnames)
{
    ui->lineEdit_ip1->setText(value.ip1);
    ui->lineEdit_ip2->setText(value.ip2);
    ui->lineEdit_ip3->setText(value.ip3);
    ui->lineEdit_ip4->setText(value.ip4);
    ui->lineEdit_port->setText(value.port);
//    ui->comboBox_device->setItemText((value.device).toUtf8());  //显示中文
//    ui->comboBox_addr->setText((value.address).toUtf8());

    ui->comboBox_addr->addItems(projnames);
    ui->comboBox_addr->setEditable(true);
    QCompleter *proj_completer = new QCompleter(projnames, this);
    ui->comboBox_addr->setCompleter(proj_completer);
    ui->comboBox_addr->setCurrentText((value.address).toUtf8());

    ui->comboBox_device->addItems(devnames);
    ui->comboBox_device->setEditable(true);
    QCompleter *dev_completer = new QCompleter(devnames, this);
    ui->comboBox_device->setCompleter(dev_completer);
    ui->comboBox_device->setCurrentText((value.device).toUtf8());
}

ConfigValue ConfigDialog::get_value()
{
    ConfigValue value;

    value.ip1 = ui->lineEdit_ip1->text().trimmed() ;
    value.ip2 = ui->lineEdit_ip2->text().trimmed() ;
    value.ip3 = ui->lineEdit_ip3->text().trimmed() ;
    value.ip4 = ui->lineEdit_ip4->text().trimmed() ;
    value.port = ui->lineEdit_port->text().trimmed();
    value.device = ui->comboBox_device->currentText().trimmed();
    value.address = ui->comboBox_addr->currentText().trimmed();

    return value;
}
