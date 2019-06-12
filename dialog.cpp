#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->enter_pwrd->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Password Manager");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(ui->enter_pwrd->text()!="haslo")
    {
        ui->wrong_label->setText("Wrong password!");
    }
    else
    {
        mainwindow = new MainWindow(this);
        this->hide();
        mainwindow->show();
    }
}
