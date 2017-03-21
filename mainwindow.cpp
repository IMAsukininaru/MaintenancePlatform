#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QHeaderView>
#include <QDateTime>

#include <QSettings>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    operate_over = true; //操作结束

    pid = "";
    userID = "";
    Name = QString::fromLocal8Bit("未登录");


    openIni();
    openSqlite();


    inits();



    //系统启动后，弹出“启动画面”
    QTimer::singleShot(1000, this, SLOT(showLoginDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openIni()
{
    QSettings *configIniRead = new QSettings("./setting.ini", QSettings::IniFormat);
    configIniRead->setIniCodec(QTextCodec::codecForName("GB2312"));   //读写ini文件中的中文
    //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    settingValue.ip1 = configIniRead->value("/network/ip1").toString().trimmed();
    settingValue.ip2 = configIniRead->value("/network/ip2").toString().trimmed();
    settingValue.ip3 = configIniRead->value("/network/ip3").toString().trimmed();
    settingValue.ip4 = configIniRead->value("/network/ip4").toString().trimmed();
    settingValue.port = configIniRead->value("/network/port").toString().trimmed();

    settingValue.device = configIniRead->value("/other/device").toString().trimmed();
    settingValue.address = configIniRead->value("/other/address").toString().trimmed();

    delete configIniRead;
}


void MainWindow::saveIni()
{
    QSettings *configIniWrite = new QSettings("./setting.ini", QSettings::IniFormat);
    configIniWrite->setIniCodec(QTextCodec::codecForName("GB2312"));
    configIniWrite->beginGroup("network");
    configIniWrite->setValue("ip1", settingValue.ip1);
    configIniWrite->setValue("ip2", settingValue.ip2);
    configIniWrite->setValue("ip3", settingValue.ip3);
    configIniWrite->setValue("ip4", settingValue.ip4);
    configIniWrite->setValue("port", settingValue.port);
    configIniWrite->endGroup();
    configIniWrite->beginGroup("other");
    configIniWrite->setValue("device", settingValue.device);
    configIniWrite->setValue("address", settingValue.address);
    configIniWrite->endGroup();

    delete configIniWrite;
}

void MainWindow::inits()
{
    right = new QLabel(QString::fromLocal8Bit("南京理工大学2013级科研训练"));

    label_username = new QLabel(QString::fromLocal8Bit("当前用户：") + Name);
    label_username->setMinimumSize(label_username->sizeHint());
    label_username->setAlignment(Qt::AlignHCenter);

    ui->statusBar->addWidget(label_username);
    ui->statusBar->addPermanentWidget(right);
    ui->statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    ui->statusBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //不能对表格内容进行修改
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为只能选中一个目标

    QTableWidgetItem *columnHeaderItem0 = ui->tableWidget->horizontalHeaderItem(0); //获得水平方向表头的Item对象
    columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
    columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
    columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色
    //ui->tableWidget->resizeColumnsToContents();  //列的大小设为与内容相匹配
    ui->tableWidget->setColumnWidth(0,40);  //指定某个列的大小
    ui->tableWidget->setColumnWidth(1,90);
    ui->tableWidget->setColumnWidth(2,260);
    ui->tableWidget->setColumnWidth(3,1);
    ui->frame_3->setEnabled(false); //radiobutton（正常，不正确） 不可用
    ui->frame_4->setEnabled(false); //下一步 按钮不可用
    ui->frame_5->setEnabled(false);
    ui->frame_6->setEnabled(false); //结束 按钮
    //设置 故障类型 下拉列表的内容
    QSqlQuery query(lite_db);
    QStringList  strs ;
    query.clear();
    query.prepare("select * from lxb");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())//
    {
        strs.append(query.value("type").toString());//故障类型

    }
    ui->comboBox_type->addItems(strs);
}

//打开程序弹出登录对话框
void MainWindow::showLoginDialog()
{
    LoginDialog* dlg = new LoginDialog(this);
    connect(dlg, SIGNAL(login(QString,QString)), this, SLOT(login(QString,QString)));
    connect(this, SIGNAL(close_dialog()), dlg, SLOT(close_dialog()));
    dlg->exec();
}

//设置 故障类型 下拉列表的内容
void MainWindow::updateType()
{

    QSqlQuery query_s(lite_db);
    QStringList  strs ;
    query_s.clear();
    query_s.prepare("select * from lxb");
    if(!query_s.exec())
    {
        qDebug()<<query_s.lastError();
    }
    while(query_s.next())//
    {
        strs.append(query_s.value("type").toString());//故障类型

    }
    ui->comboBox_type->clear();//清空现有内容
    ui->comboBox_type->addItems(strs);
}

//首先判断本地用户表；不成功则在线判断，并保存用户信息；否则提示失败信息
void MainWindow::login(QString user_ID,QString pwd)
{
    userID = user_ID;//账号
    PWD = pwd;
    QSqlQuery query(lite_db);
    QString str = "select * from yhb where UserID =='" + user_ID +"'";
    query.clear();
    query.prepare(str);

    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    if(query.next())//本地有该 账号
    {
        if(query.value("password").toString() == pwd)
        {
            Name = query.value("name").toString();//用户名
            pid = query.value("id").toString();
            label_username->setText(QString::fromLocal8Bit("当前用户：") + Name); //设置状态栏左侧内容
            emit close_dialog();
        }
        else
        {
            pid = "";
            userID = "";//账号
            PWD = "";
            Name = "";//用户名
            label_username->setText(QString::fromLocal8Bit("当前用户：") + Name); //设置状态栏左侧内容

            QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("账号密码不匹配！"),QString::fromLocal8Bit("确定"));
        }
    }
    else//在线 验证账号密码
    {
        QNetworkAccessManager *network_manager = new QNetworkAccessManager(this);
        QNetworkRequest network_request;
        QByteArray post_data;
        connect(network_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));

        //设置url
        QString url = "http://"+settingValue.ip1+"."+settingValue.ip2+"."+settingValue.ip3+"."+
                settingValue.ip4+":"+settingValue.port+"/verify/";
        network_request.setUrl(QUrl(url));
//        network_request.setUrl(QUrl("http://192.168.3.8:8000/verify/"));
        //设置发送的数据
//        post_data.append("username=admin&password=1@1.cn");
        QString str = "username=" + user_ID;
        post_data.append(str);
        str = "&password=" + pwd;
        post_data.append(str);
        //设置头信息
        network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        network_request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

        QNetworkReply* reply = network_manager->post(network_request, post_data);

    }

}

