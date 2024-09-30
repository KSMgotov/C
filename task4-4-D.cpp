/*
Неориентированный взвешенный граф задан матрицей смежности. Найдите кратчайший цикл, который начинается и заканчивается в вершине номер 1
и проходит через все вершины по одному разу.

Формат ввода
В первой строке вводится число N (N ≤ 10) — количество вершин графа. Следующие N строк содержат по N целых неотрицательных чисел и задают матрицу смежности.
Число 0 означает, что ребро отстутствует. Любое другое число задаёт вес ребра.

Формат вывода
Выведите минимальную суммарную длину цикла или число -1, если цикл построить невозможно.
*/
#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> placements(int N, vector<int> s){
    if(N == 1) return vector<vector<int>>{s};
    vector<vector<int>> res;
    for(int i = 0; i <  N; i++){
        vector<int> s1 = s;
        s1.erase(s1.begin()+i);
        vector<vector<int>> tmp = placements(N-1, s1);
        for(auto it2 : tmp){
            it2.insert(it2.begin(), s[i]);
            res.push_back(it2);
        }
    }
    return res;
}
int main()
{
    vector<int> base;
    vector<vector<int>> order;
    vector<vector<int>> connect;
    int N, tmp, min, prev, len;
    bool found;
    cin >> N;
    connect.resize(N);
    for(int i  = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> tmp;
            connect[i].push_back(tmp);
        }
    }
    if(N == 1){
        cout << 0;
        return 0;
    }
    for(int i = 1; i < N; i++){
        base.push_back(i);
    }
    order = placements(N-1, base);
    min = 10000000;
    for(auto it : order){
        prev = 0;
        len = 0;
        it.push_back(0);
        for(auto it2 : it){
            tmp = connect[prev][it2];
            if(tmp == 0){
                len = 0;
                break;
            }
            len += tmp;
            if(len > min){
                len = 0;
                break;
            }
            prev = it2;
        }
        if(len > 0 && len < min) min = len;
    }
    if(min == 10000000) cout << -1;
    else cout << min;
    return 0;
}