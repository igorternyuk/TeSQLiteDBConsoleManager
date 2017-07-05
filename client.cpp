#include "client.h"

Client::Client()
{}

void Client::disconnect()
{
    manager.closeConnection();
}

void Client::menu()
{
    bool mayBeTerminate = false;
    while(!mayBeTerminate)
    {
        std::cout << "******MENU******" << std::endl;
        std::cout << "1 - Insert;" << std::endl;
        std::cout << "2 - Update;" << std::endl;
        std::cout << "3 - Delete;" << std::endl;
        std::cout << "4 - Read by id;" << std::endl;
        std::cout << "5 - Read all;" << std::endl;
        std::cout << "6 - Search by name;" << std::endl;
        std::cout << "7 - Exit;" << std::endl;
        int selector;
        std::cin >> selector;
        int id, id1, id2;
        Persona resP;
        std::string regExp;
        std::vector<Persona> list;
        switch (selector) {
            case 1:
                std::cout << "***insert operation***" << std::endl;
                if(manager.insert(readPersonFromConsole(false)))
                {
                    std::cout << "New person was successfully inserted ton the database" << std::endl;
                }
                break;
            case 2:
                std::cout << "***update operation***" << std::endl;
                resP = readPersonFromConsole(true);
                if(manager.insert(resP))
                {
                    std::cout << "Person with id = " << resP.getId() << " was successfully updated" << std::endl;
                }
                break;
            case 3:
                std::cout << "***deleting operation***" << std::endl;
                std::cout << "Insert min id of the persone list:" << std::endl;
                std::cin >> id1;
                std::cout << "Insert max id of the persone list:" << std::endl;
                std::cin >> id2;
                if(manager.remove(id1, id2)){
                    std::cout << "Persons were successfully deleted" << std::endl;
                }
                break;
            case 4:
                std::cout << "***reading by id***" << std::endl;
                std::cout << "Insert id of the persone to find:" << std::endl;
                std::cin >> id;
                resP = manager.read(id);
                if(id != 0){
                    std::cout << resP << std::endl;
                } else {
                    std::cout << "Such persons were not found" << std::endl;
                }
                break;
            case 5:
                std::cout << "***listing of all persons***" << std::endl;
                list = manager.readAll();
                for(auto &p : list){
                   std::cout << p << std::endl;
                }
                break;
            case 6:
                std::cout << "***Search persons by name***" << std::endl;
                std::cout << "Type the some letters of the name:" << std::endl;
                std::cin >> regExp;
                list = manager.search(QString::fromStdString(regExp));
                for(auto &p : list){
                    std::cout << p << std::endl;
                }
                break;
            case 7:
            default:
                mayBeTerminate = true;
                break;
        }
    }
    std::cout << "Good bye!" << std::endl;
}

Persona Client::readPersonFromConsole(bool withID)
{
    std::string name;
    int age;
    double salary;
    std::cout << "Insert person name: " << std::endl;
    std::cin >> name;

    //Try to read person age

    readNumericFromConsole("Insert person age: ", age, "Invalid input;");

    //Try to read person salary

    readNumericFromConsole("Insert person salary: ", salary, "Invalid input;");

    if(withID){
        int id;
        //Try to read person ID
        readNumericFromConsole("Insert person id: ", id, "Invalid input;");
        return Persona(id, QString::fromStdString(name), age, salary);
    } else {
        return Persona(QString::fromStdString(name), age, salary);
    }
}
