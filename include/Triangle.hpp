#pragma once

#include "Figure.hpp"


template <scalar T> class Triangle final : public Figure<T> {
public:
    Triangle();
    Triangle(const Triangle &other);
    Point<T> geomCenter() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    operator double() const override;
    Triangle &operator=(const Triangle &fig);
    Triangle &operator=(Triangle &&fig);
    bool operator==(const Triangle &fig) const;
    ~Triangle() = default;

private:
    std::unique_ptr<Point<T>> pt1, pt2, pt3;
};

#include "Triangle.ipp"