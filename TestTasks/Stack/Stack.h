#pragma once
#include<string>
#include "my_exception.h"
//Стек реализован в виде односвязного списка
template<typename Type>
class Stack
{
public:
    //Описание узла списка
    struct Node{
        Type elem;
        Node* next;
    };
    //Конструктор
    Stack(){
        head = NULL;
        len = 0;
    }
    //Деструктор
    ~Stack(){
        Node* tmp = head;
        while(tmp != NULL){
            tmp = head->next;
            delete(head);
            head = tmp;
        }
    }
    //Просмтор верхнего эелемента
    Type top(){
        if(len == 0){
            throw Exception("Попытка посмотреть верхний элемент пустого стека");
        }
        else return head->elem;
    }
    //Добавление элемента
    void push(Type new_elem){
        Node* tmp = head;
        head = new(Node);//Вообще говоря может выбросить bad_alloc, но в таком случае, наверное, выполнение программы в любом случае будет остановлено
        head->elem = new_elem;
        head->next = tmp;
        len++;
    }
    //Удаление элемента
    Type pop(){
        if(len == 0){
            throw Exception("Попытка достать элемент из пустого стека");
        }
        else{
            Node* tmp = head->next;
            Type top_elem = head->elem;
            delete(head);
            head = tmp;
            len--;
            return top_elem;
        }
    }
    //Проверка на пустоту
    bool isEmpty(){
        return(len == 0);
    }
    //Количество элементов
    int size(){
        return len;
    }
private:
    Node* head;
    int len;
};