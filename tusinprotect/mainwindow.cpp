#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_configration_clicked()
{
    //调用新窗口
    view=new Config(this);
    view->show();
}

extern QString filepath;
extern QString url;
extern QString sendmsg;

void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->addItem(filepath);
    ui->listWidget->addItem(url);
    ui->listWidget->addItem(sendmsg);
}
