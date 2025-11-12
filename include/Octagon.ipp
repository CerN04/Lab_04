#pragma once


template <scalar T>
Octagon<T>::Octagon()
    : pt1(std::make_unique<Point<T>>()), pt2(std::make_unique<Point<T>>()), pt3(std::make_unique<Point<T>>()),
      pt4(std::make_unique<Point<T>>()), pt5(std::make_unique<Point<T>>()), pt6(std::make_unique<Point<T>>()),
      pt7(std::make_unique<Point<T>>()), pt8(std::make_unique<Point<T>>()) {}

template <scalar T>
Octagon<T>::Octagon(const Octagon<T> &other)
    : pt1(std::make_unique<Point<T>>(*other.pt1)), pt2(std::make_unique<Point<T>>(*other.pt2)),
      pt3(std::make_unique<Point<T>>(*other.pt3)), pt4(std::make_unique<Point<T>>(*other.pt4)),
      pt5(std::make_unique<Point<T>>(*other.pt5)), pt6(std::make_unique<Point<T>>(*other.pt6)),
      pt7(std::make_unique<Point<T>>(*other.pt7)), pt8(std::make_unique<Point<T>>(*other.pt8)) {}

template <scalar T> Point<T> Octagon<T>::geomCenter() const {
    double cx = 0.0, cy = 0.0;
    double area = 0.0;
    const Point<T> *points[8] = {pt1.get(), pt2.get(), pt3.get(), pt4.get(), pt5.get(), pt6.get(), pt7.get(), pt8.get()};
    for (size_t i = 0; i < 8; ++i) {
        double x1 = points[i]->x;
        double y1 = points[i]->y;
        double x2 = points[(i + 1) % 8]->x;
        double y2 = points[(i + 1) % 8]->y;

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

template <scalar T> void Octagon<T>::print(std::ostream &os) const {
    os << "Octagon\n";
    const Point<T> *points[8] = {pt1.get(), pt2.get(), pt3.get(), pt4.get(), pt5.get(), pt6.get(), pt7.get(), pt8.get()};
    for (size_t i = 0; i < 8; ++i) {
        os << "Vertex " << i + 1 << ": " << *points[i] << "\n";
    }
}

template <scalar T> void Octagon<T>::read(std::istream &is) {
    is >> *pt1 >> *pt2 >> *pt3 >> *pt4 >> *pt5 >> *pt6 >> *pt7 >> *pt8;
}

template <scalar T> Octagon<T>::operator double() const {
    double sm = 0.0;
    const Point<T> *points[8] = {pt1.get(), pt2.get(), pt3.get(), pt4.get(), pt5.get(), pt6.get(), pt7.get(), pt8.get()};
    for (size_t i = 0; i < 8; ++i) {
        sm += points[i]->x * points[(i + 1) % 8]->y - points[(i + 1) % 8]->x * points[i]->y;
    }
    return std::abs(sm) / 2;
}

template <scalar T> Octagon<T> &Octagon<T>::operator=(const Octagon<T> &f) {
    if (this != &f) {
        *pt1 = *f.pt1;
        *pt2 = *f.pt2;
        *pt3 = *f.pt3;
        *pt4 = *f.pt4;
        *pt5 = *f.pt5;
        *pt6 = *f.pt6;
        *pt7 = *f.pt7;
        *pt8 = *f.pt8;
    }
    return *this;
}

template <scalar T> Octagon<T> &Octagon<T>::operator=(Octagon<T> &&f) {
    if (this != &f) {
        pt1 = std::move(f.pt1);
        pt2 = std::move(f.pt2);
        pt3 = std::move(f.pt3);
        pt4 = std::move(f.pt4);
        pt5 = std::move(f.pt5);
        pt6 = std::move(f.pt6);
        pt7 = std::move(f.pt7);
        pt4 = std::move(f.pt8);
    }
    return *this;
}

template <scalar T> bool Octagon<T>::operator==(const Octagon<T> &f) const {
    return pt1->x == f.pt1->x && pt1->y == f.pt1->y && pt2->x == f.pt2->x && pt2->y == f.pt2->y && pt3->x == f.pt3->x &&
           pt3->y == f.pt3->y && pt4->x == f.pt4->x && pt4->y == f.pt4->y && pt5->x == f.pt5->x && pt5->y == f.pt5->y &&
           pt6->x == f.pt6->x && pt6->y == f.pt6->y && pt7->x == f.pt7->x && pt7->y == f.pt7->y && pt8->x == f.pt8->x &&
           pt8->y == f.pt8->y;
}