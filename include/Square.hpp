#pragma once

#include "Figure.hpp"


template <scalar T> class Square final : public Figure<T> {
public:
    Square();
    Square(const Square &other);
    Point<T> geomCenter() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    operator double() const override;
    Square &operator=(const Square &fig);
    Square &operator=(Square &&fig);
    bool operator==(const Square &fig) const;
    ~Square() = default;

private:
    std::unique_ptr<Point<T>> pt1, pt2, pt3, pt4;
};

#include "Square.ipp"