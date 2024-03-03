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

void Merge_Join_Runs(){
    fstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);
    int i=0,j=0, k=0;
    while (i<15)
    {
        if (DeptBuffer[i].managerid == EmpBuffer1[j].eid || DeptBuffer[i].managerid == EmpBuffer2[k].eid) {
            joinout << DeptBuffer[i].did << "," << DeptBuffer[i].dname << "," << DeptBuffer[i].budget << "," << DeptBuffer[i].managerid << "," << EmpBuffer1[j].eid << "," << EmpBuffer1[j].ename << "," << EmpBuffer1[j].age << "," << EmpBuffer1[j].salary << endl;
            i++;
            j++;
            continue;
        }
        for (int l = 0; l < 22; l++) {
            if (DeptBuffer[i].managerid == EmpBuffer1[l].eid) {
                joinout << DeptBuffer[i].did << "," << DeptBuffer[i].dname << "," << DeptBuffer[i].budget << "," << DeptBuffer[i].managerid << "," << EmpBuffer1[l].eid << "," << EmpBuffer1[l].ename << "," << EmpBuffer1[l].age << "," << EmpBuffer1[l].salary << endl;
                i++;
                break;
            }
        }
        for (int l = 0; l < 22; l++) {
            if (DeptBuffer[i].managerid == EmpBuffer2[l].eid) {
                joinout << DeptBuffer[i].did << "," << DeptBuffer[i].dname << "," << DeptBuffer[i].budget << "," << DeptBuffer[i].managerid << "," << EmpBuffer2[l].eid << "," << EmpBuffer2[l].ename << "," << EmpBuffer2[l].age << "," << EmpBuffer2[l].salary << endl;
                i++;
                break;
            }
        }
    }
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
    empin.close();
    deptin.close();

    Merge_Join_Runs();

    remove("empRun1.csv");
    remove("empRun2.csv");
    remove("deptRun.csv");
    


    return 0;
}
