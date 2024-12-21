#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include <iostream>
#include <memory>

template<typename T>
class Optional{
    public:
    Optional():has_value_(false)
    {

    }

    //Param Constrcutor
    Optional(const T& value):has_value_(true)
    {
        new(data_)T(value);
    }

    Optional(T&& value): has_value_(true)
    {
        new(data_)T(std::move(value));
    }
   
   // Copy constructor
    Optional(const Optional& copy): has_value_(copy.has_value_)
    {
        new(data_)T(*reinterpret_cast<const T*>(copy.data_));
    }

    //Move constructor
    Optional(Optional&& copy): has_value_(copy.has_value_)
    {
        new(data_)T(std::move(*reinterpret_cast<T*>(copy.data_)));
        copy.has_value_ = false;
        memset(copy.data_, 0, sizeof(T));
    }

    //Move Assignment Operator
    Optional& operator=(Optional&& copy)
    {
        has_value_ = copy.has_value_;
        new(data_)T(std::move(*reinterpret_cast<T*>(copy.data_)));
        copy.has_value_ = false;
        memset(copy.data_, 0, sizeof(T));
       return *this;
    }

    bool has_value()
    {
        return has_value_;
    }

    T& value()
    {
        T* temp = reinterpret_cast<T*>(data_);
        return *temp;
    }

    //Copy Assignment Operator
    Optional& operator=(Optional& copy)
    {
        std::cout << "Copy Assignment Operator" << std::endl;
        has_value_ = copy.has_value_;
        new(data_)T(*(reinterpret_cast<T*>(copy.data_)));
        return *this;
    }

    ~Optional()
    {

    }

    private:
    bool has_value_;
    char data_[sizeof(T)];

};

#endif