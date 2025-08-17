#include "vector.hpp"

#include <memory>
#include <stdexcept>

template <typename T>
Vector<T>::Vector() noexcept : m_data{nullptr}, m_capacity{0}, m_size{0} { }

template <typename T>
Vector<T>::Vector(size_type count, const T &value) : Vector{} {
    m_data = static_cast<T *>(operator new(sizeof(T) * count));

    try {
        std::uninitialized_fill_n(m_data, count, value);
        m_size = m_capacity = count;
    }
    catch (...) {
        operator delete[](m_data);
        throw;
    }
}

template <typename T>
Vector<T>::Vector(const Vector &other) : Vector{} {
    m_data = static_cast<T *>(operator new(sizeof(T) * other.m_capacity));

    try {
        std::uninitialized_copy_n(other.m_data, other.m_size, m_data);
        m_capacity = other.m_capacity;
        m_size = other.m_size;
    }
    catch (...) {
        operator delete[](m_data);
        throw;
    }
}

template <typename T>
Vector<T>::Vector(Vector &&other) noexcept : m_data{other.m_data}, m_capacity{other.m_capacity}, m_size{other.m_size} {
    other.m_data = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> &il) {
    m_data = static_cast<T *>(operator new(sizeof(T) * il.size()));

    try {
        std::uninitialized_copy(il.begin(), il.end(), m_data);
        m_capacity = m_size = il.size();
    }
    catch (...) {
        operator delete[](m_data);
        throw;
    }
}

