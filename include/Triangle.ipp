#pragma once


template <scalar T>
Triangle<T>::Triangle()
    : pt1(std::make_unique<Point<T>>()), pt2(std::make_unique<Point<T>>()), pt3(std::make_unique<Point<T>>()) {}

template <scalar T>
Triangle<T>::Triangle(const Triangle<T> &other)
    : pt1(std::make_unique<Point<T>>(*other.pt1)), pt2(std::make_unique<Point<T>>(*other.pt2)),
      pt3(std::make_unique<Point<T>>(*other.pt3)) {}

template <scalar T> Point<T> Triangle<T>::geomCenter() const {
    double sm_x = 0.0, sm_y = 0.0;
    const Point<T> *points[3] = {pt1.get(), pt2.get(), pt3.get()};
    for (size_t i = 0; i < 3; ++i) {
        sm_x += points[i]->x;
        sm_y += points[i]->y;
    }
    return Point<T>{sm_x / 3, sm_y / 3};
}

template <scalar T> void Triangle<T>::print(std::ostream &os) const {
    os << "Triangle\n";
    const Point<T> *points[3] = {pt1.get(), pt2.get(), pt3.get()};
    for (size_t i = 0; i < 3; ++i) {
        os << "Vertex " << i + 1 << ": " << *points[i] << "\n";
    }
}

template <scalar T> void Triangle<T>::read(std::istream &is) { is >> *pt1 >> *pt2 >> *pt3; }

template <scalar T> Triangle<T>::operator double() const {
    return (1.0 / 2.0) * std::abs(pt1->x * (pt2->y - pt3->y) + pt2->x * (pt3->y - pt1->y) + pt3->x * (pt1->y - pt2->y));
}

template <scalar T> Triangle<T> &Triangle<T>::operator=(const Triangle<T> &f) {
    if (this != &f) {
        *pt1 = *f.pt1;
        *pt2 = *f.pt2;
        *pt3 = *f.pt3;
    }
    return *this;
}

template <scalar T> Triangle<T> &Triangle<T>::operator=(Triangle<T> &&f) {
    if (this != &f) {
        pt1 = std::move(f.pt1);
        pt2 = std::move(f.pt2);
        pt3 = std::move(f.pt3);
    }
    return *this;
}

template <scalar T> bool Triangle<T>::operator==(const Triangle<T> &f) const {
    return pt1->x == f.pt1->x && pt1->y == f.pt1->y && pt2->x == f.pt2->x && pt2->y == f.pt2->y && pt3->x == f.pt3->x &&
           pt3->y == f.pt3->y;
}