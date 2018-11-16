#include <bits/stdc++.h>
using namespace std;

int main(int argc, char ** argv){
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    int process_num;
    infile >> process_num;
    vector< pair<int, int> > arrival(process_num);
    int burst[process_num] = {0};
    int wait[process_num] = {0};
    int static_arrival[process_num] = {0};
    int turnaround[process_num] = {0};

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

    int j = 0;
    int time = arrival[0].first;
    vector< pair<int, int> > process;
    for (int i = 0; i < process_num; i++){
        for (; j < process_num; j++){
            if(arrival[j].first <= time) process.push_back(make_pair(burst[arrival[j].second], arrival[j].second));
            else break;
        }
        sort(process.begin()+i, process.end());
        wait[process[i].second] = time - static_arrival[process[i].second];
        time += burst[process[i].second];
        turnaround[process[i].second] = time - static_arrival[process[i].second];
    }

    outfile.open("ans1.txt");

    double sum_wait = 0.0, sum_turn = 0.0;
    for (int i = 0; i < process_num; i++){
        outfile << wait[i] << " " << turnaround[i] << endl;
        sum_wait += wait[i];
        sum_turn += turnaround[i];
    }
    outfile << ((double)(long long)((sum_wait / process_num)*100000 + 0.5)) / 100000 << endl;
    outfile << ((double)(long long)((sum_turn / process_num)*100000 + 0.5)) / 100000 << endl;

    outfile.close();

    return 0;
}