
#ifndef LEXER_H
#define LEXER_H
#include<string>
#include"Stack.h"
class Lexer{
public:
    static std::string toRPN(std::string expression){
        std::string res = "";
        Stack<char> opStack;
        for(int i = 0; i < expression.length(); i++){
            char c = expression[i];
            if(c >= '0' && c <= '9'){
                res += c;
            }
            else if(c == '*' || c == '/' || c == '+' || c == '-'){
                if(c == '*' || c == '/'){
                    while(not opStack.isEmpty() && (opStack.top() == '*' || opStack.top() == '/')){
                        res += opStack.pop();
                    }
                }
                if(c == '-' || c == '+'){
                    while(not opStack.isEmpty() && (opStack.top() == '*' || opStack.top() == '/' || opStack.top() == '+' || opStack.top() == '-')){
                        res += opStack.pop();
                    }
                }
                opStack.push(c);
            }
            else if(c == '('){
                opStack.push('(');
            }
            else if(c == ')'){
                bool found = false;
                char tmp;
                while(not found && not opStack.isEmpty()){
                    tmp = opStack.pop();
                    if(tmp == '(') found = true;
                    else res += tmp;
                }
                if(not found) throw std::exception();
            }
        }
        while(not opStack.isEmpty()){
            if(opStack.top() == '(') throw std::exception();
            res += opStack.pop();
        }
        return res;
    }
};
#endif