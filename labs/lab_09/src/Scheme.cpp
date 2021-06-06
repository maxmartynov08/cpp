#include "Scheme.hpp"

Scheme::Scheme(int capacity) {
    figures_ = new Figure* [capacity];
}

Scheme::~Scheme() {
    for (std::size_t i = 0; i < size_; ++i)
        delete figures_[i];
    delete [] figures_;
    figures_ = nullptr;
    size_ = 0;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[size_++] = fg;
}

std::size_t Scheme::find_position_by_id(int id) const {
    std::size_t position = 0;
    while (figures_[position]->get_id() != id)
        position++;
    return position;
}

void Scheme::remove_figure(int id) {
    std::size_t position = find_position_by_id(id);
    delete figures_[position];
    size_--;
    for (; position < size_; position++)
        figures_[position] = figures_[position + 1];
}

void Scheme::print_all_figures() {
    for (std::size_t i = 0; i < size_; ++i)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    std::size_t position = find_position_by_id(id);
    figures_[position]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (std::size_t i = 0; i < size_; ++i) {
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    std::size_t position = find_position_by_id(id);
    figures_[position]->move(new_x, new_y);
}
