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
    const int BLOCK_SIZE = 4096 - 300; // initialize the  block size allowed in main memory according to the question 
    const int MAX_MEMORY_SIZE = 4096 * 3; // Three pages maximum in main memory 
    int rec_size = 0;
    // int memory_size = 0;
    int free_space_ptr = 0;
    int r_length, r_offset;
    tuple<int, int> entry = make_tuple(r_offset, r_length);
    int numRecords = 0;
    int page_rec_count = 0;
    string fileName;
    vector<tuple<int, int>> slot_directory;


    void insertRecord(Record record) {
        FILE *file = fopen(fileName.c_str(), "a+");

        // Write record to file
        fprintf(file, "%d$%s$%s$%d$", record.id, record.name.c_str(), record.bio.c_str(), record.manager_id);
        fflush(file); // Flush the buffer to ensure data is written to the file

        // Update slot directory
        free_space_ptr += rec_size;
        r_length = rec_size;
        r_offset = free_space_ptr - rec_size;
        entry = make_tuple(r_offset, r_length);
        slot_directory.push_back(entry);
        // slot_directory[0] = make_tuple(free_space_ptr, page_rec_count);

        // Check if block size is exceeded
        if (free_space_ptr + rec_size >= BLOCK_SIZE || numRecords == 50) {
            // Write slot directory to the end of the file
            fseek(file, -300, SEEK_END);
            for (int i = 0; i < slot_directory.size(); i++) {
                fprintf(file, "%d,%d.", get<0>(slot_directory[i]), get<1>(slot_directory[i]));
            }
            fprintf(file, "\n");
            fflush(file);

            // Clear slot directory and reset free_space_ptr
            slot_directory.clear();
            free_space_ptr = 0;
            page_rec_count = 0;
            r_offset = 0;
            
        }

        fclose(file);
    }


public:
    StorageBufferManager(string NewFileName) {
        fileName = NewFileName;
        // plug slot directory at the end of file
        FILE *file_ = fopen(NewFileName.c_str(), "w+");
        // cout << get<0>(index[0]) << " " << get<1>(index[0]) << endl;
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
            rec_size = 8 + 8 + record.name.size() + record.bio.size() + 5; // 4 is size of $ sign, and 1 is NULL terminator
            numRecords ++;
            page_rec_count ++;
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
        bool flag_exit = 0;

        FILE *file_ = fopen(fileName.c_str(), "r");
        if (file_ == NULL) {
            perror("Error opening file");
            exit(1);
        }

        char *token0;;
        while (flag_exit == 0 && fgets(buffer, MAX_MEMORY_SIZE, file_)) {
            // get fields from EmployeeRelation
            token0 = strtok(buffer, "$");
            while (token0) {
                if (atoi(token0) == id) {
                    // collect and push token0 to fields
                    for (int i = 0; i < 4; i++) {
                        fields.push_back(token0);
                        token0 = strtok(NULL, "$");
                    }
                    Record record(fields);
                    flag_exit = 1;
                    break;
                }
                else {
                    // continue check after passing next three $;
                    for (int i = 0; i < 4; i++) {
                        token0 = strtok(NULL, "$");
                    }
                }
            }
            memset(buffer, 0, MAX_MEMORY_SIZE);
        }
        fclose(file_);
        return Record(fields);
    }
};
