#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include"register.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    Register * r;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();



private:
    Ui::Login *ui;
};

#endif // LOGIN_H
