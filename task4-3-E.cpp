/*
В начале XVIII века еще не было самолетов, поездов и автомобилей, поэтому все междугородние зимние поездки совершались на санях.
Как известно, с дорогами в России тогда было даже больше проблем, чем сейчас, а именно на N существовавших тогда городов имелась N-1 дорога,
каждая из которых соединяла два города. Из каждого города можно было добраться в любой другой (возможно, через промежуточные города).
В каждом городе была почтовая станция («ям»), на которой можно было пересесть в другие сани.
При этом ямщики могли долго запрягать (для каждого города известно время, которое ямщики в этом городе тратят на подготовку саней к поездке)
и быстро ехать (также для каждого города известна скорость, с которой ездят ямщики из него). Можно считать, что количество ямщиков в каждом городе не ограничено.

Если бы олимпиада проводилась 300 лет назад, то путь участников занимал бы гораздо большее время, чем сейчас.
Допустим, из каждого города в Москву выезжает участник олимпиады и хочет добраться до Москвы за наименьшее время
(не обязательно по кратчайшему пути: он может заезжать в любые города, через один и тот же город можно проезжать несколько раз).
Сначала он едет с ямщиком из своего города. Приехав в любой город, он может либо сразу ехать дальше, либо пересесть.
В первом случае он едет с той же скоростью, с какой ехал раньше. Если сменить ямщика, он сначала ждет, пока ямщик подготовит сани,
и только потом едет с ним (с той скоростью, с которой ездит этот ямщик). В пути можно делать сколько угодно пересадок.

Определите, какое время необходимо, чтобы все участники олимпиады доехали из своего города в Москву 300 лет назад. Все участники выезжают из своих городов одновременно.

Формат ввода
В первой строке входного файла дано натуральное число N, не превышающее 2000 — количество городов, соединенных дорогами. Город с номером 1 является столицей.

Следующие N строк содержат по два целых числа: Ti и Vi — время подготовки саней в городе i, выраженное в часах, и скорость, с которой ездят ямщики из города i,
в километрах в час (0 ≤ Ti ≤ 100, 1 ≤ Vi ≤ 100).

Следующие N–1 строк содержат описания дорог того времени. Каждое описание состоит из трех чисел Aj, Bj и Sj, где Aj и Bj — номера соединенных городов,
а Sj — расстояние между ними в километрах (1 ≤ Aj ≤ N, 1 ≤ Bj ≤ N, Aj ≠ Bj, 1 ≤ Sj ≤ 10000). Все дороги двусторонние,
то есть если из A можно проехать в B, то из B можно проехать в A. Гарантируется, что из всех городов можно добраться в столицу.

Формат вывода
Сначала выведите одно вещественное число — время в часах, в которое в Москву приедет последний участник.

Далее выведите путь участника, который приедет самым последним (если таких участников несколько, выведите путь любого из них).
Выведите город, из которого этот участник выехал первоначально, и перечислите в порядке посещения те города, в которых он делал пересадки.
Последовательность должна заканчиваться столицей.
*/
#include<iostream>
#include<vector>
#include<map>
using namespace std;
int main()
{
    int N, t, v, a, b, l, current, cur_len, prep_time, max_start;
    double min, vel_coef, tmp, max;
    vector<int> next;
    vector<vector<pair<int, int>>> roads;
    vector<pair<int, double>> min_paths;
    multimap<double, pair<int, int>> cities;
    multimap<int, int> paths;
    vector<vector<int>> shortest;
    cin >> N;
    shortest.resize(N);
    for(int i = 0; i < N; i++) shortest[i].assign(N, -1);
    roads.resize(N);
    next.resize(N);
    for(int i = 0; i < N; i++){
        cin >> t >> v;
        cities.insert(pair<double, pair<int,int>>(1.0/v,pair<int,int>(i, t)));
    }
    for(int i = 0; i < N-1; i++){
        cin >> a >> b >> l;
        roads[a-1].push_back(pair<int, int>(b-1, l));
        roads[b-1].push_back(pair<int, int>(a-1, l));
    }
    for(int i = 0; i < N; i ++){
        paths.insert(pair<long long int, long int>(0, i));
        while (not paths.empty()){
            current = paths.begin()->second;
            cur_len = paths.begin()->first;
            paths.erase(paths.begin());
            for(auto it: roads[current]){
                if(shortest[i][it.first] == -1 || cur_len + it.second < shortest[i][it.first]){
                    shortest[i][it.first] = cur_len + it.second;
                    paths.insert(pair<int,int>(shortest[i][it.first], it.first));
                }
            }
        }
    }
    for(int i = 0; i < N; i++){
        current = cities.begin()->second.first;
        prep_time = cities.begin()->second.second;
        vel_coef = cities.begin()->first;
        cities.erase(cities.begin());
        if(current == 0) continue;
        min = shortest[0][current]*vel_coef+prep_time;
        next[current] = 0;
        for(auto it : min_paths){
            tmp = shortest[current][it.first]*vel_coef+prep_time + it.second;
            if(tmp < min){ 
                min = tmp;
                next[current] = it.first;
            }
        }
        min_paths.push_back(pair<int, double>(current, min));
    }
    min_paths.push_back(pair<double,int>(0, 0));
    max = 0;
    for(auto it:min_paths){
        if (it.second > max){
            max = it.second;
            max_start = it.first;
        }
    }
    cout << fixed << max << endl;
    cout << max_start+1;
    while(max_start != 0){
        max_start = next[max_start];
        cout << ' ' << max_start+1; 
    }
    return 0;
}