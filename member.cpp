#include<iostream>
#include"member.h"
using namespace std;

//default
Member::Member() : age(0), name(), memberId(), phoneNumber(), membershipType(), password() {}

//parametrized constructor
Member::Member(int age, string name, string memberId, string phoneNumber, string membershipType, string password) :

    age(age),
    name(name),
    memberId(memberId),
    phoneNumber(phoneNumber),
    membershipType(membershipType),
    password(password)
{}


//copy constructor
Member::Member(const Member& other)
{
    age = other.age;
    name = other.name;
    memberId = other.memberId;
    phoneNumber = other.phoneNumber;
    membershipType = other.membershipType;
    password = other.password;
}

// Assignment operator
Member& Member::operator=(const Member& other)
{
    if (this != &other)
    {
        age = other.age;
        name = other.name;
        memberId = other.memberId;
        phoneNumber = other.phoneNumber;
        membershipType = other.membershipType;
        password = other.password;
    }
    return *this;
}
//destructor
Member::~Member() {}


//Setters
void Member::setAge(int newAge)
{
    age = newAge;
}

void Member::setName(string newName)
{
    name = newName;
}

void Member::setMemberId(string newId)
{
    memberId = newId;
}

void Member::setPhoneNumber(string newPhone)
{
    phoneNumber = newPhone;
}

void Member::setMembershipType(string newType)
{
    membershipType = newType;
}

void Member::setPassword(string newPassword)
{
    password = newPassword;
}

// Getters
int Member::getAge() const
{
    return age;
}

string Member::getName() const
{
    return name;
}

string Member::getMemberId() const
{
    return memberId;
}

string Member::getPhoneNumber() const
{
    return phoneNumber;
}

string Member::getMembershipType() const
{
    return membershipType;
}

string Member::getPassword() const
{
    return password;
}

// Display 
// (admin view, all fields, password hidden)
void Member::display() const
{
    cout << "---------------------------------------" << endl;
    cout << "Member ID      : " << memberId << endl;
    cout << "Name           : " << name << endl;
    cout << "Age            : " << age << endl;
    cout << "Phone Number   : " << phoneNumber << endl;
    cout << "Membership Type: " << membershipType << endl;
    cout << "Password       : ";
    for (int i = 0; i < (int)password.length(); i++)
    {
        cout << '*';
    }
    cout << endl;
    cout << "---------------------------------------" << endl;
}


// displayOwnProfile
// (user/member view, no password)
void Member::displayOwnProfile() const
{
    cout << "\n===== Your Profile =====" << endl;
    cout << "Member ID      : " << memberId << endl;
    cout << "Name           : " << name << endl;
    cout << "Age            : " << age << endl;
    cout << "Phone Number   : " << phoneNumber << endl;
    cout << "Membership Type: " << membershipType << endl;
    cout << "========================" << endl;
}

// update
void Member::update()
{
    int choice;
    cout << "\n--- Update Member Record ---" << endl;
    cout << "1. Name" << endl;
    cout << "2. Age" << endl;
    cout << "3. Phone Number" << endl;
    cout << "4. Membership Type" << endl;
    cout << "5. Password" << endl;
    cout << "6. Cancel" << endl;

    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
        cout << "New name: ";
        getline(cin, name);
        break;

    case 2:
        cout << "New age: ";
        cin >> age;
        cin.ignore();
        break;

    case 3:
        cout << "New phone number: ";
        getline(cin, phoneNumber);
        break;

    case 4:
        cout << "New membership type (Basic / Standard / Premium): ";
        getline(cin, membershipType);
        break;

    case 5:
    {
        string current;
        cout << "Current password: ";
        getline(cin, current);
        if (current == password)
        {
            string newPwd;
            cout << "New password    : ";
            getline(cin, newPwd);


            string confirm;
            cout << "Confirm password: ";
            getline(cin, confirm);

            if (newPwd == confirm)
            {
                password = newPwd;
                cout << "Password updated." << endl;
            }
            else
            {
                cout << "Passwords do not match. Update cancelled." << endl;
            }
        }
        else
        {
            cout << "Incorrect current password. Update cancelled." << endl;
        }
        break;
    }

    case 6:
        cout << "Update cancelled." << endl;
        break;

    default:
        cout << "Invalid choice." << endl;
    }
}