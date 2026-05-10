#include <iostream>
#include <fstream>
#include "userAccount.h"
using namespace std;

// reads and throws away characters until it hits '\n'
void flushInputLine()
{
    char ch;
    while (cin.get(ch) && ch != '\n')
    {
        // discard
    }
}


//convert a string of digit characters into an integer
bool stringToInt(const string& str, int& result)
{
    if (str.empty())
        return false;

    result = 0;
    for (int i = 0; i < (int)str.length(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;

        result = result * 10 + (str[i] - '0');
    }
    return true;
}


//extract one field from a line, reading up to the next '|' or end
bool extractField(const string& line, int& startPos, string& field)
{

    if (startPos >= (int)line.length())
        return false;

    field = "";   

    int i = startPos;
    while (i < (int)line.length() && line[i] != '|')
    {
        field += line[i];
        i++;
    }
    startPos = i + 1;
    return true;
}

// Constructor
UserAccount::UserAccount(string filename) : members(nullptr), memberCount(0), capacity(4), dataFile(filename) 
{
    members = new Member * [capacity];
    loadFromFile();
}
// Destructor
UserAccount::~UserAccount()
{
    saveToFile();
    for (int i = 0; i < memberCount; i++)
        delete members[i];
    delete[] members;
}

 
//growArray
void UserAccount::growArray()
{
    capacity *= 2;
    Member** newArr = new Member * [capacity];
    for (int i = 0; i < memberCount; i++)
        newArr[i] = members[i];
    delete[] members;
    members = newArr;
}

//findIndexById linear search, returns index or -1
int UserAccount::findIndexById(string id) const
{
    for (int i = 0; i < memberCount; i++)
        if (members[i]->getMemberId() == id)
            return i;
    return -1;
}


// FILE FORMAT  (members.txt)
void UserAccount::loadFromFile()
{
    ifstream fin(dataFile);
    if (!fin.is_open())
        return;  

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        int pos = 0;  
        string id, name, ageStr, phone, type, pwd;

        // extract all six fields one by one
        if (!extractField(line, pos, id))
        {
            continue;
        }
            
        if (!extractField(line, pos, name)) 
        {
            continue;
        }
        if (!extractField(line, pos, ageStr))
        {
            continue;
        }
        if (!extractField(line, pos, phone))
        {
            continue;
        }
        if (!extractField(line, pos, type)) 
        {
            continue;
        }
        if (!extractField(line, pos, pwd)) 
        {
            continue;
        }

        int age = 0;
        if (!stringToInt(ageStr, age))
        {
            cerr << "Warning: skipping bad record (invalid age): " << line << endl;
            continue;
        }

        if (memberCount == capacity)
            growArray();

        members[memberCount++] = new Member(age, name, id, phone, type, pwd);
    }

    fin.close();
}

// saveToFile  
// — writes every member back to members.txt
void UserAccount::saveToFile() const
{
    ofstream fout(dataFile);
    if (!fout.is_open())
    {
        cerr << "Error: could not open '" << dataFile << "' for writing." << endl;
        return;
    }

    for (int i = 0; i < memberCount; i++)
    {
        fout << members[i]->getMemberId() << '|'
            << members[i]->getName() << '|'
            << members[i]->getAge() << '|'
            << members[i]->getPhoneNumber() << '|'
            << members[i]->getMembershipType() << '|'
            << members[i]->getPassword() << '\n';
    }

    fout.close();
}


// addMember  
void UserAccount::addMember()
{
    string id, name, phone, type, pwd;
    int age = 0;

    flushInputLine();  

    cout << "\n--- Add New Member ---" << endl;

    cout << "Enter Member ID   : ";
    getline(cin, id);

    if (id.empty())
    {
        cout << "Error: Member ID cannot be empty." << endl;
        return;
    }
    if (findIndexById(id) != -1)
    {
        cout << "Error: Member ID '" << id << "' already exists." << endl;
        return;
    }

    cout << "Enter Name        : ";
    getline(cin, name);

    while (true)
    {
        cout << "Enter Age         : ";
        cin >> age;

        if (cin && age > 0 && age < 120)
        {
            flushInputLine();
            break;
        }

        cout << "Invalid age. Please enter a number between 1 and 119." << endl;
        cin.clear();
        flushInputLine();
    }

    cout << "Enter Phone Number: ";
    getline(cin, phone);

    cout << "Membership Type" << endl;
    cout << "  (1) Basic" << endl;
    cout << "  (2) Standard" << endl;
    cout << "  (3) Premium" << endl;
    cout << "Choice: ";
    int t = 0;
    cin >> t;
    flushInputLine();

    if (t == 1)
    {
        type = "Basic";
    }
    else if (t == 2)
    {
        type = "Standard";
    }
    else
    {
        type = "Premium";
    }

    cout << "Set Password      : ";
    getline(cin, pwd);

    if (memberCount == capacity)
        growArray();

    members[memberCount++] = new Member(age, name, id, phone, type, pwd);
    saveToFile();
    cout << "Member added successfully." << endl;
}

// displayAllMembers
void UserAccount::displayAllMembers() const
{
    if (memberCount == 0)
    {
        cout << "No members found." << endl;
        return;
    }
    cout << "\n===== All Members (" << memberCount << ") =====" << endl;
    for (int i = 0; i < memberCount; i++)
        members[i]->display();
}

// searchMember
void UserAccount::searchMember(string id) const
{
    int idx = findIndexById(id);
    if (idx == -1)
    {
        cout << "Member with ID '" << id << "' not found." << endl;
    }   
    else
    {
        members[idx]->display();
    }
}

// updateMember
void UserAccount::updateMember(string id)
{
    int idx = findIndexById(id);
    if (idx == -1)
    {
        cout << "Member with ID '" << id << "' not found." << endl;
        return;
    }
    members[idx]->update();
    saveToFile();
    cout << "Record saved." << endl;
}

// deleteMember
void UserAccount::deleteMember(string id)
{
    int idx = findIndexById(id);
    if (idx == -1)
    {
        cout << "Member with ID '" << id << "' not found." << endl;
        return;
    }

    cout << "Are you sure you want to delete member '"
        << members[idx]->getName() << "'? (y/n): ";

    char confirm;
    cin >> confirm;

    flushInputLine();

    if (confirm != 'y' && confirm != 'Y')
    {
        cout << "Delete cancelled." << endl;
        return;
    }

    delete members[idx];

    for (int i = idx; i < memberCount - 1; i++)
        members[i] = members[i + 1];

    memberCount--;
    saveToFile();
    cout << "Member deleted." << endl;
}


// login
Member* UserAccount::login(string id, string password) const
{
    int idx = findIndexById(id);
    if (idx == -1)
    {
        cout << "Login failed: ID not found." << endl;
        return nullptr;
    }
    if (members[idx]->getPassword() != password)
    {
        cout << "Login failed: Incorrect password." << endl;
        return nullptr;
    }
    cout << "Login successful. Welcome, " << members[idx]->getName() << "!" << endl;
    return members[idx];
}


// showOwnProfile
void UserAccount::showOwnProfile(const Member* loggedIn) const
{
    if (loggedIn == nullptr)
    {
        cout << "No member is currently logged in." << endl;
        return;
    }
    loggedIn->displayOwnProfile();
}

void UserAccount::showMemberOwnProfile(string id) const
{
    int idx = findIndexById(id);
    if (idx == -1)
    {
        cout << "Member not found.\n";
        return;
    }
    members[idx]->displayOwnProfile();
}