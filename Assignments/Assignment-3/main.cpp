/*
Skeleton code for linear hash indexing
*/

#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "classes.h"
using namespace std;


int main(int argc, char* const argv[]) {
    int quitOrNot = 1;
    int lookupID;

    // Create the index
    LinearHashIndex emp_index("EmployeeIndex");
    emp_index.createFromFile("Employee.csv");
    
    // Loop to lookup IDs until user is ready to quit
    while (quitOrNot == 1) {
        cout << "Please enter an ID to look up: ";
        if (cin >> lookupID) {
        } else {
            cin.clear();  // Clear error state
            perror("Invalid input");
            exit(1);
        }
        Record record = emp_index.findRecordById(lookupID);
        cout << endl;
        record.print();
        cout << "\nDo you want to look up for another ID? (1 for yes, 0 for no): ";
        cin >> quitOrNot;
        if (quitOrNot == 0) {
            cout << "Thank you, goodbye!\n";
        }
    }


    return 0;
}
