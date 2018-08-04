#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

const static double PI=3.1416;

void Dialog::on_countBtn_clicked()
{
    bool ok;
    QString tempStr;
    QString valueStr=ui->radiusLineEdit->text();//获取输入框值
    int valueInt=valueStr.toInt(&ok);
    double area=valueInt*valueInt*PI;
    ui->areaLabel_2->setText(tempStr.setNum(area));
}

void Dialog::on_radiusLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    QString tempStr;
    QString valueStr=ui->radiusLineEdit->text();//获取输入框值
    int valueInt=valueStr.toInt(&ok);
    double area=valueInt*valueInt*PI;
    ui->areaLabel_3->setText(tempStr.setNum(area));//将数字转成string输出
}