template <typename T>
Vector<T>::~Vector() {
    clear();

    operator delete[](m_data);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (this != &other) {
        Vector<T> tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&other) noexcept {
    if (this != &other) {
        Vector<T> tmp(std::move(other));
        swap(tmp);
    }
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const std::initializer_list<T> &il) {
    Vector<T> tmp(il);
    swap(tmp);
    return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type index) {
    if (index >= m_size) throw std::out_of_range("");
    return m_data[index];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type index) const {
    if (index >= m_size) throw std::out_of_range("");
    return m_data[index];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type index) {
    return m_data[index];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type index) const {
    return m_data[index];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() {
    return m_data[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return m_data[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back() {
    return m_data[m_size - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return m_data[m_size - 1];
}

template <typename T>
typename Vector<T>::pointer Vector<T>::data() {
    return m_data;
}

template <typename T>
typename Vector<T>::const_pointer Vector<T>::data() const noexcept {
    return m_data;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
    return m_size == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return m_size;
}

template <typename T>
void Vector<T>::reserve(typename Vector<T>::size_type new_cap) {
    if (new_cap <= m_capacity) return;

    T *new_data = static_cast<T *>(operator new(new_cap));

    size_type i = 0;
    try {
        for (; i < m_size; ++i) {
            new (&new_data[i]) T(m_data[i]);
        }
    }
    catch (...) {
        for (size_type j = 0; j < i; ++j) {
            new_data[j].~T();
        }
        operator delete[](new_data);
        throw;
    }

    size_type tmp = m_size;
    clear();
    operator delete[](m_data);

    m_data = new_data;
    m_capacity = new_cap;
    m_size = tmp;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return m_capacity;
}

template <typename T>
void Vector<T>::clear() {
    for (size_type i = 0; i < m_size; ++i) {
        m_data[i].~T();
    }
    m_size = 0;
}

template <typename T>
void Vector<T>::insert(size_type pos, const T& val) {
    T *new_data = nullptr;
    size_type new_capacity = m_capacity;

    if (m_size == m_capacity) {
        new_data = static_cast<T *>(operator new(m_capacity * 2));
        new_capacity = m_capacity * 2;
    }
    else {
        new_data = static_cast<T *>(operator new(m_capacity));
    }

    for (size_type i = 0; i < pos; ++i) {
        new (new_data[i]) T(std::move(m_data[i]));
    }

    try {
        new (&new_data[pos]) T(val);
    }
    catch (...) {
        for (size_type i = 0; i < pos; ++i) {
            new (m_data[i]) T(std::move(new_data[i]));
        }
        operator delete[](new_data);
        throw;
    }

    for (size_type i = m_size; i > pos; --i) {
        new (&new_data[i]) T(std::move(m_data[i - 1]));
    }

    operator delete[](m_data);
    m_data = new_data;
    ++m_size;
    m_capacity = new_capacity;
}

template <typename T>
void Vector<T>::insert(size_type pos, T&& val) {
    if (m_size == m_capacity) {
        reserve(m_capacity * 2);
    }

    for (size_type i = m_size; i >= pos; --i) {
        new (&m_data[i]) T(std::move(m_data[i - 1]));
    }
    new (&m_data[pos]) T(std::move(val));

    ++m_size;
} 

//logic error here
template <typename T>
void Vector<T>::insert(size_type pos, size_type count, const T &val) {
    T *new_data = nullptr;
    size_type new_capacity = m_capacity;
    if (m_size + count > m_capacity) {
        new_data = static_cast<T *>(operator new((m_size + count) * 2));
        new_capacity = (m_size + count) * 2;
    }
    else {
        // std::cout << std::endl << "here" << std::endl;
        new_data = static_cast<T *>(operator new(m_capacity));
    }

    for (size_type i = 0; i < pos; ++i) {
        new (&new_data[i]) T(std::move(m_data[i]));
    }

    try {
        std::uninitialized_fill_n(new_data + pos, count, val);
    }
    catch (...) {
        for (size_type i = 0; i < pos; ++i) {
            new (&m_data[i]) T(std::move(new_data[i]));
        }
        operator delete[](new_data);
        throw;
    }

    for (size_type i = m_size + count - 1; i > pos; --i) {
        new (&new_data[i]) T(std::move(m_data[i - count]));
    }

    operator delete[](m_data);
    m_data = new_data;
    m_size += count;
    m_capacity = new_capacity;
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace(size_type pos, Args &&...args) {
    T *new_data = nullptr;
    size_type new_capacity = m_capacity;

    if (m_size == m_capacity) {
        new_data = static_cast<T *>(operator new(m_capacity * 2));
        new_capacity = m_capacity * 2;
    }
    else {
        new_data = static_cast<T *>(operator new(m_capacity));
    }

    for (size_type i = 0; i < pos; ++i) {
        new (new_data[i]) T(std::move(m_data[i]));
    }

    try {
        new (&new_data[pos]) T(std::forward<Args>(args)...);
    }
    catch (...) {
        for (size_type i = 0; i < pos; ++i) {
            new (m_data[i]) T(std::move(new_data[i]));
        }
        operator delete[](new_data);
        throw;
    }

    for (size_type i = m_size; i > pos; --i) {
        new (&new_data[i]) T(std::move(m_data[i - 1]));
    }

    operator delete[](m_data);
    m_data = new_data;
    ++m_size;
    m_capacity = new_capacity;
}

template <typename T>
void Vector<T>::erase(size_type pos) {
    m_data[pos].~T();
    for (size_type i = pos; i < m_size - 1; ++i) {
        new (&m_data[i]) T(std::move(m_data[i + 1]));
    }
    --m_size;
}

template <typename T>
void Vector<T>::erase(size_type first, size_type last) {
    for (size_type i = first; i < last; ++i) {
        m_data[i].~T();
    }
    for (size_type i = first; i < m_size - last + first; ++i) {
        new (&m_data[i]) T(std::move(m_data[i + last - first]));
    }
    m_size -= last - first;
}   

template <typename T>
void Vector<T>::push_back(const T &val) {
    if (m_size == m_capacity) {
        reserve(m_capacity * 2);
    }
    new (&m_data[m_size]) T(val);
    ++m_size;
}

template <typename T>
void Vector<T>::push_back(T &&val) {
    if (m_size == m_capacity) {
        reserve(m_capacity * 2);
    }
    new (&m_data[m_size]) T(std::move(val));
    ++m_size;
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args &&...args) {
    if (m_size == m_capacity) {
        reserve(m_capacity * 2);
    }
    new (&m_data[m_size]) T(std::forward<Args>(args)...);
    ++m_size;
} 

template <typename T>
void Vector<T>::pop_back() {
    m_data[m_size - 1].~T();
    --m_size;
}

template <typename T>
void Vector<T>::resize(size_type count, const T& value) {
    if (count < m_size) {
        for (size_type i = count; i < m_size; ++i) {
            m_data[i].~T();
        }
    }
    else if (count > m_size) {
        if (count > m_capacity) {
            reserve(count);
        }
        std::uninitialized_fill_n(m_data + m_size, count - m_size, value);
    }
    m_size = count;
}

template <typename T>
void Vector<T>::swap(Vector &other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_size, other.m_size);
}
