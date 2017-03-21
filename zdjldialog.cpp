#include "zdjldialog.h"
#include "ui_zdjldialog.h"

#include <QSettings>
#include <QTextCodec>

ZDJLDialog::ZDJLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZDJLDialog)
{
    ui->setupUi(this);
    openSqlite();
    openIni();
    ui->dateEdit_start->setDate(QDate().currentDate().addMonths(-1));
    ui->dateEdit_end->setDate(QDate().currentDate());
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //不能对表格内容进行修改
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为只能选中一个目标
    ui->tableWidget->setColumnWidth(0,1);  //指定某个列的大小
    ui->tableWidget->setColumnWidth(1,40);
    ui->tableWidget->setColumnWidth(2,230); //记录编号
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,200);
    ui->tableWidget->setColumnWidth(5,180);
    ui->tableWidget->setColumnWidth(6,170);
    mZDID = "";//当前诊断记录编号
    ui->toolButton_del->setEnabled(false);
//    init(); //在日期控件中已经初始化过了
}

ZDJLDialog::~ZDJLDialog()
{
//    tcpSocket->close();
    delete ui;
}

void ZDJLDialog::openIni()
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
void ZDJLDialog::openSqlite()
{
    //若数据库文件不存在，程序退出
    QFile db_file("./kn_maintenance.db");
    if(!db_file.exists())
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误")
                              , QString::fromLocal8Bit("数据库文件不存在！")
                              ,QString::fromLocal8Bit("确定"));
        exit(-1);
    }
    if(QSqlDatabase::contains("save_connection"))
        lite_db = QSqlDatabase::database("save_connection");
    else
        lite_db = QSqlDatabase::addDatabase("QSQLITE"
                                            ,"save_connection");
    //使用sqlite数据库
    lite_db.setDatabaseName(db_file.fileName());  //建立的数据库
    bool ok = lite_db.open();  //连接数据库
    if(!ok)
    {
        qDebug()<<lite_db.lastError();
        qFatal("failed to connect.") ;
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误")
                              , QString::fromLocal8Bit("数据库连接失败！")
                              ,QString::fromLocal8Bit("确定"));
        exit(-1);
    }
}

//打开 postgresql 数据库
void ZDJLDialog::openPostgreSql()
{
    if(QSqlDatabase::contains("update_connection"))
        post_db = QSqlDatabase::database("update_connection");
    else
        post_db = QSqlDatabase::addDatabase("QPSQL","update_connection");
    post_db.setHostName(settingValue.ip1+"."+settingValue.ip2+"."
                        +settingValue.ip3+"."+settingValue.ip4);
//    post_db.setHostName("192.168.3.8");
    post_db.setDatabaseName("main");
    post_db.setUserName("postgres");
    post_db.setPassword("yukiyuki");
    bool ok = post_db.open();
    if(!ok)
    {
        qDebug()<<post_db.lastError();
        qFatal("failed to connect.") ;
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误")
                              , QString::fromLocal8Bit("PostgreSql 数据库连接失败！")
                              ,QString::fromLocal8Bit("确定"));
        exit(-1);
    }
}

void ZDJLDialog::init()
{
    QString time_start, time_end, str;
    time_start = ui->dateEdit_start->date().toString("yyyy-MM-dd");
    time_end = ui->dateEdit_end->date().toString("yyyy-MM-dd");
    time_end = time_end + " 23:59:59";

    QSqlQuery query(lite_db);
    query.clear();
    query.prepare("select * from gzzdjlb where isDeleted =='false' and time >='"
                  +time_start+ "' and time <='"+time_end+ "'");

    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    int i = 1;

    while(query.next())
    {
        ui->tableWidget->setRowCount(i);     //设置行数
        ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(QString::number(i, 10)));

        str = query.value("ZDID").toString();
        ui->tableWidget->setItem(i-1,2,new QTableWidgetItem(str));
        str = query.value("TMID").toString();
        ui->tableWidget->setItem(i-1,3,new QTableWidgetItem(str));
        str = query.value("name").toString();
        ui->tableWidget->setItem(i-1,4,new QTableWidgetItem(str));
        str = query.value("device").toString();
        ui->tableWidget->setItem(i-1,5,new QTableWidgetItem(str));
        str = query.value("time").toString();
        ui->tableWidget->setItem(i-1,6,new QTableWidgetItem(str));
        i++;
    }

