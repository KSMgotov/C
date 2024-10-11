#pragma once
#include<exception>
class Exception: public std::exception{
public:
    Exception(const char* message){
        errorMessage = message;
    }
    const char* what() const noexcept override{
        return errorMessage;
    }
private:
    const char* errorMessage;
};