void MainWindow::finishedSlot(QNetworkReply *reply)
{
    //获取响应的信息，状态码为200表示正常
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(status_code.toInt() != 200)
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络通讯失败！"),QString::fromLocal8Bit("确定"));
    }
    //无错误返回
    if(reply->error() == QNetworkReply::NoError)
    {

        openPostgreSql();  //打开远程数据库，用于登录

        QByteArray bytes = reply->readAll();  //获取字节
        QString result(bytes);  //转化为字符串
        qDebug()<<result;
        QString isOK, isTestor;
        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(result.toUtf8(), &error);

        if(error.error == QJsonParseError::NoError)
        {
            if(jsonDocument.isObject())
            {
                QVariantMap map = jsonDocument.toVariant().toMap();
                isTestor =  map["isTestor"].toString();
                isOK = map["err"].toString();
                qDebug()<<isTestor;qDebug()<<isOK;
            }
        }
        if( isTestor == "false")//不是检测者权限
        {
            QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("该账号不具有相应权限！"),
                                  QString::fromLocal8Bit("确定"));
            return;
        }

        if( isOK == "false" )//账号密码 验证正确
        {
            QSqlQuery query_p(post_db);
            QSqlQuery query(lite_db);

            query_p.clear();
            query_p.prepare("select * from \"knAutoDocApp_user\" where username = '"+ userID +"'");
            if(!query_p.exec())
            {
                qDebug()<<query_p.lastError();
                QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络连接失败！"),QString::fromLocal8Bit("确定"));
                return;
            }
            if(query_p.next())//
            {
                pid = query_p.value("id").toString(); //用户表 id
                Name = query_p.value("nickName").toString();//用户名
                label_username->setText(QString::fromLocal8Bit("当前用户：") + Name); //设置状态栏左侧内容
                query.clear();
                query.prepare("insert into yhb (UserID, name, department, password, id) "
                              "values (:UserID, :name, :department, :password, :id)");
                query.bindValue(":UserID",userID);
                query.bindValue(":name", Name);
                query.bindValue(":department",query_p.value("department").toString());
                query.bindValue(":password",PWD);
                query.bindValue(":id",pid);

                if(!query.exec())
                {
                    qDebug()<<query.lastError();
                }
            }

            emit close_dialog();

        }
        else
        {
            pid = "";
            userID = "";//账号
            PWD = "";
            Name = "";//用户名
            label_username->setText(QString::fromLocal8Bit("当前用户：") + Name); //设置状态栏左侧内容

            QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("账号密码不匹配！"),
                                  QString::fromLocal8Bit("确定"));
        }

    }
    else
    {
        //处理错误
    }

    //收到响应，因此需要处理
    delete reply;

}


