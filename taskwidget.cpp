#include "taskwidget.h"
#include "ui_taskwidget.h"

TaskOnListWidget::TaskOnListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskOnListWidget)
{
    ui->setupUi(this);
    setFixedSize(size());
}

TaskOnListWidget::TaskOnListWidget(const Task &task, QWidget *parent):
    QWidget(parent)
    , ui(new Ui::TaskOnListWidget)
{
    ui->setupUi(this);
    setTaskInfo(task);
    setFixedSize(size());
}

TaskOnListWidget::~TaskOnListWidget()
{
    delete ui;
}

const Task& TaskOnListWidget::getTaskInfo() const
{
    return task;
}

void TaskOnListWidget::setTaskInfo(Task task)
{
    ui->name->setText(task.name);
    ui->date->setText(task.deadline.toString(date_format));
    ui->state->setCheckState(task.state ? Qt::Checked : Qt::Unchecked);
    this->task = task;
}

void TaskOnListWidget::on_pushButton_clicked()
{
    task_creation_win.show();
    task_creation_win.setTask(task);
    connect(
        &task_creation_win,
        &TaskEditionWindow::changed,
        this,
        [this](Task task){
            setTaskInfo(task);
            emit changed(task);
        }
    );
}


void TaskOnListWidget::on_state_checkStateChanged(const Qt::CheckState &state)
{
    task.state = (state == Qt::Checked);
    emit changed(task);
}

