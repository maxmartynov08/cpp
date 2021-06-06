#include "employees_array.h"


int main() {
    EmployeesArray employees_array;
    std::string cmd;

    while (true) {
        std::cin >> cmd;
        if (cmd == "add") {
            int32_t type;
            std::cin >> type;
            Employee* e = employees_array.create_by_type(type);
            assert(e);
            std::cin >> *e;
            employees_array.add(e);
        }
        else if (cmd == "list") {
            std::cout << employees_array;
        }
        else if (cmd == "load") {
            std::string path_to_file;
            std::cin >> path_to_file;
            std::ifstream in(path_to_file, std::ifstream::binary);
            assert(in.is_open());

            employees_array.add_from_file(in);
        }
        else if (cmd == "save") {
            std::string path_to_file;
            std::cin >> path_to_file;
            std::ofstream out(path_to_file, std::ofstream::binary);
            assert(out.is_open());

            out << employees_array;
        }
        else
            break;
    }

    return 0;
}

