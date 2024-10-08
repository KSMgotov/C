/*
В системе умного дома под управлением голосового помощника Лариса n устройств, соединяющихся между собой по сети LoRaWAN.
Устройство номер 1 подключено к интернету и на него было скачано обновление, которое необходимо передать на все устройства.

Сеть LoRaWAN очень медленная, поэтому для распространения протокола был придуман peer-to-peer (P2P) протокол.
Файл обновления разбивается на k одинаковых по размеру частей, занумерованных от 1 до k.

Передача части обновления происходит во время таймслотов. Каждый таймслот занимает одну минуту.
За один таймслот каждое устройство может получить и передать ровно одну часть обновления.
То есть устройство во время таймслота может получать новую часть обновления и передавать уже имеющуюуся у него к началу таймслота часть обновления,
или совершать только одно из этих действий, или вообще не осуществлять прием или передачу.
После приема части обновления устройство может передавать эту часть обновления другим устройствам в следующих таймслотах.

Перед каждым таймслотом для каждой части обновления определяется, на скольких устройствах сети скачана эта часть.
Каждое устройство выбирает отсутствующую на нем часть обновления, которая встречается в сети реже всего.
Если таких частей несколько, то выбирается отсутствующая на устройстве часть обновления с наименьшим номером.

После этого устройство делает запрос выбранной части обновления у одного из устройств, на котором такая часть обновления уже скачана.
Если таких устройств несколько — выбирается устройство, на котором скачано наименьшее количество частей обновления.
Если и таких устройств оказалось несколько — выбирается устройство с минимальным номером.

После того, как все запросы отправлены, каждое устройство выбирает, чей запрос удовлетворить.
Устройство A удовлетворяет тот запрос, который поступил от наиболее ценного для A устройства.
Ценность устройства B для устройства A определяется как количество частей обновления, ранее полученных устройством A от устройства B.
Если на устройство A пришло несколько запросов от одинаково ценных устройств, то удовлетворяется запрос того устройства,
на котором меньше всего скачанных частей обновления. Если и таких запросов несколько, то среди них выбирается устройство с наименьшим номером.

Далее начинается новый таймслот. Устройства, чьи запросы удовлетворены, скачивают запрошенную часть обновления, а остальные не скачивают ничего.

Для каждого устройства определите, сколько таймслотов понадобится для скачивания всех частей обновления.

Формат ввода
Вводится два числа n и k (2 ≤ n ≤ 100, 1 ≤ k ≤ 200).

Формат вывода
Выведите n-1 число — количество таймслотов, необходимых для скачивания обновления на устройства с номерами от 2 до n.
*/
#include<iostream>
#include<set>
#include<vector>
using namespace std;
int main(){
    int N, k, min_part_downloads, chosen_part, min_device_downloads, chosen_device, rating_max, time_slot, updated_devices;
    cin >> N >> k;
    vector<int> parts_download_count(k, 1);
    vector<set<int>> devices(N);
    for(int i = 0; i < k; i++) devices[0].insert(i);
    vector<int> answer(N);
    vector<int> tmp;
    vector<vector<int>> rating(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            rating[i].push_back(0);
        }
    }
    vector<vector<int>> requests(N);
    time_slot = 1;
    updated_devices = 1;
    while(updated_devices < N){
        for(int i = 1; i < N; i++){
            if(answer[i] == 0){
                min_part_downloads = 300;
                for(int j = 0; j < k; j++){
                    if((not devices[i].count(j)) && parts_download_count[j] < min_part_downloads){
                        chosen_part = j;
                        min_part_downloads = parts_download_count[j];
                    }
                }
                min_device_downloads = 300;
                for(int j = 0; j < N; j++){
                    if(devices[j].count(chosen_part) && devices[j].size() < min_device_downloads){
                        chosen_device = j;
                        min_device_downloads = devices[j].size();
                    }
                }
                if(requests[chosen_device].empty()){
                    tmp = {i, chosen_part};
                    requests[chosen_device] = tmp;
                }
                else{
                    if((rating[chosen_device][i] > rating[chosen_device][requests[chosen_device][0]]) || ((rating[chosen_device][i] == rating[chosen_device][requests[chosen_device][0]]) && (devices[i].size() < devices[requests[chosen_device][0]].size()))){
                        tmp = {i, chosen_part};
                        requests[chosen_device] = tmp;
                    }
                }
            }
        }
        for(int i = 0; i < N; i++){
            if(not requests[i].empty()){
                tmp = requests[i];
                rating[tmp[0]][i]++;
                devices[tmp[0]].insert(tmp[1]);
                parts_download_count[tmp[1]]++;
                if(devices[tmp[0]].size() == k){
                    answer[tmp[0]] = time_slot;
                    updated_devices++;
                }
                requests[i].clear();
            }
        }
        time_slot++;
    }
    for(int i = 1; i < N; i++) cout << answer[i] << ' ';
    return 0;
}