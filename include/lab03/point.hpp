#pragma once
#include <iosfwd>
namespace lab03 {

class Point2D {
private:
    int x_;
    int y_;

public:
    Point2D(int x = 0, int y = 0);
    int x() const {
        return x_;
    }
    int y() const {
        return y_;
    }
    bool operator==(const Point2D& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Point2D& point);
};

}  // namespace lab03
