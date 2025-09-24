
#include <iostream>
#include <algorithm>  //for std::max

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
}

#include "./vector.ipp"
#endif