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

    operate_over = true; //��������

    pid = "";
    userID = "";
    Name = QString::fromLocal8Bit("δ��¼");


    openIni();
    openSqlite();


    inits();



    //ϵͳ�����󣬵������������桱
    QTimer::singleShot(1000, this, SLOT(showLoginDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openIni()
{
    QSettings *configIniRead = new QSettings("./setting.ini", QSettings::IniFormat);
    configIniRead->setIniCodec(QTextCodec::codecForName("GB2312"));   //��дini�ļ��е�����
    //����ȡ����ini�ļ�������QString�У���ȡֵ��Ȼ��ͨ��toString()����ת����QString����
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
    right = new QLabel(QString::fromLocal8Bit("�Ͼ�����ѧ2013������ѵ��"));

    label_username = new QLabel(QString::fromLocal8Bit("��ǰ�û���") + Name);
    label_username->setMinimumSize(label_username->sizeHint());
    label_username->setAlignment(Qt::AlignHCenter);

    ui->statusBar->addWidget(label_username);
    ui->statusBar->addPermanentWidget(right);
    ui->statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    ui->statusBar->setSizeGripEnabled(false); //�����Ƿ���ʾ�ұߵĴ�С���Ƶ�

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //���ܶԱ�����ݽ����޸�
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ�еķ�ʽ
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //����Ϊֻ��ѡ��һ��Ŀ��

    QTableWidgetItem *columnHeaderItem0 = ui->tableWidget->horizontalHeaderItem(0); //���ˮƽ�����ͷ��Item����
    columnHeaderItem0->setFont(QFont("Helvetica")); //��������
    columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //���õ�Ԫ�񱳾���ɫ
    columnHeaderItem0->setTextColor(QColor(200,111,30)); //����������ɫ
    //ui->tableWidget->resizeColumnsToContents();  //�еĴ�С��Ϊ��������ƥ��
    ui->tableWidget->setColumnWidth(0,40);  //ָ��ĳ���еĴ�С
    ui->tableWidget->setColumnWidth(1,90);
    ui->tableWidget->setColumnWidth(2,260);
    ui->tableWidget->setColumnWidth(3,1);
    ui->frame_3->setEnabled(false); //radiobutton������������ȷ�� ������
    ui->frame_4->setEnabled(false); //��һ�� ��ť������
    ui->frame_5->setEnabled(false);
    ui->frame_6->setEnabled(false); //���� ��ť
    //���� �������� �����б������
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
        strs.append(query.value("type").toString());//��������

    }
    ui->comboBox_type->addItems(strs);
}

//�򿪳��򵯳���¼�Ի���
void MainWindow::showLoginDialog()
{
    LoginDialog* dlg = new LoginDialog(this);
    connect(dlg, SIGNAL(login(QString,QString)), this, SLOT(login(QString,QString)));
    connect(this, SIGNAL(close_dialog()), dlg, SLOT(close_dialog()));
    dlg->exec();
}

//���� �������� �����б������
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
        strs.append(query_s.value("type").toString());//��������

    }
    ui->comboBox_type->clear();//�����������
    ui->comboBox_type->addItems(strs);
}

//�����жϱ����û������ɹ��������жϣ��������û���Ϣ��������ʾʧ����Ϣ
void MainWindow::login(QString user_ID,QString pwd)
{
    userID = user_ID;//�˺�
    PWD = pwd;
    QSqlQuery query(lite_db);
    QString str = "select * from yhb where UserID =='" + user_ID +"'";
    query.clear();
    query.prepare(str);

    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    if(query.next())//�����и� �˺�
    {
        if(query.value("password").toString() == pwd)
        {
            Name = query.value("name").toString();//�û���
            pid = query.value("id").toString();
            label_username->setText(QString::fromLocal8Bit("��ǰ�û���") + Name); //����״̬���������
            emit close_dialog();
        }
        else
        {
            pid = "";
            userID = "";//�˺�
            PWD = "";
            Name = "";//�û���
            label_username->setText(QString::fromLocal8Bit("��ǰ�û���") + Name); //����״̬���������

            QMessageBox::critical(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˺����벻ƥ�䣡"),QString::fromLocal8Bit("ȷ��"));
        }
    }
    else//���� ��֤�˺�����
    {
        QNetworkAccessManager *network_manager = new QNetworkAccessManager(this);
        QNetworkRequest network_request;
        QByteArray post_data;
        connect(network_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));

        //����url
        QString url = "http://"+settingValue.ip1+"."+settingValue.ip2+"."+settingValue.ip3+"."+
                settingValue.ip4+":"+settingValue.port+"/verify/";
        network_request.setUrl(QUrl(url));
//        network_request.setUrl(QUrl("http://192.168.3.8:8000/verify/"));
        //���÷��͵�����
//        post_data.append("username=admin&password=1@1.cn");
        QString str = "username=" + user_ID;
        post_data.append(str);
        str = "&password=" + pwd;
        post_data.append(str);
        //����ͷ��Ϣ
        network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        network_request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

        QNetworkReply* reply = network_manager->post(network_request, post_data);

    }

}

