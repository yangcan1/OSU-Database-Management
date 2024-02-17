#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
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


class LinearHashIndex {

private:
    const int BLOCK_SIZE = 4096;

    vector<int> blockDirectory; // Map the least-significant-bits of h(id) to a bucket location in EmployeeIndex (e.g., the jth bucket)
                                // can scan to correct bucket using j*BLOCK_SIZE as offset (using seek function)
								// can initialize to a size of 256 (assume that we will never have more than 256 regular (i.e., non-overflow) buckets)
    int n;  // The number of indexes in blockDirectory currently being used
    int i;	// The number of least-significant-bits of h(id) to check. Will need to increase i once n > 2^i
    int numRecords;    // Records currently in index. Used to test whether to increase n
    int currentSize;   // Current size of index file
    int rec_size= 0; // Size of a record
    int nextFreeBlock; // Next place to write a bucket. Should increment it by BLOCK_SIZE whenever a bucket is written to EmployeeIndex
    string fName;      // Name of index file

    // Insert new record into index
    void writeRecord(Record record, int block) {
        // Write record to block
        // Update blockDirectory
        // Update currentSize
        // Update nextFreeBlock
    }

    void insertRecord(Record record) {

        // No records written to index yet
        if (rec_size + currentSize > BLOCK_SIZE) {
            // Need to increase n
            // Need to increase i
            // Need to create new bucket
            // Need to rehash records
        }

        // Add record to the index in the correct block, creating a overflow block if necessary


        // Take neccessary steps if capacity is reached:
		// increase n; increase i (if necessary); place records in the new bucket that may have been originally misplaced due to a bit flip


    }

public:
    LinearHashIndex(string indexFileName) {
        n = 4; // Start with 4 buckets in index
        i = 2; // Need 2 bits to address 4 buckets

        numRecords = 0;
        currentSize = 0;
        nextFreeBlock = 0;
        fName = indexFileName;
        blockDirectory.resize(256, -1); // Initialize all values to -1, indicating that the bucket has not been written to yet
        // Create your EmployeeIndex file and write out the initial 4 buckets
        // make sure to account for the created buckets by incrementing nextFreeBlock appropriately
      
    }

    // Read csv file and add records to the index
    void createFromFile(string csvFName) {
        ifstream file(csvFName);
        if (!file.is_open()) {
            perror("Error open");
            exit(1);
        }
        string line;
        while (getline(file, line)) {
            vector<string> fields;
            stringstream ss(line);
            string field;
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            Record record(fields);
            record.print();
            numRecords++;
            rec_size = sizeof(record);
            insertRecord(record);
        }
        
    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        
    }
};
