#include "Rectangle.hpp"
#include <cstdlib>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int px, int py) const {
    return 2 * std::abs(x - px) <= width && 2 * std::abs(y - py) <= height;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}
