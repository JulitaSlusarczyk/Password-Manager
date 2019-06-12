#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    char losuj();
    void wczytaj();
    void wczytaj2();
    void pytanie();

public slots:
    void closeEvent(QCloseEvent *e);
private slots:
    void on_dodaj_clicked();

    void on_losuj_haslo_clicked();

    void on_usun_clicked();

    void on_usun_wszystko_clicked();

    void on_edytuj_clicked();

    void on_pokaz_haslo_clicked();

    void on_zapisz_clicked();

    void on_wyzej_clicked();

    void on_nizej_clicked();

    void on_lista_hasel_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
