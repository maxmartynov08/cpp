#include "employee.h"
#include "util.h"
#include <cstring>


std::istream& operator>>(std::istream& in, Employee& e) {
    in >> e._name >> e._base_salary;
    e.read_employee(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Employee &e) {
    e.print_employee(out);
    return out;
}

void Employee::print_employee(std::ostream& out) const {
    out << "Name: " << _name << std::endl;
    out << "Base Salary: " << _base_salary << std::endl;
}

std::ifstream& operator>>(std::ifstream& in, Employee& e) {
    e.read_name(in);
    e._base_salary = read_int_from_file(in);
    e.read_employee_from_file(in);
    return in;
}

void Employee::read_name(std::ifstream& in) {
    char c;
    while (in.read(&c, sizeof c)) {
        if (c == '\0')
            break;
        _name.push_back(c);
    }
}

std::ofstream& operator<<(std::ofstream& out, const Employee& e) {
    e.print_employee_to_file(out);
    return out;
}

void Employee::print_employee_to_file(std::ofstream& out) const {
    print_int_to_file(out, _type);
    print_name(out);
    print_int_to_file(out, _base_salary);
}

void Employee::print_name(std::ofstream &out) const {
    char name[_name.length() + 1];
    strcpy(name, _name.c_str());
    out.write(name, sizeof name);
}
