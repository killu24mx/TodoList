#include "mainwindow.h"

#include <QApplication>

#include "tasklist.h"
#include "dbmanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DBManager manager;

    w.setDB(&manager);

    manager.loadDataFromDB();

    return a.exec();
}
