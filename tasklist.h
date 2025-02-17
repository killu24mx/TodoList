#ifndef TASKLIST_H
#define TASKLIST_H

#include <QWidget>
#include <QListWidget>
#include <QList>
#include "task.h"
#include "taskwidget.h"
#include "filter.h"
#include "dbmanager.h"

class TaskList : public QListWidget
{
    Q_OBJECT
public:
    explicit TaskList(QWidget *parent = nullptr);

    void removeTaskWidget(QListWidgetItem *item);

    Task getTaskFromListItem(QListWidgetItem* item) const;

    size_t indexOfItem(QListWidgetItem* item) const;

    QListWidgetItem* selectedItem()const;

    void showOrHideFilter(Filter::TaskFilterFunctor filter);

signals:
    void removed(size_t id);
    void added(Task task);
    void taskChanged(size_t id, Task new_info);

public slots:
    void addTaskWidget(Task task);
    void addTasks(QList<Task>* tasks);
    void setFilter(Filter::TaskFilterFunctor filter);

private:
    TaskOnListWidget* getTaskWidgetFromListItem(QListWidgetItem *item) const;

};

#endif // TASKLIST_H
