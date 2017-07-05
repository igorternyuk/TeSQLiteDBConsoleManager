#include "sqlexception.h"

SQLException::SQLException(const QString &description) :
    std::runtime_error(description.toStdString().c_str()),
    description(description)
{}

const char *SQLException::what() const throw()
{
    std::ostringstream oss;
    oss << "Error: " << description.toStdString() << std::endl;
    return oss.str().c_str();
}
