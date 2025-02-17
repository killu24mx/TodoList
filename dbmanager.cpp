#include "dbmanager.h"

#include <QTextStream>
DBManager::DBManager(QObject *parent)
    : QObject{parent}
{
    connectToDB();
    createTable();
}

DBManager::~DBManager()
{
    db.close();
}

QString DBManager::lastError() const
{
    return db.lastError().text();
}

bool DBManager::connectToDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_NAME);
    return db.open();

}

bool DBManager::loadDataFromDB()
{
    QSqlQuery query;

    if(!query.exec(QString("SELECT * FROM " + TABLE_NAME))){
        qDebug() << query.lastError();
        return false;
    }

    while(query.next()){
        Task task;
        task.name = query.value(1).toString();
        task.description = query.value(2).toString();
        QString date = query.value(3).toString();
        task.deadline = QDateTime::fromString(date,date_format);
        task.state = static_cast<bool>(query.value(4).toInt());
        loaded_data.append(task);
    }

    emit dataLoaded(&loaded_data);

    return true;
}

bool DBManager::createTable()
{
    QSqlQuery query;
    QString request;


    QTextStream stream(&request);

    stream << "CREATE TABLE IF NOT EXISTS " << TABLE_NAME
           << "("
           << "Id INTEGER PRIMARY KEY, "
           << "name TEXT, "
           << "description TEXT, "
           << "_date TEXT, "
           << "state INTEGER"
           << ")";

    if(!query.exec(request)){
        qDebug() << lastError();
        return false;
    }

    return true;
}

void DBManager::insertTask(Task task)
{
    QSqlQuery query;
    QString request;
    QTextStream stream(&request);

    stream << "INSERT INTO " << TABLE_NAME <<
        " (name, description, _date, state) "
        "VALUES (:name, :description, :_date, :state)";

    query.prepare(request);

    query.bindValue(":name", task.name);
    query.bindValue(":description", task.description);
    query.bindValue(":_date", task.deadline.toString(date_format));
    query.bindValue(":state", static_cast<int>(task.state));

    if(!query.exec()){
        qDebug() << query.lastError() << ": insertTask";
    }
}

void DBManager::removeTask(size_t id)
{
    if(!id)  return;

    QSqlQuery query;
    QString request;
    QTextStream stream(&request);

    stream << "DELETE FROM " << TABLE_NAME << " WHERE Id = " << id;

    if(!query.exec(request)){
        qDebug() << query.lastError() << ": removeTask1";
        return;
    }

    query.clear();
    request.clear();

    stream << "UPDATE " << TABLE_NAME << " SET Id = Id - 1 WHERE Id > " << id;
    qDebug() << request;
    if(!query.exec(request)){
        qDebug() << query.lastError() << ": removeTask2";
        return;
    }
}

void DBManager::changeTask(size_t id, Task task)
{
    QSqlQuery query;

    QString request;
    QTextStream stream(&request);
    stream <<"UPDATE " << TABLE_NAME << " SET "
           << "name = \"" << task.name << "\", "
           << "description = \"" << task.description << "\", "
           << "_date = \"" << task.deadline.toString(date_format) << "\", "
           << "state = " << QString::number(static_cast<int>(task.state)) << " "
           << "WHERE Id = " << QString::number(id);

    if(!query.exec(request)){
        qDebug() << query.lastError().text() << ": change";
    }

}
