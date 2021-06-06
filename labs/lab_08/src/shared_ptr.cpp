#include "shared_ptr.h"
#include <algorithm>

shared_ptr::Storage::Storage(Matrix *mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    delete data_;
    data_ = nullptr;
    ref_count_ = 0;
}

void shared_ptr::Storage::incr() { ref_count_++; }

void shared_ptr::Storage::decr() { ref_count_--; }

int shared_ptr::Storage::getCounter() const { return ref_count_; }

Matrix* shared_ptr::Storage::getObject() const { return data_; }

shared_ptr::shared_ptr(Matrix *obj) {
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    storage_ = other.storage_;
    storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    std::swap(storage_, other.storage_);
    return *this;
}

void shared_ptr::delete_ptr() {
    if (storage_ == nullptr)
        return;
    storage_->decr();
    if (storage_->getCounter() == 0) {
        delete storage_;
        storage_ = nullptr;
    }
}

shared_ptr::~shared_ptr() {
    delete_ptr();
}

Matrix* shared_ptr::ptr() const { return storage_->getObject(); }

bool shared_ptr::isNull() const { return storage_->getObject() == nullptr; }

void shared_ptr::reset(Matrix *obj) {
    delete_ptr();
    storage_ = new Storage(obj);
}

Matrix& shared_ptr::operator*() const {
    return *ptr();
}

Matrix* shared_ptr::operator->() const {
    return ptr();
}
