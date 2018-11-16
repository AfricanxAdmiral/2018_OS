#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv){
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    int process_num;
    infile >> process_num;
    vector< pair<int, int> > arrival(process_num);
    int burst[process_num] = {0};
    int end[process_num] = {0};
    int static_arrival[process_num] = {0};

    for (int i = 0; i < process_num; i++){
        int x;
        infile >> x;
        static_arrival[i] = x;
        arrival[i].first = x;
        arrival[i].second = i;
    }
    for (int i = 0; i < process_num; i++){
        int x;
        infile >> x;
        burst[i] = x;
    }

    int quan;
    infile >> quan;

    infile.close();

    sort(arrival.begin(), arrival.end());

    int time = arrival[0].first, j = 0, done = 0;
    vector< pair<int, int> > process;
    for (int i = 0; done < process_num; i++){
        if ((int)process.size() == done && done < process_num){
            process.push_back(make_pair(burst[arrival[j].second], arrival[j].second));
            j++;
        }
        if (process[i].first){
            if (process[i].first > quan){
                time += quan;
            }
            else{
                time += process[i].first;
                end[process[i].second] = time;
                process[i].first = 0;
                done++;
            }
        }
        while (j < process_num){
            if (arrival[j].first <= time){
                process.push_back(make_pair(burst[arrival[j].second], arrival[j].second));
                j++;
            }
            else break;
        }
        if (process[i].first)
            if (process[i].first > quan)
                process.push_back(make_pair(process[i].first - quan, process[i].second));
    }
    outfile.open("ans3.txt");

    double sum_wait = 0.0, sum_turn = 0.0;
    for (int i = 0; i < process_num; i++){
        outfile << end[i] - static_arrival[i] - burst[i] << " " << end[i] - static_arrival[i] << endl;
        sum_turn += end[i] - static_arrival[i];
        sum_wait += burst[i];
    }
    outfile << ((double)(long long)(((sum_turn - sum_wait) / process_num)*100000 + 0.5)) / 100000 << endl;
    outfile << ((double)(long long)((sum_turn / process_num)*100000 + 0.5)) / 100000 << endl;

    outfile.close();

    return 0;
}