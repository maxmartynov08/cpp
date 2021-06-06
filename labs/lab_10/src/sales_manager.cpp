#include "sales_manager.h"
#include "util.h"


int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

void SalesManager::read_employee(std::istream& in) {
    in >> _sold_nm >> _price;
}

void SalesManager::print_employee(std::ostream &out) const {
    out << "Sales Manager" << std::endl;
    Employee::print_employee(out);
    out << "Sold items: " << _sold_nm << std::endl;
    out << "Item price: " << _price << std::endl;
}

void SalesManager::read_employee_from_file(std::ifstream &in) {
    _sold_nm = read_int_from_file(in);
    _price = read_int_from_file(in);
}

void SalesManager::print_employee_to_file(std::ofstream &out) const {
    Employee::print_employee_to_file(out);
    print_int_to_file(out, _sold_nm);
    print_int_to_file(out, _price);
}
