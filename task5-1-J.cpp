/*
Вася пишет новую версию своего офисного пакета "Closed Office". Недавно он начал работу над редактором "Dword", входящим в состав пакета.

Последняя проблема, с которой столкнулся Вася — размещение рисунков в документе. Он никак не может добиться стабильного отображения рисунков в тех местах,
в которые он их помещает. Окончательно отчаявшись написать соответствующий модуль самостоятельно, Вася решил обратиться за помощью к вам. Напишите программу,
которая будет осуществлять размещение документа на странице.

Документ в формате редактора "Dword" представляет собой последовательность абзацев.
Каждый абзац представляет собой последовательность элементов – слов и рисунков.
Элементы одного абзаца разделены пробелами и/или переводом строки. Абзацы разделены пустой строкой.
Строка, состоящая только из пробелов, считается пустой.

Слово — это последовательность символов, состоящая из букв латинского алфавита, цифр, и знаков препинания: ".", ",", ":", ";", "!", "?", "-", "'".

Рисунок описывается следующим образом: "(image image parameters)". Каждый параметр рисунка имеет вид "имя=значение".
Параметры рисунка разделены пробелами и/или переводом строки. У каждого рисунка обязательно есть следующие параметры:

width — целое положительное число, ширина рисунка в пикселях
height — целое положительное число, высота рисунка в пикселях
layout — одно из следующих значений: embedded (в тексте), surrounded (обтекание текстом), floating (свободное), описывает расположение рисунка относительно текста

Документ размещается на бесконечной вверх и вниз странице шириной w пикселей (разбиение на конечные по высоте страницы планируется в следующей версии редактора).
Одна из точек на левой границе страницы условно считается точкой с ординатой равной нулю. Ордината увеличивается вниз.

Размещение документа происходит следующим образом. Абзацы размещаются по очереди. Первый абзац размещается так, что его верхняя граница имеет ординату 0.

Абзац размещается следующим образом. Элементы располагаются по строкам. Каждая строка исходно имеет высоту h пикселей.
В процессе размещения рисунков высота строк может увеличиваться, и строки могут разбиваться рисунками на фрагменты.

Слова размещаются следующим образом. Считается, что каждый символ имеет ширину c пикселей.
Перед каждым словом, кроме первого во фрагменте, ставится пробел шириной также в c пикселей.
Если слово помещается в текущем фрагменте, то оно размещается на нем. Если слово не помещается в текущем фрагменте,
то оно размещается в первом фрагменте текущей строки, расположенном правее текущего, в котором оно помещается.
Если такого фрагмента нет, то начинается новая строка, и поиск подходящего фрагмента продолжается в ней. Слово всегда "прижимается" к верхней границе строки.

Размещение рисунка зависит от его расположения относительно текста.

Если расположение рисунка относительно текста установлено в "embedded", то он располагается так же, как слово, за тем исключением,
что его ширина равна ширине, указанной в параметрах рисунка. Кроме того, если высота рисунка больше текущей высоты строки,
то она увеличивается до высоты рисунка (при этом верхняя граница строки не перемещается, а смещается вниз нижняя граница).
Если рисунок типа "embedded" не первый элемент во фрагменте, то перед ним ставится пробел шириной c пикселей.
Рисунки типа "embedded" также прижимаются к верхней границе строки.

Если расположение рисунка относительно текста установлено в "surrounded", то рисунок размещается следующим образом.
Сначала аналогично находится первый фрагмент, в котором рисунок помещается по ширине.
При этом перед рисунком этого типа не ставится пробел, даже если это не первый элемент во фрагменте.

После этого рисунок размещается следующим образом: верхний край рисунка совпадает с верхней границей строки,
в которой находится найденный фрагмент, а сам рисунок продолжается вниз. При этом строки, через которые он проходит, разбиваются им на фрагменты.

Если расположение рисунка относительно текста установлено в "floating", то рисунок размещается поверх текста и других рисунков и никак с ними не взаимодействует.
В этом случае у рисунка есть два дополнительных параметра: "dx" и "dy" — целые числа, задающие смещение в пикселях верхнего левого угла рисунка вправо и вниз,
соответственно, относительно позиции, где находится верхний правый угол предыдущего слова или рисунка
(или самой левой верхней точки первой строки абзаца, если рисунок — первый элемент абзаца).

Если при размещении рисунка таким образом он выходит за левую границу страницы, то он смещается вправо,
так, чтобы его левый край совпадал с левой границей страницы. Аналогично, если рисунок выходит за правую границу страницы,
то он смещается влево, чтобы его правый край совпадал с правой границей страницы.

Верхняя граница следующего абзаца совпадает с более низкой точкой из нижней границы последней строки и самой нижней границы рисунков типа "surrounded" предыдущего абзаца.

По заданным w, h, c и документу найдите координаты верхних левых углов всех рисунков в документе.

Формат ввода
Первая строка входного файла содержит три целых числа: w, h и c (1 ≤ w ≤ 1000, 1 ≤ h ≤ 50, 1 ≤ c ≤ w).

Далее следует документ. Размер входного файла не превышает 1000 байт. Гарантируется, что ширина любого слова и любого рисунка не превышает w.
Высота всех рисунков не превышает 1000. Относительное смещение всех рисунков типа «floating» не превышает 1000 по абсолютной величине.

Формат вывода
Выведите в выходной файл по два числа для каждого рисунка — координаты его верхнего левого угла. Выводите координаты рисунков в том порядке, в котором они встречаются во входном файле.

Пример 1
Ввод
120 10 8
start (image layout=embedded width=12 height=5)
(image layout=surrounded width=25 height=58)
and word is 
(image layout=floating dx=18 dy=-15 width=25 height=20)
here new 
(image layout=embedded width=20 height=22)
another
(image layout=embedded width=40 height=19)
longword

new paragraph
(image layout=surrounded width=5 height=30)
(image layout=floating width=20 height=35 dx=50 dy=-16)

Вывод
48 0
60 0
74 -5
32 20
0 52
104 81
100 65

*/

