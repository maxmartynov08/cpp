#ifndef LAB_10_DEVELOPER_H
#define LAB_10_DEVELOPER_H

#include "employee.h"


class Developer : public Employee {
public:
    Developer(): Employee(1) {};
    ~Developer() {};

    int salary() const override;

    void read_employee(std::istream& in) override;
    void print_employee(std::ostream& out) const override;

    void read_employee_from_file(std::ifstream& in) override;
    void print_employee_to_file(std::ofstream& out) const override;

private:
    bool _has_bonus;
};

#endif //LAB_10_DEVELOPER_H
