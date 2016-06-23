#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_go->setVisible(false);
    _display_step=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    int i;
    int j;

    _snooping.reset();

    //clear display
    ui->radioButton_by_step->setEnabled(true);
    ui->radioButton_to_end->setEnabled(true);
    ui->radioButton_by_step->setChecked(true);
    ui->pushButton_go->setVisible(false);

    ui->label_cpu1_status->setText("");
    ui->label_cpu2_status->setText("");
    ui->label_cpu3_status->setText("");
    ui->label_cpu4_status->setText("");
    ui->label_bus_status->setText("");

    ui->groupBox_access->setEnabled(true);
    ui->lineEdit_cpu1_addr->setText("");
    ui->comboBox_cpu1_op->setCurrentIndex(0);
    ui->lineEdit_cpu2_addr->setText("");
    ui->comboBox_cpu2_op->setCurrentIndex(0);
    ui->lineEdit_cpu3_addr->setText("");
    ui->comboBox_cpu3_op->setCurrentIndex(0);
    ui->lineEdit_cpu4_addr->setText("");
    ui->comboBox_cpu4_op->setCurrentIndex(0);

    for(i=0;i<CACHE_SIZE;i++)
    {
        ui->tableWidget_cache1->setItem(i,1,new QTableWidgetItem("失效"));
        ui->tableWidget_cache1->setItem(i,2,new QTableWidgetItem(""));

        ui->tableWidget_cache2->setItem(i,1,new QTableWidgetItem("失效"));
        ui->tableWidget_cache2->setItem(i,2,new QTableWidgetItem(""));

        ui->tableWidget_cache3->setItem(i,1,new QTableWidgetItem("失效"));
        ui->tableWidget_cache3->setItem(i,2,new QTableWidgetItem(""));

        ui->tableWidget_cache4->setItem(i,1,new QTableWidgetItem("失效"));
        ui->tableWidget_cache4->setItem(i,2,new QTableWidgetItem(""));
    }

    for(i=0;i<8;i++)
    {
        for(j=1;j<8;j+=2)
        {
            ui->tableWidget_memory->setItem(i,j,new QTableWidgetItem(""));
        }
    }


}

void MainWindow::on_pushButton_cpu1_go_clicked()
{
    int index;
    int i;

    index=ui->comboBox_cpu1_op->currentIndex();

    _memAddr=ui->lineEdit_cpu1_addr->text().toInt();
    _cacheAddr=_memAddr%CACHE_SIZE;


    if(_memAddr>31 || _memAddr<0)
    {
        ui->label_cpu1_status->setText("内存地址错误");
        return;
    }

    switch(index)
    {
    case 0:
        _snooping.read(0,_memAddr);
        break;
    case 1:
        _snooping.write(0,_memAddr);
        break;

    default:
        break;
    }

    _status=_snooping.get_status();

    ui->groupBox_access->setEnabled(false);
    ui->radioButton_by_step->setEnabled(false);
    ui->radioButton_to_end->setEnabled(false);

    if(ui->radioButton_by_step->isChecked())
    {
        ui->pushButton_go->setVisible(true);
    }
    else
    {
        for(i=0;i<6;i++)
        {
            display();
            //QThread::msleep(500);
        }

    }

}

void MainWindow::on_pushButton_cpu2_go_clicked()
{
    int index;
    int i;

    index=ui->comboBox_cpu2_op->currentIndex();

    _memAddr=ui->lineEdit_cpu2_addr->text().toInt();
    _cacheAddr=_memAddr%CACHE_SIZE;


    if(_memAddr>31 || _memAddr<0)
    {
        ui->label_cpu2_status->setText("内存地址错误");
        return;
    }

    switch(index)
    {
    case 0:
        _snooping.read(1,_memAddr);
        break;
    case 1:
        _snooping.write(1,_memAddr);
        break;

    default:
        break;
    }

    _status=_snooping.get_status();

    ui->groupBox_access->setEnabled(false);
    ui->radioButton_by_step->setEnabled(false);
    ui->radioButton_to_end->setEnabled(false);

    if(ui->radioButton_by_step->isChecked())
    {
        ui->pushButton_go->setVisible(true);
    }
    else
    {
        for(i=0;i<6;i++)
        {
            display();
        }

    }

}

void MainWindow::on_pushButton_cpu3_go_clicked()
{
    int index;
    int i;

    index=ui->comboBox_cpu3_op->currentIndex();

    _memAddr=ui->lineEdit_cpu3_addr->text().toInt();
    _cacheAddr=_memAddr%CACHE_SIZE;


    if(_memAddr>31 || _memAddr<0)
    {
        ui->label_cpu3_status->setText("内存地址错误");
        return;
    }

    switch(index)
    {
    case 0:
        _snooping.read(2,_memAddr);
        break;
    case 1:
        _snooping.write(2,_memAddr);
        break;

    default:
        break;
    }

    _status=_snooping.get_status();
    ui->groupBox_access->setEnabled(false);
    ui->radioButton_by_step->setEnabled(false);
    ui->radioButton_to_end->setEnabled(false);


    if(ui->radioButton_by_step->isChecked())
    {
        ui->pushButton_go->setVisible(true);
    }
    else
    {
        for(i=0;i<6;i++)
        {
            display();
        }

    }

}