// Ввод и вывод осуществляются через файлы input.txt и output.txt соответственно.
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
void add_object(string s, vector<vector<int>>& vec){
    vector<int> tmp;
    tmp.clear();
    if(s[0] != '('){
        int a = s.size();
        tmp = {0, a};
        vec.push_back(tmp);
    }
    else{
        int sign, value;
        int count1 = 0;
        int count2 = 1;
        int count3 = 2;
        while(s[count1] != 'u' || s[count2] != 't' || s[count3] != '='){
            count1++;
            count2++;
            count3++;
        }
        count3++;
        if(s[count3] == 'e'){
            tmp.push_back(1);
        }
        if(s[count3] == 's'){
            tmp.push_back(2);
        }
        if(s[count3] == 'f'){
            tmp.push_back(3);
        }
        sign = 1;
        value = 0;
        count1 = 0;
        count2 = 1;
        count3 = 2;
        while(s[count1] != 't' || s[count2] != 'h' || s[count3] != '='){
            count1++;
            count2++;
            count3++;
        }
        count3++;
        if(s[count3] == '-'){
            sign = -1;
            count3++;
        }
        while(s[count3] >= '0' && s[count3] <= '9'){
            value *= 10;
            value += s[count3] - '0';
            count3++;
        }
        tmp.push_back(value*sign);
        sign = 1;
        value = 0;
        count1 = 0;
        count2 = 1;
        count3 = 2;
        while(s[count1] != 'h' || s[count2] != 't' || s[count3] != '='){
            count1++;
            count2++;
            count3++;
        }
        count3++;
        if(s[count3] == '-'){
            sign = -1;
            count3++;
        }
        while(s[count3] >= '0' && s[count3] <= '9'){
            value *= 10;
            value += s[count3] - '0';
            count3++;
        }
        tmp.push_back(value*sign);
        if(tmp[0] == 3){
            sign = 1;
            value = 0;
            count1 = 0;
            count2 = 1;
            count3 = 2;
            while(s[count1] != 'd' || s[count2] != 'x' || s[count3] != '='){
                count1++;
                count2++;
                count3++;
            }
            count3++;
            if(s[count3] == '-'){
                sign = -1;
                count3++;
            }
            while(s[count3] >= '0' && s[count3] <= '9'){
                value *= 10;
                value += s[count3] - '0';
                count3++;
            }
            tmp.push_back(value*sign);
            sign = 1;
            value = 0;
            count1 = 0;
            count2 = 1;
            count3 = 2;
            while(s[count1] != 'd' || s[count2] != 'y' || s[count3] != '='){
                count1++;
                count2++;
                count3++;
            }
            count3++;
            if(s[count3] == '-'){
                sign = -1;
                count3++;
            }
            while(s[count3] >= '0' && s[count3] <= '9'){
                value *= 10;
                value += s[count3] - '0';
                count3++;
            }
            tmp.push_back(value*sign);
        }
        vec.push_back(tmp);
    }
}

