#ifndef TASKEDITIONWINDOW_H
#define TASKEDITIONWINDOW_H

#include <QWidget>
#include "task.h"

namespace Ui {
class TaskEditionWindow;
}

class TaskEditionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskEditionWindow(QWidget *parent = nullptr);
    ~TaskEditionWindow();

    void viewTask();

    void setTask(const Task& task);

signals:
    void changed(Task task);

private slots:
    void on_cancel_bt_clicked();

    void on_save_bt_clicked();

private:
    Ui::TaskEditionWindow *ui;

    QString date_format = "dd.MM.yyyy hh:mm";

    Task task;
};

#endif // TASKEDITIONWINDOW_H
