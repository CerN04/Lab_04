#pragma once


template <scalar T> Triangle<T>::Triangle() : points(3, std::shared_ptr<Point<T>>{}) {
    for (size_t i = 0; i < 3; ++i) {
        points[i] = std::make_shared<Point<T>>();
    }
}

template <scalar T> Triangle<T>::Triangle(const Triangle<T> &other) : points(other.points) {}

template <scalar T> Point<T> Triangle<T>::geomCenter() const {
    double sm_x = 0.0, sm_y = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        sm_x += points[i]->x;
        sm_y += points[i]->y;
    }
    return Point<T>{sm_x / 3, sm_y / 3};
}

template <scalar T> void Triangle<T>::print(std::ostream &os) const {
    os << "Triangle\n";
    for (size_t i = 0; i < points.GetSize(); ++i) {
        os << "Vertex " << i + 1 << ": " << *points[i] << "\n";
    }
}

template <scalar T> void Triangle<T>::read(std::istream &is) {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        is >> *points[i];
    }
}

template <scalar T> Triangle<T>::operator double() const {
    return (1.0 / 2.0) *
           std::abs(points[0]->x * (points[1]->y - points[2]->y) + points[1]->x * (points[2]->y - points[0]->y) +
                    points[2]->x * (points[0]->y - points[1]->y));
}

template <scalar T> Triangle<T> &Triangle<T>::operator=(const Triangle<T> &f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            *points[i] = *f.points[i];
        }
    }
    return *this;
}

template <scalar T> Triangle<T> &Triangle<T>::operator=(Triangle<T> &&f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points[i] = std::move(f.points[i]);
        }
    }
    return *this;
}

template <scalar T> bool Triangle<T>::operator==(const Triangle<T> &f) const {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        if (points[i]->x != f.points[i]->x || points[i]->y != f.points[i]->y) {
            return false;
        }
    }
    return true;
}