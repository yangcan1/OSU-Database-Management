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
        cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};


class StorageBufferManager {

private:
    // Variables:
    const int BLOCK_SIZE = 4096; // initialize the  block size allowed in main memory according to the question 
    const int MAX_MEMORY_SIZE = 4096 * 3; // Three pages maximum in main memory 
    int rec_size = 0;
    int memory_size = 0;
    int numRecords = 0;
    string fileName;

    void insertRecord(Record record) {
        if (rec_size < MAX_MEMORY_SIZE) {
            FILE *file_ = fopen(fileName.c_str(), "a+");
            fprintf(file_, "%d,%s,%s,%d$\n", record.id, record.name.c_str(), record.bio.c_str(), record.manager_id);
            fclose(file_);
        }
    }

public:
    StorageBufferManager(string NewFileName) {
        fileName = NewFileName;

        FILE *file_ = fopen(NewFileName.c_str(), "w+");
        fclose(file_);

    }

    // Read csv file (Employee.csv) and add records to the (EmployeeRelation)
    void createFromFile(string csvFName) {
        vector<std::string> fields;
        char buffer[BLOCK_SIZE];

        FILE *file = fopen(csvFName.c_str(), "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(1);
        }

        while (fgets(buffer, BLOCK_SIZE, file)) {
            // get fields from Employee.csv
            char* token = strtok(buffer, ",");
            while (token) {
                fields.push_back(token);
                token = strtok(NULL, ",");
            }

            // Create record
            Record record(fields);
            rec_size = 8 + 8 + record.name.size() + record.bio.size();
            numRecords ++;
            insertRecord(record);

            // Clear buffer and fields
            memset(buffer, 0, BLOCK_SIZE);
            fields.clear();
        }

        fclose(file);
    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        vector<std::string> fields;
        char buffer[MAX_MEMORY_SIZE];

        FILE *file_ = fopen(fileName.c_str(), "r");
        if (file_ == NULL) {
            perror("Error opening file");
            exit(1);
        }

        char *token;
        while (fgets(buffer, MAX_MEMORY_SIZE, file_)) {
            // cout << buffer << endl;
            // get fields from EmployeeRelation
            char* token = strtok(buffer, ",");
            if (stoi(token) == id) {
                while (token) {
                    fields.push_back(token);
                    token = strtok(NULL, ",");
                }
                break;
            }
            memset(buffer, 0, MAX_MEMORY_SIZE);
        }
        // cout << fields.size() << endl;
        // cout << fields[0].length() << endl;
        fclose(file_);
        return Record(fields);
    }
};
