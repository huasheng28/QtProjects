#include "config.h"
#include "ui_config.h"
#include <QFileDialog>
#include <QString>

QString filepath;
QString spyurl;
QString sendmsgurl;

Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);
}

Config::~Config()
{
    delete ui;
}

void Config::on_filepath_btn_clicked()
{
    //文件选择框
    filepath=QFileDialog::getOpenFileName(this,tr("选择程序"),"/",tr("Allfile(*.*);;exefile(*.exe)"));
    ui->lineEdit_filepath->setText(filepath);
}

void Config::on_pushButton_clicked()
{
    spyurl=ui->lineEdit_url->text();
    sendmsgurl=ui->lineEdit_sendmsg->text();
    this->close();
}
