#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Windows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static BOOL CALLBACK StaticEnumWindowsProc(HWND hwnd, LPARAM lParam);
    BOOL EnumWindowsProc(HWND hwnd);

private slots:
    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
