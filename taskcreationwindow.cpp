#include "taskcreationwindow.h"
#include "ui_taskcreationwindow.h"

TaskCreationWindow::TaskCreationWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskCreationWindow)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    setFixedSize(size());
    ui->daedline->setDateTime(QDateTime::currentDateTime());
    setWindowTitle("Создание новой задачи");
}

TaskCreationWindow::~TaskCreationWindow()
{
    delete ui;
}


void TaskCreationWindow::clear()
{
    ui->name_edit->clear();
    ui->description_edit->clear();
    ui->daedline->clear();
}


void TaskCreationWindow::on_cancel_bt_clicked()
{
    clear();
    hide();
    emit cancel();
}


void TaskCreationWindow::on_create_bt_clicked()
{
    Task task{
        ui->name_edit->text(),
        ui->description_edit->toPlainText(),
        ui->daedline->dateTime(),
        false
    };

    hide();
    clear();
    emit created(task);
}

