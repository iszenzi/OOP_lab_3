#include "lab03/point_set.hpp"

#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "lab03/point.hpp"

namespace lab03 {

TEST(PointSetTest, DefaultSetIsEmpty) {
    const Point2DSet set;
    EXPECT_TRUE(set.empty());
    EXPECT_EQ(set.size(), 0);
    EXPECT_EQ(set.capacity(), 0);
    EXPECT_FALSE(set.contains(Point2D()));
    EXPECT_FALSE(set(Point2D()));
}

TEST(PointSetTest, AddStoresPointAndGrowsCapacity) {
    Point2DSet set;
    EXPECT_TRUE(set.add(Point2D(1, 2)));
    EXPECT_TRUE(set.contains(Point2D(1, 2)));
    EXPECT_EQ(set.size(), 1);
    EXPECT_EQ(set.capacity(), 1);
    EXPECT_TRUE(set.add(Point2D(3, 4)));
    EXPECT_TRUE(set.add(Point2D(5, 6)));
    EXPECT_EQ(set.size(), 3);
    EXPECT_EQ(set.capacity(), 4);
}

TEST(PointSetTest_Fail, DuplicateDoesNotChangeSet) {
    Point2DSet set;
    set.add(Point2D(1, 2));
    EXPECT_FALSE(set.add(Point2D(1, 2)));
    EXPECT_EQ(set.size(), 1);
    EXPECT_EQ(set.capacity(), 1);
}

TEST(PointSetTest_Fail, RemoveFromEmptySetReturnsFalse) {
    Point2DSet set;
    EXPECT_FALSE(set.remove(Point2D()));
    EXPECT_TRUE(set.empty());
}

TEST(PointSetTest_Fail, MissingPointDoesNotChangeSet) {
    Point2DSet set;
    set.add(Point2D(1, 2));
    EXPECT_FALSE(set.remove(Point2D(9, 9)));
    EXPECT_EQ(set.size(), 1);
    EXPECT_TRUE(set.contains(Point2D(1, 2)));
}

TEST(PointSetTest, RemovePreservesOrderAndCapacity) {
    Point2DSet set;
    for (int i = 0; i < 5; ++i) {
        set.add(Point2D(i, i));
    }
    const std::size_t capacity = set.capacity();
    EXPECT_TRUE(set.remove(Point2D(0, 0)));
    EXPECT_TRUE(set.remove(Point2D(2, 2)));
    EXPECT_TRUE(set.remove(Point2D(4, 4)));
    std::ostringstream out;
    out << set;
    EXPECT_EQ(out.str(), "{ (1, 1), (3, 3) }");
    EXPECT_EQ(set.size(), 2);
    EXPECT_EQ(set.capacity(), capacity);
}

TEST(PointSetTest, RemoveLastPointAndReuseStorage) {
    Point2DSet set;
    set.add(Point2D(1, 2));
    EXPECT_TRUE(set.remove(Point2D(1, 2)));
    EXPECT_TRUE(set.empty());
    EXPECT_EQ(set.capacity(), 1);
    EXPECT_TRUE(set.add(Point2D(3, 4)));
    EXPECT_TRUE(set.contains(Point2D(3, 4)));
}

TEST(PointSetTest, MembershipOperatorMatchesContains) {
    Point2DSet set;
    set.add(Point2D(1, 2));
    const Point2DSet& view = set;
    EXPECT_TRUE(view(Point2D(1, 2)));
    EXPECT_FALSE(view(Point2D(3, 4)));
    EXPECT_EQ(view(Point2D(1, 2)), view.contains(Point2D(1, 2)));
}

TEST(PointSetTest, CopyConstructorCreatesIndependentStorage) {
    Point2DSet original;
    original.add(Point2D(1, 2));
    Point2DSet copy(original);
    copy.remove(Point2D(1, 2));
    copy.add(Point2D(3, 4));
    EXPECT_TRUE(original.contains(Point2D(1, 2)));
    EXPECT_FALSE(original.contains(Point2D(3, 4)));
}

TEST(PointSetTest, CopyEmptySetWithAndWithoutReservedStorage) {
    Point2DSet original;
    const Point2DSet empty_copy(original);
    EXPECT_TRUE(empty_copy.empty());
    original.add(Point2D());
    original.remove(Point2D());
    Point2DSet copy(original);
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.capacity(), original.capacity());
    copy.add(Point2D(1, 2));
    EXPECT_TRUE(original.empty());
}

