#ifndef SQL_CMD_H
#define SQL_CMD_H

#include <QString>

namespace SQL_CMD {
    const QString SQL_INSERT = "INSERT INTO employee(name,age,salary) VALUES('%1', %2, %3);";
    const QString SQL_UPDATE = "UPDATE employee SET name = '%1', age = %2, salary = %3 WHERE id = %4;";
    const QString SQL_DELETE = "DELETE FROM employee WHERE id >= %1 AND id <= %2;";
    const QString SQL_READ = "SELECT * FROM employee WHERE id = %1;";
    const QString SQL_READ_ALL = "SELECT * FROM employee;";
    const QString SQL_SEARCH = "SELECT * FROM employee WHERE name like '%1%2%3';";
}

#endif // SQL_CMD_H
