#include "lab03/point.hpp"

namespace lab03 {

Point2D::Point2D(int x, int y) : x_(x), y_(y) {}

bool Point2D::operator==(const Point2D& other) const {
    return (x_ == other.x_) && (y_ == other.y_);
}
std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << '(' << point.x_ << ", " << point.y_ << ')';
    return os;
}

}  // namespace lab03
