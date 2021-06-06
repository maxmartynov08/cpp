#include "developer.h"
#include "util.h"


void Developer::read_employee(std::istream& in) {
    in >> _has_bonus;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

void Developer::print_employee(std::ostream& out) const {
    out << "Developer" << std::endl;
    Employee::print_employee(out);
    out << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}

void Developer::read_employee_from_file(std::ifstream &in) {
    char bonus[1];
    in.read(bonus, sizeof bonus);
    _has_bonus = bonus[0] != '\0';
}

void Developer::print_employee_to_file(std::ofstream &out) const {
    Employee::print_employee_to_file(out);
    out.write((char*)&_has_bonus, sizeof _has_bonus);
}
