#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    a.setApplicationName("Manager haseł");
    w.show();

    return a.exec();
}
