#pragma once


template <scalar T> Octagon<T>::Octagon() : points(8, std::shared_ptr<Point<T>>{}) {
    for (size_t i = 0; i < 8; ++i) {
        points[i] = std::make_shared<Point<T>>();
    }
}

template <scalar T> Octagon<T>::Octagon(const Octagon<T> &other) : points(other.points) {}

template <scalar T> Point<T> Octagon<T>::geomCenter() const {
    double cx = 0.0, cy = 0.0;
    double area = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
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
        return Point<T>{points[0]->x, points[0]->y};
    }
    cx /= (6.0 * area);
    cy /= (6.0 * area);
    return Point<T>{cx, cy};
}

template <scalar T> void Octagon<T>::print(std::ostream &os) const {
    os << "Octagon\n";
    for (size_t i = 0; i < points.GetSize(); ++i) {
        os << "Vertex " << i + 1 << ": " << *points[i] << "\n";
    }
}

template <scalar T> void Octagon<T>::read(std::istream &is) {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        is >> *points[i];
    }
}

template <scalar T> Octagon<T>::operator double() const {
    double sm = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        sm += points[i]->x * points[(i + 1) % 8]->y - points[(i + 1) % 8]->x * points[i]->y;
    }
    return std::abs(sm) / 2;
}

template <scalar T> Octagon<T> &Octagon<T>::operator=(const Octagon<T> &f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            *points[i] = *f.points[i];
        }
    }
    return *this;
}

template <scalar T> Octagon<T> &Octagon<T>::operator=(Octagon<T> &&f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points[i] = std::move(f.points[i]);
        }
    }
    return *this;
}

template <scalar T> bool Octagon<T>::operator==(const Octagon<T> &f) const {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        if (points[i]->x != f.points[i]->x || points[i]->y != f.points[i]->y) {
            return false;
        }
    }
    return true;
}