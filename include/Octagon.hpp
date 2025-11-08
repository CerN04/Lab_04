#pragma once

#include "Array.hpp"
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
    Array<std::shared_ptr<Point<T>>> points;
};

#include "Octagon.ipp"