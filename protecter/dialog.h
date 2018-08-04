#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "config.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_configration_clicked();

private:
    Ui::Dialog *ui;
    Config *view;
};

#endif // DIALOG_H