void MainWindow::finishedSlot(QNetworkReply *reply)
{
    //��ȡ��Ӧ����Ϣ��״̬��Ϊ200��ʾ����
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(status_code.toInt() != 200)
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ͨѶʧ�ܣ�"),QString::fromLocal8Bit("ȷ��"));
    }
    //�޴��󷵻�
    if(reply->error() == QNetworkReply::NoError)
    {

        openPostgreSql();  //��Զ�����ݿ⣬���ڵ�¼

        QByteArray bytes = reply->readAll();  //��ȡ�ֽ�
        QString result(bytes);  //ת��Ϊ�ַ���
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
        if( isTestor == "false")//���Ǽ����Ȩ��
        {
            QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���˺Ų�������ӦȨ�ޣ�"),
                                  QString::fromLocal8Bit("ȷ��"));
            return;
        }

        if( isOK == "false" )//�˺����� ��֤��ȷ
        {
            QSqlQuery query_p(post_db);
            QSqlQuery query(lite_db);

            query_p.clear();
            query_p.prepare("select * from \"knAutoDocApp_user\" where username = '"+ userID +"'");
            if(!query_p.exec())
            {
                qDebug()<<query_p.lastError();
                QMessageBox::critical(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������ʧ�ܣ�"),QString::fromLocal8Bit("ȷ��"));
                return;
            }
            if(query_p.next())//
            {
                pid = query_p.value("id").toString(); //�û��� id
                Name = query_p.value("nickName").toString();//�û���
                label_username->setText(QString::fromLocal8Bit("��ǰ�û���") + Name); //����״̬���������
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
            userID = "";//�˺�
            PWD = "";
            Name = "";//�û���
            label_username->setText(QString::fromLocal8Bit("��ǰ�û���") + Name); //����״̬���������

            QMessageBox::critical(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˺����벻ƥ�䣡"),
                                  QString::fromLocal8Bit("ȷ��"));
        }

    }
    else
    {
        //�������
    }

    //�յ���Ӧ�������Ҫ����
    delete reply;

}


void MainWindow::on_action_exit_triggered()
{
    qApp->quit();
}

//��SQLite���ݿ�
void MainWindow::openSqlite()
{
    //�����ݿ��ļ������ڣ������˳�
    QFile db_file("./kn_maintenance.db");
    if(!db_file.exists())
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ݿ��ļ������ڣ�"),QString::fromLocal8Bit("ȷ��"));
        exit(-1);
    }
    if(QSqlDatabase::contains("lite_connection"))
        lite_db = QSqlDatabase::database("lite_connection");
    else
        lite_db = QSqlDatabase::addDatabase("QSQLITE","lite_connection"); //ʹ��sqlite���ݿ�

    lite_db.setDatabaseName(db_file.fileName());  //���������ݿ�

    bool ok = lite_db.open();  //�������ݿ�
    if(!ok)
    {
        qDebug()<<lite_db.lastError();
        qFatal("failed to connect.") ;
        QMessageBox::critical(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ݿ�����ʧ�ܣ�"),QString::fromLocal8Bit("ȷ��"));
        exit(-1);
    }
}

//�� postgresql ���ݿ�
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
        QMessageBox::critical(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ϣ����ݿ�����ʧ�ܣ�"),QString::fromLocal8Bit("ȷ��"));
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


//���� ���� ��ѯ
//���� ʹ��Ƶ�� fre ��������
void MainWindow::on_toolButton_search_clicked()
{
    ui->tableWidget->setRowCount(0);
    QSqlQuery query(lite_db);
    QString str = "";
    QString type = ui->comboBox_type->currentText();
    QString gzdm = ui->lineEdit_ID->text().trimmed();  //���ϴ���
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
        ui->tableWidget->setRowCount(i);     //��������
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
        item->setTextColor(QColor(255,255,255)); //����������ɫ
        ui->tableWidget->setItem(i-1,3,item);
        i++;
    }

}

