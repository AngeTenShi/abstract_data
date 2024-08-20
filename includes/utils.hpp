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

    template <class T>
    struct is_integral { static const bool value = false; };
    
    template<>
    struct is_integral<bool> {
        static const bool value = true;
    };

    template<>
    struct is_integral<char> {
        static const bool value = true;
    };

    template<>
    struct is_integral<signed char> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned char> {
        static const bool value = true;
    };

    template<>
    struct is_integral<short> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned short> {
        static const bool value = true;
    };

    template<>
    struct is_integral<int> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned int> {
        static const bool value = true;
    };

    template<>
    struct is_integral<long> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned long> {
        static const bool value = true;
    };

    template<>
    struct is_integral<long long> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned long long> {
        static const bool value = true;
    };
}

#endif