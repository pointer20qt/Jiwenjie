#include "login.h"
#include "ui_login.h"
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QMessageBox>
#include"widget.h"
#include<QDebug>
#include"register.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("20_sign");
    db.setUserName("root");
    db.setPassword("123456");

    if(db.open())
    {
        qDebug()<<"成功打开数据库";
    }
    else
    {
       qDebug()<<"打开数据库失败";
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_2_clicked()
{
    QString sname=ui->lineEdit->text();
    QString pwd=ui->lineEdit_2->text();

    QSqlQuery q;
    q.exec(QString("select * from student where sname='%1'").arg(sname));
    if(q.size()>0)
    {
        q.exec(QString("select * from student where sname='%1' and pwd='%2'").arg(sname).arg(pwd));
        if(q.size()>0)
        {
            Widget *w=new Widget(NULL,sname);

            w->show();
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"warn","密码错误");
        }
    }
    else
    {
        QMessageBox::warning(this,"warn","用户不存在");
    }
}

void Login::on_pushButton_clicked()
{
    r=new Register();
    r->show();
}
