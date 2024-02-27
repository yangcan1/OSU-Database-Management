/* This is a skeleton code for External Memory Sorting, you can make modifications as long as you meet 
   all question requirements*/  

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include "record_class.h"
#include <algorithm>

using namespace std;
#define buffer_size 22
Records buffers[buffer_size]; //use this class object of size 22 as your main memory

int run = 0;
int flag = 0;


void PrintSorted(){

    //Store in EmpSorted.csv
    return;
}

bool compareByID(const Records& a, const Records& b) {
    return a.emp_record.eid < b.emp_record.eid;
}

//PASS 1
//Sorting the buffers in main_memory and storing the sorted records into a temporary file (Runs) 
void Sort_Buffer(Records buffers[buffer_size]){
    if (flag == 399) {
        sort(buffers, buffers + 3, compareByID);
        string filename = "runs18.txt";
        fstream runs;
        runs.open(filename, ios::in| ios::out | ios::app);
        for (int i = 0; i < 3; i++) {
            runs << buffers[i].emp_record.eid << "," << buffers[i].emp_record.ename << "," << buffers[i].emp_record.age << "," << buffers[i].emp_record.salary << "\n";
        }
        runs.close();
        run++;
        return;
    }
    sort(buffers, buffers + buffer_size, compareByID);
    // for (int i = 0; i < buffer_size; i++) {
    //     cout << "i: eID: " << i << ":" << buffers[i].emp_record.eid << "\n";
    // }
    string filename = "runs" + to_string(run) + ".txt";
    fstream runs;
    runs.open(filename, ios::in| ios::out | ios::app);
    for (int i = 0; i < buffer_size; i++) {
        runs << buffers[i].emp_record.eid << "," << buffers[i].emp_record.ename << "," << buffers[i].emp_record.age << "," << buffers[i].emp_record.salary << "\n";
    }
    runs.close();
    run++;

    return;
}

//PASS 2
//Use main memory to Merge the Runs 
//which are already sorted in 'runs' of the relation Emp.csv 
void Merge_Runs(){
    // 
    return;
}


int main() {
    //Open file streams to read and write
    //Opening out the Emp.csv relation that we want to Sort
    fstream empin;
    string line;
    int count = 0;

    empin.open("Emp.csv", ios::in);
    while (getline(empin, line))
    {
        Records records = Grab_Emp_Record(line);
        buffers[count] = records;
        flag++;
        count++;
        if (count == buffer_size || flag == 399){
            Sort_Buffer(buffers);
            count = 0;
        }
    }
    empin.close();

    //Creating the EmpSorted.csv file where we will store our sorted results
    fstream SortOut;
    SortOut.open("EmpSorted.csv", ios::out | ios::app);
    SortOut.close();

    return 0;
}
