#pragma once
#include<exception>

/*Пользовательский класс исключений с переопределенным методом what(),
возвращающим сообщение об ошибке. Оно задается при создании объекта класса
с помощью вызова конструктора с одним параметром типа const char*
*/
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