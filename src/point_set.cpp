#include "lab03/point_set.hpp"

#include <utility>

namespace lab03 {

Point2DSet::Point2DSet() : data_(nullptr), size_(0), capacity_(0) {}

Point2DSet::Point2DSet(const Point2DSet& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (other.capacity_ != 0) {
        data_ = new Point2D[other.capacity_];

        for (std::size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}
Point2DSet::Point2DSet(Point2DSet&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Point2DSet::~Point2DSet() {
    delete[] data_;
}

Point2DSet& Point2DSet::operator=(const Point2DSet& other) {
    Point2DSet copy = other;
    swap(copy);
    return *this;
}
Point2DSet& Point2DSet::operator=(Point2DSet&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] data_;

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

void Point2DSet::swap(Point2DSet& other) noexcept {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
}

bool Point2DSet::empty() const {
    return size_ == 0;
}
}  // namespace lab03
