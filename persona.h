#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include <QDataStream>
#include <iostream>
#include <string>

class Persona
{
public:    
    explicit Persona();
    explicit Persona(const QString &nombre, int edad, double salario);
    explicit Persona(int id, const QString &nombre, int edad, double salario);
    Persona(const Persona &otra);
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &nombre);
    int getAge() const;
    void setAge(int edad);
    double getSalary() const;
    void setSalary(double salario);

private:
    int id;
    QString mName;
    int mAge;
    double mSalary;
};

QDataStream &operator<<(QDataStream &ds, const Persona &p);
QDataStream &operator>>(QDataStream &is, Persona &p);
std::ostream &operator<<(std::ostream &ds, const Persona &p);
std::istream &operator>>(std::istream &is, Persona &p);

#endif // PERSONA_H
