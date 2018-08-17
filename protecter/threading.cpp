#include "threading.h"
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

Threading::Threading(QObject *parent) : QThread(parent)
{

}

Threading::~Threading()
{

}

void Threading::run()
{
    canrun=true;
    cou=0;
    while(true)
    {
        int spystatus=get_req_status(MainWindow::spyurl);
        emit sig_spyreturn(spystatus);
        if (spystatus!=200)
        {
            restartExe(MainWindow::filepath);
            emit sig_restart();
            emit sig_sendreturn(get_req_status(MainWindow::sendmsgurl));
            emit sig_emailreturn(get_req_status(MainWindow::emailurl));
            //qDebug()<<"重启完成"<<endl;
        }
        msleep(MainWindow::cycletime*1000);
        QMutexLocker locker(&m_lock);
        if (!canrun)
        {
            emit sig_costartBtn();
            return;
        }
        cou++;
        if (cou>100)
        {
            emit sig_clear();
            cou=0;
        }
        //qDebug()<<"循环完成"<<endl;
    }
}

void Threading::stopthread()
{
    QMutexLocker locker(&m_lock);
    canrun=false;
}

int Threading::get_req_status(QString url)
{
    // 构造请求
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    QNetworkAccessManager *manager=new QNetworkAccessManager();
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

void Threading::restartExe(QString filepath)
{
    //kill
    QProcess process;
    QProcess cmd;
    QString search;
    QString name;
    name=filepath.section("/",-1);
    search=QString("wmic process where \"name='%1'\" get ProcessID, ExecutablePath").arg(name);
    //qDebug()<<search<<endl;
    process.start(search);
    process.waitForFinished(-1);
    QString stdouts = process.readAllStandardOutput();
    QStringList list = stdouts.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    //qDebug()<<list<<endl;
    int i;
    if (list.size()!=0){
        for (i=2;i<list.size();i+=2)
        {
            if (list[i].replace("\\","/")==filepath)
            {
                QString command=QString("taskkill /pid %1 /f").arg(list[i+1]);
                //qDebug()<<command<<endl;
                cmd.start(command);
                cmd.waitForFinished(-1);
            }
        }
    }
    //start
    QProcess newProc;
    newProc.startDetached(filepath);
}