void MainWindow::on_action_exit_triggered()
{
    qApp->quit();
}

//打开SQLite数据库
void MainWindow::openSqlite()
{
    //若数据库文件不存在，程序退出
    QFile db_file("./kn_maintenance.db");
    if(!db_file.exists())
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库文件不存在！"),QString::fromLocal8Bit("确定"));
        exit(-1);
    }
    if(QSqlDatabase::contains("lite_connection"))
        lite_db = QSqlDatabase::database("lite_connection");
    else
        lite_db = QSqlDatabase::addDatabase("QSQLITE","lite_connection"); //使用sqlite数据库

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
void MainWindow::openPostgreSql()
{
    if(QSqlDatabase::contains("post_connection"))
        post_db = QSqlDatabase::database("post_connection");
    else
        post_db = QSqlDatabase::addDatabase("QPSQL","post_connection");

    post_db.setHostName(settingValue.ip1+"."+settingValue.ip2+"."+settingValue.ip3+"."+settingValue.ip4);
    post_db.setDatabaseName("main");
    post_db.setUserName("postgres");
    post_db.setPassword("yukiyuki");
    bool ok = post_db.open();

    if(!ok)
    {
        qDebug()<<post_db.lastError();
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("网络故障，数据库连接失败！"),QString::fromLocal8Bit("确定"));
        exit(-1);
//        qFatal("Database server failed to connect.") ;

    }

//    QSqlQuery query(post_db);

//    query.prepare(QString::fromLocal8Bit("select * from \"knAutoDocApp_glitch\""));
//    if(!query.exec())
//    {
//        qDebug()<<query.lastError();
//    }
//    while(query.next())
//    {
//        QString str = query.value("id").toString();
//        QChar ch = query.value("name").toChar();
//        qDebug()<<query.value("id").toString();
//        qDebug()<<query.value(7).toString();
//    }
}


//根据 条件 查询
//按照 使用频次 fre 进行排序
void MainWindow::on_toolButton_search_clicked()
{
    ui->tableWidget->setRowCount(0);
    QSqlQuery query(lite_db);
    QString str = "";
    QString type = ui->comboBox_type->currentText();
    QString gzdm = ui->lineEdit_ID->text().trimmed();  //故障代码
    QString des = ui->lineEdit_description->text().trimmed();
    str = "select TMID, name, id from gztmxxb where isDeleted =='false' and TMID like '%" + gzdm +"%' and type =='" + type
            +"' and description like '%"+ des +"%' order by fre desc";
    query.clear();
    query.prepare(str);

    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    int i = 1;

    while(query.next())
    {
        ui->tableWidget->setRowCount(i);     //设置行数
        ui->tableWidget->setItem(i-1,0,new QTableWidgetItem(QString::number(i, 10)));
        str = query.value(0).toString();
        qDebug()<<str;
        ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(str));
        str = query.value(1).toString();
        qDebug()<<str;
        ui->tableWidget->setItem(i-1,2,new QTableWidgetItem(str));
        str = query.value(2).toString();
        qDebug()<<str;
        QTableWidgetItem *item = new QTableWidgetItem(str);
        item->setTextColor(QColor(255,255,255)); //设置文字颜色
        ui->tableWidget->setItem(i-1,3,item);
        i++;
    }

}

