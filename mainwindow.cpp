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
    this->setWindowTitle("Password Manager");
    ui->lista_hasel->setCurrentRow(0);
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
            ui->lista_hasel->addItem(readfLine);
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

void MainWindow::on_dodaj_clicked()
{
    if(ui->witryna->text()=="" || ui->haslo->text()=="")
    {
        ui->info2_label->setText("Fill all fields!");
    }
    else
    {
        sites << ui->witryna->text();
        ui->lista_hasel->addItem(ui->witryna->text());
        passwords << ui->haslo->text();
        ui->witryna->setText("");
        ui->haslo->setText("");
        ui->witryna->setFocus();
        edited = true;
        ui->info_label->setText("Added!");
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
    foreach (QListWidgetItem *item, ui->lista_hasel->selectedItems())
        delete item;
    int er = ui->lista_hasel->currentRow();
    sites.removeOne(sites[ui->lista_hasel->currentRow()]);
    logins.removeOne(passwords[ui->lista_hasel->currentRow()]);
    passwords.removeOne(passwords[ui->lista_hasel->currentRow()]);
    ui->info_label->setText("Deleted!");
    edited = true;
}

void MainWindow::on_delete_all_clicked()
{
    ui->lista_hasel->clear();
    sites.clear();
    passwords.clear();
    ui->info_label->setText("Deleted!");
    edited = true;
}

void MainWindow::on_edit_button_clicked()
{
    int ak = ui->lista_hasel->currentRow();
    if(ui->edit_pwrd->text()!="")
    {
        passwords[ak] = ui->edit_pwrd->text();
        ui->info_label->setText("Edited!");
        edited = true;
    }
}

void MainWindow::on_show_pwrd_clicked()
{
    if(ui->show_pwrd->text()=="Show password")
    {
        int re = ui->lista_hasel->currentRow();
        ui->edit_pwrd->setText(passwords[re]);
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


void MainWindow::on_wyzej_clicked()
{
    int rer = ui->lista_hasel->currentRow();
    if(rer!=0)
    {
        sites.swap(rer,rer-1);
        passwords.swap(rer,rer-1);
        ui->lista_hasel->clear();
        for(int i; i<sites.size();i++)
        {
            ui->lista_hasel->addItem(sites[i]);
        }
        ui->lista_hasel->setCurrentRow(rer-1);
        edited = true;
    }
}

void MainWindow::on_nizej_clicked()
{
    int rer = ui->lista_hasel->currentRow();
    if(rer!=sites.size()-1)
    {
        sites.swap(rer,rer+1);
        passwords.swap(rer,rer+1);
        ui->lista_hasel->clear();
        for(int i; i<sites.size();i++)
        {
            ui->lista_hasel->addItem(sites[i]);
        }
        ui->lista_hasel->setCurrentRow(rer+1);
        edited = true;
    }
}

void MainWindow::on_lista_hasel_itemSelectionChanged()
{
    ui->edit_login->setText(logins[ui->lista_hasel->currentRow()]);
    ui->edit_pwrd->setText("");
    ui->show_pwrd->setText("Show password");
    ui->info2_label->setText("");
    ui->info_label->setText("");
}
