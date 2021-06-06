#include "Circle.hpp"
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char* label1) : Figure(id, x, y), radius(radius) {
    char* ptr = new char [strlen(label1) + 1];
    std::strcpy(ptr, label1);
    label = ptr;
}

Circle::~Circle() {
    delete [] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int px, int py) const {
    return (x - px) * (x - px) + (y - py) * (y - py) <= radius * radius;
}

void Circle::zoom(int factor) {
    radius *= factor;
}