//选中左侧列表中一条 故障条目信息
void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{

    QSqlQuery query(lite_db);
    if(!operate_over)//当前故障检测操作没有结束
    {
        if(QMessageBox::No == QMessageBox::question(NULL, QString::fromLocal8Bit("确认"), QString::fromLocal8Bit("是否放弃当前检测流程？"),QMessageBox::Yes | QMessageBox::No))
        {
            ui->tableWidget->setCurrentCell(current_row,0); //取消，则tableWidget的当前行保持不变
            return;
        }
        else
        {
            operate_over = true; //开始一个新的检测操作流程
            save_cznr();
        }
    }

    int row = item->row();
    mgz_code = ui->tableWidget->item(row, 1)->text();  //故障编码
    mgz_name = ui->tableWidget->item(row, 2)->text();  //故障名称
    mid = ui->tableWidget->item(row,3)->text(); //id，不是 故障编码
    QString str;

    query.clear();
    query.prepare("select description from gztmxxb where id == '"+ mid +"'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        str = query.value(0).toString();
    }
    ui->textBrowser_description->setText(str);
    ui->plainTextEdit_result->setPlainText("");

    str = "";
    query.clear();
    query.prepare("select title from gzczznb where TMID == '"+mid+"' and CZID =='1' and isDeleted =='false'" );
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        str = query.value(0).toString();
        mczid = "1"; //记录当前操作步骤ID
    }
    ui->textBrowser_operation->setText(str);

    ui->frame_3->setEnabled(true); //radiobutton（正常，异常）面板
    ui->radioButton_no->setEnabled(true);
    ui->radioButton_yes->setEnabled(true);
    ui->radioButton_yes->setChecked(true); //默认选中 正常 状态
    ui->frame_4->setEnabled(true); //toolbutton 面板
    ui->toolButton_next->setEnabled(true); //下一步 可用
    ui->frame_5->setEnabled(false);
    ui->toolButton_last->setEnabled(false); //上一步 不可用


    current_row = ui->tableWidget->currentRow();  //设置 故障条目列表 当前行

}

//生成诊断记录编号 ZDID
QString MainWindow::create_zdid()
{
    QSqlQuery query(lite_db);
    QString temp_zdid;

    QDateTime dt = QDateTime::currentDateTime();
    QString dt_str = dt.toString("_yyyyMMdd_hhmmss");
    query.clear();
    query.prepare("select ZDID from gzzdjlb where UserID =='"+ pid +"'  order by ZDID DESC");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    if(query.next())
    {
        temp_zdid = query.value("ZDID").toString();
        temp_zdid = temp_zdid.right(temp_zdid.length() - temp_zdid.lastIndexOf('_') -1);

        int i = temp_zdid.toInt()+1;
        temp_zdid = QString("%1").arg(i);
    }
    else
        temp_zdid = "1";

    temp_zdid = userID + dt_str +"_" + temp_zdid;
    return temp_zdid;
}

//从数据库中提取当前诊断操作流程中的上一条czid，更新 CaoZBZ 字段内容
QString MainWindow::get_lastczid(QString zdid)
{
    QSqlQuery query(lite_db);
    QString czid;
    QString temp_czbz = "";

    query.clear();
    query.prepare("select CaoZBZ from gzzdjlb where ZDID == '"+ zdid +"'");//读取现有操作步骤
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        temp_czbz = query.value(0).toString(); //操作步骤序列
    }
    int i = temp_czbz.lastIndexOf(",");  //操作步骤 之间用”，“分隔
    if(i != -1)//有多个操作ID, 则提取最后一个
    {
        czid = temp_czbz.right(temp_czbz.length() - i -1);
    }
    else
        czid = temp_czbz;

    //更新 gzzdjlb
    if(i != -1)//有多个操作ID, 删掉最后一个
    {
        temp_czbz = temp_czbz.left(i);
    }
    else //只有一个，删除后则为空
        temp_czbz = "";
    query.clear();
    query.prepare("update gzzdjlb set CaoZBZ = :czbz where ZDID == '"+ zdid +"'");
    query.bindValue(":czbz" , temp_czbz);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    czid = czid.left(czid.length() - 1);  //去掉 Y /N
    return czid;
}

