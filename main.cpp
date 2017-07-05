#include <QCoreApplication>

#include <iostream>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "********SQLiteDBConsoleManager********" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    Client c;
    c.menu();
    return a.exec();
}
