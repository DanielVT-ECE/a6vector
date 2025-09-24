#include <iostream>
#include <algorithm>  //for std::max
#include <stdexcept>

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace dsa{

template <typename T>
class Vector {

private:
    int cap{0};
    int sz{0};
    T* data{nullptr};

public:
    //empty
    Vector() = default;
    
    //capacity
    int capacity() const;

    //elements stored
    int size() const;
    
    // True is empty
    bool empty() const;
    
    //element at index when vector is const
    const T& operator[](int i) const;
    
    //element at index when vector is non-const
    T& operator[](int i);
    
    // at function for const
    const T& at(int i) const;
    
    // at function for non const
    T& at(int i);
    
    // first element
    const T& front() const;

    // first element
    T& front();
    
    // last element
    const T& back() const;

    // last element
    T& back();
    
    // insert at end
    void push_back(const T& elem);

    // remove from end
    void pop_back();

    // insert at index
    void insert(int i, const T& elem);

    // removes at index
    void erase(int i);

    //capacity >= minimum
    void reserve(int minimum);

    // called by other functions to reduce cap by half 
    // when sz <= cap/4 
    void shrink();
    
    // explicitly reduce the cap to sz and keep at least 1 slot
    void shrink_to_fit();

}; //end class Vector

template <typename T>
int Vector<T>::capacity() const {
    return cap;
}

template <typename T>
int Vector<T>::size() const {
    return sz;
}

template <typename T>
bool Vector<T>::empty() const {
    return (sz == 0);
}

template <typename T>
const T& Vector<T>::operator[](int i) const {
    return data[i];
}

template <typename T>
T& Vector<T>::operator[](int i) {
    return data[i];
}

template <typename T>
const T& Vector<T>::at(int i) const {
    if (i < 0 || i >= sz) {
        throw std::out_of_range("out of bounds error");
    }
    return data[i];
}

template <typename T>
T& Vector<T>::at(int i) {
    if (i < 0 || i >= sz) {
        throw std::out_of_range("out of bounds error");
    }
    return data[i];
}

template <typename T>
const T& Vector<T>::front() const {
    return data[0];
}

template <typename T>
T& Vector<T>::front() {
    return data[0];
}

template <typename T>
const T& Vector<T>::back() const {
    return data[sz - 1];
}

template <typename T>
T& Vector<T>::back() {
    return data[sz - 1];
}

template <typename T>
void Vector<T>::push_back(const T& elem) {
    if (sz == cap) {
        reserve(std::max(1, 2 * cap));
    }
    data[sz] = elem;
    sz = sz + 1;
}

template <typename T>
void Vector<T>::pop_back() {
    // undefined if called on empty vector; follow pseudocode
    sz = sz - 1;
    shrink();
}

template <typename T>
void Vector<T>::insert(int i, const T& elem) {
    if (sz == cap) {
        reserve(std::max(1, 2 * cap));
    }

    for (int k = sz - 1; k >= i; --k) {
        data[k + 1] = data[k];
    }

    data[i] = elem;
    sz = sz + 1;
}

template <typename T>
void Vector<T>::erase(int i) {
    for (int k = i + 1; k <= sz - 1; ++k) {
        data[k - 1] = data[k];
    }

    sz = sz - 1;
    shrink();
}

template <typename T>
void Vector<T>::reserve(int minimum) {
    if (cap < minimum) {
        T* new_array = new T[minimum];

        for (int k = 0; k <= sz - 1; ++k) {
            if (data) new_array[k] = data[k];
            else new_array[k] = T();
        }

        delete[] data;
        data = new_array;
        cap = minimum;
    }
}

template <typename T>
void Vector<T>::shrink() {
    if (cap > 0 && sz <= cap / 4) {
        int new_cap = std::max(1, cap / 2);
        if (new_cap == cap) return;

        T* tmp = new T[new_cap];
        for (int k = 0; k <= sz - 1; ++k) {
            tmp[k] = data[k];
        }
        delete[] data;
        data = tmp;
        cap = new_cap;
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (cap > sz) {
        int new_cap = std::max(1, sz);
        if (new_cap == cap) return;
        T* tmp = new T[new_cap];
        for (int k = 0; k <= sz - 1; ++k) {
            tmp[k] = data[k];
        }
        delete[] data;
        data = tmp;
        cap = new_cap;
    }
}

} // namespace dsa

#endif