//    this->tcpSocket = new QTcpSocket(this);

//    //这里我是采用程序启动就自访问服务端（也可根据实际情况采用手动连接手动输入服务端ip的方式。）
//    newTCPConnect();
//    //readyRead()表示服务端发送数据过来即发动信号，接着revData()进行处理。
//    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
//    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
//            this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void ZDJLDialog::revData()
{
   QString datas = tcpSocket->readAll();//接收字符串数据。
//   ui->lineEdit_2->setText(datas);//显示字符串数据。
}

void ZDJLDialog::newTCPConnect()
{
   tcpSocket->abort();
   tcpSocket->connectToHost("127.0.0.1",6666);
   //这里可以根据实际情况在用户界面上进行输入。
}

void ZDJLDialog::displayError(QAbstractSocket::SocketError)
{
   qDebug()<<tcpSocket->errorString();
   tcpSocket->close();
}

void ZDJLDialog::on_pushButton_send_clicked()
{
    openPostgreSql();

    QString time_start, time_end;
    time_start = ui->dateEdit_start->date().toString("yyyy-MM-dd");
    time_end = ui->dateEdit_end->date().toString("yyyy-MM-dd");
    time_end = time_end + " 23:59:59";

    QSqlQuery query(post_db);
    QSqlQuery query_s(lite_db);

    int i = 0;
    query_s.clear();
    query_s.prepare("select * from gzzdjlb where isDeleted =='false' and time >='"
                    +time_start+ "' and time <='"+time_end+ "'");
    if(!query_s.exec())
    {
        qDebug()<<query_s.lastError();
    }
    QString id, CaoZBuZ, CaoZNeiR,device, datetime,address,code,name,type;
    int  userid;

    QString step, result, title, description;
    bool tf;
    while(query_s.next())
    {
        userid = query_s.value("UserID").toInt();
        id = query_s.value("ZDID").toString();
        CaoZBuZ = query_s.value("CaoZBZ").toString();
        CaoZNeiR = query_s.value("CZNR").toString();
        device = query_s.value("device").toString();
        datetime = query_s.value("time").toString();
        address = query_s.value("address").toString();
        code = query_s.value("TMID").toString();
        name = query_s.value("name").toString();
        type = query_s.value("type").toString();

        query.clear();
        query.prepare("select * from \"knAutoDocApp_operation\" where id = '"+ id +"'");
        //注意sql语句中的 等于
        if(!query.exec())
        {
            qDebug()<<query.lastError();
            QMessageBox::critical(NULL, QString::fromLocal8Bit("错误")
                                  , QString::fromLocal8Bit("网络连接失败！")
                                  ,QString::fromLocal8Bit("确定"));
            return;
        }
        if(query.next())//本条诊断记录在 服务器数据库 中 存在
            continue;   //跳过，不保存

        //否则插入新纪录
        i ++;
        query.clear();
        query.prepare("insert into \"knAutoDocApp_operation\" "
                      "(id, datetime, projname, hanlder_id,code,name,type,devicename) "
                      "values(:id, :datetime, :projname, :hanlder_id,:code,"
                      ":name,:type, :devicename)");
        query.bindValue(":id", id);
        query.bindValue(":datetime",datetime);
        query.bindValue(":projname",address);
        query.bindValue(":hanlder_id", userid);
        query.bindValue(":code",code);
        query.bindValue(":name",name);
        query.bindValue(":type",type);
        query.bindValue(":devicename",device);

        if(!query.exec())
        {
            qDebug()<<query.lastError();
            QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"),
                                  QString::fromLocal8Bit("网络连接失败！"),
                                  QString::fromLocal8Bit("确定"));
            return;
        }

        while(CaoZBuZ != "")
        {
            step = CaoZBuZ.left(CaoZBuZ.indexOf(",")); //1Y@补充内容
            if(CaoZBuZ.indexOf(",") != -1)
                CaoZBuZ = CaoZBuZ.right(CaoZBuZ.length() - CaoZBuZ.indexOf(",") -1);
            else
                CaoZBuZ = "";
            //result = step.right(1);
            result = step.mid(step.indexOf("@")-1, 1);
            step = step.left(step.indexOf("@") - 1);
            if (result =="Y")
                tf = true;
            else if(result =="N")
                tf = false;

            title = CaoZNeiR.left(CaoZNeiR.indexOf("$"));
            if(title.indexOf("@") == -1)
                description = "";
            else
                description = title.right(title.length() - title.indexOf("@") -1);

            title = title.left(title.indexOf("@") -1);

            CaoZNeiR = CaoZNeiR.right(CaoZNeiR.length() - CaoZNeiR.indexOf("$") -1);

            query.clear();
            query.prepare("insert into \"knAutoDocApp_operationnode\" (step, title,"
                          " operation_id, result, description) "
                          "values(:step, :title, :operation_id, :result, :description)");
            query.bindValue(":step", step);
            query.bindValue(":title",title);
            query.bindValue(":description",description);
            query.bindValue(":operation_id",id);
            query.bindValue(":result", tf);

            if(!query.exec())
            {
                qDebug()<<query.lastError();
                QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"),
                                      QString::fromLocal8Bit("网络连接失败！"),
                                      QString::fromLocal8Bit("确定"));
                return;
            }

        }

        query.clear();
        query.prepare("update \"knAutoDocApp_operation\" "
                      "set description = :description where id = '"+ id +"'");
        query.bindValue(":description" , description);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
            return;
        }

    }
    QMessageBox::information(NULL, QString::fromLocal8Bit("提示"),
                             QString::fromLocal8Bit("总计提交了 %1 条新诊断记录！").arg(i)
                             ,QString::fromLocal8Bit("确定"));


}

