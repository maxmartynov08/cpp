#include "employees_array.h"
#include "developer.h"
#include "sales_manager.h"
#include "util.h"

EmployeesArray::~EmployeesArray() {
    for (std::size_t i = 0; i < _employees.size(); i++)
        delete _employees[i];
}

Employee* EmployeesArray::create_by_type(int type) {
    switch (type) {
        case 1:
            return new Developer();
        case 2:
            return new SalesManager();
        default:
            return nullptr;
    }
}

void EmployeesArray::add(Employee *e) {
    _employees.push_back(e);
}

std::ostream& operator<<(std::ostream& out, const EmployeesArray& ea) {
    for (std::size_t i = 0; i < ea._employees.size(); i++)
        out << i + 1 << ". " << *(ea._employees[i]);
    out << "== Total salary: " << ea.total_salary() << std::endl << std::endl;
    return out;
}

int EmployeesArray::total_salary() const {
    int sum = 0;
    for (std::size_t i = 0; i < _employees.size(); i++)
        sum += _employees[i]->salary();
    return sum;
}

void EmployeesArray::add_from_file(std::ifstream& in) {
    int32_t amount = read_int_from_file(in);
    for (int32_t i = 0; i < amount; i++)
        add(read_one_employee_from_file(in));
}

Employee* EmployeesArray::read_one_employee_from_file(std::ifstream& in) {
    int32_t type = read_int_from_file(in);
    Employee* e = create_by_type(type);
    assert(e != nullptr);
    in >> *e;
    return e;
}

std::ofstream& operator<<(std::ofstream& out, const EmployeesArray& ea) {
    int32_t sz = ea._employees.size();
    print_int_to_file(out, sz);
    for (std::size_t i = 0; i < ea._employees.size(); i++)
        out << *(ea._employees[i]);
    return out;
}