void split_into_fragments(vector<vector<int>>& fragments, vector<vector<int>>& sur_images, int cur_y){
    vector<vector<int>> fragments_new;
    vector<vector<int>> sur_images_new;
    vector<int> tmp;
    fragments_new.clear();
    sur_images_new.clear();
    tmp.clear();
    for(auto it1 : sur_images){
        if(it1[0] > cur_y){
            sur_images_new.push_back(it1);
            for(auto it2 : fragments){
                if(it1[1] > it2[0] && it1[2] < it2[1]){
                    tmp = {it2[0], it1[1]};
                    fragments_new.push_back(tmp);
                    tmp = {it1[2], it2[1]};
                    fragments_new.push_back(tmp);
                }
                else if(it1[1] == it2[0] && it1[2] < it2[1]){
                    tmp = {it1[2], it2[1]};
                    fragments_new.push_back(tmp);
                }
                else if(it1[1] > it2[0] && it1[2] == it2[1]){
                    tmp = {it2[0], it1[1]};
                    fragments_new.push_back(tmp);
                }
                else if(it1[1] == it2[0] && it1[2] == it2[1]){
                    
                }
                else fragments_new.push_back(it2);
            }
            fragments = fragments_new;
            fragments_new.clear();
        }
    }
    sur_images = sur_images_new;
} 