void ZDJLDialog::on_pushButton_cancel_clicked()
{
    lite_db.close();
    post_db.close();
    close();
}


void ZDJLDialog::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    QSqlQuery query(lite_db);
    mrow = item->row();

    QString str;
    mZDID = ui->tableWidget->item(mrow, 2)->text();  //记录编码
    ui->toolButton_del->setEnabled(true);
    query.clear();
    query.prepare("select CZNR from gzzdjlb where ZDID == '"+ mZDID +"'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        str = query.value("CZNR").toString();
    }
    str.replace(QString("$"), QString("\n"));
    ui->textBrowser->setText(str);

}

void ZDJLDialog::on_toolButton_del_clicked()
{
    if(mZDID == "")
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("提示")
                             , QString::fromLocal8Bit("请选中一条诊断记录！")
                             ,QString::fromLocal8Bit("确定"));
        return;
    }
    //确认删除
    if (!(QMessageBox::question(this,QString::fromLocal8Bit("删除")
                                ,QString::fromLocal8Bit("确实要删除该诊断记录?")
                                ,QString::fromLocal8Bit("确定"),
                                QString::fromLocal8Bit("取消"))))
    {
        QSqlQuery query(lite_db);
        query.prepare("update gzzdjlb set isDeleted = :isDeleted whe"
                      "re ZDID == '"+ mZDID +"'"); //注意sql语句中的 等于
        query.bindValue(":isDeleted" , "true");
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }

        ui->textBrowser->setText("");
//        ui->tableWidget->removeRow(mrow);
        //delete all contents
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->clearContents();
        init();
        ui->tableWidget->setFocusPolicy(Qt::NoFocus);
        ui->textBrowser->setFocus();
        mZDID = "";
        ui->toolButton_del->setEnabled(false);
    }

}


void ZDJLDialog::on_dateEdit_end_dateChanged(const QDate &date)
{
//    qDebug("aaaaaaaaaaaaaaa");
    ui->tableWidget->setRowCount(0);
    init();
}

void ZDJLDialog::on_dateEdit_start_dateChanged(const QDate &date)
{
    ui->tableWidget->setRowCount(0);
    init();
}
