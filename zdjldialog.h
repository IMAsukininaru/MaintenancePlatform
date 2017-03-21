#ifndef ZDJLDIALOG_H
#define ZDJLDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTableWidgetItem>
#include <QtNetwork>
#include <QtNetwork/QTcpSocket>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "configdialog.h"

namespace Ui {
class ZDJLDialog;
}

class ZDJLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZDJLDialog(QWidget *parent = 0);
    ~ZDJLDialog();

protected:

   void init();
   void newTCPConnect();//���ڽ����������ͻ�֮������Ӻ���



private:
    Ui::ZDJLDialog *ui;

    QTcpSocket *tcpSocket;
    QSqlDatabase lite_db, post_db;

    ConfigValue settingValue;
    QString mZDID;
    int mrow; //��ǰ��

    void openIni();
    void openSqlite();
    void openPostgreSql();

private slots:
   void revData(); //�������Է���˵�����

   void displayError(QAbstractSocket::SocketError);

   void on_pushButton_send_clicked();
   void on_pushButton_cancel_clicked();
   void on_tableWidget_itemClicked(QTableWidgetItem *item);
   void on_toolButton_del_clicked();

   void on_dateEdit_end_dateChanged(const QDate &date);
   void on_dateEdit_start_dateChanged(const QDate &date);
};

#endif // ZDJLDIALOG_H
