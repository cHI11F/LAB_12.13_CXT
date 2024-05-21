#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Employee {
    string lastName;
    string phoneNumber;
    string roomNumber;

    Employee() : lastName(""), phoneNumber(""), roomNumber("") {}

    Employee(const string& ln, const string& pn, const string& rn)
        : lastName(ln), phoneNumber(pn), roomNumber(rn) {}
};

class ClosedHashTable {
private:
    static const size_t TABLE_SIZE = 100;
    vector<Employee> table[TABLE_SIZE];

    size_t hashFunction(const string& key) const {
        size_t hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return hash % TABLE_SIZE;
    }

public:
    void addEmployee(const Employee& emp) {
        size_t index = hashFunction(emp.phoneNumber);
        for (Employee& e : table[index]) {
            if (e.phoneNumber == emp.phoneNumber) {
                e = emp;  // Update existing employee
                return;
            }
        }
        table[index].push_back(emp);
    }

    void deleteEmployee(const string& phoneNumber) {
        size_t index = hashFunction(phoneNumber);
        vector<Employee>& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->phoneNumber == phoneNumber) {
                bucket.erase(it);
                cout << "Employee with phone number " << phoneNumber << " deleted successfully." << endl;
                return;
            }
        }
        cout << "Employee with phone number " << phoneNumber << " not found." << endl;
    }

    Employee* searchByPhoneNumber(const string& phoneNumber) const {
        size_t index = hashFunction(phoneNumber);
        const vector<Employee>& bucket = table[index];
        for (const Employee& e : bucket) {
            if (e.phoneNumber == phoneNumber) {
                return new Employee(e);
            }
        }
        return nullptr;
    }

    void saveToFile(const string& filename) const {
        ofstream fout(filename);
        if (!fout.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        for (const auto& bucket : table) {
            for (const auto& e : bucket) {
                fout << e.lastName << " " << e.phoneNumber << " " << e.roomNumber << endl;
            }
        }
        fout.close();
    }

    void readFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        string lastName, phoneNumber, roomNumber;
        while (fin >> lastName >> phoneNumber >> roomNumber) {
            addEmployee(Employee(lastName, phoneNumber, roomNumber));
        }
        fin.close();
    }
};

string filename;

void addEmployee(ClosedHashTable& phoneBook) {
    Employee newEmployee;
    cout << "Enter last name: ";
    cin >> newEmployee.lastName;
    cout << "Enter phone number (two digits): ";
    cin >> newEmployee.phoneNumber;
    cout << "Enter room number: ";
    cin >> newEmployee.roomNumber;

    phoneBook.addEmployee(newEmployee);
}

void deleteEmployee(ClosedHashTable& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number to delete: ";
    cin >> phoneNumber;

    phoneBook.deleteEmployee(phoneNumber);
}

void printEmployeeByPhoneNumber(const ClosedHashTable& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    Employee* employee = phoneBook.searchByPhoneNumber(phoneNumber);
    if (employee != nullptr) {
        cout << "Last name: " << employee->lastName << ", Room number: " << employee->roomNumber << endl;
        delete employee;
    }
    else {
        cout << "Employee with phone number " << phoneNumber << " not found." << endl;
    }
}

void savePhoneBookToFile(const ClosedHashTable& phoneBook) {
    phoneBook.saveToFile(filename);
    cout << "Phone book has been saved to file: " << filename << endl;
}

void readPhoneBookFromFile(ClosedHashTable& phoneBook) {
    phoneBook.readFromFile(filename);
    cout << "Phone book has been read from file: " << filename << endl;
}

int main() {
    ClosedHashTable phoneBook;

    cout << "Enter filename: ";
    cin >> filename;

    readPhoneBookFromFile(phoneBook);

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Delete employee" << endl;
        cout << "3. Print employee by phone number" << endl;
        cout << "4. Save phone book to file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee(phoneBook);
            break;
        case 2:
            deleteEmployee(phoneBook);
            break;
        case 3:
            printEmployeeByPhoneNumber(phoneBook);
            break;
        case 4:
            savePhoneBookToFile(phoneBook);
            break;
        case 5:
            cout << "Exiting program." << endl;
            savePhoneBookToFile(phoneBook);
            return 0;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
        }

        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}