void MainWindow::on_pushButton_cpu4_go_clicked()
{
    int index;
    int i;

    index=ui->comboBox_cpu4_op->currentIndex();

    _memAddr=ui->lineEdit_cpu4_addr->text().toInt();
    _cacheAddr=_memAddr%CACHE_SIZE;


    if(_memAddr>31 || _memAddr<0)
    {
        ui->label_cpu4_status->setText("内存地址错误");
        return;
    }

    switch(index)
    {
    case 0:
        _snooping.read(3,_memAddr);
        break;
    case 1:
        _snooping.write(3,_memAddr);
        break;

    default:
        break;
    }

    _status=_snooping.get_status();
    ui->groupBox_access->setEnabled(false);
    ui->radioButton_by_step->setEnabled(false);
    ui->radioButton_to_end->setEnabled(false);

    if(ui->radioButton_by_step->isChecked())
    {
        ui->pushButton_go->setVisible(true);
    }
    else
    {
        for(i=0;i<6;i++)
        {
            display();
        }

    }

}



void MainWindow::on_pushButton_go_clicked()
{
    display();
}

void MainWindow::display()
{
    int i;
    int column;
    int row;
    int addr;

    char indexch;
    QString tempStr;
    QString tempStr1;

    switch(_display_step)
    {
    case 0://cpu
        ui->label_cpu1_status->setText(status_str[_status[0]]);
        ui->label_cpu2_status->setText(status_str[_status[1]]);
        ui->label_cpu3_status->setText(status_str[_status[2]]);
        ui->label_cpu4_status->setText(status_str[_status[3]]);
        _display_step++;
        break;
    case 2://bus
        for(i=0;i<4;i++)
        {
            if(_status[i+2*CACHE_NUM] != NO_ACTION)
            {
                ui->label_bus_status->setText(status_str[_status[i+2*CACHE_NUM]]);
            }
        }
        _display_step++;
        break;
    case 1://local write back
        for(i=0;i<4;i++)
        {
            if(_status[i+CACHE_NUM] != NO_ACTION)
            {
                tempStr="CPU";
                indexch='A'+i;
                tempStr+=indexch;

                ui->label_bus_status->setText(tempStr+"写回");

                tempStr="写回";
                addr=_snooping.get_local_wb_addr();
                column=addr/8*2+1;
                row=addr%8;
                ui->tableWidget_memory->setItem(row,column,new QTableWidgetItem(tempStr));


                tempStr=status_str[_status[i+CACHE_NUM]];

                switch(i)
                {
                case 0:

                    ui->tableWidget_cache1->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache1->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache1->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 1:
                    ui->tableWidget_cache2->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache2->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache2->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 2:
                    ui->tableWidget_cache3->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache3->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache3->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 3:
                    ui->tableWidget_cache4->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache4->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache4->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                default:
                    break;
                }
            }
        }



        _display_step++;
        break;
    case 3://remote write back

        tempStr="";
        // clear local_wb_addr first
        addr=_snooping.get_local_wb_addr();
        column=addr/8*2+1;
        row=addr%8;
        ui->tableWidget_memory->setItem(row,column,new QTableWidgetItem(tempStr));


        for(i=0;i<4;i++)
        {
            if(_status[i+3*CACHE_NUM] != NO_ACTION)
            {
                tempStr="CPU";
                indexch='A'+i;
                tempStr+=indexch;
                ui->label_bus_status->setText(tempStr+"写回");

                tempStr="写回";
                addr=_snooping.get_remote_wb_addr();
                column=addr/8*2+1;
                row=addr%8;
                ui->tableWidget_memory->setItem(row,column,new QTableWidgetItem(tempStr));


                tempStr=status_str[_status[i+3*CACHE_NUM]];

                switch(i)
                {
                case 0:

                    ui->tableWidget_cache1->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+3*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache1->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache1->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 1:
                    ui->tableWidget_cache2->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+3*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache2->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache2->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 2:
                    ui->tableWidget_cache3->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+3*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache3->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache3->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 3:
                    ui->tableWidget_cache4->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+3*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache4->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache4->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                default:
                    break;
                }
            }
        }



        _display_step++;
        break;

    case 4:

        tempStr="";

        addr=_snooping.get_remote_wb_addr();
        column=addr/8*2+1;
        row=addr%8;
        ui->tableWidget_memory->setItem(row,column,new QTableWidgetItem(tempStr));

        for(i=0;i<4;i++)
        {
            if(_status[i+4*CACHE_NUM] != NO_ACTION)
            {
                tempStr=status_str[_status[i+4*CACHE_NUM]];
                switch(i)
                {
                case 0:

                    ui->tableWidget_cache1->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+4*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache1->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache1->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 1:
                    ui->tableWidget_cache2->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+4*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache2->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache2->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 2:
                    ui->tableWidget_cache3->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+4*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache3->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache3->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                case 3:
                    ui->tableWidget_cache4->setItem(_cacheAddr,1,new QTableWidgetItem(tempStr));
                    if(_status[i+4*CACHE_NUM]==INVALID)
                    {
                        tempStr1="";
                        ui->tableWidget_cache4->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    else
                    {
                        tempStr1.setNum(_memAddr);
                        ui->tableWidget_cache4->setItem(_cacheAddr,2,new QTableWidgetItem(tempStr1));
                    }
                    break;
                default:
                    break;
                }

            }
        }

        _display_step++;

        break;
    case 5:
        ui->label_bus_status->setText("");
        ui->label_cpu1_status->setText("");
        ui->label_cpu2_status->setText("");
        ui->label_cpu3_status->setText("");
        ui->label_cpu4_status->setText("");
        ui->label_bus_status->setText("");

        // clear all status
        _snooping.clear_status();

        _display_step=0;
        ui->pushButton_go->setVisible(false);
        ui->groupBox_access->setEnabled(true);
        ui->radioButton_by_step->setEnabled(true);
        ui->radioButton_to_end->setEnabled(true);
    default:
        break;

    }
}

void MainWindow::on_pushButton_reset_clicked()
{
    reset();
}
