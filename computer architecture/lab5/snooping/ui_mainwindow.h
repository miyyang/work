/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_op;
    QRadioButton *radioButton_by_step;
    QRadioButton *radioButton_to_end;
    QLabel *label;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_go;
    QGroupBox *groupBox_access;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_cpu1_addr;
    QComboBox *comboBox_cpu1_op;
    QPushButton *pushButton_cpu1_go;
    QLabel *label_4;
    QComboBox *comboBox_cpu2_op;
    QLabel *label_5;
    QPushButton *pushButton_cpu2_go;
    QLineEdit *lineEdit_cpu2_addr;
    QLabel *label_6;
    QComboBox *comboBox_cpu3_op;
    QLabel *label_7;
    QPushButton *pushButton_cpu3_go;
    QLineEdit *lineEdit_cpu3_addr;
    QLabel *label_8;
    QComboBox *comboBox_cpu4_op;
    QLabel *label_9;
    QPushButton *pushButton_cpu4_go;
    QLineEdit *lineEdit_cpu4_addr;
    QTableWidget *tableWidget_cache1;
    QLabel *label_10;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_4;
    QFrame *line_3;
    QFrame *line_5;
    QFrame *line_6;
    QTableWidget *tableWidget_memory;
    QLabel *label_bus_status;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QTableWidget *tableWidget_cache2;
    QTableWidget *tableWidget_cache3;
    QTableWidget *tableWidget_cache4;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_cpu1_status;
    QLabel *label_cpu2_status;
    QLabel *label_cpu3_status;
    QLabel *label_cpu4_status;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(956, 737);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox_op = new QGroupBox(centralWidget);
        groupBox_op->setObjectName(QString::fromUtf8("groupBox_op"));
        groupBox_op->setGeometry(QRect(0, 0, 491, 51));
        radioButton_by_step = new QRadioButton(groupBox_op);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton_by_step);
        radioButton_by_step->setObjectName(QString::fromUtf8("radioButton_by_step"));
        radioButton_by_step->setGeometry(QRect(80, 20, 71, 16));
        radioButton_by_step->setChecked(true);
        radioButton_to_end = new QRadioButton(groupBox_op);
        buttonGroup->addButton(radioButton_to_end);
        radioButton_to_end->setObjectName(QString::fromUtf8("radioButton_to_end"));
        radioButton_to_end->setGeometry(QRect(170, 20, 71, 16));
        label = new QLabel(groupBox_op);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 61, 16));
        pushButton_reset = new QPushButton(groupBox_op);
        pushButton_reset->setObjectName(QString::fromUtf8("pushButton_reset"));
        pushButton_reset->setGeometry(QRect(250, 20, 75, 23));
        pushButton_go = new QPushButton(groupBox_op);
        pushButton_go->setObjectName(QString::fromUtf8("pushButton_go"));
        pushButton_go->setGeometry(QRect(330, 20, 75, 23));
        groupBox_access = new QGroupBox(centralWidget);
        groupBox_access->setObjectName(QString::fromUtf8("groupBox_access"));
        groupBox_access->setGeometry(QRect(0, 60, 911, 80));
        label_2 = new QLabel(groupBox_access);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 20, 54, 12));
        label_3 = new QLabel(groupBox_access);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 61, 16));
        lineEdit_cpu1_addr = new QLineEdit(groupBox_access);
        lineEdit_cpu1_addr->setObjectName(QString::fromUtf8("lineEdit_cpu1_addr"));
        lineEdit_cpu1_addr->setGeometry(QRect(80, 30, 41, 20));
        comboBox_cpu1_op = new QComboBox(groupBox_access);
        comboBox_cpu1_op->setObjectName(QString::fromUtf8("comboBox_cpu1_op"));
        comboBox_cpu1_op->setGeometry(QRect(130, 30, 41, 22));
        pushButton_cpu1_go = new QPushButton(groupBox_access);
        pushButton_cpu1_go->setObjectName(QString::fromUtf8("pushButton_cpu1_go"));
        pushButton_cpu1_go->setGeometry(QRect(180, 30, 41, 23));
        label_4 = new QLabel(groupBox_access);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(240, 20, 54, 12));
        comboBox_cpu2_op = new QComboBox(groupBox_access);
        comboBox_cpu2_op->setObjectName(QString::fromUtf8("comboBox_cpu2_op"));
        comboBox_cpu2_op->setGeometry(QRect(360, 30, 41, 22));
        label_5 = new QLabel(groupBox_access);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(240, 40, 61, 16));
        pushButton_cpu2_go = new QPushButton(groupBox_access);
        pushButton_cpu2_go->setObjectName(QString::fromUtf8("pushButton_cpu2_go"));
        pushButton_cpu2_go->setGeometry(QRect(410, 30, 41, 23));
        lineEdit_cpu2_addr = new QLineEdit(groupBox_access);
        lineEdit_cpu2_addr->setObjectName(QString::fromUtf8("lineEdit_cpu2_addr"));
        lineEdit_cpu2_addr->setGeometry(QRect(310, 30, 41, 20));
        label_6 = new QLabel(groupBox_access);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(470, 20, 54, 12));
        comboBox_cpu3_op = new QComboBox(groupBox_access);
        comboBox_cpu3_op->setObjectName(QString::fromUtf8("comboBox_cpu3_op"));
        comboBox_cpu3_op->setGeometry(QRect(590, 30, 41, 22));
        label_7 = new QLabel(groupBox_access);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(470, 40, 61, 16));
        pushButton_cpu3_go = new QPushButton(groupBox_access);
        pushButton_cpu3_go->setObjectName(QString::fromUtf8("pushButton_cpu3_go"));
        pushButton_cpu3_go->setGeometry(QRect(640, 30, 41, 23));
        lineEdit_cpu3_addr = new QLineEdit(groupBox_access);
        lineEdit_cpu3_addr->setObjectName(QString::fromUtf8("lineEdit_cpu3_addr"));
        lineEdit_cpu3_addr->setGeometry(QRect(540, 30, 41, 20));
        label_8 = new QLabel(groupBox_access);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(690, 20, 54, 12));
        comboBox_cpu4_op = new QComboBox(groupBox_access);
        comboBox_cpu4_op->setObjectName(QString::fromUtf8("comboBox_cpu4_op"));
        comboBox_cpu4_op->setGeometry(QRect(810, 30, 41, 22));
        label_9 = new QLabel(groupBox_access);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(690, 40, 61, 16));
        pushButton_cpu4_go = new QPushButton(groupBox_access);
        pushButton_cpu4_go->setObjectName(QString::fromUtf8("pushButton_cpu4_go"));
        pushButton_cpu4_go->setGeometry(QRect(860, 30, 41, 23));
        lineEdit_cpu4_addr = new QLineEdit(groupBox_access);
        lineEdit_cpu4_addr->setObjectName(QString::fromUtf8("lineEdit_cpu4_addr"));
        lineEdit_cpu4_addr->setGeometry(QRect(760, 30, 41, 20));
        tableWidget_cache1 = new QTableWidget(centralWidget);
        if (tableWidget_cache1->columnCount() < 3)
            tableWidget_cache1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_cache1->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_cache1->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_cache1->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_cache1->rowCount() < 4)
            tableWidget_cache1->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_cache1->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_cache1->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_cache1->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_cache1->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_cache1->setItem(0, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_cache1->setItem(0, 1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_cache1->setItem(1, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_cache1->setItem(1, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_cache1->setItem(2, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_cache1->setItem(2, 1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_cache1->setItem(3, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_cache1->setItem(3, 1, __qtablewidgetitem14);
        tableWidget_cache1->setObjectName(QString::fromUtf8("tableWidget_cache1"));
        tableWidget_cache1->setGeometry(QRect(10, 190, 231, 131));
        tableWidget_cache1->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_cache1->horizontalHeader()->setVisible(false);
        tableWidget_cache1->horizontalHeader()->setDefaultSectionSize(75);
        tableWidget_cache1->horizontalHeader()->setHighlightSections(true);
        tableWidget_cache1->verticalHeader()->setVisible(false);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(410, 370, 54, 12));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 360, 851, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(120, 320, 20, 51));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(350, 320, 20, 51));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(580, 320, 20, 51));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(800, 320, 20, 51));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(470, 370, 3, 61));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        tableWidget_memory = new QTableWidget(centralWidget);
        if (tableWidget_memory->columnCount() < 8)
            tableWidget_memory->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(6, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_memory->setHorizontalHeaderItem(7, __qtablewidgetitem22);
        if (tableWidget_memory->rowCount() < 8)
            tableWidget_memory->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(2, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(3, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(4, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(5, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(6, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_memory->setVerticalHeaderItem(7, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_memory->setItem(0, 0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_memory->setItem(0, 2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_memory->setItem(0, 3, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_memory->setItem(0, 4, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_memory->setItem(0, 6, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_memory->setItem(1, 0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_memory->setItem(1, 2, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_memory->setItem(1, 4, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_memory->setItem(1, 6, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_memory->setItem(2, 0, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_memory->setItem(2, 2, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_memory->setItem(2, 4, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_memory->setItem(2, 6, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_memory->setItem(3, 0, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_memory->setItem(3, 2, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_memory->setItem(3, 4, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_memory->setItem(3, 6, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget_memory->setItem(4, 0, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget_memory->setItem(4, 2, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget_memory->setItem(4, 4, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget_memory->setItem(4, 6, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget_memory->setItem(5, 0, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget_memory->setItem(5, 2, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget_memory->setItem(5, 4, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget_memory->setItem(5, 6, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget_memory->setItem(6, 0, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidget_memory->setItem(6, 2, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidget_memory->setItem(6, 4, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidget_memory->setItem(6, 6, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tableWidget_memory->setItem(7, 0, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tableWidget_memory->setItem(7, 2, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tableWidget_memory->setItem(7, 4, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tableWidget_memory->setItem(7, 6, __qtablewidgetitem63);
        tableWidget_memory->setObjectName(QString::fromUtf8("tableWidget_memory"));
        tableWidget_memory->setGeometry(QRect(55, 430, 821, 251));
        tableWidget_memory->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_memory->horizontalHeader()->setVisible(false);
        tableWidget_memory->verticalHeader()->setVisible(false);
        label_bus_status = new QLabel(centralWidget);
        label_bus_status->setObjectName(QString::fromUtf8("label_bus_status"));
        label_bus_status->setGeometry(QRect(480, 380, 361, 16));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 520, 54, 12));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(110, 150, 54, 12));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(340, 150, 51, 16));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(570, 150, 54, 12));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(790, 150, 54, 12));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(110, 170, 54, 12));
        tableWidget_cache2 = new QTableWidget(centralWidget);
        if (tableWidget_cache2->columnCount() < 3)
            tableWidget_cache2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tableWidget_cache2->setHorizontalHeaderItem(0, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tableWidget_cache2->setHorizontalHeaderItem(1, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tableWidget_cache2->setHorizontalHeaderItem(2, __qtablewidgetitem66);
        if (tableWidget_cache2->rowCount() < 4)
            tableWidget_cache2->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tableWidget_cache2->setVerticalHeaderItem(0, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tableWidget_cache2->setVerticalHeaderItem(1, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tableWidget_cache2->setVerticalHeaderItem(2, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tableWidget_cache2->setVerticalHeaderItem(3, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tableWidget_cache2->setItem(0, 0, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tableWidget_cache2->setItem(0, 1, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tableWidget_cache2->setItem(1, 0, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tableWidget_cache2->setItem(1, 1, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tableWidget_cache2->setItem(2, 0, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tableWidget_cache2->setItem(2, 1, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tableWidget_cache2->setItem(3, 0, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tableWidget_cache2->setItem(3, 1, __qtablewidgetitem78);
        tableWidget_cache2->setObjectName(QString::fromUtf8("tableWidget_cache2"));
        tableWidget_cache2->setGeometry(QRect(240, 190, 231, 131));
        tableWidget_cache2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_cache2->horizontalHeader()->setVisible(false);
        tableWidget_cache2->horizontalHeader()->setDefaultSectionSize(75);
        tableWidget_cache2->horizontalHeader()->setHighlightSections(true);
        tableWidget_cache2->verticalHeader()->setVisible(false);
        tableWidget_cache3 = new QTableWidget(centralWidget);
        if (tableWidget_cache3->columnCount() < 3)
            tableWidget_cache3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tableWidget_cache3->setHorizontalHeaderItem(0, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tableWidget_cache3->setHorizontalHeaderItem(1, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tableWidget_cache3->setHorizontalHeaderItem(2, __qtablewidgetitem81);
        if (tableWidget_cache3->rowCount() < 4)
            tableWidget_cache3->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tableWidget_cache3->setVerticalHeaderItem(0, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tableWidget_cache3->setVerticalHeaderItem(1, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tableWidget_cache3->setVerticalHeaderItem(2, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tableWidget_cache3->setVerticalHeaderItem(3, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tableWidget_cache3->setItem(0, 0, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tableWidget_cache3->setItem(0, 1, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tableWidget_cache3->setItem(1, 0, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tableWidget_cache3->setItem(1, 1, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tableWidget_cache3->setItem(2, 0, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tableWidget_cache3->setItem(2, 1, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tableWidget_cache3->setItem(3, 0, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tableWidget_cache3->setItem(3, 1, __qtablewidgetitem93);
        tableWidget_cache3->setObjectName(QString::fromUtf8("tableWidget_cache3"));
        tableWidget_cache3->setGeometry(QRect(480, 190, 231, 131));
        tableWidget_cache3->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_cache3->horizontalHeader()->setVisible(false);
        tableWidget_cache3->horizontalHeader()->setDefaultSectionSize(75);
        tableWidget_cache3->horizontalHeader()->setHighlightSections(true);
        tableWidget_cache3->verticalHeader()->setVisible(false);
        tableWidget_cache4 = new QTableWidget(centralWidget);
        if (tableWidget_cache4->columnCount() < 3)
            tableWidget_cache4->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tableWidget_cache4->setHorizontalHeaderItem(0, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tableWidget_cache4->setHorizontalHeaderItem(1, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tableWidget_cache4->setHorizontalHeaderItem(2, __qtablewidgetitem96);
        if (tableWidget_cache4->rowCount() < 4)
            tableWidget_cache4->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tableWidget_cache4->setVerticalHeaderItem(0, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tableWidget_cache4->setVerticalHeaderItem(1, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tableWidget_cache4->setVerticalHeaderItem(2, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tableWidget_cache4->setVerticalHeaderItem(3, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        tableWidget_cache4->setItem(0, 0, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        tableWidget_cache4->setItem(0, 1, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        tableWidget_cache4->setItem(1, 0, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        tableWidget_cache4->setItem(1, 1, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        tableWidget_cache4->setItem(2, 0, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        tableWidget_cache4->setItem(2, 1, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        tableWidget_cache4->setItem(3, 0, __qtablewidgetitem107);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        tableWidget_cache4->setItem(3, 1, __qtablewidgetitem108);
        tableWidget_cache4->setObjectName(QString::fromUtf8("tableWidget_cache4"));
        tableWidget_cache4->setGeometry(QRect(710, 190, 231, 131));
        tableWidget_cache4->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_cache4->horizontalHeader()->setVisible(false);
        tableWidget_cache4->horizontalHeader()->setDefaultSectionSize(75);
        tableWidget_cache4->horizontalHeader()->setHighlightSections(true);
        tableWidget_cache4->verticalHeader()->setVisible(false);
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(340, 170, 54, 12));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(570, 170, 54, 12));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(790, 170, 54, 12));
        label_cpu1_status = new QLabel(centralWidget);
        label_cpu1_status->setObjectName(QString::fromUtf8("label_cpu1_status"));
        label_cpu1_status->setGeometry(QRect(160, 160, 141, 16));
        label_cpu2_status = new QLabel(centralWidget);
        label_cpu2_status->setObjectName(QString::fromUtf8("label_cpu2_status"));
        label_cpu2_status->setGeometry(QRect(390, 160, 151, 16));
        label_cpu3_status = new QLabel(centralWidget);
        label_cpu3_status->setObjectName(QString::fromUtf8("label_cpu3_status"));
        label_cpu3_status->setGeometry(QRect(630, 160, 131, 16));
        label_cpu4_status = new QLabel(centralWidget);
        label_cpu4_status->setObjectName(QString::fromUtf8("label_cpu4_status"));
        label_cpu4_status->setGeometry(QRect(850, 160, 101, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 956, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\244\232Cache\344\270\200\350\207\264\346\200\247\346\250\241\346\213\237\345\231\250--\347\233\221\345\220\254\346\263\225", 0, QApplication::UnicodeUTF8));
        groupBox_op->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        radioButton_by_step->setText(QApplication::translate("MainWindow", "\345\215\225\346\255\245\346\211\247\350\241\214", 0, QApplication::UnicodeUTF8));
        radioButton_to_end->setText(QApplication::translate("MainWindow", "\350\277\236\347\273\255\346\211\247\350\241\214", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_reset->setText(QApplication::translate("MainWindow", "\345\244\215\344\275\215", 0, QApplication::UnicodeUTF8));
        pushButton_go->setText(QApplication::translate("MainWindow", "\346\255\245\350\277\233", 0, QApplication::UnicodeUTF8));
        groupBox_access->setTitle(QString());
        label_2->setText(QApplication::translate("MainWindow", "\350\256\277\351\227\256\345\235\227\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "(\344\270\273\345\255\230\345\234\260\345\235\200)", 0, QApplication::UnicodeUTF8));
        comboBox_cpu1_op->clear();
        comboBox_cpu1_op->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\350\257\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\345\206\231", 0, QApplication::UnicodeUTF8)
        );
        pushButton_cpu1_go->setText(QApplication::translate("MainWindow", "go", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\350\256\277\351\227\256\345\235\227\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_cpu2_op->clear();
        comboBox_cpu2_op->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\350\257\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\345\206\231", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("MainWindow", "(\344\270\273\345\255\230\345\234\260\345\235\200)", 0, QApplication::UnicodeUTF8));
        pushButton_cpu2_go->setText(QApplication::translate("MainWindow", "go", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "\350\256\277\351\227\256\345\235\227\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_cpu3_op->clear();
        comboBox_cpu3_op->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\350\257\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\345\206\231", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("MainWindow", "(\344\270\273\345\255\230\345\234\260\345\235\200)", 0, QApplication::UnicodeUTF8));
        pushButton_cpu3_go->setText(QApplication::translate("MainWindow", "go", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "\350\256\277\351\227\256\345\235\227\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_cpu4_op->clear();
        comboBox_cpu4_op->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\350\257\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\345\206\231", 0, QApplication::UnicodeUTF8)
        );
        label_9->setText(QApplication::translate("MainWindow", "(\344\270\273\345\255\230\345\234\260\345\235\200)", 0, QApplication::UnicodeUTF8));
        pushButton_cpu4_go->setText(QApplication::translate("MainWindow", "go", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_cache1->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Cache A", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_cache1->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_cache1->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_cache1->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_cache1->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_cache1->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_cache1->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget_cache1->isSortingEnabled();
        tableWidget_cache1->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_cache1->item(0, 0);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_cache1->item(0, 1);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_cache1->item(1, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_cache1->item(1, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_cache1->item(2, 0);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_cache1->item(2, 1);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_cache1->item(3, 0);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_cache1->item(3, 1);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        tableWidget_cache1->setSortingEnabled(__sortingEnabled);

        label_10->setText(QApplication::translate("MainWindow", "\346\200\273\347\272\277", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_memory->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_memory->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_memory->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_memory->horizontalHeaderItem(3);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_memory->horizontalHeaderItem(4);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_memory->horizontalHeaderItem(5);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_memory->horizontalHeaderItem(6);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_memory->horizontalHeaderItem(7);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_memory->verticalHeaderItem(0);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_memory->verticalHeaderItem(1);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_memory->verticalHeaderItem(2);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_memory->verticalHeaderItem(3);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_memory->verticalHeaderItem(4);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_memory->verticalHeaderItem(5);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_memory->verticalHeaderItem(6);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_memory->verticalHeaderItem(7);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tableWidget_memory->isSortingEnabled();
        tableWidget_memory->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_memory->item(0, 0);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_memory->item(0, 2);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_memory->item(0, 4);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "16", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_memory->item(0, 6);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "24", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_memory->item(1, 0);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_memory->item(1, 2);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "9", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_memory->item(1, 4);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "17", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_memory->item(1, 6);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "25", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_memory->item(2, 0);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_memory->item(2, 2);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_memory->item(2, 4);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "18", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_memory->item(2, 6);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "26", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_memory->item(3, 0);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_memory->item(3, 2);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "11", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_memory->item(3, 4);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "19", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_memory->item(3, 6);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "27", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget_memory->item(4, 0);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget_memory->item(4, 2);
        ___qtablewidgetitem48->setText(QApplication::translate("MainWindow", "12", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget_memory->item(4, 4);
        ___qtablewidgetitem49->setText(QApplication::translate("MainWindow", "20", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget_memory->item(4, 6);
        ___qtablewidgetitem50->setText(QApplication::translate("MainWindow", "28", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget_memory->item(5, 0);
        ___qtablewidgetitem51->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget_memory->item(5, 2);
        ___qtablewidgetitem52->setText(QApplication::translate("MainWindow", "13", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget_memory->item(5, 4);
        ___qtablewidgetitem53->setText(QApplication::translate("MainWindow", "21", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget_memory->item(5, 6);
        ___qtablewidgetitem54->setText(QApplication::translate("MainWindow", "29", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidget_memory->item(6, 0);
        ___qtablewidgetitem55->setText(QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem56 = tableWidget_memory->item(6, 2);
        ___qtablewidgetitem56->setText(QApplication::translate("MainWindow", "14", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem57 = tableWidget_memory->item(6, 4);
        ___qtablewidgetitem57->setText(QApplication::translate("MainWindow", "22", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem58 = tableWidget_memory->item(6, 6);
        ___qtablewidgetitem58->setText(QApplication::translate("MainWindow", "30", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem59 = tableWidget_memory->item(7, 0);
        ___qtablewidgetitem59->setText(QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem60 = tableWidget_memory->item(7, 2);
        ___qtablewidgetitem60->setText(QApplication::translate("MainWindow", "15", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem61 = tableWidget_memory->item(7, 4);
        ___qtablewidgetitem61->setText(QApplication::translate("MainWindow", "23", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem62 = tableWidget_memory->item(7, 6);
        ___qtablewidgetitem62->setText(QApplication::translate("MainWindow", "31", 0, QApplication::UnicodeUTF8));
        tableWidget_memory->setSortingEnabled(__sortingEnabled1);

        label_bus_status->setText(QString());
        label_12->setText(QApplication::translate("MainWindow", "\345\255\230\345\202\250\345\231\250", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "CPU A", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "CPU B", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "CPU C", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "CPU D", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "Cache A", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem63 = tableWidget_cache2->horizontalHeaderItem(0);
        ___qtablewidgetitem63->setText(QApplication::translate("MainWindow", "Cache A", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem64 = tableWidget_cache2->horizontalHeaderItem(1);
        ___qtablewidgetitem64->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem65 = tableWidget_cache2->horizontalHeaderItem(2);
        ___qtablewidgetitem65->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem66 = tableWidget_cache2->verticalHeaderItem(0);
        ___qtablewidgetitem66->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem67 = tableWidget_cache2->verticalHeaderItem(1);
        ___qtablewidgetitem67->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem68 = tableWidget_cache2->verticalHeaderItem(2);
        ___qtablewidgetitem68->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem69 = tableWidget_cache2->verticalHeaderItem(3);
        ___qtablewidgetitem69->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = tableWidget_cache2->isSortingEnabled();
        tableWidget_cache2->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem70 = tableWidget_cache2->item(0, 0);
        ___qtablewidgetitem70->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem71 = tableWidget_cache2->item(0, 1);
        ___qtablewidgetitem71->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem72 = tableWidget_cache2->item(1, 0);
        ___qtablewidgetitem72->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem73 = tableWidget_cache2->item(1, 1);
        ___qtablewidgetitem73->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem74 = tableWidget_cache2->item(2, 0);
        ___qtablewidgetitem74->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem75 = tableWidget_cache2->item(2, 1);
        ___qtablewidgetitem75->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem76 = tableWidget_cache2->item(3, 0);
        ___qtablewidgetitem76->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem77 = tableWidget_cache2->item(3, 1);
        ___qtablewidgetitem77->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        tableWidget_cache2->setSortingEnabled(__sortingEnabled2);

        QTableWidgetItem *___qtablewidgetitem78 = tableWidget_cache3->horizontalHeaderItem(0);
        ___qtablewidgetitem78->setText(QApplication::translate("MainWindow", "Cache A", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem79 = tableWidget_cache3->horizontalHeaderItem(1);
        ___qtablewidgetitem79->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem80 = tableWidget_cache3->horizontalHeaderItem(2);
        ___qtablewidgetitem80->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem81 = tableWidget_cache3->verticalHeaderItem(0);
        ___qtablewidgetitem81->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem82 = tableWidget_cache3->verticalHeaderItem(1);
        ___qtablewidgetitem82->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem83 = tableWidget_cache3->verticalHeaderItem(2);
        ___qtablewidgetitem83->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem84 = tableWidget_cache3->verticalHeaderItem(3);
        ___qtablewidgetitem84->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled3 = tableWidget_cache3->isSortingEnabled();
        tableWidget_cache3->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem85 = tableWidget_cache3->item(0, 0);
        ___qtablewidgetitem85->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem86 = tableWidget_cache3->item(0, 1);
        ___qtablewidgetitem86->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem87 = tableWidget_cache3->item(1, 0);
        ___qtablewidgetitem87->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem88 = tableWidget_cache3->item(1, 1);
        ___qtablewidgetitem88->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem89 = tableWidget_cache3->item(2, 0);
        ___qtablewidgetitem89->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem90 = tableWidget_cache3->item(2, 1);
        ___qtablewidgetitem90->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem91 = tableWidget_cache3->item(3, 0);
        ___qtablewidgetitem91->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem92 = tableWidget_cache3->item(3, 1);
        ___qtablewidgetitem92->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        tableWidget_cache3->setSortingEnabled(__sortingEnabled3);

        QTableWidgetItem *___qtablewidgetitem93 = tableWidget_cache4->horizontalHeaderItem(0);
        ___qtablewidgetitem93->setText(QApplication::translate("MainWindow", "Cache A", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem94 = tableWidget_cache4->horizontalHeaderItem(1);
        ___qtablewidgetitem94->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem95 = tableWidget_cache4->horizontalHeaderItem(2);
        ___qtablewidgetitem95->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem96 = tableWidget_cache4->verticalHeaderItem(0);
        ___qtablewidgetitem96->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem97 = tableWidget_cache4->verticalHeaderItem(1);
        ___qtablewidgetitem97->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem98 = tableWidget_cache4->verticalHeaderItem(2);
        ___qtablewidgetitem98->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem99 = tableWidget_cache4->verticalHeaderItem(3);
        ___qtablewidgetitem99->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled4 = tableWidget_cache4->isSortingEnabled();
        tableWidget_cache4->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem100 = tableWidget_cache4->item(0, 0);
        ___qtablewidgetitem100->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem101 = tableWidget_cache4->item(0, 1);
        ___qtablewidgetitem101->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem102 = tableWidget_cache4->item(1, 0);
        ___qtablewidgetitem102->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem103 = tableWidget_cache4->item(1, 1);
        ___qtablewidgetitem103->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem104 = tableWidget_cache4->item(2, 0);
        ___qtablewidgetitem104->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem105 = tableWidget_cache4->item(2, 1);
        ___qtablewidgetitem105->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem106 = tableWidget_cache4->item(3, 0);
        ___qtablewidgetitem106->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem107 = tableWidget_cache4->item(3, 1);
        ___qtablewidgetitem107->setText(QApplication::translate("MainWindow", "\345\244\261\346\225\210", 0, QApplication::UnicodeUTF8));
        tableWidget_cache4->setSortingEnabled(__sortingEnabled4);

        label_18->setText(QApplication::translate("MainWindow", "Cache B", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "Cache C", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "Cache D", 0, QApplication::UnicodeUTF8));
        label_cpu1_status->setText(QString());
        label_cpu2_status->setText(QString());
        label_cpu3_status->setText(QString());
        label_cpu4_status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