int main(){
    int width, height, char_size, cur_x, cur_y, cur_h, space_bar, prev_x, prev_y;
    bool placed, empty;
    string line, tmp;
    ifstream in("input.txt");
    ofstream out("output.txt");
    vector<int> sur_image;
    vector<vector<int>> objects, sur_images, fragments;
    objects.clear();
    sur_images.clear();
    fragments.clear();
    in >> width >> height >> char_size;
    getline(in ,line);
    while(getline(in, line)){
        if(line.size() == 0){
            vector<int> v = {4};
            objects.push_back(v);
            continue;
        }        
        empty = true;
        auto it = line.begin();
        while(it < line.end()){
            if(*it != ' '){
                empty = false;
                break;
            }
            it++;
        }
        if(empty){
            vector<int> v = {4};
            objects.push_back(v);
            continue;
        }
        tmp.clear();
        while(it < line.end()){
            if(*it == ' '){
                if(not tmp.empty()){
                    add_object(tmp, objects);
                    tmp.clear();
                }
            }
            else if(*it == '('){
                while(*it != ')'){
                    tmp.push_back(*it);
                    it++;
                    if(it > line.end()){
                        getline(in, line);
                        it = line.begin();
                    }
                }
                tmp.push_back(*it);
                add_object(tmp, objects);
                tmp.clear();
            }
            else tmp.push_back(*it);
            it++;
        }
        if(not tmp.empty()){
            add_object(tmp, objects);
            tmp.clear();
        }
    }
    in.close();
    cur_x = 0;
    cur_y = 0;
    cur_h = height;
    fragments = {{0, width}};
    auto fragment = fragments.begin();
    space_bar = 0;
    prev_x = 0;
    prev_y = 0;
    for(auto it : objects){
        placed = false;
        switch(it[0]){
            case(0):
                while(not placed){
                    if(char_size*(it[1] + space_bar) <= (*fragment)[1] - cur_x){
                        cur_x += char_size*(it[1] + space_bar);
                        placed = true;
                        space_bar = 1;
                        prev_x = cur_x;
                        prev_y = cur_y;
                    }
                    else{
                        fragment++;
                        if(fragment < fragments.end()){
                            cur_x = (*fragment)[0];
                            space_bar = 0;
                        }
                        else{
                            do{
                                cur_y += cur_h;
                                cur_h = height;
                                fragments = {{0, width}};
                                split_into_fragments(fragments, sur_images, cur_y);
                            } while(fragments.empty());
                            fragment = fragments.begin();
                            cur_x = (*fragment)[0];
                            space_bar = 0;
                        }
                    }
                }
                break;
            case(1):
                while(not placed){
                    if(it[1] + space_bar*char_size <= (*fragment)[1] - cur_x){
                        cur_x += it[1] + space_bar*char_size;
                        placed = true;
                        prev_x = cur_x;
                        prev_y = cur_y;
                        out << cur_x - it[1] << ' ' << cur_y << endl;
                        if(it[2] > cur_h) cur_h = it[2];
                        space_bar = 1;
                    }
                    else{
                        fragment++;
                        if(fragment < fragments.end()){
                            cur_x = (*fragment)[0];
                            space_bar = 0;
                        }
                        else{
                            do{
                                cur_y += cur_h;
                                cur_h = height;
                                fragments = {{0, width}};
                                split_into_fragments(fragments, sur_images, cur_y);
                            } while(fragments.empty());
                            fragment = fragments.begin();
                            cur_x = (*fragment)[0];
                            space_bar = 0;
                        }
                    }
                }
                break;
            case(2):
                while(not placed){
                    if(it[1] <= (*fragment)[1] - cur_x){
                        cur_x += it[1];
                        placed = true;
                        prev_x = cur_x;
                        prev_y = cur_y;
                        out << cur_x - it[1] << ' ' << cur_y << endl;
                        sur_image = {cur_y + it[2], cur_x - it[1], cur_x};
                        sur_images.push_back(sur_image);
                        space_bar = 0;
                    }
                    else{
                        fragment++;
                        if(fragment < fragments.end()){
                            cur_x = (*fragment)[0];
                            space_bar = 0;
                        }
                        else{
                            do{
                                cur_y += cur_h;
                                cur_h = height;
                                fragments = {{0, width}};
                                split_into_fragments(fragments, sur_images, cur_y);
                            } while(fragments.empty());
                            fragment = fragments.begin();
                            cur_x = (*fragment)[0];
                            space_bar = 0;
                        }
                    }
                }
                break;
            case(3):
                out << max(0, min(prev_x + it[3], width - it[1])) << ' ' << prev_y + it[4] << endl;
                prev_x = max(0, min(prev_x + it[3], width - it[1])) + it[1];
                prev_y = prev_y + it[4];
                break;
            case(4):
                cur_x = 0;
                cur_y += cur_h;
                cur_h = height;
                fragments = {{0, width}};
                auto fragment = fragments.begin();
                space_bar = 0;
                for(auto it2 : sur_images){
                    if(it2[0] > cur_y) cur_y == it2[0];
                }
                prev_x = 0;
                prev_y = cur_y;
                break;
        }
    }
    out.close();
    return 0;
}