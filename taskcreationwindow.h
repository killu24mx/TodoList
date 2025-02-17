#ifndef TASKCREATIONWINDOW_H
#define TASKCREATIONWINDOW_H

#include <QWidget>
#include "task.h"

namespace Ui {
class TaskCreationWindow;
}

class TaskCreationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskCreationWindow(QWidget *parent = nullptr);
    ~TaskCreationWindow();

signals:
    void cancel();
    void created(Task task);

public slots:
    void clear();

private slots:
    void on_cancel_bt_clicked();

    void on_create_bt_clicked();

private:
    Ui::TaskCreationWindow *ui;
};

#endif // TASKCREATIONWINDOW_H
