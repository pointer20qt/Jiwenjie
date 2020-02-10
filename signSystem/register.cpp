#include "register.h"
#include "ui_register.h"
#include"login.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);


}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    QString sname=ui->lineEdit->text();
    QString sno=ui->lineEdit_2->text();
    QString cls=ui->lineEdit_3->text();
    QString pwd=ui->lineEdit_4->text();

    QSqlQuery q;

       q.exec(QString("select * from login where login_name='%1' ").arg(sno));
       if(q.size()>0)
       {
           QMessageBox::warning(this,"warn","学号已存在！");
       }
       else if(sno==NULL)
       {
           QMessageBox::warning(this,"warn","学号不能为空！");
       }
       else if(pwd==NULL)
       {
           QMessageBox::warning(this,"warn","密码不能为空！");
       }
       else if(sname==NULL)
       {
           QMessageBox::warning(this,"warn","姓名不能为空！");
       }
       else if(cls==NULL)
       {
           QMessageBox::warning(this,"warn","班级不能为空！");
       }
       else
       {
           QSqlQuery q1;
           qDebug()<<q1.exec(QString("insert into student(sname,sno,class,pwd) values('%1','%2','%3','%4')").arg(sname).arg(sno).arg(cls).arg(pwd));
           QMessageBox::warning(this,"warn","注册成功！");
       }

}

void Register::on_pushButton_2_clicked()
{
    this->close();
}
