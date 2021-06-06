#ifndef LAB_10_EMPLOYEES_ARRAY_H
#define LAB_10_EMPLOYEES_ARRAY_H

#include "employee.h"


class EmployeesArray {
public:
    EmployeesArray() {}
    ~EmployeesArray();

    Employee* create_by_type(int32_t type);

    void add(Employee *e);

    void add_from_file(std::ifstream& in);

    friend std::ostream& operator<<(std::ostream&, const EmployeesArray&);
    friend std::ofstream& operator<<(std::ofstream&, const EmployeesArray&);

private:
    int total_salary() const;
    Employee* read_one_employee_from_file(std::ifstream& in);

private:
    std::vector <Employee*> _employees;
};

#endif //LAB_10_EMPLOYEES_ARRAY_H
