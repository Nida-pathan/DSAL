/*Company maintains employee information as employee ID, name, designation and salary.
Allow user to add, delete information of employee. Display information of particular
employee. If employee does not exist an appropriate message is displayed. If it is, then
the system displays the employee details. Use index sequential file to maintain the data*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;

class EMP_CLASS
{
    typedef struct EMPLOYEE
    {
        char name[10];
        int emp_id;
        int salary;
    } Rec;

    typedef struct INDEX
    {
        int emp_id;
        int position;
    } Ind_Rec;

    Rec Records;
    Ind_Rec Ind_Records;

public:
    EMP_CLASS();
    void Create();
    void Display();
    void Update();
    void Delete();
    void Append();
    void Search();
};

EMP_CLASS::EMP_CLASS()
{
    strcpy(Records.name, "");
}

void EMP_CLASS::Create()
{
    int i = 0;
    char ch = 'y';
    fstream seqfile;
    fstream indexfile;
    indexfile.open("IND.DAT", ios::out | ios::binary);
    seqfile.open("EMP.DAT", ios::out | ios::binary);

    do
    {
        cout << "Enter Name: ";
        cin >> Records.name;
        cout << "Enter Emp_ID: ";
        cin >> Records.emp_id;
        cout << "Enter Salary: ";
        cin >> Records.salary;
        seqfile.write((char*)&Records, sizeof(Records));
        Ind_Records.emp_id = Records.emp_id;
        Ind_Records.position = i;
        indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
        i++;
        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Display()
{
    fstream seqfile, indexfile;
    seqfile.open("EMP.DAT", ios::in | ios::binary);
    indexfile.open("IND.DAT", ios::in | ios::binary);

    if (!seqfile || !indexfile)
    {
        cout << "Error opening files.\n";
        return;
    }

    cout << "\nEmployee Records:\n";
    cout << left << setw(10) << "Name" << setw(8) << "Emp_ID" << setw(8) << "Salary" << endl;

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        int pos = Ind_Records.position * sizeof(Rec);
        seqfile.seekg(pos, ios::beg);
        seqfile.read((char*)&Records, sizeof(Records));

        if (Records.emp_id != -1)
        {
            cout << left << setw(10) << Records.name
                 << setw(8) << Records.emp_id
                 << setw(8) << Records.salary << endl;
        }
    }

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Update()
{
    int id, pos = -1;
    char New_name[10];
    int New_salary;

    cout << "\nEnter Emp_ID to update: ";
    cin >> id;

    fstream seqfile("EMP.DAT", ios::in | ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::binary);

    if (!seqfile || !indexfile)
    {
        cout << "Error opening files.\n";
        return;
    }

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        if (Ind_Records.emp_id == id)
        {
            pos = Ind_Records.position;
            break;
        }
    }

    if (pos == -1)
    {
        cout << "Record not found.\n";
        return;
    }

    cout << "Enter new Name: ";
    cin >> New_name;
    cout << "Enter new Salary: ";
    cin >> New_salary;

    int offset = pos * sizeof(Rec);
    seqfile.seekp(offset, ios::beg);
    strcpy(Records.name, New_name);
    Records.emp_id = id;
    Records.salary = New_salary;
    seqfile.write((char*)&Records, sizeof(Records));
    cout << "Record updated.\n";

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Delete()
{
    int id, pos = -1;

    cout << "\nEnter Emp_ID to delete: ";
    cin >> id;

    fstream seqfile("EMP.DAT", ios::in | ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::out | ios::binary);

    if (!seqfile || !indexfile)
    {
        cout << "Error opening files.\n";
        return;
    }

    // Find and mark in index
    streampos index_pos;
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        index_pos = indexfile.tellg();
        if (Ind_Records.emp_id == id)
        {
            pos = Ind_Records.position;
            Ind_Records.emp_id = -1;
            break;
        }
    }

    if (pos == -1)
    {
        cout << "Record not found.\n";
        return;
    }

    // Mark in data file
    int offset = pos * sizeof(Rec);
    seqfile.seekp(offset, ios::beg);
    strcpy(Records.name, "");
    Records.emp_id = -1;
    Records.salary = -1;
    seqfile.write((char*)&Records, sizeof(Records));

    // Update index file
    indexfile.clear(); // clear EOF
    indexfile.seekp(index_pos - (streampos)sizeof(Ind_Records));
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));

    cout << "Record deleted.\n";

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Append()
{
    fstream seqfile("EMP.DAT", ios::app | ios::binary);
    fstream indexfile("IND.DAT", ios::app | ios::binary);
    int pos;

    ifstream countfile("IND.DAT", ios::binary | ios::ate);
    pos = countfile.tellg() / sizeof(Ind_Records);
    countfile.close();

    cout << "Enter Name: ";
    cin >> Records.name;
    cout << "Enter Emp_ID: ";
    cin >> Records.emp_id;
    cout << "Enter Salary: ";
    cin >> Records.salary;

    seqfile.write((char*)&Records, sizeof(Records));
    Ind_Records.emp_id = Records.emp_id;
    Ind_Records.position = pos;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));

    cout << "Record appended.\n";

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Search()
{
    int id, pos = -1;
    cout << "Enter Emp_ID to search: ";
    cin >> id;

    fstream indexfile("IND.DAT", ios::in | ios::binary);
    fstream seqfile("EMP.DAT", ios::in | ios::binary);

    if (!indexfile || !seqfile)
    {
        cout << "Error opening files.\n";
        return;
    }

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
    {
        if (Ind_Records.emp_id == id)
        {
            pos = Ind_Records.position;
            break;
        }
    }

    if (pos == -1)
    {
        cout << "Record not found.\n";
        return;
    }

    int offset = pos * sizeof(Records);
    seqfile.seekg(offset, ios::beg);
    seqfile.read((char*)&Records, sizeof(Records));

    if (Records.emp_id == -1)
    {
        cout << "Record not found.\n";
    }
    else
    {
        cout << "\nRecord found:\n";
        cout << "Name: " << Records.name << "\n";
        cout << "Emp_ID: " << Records.emp_id << "\n";
        cout << "Salary: " << Records.salary << "\n";
    }

    seqfile.close();
    indexfile.close();
}

int main()
{
    EMP_CLASS List;
    int choice;

    while (true)
    {
        cout << "\nMain Menu";
        cout << "\n1. Create";
        cout << "\n2. Display";
        cout << "\n3. Update";
        cout << "\n4. Delete";
        cout << "\n5. Append";
        cout << "\n6. Search";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: List.Create(); break;
        case 2: List.Display(); break;
        case 3: List.Update(); break;
        case 4: List.Delete(); break;
        case 5: List.Append(); break;
        case 6: List.Search(); break;
        case 7: return 0;
        default: cout << "Invalid choice.\n";
        }
    }

    return 0;
}
