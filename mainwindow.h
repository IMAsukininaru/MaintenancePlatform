#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <qDebug>
#include <QTableWidgetItem>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtNetwork>

#include "configdialog.h"
#include "logindialog.h"
#include "updatedialog.h"
#include "zdjldialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel* right;
    QLabel* label_username; //状态栏显示
    ConfigValue settingValue; //保存ini配置文件的值
    QString mid, mgz_code, mgz_name; //故障ID
    QString mczid; //操作ID
    QString mzdid; //诊断记录编号

    bool operate_over;
    int current_row; //故障列表的当前行号
    QString pid,userID, Name, PWD;//登录账号

    QSqlDatabase lite_db,post_db;

    void inits();
    void openIni();
    void saveIni();
    void openSqlite();
    void openPostgreSql();
    QString get_nextczid(bool yesno, QString czid);
    QString get_lastczid(QString zdid);
    QString create_zdid();
    void save_cznr();

signals:
    void close_dialog();
    void close_config();

private slots:
    void on_action_exit_triggered();
    void showLoginDialog();
    void login(QString user_ID, QString pwd);

    void on_toolButton_search_clicked();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_toolButton_next_clicked();
    void on_toolButton_last_clicked();
    void on_action_upload_triggered();
    void on_action_download_triggered();

    void saveConfigValue(ConfigValue value);
    void finishedSlot(QNetworkReply *reply) ;
    void on_action_login_triggered();
    void on_action_config_triggered();

    void on_toolButton_end_clicked();

    void updateType();
};

#endif // MAINWINDOW_H
