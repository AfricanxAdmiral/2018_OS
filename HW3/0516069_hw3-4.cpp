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

    int quan_h, quan_m;
    infile >> quan_h;
    infile >> quan_m;

    infile.close();

    sort(arrival.begin(), arrival.end());

    int time = arrival[0].first, h = 0, m = 0, l = 0, done = 0, con_swi_time = 0;
    vector< pair<int, int> > process_m;
    vector< pair<int, int> > process_l;
    while (done < process_num){
        if (h < process_num && arrival[h].first <= time){
            if (burst[arrival[h].second] > quan_h){
                time += quan_h;
                process_m.push_back(make_pair(burst[arrival[h].second] - quan_h, arrival[h].second));
            }
            else{
                time += burst[arrival[h].second];
                end[arrival[h].second] = time;
                done++;
            }
            h++;
        }
        else if (h < process_num && m < (int)process_m.size()){
            if (arrival[h].first - time < quan_m){
                if(arrival[h].first - time < con_swi_time){
                    process_m[m].first -= (arrival[h].first - time);
                    con_swi_time -= (arrival[h].first - time);
                    time = arrival[h].first;
                }
                else if (con_swi_time){
                    if (process_m[m].first > con_swi_time){
                        process_l.push_back(make_pair(process_m[m].first - con_swi_time, process_m[m].second));
                        m++;
                        time += con_swi_time;
                        con_swi_time = 0;
                    }
                    else{
                        time += process_m[m].first;
                        end[process_m[m].second] = time;
                        m++;
                        done++;
                        con_swi_time = 0;
                    }
                }
                else{
                    if (process_m[m].first > arrival[h].first - time){
                        con_swi_time = quan_m - arrival[h].first + time;
                        process_m[m].first -= arrival[h].first - time;
                        time = arrival[h].first;
                    }
                    else{
                        time += process_m[m].first;
                        end[process_m[m].second] = time;
                        m++;
                        done++;
                    }
                }
            }
            else{
                if (con_swi_time){
                    if (process_m[m].first > con_swi_time){
                        process_l.push_back(make_pair(process_m[m].first - con_swi_time, process_m[m].second));
                        m++;
                        time += con_swi_time;
                        con_swi_time = 0;
                    }
                    else{
                        time += process_m[m].first;
                        end[process_m[m].second] = time;
                        m++;
                        done++;
                        con_swi_time = 0;
                    }
                }
                else{
                    if (process_m[m].first > quan_m){
                        process_l.push_back(make_pair(process_m[m].first - quan_m, process_m[m].second));
                        time += quan_m;
                        m++;
                    }
                    else{
                        time += process_m[m].first;
                        end[process_m[m].second] = time;
                        m++;
                        done++;
                    }
                }
            }
        }
        else if (m < (int)process_m.size()){
            if (con_swi_time){
                if (process_m[m].first > con_swi_time){
                    process_l.push_back(make_pair(process_m[m].first - con_swi_time, process_m[m].second));
                    m++;
                    time += con_swi_time;
                    con_swi_time = 0;
                }
                else{
                    time += process_m[m].first;
                    end[process_m[m].second] = time;
                    m++;
                    done++;
                    con_swi_time = 0;
                }
            }
            else{
                if (process_m[m].first > quan_m){
                    process_l.push_back(make_pair(process_m[m].first - quan_m, process_m[m].second));
                    time += quan_m;
                    m++;
                }
                else{
                    time += process_m[m].first;
                    end[process_m[m].second] = time;
                    m++;
                    done++;
                }
            }
        }
        else if (h < process_num && m == (int)process_m.size() && l < (int)process_l.size()){
            sort(process_l.begin()+l, process_l.end());
            if (process_l[l].first > arrival[h].first - time){
                process_l[l].first -= (arrival[h].first - time);
                time = arrival[h].first;
            }
            else{
                time += process_l[l].first;
                end[process_l[l].second] = time;
                done++;
                l++;
            }
        }
        else if (l < (int)process_l.size()){
            sort(process_l.begin()+l, process_l.end());
            time += process_l[l].first;
            end[process_l[l].second] = time;
            done++;
            l++;
        }
        else if (h < process_num && m == (int)process_m.size() && l == (int)process_l.size()){
            time = arrival[h].first;
        } 
    }
    outfile.open("ans4.txt");

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