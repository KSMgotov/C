#include "Parser.h"
double Parser::calculateRPN(std::vector<std::string> tokenVec){
    //Перевод выражения в обратную польскую запись
    Stack<char> opStack;
    std::vector<std::string> rpnVec;
    for(const auto& token : tokenVec){
        char c = token[0];
        //Числа сразу заносятся в новый вектор
        if(c >= '0' && c <= '9'){
            rpnVec.push_back(token);
        }
        //Операторы выталкивают из стека все другие операторы, имеющие приоритет больше или равный их собственному, и заносятся в стек
        else if(c == '~'){
            if(not opStack.isEmpty() && opStack.top() == '~'){
                rpnVec.push_back(std::string(1, opStack.pop()));
            }
            opStack.push(c);
        }
        else if(c == '*' || c == '/'){
            while(not opStack.isEmpty() && (opStack.top() == '*' || opStack.top() == '/' || opStack.top() == '~')){
                rpnVec.push_back(std::string(1, opStack.pop()));
            }
            opStack.push(c);
        }
        else if(c == '-' || c == '+'){
            while(not opStack.isEmpty() && (opStack.top() == '*' || opStack.top() == '/' || opStack.top() == '+' || opStack.top() == '-' || opStack.top() == '~')){
                rpnVec.push_back(std::string(1, opStack.pop()));
            }
            opStack.push(c);
        }
        //Открывающая скобка заносится в стек
        else if(c == '('){
            opStack.push('(');
        }
        //закрывающая собка выталкивает из стека все операторы до открывающей скобки, а затем и ее
        else if(c == ')'){
            bool found = false;
            bool foundOp = false;
            char tmp;
            while(not found && not opStack.isEmpty()){
                tmp = opStack.pop();
                if(tmp == '(') found = true;
                else{
                    foundOp = true;
                    rpnVec.push_back(std::string(1, tmp));
                }
            }
            if(not found) throw Exception("Нарушен баланс скобок");
            else if(not foundOp) throw Exception("Скобки не содержат операторов");
        }
    }
    //Оставшиеся в стеке операторы выталкиваются
    while(not opStack.isEmpty()){
        if(opStack.top() == '(') throw Exception("Нарушен баланс скобок");
        rpnVec.push_back(std::string(1, opStack.pop()));
    }
    //Вычисление выражения по обратной польской записи
    double op1, op2;
    Stack<double> numStack;
    for(const auto& token : rpnVec){
        char c = token[0];
        //Числа заносятся в стек
        if(c >= '0' && c <= '9') numStack.push(stoi(token));
        //Операторы берут из стека нужное количество операндов, результат операции заносится в стек
        else if(c == '~'){
            if(numStack.isEmpty()) throw Exception("Некорректное выражение");
            else{
                double op0 = numStack.pop();
                numStack.push(-op0);
            }
        }
        else{
            if(numStack.size() < 2) throw Exception("Некорректное выражение");
            else{
                op2 = numStack.pop();
                op1 = numStack.pop();
                if(c == '*') numStack.push(op1*op2);
                if(c == '/'){
                    if(op2 == 0) throw Exception("Деление на ноль");
                    else numStack.push(op1/op2);
                }
                if(c == '+') numStack.push(op1+op2);
                if(c == '-') numStack.push(op1-op2);
            }
        }
    }
    //Последнее число в стеке является результатом вычисления выражения
    if(numStack.size() != 1) throw Exception("Некорректное выражение");
    else return numStack.pop();
}
double Parser::parse(std::string str){
    return(calculateRPN(Lexer::tokenize(str)));
}