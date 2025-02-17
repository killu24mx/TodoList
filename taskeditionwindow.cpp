#include "taskeditionwindow.h"
#include "ui_taskeditionwindow.h"

TaskEditionWindow::TaskEditionWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskEditionWindow)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    setFixedSize(size());
    setWindowTitle("Изменение задачи");
}

TaskEditionWindow::~TaskEditionWindow()
{
    delete ui;
}

void TaskEditionWindow::setTask(const Task &task)
{
    ui->name_edit->setText(task.name);
    ui->description_edit->setText(task.description);
    ui->daedline->setDateTime(task.deadline);

    this->task = task;
}

void TaskEditionWindow::on_cancel_bt_clicked()
{
    hide();
}


void TaskEditionWindow::on_save_bt_clicked()
{
    task.name = ui->name_edit->text();
    task.description = ui->description_edit->toPlainText();
    task.deadline = ui->daedline->dateTime();
    emit changed(task);
    hide();
}

