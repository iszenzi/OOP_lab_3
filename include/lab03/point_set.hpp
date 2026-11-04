#pragma once
#include <cstddef>

#include "lab03/point.hpp"

namespace lab03 {

class Point2DSet {
private:
    Point2D* data_;
    std::size_t size_;
    std::size_t capacity_;

public:
    Point2DSet();
    Point2DSet(const Point2DSet& other);
    Point2DSet(Point2DSet&& other) noexcept;

    ~Point2DSet();

    Point2DSet& operator=(const Point2DSet& other);
    Point2DSet& operator=(Point2DSet&& other) noexcept;

    void swap(Point2DSet& other) noexcept;

    std::size_t size() const {
        return size_;
    }
    std::size_t capacity() const {
        return capacity_;
    }

    bool empty() const;
};

}  // namespace lab03
