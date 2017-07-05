#include "dbmanager.h"

DBManager::DBManager()
{
    m_driverName = DEFAULT_DRIVER_NAME;
    readPathToDBFile();
    connect();
}

DBManager::DBManager(const QString &driverName) :
    m_driverName(driverName)
{
    readPathToDBFile();
    connect();
}

DBManager::~DBManager()
{
    if(m_db.isOpen())
    {
        closeConnection();
    }
}

DBManager::_sql_cmds DBManager::cmd;

DBManager::sql_table_columns DBManager::cln;

DBManager::errors DBManager::err;

const QString DBManager::DEFAULT_DRIVER_NAME = "QSQLITE";

void DBManager::connect()
{
    try
    {
        if(!QSqlDatabase::isDriverAvailable(m_driverName))
        {
            throw SQLException("SQLite driver is not available");
        }
        m_db = QSqlDatabase::addDatabase(m_driverName);
        m_db.setDatabaseName(m_pathToDBFile);

        if(!m_db.open())
        {
            throw SQLException(m_db.lastError().text());
        }

    } catch(SQLException &ex) {
        std::cout << ex.what() << std::endl;
        return;
    }
}

bool DBManager::insert(const Persona &p)
{
    QSqlQuery sql(m_db);
    try
    {
        QString query = cmd.SQL_INSERT.arg(p.getName(), QString::number(p.getAge()),
                      QString::number(p.getSalary()));
        std::cout << "SQL = " << query.toStdString() << std::endl;
        if(!sql.exec(query))
        {
            throw SQLException(QString::fromStdString(err.ERR_INSERT));
        }
        return true;
    }
    catch(SQLException &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return false;
}

bool DBManager::update(const Persona &p)
{
    QSqlQuery sql(m_db);
    try
    {
        QString query = cmd.SQL_UPDATE.arg(p.getName(),
                      QString::number(p.getAge()),
                      QString::number(p.getSalary()),
                      QString::number(p.getId()));
        std::cout << "SQL = " << query.toStdString() << std::endl;
        if(!sql.exec(query))
        {
            throw SQLException(QString::fromStdString(err.ERR_UPDATE));
        }
        return true;
    }
    catch(SQLException &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return false;
}

bool DBManager::remove(int id1, int id2)
{
    QSqlQuery sql(m_db);
    try
    {
        QString query = cmd.SQL_DELETE.arg(id1).arg(id2);
        std::cout << "SQL = " << query.toStdString() << std::endl;
        if(!sql.exec(query))
        {
            throw SQLException(QString::fromStdString(err.ERR_DELETE));
        }
        return true;
    }
    catch(SQLException &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return false;
}

Persona DBManager::read(int id)
{
    QSqlQuery sql(m_db);
    try
    {
        if(!sql.exec(cmd.SQL_READ.arg(id)))
        {
            throw SQLException(QString::fromStdString(err.ERR_READ_BY_ID));
        }
        if(sql.next())
        {
            int id = sql.value(cln.COLUMN_ID).toInt();
            QString name = sql.value(cln.COLUMN_NAME).toString();
            int age = sql.value(cln.COLUMN_AGE).toInt();
            double salary = sql.value(cln.COLUMN_SALARY).toDouble();
            return Persona(id, name, age, salary);
        }
        else
        {
            std::cout << err.ERR_ITEM_NOT_FOUND << std::endl;
        }

    }
    catch(SQLException &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return Persona();
}

std::vector<Persona> DBManager::readAll()
{
    QSqlQuery sql(m_db);
    std::vector<Persona> result;
    try
    {
        if(!sql.exec(cmd.SQL_READ_ALL))
        {
            throw SQLException(QString::fromStdString(err.ERR_READ_ALL));
        }
        while(sql.next())
        {
            int id = sql.value(cln.COLUMN_ID).toInt();
            QString name = sql.value(cln.COLUMN_NAME).toString();
            int age = sql.value(cln.COLUMN_AGE).toInt();
            double salary = sql.value(cln.COLUMN_SALARY).toDouble();
            result.emplace_back(id, name, age, salary);
        }
    }
    catch(SQLException &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return result;
}

std::vector<Persona> DBManager::search(const QString &regExp)
{
    QSqlQuery sql(m_db);
    std::vector<Persona> result;
    try
    {
        if(!sql.exec(cmd.SQL_SEARCH.arg(
                     QString::fromStdString("%"),
                     regExp,
                     QString::fromStdString("%"))
        ))
        {
            throw SQLException(QString::fromStdString(err.ERR_SEARCH));
        }
        while(sql.next())
        {
            int id = sql.value(cln.COLUMN_ID).toInt();
            QString name = sql.value(cln.COLUMN_NAME).toString();
            int age = sql.value(cln.COLUMN_AGE).toInt();
            double salary = sql.value(cln.COLUMN_SALARY).toDouble();
            result.emplace_back(id, name, age, salary);
        }
    }
    catch(SQLException &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return result;
}

void DBManager::closeConnection()
{
    m_db.close();
}

QString DBManager::driverName() const
{
    return m_driverName;
}

QString DBManager::pathToDBFile() const
{
    return m_pathToDBFile;
}

void DBManager::readPathToDBFile()
{
    std::string pathToDBFile;
    bool flag = false;
    do
    {
        std::cout << "Type full path to the databse file:" << std::endl;
        std::cin >> pathToDBFile;
        if(fileExists(pathToDBFile)){
            flag = true;
        } else {
            std::cout << err.ERR_DB_FILE_NOT_FOUND << std::endl;
        }
    } while(!flag);
    m_pathToDBFile = QString::fromStdString(pathToDBFile);
}

bool DBManager::fileExists(const std::string &name)
{
    std::ifstream f(name.c_str());
    return f.good();
}


