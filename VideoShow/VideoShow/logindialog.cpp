#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
#include<QRegExp>

LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //构造里面注册信号中使用的结构
    qRegisterMetaType<Hobby>("Hobby");
    ui->tabWidget->setCurrentIndex(0);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


//清空
void LoginDialog::on_pb_register_clear_clicked()
{
    slot_register_clear();
}

//登录的清空
void LoginDialog::slot_login_clear()
{
    ui->le_name->setText("");
    ui->le_password->setText("");
}

//注册的清空
void LoginDialog::slot_register_clear()
{
    ui->le_register_name->setText("");
    ui->le_register_password->setText("");
    ui->le_register_confirm->setText("");

    ui->cb_all->setChecked(false);
    ui->cb_allnot->setChecked(false);

    ui->cb_dance   ->setChecked(false);
    ui->cb_edu     ->setChecked(false);
    ui->cb_ennegy  ->setChecked(false);
    ui->cb_food    ->setChecked(false);
    ui->cb_funny   ->setChecked(false);
    ui->cb_music   ->setChecked(false);
    ui->cb_outside ->setChecked(false);
    ui->cb_video   ->setChecked(false);
}

//注册
void LoginDialog::on_pb_register_clicked()
{
    QString name = ui->le_register_name->text();
    QString password = ui->le_register_password->text();
    QString confirm = ui->le_register_confirm->text();
    //如果为空的话 提示
    if( name.isEmpty() || name.remove(" ").isEmpty() || password.isEmpty() ||confirm.isEmpty())
    {
        QMessageBox::information( this , "提示" ,"用户名或密码不能为空");
        return;
    }
    //正则表达式 判断 name
    QRegExp reg("[a-zA-Z0-9]{1,10}");

    bool res = reg.exactMatch(name);
    if( !res )
    {
        QMessageBox::information( this , "提示" ,"用户名非法 ,要使用字母或数字");
        return;
    }
    //长度 name <10  password <20长
    if( name.length() >10 ||password.length() > 20 )
    {
        QMessageBox::information( this , "提示" ,"用户名或密码过长");
        return;
    }
    //两次是否一致
    if( password != confirm)
    {
        QMessageBox::information( this , "提示" ,"两次密码不一致");
        return;
    }
    Hobby hy;
    hy.dance   = ui->cb_dance   ->isChecked() ? 50 : 0;
    hy.edu     = ui->cb_edu     ->isChecked() ? 50 : 0;
    hy.ennegy  = ui->cb_ennegy  ->isChecked() ? 50 : 0;
    hy.food    = ui->cb_food    ->isChecked() ? 50 : 0;
    hy.funny   = ui->cb_funny   ->isChecked() ? 50 : 0;
    hy.music   = ui->cb_music   ->isChecked() ? 50 : 0;
    hy.outside = ui->cb_outside ->isChecked() ? 50 : 0;
    hy.video   = ui->cb_video   ->isChecked() ? 50 : 0;
    //发送信号
    emit SIG_registerCommit(name , password ,hy);
}
//登陆
void LoginDialog::on_pb_login_clicked()
{
    QString name = ui->le_name->text();
    QString password = ui->le_password->text();

    //如果为空的话 提示
    if( name.isEmpty() || name.remove(" ").isEmpty() || password.isEmpty())
    {
        QMessageBox::information( this , "提示" ,"用户名或密码不能为空");
        return;
    }
    //正则表达式 判断 name
    QRegExp reg("[a-zA-Z0-9]{1,10}");

    bool res = reg.exactMatch(name);
    if( !res )
    {
        QMessageBox::information( this , "提示" ,"用户名非法 ,要使用字母或数字");
        return;
    }
    //长度 name <10  password <20长
    if( name.length() >10 ||password.length() > 20 )
    {
        QMessageBox::information( this , "提示" ,"用户名或密码过长");
        return;
    }

    //发送信号
    emit SIG_loginCommit(name , password);
}

//点击全选
void LoginDialog::on_cb_all_clicked()
{
    ui->cb_all->setChecked(true);
    ui->cb_allnot->setChecked(false);

    ui->cb_dance   ->setChecked(true);
    ui->cb_edu     ->setChecked(true);
    ui->cb_ennegy  ->setChecked(true);
    ui->cb_food    ->setChecked(true);
    ui->cb_funny   ->setChecked(true);
    ui->cb_music   ->setChecked(true);
    ui->cb_outside ->setChecked(true);
    ui->cb_video   ->setChecked(true);
}

//点击全不选
void LoginDialog::on_cb_allnot_clicked()
{
    ui->cb_all->setChecked(false);
    ui->cb_allnot->setChecked(true);

    ui->cb_dance   ->setChecked(false);
    ui->cb_edu     ->setChecked(false);
    ui->cb_ennegy  ->setChecked(false);
    ui->cb_food    ->setChecked(false);
    ui->cb_funny   ->setChecked(false);
    ui->cb_music   ->setChecked(false);
    ui->cb_outside ->setChecked(false);
    ui->cb_video   ->setChecked(false);
}
