#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QList>
#include "task.h"

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();

    QString lastError()const;

    bool loadDataFromDB();

public slots:
    void insertTask(Task task);
    void removeTask(size_t id);
    void changeTask(size_t id, Task new_task);

signals:
    void dataLoaded(QList<Task>*);

private:
    QSqlDatabase db;
    const QString DB_NAME = "Tasks.db";
    const QString TABLE_NAME = "tasks";
    QString date_format = "dd.MM.yyyy hh:mm";
    QList<Task> loaded_data;

    bool createTable();
    bool connectToDB();
};

#endif // DBMANAGER_H
