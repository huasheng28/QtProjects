#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT//宏，作用是启动qt元对象系统的一些特性，必须放在类定义的私有区

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_countBtn_clicked();

    void on_radiusLineEdit_textChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
