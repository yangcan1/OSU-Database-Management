/* This is a skeleton code for External Memory Sorting, you can make modifications as long as you meet 
   all question requirements*/  
/* This record_class.h contains the class Records, which can be used to store tuples form Emp.csv (stored
in the EmpRecord).
*/
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>

using namespace std;

class Records{
    public:
    struct EmpRecord {
        int eid;
        string ename;
        int age;
        long salary;
    }emp_record;

    int no_values = 0; //You can use this to check if you've don't have any more tuples
    int number_of_emp_records = 0; // Tracks number of emp_records you have on the buffer

    void print() {
        cout << "\teID: " << emp_record.eid << "\n";
        cout << "\tename: " << emp_record.ename << "\n";
        cout << "\tage: " << emp_record.age << "\n";
        cout << "\tsalary: " << emp_record.salary << "\n\n";
    }
};

// Grab a single block from the Emp.csv file and put it inside the EmpRecord structure of the Records Class
Records Grab_Emp_Record(string empin) {
    string line, word;
    Records emp;
    // grab entire line
    if (empin != "") {
        stringstream s(empin);
        getline(s, line);
        stringstream ss(line);
        // grab each word
        getline(ss, word, ',');
        emp.emp_record.eid = stoi(word);
        getline(ss, word, ',');
        emp.emp_record.ename = word;
        getline(ss, word, ',');
        emp.emp_record.age = stoi(word);
        getline(ss, word, ',');
        emp.emp_record.salary = stod(word);
        emp.no_values = 1;
        return emp;
    } 
    else {
        emp.no_values = -1;
        return emp;
    }
}