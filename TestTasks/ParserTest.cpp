#include<iostream>
#include "Parser.h"
using namespace std;
int main() {
    Lexer lex;
    string str = "5/(7-(1+1))*3-(2+(1+1))*5/(7-(2+1))*3-(2+(1+1))*(5/(7-(1+1))*3-(2+(1+1))+5/(7-(1+1))*3-(2+(1+1)))";
    try{
        cout << Parser::parse(str) << endl;
    }
    catch(const exception& e){
        cout << "Ошибка" << endl;
    }
    return 0;
}