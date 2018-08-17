#include "config.h"
#include "ui_config.h"

#include "mainwindow.h"
#include <QFileDialog>
#include <QDebug>

Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    //数字框属性
    ui->spinBox->setRange(5,100);
    ui->spinBox->setSingleStep(1);
    ui->spinBox->setWrapping(true);

    //赋值
    ui->filepathLine->setText(MainWindow::filepath);
    ui->spyurlLine->setText(MainWindow::spyurl);
    ui->sendmsgLine->setText(MainWindow::sendmsgurl);
    ui->emailLine->setText(MainWindow::emailurl);
    ui->spinBox->setValue(MainWindow::cycletime);
}

Config::~Config()
{
    delete ui;
}

QString MainWindow::filepath;
QString MainWindow::spyurl;
QString MainWindow::sendmsgurl;
QString MainWindow::emailurl;
int MainWindow::cycletime;

void Config::on_chooseBtn_clicked()
{
    //选择监控程序
    QString temp=QFileDialog::getOpenFileName(this,tr("选择程序"),"/",tr("Allfile(*.*);;exefile(*.exe)"));
    ui->filepathLine->setText(temp);
}

void Config::on_setBtn_clicked()
{
    //确定按钮
    MainWindow::filepath=ui->filepathLine->text();
    MainWindow::spyurl=ui->spyurlLine->text();
    MainWindow::sendmsgurl=ui->sendmsgLine->text();
    MainWindow::emailurl=ui->emailLine->text();
    MainWindow::cycletime=ui->spinBox->value();

    QFile file("config.csv");
    if(file.open(QFile::WriteOnly | QIODevice::Truncate))
    {
        QString temp=QString("%1,%2,%3,%4,%5").arg(MainWindow::filepath).arg(MainWindow::spyurl).arg(MainWindow::sendmsgurl).arg(MainWindow::emailurl).arg(QString::number(MainWindow::cycletime));
        QTextStream out(&file);
        out<<temp;
    }
    file.close();

    this->close();
}
