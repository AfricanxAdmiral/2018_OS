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

    infile.close();

    sort(arrival.begin(), arrival.end());

    int time = arrival[0].first, j = 1;
    vector< pair<int, int> > process;
    for (int i = 0; i < process_num;){
        if (i == (int)process.size())
            process.push_back(make_pair(burst[arrival[i].second], arrival[i].second));
        while (j < process_num){
            process.push_back(make_pair(burst[arrival[j].second], arrival[j].second));
            if (burst[arrival[j].second] < (process[arrival[i].second].first - arrival[j].first + time)){
                process[i].first -= (arrival[j].first - time);
                time = arrival[j].first;
                j++;
                break;
            }
            j++;
        }
        if (j == process_num){
            time += process[i].first;
            end[process[i].second] = time;
            i++;
        }
        sort(process.begin()+i, process.end());
    }

    outfile.open("ans2.txt");

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