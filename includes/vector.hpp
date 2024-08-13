#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "exception.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector 
    {
        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::size_type size_type;
            typedef ft::RandomAccessIterator<T> iterator;
            typedef ft::RandomAccessIterator<const T> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        private:
            pointer _array;
            size_type _size;
            size_type _capacity;
            allocator_type _alloc;
                     
        public: 

            /* ITERATORS */
            iterator begin() { return iterator(_array); }
            const_iterator begin() const { return const_iterator(_array); }
            iterator end() { return iterator(_array + _size); }
            const_iterator end() const { return const_iterator(_array + _size); }
            reverse_iterator rbegin() { return reverse_iterator(end()); }
            reverse_iterator rend() { return reverse_iterator(begin()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
            
            /* CAPACITY*/
            size_type size() const { return _size; }
            size_type max_size() const { return _alloc.max_size(); }
            void resize(size_type n, value_type val = value_type()) //https://cplusplus.com/reference/vector/vector/resize/
            {
                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++)
                        _alloc.destroy(_array + i);
                    _size = n;
                }
                else if (n > _size)
                {
                    if (n > _capacity)
                        reserve(n);
                    for (size_type i = _size; i < n; i++)
                        _alloc.construct(_array + i, val);
                    _size = n;
                }
            }
            size_type capacity() const { return _capacity; }
            bool empty() const { return _size == 0; }
            void reserve(size_type n) 
            {
                if (n <= _capacity)
                    return;
                if (n == 1)
                {
                    pointer new_data = _alloc.allocate(2);
                    _array = new_data;
                    _capacity = 2;
                    _size = 0;
                    return;
                }
                pointer new_data = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++)
                {
                    _alloc.construct(new_data + i, _array[i]);
                    _alloc.destroy(_array + i);
                }
                _alloc.deallocate(_array, _capacity);
                _array = new_data;
                _capacity = n;
            }
            void shrink_to_fit() // maybe not working need to keep the same array ?
            {
                if (_size < _capacity)
                {
                    pointer new_data = _alloc.allocate(_size);
                    for (size_type i = 0; i < _size; i++)
                    {
                        _alloc.construct(new_data + i, _array[i]);
                        _alloc.destroy(_array + i);
                    }
                    _alloc.deallocate(_array, _capacity);
                    _array = new_data;
                    _capacity = _size;
                }
            }

            /* ELEMENT ACCESS */
            reference operator[](size_type index) { return _array[index]; }
            const_reference operator[](size_type index) const { return _array[index]; }
            reference at(size_type index) {
                if (index >= _size) {
                    throw ft::out_of_range("vector::at: index out of range");
                }
                return _array[index];
            }
            const_reference at(size_type index) const {
                if (index >= _size) {
                    throw ft::out_of_range("vector::at: index out of range");
                }
                return _array[index];
            }
            reference front() { return _array[0]; }
            const_reference front() const { return _array[0]; }
            reference back() { return _array[_size - 1]; }
            const_reference back() const { return _array[_size - 1]; }
            value_type* data() { return _array; }
            const value_type* data() const { return _array; }

            /* MODIFIERS */
            template <class InputIterator> void assign(InputIterator first, InputIterator last)
            {
                clear();
                while (first != last)
                {
                    push_back(*first);
                    first++;
                }
            }
            void push_back(const value_type& value) {
                if (_size == _capacity)
                    reserve(_capacity == 0 ? 1 : _capacity * 2);
                _alloc.construct(_array + _size, value);
                ++_size;
            }

            void pop_back() {
                if (_size > 0) {
                    _alloc.destroy(_array + _size - 1);
                    --_size;
                }
            }
            iterator    insert(const_iterator position, size_type n, const value_type& val)
            {
                if (n == 0)
                    throw ft::out_of_range("vector::insert: n is 0");
                if (_size + n > _capacity)
                    reserve(_capacity == 0 ? 1 : _capacity * 2);
                for (iterator i = end() - 1; i >= position; i--)
                    _array[i - begin() + n] = *i;
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_array + (position - begin()) + i, val);
                _size += n;
                return (begin() + (position - begin()));
            }
            iterator insert(const_iterator position, const value_type& val) {
                size_type index = position - begin();
                insert(position, 1, val);
                return begin() + index;
            }
            template <class InputIterator>
            iterator insert(const_iterator position, InputIterator first, InputIterator last)
            {
                size_type n = last - first;
                if (n == 0)
                    return begin() + (position - begin());
                if (_size + n > _capacity)
                    reserve(_capacity == 0 ? 1 : _capacity * 2);
                for (const_iterator i = end() - 1; i >= position; i--)
                    _array[i - begin() + n] = *i;
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_array + (position - begin()) + i, *first++);
                _size += n;
                return (begin() + (position - begin()));
            }
            iterator erase(iterator position)
            {
                erase(position, position + 1);
                return position;
            }
            iterator erase(iterator first, iterator last)
            {
                size_type n = last - first;
                for (size_type i = 0; i < n; i++)
                    _alloc.destroy(_array + (first - begin()) + i);
                for (size_type i = first - begin(); i < _size - n; i++)
                    _array[i] = _array[i + n];
                _size -= n;
                return first;
            }
            void swap(vector& x)
            {
                pointer tmp_array = _array;
                size_type tmp_size = _size;
                size_type tmp_capacity = _capacity;
                _array = x._array;
                _size = x._size;
                _capacity = x._capacity;
                x._array = tmp_array;
                x._size = tmp_size;
                x._capacity = tmp_capacity;
            }
            void    clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_array + i);
                _size = 0;
            }
            /* CONSTRUCTORS */
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {
                _alloc = alloc;
                _size = 0;
                _capacity = 0;
                _array = 0;
                assign(first, last);
            }
            explicit vector(const Alloc& alloc = Alloc()) : _size(0), _capacity(0), _alloc(alloc) {}
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            {
                _alloc = alloc;
                _size = n;
                _capacity = n;
                _array = _alloc.allocate(n);
                for (size_type i = 0; i < n; i++)
                    push_back(val);
            }
            vector (const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
            {
                _array = _alloc.allocate(_size);
                for (size_type i = 0; i < _size; i++)
                    push_back(x._array[i]);
            }
            ~vector() 
            {
                if (_size > 0)
                    clear();
            }
            vector& operator= (const vector& x) 
            {
                if (this == &x)
                    return *this;
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_array + i);
                _alloc.deallocate(_array, _size);
                _alloc = x._alloc;
                _size = x._size;
                _capacity = x._capacity;
                _array = _alloc.allocate(_size);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(_array + i, x._array[i]);
                return *this;
            }

            allocator_type get_allocator() const { return _alloc; }
};
    template <typename T, typename Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        typename vector<T, Alloc>::const_iterator lit = lhs.begin();
        typename vector<T, Alloc>::const_iterator rit = rhs.begin();
        while (lit != lhs.end() && rit != rhs.end()) {
            if (*lit != *rit) {
                return false;
            }
            ++lit;
            ++rit;
        }
        return lit == lhs.end() && rit == rhs.end();
    }

    template <typename T, typename Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <typename T, typename Alloc>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        typename vector<T, Alloc>::const_iterator lit = lhs.begin();
        typename vector<T, Alloc>::const_iterator rit = rhs.begin();
        while (lit != lhs.end() && rit != rhs.end()) {
            if (*lit < *rit) {
                return true;
            }
            if (*rit < *lit) {
                return false;
            }
            ++lit;
            ++rit;
        }
        return lit == lhs.end() && rit != rhs.end();
    }

    template <typename T, typename Alloc>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <typename T, typename Alloc>
    bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return rhs < lhs;
    }

    template <typename T, typename Alloc>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <typename T, typename Alloc>
    void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) 
    {
        lhs.swap(rhs);
    }
} 

#endif