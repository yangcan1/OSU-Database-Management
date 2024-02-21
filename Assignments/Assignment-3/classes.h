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

    int h(int id) {
        int hash_value = id % 216;
        return hash_value;
    }

    int last_i_bits(int i, int hash_value) {
        int bits = hash_value % ((int)pow(2, i));
        cout << "----hash value: " << hash_value << "\nbits: " << bits << endl;
        return (bits);
    }

    void writeRecord(Record record, int lastBits, vector<int> blockDirectory, int rec_size) {

        // testing if there is existing records on that page
        char buffer[BLOCK_SIZE];
        memset(buffer, '\0', sizeof(buffer)); // Initialize buffer to empty

        fstream file_;
        file_.open(fName, ios::in | ios::out | ios::binary);
        file_.seekg(blockDirectory[lastBits], ios::beg);
        file_.read(buffer, BLOCK_SIZE);
        cout << "\nbuffer after reading: " << buffer << endl;
        file_.close();
        int buffer_length = strlen(buffer);
        std::cout << "length of buffer: " << buffer_length << std::endl;
        if (strlen(buffer) == 0) {
            cout << "\nbuffer is empty meaning so we're writing record into buffer:--" << endl;
            // write record in offeset blockDirectory[lastBits]
            fstream file;
            file.open(fName, ios::in | ios::out | ios::binary);
            file.seekp(blockDirectory[lastBits], ios::beg);
            file << record.id << "$" << record.name << "$" << record.bio << "$" << record.manager_id << "$";
            file.close();
            cout << "\nwriting record completed, name: " << record.name <<endl;
            memset(buffer, '\0', sizeof(buffer));
        }
        else {
            // buffer has something, we will insert the record behind it if ther's enough space
            if (buffer_length + rec_size < BLOCK_SIZE) {
                cout << "\n rec_size: " << rec_size << endl;
                fstream file;
                file.open(fName, ios::in | ios::out | ios::binary);
                file.seekp(blockDirectory[lastBits] + buffer_length, ios::beg);
                file << record.id << "$" << record.name << "$" << record.bio << "$" << record.manager_id << "$";
                file.close();
                cout << "\nBuffer ISN't empty, but luckly. writing record completed, name: " << record.name <<endl;
                memset(buffer, '\0', sizeof(buffer));
            } else {
                cout << "\nSorry we cannot fit this record, name: " << record.name <<endl;
                
            }
        }
    }

    void insertRecord(Record record) {
        // Get the hash value and the last i bits
        int hash_value = h(record.id);
        int lastBits = last_i_bits(i, hash_value);

        // if bucket is avaliable, write record to bucket
        cout << "insert loop count: "<< endl;
        if (lastBits <= n) {
            cout << "lastBits<= n counts: "<< endl;

            writeRecord(record, lastBits, blockDirectory, rec_size);
        } 
        else {
            // flip bits and write record to bucket

        }
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
        blockDirectory[0] = 0 * BLOCK_SIZE;
        blockDirectory[1] = 1 * BLOCK_SIZE;
        blockDirectory[2] = 2 * BLOCK_SIZE;
        blockDirectory[3] = 3 * BLOCK_SIZE;
        ofstream file(indexFileName);
        file.close();
      
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
            numRecords++;
            rec_size = 8 + 8 + record.name.size() + record.bio.size() + 5;
            insertRecord(record);
        }
        
    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        
    }
};
