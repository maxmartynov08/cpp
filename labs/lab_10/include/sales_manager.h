#ifndef LAB_10_SALES_MANAGER_H
#define LAB_10_SALES_MANAGER_H

#include "employee.h"


class SalesManager : public Employee {
public:
    SalesManager(): Employee(2) {};
    ~SalesManager() {};

    int salary() const override;

    void read_employee(std::istream& in) override;
    void print_employee(std::ostream& out) const override;

    void read_employee_from_file(std::ifstream& in) override;
    void print_employee_to_file(std::ofstream& out) const override;

private:
    int32_t _sold_nm, _price;
};


#endif //LAB_10_SALES_MANAGER_H
