#define		_CRT_SECURE_NO_WARNINGS
#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include    <string>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char*, BST*);
int menu();

int main() {
    BST t1, clonet1;
    type studentquery;

    int choice;
    do {
        choice = menu();

        switch (choice) {
        case 1:
            //read file
            readFile("student.txt", &t1);
            break;

        case 2:
            if (t1.empty()) {
                cout << "Please go to option 1 for read file!\n";
            }
            t1.deepestNodes();
            break;

        case 3:
            int order, outputlocation;
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl;
            cin >> order;
            cout << "1.Output to Screen" << endl;
            cout << "2.Output to File" << endl;
            cin >> outputlocation;
            t1.display(order, outputlocation);
            break;
        case 4:
            clonet1 = BST();
            cout << "Enter ID: ";
            cin >> studentquery.id;
            if (!clonet1.CloneSubtree(t1, studentquery)) cout << "cannot clone sub tree!" << endl;
            break;
        case 5:
            if(!t1.printLevelNodes()) cout << "unable to print!" << endl;
            break;
        case 6:
            if(!t1.printPath()) cout << "unable to print!" << endl;
            break;

        case 7:
            //exit
            cout << "=========================================\n";
            cout << "Thanks for using our program! Goodbye~\n";
            cout << "=========================================\n";
            break;
        default:
            cout << "Invalid input! Please try again.\n";
        }


    } while (choice != 7);


    system("pause");
    return 0;
}

int menu() {
    int choice;
    do {
        cout << "===============";
        cout << "\nMain Menu\n";
        cout << "===============";
        cout << "\n1. Read data to BST\n2. Print deepest nodes\n3. Display student"
            << "\n4. Clone Subtree\n5. Print Level Nodes\n6. Print Path\n7. Exit\n";
        cout << "Please enter your choice(1-7): ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }
        if (choice < 1 || choice >7) {
            cout << "Invalid input! Please enter again.(1-7): ";
            cin >> choice;
        }
    } while (choice < 1 || choice >7);
    system("cls");
    return choice;
}

bool readFile(const char* filename, BST* t1) {
    ifstream infile(filename);
    string line;
    size_t pos;
    int linepos = 0, count = 0;
    Student s;

    if (!infile.is_open()) {
        cout << "The file does not exist!" << endl;
        return false;
    }

    while (getline(infile, line)) {
        if (line.find("Student Id") != string::npos) {
            pos = line.find('=');
            s.id = stoi(line.substr(pos + 2)); // convert string -> int
            linepos++;
        }
        else if (line.find("Name") != string::npos) {
            pos = line.find('=');
            strcpy(s.name, line.substr(pos + 2).c_str());
            linepos++;
        }
        else if (line.find("Address") != string::npos) {
            pos = line.find('=');
            strcpy(s.address, line.substr(pos + 2).c_str());
            linepos++;
        }
        else if (line.find("DOB") != string::npos) {
            pos = line.find('=');
            strcpy(s.DOB, line.substr(pos + 2).c_str());
            linepos++;
        }
        else if (line.find("Phone Number") != string::npos) {
            pos = line.find('=');
            strcpy(s.phone_no, line.substr(pos + 2).c_str());
            linepos++;
        }
        else if (line.find("Course") != string::npos) {
            pos = line.find('=');
            strcpy(s.course, line.substr(pos + 2).c_str());
            linepos++;
        }
        else if (line.find("CGPA") != string::npos) {
            pos = line.find('=');
            s.cgpa = stod(line.substr(pos + 2).c_str()); // convert string -> double
            linepos++;
        }

        // Once we have read all 7 fields -> insert into BST
        if (linepos == 7) {
            if (t1->insert(s)) {
                count++;
            }
            // reset for next student
            s = Student();
            linepos = 0;
        }
    }

    if (t1->empty()) {
        cout << "This file is empty or no valid records found.\n";
        return false;
    }
    //t1->inOrderPrint();
    cout << count << " student records successfully read into BST.\n";
    return true;
}