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
    char rand_pwrd();
    void load();
    void load2();
    void load3();

public slots:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_dodaj_clicked();
    void on_zapisz_clicked();
    void on_wyzej_clicked();
    void on_nizej_clicked();
    void on_lista_hasel_itemSelectionChanged();
    void on_edit_button_clicked();
    void on_random_pwrd_clicked();
    void on_show_pwrd_clicked();
    void on_delete_one_clicked();
    void on_delete_all_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
