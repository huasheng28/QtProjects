#ifndef THREADING_H
#define THREADING_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QMutex>
#include "mainwindow.h"

class Threading : public QThread
{
    Q_OBJECT
public:
    explicit Threading(QObject *parent = 0);
    ~Threading();
    void run();
    void restartExe(QString filepath);
    int get_req_status(QString url);


signals:
    void sig_restart();
    void sig_sendreturn(int status);
    void sig_spyreturn(int status);
    void sig_emailreturn(int status);
    void sig_clear();
    void sig_costartBtn();

public slots:
    void stopthread();

private:
    QMutex m_lock;
    bool canrun;
    int cou;
};

#endif // THREADING_H
