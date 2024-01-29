/*
Skeleton code for storage and buffer management
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
    // Create the EmployeeRelation file from Employee.csv
    StorageBufferManager manager("EmployeeRelation");
    manager.createFromFile("Employee.csv");
    
    // Loop to lookup IDs until user is ready to quit
    
    while (quitOrNot == 1) {
        cout << "Please enter an ID to look up: ";
        cin >> lookupID;
        Record record = manager.findRecordById(lookupID);
        record.print();
        cout << "\nDo you want to look up for another ID? (1 for yes, 0 for no): ";
        cin >> quitOrNot;
        if (quitOrNot == 0) {
            cout << "Thank you, goodbye!\n";
        }
    }
    

    return 0;
}
