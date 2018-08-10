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
    //调用配置窗口
    view=new Config(this);
    view->show();
}

extern QString filepath;
extern QString spyurl;
extern QString sendmsgurl;

void MainWindow::on_startBtn_clicked()
{
    //开始按钮
    //QString statuscode=QString::number(get_req_status());
    restartExe();
}

int MainWindow::get_req_status(QString geturl)
{
    // 构造请求
    QNetworkRequest req;
    req.setUrl(QUrl(geturl));
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    // 发送请求
    QNetworkReply *pReply=manager->get(req);
    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager,&QNetworkAccessManager::finished,&eventLoop,&QEventLoop::quit);
    eventLoop.exec();
    // 获取响应信息
    QVariant statusCode= pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    return statusCode.toInt();
}

void MainWindow::restartExe()
{
    //kill
    QProcess process;
    QProcess cmd;
    process.start("wmic process where \"name='tusin.exe'\" get ProcessID, ExecutablePath");
    process.waitForFinished(-1);
    QString stdouts = process.readAllStandardOutput();
    QStringList list = stdouts.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    int i;
    if (list.size()!=0){
        for (i=2;i<list.size();i+=2)
        {
            if (list[i]==filepath)
            {
                QString command=QString("taskkill /pid %1 /f").arg(list[i+1]);
                cmd.start(command);
            }
        }
    }
    //start
    QProcess newProc;
    newProc.startDetached(filepath);
}




