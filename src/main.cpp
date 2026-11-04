#include <iostream>
#include <new>
#include <utility>

#include "lab03/point.hpp"
#include "lab03/point_set.hpp"

int main() {
    try {
        lab03::Point2DSet first;
        first += lab03::Point2D(0, 0);
        first += lab03::Point2D(1, 2);

        lab03::Point2DSet second;
        second += lab03::Point2D(1, 2);
        second += lab03::Point2D(3, 4);

        std::cout << "Лабораторная работа 3. Вариант 1\n" << std::boolalpha;
        std::cout << "A = " << first << "\nB = " << second << '\n';
        std::cout << "A | B = " << (first | second) << '\n';
        std::cout << "A & B = " << (first & second) << '\n';
        std::cout << "A - B = " << (first - second) << '\n';
        std::cout << "В A есть (1, 2): " << first(lab03::Point2D(1, 2)) << '\n';
        std::cout << "Добавление дубликата изменило A: " << first.add(lab03::Point2D(1, 2)) << '\n';
        std::cout << "A == B: " << (first == second) << '\n';
        std::cout << "Размер A: " << first.size() << ", вместимость: " << first.capacity() << '\n';

        lab03::Point2DSet copy(first);
        copy -= lab03::Point2D(0, 0);
        std::cout << "Копия после удаления (0, 0): " << copy << '\n';
        std::cout << "Исходное A: " << first << '\n';

        const lab03::Point2DSet moved(std::move(copy));
        std::cout << "После перемещения: " << moved << '\n';
        std::cout << "Источник после перемещения: " << copy << ", пуст: " << copy.empty() << '\n';
    } catch (const std::bad_alloc&) {
        std::cerr << "Не удалось выделить память\n";
        return 1;
    }
    return 0;
}
