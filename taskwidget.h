#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include "task.h"
#include "taskeditionwindow.h"

namespace Ui {
class TaskOnListWidget;
}

class TaskOnListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskOnListWidget(QWidget *parent = nullptr);
    TaskOnListWidget(const Task& task, QWidget *parent = nullptr);
    ~TaskOnListWidget();

    const Task& getTaskInfo()const;

signals:
    void changed(Task task);

private slots:
    void on_pushButton_clicked();
    void setTaskInfo(Task task);
    void on_state_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::TaskOnListWidget *ui;
    Task task;
    QString date_format = "dd.MM.yyyy hh:mm";
    TaskEditionWindow task_creation_win;
};

#endif // TASKWIDGET_H
