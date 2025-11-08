#pragma once

#include <iostream>
#include <memory>
#include <type_traits>


template <typename T>
concept scalar = std::is_scalar_v<T>;

template <scalar T> struct Point {
    T x;
    T y;
};

template <scalar T> inline std::ostream &operator<<(std::ostream &os, const Point<T> &p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

template <scalar T> inline std::istream &operator>>(std::istream &is, Point<T> &p) { return is >> p.x >> p.y; }

template <scalar T> class Figure {
public:
    Figure() = default;
    virtual Point<T> geomCenter() const = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
    virtual operator double() const = 0;
    virtual ~Figure() = default;
};

template <scalar T> inline std::ostream &operator<<(std::ostream &os, const Figure<T> &fig) {
    fig.print(os);
    return os;
}

template <scalar T> inline std::istream &operator>>(std::istream &is, Figure<T> &fig) {
    fig.read(is);
    return is;
}
