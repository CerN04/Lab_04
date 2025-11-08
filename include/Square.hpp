#pragma once

#include "Array.hpp"
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
    Array<std::shared_ptr<Point<T>>> points;
};

#include "Square.ipp"