#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdio>
#include <fstream>
using namespace std;

class Record {
public:
    int id, manager_id;
    std::string bio, name;

    Record(vector<std::string> fields) {
        id = stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = stoi(fields[3]);
    }

    void print() {
        cout << "\tID: " << id << "\n";
        cout << "\tNAME: " << name << "\n";
        cout << "\tBIO: " << bio << "\n";
        cout << "\tMANAGER_ID: " << manager_id << "\n\n";
    }
};


class StorageBufferManager {

private:
    
    const int BLOCK_SIZE = 4096; // initialize the  block size allowed in main memory according to the question 

    // You may declare variables based on your need 
    int numRecords = 0;

    // Insert new record 
    void insertRecord(Record record) {

        // No records written yet
        if (numRecords == 0) {
            // Initialize first block

        }
        // Add record to the block


        // Take neccessary steps if capacity is reached (you've utilized all the blocks in main memory)


    }
 
public:
    StorageBufferManager(string NewFileName) {
        
        //initialize your variables
        char buffer[BLOCK_SIZE];

        // Create your EmployeeRelation file 
        FILE *file_ = fopen(NewFileName.c_str(), "w+");
        fputs("ID,NAME,BIO,MANAGER_ID\n", file_); 

        fclose(file_);

    }

    // Read csv file (Employee.csv) and add records to the (EmployeeRelation)
    void createFromFile(string csvFName) {
        FILE *file = fopen(csvFName.c_str(), "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(1);
        }

        vector<std::string> fields;
        char buffer[BLOCK_SIZE];
        while (fgets(buffer, BLOCK_SIZE, file)) {
            char* token = strtok(buffer, ",");
            // Store id, name. bio. manager_id
            fields.push_back(token);
            token = strtok(NULL, ",");
            fields.push_back(token);
            token = strtok(NULL, ",");
            fields.push_back(token);
            token = strtok(NULL, ",");
            fields.push_back(token);

            // Create record
            Record record(fields);
            numRecords++;
            insertRecord(record);

            // Clear buffer and fields
            memset(buffer, 0, BLOCK_SIZE);
            fields.clear();
        }
        fclose(file);
    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        
    }
};
