#ifndef LIB_HEAP_HEAP_H
#define LIB_HEAP_HEAP_H

#include <string>
#include <iostream>
#include "..\lib_tvector\tvector.h"

template<typename T>
class Heap {
    TVector<T> heap;

    void sift_down(size_t i);
    void sift_up(size_t i);
public:
    Heap() = default;
    Heap(const TVector<T>& arr);

    size_t parent(size_t i) const noexcept;
    size_t left_child(size_t i) const noexcept;
    size_t right_child(size_t i) const noexcept;

    size_t size() const noexcept;
    bool is_empty() const noexcept;

    const TVector<T>& get_heap() const;

    void insert(const T& value);
    T extract_min();
    const T& get_min() const;
    void increase_key(size_t i, const T& new_val);
    void build_heap(const TVector<T>& arr);
    void print_heap();
};

template<typename T>
Heap<T>::Heap(const TVector<T>& arr) {
    build_heap(arr);
}

template<typename T>
size_t Heap<T>::parent(size_t i) const noexcept {
    //return (i - (1 + !i % 2) / 2);
    return (i - 1) / 2;
}

template<typename T>
size_t Heap<T>::left_child(size_t i) const noexcept {
    return 2 * i + 1;
}

template<typename T>
size_t Heap<T>::right_child(size_t i) const noexcept {
    return 2 * i + 2;
}

template<typename T>
size_t Heap<T>::size() const noexcept {
    return heap.size();
}

template<typename T>
bool Heap<T>::is_empty() const noexcept {
    return heap.size() == 0;
}

template<typename T>
const TVector<T>& Heap<T>::get_heap() const { return heap; }

template<typename T>
void Heap<T>::sift_down(size_t i) {
    size_t smallest = i;
    size_t left = left_child(i);
    size_t right = right_child(i);
    int size = heap.size();

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < heap.size() && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(heap, i, smallest);
        sift_down(smallest);
    }
}

template<typename T>
void Heap<T>::sift_up(size_t i) {
    while (i > 0 && heap[parent(i)] > heap[i]) {
        swap(heap, i, parent(i));
        i = parent(i);
    }
}

template<typename T>
void Heap<T>::insert(const T& value) {
    heap.push_back_elem(value);
    sift_up(heap.size() - 1);
}

template<typename T>
T Heap<T>::extract_min() {
    if (heap.is_empty()) { throw std::runtime_error("Heap::extract_min: heap is empty!"); }

    T root = heap[0];
    heap[0] = heap.back();
    heap.pop_back_elem();

    if (heap.size() > 0) { sift_down(0); }

    return root;
}

template<typename T>
const T& Heap<T>::get_min() const {
    if (heap.is_empty()) { throw std::runtime_error("Heap::extract_min: heap is empty!"); }
    return heap[0];
}

template<typename T>
void Heap<T>::build_heap(const TVector<T>& arr) {
    heap = arr;

    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        sift_down(i);
    }
}

template<typename T>
void Heap<T>::print_heap() {
    for (size_t i = 0; i < heap.size(); ++i) {
        std::cout << heap[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void Heap<T>::increase_key(size_t i, const T& new_val) {
    if (i >= heap.size() || heap[i] >= new_val) { throw std::invalid_argument("Invalid index or new value is not greater"); }

    heap[i] = new_val;
    sift_up(i);
}

#endif