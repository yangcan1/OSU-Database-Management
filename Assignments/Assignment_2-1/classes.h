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
    // Variables:
    const int BLOCK_SIZE = 4096; // initialize the  block size allowed in main memory according to the question 
    const int MAX_MEMORY_SIZE = 4096 * 3; // Three pages maximum in main memory 
    int rec_size = 0;
    int memory_size = 0;
    int numRecords = 0;
    string fileName;
    vector<Record> blocks;

    void insertRecord(Record record) {
        // if record size can be added to main memory:
        if (memory_size + rec_size <= MAX_MEMORY_SIZE) {
            memory_size += rec_size;
            // cout << memory_size << endl;
            blocks.push_back(record);
        } 
        // If record size is overload:
        if (numRecords == 50 || memory_size + rec_size > MAX_MEMORY_SIZE) {
            // cout << "Hello world" << endl;
            // blocks[1].print();

            FILE *file_ = fopen(fileName.c_str(), "a+");
            for (int i = 0; i < blocks.size(); i++) {
                fprintf(file_, "%d,%s,%s,%d$", blocks[i].id, blocks[i].name.c_str(), blocks[i].bio.c_str(), blocks[i].manager_id);
            }
            blocks.clear();
            memory_size = 0;
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
        cout << id+1 << endl;
        Record record = Record({"0", "0", "0", "0"});
        return record;
        }
};