//根据当前czid，以及操作结果是否 正常，从数据库中获取下一条的czid
QString MainWindow::get_nextczid(bool yesno, QString czid)
{

    QSqlQuery query(lite_db);
    QString temp_czid;

    query.clear();
    if(yesno)//正常
    {
        query.prepare("select YCZID from gzczznb where isDeleted =='false' and CZID =='"+ czid +"' and TMID == '"+ mid + "'");
    }
    else
    {
        query.prepare("select NCZID from gzczznb where isDeleted =='false' and CZID =='"+ czid +"' and TMID == '"+ mid + "'");
    }
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        temp_czid = query.value(0).toString();
    }

    return temp_czid;
}



//检测流程未完成，提前结束，并保存记录
void MainWindow::on_toolButton_end_clicked()
{
    if(operate_over == false)//正在检测操作过程中
    {
        ui->frame_3->setEnabled(false);
        ui->frame_4->setEnabled(false);
        ui->frame_5->setEnabled(false);
        ui->frame_6->setEnabled(false);
        operate_over = true ;
        save_cznr();
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("检测终止，操作记录已保存！"),QString::fromLocal8Bit("确定"));

        return;
    }
}

//下一步 按钮操作
void MainWindow::on_toolButton_next_clicked()
{
    if(!ui->radioButton_yes->isChecked() && !ui->radioButton_no->isChecked())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请先确认操作结果！"),QString::fromLocal8Bit("确定"));
        return;
    }
    QDateTime datetime = QDateTime::currentDateTime();
    QString czbz, str, tmp_czid;
    QSqlQuery query(lite_db);

    if(ui->plainTextEdit_result->toPlainText().trimmed() != "")
    {
        if(ui->radioButton_yes->isChecked())//正常，tmp_czid用于构成数据库 CaoZBZ 字段
        {
            tmp_czid = mczid+ "Y"+"@"+ui->plainTextEdit_result->toPlainText().trimmed();
        }
        else if(ui->radioButton_no->isChecked())
        {
            tmp_czid = mczid+ "N"+"@"+ui->plainTextEdit_result->toPlainText().trimmed();
        }
    }
    else
    {
        if(ui->radioButton_yes->isChecked())//正常，tmp_czid用于构成数据库 CaoZBZ 字段
        {
            tmp_czid = mczid+ "Y";//+"@"+ui->plainTextEdit_result->toPlainText().trimmed();
        }
        else if(ui->radioButton_no->isChecked())
        {
            tmp_czid = mczid+ "N";//+"@"+ui->plainTextEdit_result->toPlainText().trimmed();
        }
    }
    //记录当前操作内容
    if(operate_over == true)//第一项操作，新增一条数据库记录
    {
        operate_over = false; //正在检测过程中，标志位置为false
        ui->frame_6->setEnabled(true);
        ui->toolButton_end->setEnabled(true);

        mzdid = create_zdid(); //生成 诊断记录ID

        query.clear();
        query.prepare("insert into gzzdjlb (isDeleted, ZDID, CaoZBZ, device, time, address, UserID, type, TMID, name) "
                      "values (:isDeleted, :zdid, :czbz, :device, :time, :address, :userid, :type, :tmid, :name)");
        query.bindValue(":isDeleted","false");
        query.bindValue(":zdid",mzdid);
        query.bindValue(":czbz", tmp_czid);
        query.bindValue(":device", settingValue.device);
        query.bindValue(":time",datetime.toString("yyyy-MM-dd hh:mm:ss"));
        query.bindValue(":address", settingValue.address);
        query.bindValue(":userid",pid);
        query.bindValue(":type",ui->comboBox_type->currentText());
        query.bindValue(":tmid",mgz_code);
        query.bindValue(":name",mgz_name);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }

    }
    else//不是第一项操作，更新数据库记录
    {
        query.clear();
        query.prepare("select CaoZBZ from gzzdjlb where ZDID == '"+ mzdid +"'");//读取现有操作步骤
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        while(query.next())
        {
            czbz = query.value(0).toString(); //操作步骤序列
        }
        if(czbz == "") //操作步骤的第一个操作指南ID
            czbz = tmp_czid;
        else  //不是第一个
            czbz = czbz + "," + tmp_czid;

        query.clear();
        query.prepare("update gzzdjlb set CaoZBZ = :czbz where ZDID == '"+ mzdid +"'");
        query.bindValue(":czbz" , czbz);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
    }



    //获取下一步的czid
    if(ui->radioButton_yes->isChecked())//正常
    {
        mczid = get_nextczid(1, mczid);
    }
    else if(ui->radioButton_no->isChecked())
    {
        mczid = get_nextczid(0, mczid);
    }

    if("0" == mczid)//看见操作内容为“结束”以后，再点击“下一步”，mczid等于0
    {
        ui->frame_3->setEnabled(false);//(正常、不正常步)
        ui->frame_4->setEnabled(false);//（下一步）
        ui->frame_5->setEnabled(false);//（上一步）
        ui->frame_6->setEnabled(false);//（结束）
        operate_over = true ;
        save_cznr();
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("检测结束，操作记录已保存！"),QString::fromLocal8Bit("确定"));

        return;
    }

    //显示下一步的内容
    QString Y_sub, N_sub;
    query.clear();
    query.prepare("select * from gzczznb where CZID == '"+ mczid +"' and TMID == '"+ mid + "'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        str = query.value("title").toString(); //操作内容
        Y_sub = query.value("YCZID").toString();
        N_sub = query.value("NCZID").toString();
    }
    ui->textBrowser_operation->setText(str);

    ui->frame_5->setEnabled(true);
    ui->toolButton_last->setEnabled(true);
    ui->plainTextEdit_result->setPlainText("");

    //判断操作是否缺少某个分支
    if("0" == Y_sub)
        ui->radioButton_yes->setEnabled(false);
    else
        ui->radioButton_yes->setEnabled(true);

    if("0" == N_sub)
        ui->radioButton_no->setEnabled(false);
    else
        ui->radioButton_no->setEnabled(true);


}



