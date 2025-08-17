#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>

template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    Vector() noexcept;
    explicit Vector(size_type count, const T &value = T());
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;
    Vector(const std::initializer_list<T> &il);
    ~Vector();

    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;
    Vector &operator=(const std::initializer_list<T> &il);

    reference at(size_type index);
    const_reference at(size_type index) const;
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    pointer data();
    const_pointer data() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;

    void clear();
    void insert(size_type pos, const T& val);
    void insert(size_type pos, T&& val);
    void insert(size_type pos, size_type count, const T &val);
    template <typename... Args>
    void emplace(size_type pos, Args &&...arg);
    void erase(size_type pos);
    void erase(size_type first, size_type last);
    void push_back(const T &val);
    void push_back(T &&val);
    template <typename... Args>
    void emplace_back(Args &&...arg); 
    void pop_back();
    void resize(size_type count, const T& value = T());
    void swap(Vector &other) noexcept;
private:
    pointer m_data;
    size_type m_capacity;
    size_type m_size;
};

#include "vector.tpp"

#endif