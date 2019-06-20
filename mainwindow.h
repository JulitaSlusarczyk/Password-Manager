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
    void on_zapisz_clicked();
    void on_up_button_clicked();
    void on_down_button_clicked();
    void on_edit_button_clicked();
    void on_random_pwrd_clicked();
    void on_show_pwrd_clicked();
    void on_delete_one_clicked();
    void on_delete_all_clicked();
    void on_sites_list_itemSelectionChanged();
    void on_add_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
