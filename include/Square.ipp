#pragma once


template <scalar T> Square<T>::Square() : points(4, std::shared_ptr<Point<T>>{}) {
    for (size_t i = 0; i < 4; ++i) {
        points[i] = std::make_shared<Point<T>>();
    }
}

template <scalar T> Square<T>::Square(const Square<T> &other) : points(other.points) {}

template <scalar T> Point<T> Square<T>::geomCenter() const {
    double cx = 0.0, cy = 0.0;
    double area = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
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
        return Point<T>{points[0]->x, points[0]->y};
    }
    cx /= (6.0 * area);
    cy /= (6.0 * area);
    return Point<T>{cx, cy};
}

template <scalar T> void Square<T>::print(std::ostream &os) const {
    os << "Square\n";
    for (size_t i = 0; i < points.GetSize(); ++i) {
        os << "Vertex " << i + 1 << ": " << *points[i] << "\n";
    }
}

template <scalar T> void Square<T>::read(std::istream &is) {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        is >> *points[i];
    }
}

template <scalar T> Square<T>::operator double() const {
    double sm = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        sm += points[i]->x * points[(i + 1) % 4]->y - points[(i + 1) % 4]->x * points[i]->y;
    }
    return std::abs(sm) / 2;
}

template <scalar T> Square<T> &Square<T>::operator=(const Square<T> &f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            *points[i] = *f.points[i];
        }
    }
    return *this;
}

template <scalar T> Square<T> &Square<T>::operator=(Square<T> &&f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points[i] = std::move(f.points[i]);
        }
    }
    return *this;
}

template <scalar T> bool Square<T>::operator==(const Square<T> &f) const {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        if (points[i]->x != f.points[i]->x || points[i]->y != f.points[i]->y) {
            return false;
        }
    }
    return true;
}