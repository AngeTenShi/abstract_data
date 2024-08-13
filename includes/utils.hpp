#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
    template <bool B, class T = void>
    struct enable_if {};
    
    template <class T>
    struct enable_if<true, T> { typedef T type; };

    template <class T, class U>
    struct is_same { static const bool value = false; };

    template <class T>
    struct is_same<T, T> { static const bool value = true; };
}

#endif