TEST(PointSetTest, CopyAssignmentReplacesStorageIndependently) {
    Point2DSet original;
    original.add(Point2D(1, 2));
    Point2DSet target;
    target.add(Point2D(9, 9));
    EXPECT_EQ(&(target = original), &target);
    original.remove(Point2D(1, 2));
    EXPECT_TRUE(target.contains(Point2D(1, 2)));
    EXPECT_FALSE(target.contains(Point2D(9, 9)));
    target = original;
    EXPECT_TRUE(target.empty());
}

TEST(PointSetTest, SelfCopyAssignmentPreservesElements) {
    Point2DSet set;
    set.add(Point2D(1, 2));
    const Point2DSet& alias = set;
    set = alias;
    EXPECT_EQ(set.size(), 1);
    EXPECT_TRUE(set.contains(Point2D(1, 2)));
}

TEST(PointSetTest, MoveConstructorEmptiesSourceAndAllowsReuse) {
    Point2DSet source;
    source.add(Point2D(1, 2));
    const Point2DSet target(std::move(source));
    EXPECT_TRUE(target.contains(Point2D(1, 2)));
    EXPECT_TRUE(source.empty());
    EXPECT_EQ(source.capacity(), 0);
    EXPECT_TRUE(source.add(Point2D(3, 4)));
    EXPECT_FALSE(target.contains(Point2D(3, 4)));
}

TEST(PointSetTest, MoveAssignmentReleasesOldStorageAndEmptiesSource) {
    Point2DSet source;
    source.add(Point2D(1, 2));
    Point2DSet target;
    target.add(Point2D(9, 9));
    EXPECT_EQ(&(target = std::move(source)), &target);
    EXPECT_TRUE(target.contains(Point2D(1, 2)));
    EXPECT_FALSE(target.contains(Point2D(9, 9)));
    EXPECT_TRUE(source.empty());
    EXPECT_EQ(source.capacity(), 0);
    EXPECT_TRUE(source.add(Point2D()));
}

TEST(PointSetTest, SelfMoveAssignmentPreservesElements) {
    Point2DSet set;
    set.add(Point2D(1, 2));
    Point2DSet& alias = set;
    set = std::move(alias);
    EXPECT_EQ(set.size(), 1);
    EXPECT_TRUE(set.contains(Point2D(1, 2)));
}

TEST(PointSetTest, MovingEmptySetsIsValid) {
    Point2DSet source;
    Point2DSet target(std::move(source));
    Point2DSet nonempty;
    nonempty.add(Point2D());
    nonempty = std::move(target);
    EXPECT_TRUE(source.empty());
    EXPECT_TRUE(target.empty());
    EXPECT_TRUE(nonempty.empty());
    EXPECT_EQ(nonempty.capacity(), 0);
}

TEST(PointSetTest, SwapExchangesStatesAndSupportsSelfSwap) {
    Point2DSet first;
    first.add(Point2D(1, 2));
    Point2DSet second;
    first.swap(second);
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.contains(Point2D(1, 2)));
    second.swap(second);
    EXPECT_TRUE(second.contains(Point2D(1, 2)));
}

TEST(PointSetTest, CompoundOperatorsReturnObjectAndSupportChaining) {
    Point2DSet set;
    EXPECT_EQ(&(set += Point2D(1, 2)), &set);
    (set += Point2D(1, 2)) += Point2D(3, 4);
    EXPECT_EQ(set.size(), 2);
    EXPECT_EQ(&(set -= Point2D(9, 9)), &set);
    (set -= Point2D(1, 2)) -= Point2D(3, 4);
    EXPECT_TRUE(set.empty());
}

