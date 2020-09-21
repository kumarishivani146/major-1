#include <iostream>
#include <cstdlib>
#include <cmath>
#include<fstream>
#define MAX 1000
#define Q 1
#define BUSY 1
#define IDLE 0

using namespace std;


struct process_type{
    int pid;
    float BT;
    float AT;
    int priority;
};

struct stat_type{
    int pid;
    float BT;
    float AT;
    int priority;
    float ET;
    float TT;
    float WT;
};

process_type process_list[MAX], ready_q[MAX];
stat_type process_stat[MAX];
const int a=100000;
    double arr[a];
int count;
float sim_time;
float next_arrival;
float next_departure;
int server_status;
int listsize, qsize;
int pid;
int nxt_aps;
int nxt_rps;
int algo;

void initialize(float mean_arrival, int num_process);
void remove_from_list(int idx);
void remove_from_readyq(int idx);
int get_next_arriving_process(int n);
int get_nxt_run_process(int algorithm);
float expon(float mean);
void printstat(int n);
void getdata();



int main(){
    int seed_num = 1;
    int num_process = 0;
    int required_process = 1000;
    float mean_arrival = 5.0;


    int cpid;



    srand(seed_num);

    initialize(mean_arrival, required_process);
    do{

        if ((next_arrival < next_departure) && (listsize > 0)){

        if (server_status == BUSY){

            sim_time = next_arrival;
                    pid = process_list[nxt_aps].pid;
                    cout << "Time = " << sim_time << ". Process " << pid
                         << " arrived. Server is busy. Enqueueing." << endl;
                    ready_q[qsize].pid = process_list[nxt_aps].pid;
                    ready_q[qsize].AT = process_list[nxt_aps].AT;
            ready_q[qsize].BT = process_list[nxt_aps].BT;
            ready_q[qsize].priority = process_list[nxt_aps].priority;
                    qsize++;
                    remove_from_list(nxt_aps);

                    nxt_aps = get_next_arriving_process(listsize);
                    next_arrival = process_list[nxt_aps].AT;
        }
        else{

            sim_time = next_arrival;
                    pid = process_list[nxt_aps].pid;
                    cout << "Time = " << sim_time << ". Process " << pid
                         << " arrived. Server is idle." << endl;
                    cout << "          CPU will run process until time = "
                         << sim_time + process_list[nxt_aps].BT << endl;

                    process_stat[pid-1].pid = pid;
                    process_stat[pid-1].BT = process_list[nxt_aps].BT;
                    process_stat[pid-1].AT = process_list[nxt_aps].AT;
                    process_stat[pid-1].priority = process_list[nxt_aps].priority;
                    process_stat[pid-1].WT = 0.0;
                    process_stat[pid-1].ET = sim_time;
                    process_stat[pid-1].TT = process_list[nxt_aps].BT + 0.0;

                    server_status = BUSY;
                    cpid = pid;
                    next_departure = sim_time + process_list[nxt_aps].BT;
                    remove_from_list(nxt_aps);
                    nxt_aps = get_next_arriving_process(listsize);
            next_arrival = process_list[nxt_aps].AT;
        }
        }
        else{

        if (qsize == 0){

            sim_time = next_departure;
                    cout << "Time = " << sim_time << ". Process " << cpid
                        << " is finished with the CPU . Ready queue is empty."
                        << endl;
            server_status = IDLE;

                    next_departure = 1.0e+30;
        }
        else{

            sim_time = next_departure;
                    cout << "Time = " << sim_time << ". Process " << cpid
                         << " is finished with the CPU. " << endl;
                    cout << "      Getting next process from the ready queue."
                         << endl;

            nxt_rps = get_nxt_run_process(algo);
                    cpid = ready_q[nxt_rps].pid;
                    cout << "      Running next process: Process "
                         << cpid << "."<< endl;
                    cout << "      CPU will run process until time = "
                         << sim_time + ready_q[nxt_rps].BT << endl;


                    process_stat[cpid-1].pid = ready_q[nxt_rps].pid;
                    process_stat[cpid-1].BT = ready_q[nxt_rps].BT;
                    process_stat[cpid-1].AT = ready_q[nxt_rps].AT;
                    process_stat[cpid-1].priority = ready_q[nxt_rps].priority;
                    process_stat[cpid-1].WT = sim_time - ready_q[nxt_rps].AT;
                    process_stat[cpid-1].ET = sim_time;
                    process_stat[cpid-1].TT = ready_q[nxt_aps].BT + (sim_time - ready_q[nxt_rps].AT);


            next_departure = sim_time + ready_q[nxt_rps].BT;
            remove_from_readyq(nxt_rps);
                }
                num_process++;
        }

    }while (num_process < required_process);

        cout << "Simulation Ends." << endl;
        cout << "*******************************" << endl;
        cout << "Simulation Statistics:" << endl;
        printstat(required_process);

    return 0;
}

