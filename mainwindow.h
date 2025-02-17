#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <functional>

#include "taskcreationwindow.h"
#include "taskwidget.h"
#include "tasklist.h"
#include "filter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDB(DBManager* manager);

private slots:
    void on_add_bt_clicked();
    void on_remove_bt_clicked();

    void on_remove_bt_3_clicked();

private:
    Ui::MainWindow *ui;
    TaskCreationWindow task_creation_win;
    Filter filter_win;

};
#endif // MAINWINDOW_H
