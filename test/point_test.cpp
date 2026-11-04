#include "lab03/point.hpp"

#include <limits>
#include <sstream>

#include <gtest/gtest.h>

namespace lab03 {

TEST(PointTest, DefaultCoordinatesAreZero) {
    const Point2D point;
    EXPECT_EQ(point.x(), 0);
    EXPECT_EQ(point.y(), 0);
}

TEST(PointTest, ConstructorPreservesCoordinates) {
    const Point2D point(-7, 12);
    EXPECT_EQ(point.x(), -7);
    EXPECT_EQ(point.y(), 12);
}

TEST(PointTest, EqualityChecksBothCoordinates) {
    const Point2D point(1, 2);
    EXPECT_TRUE(point == Point2D(1, 2));
    EXPECT_FALSE(point == Point2D(9, 2));
    EXPECT_FALSE(point == Point2D(1, 9));
}

TEST(PointTest, ExtremeIntegerCoordinatesAreSupported) {
    const Point2D point(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    EXPECT_EQ(point.x(), std::numeric_limits<int>::min());
    EXPECT_EQ(point.y(), std::numeric_limits<int>::max());
}

TEST(PointTest, OutputSupportsConstObjectsAndChaining) {
    const Point2D point(-1, 2);
    std::ostringstream out;
    EXPECT_EQ(&(out << point), &out);
    out << Point2D();
    EXPECT_EQ(out.str(), "(-1, 2)(0, 0)");
}

}  // namespace lab03
