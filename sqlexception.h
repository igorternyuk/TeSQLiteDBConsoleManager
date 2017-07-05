#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include <stdexcept>
#include <exception>
#include <QString>
#include <sstream>

class SQLException: public std::runtime_error
{
public:
    SQLException(const QString &description);
    virtual const char* what() const throw();
private:
    QString description;
};

#endif // SQLEXCEPTION_H
