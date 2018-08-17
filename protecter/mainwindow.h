#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "config.h"
#include "threading.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static QString filepath;
    static QString spyurl;
    static QString sendmsgurl;
    static QString emailurl;
    static int cycletime;

signals:
    void stopcycle();

private slots:
    void on_configBtn_clicked();
    void on_startBtn_clicked();
    void on_stopBtn_clicked();
    void on_clearBtn_clicked();

    void slo_restart();
    void slo_spyreturn(int status);
    void slo_sendreturn(int status);
    void slo_emailreturn(int status);
    void slo_costartBtn();

private:
    Ui::MainWindow *ui;
    Config *config;
    QSystemTrayIcon *trayIcon;
};

#endif // MAINWINDOW_H
