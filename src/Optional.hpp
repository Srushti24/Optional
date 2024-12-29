#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include <iostream>
#include <memory>

template<typename T>
class Optional{
    public:
    Optional():has_value_(false) // Default constructor
    {
        std::cout << "Default Constructor called" << std::endl;
    }


    //Param Constrcutor
    Optional(const T& value):has_value_(true)
    {
        std::cout << "Param Constrcutor called" << std::endl;
        new(data_)T(value);
    }

    Optional(T&& value): has_value_(true)
    {
        std::cout << "Param Constrcutor move called" << std::endl;
        new(data_)T(std::move(value));
    }
   
   // Copy constructor
    Optional(const Optional& copy)
    {
        std::cout << "Copy constructor called" << std::endl;
        if(copy.has_value_)
        {
            new(data_)T(copy.value());
        }
        has_value_ = copy.has_value_;
    }

    //Move constructor
    Optional(Optional&& copy)
    {
        std::cout << "Move constructor called" << std::endl;
        if(copy.has_value_)
        {
            new(data_)T(std::move(copy.value()));
        }
        has_value_ = copy.has_value_;
    }

    //Move Assignment Operator
    Optional& operator=(Optional&& copy)
    {
        std::cout << "Move Assignment called" << std::endl;
        destroy();
        if(copy.has_value_)
        {
            new(data_)T(std::move(copy.value()));
        }
        has_value_ = copy.has_value_;
        return *this;
    }

    bool has_value()
    {
        return has_value_;
    }

    const T& value() const
    {
        const T* temp = reinterpret_cast<const T*>(data_);
        return *temp;
    }

    T& value() 
    {
         T* temp = reinterpret_cast<T*>(data_);
        return *temp;
    }

    //Copy Assignment Operator
    Optional& operator=(const Optional& copy)
    {
        std::cout << "Copy Assignment called" << std::endl;
        destroy();
        if(copy.has_value_)
        {
            new(data_)T(copy.value());
        }
        has_value_ = copy.has_value_;
        return *this;
    }

    ~Optional()
    {
        destroy();
    }
    void destroy()
    {
        if(has_value_)
        {
            reinterpret_cast<T*>(data_)->~T();
        }
    }

    private:
    /*INVARIENT: Only if has_value_ is set to true data_ has value
    */
    bool has_value_;
    char data_[sizeof(T)];

};

#endif