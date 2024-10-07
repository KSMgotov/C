#ifndef STACK_H
#define STACK_H
#include<exception>
template<typename Type>
class Stack
{
public:
    struct Node{
        Type elem;
        Node* next;
    };
    Stack(){
        head = NULL;
        len = 0;
    }
    ~Stack(){
        Node* tmp = head;
        while(tmp != NULL){
            tmp = head->next;
            delete(head);
            head = tmp;
        }
    }
    Type top(){
        if(len == 0){
            throw std::exception();
        }
        else return head->elem;
    }
    void push(Type new_elem){
        Node* tmp = head;
        head = new(Node);
        head->elem = new_elem;
        head->next = tmp;
        len++;
    }
    Type pop(){
        if(len == 0){
            throw std::exception();
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
    bool isEmpty(){
        return(len == 0);
    }
    int size(){
        return len;
    }
private:
    Node* head;
    int len;
};
#endif