#include "mainwindow.h"
#include "tasklist.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("Todo List");

    connect(
        &task_creation_win,
        &TaskCreationWindow::created,
        ui->listWidget,
        &TaskList::addTaskWidget
    );

    connect(
        &filter_win,
        &Filter::aply,
        ui->listWidget,
        &TaskList::setFilter
    );


}

MainWindow::~MainWindow()
{
    filter_win.hide();
    delete ui;
}

void MainWindow::setDB(DBManager *manager)
{
    connect(ui->listWidget, &TaskList::added, manager, &DBManager::insertTask);
    connect(ui->listWidget, &TaskList::removed, manager, &DBManager::removeTask);
    connect(ui->listWidget, &TaskList::taskChanged, manager, &DBManager::changeTask);
    connect(manager, &DBManager::dataLoaded, ui->listWidget, &TaskList::addTasks);

}

void MainWindow::on_add_bt_clicked()
{
    task_creation_win.show();
}


void MainWindow::on_remove_bt_clicked()
{
    QListWidgetItem* item = ui->listWidget->selectedItem();
    if(item){
        ui->listWidget->removeTaskWidget(item);
    }
}


void MainWindow::on_remove_bt_3_clicked()
{
    filter_win.show();
}

