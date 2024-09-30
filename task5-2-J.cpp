/*
Недавно один известный художник-абстракционист произвел на свет новый шедевр — картину «Два черных непересекающихся прямоугольника».
Картина представляет собой прямоугольник m× n, разбитый на квадраты 1× 1, некоторые из которых закрашены любимым цветом автора — черным.
Федя — не любитель абстрактных картин, однако ему стало интересно, действительно ли на картине изображены два непересекающихся прямоугольника.
Помогите ему это узнать. Прямоугольники не пересекаются в том смысле, что они не имеют общих клеток.

Формат ввода
Первая строка входного файла содержит числа m и n (1 ≤ m, n ≤ 200). Следующие m строк содержат описание рисунка.
Каждая строка содержит ровно n символов. Символ «.» обозначает пустой квадрат, а символ «#» — закрашенный.

Формат вывода
Если рисунок можно представить как два непересекающихся прямоугольника, выведите в первой строке «YES»,
а в следующих m строках выведите рисунок в том же виде, в каком он задан во входном файле, заменив квадраты,
соответствующие первому прямоугольнику на символ «a», а второму — на символ «b». Если решений несколько, выведите любое.

Если же этого сделать нельзя, выведите в выходной файл «NO».
*/
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int N, M, i_start1, j_start1, i_end1, j_end1, i_start2, j_start2, i_end2, j_end2, count;
    char tmp;
    bool possible, possible1, possible2, empty;
    vector<vector<char>> vec;
    cin >> M >> N;
    vec.resize(M);
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            cin >> tmp;
            vec[i].push_back(tmp);
        }
    }
    possible = false;
    for(int i = 1; i < M; i++){
        possible1 = true;
        possible2 = true;
        i_start1 = M;
        j_start1 = N;
        i_end1 = 0;
        j_end1 = 0;
        empty = true;
        for(int k = 0; k < i; k++){
            for(int m = 0; m < N; m++){
                if(vec[k][m] == '#'){
                    empty = false;
                    if(k < i_start1) i_start1 = k;
                    if(k > i_end1) i_end1 = k;
                    if(m < j_start1) j_start1 = m;
                    if(m > j_end1) j_end1 = m;
                }
            }
        }
        if(empty) possible1 = false;
        else{
            for(int k = i_start1; k <= i_end1; k++){
                for(int m = j_start1; m <= j_end1; m++){
                    if(vec[k][m] != '#'){
                        possible1 = false;
                        break;
                    }
                }
                if(not possible1) break;
            }
        }
        if(possible1){
            i_start2 = M;
            j_start2 = N;
            i_end2 = 0;
            j_end2 = 0;
            empty = true;
            for(int k = i; k < M; k++){
                for(int m = 0; m < N; m++){
                    if(vec[k][m] == '#'){
                        empty = false;
                        if(k < i_start2) i_start2 = k;
                        if(k > i_end2) i_end2 = k;
                        if(m < j_start2) j_start2 = m;
                        if(m > j_end2) j_end2 = m;
                    }
                }
            }
            if(empty) possible2 = false;
            else{
                for(int k = i_start2; k <= i_end2; k++){
                    for(int m = j_start2; m <= j_end2; m++){
                        if(vec[k][m] != '#'){
                            possible2 = false;
                            break;
                        }
                    }
                    if(not possible2) break;
                }
            }
            if(possible2){
                possible = true;
                for(int k = i_start1; k <= i_end1; k++){
                    for(int m = j_start1; m <= j_end1; m++){
                        vec[k][m] = 'a';
                    }
                }
                for(int k = i_start2; k <= i_end2; k++){
                    for(int m = j_start2; m <= j_end2; m++){
                        vec[k][m] = 'b';
                    }
                }
                cout << "YES" << endl;
                for(int k = 0; k < M; k++){
                    for(int m = 0; m < N; m++){
                        cout << vec[k][m];
                    }
                    cout << endl;
                }
                break;
            }
        }
    }
    if(not possible){
        for(int j = 1; j < N; j++){
            possible1 = true;
            possible2 = true;
            i_start1 = M;
            j_start1 = N;
            i_end1 = 0;
            j_end1 = 0;
            empty = true;
            for(int k = 0; k < M; k++){
                for(int m = 0; m < j; m++){
                    if(vec[k][m] == '#'){
                        empty = false;
                        if(k < i_start1) i_start1 = k;
                        if(k > i_end1) i_end1 = k;
                        if(m < j_start1) j_start1 = m;
                        if(m > j_end1) j_end1 = m;
                    }
                }
            }
            if(empty) possible1 = false;
            else{
                for(int k = i_start1; k <= i_end1; k++){
                    for(int m = j_start1; m <= j_end1; m++){
                        if(vec[k][m] != '#'){
                            possible1 = false;
                            break;
                        }
                    }
                    if(not possible1) break;
                }
            }
            if(possible1){
                i_start2 = M;
                j_start2 = N;
                i_end2 = 0;
                j_end2 = 0;
                empty = true;
                for(int k = 0; k < M; k++){
                    for(int m = j; m < N; m++){
                        if(vec[k][m] == '#'){
                            empty = false;
                            if(k < i_start2) i_start2 = k;
                            if(k > i_end2) i_end2 = k;
                            if(m < j_start2) j_start2 = m;
                            if(m > j_end2) j_end2 = m;
                        }
                    }
                }
                if(empty) possible2 = false;
                else{
                    for(int k = i_start2; k <= i_end2; k++){
                        for(int m = j_start2; m <= j_end2; m++){
                            if(vec[k][m] != '#'){
                                possible2 = false;
                                break;
                            }
                        }
                        if(not possible2) break;
                    }
                }
                if(possible2){
                    possible = true;
                    for(int k = i_start1; k <= i_end1; k++){
                        for(int m = j_start1; m <= j_end1; m++){
                            vec[k][m] = 'a';
                        }
                    }
                    for(int k = i_start2; k <= i_end2; k++){
                        for(int m = j_start2; m <= j_end2; m++){
                            vec[k][m] = 'b';
                        }
                    }
                    cout << "YES" << endl;
                    for(int k = 0; k < M; k++){
                        for(int m = 0; m < N; m++){
                            cout << vec[k][m];
                        }
                        cout << endl;
                    }
                    break;
                }
            }
        }
    }
    if(not possible) cout << "NO";
    return 0;
}