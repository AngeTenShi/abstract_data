#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>
#include <iostream>
namespace ft
{
    class exception 
    {
        public:
            exception () throw() {};
            exception (const exception&) throw() {};
            exception& operator= (const exception&) throw() {  return *this; };
            virtual ~exception() throw() {};
            virtual const char* what() const throw() = 0;
    };
    
    class out_of_range : public exception
    {
        public:
            out_of_range() throw() : _msg("Out of range") {};
            out_of_range(const std::string& msg) throw() : _msg(msg) {}
            out_of_range(const out_of_range& other) : exception(other), _msg(other._msg) {};
            out_of_range& operator= (const out_of_range&other) throw()
            { 
                _msg = other._msg; 
                return *this; 
            };
            virtual ~out_of_range() throw() { };
            const char* what() const throw()
            {
                std::cout << "what() : " << _msg << std::endl;
                return _msg.c_str();
            }
        private:
            std::string _msg;

    };
}

#endif