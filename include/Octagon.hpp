#pragma once

#include "Figure.hpp"


template <scalar T> class Octagon final : public Figure<T> {
public:
    Octagon();
    Octagon(const Octagon &other);
    Point<T> geomCenter() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    operator double() const override;
    Octagon &operator=(const Octagon &fig);
    Octagon &operator=(Octagon &&fig);
    bool operator==(const Octagon &fig) const;
    ~Octagon() = default;

private:
    std::unique_ptr<Point<T>> pt1, pt2, pt3, pt4, pt5, pt6, pt7, pt8;
};

#include "Octagon.ipp"