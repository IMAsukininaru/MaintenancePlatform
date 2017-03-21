#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

struct ConfigValue
{
    QString ip1;
    QString ip2;
    QString ip3;
    QString ip4;
    QString port;
    QString address;
    QString device;
};

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

    ConfigValue get_value();
    void set_value(ConfigValue value, QStringList projnames, QStringList devnames);

signals:
    void save(ConfigValue value);

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();
    void close_dialog();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
