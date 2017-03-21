#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    void set_UI(QString UserID);
signals:
    void login(QString name, QString pwd);

private slots:
    void on_toolButton_OK_clicked();

    void on_toolButton_Cancel_clicked();
    void close_dialog();

private:
    Ui::LoginDialog *ui;



};

#endif // LOGINDIALOG_H
