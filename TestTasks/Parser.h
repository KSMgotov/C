#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
class Parser{
public:
    static double calculateRPN(std::string str){
        Stack<double> numStack;
        char c;
        double op1, op2;
        for(int i = 0; i < str.length(); i++){
            c = str[i];
            if(c >= '0' && c <= '9') numStack.push(c - '0');
            else{
                if(numStack.size() < 2) throw std::exception();
                else{
                    op2 = numStack.pop();
                    op1 = numStack.pop();
                    if(c == '*') numStack.push(op1*op2);
                    if(c == '/') numStack.push(op1/op2);
                    if(c == '+') numStack.push(op1+op2);
                    if(c == '-') numStack.push(op1-op2);
                }
            }
        }
        if(numStack.size() != 1) throw std::exception();
        else return numStack.pop();
    }
    static double parse(std::string str){
        return(calculateRPN(Lexer::toRPN(str)));
    }
};
#endif