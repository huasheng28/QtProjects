#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    EnumWindows(StaticEnumWindowsProc, reinterpret_cast<LPARAM>(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    ui->listWidget->clear();
    EnumWindows(StaticEnumWindowsProc, reinterpret_cast<LPARAM>(this));
}

BOOL MainWindow::StaticEnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    MainWindow *pThis = reinterpret_cast<MainWindow*>(lParam);
    return pThis->EnumWindowsProc(hwnd);
}

BOOL MainWindow::EnumWindowsProc(HWND hwnd)
{
    WCHAR title[255];
    if(GetWindowText(hwnd, title, 255))
        ui->listWidget->addItem(QString::fromWCharArray(title));
        //ui->listWidget->addItem((QString::fromWCharArray(hwnd)));
    return TRUE;
}