TEST(PointSetTest, EqualityIgnoresOrderAndCapacity) {
    Point2DSet first;
    Point2DSet second;
    EXPECT_TRUE(first == second);
    first += Point2D(1, 2);
    first += Point2D(3, 4);
    second += Point2D(3, 4);
    second += Point2D(1, 2);
    second += Point2D(9, 9);
    second -= Point2D(9, 9);
    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);
    second -= Point2D(1, 2);
    second += Point2D(8, 8);
    EXPECT_FALSE(first == second);
    EXPECT_TRUE(first != second);
    second -= Point2D(8, 8);
    EXPECT_FALSE(first == second);
}

TEST(PointSetTest, SetOperationsMatchAllSubsetPairs) {
    for (unsigned first_mask = 0; first_mask < 16; ++first_mask) {
        for (unsigned second_mask = 0; second_mask < 16; ++second_mask) {
            Point2DSet first;
            Point2DSet second;
            for (int i = 0; i < 4; ++i) {
                if ((first_mask & (1u << i)) != 0) {
                    first.add(Point2D(i, -i));
                }
            }
            for (int i = 3; i >= 0; --i) {
                if ((second_mask & (1u << i)) != 0) {
                    second.add(Point2D(i, -i));
                }
            }
            const Point2DSet first_copy(first);
            const Point2DSet second_copy(second);
            Point2DSet united = first | second;
            const Point2DSet intersected = first & second;
            const Point2DSet difference = first - second;
            std::size_t union_size = 0;
            std::size_t intersection_size = 0;
            std::size_t difference_size = 0;
            for (int i = 0; i < 4; ++i) {
                const Point2D point(i, -i);
                const bool in_first = (first_mask & (1u << i)) != 0;
                const bool in_second = (second_mask & (1u << i)) != 0;
                EXPECT_EQ(united.contains(point), in_first || in_second);
                EXPECT_EQ(intersected.contains(point), in_first && in_second);
                EXPECT_EQ(difference.contains(point), in_first && !in_second);
                union_size += in_first || in_second;
                intersection_size += in_first && in_second;
                difference_size += in_first && !in_second;
            }
            EXPECT_EQ(united.size(), union_size);
            EXPECT_EQ(intersected.size(), intersection_size);
            EXPECT_EQ(difference.size(), difference_size);
            EXPECT_TRUE(first == first_copy);
            EXPECT_TRUE(second == second_copy);
            united.add(Point2D(9, 9));
            EXPECT_FALSE(first.contains(Point2D(9, 9)));
            EXPECT_FALSE(second.contains(Point2D(9, 9)));
        }
    }
}

TEST(PointSetTest, OperationsWithSelfReturnExpectedSets) {
    Point2DSet set;
    set.add(Point2D(1, 2));
    EXPECT_TRUE((set | set) == set);
    EXPECT_TRUE((set & set) == set);
    EXPECT_TRUE((set - set).empty());
}

TEST(PointSetTest, ThousandInsertionsPreserveUniqueness) {
    Point2DSet set;
    for (int i = 0; i < 1000; ++i) {
        ASSERT_TRUE(set.add(Point2D(i, -i)));
    }
    EXPECT_EQ(set.size(), 1000);
    EXPECT_GE(set.capacity(), set.size());
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(set.contains(Point2D(i, -i)));
        EXPECT_FALSE(set.add(Point2D(i, -i)));
    }
    EXPECT_EQ(set.size(), 1000);
}

TEST(PointSetTest, OutputHandlesEmptyAndSingleElementSets) {
    Point2DSet set;
    std::ostringstream empty_out;
    empty_out << set;
    EXPECT_EQ(empty_out.str(), "{}");
    set.add(Point2D(-1, 2));
    std::ostringstream single_out;
    single_out << set;
    EXPECT_EQ(single_out.str(), "{ (-1, 2) }");
}

TEST(PointSetTest, OutputPreservesUnionOrderAndSupportsChaining) {
    Point2DSet first;
    first += Point2D(1, 2);
    first += Point2D(3, 4);
    Point2DSet second;
    second += Point2D(3, 4);
    second += Point2D(5, 6);
    const Point2DSet united = first | second;
    std::ostringstream out;
    EXPECT_EQ(&(out << united), &out);
    out << '!';
    EXPECT_EQ(out.str(), "{ (1, 2), (3, 4), (5, 6) }!");
}

}  // namespace lab03