//上一步 按钮操作
void MainWindow::on_toolButton_last_clicked()
{
    QString temp_czid = mczid; //临时保存 当前操作指南ID
    mczid = get_lastczid(mzdid);
    if(mczid == "")
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("此为第一条操作指南！"),QString::fromLocal8Bit("确定"));
        ui->toolButton_last->setEnabled(false);
        mczid = temp_czid;
        return;
    }

    QSqlQuery query(lite_db);
    QString str, Y_sub, N_sub;
    query.clear();
    query.prepare("select * from gzczznb where isDeleted =='false' and CZID == '"+ mczid +"' and TMID == '"+ mid + "'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        str = query.value("title").toString(); //操作内容
        Y_sub = query.value("YCZID").toString();
        N_sub = query.value("NCZID").toString();
    }
    ui->textBrowser_operation->setText(str);

    //判断操作是否缺少某个分支
    if("0" == Y_sub)
        ui->radioButton_yes->setEnabled(false);
    else
        ui->radioButton_yes->setEnabled(true);

    if("0" == N_sub)
        ui->radioButton_no->setEnabled(false);
    else
        ui->radioButton_no->setEnabled(true);

}

//操作结束的时候，或者更换故障条目的时候：根据czid保存操作内容 cznr
void MainWindow::save_cznr()
{
    QString str_cznr, str_czid, str_result, czid, gzid;
    str_cznr = "";
    QSqlQuery query(lite_db);
    query.clear();
    query.prepare("select CaoZBZ, TMID from gzzdjlb where ZDID == '"+ mzdid +"'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        str_czid = query.value(0).toString();
        gzid = query.value(1).toString();
    }

    while(str_czid !="")
    {
        czid = str_czid.left(str_czid.indexOf(","));
        str_result = "";

        if(str_czid.indexOf(",") == -1)//仅剩一个czid
            str_czid = ""; //操作id的字符串置为空
        else
            str_czid = str_czid.right(str_czid.length() - str_czid.indexOf(",") -1);

        if(czid.indexOf("@") != -1)//操作步骤中存在 结果补充说明
        {
            str_result = czid.right(czid.length() - czid.indexOf("@") -1);
            czid = czid.left(czid.indexOf("@"));
        }
        query.clear();
        query.prepare("select title from gzczznb where isDeleted =='false' and CZID == '"+ czid.left(czid.length() - 1) +"' and TMID == '"+ mid + "'"); //去掉czid中的Y/N
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        while(query.next())
        {
            if(str_result != "")
                str_cznr += query.value(0).toString()+"@"+ str_result +"$";
            else
                str_cznr += query.value(0).toString()+"$";

        }
    }

    //更新 gzzdjlb 中的 CZNR 字段
    query.clear();
    query.prepare("update gzzdjlb set CZNR = :cznr where ZDID == '"+ mzdid +"'");
    query.bindValue(":cznr" , str_cznr);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }

    //更新 gztmxxb 中的 fre 字段
    QString num;
    query.clear();
    query.prepare("select fre from gztmxxb where TMID == '"+ gzid +"'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        num = query.value(0).toString();
    }
    num = QString::number((num.toInt() +1));
    query.clear();
    query.prepare("update gztmxxb set fre = :fre where TMID == '"+ gzid +"'");
    query.bindValue(":fre" , num);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
}