//ѡ������б���һ�� ������Ŀ��Ϣ
void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{

    QSqlQuery query(lite_db);
    if(!operate_over)//��ǰ���ϼ�����û�н���
    {
        if(QMessageBox::No == QMessageBox::question(NULL, QString::fromLocal8Bit("ȷ��"), QString::fromLocal8Bit("�Ƿ������ǰ������̣�"),QMessageBox::Yes | QMessageBox::No))
        {
            ui->tableWidget->setCurrentCell(current_row,0); //ȡ������tableWidget�ĵ�ǰ�б��ֲ���
            return;
        }
        else
        {
            operate_over = true; //��ʼһ���µļ���������
            save_cznr();
        }
    }

    int row = item->row();
    mgz_code = ui->tableWidget->item(row, 1)->text();  //���ϱ���
    mgz_name = ui->tableWidget->item(row, 2)->text();  //��������
    mid = ui->tableWidget->item(row,3)->text(); //id������ ���ϱ���
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
        mczid = "1"; //��¼��ǰ��������ID
    }
    ui->textBrowser_operation->setText(str);

    ui->frame_3->setEnabled(true); //radiobutton���������쳣�����
    ui->radioButton_no->setEnabled(true);
    ui->radioButton_yes->setEnabled(true);
    ui->radioButton_yes->setChecked(true); //Ĭ��ѡ�� ���� ״̬
    ui->frame_4->setEnabled(true); //toolbutton ���
    ui->toolButton_next->setEnabled(true); //��һ�� ����
    ui->frame_5->setEnabled(false);
    ui->toolButton_last->setEnabled(false); //��һ�� ������


    current_row = ui->tableWidget->currentRow();  //���� ������Ŀ�б� ��ǰ��

}

//������ϼ�¼��� ZDID
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

//�����ݿ�����ȡ��ǰ��ϲ��������е���һ��czid������ CaoZBZ �ֶ�����
QString MainWindow::get_lastczid(QString zdid)
{
    QSqlQuery query(lite_db);
    QString czid;
    QString temp_czbz = "";

    query.clear();
    query.prepare("select CaoZBZ from gzzdjlb where ZDID == '"+ zdid +"'");//��ȡ���в�������
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        temp_czbz = query.value(0).toString(); //������������
    }
    int i = temp_czbz.lastIndexOf(",");  //�������� ֮���á������ָ�
    if(i != -1)//�ж������ID, ����ȡ���һ��
    {
        czid = temp_czbz.right(temp_czbz.length() - i -1);
    }
    else
        czid = temp_czbz;

    //���� gzzdjlb
    if(i != -1)//�ж������ID, ɾ�����һ��
    {
        temp_czbz = temp_czbz.left(i);
    }
    else //ֻ��һ����ɾ������Ϊ��
        temp_czbz = "";
    query.clear();
    query.prepare("update gzzdjlb set CaoZBZ = :czbz where ZDID == '"+ zdid +"'");
    query.bindValue(":czbz" , temp_czbz);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    czid = czid.left(czid.length() - 1);  //ȥ�� Y /N
    return czid;
}

//���ݵ�ǰczid���Լ���������Ƿ� �����������ݿ��л�ȡ��һ����czid
QString MainWindow::get_nextczid(bool yesno, QString czid)
{

    QSqlQuery query(lite_db);
    QString temp_czid;

    query.clear();
    if(yesno)//����
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



//�������δ��ɣ���ǰ�������������¼
void MainWindow::on_toolButton_end_clicked()
{
    if(operate_over == false)//���ڼ�����������
    {
        ui->frame_3->setEnabled(false);
        ui->frame_4->setEnabled(false);
        ui->frame_5->setEnabled(false);
        ui->frame_6->setEnabled(false);
        operate_over = true ;
        save_cznr();
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("�����ֹ��������¼�ѱ��棡"),QString::fromLocal8Bit("ȷ��"));

        return;
    }
}

