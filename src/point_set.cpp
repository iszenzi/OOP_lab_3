#include "lab03/point_set.hpp"

#include <ostream>
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

bool Point2DSet::contains(const Point2D& point) const {
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] == point) {
            return true;
        }
    }
    return false;
}

bool Point2DSet::add(const Point2D& point) {
    if (contains(point)) {
        return false;
    }

    if (size_ == capacity_) {
        const std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Point2D* new_data = new Point2D[new_capacity];

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    data_[size_] = point;
    ++size_;
    return true;
}

bool Point2DSet::remove(const Point2D& point) {
    std::size_t index = 0;
    while (index < size_ && !(data_[index] == point)) {
        ++index;
    }

    if (index == size_) {
        return false;
    }

    for (; index + 1 < size_; ++index) {
        data_[index] = data_[index + 1];
    }

    --size_;
    return true;
}

bool Point2DSet::operator()(const Point2D& point) const {
    return contains(point);
}

Point2DSet& Point2DSet::operator+=(const Point2D& point) {
    add(point);
    return *this;
}
Point2DSet& Point2DSet::operator-=(const Point2D& point) {
    remove(point);
    return *this;
}

bool Point2DSet::operator==(const Point2DSet& other) const {
    if (size_ == other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            if (other(data_[i])) {
                continue;
            } else {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
bool Point2DSet::operator!=(const Point2DSet& other) const {
    return !(*this == other);
}
Point2DSet Point2DSet::operator|(const Point2DSet& other) const {
    Point2DSet result;
    for (std::size_t i = 0; i < size_; ++i) {
        result.add(data_[i]);
    }
    for (std::size_t i = 0; i < other.size_; ++i) {
        result.add(other.data_[i]);
    }
    return result;
}
Point2DSet Point2DSet::operator&(const Point2DSet& other) const {
    Point2DSet result;
    for (std::size_t i = 0; i < size_; ++i) {
        if (other(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}
Point2DSet Point2DSet::operator-(const Point2DSet& other) const {
    Point2DSet result;
    for (std::size_t i = 0; i < size_; ++i) {
        if (!(other(data_[i]))) {
            result.add(data_[i]);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Point2DSet& a) {
    os << '{';
    for (std::size_t i = 0; i < a.size_; ++i) {
        if (i == 0) {
            os << ' ';
        } else {
            os << ", ";
        }

        os << a.data_[i];
    }
    if (!a.empty()) {
        os << ' ';
    }

    os << '}';
    return os;
}
}  // namespace lab03
