#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->podaj_haslo->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Manager haseł");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(ui->podaj_haslo->text()!="haslo")
    {
        ui->zle_haslo->setText("Złe hasło");
    }
    else
    {
        mainwindow = new MainWindow(this);
        this->hide();
        mainwindow->show();
    }
}
