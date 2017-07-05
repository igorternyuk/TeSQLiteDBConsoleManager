#include "persona.h"

Persona::Persona():
    id(0), mName(""), mAge(0), mSalary(0.0)
{}

Persona::Persona(const QString &nombre, int edad, double salario):
    id(0), mName(nombre), mAge(edad), mSalary(salario)
{}

Persona::Persona(int id, const QString &nombre, int edad, double salario):
    id(id), mName(nombre), mAge(edad), mSalary(salario)
{}

Persona::Persona(const Persona &otra):
    id(otra.getId()), mName(otra.getName()), mAge(otra.getAge()),
    mSalary(otra.getSalary())
{}

int Persona::getId() const
{
    return id;
}

void Persona::setId(int value)
{
    id = value;
}

QString Persona::getName() const
{
    return mName;
}

void Persona::setName(const QString &nombre)
{
    mName = nombre;
}

int Persona::getAge() const
{
    return mAge;
}

void Persona::setAge(int edad)
{
    mAge = edad;
}

double Persona::getSalary() const
{
    return mSalary;
}

void Persona::setSalary(double salario)
{
    mSalary = salario;
}

QDataStream& operator<<(QDataStream &ds, const Persona &p)
{
    return ds << p.getId() << p.getName() << p.getAge() << p.getSalary();
}

QDataStream& operator>>(QDataStream &is, Persona &p){
    int id;
    QString nombre;
    int edad;
    double salario;
    is >> id >> nombre >> edad >> salario;
    p.setId(id);
    p.setName(nombre);
    p.setAge(edad);
    p.setSalary(salario);
    return is;
}

std::ostream &operator<<(std::ostream &os, const Persona &p)
{
    os << p.getId() << " " << p.getName().toStdString() << " " << p.getAge() << " " << p.getSalary();
    return os;
}

std::istream &operator>>(std::istream &is, Persona &p)
{
    int id;
    std::string nombre;
    int edad;
    double salario;
    is >> id >> nombre >> edad >> salario;
    p.setId(id);
    p.setName(QString::fromStdString(nombre));
    p.setAge(edad);
    p.setSalary(salario);
    return is;
}