//��һ�� ��ť����
void MainWindow::on_toolButton_next_clicked()
{
    if(!ui->radioButton_yes->isChecked() && !ui->radioButton_no->isChecked())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����ȷ�ϲ��������"),QString::fromLocal8Bit("ȷ��"));
        return;
    }
    QDateTime datetime = QDateTime::currentDateTime();
    QString czbz, str, tmp_czid;
    QSqlQuery query(lite_db);

    if(ui->plainTextEdit_result->toPlainText().trimmed() != "")
    {
        if(ui->radioButton_yes->isChecked())//������tmp_czid���ڹ������ݿ� CaoZBZ �ֶ�
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
        if(ui->radioButton_yes->isChecked())//������tmp_czid���ڹ������ݿ� CaoZBZ �ֶ�
        {
            tmp_czid = mczid+ "Y";//+"@"+ui->plainTextEdit_result->toPlainText().trimmed();
        }
        else if(ui->radioButton_no->isChecked())
        {
            tmp_czid = mczid+ "N";//+"@"+ui->plainTextEdit_result->toPlainText().trimmed();
        }
    }
    //��¼��ǰ��������
    if(operate_over == true)//��һ�����������һ�����ݿ��¼
    {
        operate_over = false; //���ڼ������У���־λ��Ϊfalse
        ui->frame_6->setEnabled(true);
        ui->toolButton_end->setEnabled(true);

        mzdid = create_zdid(); //���� ��ϼ�¼ID

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
    else//���ǵ�һ��������������ݿ��¼
    {
        query.clear();
        query.prepare("select CaoZBZ from gzzdjlb where ZDID == '"+ mzdid +"'");//��ȡ���в�������
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        while(query.next())
        {
            czbz = query.value(0).toString(); //������������
        }
        if(czbz == "") //��������ĵ�һ������ָ��ID
            czbz = tmp_czid;
        else  //���ǵ�һ��
            czbz = czbz + "," + tmp_czid;

        query.clear();
        query.prepare("update gzzdjlb set CaoZBZ = :czbz where ZDID == '"+ mzdid +"'");
        query.bindValue(":czbz" , czbz);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
    }



    //��ȡ��һ����czid
    if(ui->radioButton_yes->isChecked())//����
    {
        mczid = get_nextczid(1, mczid);
    }
    else if(ui->radioButton_no->isChecked())
    {
        mczid = get_nextczid(0, mczid);
    }

    if("0" == mczid)//������������Ϊ���������Ժ��ٵ������һ������mczid����0
    {
        ui->frame_3->setEnabled(false);//(��������������)
        ui->frame_4->setEnabled(false);//����һ����
        ui->frame_5->setEnabled(false);//����һ����
        ui->frame_6->setEnabled(false);//��������
        operate_over = true ;
        save_cznr();
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��������������¼�ѱ��棡"),QString::fromLocal8Bit("ȷ��"));

        return;
    }

    //��ʾ��һ��������
    QString Y_sub, N_sub;
    query.clear();
    query.prepare("select * from gzczznb where CZID == '"+ mczid +"' and TMID == '"+ mid + "'");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    while(query.next())
    {
        str = query.value("title").toString(); //��������
        Y_sub = query.value("YCZID").toString();
        N_sub = query.value("NCZID").toString();
    }
    ui->textBrowser_operation->setText(str);

    ui->frame_5->setEnabled(true);
    ui->toolButton_last->setEnabled(true);
    ui->plainTextEdit_result->setPlainText("");

    //�жϲ����Ƿ�ȱ��ĳ����֧
    if("0" == Y_sub)
        ui->radioButton_yes->setEnabled(false);
    else
        ui->radioButton_yes->setEnabled(true);

    if("0" == N_sub)
        ui->radioButton_no->setEnabled(false);
    else
        ui->radioButton_no->setEnabled(true);


}



//��һ�� ��ť����
void MainWindow::on_toolButton_last_clicked()
{
    QString temp_czid = mczid; //��ʱ���� ��ǰ����ָ��ID
    mczid = get_lastczid(mzdid);
    if(mczid == "")
    {
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("��Ϊ��һ������ָ�ϣ�"),QString::fromLocal8Bit("ȷ��"));
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
        str = query.value("title").toString(); //��������
        Y_sub = query.value("YCZID").toString();
        N_sub = query.value("NCZID").toString();
    }
    ui->textBrowser_operation->setText(str);

    //�жϲ����Ƿ�ȱ��ĳ����֧
    if("0" == Y_sub)
        ui->radioButton_yes->setEnabled(false);
    else
        ui->radioButton_yes->setEnabled(true);

    if("0" == N_sub)
        ui->radioButton_no->setEnabled(false);
    else
        ui->radioButton_no->setEnabled(true);

}

//����������ʱ�򣬻��߸���������Ŀ��ʱ�򣺸���czid����������� cznr
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

        if(str_czid.indexOf(",") == -1)//��ʣһ��czid
            str_czid = ""; //����id���ַ�����Ϊ��
        else
            str_czid = str_czid.right(str_czid.length() - str_czid.indexOf(",") -1);

        if(czid.indexOf("@") != -1)//���������д��� �������˵��
        {
            str_result = czid.right(czid.length() - czid.indexOf("@") -1);
            czid = czid.left(czid.indexOf("@"));
        }
        query.clear();
        query.prepare("select title from gzczznb where isDeleted =='false' and CZID == '"+ czid.left(czid.length() - 1) +"' and TMID == '"+ mid + "'"); //ȥ��czid�е�Y/N
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

    //���� gzzdjlb �е� CZNR �ֶ�
    query.clear();
    query.prepare("update gzzdjlb set CZNR = :cznr where ZDID == '"+ mzdid +"'");
    query.bindValue(":cznr" , str_cznr);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }

    //���� gztmxxb �е� fre �ֶ�
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
        dlg->setWindowTitle(QString::fromLocal8Bit("���µ�¼"));
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