void getdata()
{


    ifstream inp;
    inp.open("text.txt");
    count=0;
    if(!inp)
    {
        cout<<"error find";

    }
    while(!inp.eof())
    {
        inp>>arr[count];
        count++;
    }
}
void initialize(float mean_arrival,int num_process){
    int i;

    sim_time = 0.0;
        listsize = num_process;

        getdata();
    for (i=0; i< num_process; i++){

            process_list[i].pid = i+1;
            process_list[i].AT = expon(mean_arrival);
        process_list[i].BT = arr[i]/2500000000;
        process_list[i].priority = rand();
    }
    int ch;
    cout<<"Scheduling algorithm:"<<endl;
    cout<<"1.FCFS"<<endl;
    cout<<"2.SJF"<<endl;
    cout<<"3.RR"<<endl;
    cout<<"Enter choice:"<<endl;
    cout << "**********************************" << endl;
    cin>>ch;
    switch(ch)
    {
    case 1:
        algo=1;
        break;
    case 2:
        algo=2;
        break;
    case 3:
        algo=3;
        break;
    default:
        cout<<"Wrong choice";
    }

    for (i=0; i< num_process; i++)
        cout << i+1 << " " << process_list[i].AT << " " <<
        process_list[i].BT << " " <<
        process_list[i].priority << endl;
    cout<<endl;
    cout<<count-1<<" Tasks are retrieved from the file"<<endl;
    cout<<"Press Enter to start simulation:"<<endl;
    cout << "**********************************" << endl;
    cin.ignore();
    cin.ignore();
        cout << "Simulation starts." << endl;
        cout << "Time = 0.0" << endl;

    nxt_aps = get_next_arriving_process(num_process);

    next_arrival = sim_time + process_list[nxt_aps].AT;

    next_departure = 1.0e+30;
    qsize = 0;
    server_status = IDLE;
}

void remove_from_list(int idx){

    int i;
    for (i=idx+1; i< listsize; i++){
            process_list[i-1].pid = process_list[i].pid;
        process_list[i-1].AT = process_list[i].AT;
        process_list[i-1].BT = process_list[i].BT;
        process_list[i-1].priority = process_list[i].priority;
    }
    listsize--;
}

void remove_from_readyq(int idx){

    int i;
    for (i=idx+1; i< qsize; i++){
            ready_q[i-1].pid = ready_q[i].pid;
        ready_q[i-1].AT = ready_q[i].AT;
        ready_q[i-1].BT = ready_q[i].BT;
        ready_q[i-1].priority = ready_q[i].priority;
    }
    qsize--;
}

int get_next_arriving_process(int n){

    float min_AT = process_list[0].AT;
    int min_idx = 0;
    int i;

    for (i=1; i< n; i++)
        if (process_list[i].AT < min_AT){
        min_AT = process_list[i].AT;
        min_idx = i;
        }
        return min_idx;
    }



int get_nxt_run_process(int algorithm){

    int i;
    float min_value;
    int  min_idx;
    float timeQuantum=2;
    switch (algorithm){
        case 1:
        min_value = ready_q[0].BT;
        min_idx = 0;
        for (i= 1; i < qsize; i++){
            min_value = ready_q[i].BT;
            min_idx = i;
        }
        break;
        case 2:
        min_value = ready_q[0].BT;
        min_idx = 0;
        for (i= 1; i < qsize; i++){
            if (ready_q[i].BT < min_value){
            min_value = ready_q[i].BT;
            min_idx = i;
            }
        }
        break;
        case 3:
        min_value = ready_q[0].BT;
        min_idx = 0;
        for (i= 1; i < qsize; i++){
            min_value = ready_q[i].BT-timeQuantum;
            min_idx = i;
        }
        break;
    }
    return min_idx;
}


float expon(float mean){

    float u, x;


    x = rand();

    u = x / RAND_MAX;

    return (-mean * log(u));
}

void printstat(int n){
    int i;
    float sum_WT, sum_TT;

        sum_WT = 0.0;
        sum_TT = 0.0;
        for (i=0; i < n; i++){
            cout << "PID  = " << process_stat[i].pid << ". ";
            cout << "A.T. = " << process_stat[i].AT << ". ";
            cout << "B.T. = " << process_stat[i].BT << ". ";
            cout << "prio = " << process_stat[i].priority << endl;
            cout << "          E.T. = " << process_stat[i].ET << ". ";
            cout << "W.T. = " << process_stat[i].WT << ". ";
            cout << "T.T. = " << process_stat[i].TT << endl;
            sum_WT = sum_WT + process_stat[i].WT;
            sum_TT = sum_TT + process_stat[i].TT;
        }
        cout << "Average process waiting time = " << sum_WT / n << endl;
        cout << "Average process turnaround time = " << sum_TT / n << endl;

}
