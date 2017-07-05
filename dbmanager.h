#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include "persona.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <QVariant>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "sqlexception.h"
//#include "sql_cmd.h"


class DBManager
{
public:
    explicit DBManager();
    explicit DBManager(const QString &driverName);
    ~DBManager();

    bool insert(const Persona &p);
    bool update(const Persona &p);
    bool remove(int id1, int id2);
    Persona read(int id);
    std::vector<Persona> readAll();
    std::vector<Persona> search(const QString &regExp);
    void connect();
    void closeConnection();
    QString driverName() const;
    QString pathToDBFile() const;
    void readPathToDBFile();

private:
    static struct _sql_cmds{
        const QString SQL_INSERT = "INSERT INTO employee(name,age,salary) VALUES('%1', %2, %3);";
        const QString SQL_UPDATE = "UPDATE employee SET name = '%1', age = %2, salary = %3 WHERE id = %4;";
        const QString SQL_DELETE = "DELETE FROM employee WHERE id >= %1 AND id <= %2;";
        const QString SQL_READ = "SELECT * FROM employee WHERE id = %1;";
        const QString SQL_READ_ALL = "SELECT * FROM employee;";
        const QString SQL_SEARCH = "SELECT * FROM employee WHERE name like '%1%2%3';";
    } cmd;

    static struct sql_table_columns{
        const QString COLUMN_ID = "id";
        const QString COLUMN_NAME = "name";
        const QString COLUMN_AGE = "age";
        const QString COLUMN_SALARY = "salary";
    } cln;

    static struct errors{
        const std::string ERR_SQLITE_DRIVER_NOT_AVAILABLE = "SQLite driver is not available";
        const std::string ERR_INSERT = "Insertion failed";
        const std::string ERR_UPDATE = "Update failed";
        const std::string ERR_DELETE = "Deleting failed";
        const std::string ERR_READ_BY_ID = "Error occured while reading data";
        const std::string ERR_READ_ALL = "Error occured while listing all data";
        const std::string ERR_SEARCH = "Error occured while searching";
        const std::string ERR_DB_FILE_NOT_FOUND = "File not found.Try again, please:";
        const std::string ERR_ITEM_NOT_FOUND = "There is no person with such id";
    } err;

    static const QString DEFAULT_DRIVER_NAME;
    QString m_driverName;
    QString m_pathToDBFile;
    QSqlDatabase m_db;
    bool fileExists(const std::string& name);
};

#endif // DBCONNECTOR_H
