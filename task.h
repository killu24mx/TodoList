#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>
#include <QPair>
#include <functional>

struct Task
{
    QString name;
    QString description;
    QDateTime deadline;
    bool state = false;
};


#endif // TASK_H
