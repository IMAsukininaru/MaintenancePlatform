#include "updatedialog.h"
#include "ui_updatedialog.h"

#include <QSettings>
#include <QTextCodec>
UpdateDialog::UpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);

    ui->progressBar->setVisible(false);
    ui->label_info->setVisible(false);
    ui->pushButton_OK->setVisible(false);
    openIni();
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::openIni()
{
    QSettings *configIniRead = new QSettings("./setting.ini", QSettings::IniFormat);
    configIniRead->setIniCodec(QTextCodec::codecForName("GB2312"));   //读写ini文件中的中文
    //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    settingValue.ip1 = configIniRead->value("/network/ip1").toString().trimmed();
    settingValue.ip2 = configIniRead->value("/network/ip2").toString().trimmed();
    settingValue.ip3 = configIniRead->value("/network/ip3").toString().trimmed();
    settingValue.ip4 = configIniRead->value("/network/ip4").toString().trimmed();
    settingValue.port = configIniRead->value("/network/port").toString().trimmed();

//    settingValue.device = configIniRead->value("/other/device").toString().trimmed();
//    settingValue.address = configIniRead->value("/other/address").toString().trimmed();

    delete configIniRead;
}
//打开SQLite数据库
void UpdateDialog::openSqlite()
{
    //若数据库文件不存在，程序退出
    QFile db_file("./kn_maintenance.db");
    if(!db_file.exists())
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库文件不存在！"),QString::fromLocal8Bit("确定"));
        exit(-1);
    }
    if(QSqlDatabase::contains("save_connection"))
        lite_db = QSqlDatabase::database("save_connection");
    else
        lite_db = QSqlDatabase::addDatabase("QSQLITE","save_connection"); //使用sqlite数据库

    lite_db.setDatabaseName(db_file.fileName());  //建立的数据库

    bool ok = lite_db.open();  //连接数据库
    if(!ok)
    {
        qDebug()<<lite_db.lastError();
        qFatal("failed to connect.") ;
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库连接失败！"),QString::fromLocal8Bit("确定"));
        exit(-1);
    }
}

//打开 postgresql 数据库
void UpdateDialog::openPostgreSql()
{
    if(QSqlDatabase::contains("update_connection"))
        post_db = QSqlDatabase::database("update_connection");
    else
        post_db = QSqlDatabase::addDatabase("QPSQL","update_connection");

//    post_db.setHostName("localhost");
    post_db.setHostName(settingValue.ip1+"."+settingValue.ip2+"."+settingValue.ip3+"."+settingValue.ip4);
    post_db.setDatabaseName("main");
    post_db.setUserName("postgres");
    post_db.setPassword("yukiyuki");
    bool ok = post_db.open();

    if(!ok)
    {
        qDebug()<<post_db.lastError();
        qFatal("failed to connect.") ;
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("PostgreSql 数据库连接失败！"),QString::fromLocal8Bit("确定"));
        exit(-1);
    }
}

