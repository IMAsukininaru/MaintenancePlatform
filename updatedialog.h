#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "configdialog.h"

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = 0);
    ~UpdateDialog();

signals:
    void update_end();

private slots:
    void on_pushButton_update_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_OK_clicked();

private:
    Ui::UpdateDialog *ui;

    ConfigValue settingValue;

    QSqlDatabase lite_db, post_db;

    void openIni();
    void openSqlite();
    void openPostgreSql();

};

#endif // UPDATEDIALOG_H
