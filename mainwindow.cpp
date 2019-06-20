//
//  Password Manager
//  by Julita Ślusarczyk
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

QList <QString> sites;
QList <QString> logins;
QList <QString> passwords;
bool edited = false;
char arr[62]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load();
    load2();
    load3();
    if(ui->sites_list->count()<=1)
    {
        ui->up_button->setEnabled(false);
        ui->down_button->setEnabled(false);
    }
    this->setWindowTitle("Password Manager");
    ui->sites_list->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    QFile *f = new QFile("witryny.txt");
    if(!f->open(QIODevice::ReadOnly))
        qFatal("Couldn't open that file");
    QTextStream textStream(f);
    while(!textStream.atEnd())
    {
        QString readfLine = textStream.readLine();
        if(readfLine!="")
        {
            sites << readfLine;
            ui->sites_list->addItem(readfLine);
        }
    }
    f->close();
}
void MainWindow::load2()
{
    QFile *g = new QFile("hasla.txt");
    if(!g->open(QIODevice::ReadOnly))
        qFatal("Couldn't open that file");
    QTextStream textStream2(g);
    while(!textStream2.atEnd())
    {
        QString readgLine = textStream2.readLine();
        if(readgLine!="")
        {
            passwords << readgLine;
        }
    }
    g->close();
}
void MainWindow::load3()
{
    QFile *h = new QFile("logins.txt");
    if(!h->open(QIODevice::ReadOnly))
        qFatal("Couldn't open that file");
    QTextStream textStream3(h);
    while(!textStream3.atEnd())
    {
        QString readhLine = textStream3.readLine();
        if(readhLine!="")
        {
            logins << readhLine;
        }
    }
    h->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(edited)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Cancel);
        QPushButton *noButton = msgBox.addButton(QMessageBox::No);
        QPushButton *yesButton = msgBox.addButton(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setText("Have unsaved changes. Save and exit?");
        msgBox.exec();

        if (msgBox.clickedButton() == yesButton)
        {
            on_zapisz_clicked();
            e->accept();
        }
        else if (msgBox.clickedButton() == noButton)
        {
            e->accept();
        }
        else
        {
            e->ignore();
        }
    }
    else
    {
        e->accept();
    }
}

void MainWindow::on_add_button_clicked()
{
    if(ui->witryna->text()=="" || ui->haslo->text()=="")
    {
        ui->info2_label->setText("Fill all fields!");
    }
    else
    {
        sites << ui->witryna->text();
        ui->sites_list->addItem(ui->witryna->text());
        passwords << ui->haslo->text();
        logins << ui->login_line_edit->text();
        ui->witryna->setText("");
        ui->haslo->setText("");
        ui->login_line_edit->setText("");
        ui->witryna->setFocus();
        edited = true;
        ui->info_label->setText("Added!");
    }
    if(ui->sites_list->count()>1)
    {
        ui->up_button->setEnabled(true);
        ui->down_button->setEnabled(true);
    }
}

void MainWindow::on_random_pwrd_clicked()
{
    QString pwrd;
    int char_pwrd=ui->rand_pwrd_char->currentIndex()+8;
    for (int i; i<char_pwrd; i++)
    {
        pwrd+=rand_pwrd();
    }
    ui->random_pwrd_edit->setText(pwrd);
}

char MainWindow::rand_pwrd()
{
    int l = rand() % 62;
    char z = arr[l];
    return z;
}

void MainWindow::on_delete_one_clicked()
{
    foreach (QListWidgetItem *item, ui->sites_list->selectedItems())
        delete item;
    sites.removeOne(sites[ui->sites_list->currentRow()]);
    logins.removeOne(passwords[ui->sites_list->currentRow()]);
    passwords.removeOne(passwords[ui->sites_list->currentRow()]);
    ui->info_label->setText("Deleted!");
    edited = true;
}

void MainWindow::on_delete_all_clicked()
{
    ui->sites_list->clear();
    sites.clear();
    passwords.clear();
    logins.clear();
    ui->info_label->setText("Deleted!");
    edited = true;
}

void MainWindow::on_edit_button_clicked()
{
    int actual_row_list = ui->sites_list->currentRow();
    if(ui->edit_pwrd->text()!="" && ui->edit_login->text()!="")
    {
        passwords[actual_row_list] = ui->edit_pwrd->text();
        logins[actual_row_list] = ui->edit_login->text();
        ui->info_label->setText("Edited!");
        edited = true;
    }
}

void MainWindow::on_show_pwrd_clicked()
{
    if(ui->show_pwrd->text()=="Show password")
    {
        int actual_row_list = ui->sites_list->currentRow();
        ui->edit_pwrd->setText(passwords[actual_row_list]);
        ui->show_pwrd->setText("Hide password");
    }
    else
    {
        ui->edit_pwrd->setText("");
        ui->show_pwrd->setText("Show password");
    }
}

void MainWindow::on_zapisz_clicked()
{
    QFile *f = new QFile("witryny.txt");
    if(!f->open(QIODevice::WriteOnly))
        qFatal("Couldn't open that file");
    QTextStream textStream(f);
    for(int i=0; i<sites.size();i++)
    {
        textStream<<sites[i];
        textStream<<"\r\n";
    }
    f->close();

    QFile *g = new QFile("hasla.txt");
    if(!g->open(QIODevice::WriteOnly))
        qFatal("Couldn't open that file");
    QTextStream textStream2(g);
    for(int n=0; n<passwords.size();n++)
    {
        textStream2<<passwords[n];
        textStream2<<"\r\n";
    }
    g->close();

    QFile *h = new QFile("logins.txt");
    if(!h->open(QIODevice::WriteOnly))
        qFatal("Couldn't open that file");
    QTextStream textStream3(h);
    for(int n=0; n<logins.size();n++)
    {
        textStream3<<logins[n];
        textStream3<<"\r\n";
    }
    h->close();
    ui->info_label->setText("Saved!");
    edited = false;
}


void MainWindow::on_up_button_clicked()
{
    int rer = ui->sites_list->currentRow();
    if(rer!=0)
    {
        sites.swap(rer,rer-1);
        passwords.swap(rer,rer-1);
        ui->sites_list->clear();
        for(int i; i<sites.size();i++)
        {
            ui->sites_list->addItem(sites[i]);
        }
        ui->sites_list->setCurrentRow(rer-1);
        edited = true;
    }
}

void MainWindow::on_down_button_clicked()
{
    int actual_row_list = ui->sites_list->currentRow();
    if(actual_row_list!=sites.size()-1)
    {
        sites.swap(actual_row_list,actual_row_list+1);
        passwords.swap(actual_row_list,actual_row_list+1);
        ui->sites_list->clear();
        for(int i; i<sites.size();i++)
        {
            ui->sites_list->addItem(sites[i]);
        }
        ui->sites_list->setCurrentRow(actual_row_list+1);
        edited = true;
    }
}

void MainWindow::on_sites_list_itemSelectionChanged()
{
    ui->edit_login->setText(logins[ui->sites_list->currentRow()]);
    ui->edit_pwrd->setText("");
    ui->show_pwrd->setText("Show password");
    ui->info2_label->setText("");
    ui->info_label->setText("");
}
