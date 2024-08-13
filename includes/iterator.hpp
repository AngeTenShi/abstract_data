#ifndef CUSTOM_ITERATOR_HPP
#define CUSTOM_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
    template <class T>
    class RandomAccessIterator {
        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef long int difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
        protected:
            T* _ptr;
            template <class U> friend class RandomAccessIterator;
        public:
            RandomAccessIterator() : _ptr(0) {}
            RandomAccessIterator(T* ptr) : _ptr(ptr) {}
            RandomAccessIterator(const RandomAccessIterator& other) : _ptr(other._ptr) {}
            template <class U>
            RandomAccessIterator(const RandomAccessIterator<U>& other, ft::enable_if<ft::is_same<U, T>::value, void>::type* = 0) : _ptr(other._ptr) {}
            RandomAccessIterator& operator=(const RandomAccessIterator& other) {
                _ptr = other._ptr;
                return *this;
            }
            RandomAccessIterator& operator++() {
                _ptr++;
                return *this;
            }
            RandomAccessIterator operator++(int) {
                RandomAccessIterator tmp(*this);
                operator++();
                return tmp;
            }
            RandomAccessIterator& operator--() {
                _ptr--;
                return *this;
            }
            RandomAccessIterator operator--(int) {
                RandomAccessIterator tmp(*this);
                operator--();
                return tmp;
            }
            RandomAccessIterator& operator+=(difference_type n) {
                _ptr += n;
                return *this;
            }
            RandomAccessIterator operator+(difference_type n) const {
                RandomAccessIterator tmp(*this);
                tmp += n;
                return tmp;
            }
            RandomAccessIterator& operator-=(difference_type n) {
                _ptr -= n;
                return *this;
            }
            RandomAccessIterator operator-(difference_type n) const {
                RandomAccessIterator tmp(*this);
                tmp -= n;
                return tmp;
            }
            difference_type operator-(const RandomAccessIterator& other) const {
                return _ptr - other._ptr;
            }
            T& operator*() {
                return *_ptr;
            }
            const T& operator*() const {
                return *_ptr;
            }
            T* operator->() {
                return _ptr;
            }
            const T* operator->() const {
                return _ptr;
            }
            bool operator==(const RandomAccessIterator& other) const {
                return _ptr == other._ptr;
            }
            bool operator!=(const RandomAccessIterator& other) const {
                return _ptr != other._ptr;
            }
            bool operator<(const RandomAccessIterator& other) const {
                return _ptr < other._ptr;
            }
            bool operator>(const RandomAccessIterator& other) const {
                return _ptr > other._ptr;
            }
            bool operator<=(const RandomAccessIterator& other) const {
                return _ptr <= other._ptr;
            }
            bool operator>=(const RandomAccessIterator& other) const {
                return _ptr >= other._ptr;
            }
            friend RandomAccessIterator operator+(difference_type n, const RandomAccessIterator& it) {
                return it + n;
            }
    };

    template <class T>
    class reverse_iterator : public RandomAccessIterator<T> {
        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef typename RandomAccessIterator<T>::difference_type difference_type;

            reverse_iterator() : RandomAccessIterator<T>() {}
            reverse_iterator(T* ptr) : RandomAccessIterator<T>(ptr) {}
            reverse_iterator(const reverse_iterator& other) : RandomAccessIterator<T>(other._ptr) {}

            reverse_iterator& operator+=(difference_type n) {
                this->_ptr -= n;
                return *this;
            }

            reverse_iterator operator+(difference_type n) const {
                return reverse_iterator(this->_ptr - n);
            }

            reverse_iterator& operator-=(difference_type n) {
                this->_ptr += n;
                return *this;
            }

            reverse_iterator operator-(difference_type n) const {
                return reverse_iterator(this->_ptr + n);
            }

            reverse_iterator& operator++() {
                this->_ptr--;
                return *this;
            }

            reverse_iterator operator++(int) {
                reverse_iterator tmp(*this);
                operator++();
                return tmp;
            }

            reverse_iterator& operator--() {
                this->_ptr++;
                return *this;
            }

            reverse_iterator operator--(int) {
                reverse_iterator tmp(*this);
                operator--();
                return tmp;
            }
    };
}

#endif
