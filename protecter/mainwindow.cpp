#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIcon icon = QIcon("icon.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("守护进程程序"));
    QString title=tr("守护进程程序");
    QString text=tr("守护进程程序");
    trayIcon->show();
    trayIcon->showMessage(title,text,QSystemTrayIcon::Information,5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_configBtn_clicked()
{
    //读取配置文件
    filepath="";
    spyurl="";
    sendmsgurl="";
    emailurl="";
    cycletime=5;
    QFile file("config.csv");
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream* readfile=new QTextStream(&file);
        QString temp=readfile->readAll();
        QStringList templist=temp.split(",");
        if (temp!="")
        {
            if(templist.size()>4)
            {
                filepath=templist[0];
                spyurl=templist[1];
                sendmsgurl=templist[2];
                emailurl=templist[3];
                cycletime=templist[4].toInt();
            }
        }
    }
    file.close();
    //开启配置窗口
    config=new Config(this);
    config->show();
}

void MainWindow::on_startBtn_clicked()
{
    //开始按钮
    Threading* Sthread=new Threading(NULL);
    //结束按钮连接
    connect(this,SIGNAL(stopcycle()),Sthread,SLOT(stopthread()));
    //重启通知连接
    connect(Sthread,SIGNAL(sig_restart()),this,SLOT(slo_restart()));
    //监视接口返回连接
    connect(Sthread,SIGNAL(sig_spyreturn(int)),this,SLOT(slo_spyreturn(int)));
    //发送短信返回连接
    connect(Sthread,SIGNAL(sig_sendreturn(int)),this,SLOT(slo_sendreturn(int)));
    //发送邮件返回连接
    connect(Sthread,SIGNAL(sig_emailreturn(int)),this,SLOT(slo_emailreturn(int)));
    //定时清空列表
    connect(Sthread,SIGNAL(sig_clear()),this,SLOT(on_clearBtn_clicked()));
    //恢复开始按钮
    connect(Sthread,SIGNAL(sig_costartBtn()),this,SLOT(slo_costartBtn()));

    Sthread->start();
    ui->startBtn->setEnabled(false);
}

void MainWindow::on_stopBtn_clicked()
{
    //结束按钮
    emit stopcycle();
    ui->stopBtn->setEnabled(false);
}

void MainWindow::on_clearBtn_clicked()
{
    //清空按钮
    ui->listWidget->clear();
}

void MainWindow::slo_restart()
{
    //重启通知
    int i=QDateTime::currentDateTime().toTime_t();
    QString j=QDateTime::fromTime_t(i).toString("yyyy-MM-dd hh:mm:ss");
    QString k=QString("%1 重启完成").arg(j);
    ui->listWidget->addItem(k);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void MainWindow::slo_spyreturn(int status)
{
    int i=QDateTime::currentDateTime().toTime_t();
    QString j=QDateTime::fromTime_t(i).toString("yyyy-MM-dd hh:mm:ss");
    QString k=QString("%1 监视地址返回：%2").arg(j).arg(QString::number(status));
    ui->listWidget->addItem(k);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void MainWindow::slo_sendreturn(int status)
{
    int i=QDateTime::currentDateTime().toTime_t();
    QString j=QDateTime::fromTime_t(i).toString("yyyy-MM-dd hh:mm:ss");
    QString k=QString("%1 短信通知地址返回：%2").arg(j).arg(QString::number(status));
    ui->listWidget->addItem(k);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void MainWindow::slo_emailreturn(int status)
{
    int i=QDateTime::currentDateTime().toTime_t();
    QString j=QDateTime::fromTime_t(i).toString("yyyy-MM-dd hh:mm:ss");
    QString k=QString("%1 邮件通知地址返回：%2").arg(j).arg(QString::number(status));
    ui->listWidget->addItem(k);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void MainWindow::slo_costartBtn()
{
    ui->startBtn->setEnabled(true);
    ui->stopBtn->setEnabled(true);
}
