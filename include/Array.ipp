#pragma once


template <typename T> Array<T>::Array() : size(0), capacity(1), data(new T[1], deleter) {};

template <typename T> Array<T>::Array(const size_t &n, const T &t) : size(n), data(new T[n], deleter), capacity(n) {
    for (size_t i = 0; i < n; ++i) {
        data[i] = t;
    }
};

template <typename T>
Array<T>::Array(const Array<T> &other)
    : size(other.size), data(new T[other.capacity], deleter), capacity(other.capacity) {
    for (size_t i = 0; i < other.size; ++i) {
        data[i] = other.data[i];
    }
};

template <typename T>
Array<T>::Array(Array<T> &&other) noexcept : size(other.size), capacity(other.capacity), data(std::move(other.data)) {
    other.size = 0;
    other.capacity = 0;
};

template <typename T> Array<T>::~Array() noexcept {
    size = 0;
    capacity = 0;
};

template <typename T> void Array<T>::Resize(size_t new_size) {
    if (new_size == size) {
        return;
    }
    if (new_size > capacity) {
        size_t new_capacity = std::max(new_size, capacity * 2);
        std::shared_ptr<T[]> new_data(new T[new_capacity], deleter);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = new_capacity;
    }
};

template <typename T> T &Array<T>::operator[](size_t i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
};

template <typename T> const T &Array<T>::operator[](size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
};

template <typename T> void Array<T>::DeleteItem(size_t ind) {
    if (ind >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = ind; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    size--;
};

template <typename T> void Array<T>::PushItem(const T &t) {
    if (size >= capacity) {
        Resize(capacity * 2);
    }
    data[size++] = t;
};

template <typename T> T Array<T>::Pop() {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return std::move(data[--size]);
};

template <typename T> size_t Array<T>::GetSize() const { return size; };
