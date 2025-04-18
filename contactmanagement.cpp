#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
using namespace std;

void menu();
void AddNumber();
void DisplayRecords();
void SearchBySrNo();
void deleteRecord();
void modifyRecord();
void intro();

class contact {
    int srno;
    char name[25];
    char mobile[15];
    char email[30];
    char address[50];
public:
    int getSrNo() { return srno; }
    void storeData() {
        cout << "\n...............CREATE NEW RECORD...............\n";
        cout << "Enter Serial Number : "; cin >> srno; cin.ignore();
        cout << "Enter Contact Name  : "; cin.getline(name, 25);
        cout << "Enter Mobile Number : "; cin.getline(mobile, 15);
        cout << "Enter E-Mail ID     : "; cin.getline(email, 30);
        cout << "Enter Address       : "; cin.getline(address, 50);
        cout << endl;
    }
    void showData() {
        cout << "\n............. CONTACT RECORD ...............\n";
        cout << "Sr. No.    : " << srno << endl;
        cout << "Name       : " << name << endl;
        cout << "Mobile No. : " << mobile << endl;
        cout << "Email ID   : " << email << endl;
        cout << "Address    : " << address << endl;
    }
} b;

void AddNumber() {
    ofstream fout("contact.dat", ios::binary | ios::app);
    if (!fout) {
        cout << "Error opening file!\n";
        return;
    }
    b.storeData();
    fout.write((char*)&b, sizeof(b));
    fout.close();
    cout << "\nRecord Saved to File......\n";
}

void DisplayRecords() {
    ifstream fin("contact.dat", ios::binary);
    if (!fin) {
        cout << "Error opening file!\n";
        return;
    }
    while (fin.read((char*)&b, sizeof(b))) {
        b.showData();
    }
    fin.close();
    cout << "\nReading of Data File Completed......\n";
}

void SearchBySrNo() {
    ifstream fin("contact.dat", ios::binary);
    if (!fin) {
        cout << "Error opening file!\n";
        return;
    }
    int n, flag = 0;
    cout << "Enter Serial Number of Record To Display: ";
    cin >> n;

    while (fin.read((char*)&b, sizeof(b))) {
        if (n == b.getSrNo()) {
            b.showData();
            flag++;
            cout << "\n\n.....Record Found and Displayed......\n";
            break;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "\nThe Record of Serial Number " << n << " is not in file....\n";
}

void deleteRecord() {
    ifstream fin("contact.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    if (!fin || !fout) {
        cout << "Error opening file!\n";
        return;
    }

    int n, flag = 0;
    cout << "Enter Serial Number of Record To Delete: ";
    cin >> n;

    while (fin.read((char*)&b, sizeof(b))) {
        if (n == b.getSrNo()) {
            cout << "\nThe Following record is deleted....\n";
            b.showData();
            flag++;
        } else {
            fout.write((char*)&b, sizeof(b));
        }
    }
    fin.close();
    fout.close();

    remove("contact.dat");
    rename("temp.dat", "contact.dat");

    if (flag == 0)
        cout << "\nThe Record of Serial Number " << n << " is not in file....\n";
    else
        cout << "\nRecord deleted successfully.\n";
}

void modifyRecord() {
    fstream fio("contact.dat", ios::in | ios::out | ios::binary);
    if (!fio) {
        cout << "Error opening file!\n";
        return;
    }

    int n, flag = 0;
    cout << "Enter Serial Number of Record To Modify: ";
    cin >> n;

    while (fio.read((char*)&b, sizeof(b))) {
        if (n == b.getSrNo()) {
            cout << "\nThe Following record will be modified....\n";
            b.showData();
            flag++;

            cout << "\nRe-Enter the New Details.....\n";
            b.storeData();

            fio.seekp(-sizeof(b), ios::cur);  // Move file pointer back
            fio.write((char*)&b, sizeof(b));
            cout << "\n....Data Modified Successfully....\n";
            break;
        }
    }
    fio.close();

    if (flag == 0)
        cout << "\nThe Record of Serial Number " << n << " is not in file....\n";
}

void intro() {
    cout << "\n---------------------------------------------";
    cout << "\n          CONTACT MANAGEMENT SYSTEM ";
    cout << "\n          MADE BY : SURBHI SHUKLA";
    cout << "\n---------------------------------------------\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void menu() {
    int ch;
    intro();
    do {
        system("cls");
        cout << "\n==============================";
        cout << "\n       CONTACT MANAGER";
        cout << "\n==============================\n";
        cout << "1. Save New Contact\n";
        cout << "2. Display All Contacts\n";
        cout << "3. Search Contact by Serial No.\n";
        cout << "4. Delete Contact\n";
        cout << "5. Modify Contact\n";
        cout << "6. Exit\n";
        cout << "Enter Your Choice : ";
        cin >> ch;
        cin.ignore();

        system("cls");
        switch (ch) {
            case 1: AddNumber(); break;
            case 2: DisplayRecords(); break;
            case 3: SearchBySrNo(); break;
            case 4: deleteRecord(); break;
            case 5: modifyRecord(); break;
            case 6:
                cout << "\nThank you for using Contact Management System!\n";
                exit(0);
            default:
                cout << "\nERROR! Invalid Choice. Try again.\n";
        }
        cout << "\nPress any key to continue...";
        getch();
    } while (true);
}

int main() {
    menu();
    return 0;
}
