#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = 0);
    ~Config();

private slots:
    void on_filepath_btn_clicked();

    void on_pushButton_clicked();

private:
    Ui::Config *ui;
};

#endif // CONFIG_H
