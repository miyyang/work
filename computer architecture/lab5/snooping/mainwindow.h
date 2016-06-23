#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"snooping.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_cpu1_go_clicked();

    void on_pushButton_cpu2_go_clicked();

    void on_pushButton_cpu3_go_clicked();

    void on_pushButton_cpu4_go_clicked();

    void on_pushButton_go_clicked();

    void on_pushButton_reset_clicked();

private:
    void display();
    void reset();

    Ui::MainWindow *ui;
    Snooping _snooping;

    enum snooping_status *_status;
    int _display_step;
    int _memAddr;
    int _cacheAddr;
};

#endif // MAINWINDOW_H
