#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

class Employee {
public:
    Employee(int32_t type) : _type(type) {};
    virtual ~Employee() {};

    virtual int salary() const = 0;

    friend std::istream& operator >> (std::istream&, Employee&);
    virtual void read_employee(std::istream& in) = 0;

    friend std::ostream& operator<<(std::ostream&, const Employee&);
    virtual void print_employee(std::ostream& out) const = 0;

    friend std::ifstream& operator>>(std::ifstream&, Employee&);
    virtual void read_employee_from_file(std::ifstream& in) = 0;

    friend std::ofstream& operator<<(std::ofstream&, const Employee&);
    virtual void print_employee_to_file(std::ofstream& out) const = 0;

private:
    void read_name(std::ifstream& in);
    void print_name(std::ofstream &out) const;

protected:
    std::string _name;
    int32_t _base_salary;
    const int32_t _type;
};

#endif