void MainWindow::on_action_upload_triggered()
{
    ZDJLDialog * zdjlDialog = new ZDJLDialog(this);
    zdjlDialog->exec();
}

void MainWindow::on_action_download_triggered()
{
/*
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("http://time.jsontest.com/") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        //parse json
        qDebug() << "Response:" << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObj = jsonResponse.object();

        qDebug() << "Time:" << jsonObj["time"].toString();
        qDebug() << "Date:" << jsonObj["date"].toString();

        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
*/
    UpdateDialog* updateDialog = new UpdateDialog(this);

    connect(updateDialog,SIGNAL(update_end()),this,SLOT(updateType()));
    updateDialog->exec();
}

void MainWindow::on_action_login_triggered()
{

    LoginDialog* dlg = new LoginDialog(this);
    if( userID != "" )
    {
        dlg->setWindowTitle(QString::fromLocal8Bit("重新登录"));
        dlg->set_UI(Name);
    }
    connect(dlg, SIGNAL(login(QString,QString)), this, SLOT(login(QString,QString)));
    connect(this, SIGNAL(close_dialog()), dlg, SLOT(close_dialog()));
    dlg->exec();
}

void MainWindow::on_action_config_triggered()
{
    ConfigDialog* config_dlg = new ConfigDialog(this);
    QStringList projnames, devnames;
    QSqlQuery query(lite_db);
    query.clear();
    query.prepare("select projname from xmb order by projname");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        projnames.append( query.value("projname").toString());
    }

    query.clear();
    query.prepare("select devicename from sbb order by devicename");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        devnames.append( query.value("devicename").toString());
    }

    config_dlg->set_value(settingValue,projnames,devnames);

    connect(config_dlg, SIGNAL(save(ConfigValue)), this, SLOT(saveConfigValue(ConfigValue)));
    connect(this, SIGNAL(close_config()), config_dlg, SLOT(close_dialog()));
    config_dlg->exec();
}

void MainWindow::saveConfigValue(ConfigValue value)
{
    settingValue = value;
    saveIni();
    emit close_config();
}