void UpdateDialog::on_pushButton_update_clicked()
{
    openPostgreSql();
    openSqlite();

    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(1);
    ui->label_info->setVisible(true);
    ui->label_info->setText(QString::fromLocal8Bit("正在更新故障条目信息表..."));

    QSqlQuery query(post_db);
    QSqlQuery query_s(lite_db);

//    QDateTime datetime = QDateTime::currentDateTime();
//    QString dt_str = datetime.toString("yyyy-MM-dd hh:mm:ss");

    //更新故障类型表
    QString type_id, gz_type;
    query_s.clear();
    query_s.prepare("delete from lxb");   //清空 故障类型表
    if(!query_s.exec())
    {
        qDebug()<<query_s.lastError();
    }

    query.clear();
    query.prepare("select * from \"knAutoDocApp_glitchtype\" "); //从服务器数据库中读取全部 故障类型 数据
    if(!query.exec())
    {
        qDebug()<<query.lastError();
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络连接失败！"),QString::fromLocal8Bit("确定"));
        return;
    }
    while(query.next())
    {
        gz_type = query.value("type").toString();
        type_id = query.value("id").toString();
        query_s.clear();
        query_s.prepare("insert into lxb (id, type)  values (:id, :type)" );
        query_s.bindValue(":type", gz_type);
        query_s.bindValue(":id", type_id);
        if(!query_s.exec())
        {
            qDebug()<<query_s.lastError();
        }
    }


    //更新项目名称表
    QString xm_id, xm_name;
    query_s.clear();
    query_s.prepare("delete from xmb");   //清空 项目名称表
    if(!query_s.exec())
    {
        qDebug()<<query_s.lastError();
    }

    query.clear();
    query.prepare("select * from \"knAutoDocApp_projparam\" "); //从服务器数据库中读取全部 项目名称 数据
    if(!query.exec())
    {
        qDebug()<<query.lastError();
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络连接失败！"),QString::fromLocal8Bit("确定"));
        return;
    }
    while(query.next())
    {
        xm_name = query.value("name").toString();
        xm_id = query.value("id").toString();
        query_s.clear();
        query_s.prepare("insert into xmb (id, projname)  values (:id, :name)" );
        query_s.bindValue(":name", xm_name);
        query_s.bindValue(":id", xm_id);
        if(!query_s.exec())
        {
            qDebug()<<query_s.lastError();
        }
    }


    //更新设备名称表
    QString sb_id, sb_name;
    query_s.clear();
    query_s.prepare("delete from sbb");   //清空 设备名称表
    if(!query_s.exec())
    {
        qDebug()<<query_s.lastError();
    }

    query.clear();
    query.prepare("select * from \"knAutoDocApp_deviceparam\" "); //从服务器数据库中读取全部 设备名称 数据
    if(!query.exec())
    {
        qDebug()<<query.lastError();
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络连接失败！"),QString::fromLocal8Bit("确定"));
        return;
    }
    while(query.next())
    {
        sb_name = query.value("name").toString();
        sb_id = query.value("id").toString();
        query_s.clear();
        query_s.prepare("insert into sbb (id, devicename)  values (:id, :name)" );
        query_s.bindValue(":name", sb_name);
        query_s.bindValue(":id", sb_id);
        if(!query_s.exec())
        {
            qDebug()<<query_s.lastError();
        }
    }



    QString current_dt = "1900-01-01 00:00:00";
    //更新故障条目信息表
    query_s.clear();
    query_s.prepare("select datetime from gztmxxb order by datetime desc");
    if(!query_s.exec())
    {
        qDebug()<<query_s.lastError();
    }
    if(query_s.next())
        current_dt = query_s.value(0).toString();

    query.clear();
    query.prepare("select * from \"knAutoDocApp_glitch\" where datetime >'"+current_dt+ "'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络连接失败！"),QString::fromLocal8Bit("确定"));
        return;
    }
    QString id, type, code, name, description, datetime, user_id;
    bool isDeleted = false;

    int num = query.size();
    ui->progressBar->setRange(0, num);
    int i = 1;

    while(query.next())
    {
        ui->progressBar->setValue(i++);

        id = query.value("id").toString();
        isDeleted = query.value("isDeleted").toBool();
        if(isDeleted == true)  //该条目被删除,则修改本地库中的标志位
        {
            query_s.clear();
            query_s.prepare("update gztmxxb set isDeleted = :isDeleted where id == '"+ id +"'");
            query_s.bindValue(":isDeleted" , "true");
            if(!query_s.exec())
            {
                qDebug()<<query_s.lastError();
            }
        }
        else  //删除标志位 false,在本地库中新增记录
        {
            //需要判断该条记录在本地库中是否已经存在，因为sqlite库中时间精度不够
            query_s.clear();
            query_s.prepare("select * from gztmxxb where id == '"+ id +"'");
            if(!query_s.exec())
            {
                qDebug()<<query_s.lastError();
            }
            if(query_s.next())
            {
                continue;   //跳过该条记录
            }

            type = query.value("type").toString();
            code = query.value("code").toString();
            name = query.value("name").toString();
            description = query.value("description").toString();
            datetime = query.value("datetime").toString();
            user_id = query.value("user_id").toString();

            query_s.clear();
            query_s.prepare("insert into gztmxxb (datetime, id, TMID, name, type, description, UserID, isDeleted) "
                          "values (:datetime, :id, :TMID, :name, :type, :description, :UserID, :isDeleted)" );
            query_s.bindValue(":datetime", datetime);
            query_s.bindValue(":id", id);
            query_s.bindValue(":TMID", code);
            query_s.bindValue(":name", name);
            query_s.bindValue(":type", type);
            query_s.bindValue(":description", description);
            query_s.bindValue(":UserID", user_id);
            query_s.bindValue(":isDeleted", "false");

            if(!query_s.exec())
            {
                qDebug()<<query_s.lastError();
            }
        }
    }

    //更新故障操作指南表
    ui->label_info->setText(QString::fromLocal8Bit("正在更新故障操作指南表..."));
    ui->progressBar->setValue(1);
    current_dt = "1900-01-01 00:00:00";  //重置默认时间

    query_s.clear();
    query_s.prepare("select datetime from gzczznb order by datetime desc");
    if(!query_s.exec())
    {
        qDebug()<<query_s.lastError();
    }
    if(query_s.next())
        current_dt = query_s.value(0).toString();

    query.clear();
    query.prepare("select * from \"knAutoDocApp_glitchnode\" where \"lastUpdateDatetime\" >'"+current_dt+ "'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络连接失败！"),QString::fromLocal8Bit("确定"));
        return;
    }

    num = query.size();
    ui->progressBar->setRange(0, num);
    i = 1;

    QString step, title, nextOK, nextFalse, lastUpdateDatetime, glitch_id;
    while(query.next())
    {
        ui->progressBar->setValue(i++);

        id = query.value("id").toString();
        isDeleted = query.value("isDeleted").toBool();
        if(isDeleted == true)  //该 操作 被删除,则修改本地库中的标志位
        {
            query_s.clear();
            query_s.prepare("update gzczznb set isDeleted = :isDeleted where id == '"+ id +"'");
            query_s.bindValue(":isDeleted" , "true");
            if(!query_s.exec())
            {
                qDebug()<<query_s.lastError();
            }
        }
        else
        {
            //需要判断该条记录在本地库中是否已经存在，因为sqlite库中时间精度不够
            query_s.clear();
            query_s.prepare("select * from gzczznb where id == '"+ id +"'");
            if(!query_s.exec())
            {
                qDebug()<<query_s.lastError();
            }
            if(query_s.next())
            {
                continue;   //跳过该条记录
            }

            step = query.value("step").toString();
            title = query.value("title").toString();
            nextOK = query.value("nextOK").toString();
            nextFalse = query.value("nextFalse").toString();
            lastUpdateDatetime = query.value("lastUpdateDatetime").toString();
            glitch_id = query.value("glitch_id").toString();

            query_s.clear();
            query_s.prepare("insert into gzczznb (datetime, id, CZID, title, YCZID, NCZID, TMID, isDeleted) "
                          "values (:datetime, :id, :CZID, :title, :YCZID, :NCZID, :TMID, :isDeleted)" );
            query_s.bindValue(":datetime", lastUpdateDatetime);
            query_s.bindValue(":id", id);
            query_s.bindValue(":CZID", step);
            query_s.bindValue(":title", title);
            query_s.bindValue(":YCZID", nextOK);
            query_s.bindValue(":NCZID", nextFalse);
            query_s.bindValue(":TMID", glitch_id);
            query_s.bindValue(":isDeleted", "false");

            if(!query_s.exec())
            {
                qDebug()<<query_s.lastError();
            }
        }

    }
    if(num == 0)
    {
        ui->progressBar->setRange(0, 1);
        ui->progressBar->setValue(1);
    }

    emit update_end();

    ui->label_info->setText(QString::fromLocal8Bit("故障信息更新完毕！"));
    ui->pushButton_update->setVisible(false);
    ui->pushButton_cancel->setVisible(false);
    ui->pushButton_OK->setVisible(true);

}

void UpdateDialog::on_pushButton_cancel_clicked()
{
    lite_db.close();
    post_db.close();
    close();
}

void UpdateDialog::on_pushButton_OK_clicked()
{
    on_pushButton_cancel_clicked();
}
