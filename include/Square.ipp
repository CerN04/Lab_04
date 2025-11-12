#pragma once


template <scalar T>
Square<T>::Square()
    : pt1(std::make_unique<Point<T>>()), pt2(std::make_unique<Point<T>>()), pt3(std::make_unique<Point<T>>()),
      pt4(std::make_unique<Point<T>>()) {}

template <scalar T>
Square<T>::Square(const Square<T> &other)
    : pt1(std::make_unique<Point<T>>(*other.pt1)), pt2(std::make_unique<Point<T>>(*other.pt2)),
      pt3(std::make_unique<Point<T>>(*other.pt3)), pt4(std::make_unique<Point<T>>(*other.pt4)) {}

template <scalar T> Point<T> Square<T>::geomCenter() const {
    double cx = 0.0, cy = 0.0;
    double area = 0.0;

    const Point<T> *points[4] = {pt1.get(), pt2.get(), pt3.get(), pt4.get()};

    for (size_t i = 0; i < 4; ++i) {
        double x1 = points[i]->x;
        double y1 = points[i]->y;
        double x2 = points[(i + 1) % 4]->x;
        double y2 = points[(i + 1) % 4]->y;

        double f = (x1 * y2 - x2 * y1);
        area += f;
        cx += (x1 + x2) * f;
        cy += (y1 + y2) * f;
    }
    area /= 2.0;
    if (area == 0.0) {
        return Point<T>{pt1->x, pt1->y};
    }
    cx /= (6.0 * area);
    cy /= (6.0 * area);
    return Point<T>{cx, cy};
}

template <scalar T> void Square<T>::print(std::ostream &os) const {
    os << "Square\n";
    const Point<T> *points[4] = {pt1.get(), pt2.get(), pt3.get(), pt4.get()};
    for (size_t i = 0; i < 4; ++i) {
        os << "Vertex " << i + 1 << ": " << *points[i] << "\n";
    }
}

template <scalar T> void Square<T>::read(std::istream &is) { is >> *pt1 >> *pt2 >> *pt3 >> *pt4; }

template <scalar T> Square<T>::operator double() const {
    double sm = 0.0;
    sm += pt1->x * pt2->y - pt2->x * pt1->y;
    sm += pt2->x * pt3->y - pt3->x * pt2->y;
    sm += pt3->x * pt4->y - pt4->x * pt3->y;
    sm += pt4->x * pt1->y - pt1->x * pt4->y;
    return std::abs(sm) / 2.0;
}

template <scalar T> Square<T> &Square<T>::operator=(const Square<T> &f) {
    if (this != &f) {
        *pt1 = *f.pt1;
        *pt2 = *f.pt2;
        *pt3 = *f.pt3;
        *pt4 = *f.pt4;
    }
    return *this;
}

template <scalar T> Square<T> &Square<T>::operator=(Square<T> &&f) {
    if (this != &f) {
        pt1 = std::move(f.pt1);
        pt2 = std::move(f.pt2);
        pt3 = std::move(f.pt3);
        pt4 = std::move(f.pt4);
    }
    return *this;
}

template <scalar T> bool Square<T>::operator==(const Square<T> &f) const {
    return pt1->x == f.pt1->x && pt1->y == f.pt1->y && pt2->x == f.pt2->x && pt2->y == f.pt2->y && pt3->x == f.pt3->x &&
           pt3->y == f.pt3->y && pt4->x == f.pt4->x && pt4->y == f.pt4->y;
}