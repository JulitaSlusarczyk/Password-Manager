#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

QList <QString> pobrane;
QList <QString> pob_hasla;
bool edytowany = false;
char tab[62]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wczytaj();
    wczytaj2();
    this->setWindowTitle("Manager haseł");
    ui->lista_hasel->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wczytaj()
{
    QFile *f = new QFile("witryny.txt");
    if(!f->open(QIODevice::ReadOnly))
        qFatal("Nie można otworzyć pliku");
    QTextStream textStream(f);
    while(!textStream.atEnd())
    {
        QString h = textStream.readLine();
        if(h!="")
        {
            pobrane << h;
            ui->lista_hasel->addItem(h);
        }
    }
    f->close();
}

void MainWindow::wczytaj2()
{
    QFile *g = new QFile("hasla.txt");
    if(!g->open(QIODevice::ReadOnly))
        qFatal("Nie można otworzyć pliku");
    QTextStream textStream2(g);
    while(!textStream2.atEnd())
    {
        QString hh = textStream2.readLine();
        if(hh!="" || hh!=" ")
        {
            pob_hasla << hh;
        }
    }
    g->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(edytowany)
    {
        QMessageBox msgBox;
        QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);
        QPushButton *noButton = msgBox.addButton(QMessageBox::No);
        QPushButton *yesButton = msgBox.addButton(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setText("Zmiany nie zostały zapisane. Zapisać i kontynuować?");
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
        ui->puste->setText("Wypełnij oba pola witryna i hasło!");
    }
    else
    {
        pobrane << ui->witryna->text();
        ui->lista_hasel->addItem(ui->witryna->text());
        pob_hasla << ui->haslo->text();
        ui->witryna->setText("");
        ui->haslo->setText("");
        ui->witryna->setFocus();
        edytowany = true;
    }
}

void MainWindow::on_losuj_haslo_clicked()
{
    QString haslo;
    for (int i; i<8; i++)
    {
        haslo+=losuj();
    }
    ui->haslo->setText(haslo);
}

char MainWindow::losuj()
{
    int l = rand() % 62;
    char z = tab[l];
    return z;
}

void MainWindow::on_usun_clicked()
{
    foreach (QListWidgetItem *item, ui->lista_hasel->selectedItems())
        delete item;
    int er = ui->lista_hasel->currentRow();
    pobrane.removeOne(pobrane[ui->lista_hasel->currentRow()]);
    pob_hasla.removeOne(pob_hasla[ui->lista_hasel->currentRow()]);
    ui->info->setText("Usunięto!");
    edytowany = true;
}

void MainWindow::on_usun_wszystko_clicked()
{
    ui->lista_hasel->clear();
    pobrane.clear();
    pob_hasla.clear();
    ui->info->setText("Usunięto!");
    edytowany = true;
}

void MainWindow::on_edytuj_clicked()
{
    int ak = ui->lista_hasel->currentRow();
    if(ui->edytuj_haslo->text()!="")
    {
        pob_hasla[ak] = ui->edytuj_haslo->text();
        ui->info->setText("Edytowano!");
        edytowany = true;
    }
}

void MainWindow::on_pokaz_haslo_clicked()
{
    if(ui->pokaz_haslo->text()=="Pokaż hasło")
    {
        int re = ui->lista_hasel->currentRow();
        ui->edytuj_haslo->setText(pob_hasla[re]);
        ui->pokaz_haslo->setText("Ukryj hasło");
    }
    else
    {
        ui->edytuj_haslo->setText("");
        ui->pokaz_haslo->setText("Pokaż hasło");
    }
}

void MainWindow::on_zapisz_clicked()
{
    QFile *f = new QFile("witryny.txt");
    if(!f->open(QIODevice::WriteOnly))
        qFatal("Nie można otworzyć pliku");
    QTextStream textStream(f);
    for(int i=0; i<pobrane.size();i++)
    {
        textStream<<pobrane[i];
        textStream<<"\r\n";
    }
    f->close();

    QFile *g = new QFile("hasla.txt");
    if(!g->open(QIODevice::WriteOnly))
        qFatal("Nie można otworzyć pliku");
    QTextStream textStream2(g);
    for(int n=0; n<pob_hasla.size();n++)
    {
        textStream2<<pob_hasla[n];
        textStream2<<"\r\n";
    }
    g->close();
    ui->info->setText("Zapisano!");
    edytowany = false;
}


void MainWindow::on_wyzej_clicked()
{
    int rer = ui->lista_hasel->currentRow();
    if(rer!=0)
    {
        pobrane.swap(rer,rer-1);
        pob_hasla.swap(rer,rer-1);
        ui->lista_hasel->clear();
        for(int i; i<pobrane.size();i++)
        {
            ui->lista_hasel->addItem(pobrane[i]);
        }
        ui->lista_hasel->setCurrentRow(rer-1);
        edytowany = true;
    }
}

void MainWindow::on_nizej_clicked()
{
    int rer = ui->lista_hasel->currentRow();
    if(rer!=pobrane.size()-1)
    {
        pobrane.swap(rer,rer+1);
        pob_hasla.swap(rer,rer+1);
        ui->lista_hasel->clear();
        for(int i; i<pobrane.size();i++)
        {
            ui->lista_hasel->addItem(pobrane[i]);
        }
        ui->lista_hasel->setCurrentRow(rer+1);
        edytowany = true;
    }
}

void MainWindow::on_lista_hasel_itemSelectionChanged()
{
    ui->edytuj_haslo->setText("");
    ui->pokaz_haslo->setText("Pokaż hasło");
    ui->puste->setText("");
    ui->info->setText("");
}
