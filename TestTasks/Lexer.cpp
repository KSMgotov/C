#include "Lexer.h"
std::vector<std::string> Lexer::tokenize(std::string expressionWithWhitespaces){
    std::string expression = "";
    //Удаление пробелов
    for(int i = 0; i < expressionWithWhitespaces.length(); i++){
        if(expressionWithWhitespaces[i] != ' ') expression += expressionWithWhitespaces[i];
    }
    std::vector<std::string> res;
    for(int i = 0; i < expression.length(); i++){
        char c = expression[i];
        //Выделение чисел
        if(c >= '0' && c <= '9'){
            std::string num = "";
            num += c;
            while(i+1 < expression.length() && expression[i+1] >= '0' && expression[i+1] <= '9'){
                num += expression[i+1];
                i++;
            }
            res.push_back(num);
        }
        //Выделение операторов и скобок
        else{
            std::set<char> opSet{'+', '-', '*', '/', '(', ')'};
            if(c == '-' && (i == 0 || opSet.find(expression[i-1]) != opSet.end())){
                res.push_back("~");
            }
            else if(opSet.find(c) != opSet.end()){
                std::string op(1, c);
                res.push_back(op);
            }
            else throw Exception("Недопустимый символ");
        }
    }
    return res;
}