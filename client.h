#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <limits>

#include "dbmanager.h"
#include "persona.h"

#include <stdexcept>

class Client
{
public:
    explicit Client();
    void menu();
    void disconnect();
private:
    DBManager manager;

    Persona readPersonFromConsole(bool withID);
     template<class T>
    void readNumericFromConsole(const std::string &msg, T &val, const std::string &err_msg);
};

template<class T>
void Client::readNumericFromConsole(const std::string &msg, T &val,
                                    const std::string &err_msg)
{
    while(std::cout << msg << std::endl &&
          !(std::cin >> val))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << err_msg << std::endl;
    }
}

#endif // CLIENT_H
