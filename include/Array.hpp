#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>


template <typename T> class Array {
private:
    size_t size = 0;
    std::shared_ptr<T[]> data;
    size_t capacity = 1;

public:
    Array();
    Array(const size_t &n, const T &t = T{});
    Array(const Array &other);
    Array(Array &&other) noexcept;
    ~Array() noexcept;

    void Resize(size_t new_size);
    T &operator[](size_t i);
    const T &operator[](size_t i) const;
    void DeleteItem(size_t index);
    void PushItem(const T &t);
    T Pop();
    size_t GetSize() const;
};

#include "Array.ipp"