#include "tasklist.h"

TaskList::TaskList(QWidget *parent)
    : QListWidget{parent}
{
}

void TaskList::removeTaskWidget(QListWidgetItem *item)
{
    emit removed(indexOfItem(item));
    removeItemWidget(item);
    delete item;
}


QListWidgetItem *TaskList::selectedItem() const
{
    QList<QListWidgetItem*> selected_items = selectedItems();
    if(selected_items.size()){
        return selected_items[0];
    }

    return nullptr;
}

void TaskList::showOrHideFilter(Filter::TaskFilterFunctor filter)
{
    for(size_t i = 0; i < count(); ++i){
        QListWidgetItem* item = TaskList::item(i);
        if(item){
            item->setHidden(!filter(getTaskFromListItem(item)));
        }
    }
}
void TaskList::addTaskWidget(Task task)
{
    TaskOnListWidget* task_widget = new TaskOnListWidget(task);
    QListWidgetItem* item = new QListWidgetItem(this);
    task_widget->setFixedWidth(width());
    item->setSizeHint(task_widget->size());
    setItemWidget(item, task_widget);
    connect(task_widget, &TaskOnListWidget::changed, this, [this, item](Task _task){
        emit taskChanged(indexOfItem(item),_task);
    });
    emit added(task);
}

void TaskList::addTasks(QList<Task> *tasks)
{
    QList<Task>& tasks_list = *tasks;

    foreach (const Task& task, tasks_list) {
        TaskOnListWidget* task_widget = new TaskOnListWidget(task);
        QListWidgetItem* item = new QListWidgetItem(this);
        task_widget->setFixedWidth(width());
        item->setSizeHint(task_widget->size());
        connect(task_widget, &TaskOnListWidget::changed, this, [this, item](Task _task){
            emit taskChanged(indexOfItem(item),_task);
        });
        setItemWidget(item, task_widget);
    }
}


void TaskList::setFilter(Filter::TaskFilterFunctor filter)
{
    showOrHideFilter(filter);
}

TaskOnListWidget *TaskList::getTaskWidgetFromListItem(QListWidgetItem *item) const
{
    return dynamic_cast<TaskOnListWidget*>(itemWidget(item));
}


Task TaskList::getTaskFromListItem(QListWidgetItem *item) const
{
    TaskOnListWidget* task_widget = getTaskWidgetFromListItem(item);

    if(task_widget){
        return task_widget->getTaskInfo();
    }

    return {};
}

size_t TaskList::indexOfItem(QListWidgetItem *item) const
{
    return static_cast<size_t>(indexFromItem(item).row() + 1);
}

