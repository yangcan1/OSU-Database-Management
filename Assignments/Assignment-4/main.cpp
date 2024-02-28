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
#include <cstdio>

using namespace std;
#define buffer_size 22
Records buffers[buffer_size]; //use this class object of size 22 as your main memory

int run = 0;
int flag = 0;


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
void Merge_Runs() {
    vector<ifstream> runFiles(run);
    for (int i = 0; i < run; ++i) {
        string filename = "runs" + to_string(i) + ".txt";
        runFiles[i].open(filename);
    }

    // Open output file
    ofstream SortOut("EmpSorted.csv");

    // Initialize variables to store current record from each run file
    vector<Records> currentRecords(run);
    for (int i = 0; i < run; ++i) {
        string line;
        if (getline(runFiles[i], line)) {
            currentRecords[i] = Grab_Emp_Record(line);
        }
    }

    // Merge runs
    while (1) {
        // Find the smallest record
        Records smallestRecord;
        int smallestRecordIndex = -1;
        for (int i = 0; i < run; ++i) {
            if (!(currentRecords[i].no_values == -1)) {
                if (smallestRecordIndex == -1 || currentRecords[i].emp_record.eid < smallestRecord.emp_record.eid) {
                    smallestRecord = currentRecords[i];
                    smallestRecordIndex = i;
                }
            }
        }

        // If all runs are empty, break the loop
        if (smallestRecordIndex == -1) {
            break;
        }

        // Write smallest record to output file
        SortOut << smallestRecord.emp_record.eid << "," << smallestRecord.emp_record.ename << "," << smallestRecord.emp_record.age << "," << smallestRecord.emp_record.salary << "\n";

        // Read the next record from the run file from which smallest record was selected
        string line;
        if (getline(runFiles[smallestRecordIndex], line)) {
            currentRecords[smallestRecordIndex] = Grab_Emp_Record(line);
        } else {
            // If the run file is empty, mark the current record as empty
            currentRecords[smallestRecordIndex].no_values = -1;
        }
    }

    // Close all run files
    for (int i = 0; i < run; ++i) {
        runFiles[i].close();
    }

    // Close output file
    SortOut.close();
}


int main() {
    //Open file streams to read and write
    //Opening out the Emp.csv relation that we want to Sort
    fstream empin;
    string line;
    int count = 0;

    empin.open("Emp.csv", ios::in);

    for (int i = 0; i < 19; i++) {
        string fname = "runs" + to_string(i) + ".txt";
        remove(fname.c_str());
    }

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
    remove("EmpSorted.csv");
    Merge_Runs();
    // fstream SortOut;
    // SortOut.open("EmpSorted.csv", ios::out | ios::app);
    // SortOut.close();


    for (int i = 0; i < 19; i++) {
        string fname = "runs" + to_string(i) + ".txt";
        remove(fname.c_str());
    }

    return 0;
}
