/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include <fstream>
#include <stdio.h>

#include "record_class.h"

using namespace std;

#define buffer_size 22
EmpRecord EmpBuffer1[buffer_size];
EmpRecord EmpBuffer2[buffer_size];
DeptRecord DeptBuffer[buffer_size];

bool compareEmp(const EmpRecord& a, const EmpRecord& b) {
    return a.eid < b.eid;
}

bool compareDept(const DeptRecord& a, const DeptRecord& b) {
    return a.managerid < b.managerid;
}

//Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs) 
void Sort_Buffer(string filename, int size, string sortBy) {
    if (filename == "empRun1.csv") {
        sort(EmpBuffer1, EmpBuffer1 + size, compareEmp);
        fstream empout;
        empout.open(filename, ios::out | ios::app);
        for (int i = 0; i < size; i++) {
            empout << EmpBuffer1[i].eid << "," << EmpBuffer1[i].ename << "," << EmpBuffer1[i].age << "," << EmpBuffer1[i].salary << endl;
        }
        empout.close();
    }
    else if (filename == "empRun2.csv") {
        sort(EmpBuffer2, EmpBuffer2 + size, compareEmp);
        fstream empout;
        empout.open(filename, ios::out | ios::app);
        for (int i = 0; i < size; i++) {
            empout << EmpBuffer2[i].eid << "," << EmpBuffer2[i].ename << "," << EmpBuffer2[i].age << "," << EmpBuffer2[i].salary << endl;
        }
        empout.close();
    }
    else if (filename == "deptRun.csv") {
        sort(DeptBuffer, DeptBuffer + size, compareDept);
        fstream deptout;
        deptout.open(filename, ios::out | ios::app);
        for (int i = 0; i < size; i++) {
            deptout << DeptBuffer[i].did << "," << DeptBuffer[i].dname << "," << DeptBuffer[i].budget << "," << DeptBuffer[i].managerid << endl;
        }
        deptout.close();
    }

}



//Use main memory to Merge and Join tuples 
//which are already sorted in 'runs' of the relations Dept and Emp 
void Merge_Join_Runs(){
   

    //and store the Joined new tuples using PrintJoin() 
    return;
}

int main() {
    fstream empin;
    fstream deptin;
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);
    EmpRecord emp;
    DeptRecord dept;
    string empin_str;
    string deptin_str;
    removeTempFiles();
    for (int i = 0; i < buffer_size; i++) {
        getline(empin, empin_str);
        emp = Grab_Emp_Record(empin_str);
        EmpBuffer1[i] = emp;
    }
    for (int i = 0; i < 8; i++) {
        getline(empin, empin_str);
        emp = Grab_Emp_Record(empin_str);
        EmpBuffer2[i] = emp;
    }
    for (int i = 0; i < buffer_size; i++) {
        getline(deptin, deptin_str);
        dept = Grab_Dept_Record(deptin_str);
        DeptBuffer[i] = dept;
    }
    Sort_Buffer("empRun1.csv", 22, "eid");
    Sort_Buffer("empRun2.csv", 8, "eid");
    Sort_Buffer("deptRun.csv", 15, "managerid");
    
    fstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);


    return 0;
}
