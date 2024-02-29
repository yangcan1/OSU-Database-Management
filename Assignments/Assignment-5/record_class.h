/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  
/* This record_class.h contains the class Records, which can be used to store tuples form Emp.csv (stored
in the EmpRecords) and Dept.csv (Stored in DeptRecords) files.
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include <fstream>
#include <stdio.h>

using namespace std;

struct EmpRecord {
    int eid;
    string ename;
    int age;
    double salary;
    int no_values = 0;
    void print() {
        cout << "EID: " << eid << " | Ename: " << ename << " | Age: " << age << " | Salary: " << salary << endl;
    }
};

struct DeptRecord {
    int did;
    string dname;
    int budget;
    int managerid;
    int no_values = 0;
    void print() {
        cout << "DID: " << did << " | Dname: " << dname << " | Budget: " << budget << " | ManagerID: " << managerid << endl;
    }
};

class Records{
public:
    EmpRecord empRecord;
    DeptRecord deptRecord;

    int no_values = 0; 
    int number_of_emp_records = 0;
    int number_of_dept_records = 0;
};

// Grab a single block from the Emp.csv file and put it inside the EmpRecord structure of the Records Class
EmpRecord Grab_Emp_Record(string empin) {
    string line, word;
    EmpRecord emp;
    // grab entire line
    if (empin != "") {
        stringstream s(empin);
        getline(s, line);
        stringstream ss(line);
        // grab each word
        getline(ss, word, ',');
        emp.eid = stoi(word);
        getline(ss, word, ',');
        emp.ename = word;
        getline(ss, word, ',');
        emp.age = stoi(word);
        getline(ss, word, ',');
        emp.salary = stod(word);
        emp.no_values = 1;
        return emp;
    } 
    else {
        emp.no_values = -1;
        return emp;
    }
}

// Grab a single block from the Dept.csv file and put it inside the DeptRecord structure of the Records Class
DeptRecord Grab_Dept_Record(string &deptin) {
    string line, word;
    DeptRecord dept;
    // grab entire line
    if (deptin != "") {
        stringstream s(deptin);
        getline(s, line);
        stringstream ss(line);
        // grab each word
        getline(ss, word, ',');
        dept.did = stoi(word);
        getline(ss, word, ',');
        dept.dname = word;
        getline(ss, word, ',');
        dept.budget = stoi(word);
        getline(ss, word, ',');
        dept.managerid = stoi(word);
        dept.no_values = 1;
        return dept;
    } 
    else {
        dept.no_values = -1;
        return dept;
    }
}

void removeTempFiles() {
    remove("empRun1.csv");
    remove("empRun2.csv");
    remove("deptRun.csv");
    remove("Join.csv");
}
