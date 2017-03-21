/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_exit;
    QAction *action_download;
    QAction *action_upload;
    QAction *action_config;
    QAction *action_login;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QToolButton *toolButton_search;
    QLineEdit *lineEdit_description;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_ID;
    QComboBox *comboBox_type;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTextBrowser *textBrowser_description;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QTextBrowser *textBrowser_operation;
    QFrame *frame_5;
    QGridLayout *gridLayout_5;
    QToolButton *toolButton_last;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_yes;
    QRadioButton *radioButton_no;
    QFrame *frame_4;
    QGridLayout *gridLayout_3;
    QToolButton *toolButton_next;
    QFrame *frame_6;
    QGridLayout *gridLayout_6;
    QToolButton *toolButton_end;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *plainTextEdit_result;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setMinimumSize(QSize(1024, 768));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/icon/maintenance_tool_tools_96px_516592_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/icon/exit_48px_27110_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_exit->setIcon(icon1);
        action_exit->setShortcutContext(Qt::WidgetShortcut);
        action_exit->setMenuRole(QAction::TextHeuristicRole);
        action_download = new QAction(MainWindow);
        action_download->setObjectName(QStringLiteral("action_download"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/icon/refresh_48px_30803_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_download->setIcon(icon2);
        action_upload = new QAction(MainWindow);
        action_upload->setObjectName(QStringLiteral("action_upload"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/icon/upload_48px_28748_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_upload->setIcon(icon3);
        action_config = new QAction(MainWindow);
        action_config->setObjectName(QStringLiteral("action_config"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/icon/cog_config_configuracion_configuration_edit_48px_249_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_config->setIcon(icon4);
        action_login = new QAction(MainWindow);
        action_login->setObjectName(QStringLiteral("action_login"));
        action_login->setEnabled(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/icon/login.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_login->setIcon(icon5);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QFont font;
        font.setPointSize(11);
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        toolButton_search = new QToolButton(groupBox);
        toolButton_search->setObjectName(QStringLiteral("toolButton_search"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/icon/fake_find_magnifying_glass_search_zoom_48px_106_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_search->setIcon(icon6);

        gridLayout->addWidget(toolButton_search, 1, 5, 1, 1);

        lineEdit_description = new QLineEdit(groupBox);
        lineEdit_description->setObjectName(QStringLiteral("lineEdit_description"));

        gridLayout->addWidget(lineEdit_description, 1, 4, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_ID = new QLineEdit(groupBox);
        lineEdit_ID->setObjectName(QStringLiteral("lineEdit_ID"));

        gridLayout->addWidget(lineEdit_ID, 1, 1, 1, 1);

        comboBox_type = new QComboBox(groupBox);
        comboBox_type->setObjectName(QStringLiteral("comboBox_type"));

        gridLayout->addWidget(comboBox_type, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 6, 1, 1);


        verticalLayout->addWidget(groupBox);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableWidget = new QTableWidget(frame);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setBackground(QColor(255, 255, 255));
        __qtablewidgetitem3->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMaximumSize(QSize(400, 16777215));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout->addWidget(tableWidget);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(frame_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textBrowser_description = new QTextBrowser(groupBox_2);
        textBrowser_description->setObjectName(QStringLiteral("textBrowser_description"));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        textBrowser_description->setFont(font1);

        gridLayout_2->addWidget(textBrowser_description, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(frame_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        textBrowser_operation = new QTextBrowser(groupBox_3);
        textBrowser_operation->setObjectName(QStringLiteral("textBrowser_operation"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(textBrowser_operation->sizePolicy().hasHeightForWidth());
        textBrowser_operation->setSizePolicy(sizePolicy3);
        textBrowser_operation->setMaximumSize(QSize(16777215, 100));
        textBrowser_operation->setFont(font1);

        gridLayout_7->addWidget(textBrowser_operation, 0, 0, 1, 5);

        frame_5 = new QFrame(groupBox_3);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy4);
        frame_5->setMinimumSize(QSize(111, 0));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        toolButton_last = new QToolButton(frame_5);
        toolButton_last->setObjectName(QStringLiteral("toolButton_last"));
        sizePolicy2.setHeightForWidth(toolButton_last->sizePolicy().hasHeightForWidth());
        toolButton_last->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        toolButton_last->setFont(font2);

        gridLayout_5->addWidget(toolButton_last, 0, 0, 1, 1);


        gridLayout_7->addWidget(frame_5, 1, 0, 1, 1);

        frame_3 = new QFrame(groupBox_3);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        sizePolicy3.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy3);
        QFont font3;
        font3.setPointSize(12);
        frame_3->setFont(font3);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        radioButton_yes = new QRadioButton(frame_3);
        radioButton_yes->setObjectName(QStringLiteral("radioButton_yes"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        radioButton_yes->setFont(font4);
        radioButton_yes->setStyleSheet(QStringLiteral("color: qlineargradient(spread:pad, x1:0.244, y1:0.148, x2:0.552, y2:0.948864, stop:1 rgba(85, 156, 0, 255));"));

        verticalLayout_3->addWidget(radioButton_yes);

        radioButton_no = new QRadioButton(frame_3);
        radioButton_no->setObjectName(QStringLiteral("radioButton_no"));
        radioButton_no->setFont(font4);
        radioButton_no->setStyleSheet(QStringLiteral("color: qlineargradient(spread:pad, x1:0.244, y1:0.148, x2:0.552, y2:0.948864, stop:1 rgba(255, 85, 85, 255));"));

        verticalLayout_3->addWidget(radioButton_no);


        gridLayout_7->addWidget(frame_3, 1, 1, 1, 1);

        frame_4 = new QFrame(groupBox_3);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        sizePolicy2.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy2);
        frame_4->setFont(font3);
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        toolButton_next = new QToolButton(frame_4);
        toolButton_next->setObjectName(QStringLiteral("toolButton_next"));
        sizePolicy2.setHeightForWidth(toolButton_next->sizePolicy().hasHeightForWidth());
        toolButton_next->setSizePolicy(sizePolicy2);
        toolButton_next->setMinimumSize(QSize(80, 80));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font5.setBold(true);
        font5.setWeight(75);
        toolButton_next->setFont(font5);

        gridLayout_3->addWidget(toolButton_next, 0, 1, 1, 1);


        gridLayout_7->addWidget(frame_4, 1, 2, 1, 1);

        frame_6 = new QFrame(groupBox_3);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        sizePolicy2.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
        frame_6->setSizePolicy(sizePolicy2);
        frame_6->setFont(font3);
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        toolButton_end = new QToolButton(frame_6);
        toolButton_end->setObjectName(QStringLiteral("toolButton_end"));
        sizePolicy2.setHeightForWidth(toolButton_end->sizePolicy().hasHeightForWidth());
        toolButton_end->setSizePolicy(sizePolicy2);
        toolButton_end->setMinimumSize(QSize(80, 80));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font6.setBold(true);
        font6.setWeight(75);
        font6.setStyleStrategy(QFont::PreferDefault);
        toolButton_end->setFont(font6);

        gridLayout_6->addWidget(toolButton_end, 0, 1, 1, 1);


        gridLayout_7->addWidget(frame_6, 1, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        plainTextEdit_result = new QPlainTextEdit(groupBox_3);
        plainTextEdit_result->setObjectName(QStringLiteral("plainTextEdit_result"));
        sizePolicy3.setHeightForWidth(plainTextEdit_result->sizePolicy().hasHeightForWidth());
        plainTextEdit_result->setSizePolicy(sizePolicy3);
        plainTextEdit_result->setMaximumSize(QSize(16777215, 80));

        gridLayout_7->addWidget(plainTextEdit_result, 2, 0, 1, 5);


        verticalLayout_2->addWidget(groupBox_3);


        horizontalLayout->addWidget(frame_2);


        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setFont(font1);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(action_config);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_download);
        mainToolBar->addAction(action_upload);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_login);
        mainToolBar->addAction(action_exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\347\273\264\346\212\244\345\272\224\347\224\250\345\271\263\345\217\260-Version 1.0", 0));
        action_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        action_download->setText(QApplication::translate("MainWindow", "\346\233\264\346\226\260\346\225\205\351\232\234\346\235\241\347\233\256", 0));
#ifndef QT_NO_TOOLTIP
        action_download->setToolTip(QApplication::translate("MainWindow", "\346\233\264\346\226\260\346\225\205\351\232\234\346\235\241\347\233\256", 0));
#endif // QT_NO_TOOLTIP
        action_upload->setText(QApplication::translate("MainWindow", "\344\270\212\344\274\240\350\257\212\346\226\255\350\256\260\345\275\225", 0));
        action_config->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        action_login->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
        groupBox->setTitle(QString());
        toolButton_search->setText(QApplication::translate("MainWindow", "...", 0));
        label->setText(QApplication::translate("MainWindow", "\346\225\205\351\232\234\347\261\273\345\210\253\357\274\232", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\225\205\351\232\234\344\273\243\347\240\201\357\274\232", 0));
        label_3->setText(QApplication::translate("MainWindow", "\346\225\205\351\232\234\346\217\217\350\277\260\357\274\232", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\345\272\217\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\225\205\351\232\234\344\273\243\347\240\201", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\346\225\205\351\232\234\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "id", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\225\205\351\232\234\346\217\217\350\277\260", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234\346\214\207\345\215\227", 0));
        toolButton_last->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\346\255\245", 0));
        radioButton_yes->setText(QApplication::translate("MainWindow", "\346\255\243\345\270\270", 0));
        radioButton_no->setText(QApplication::translate("MainWindow", "\344\270\215\346\255\243\345\270\270", 0));
        toolButton_next->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\346\255\245", 0));
        toolButton_end->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237", 0));
        plainTextEdit_result->setPlainText(QString());
        plainTextEdit_result->setPlaceholderText(QApplication::translate("MainWindow", "\346\243\200\346\265\213\347\273\223\346\236\234\350\241\245\345\205\205\350\257\264\346\230\216...", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
