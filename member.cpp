#include<iostream>
#include"member.h"
using namespace std;

//default
Member::Member() : age(0), name(), memberId(), phoneNumber(), membershipType(), password() {}

//parametrized
Member::Member(int age, string name, string memberId, string phoneNumber, string membershipType, string password) :

    age(age),
    name(name),
    memberId(memberId),
    phoneNumber(phoneNumber),
    membershipType(membershipType),
    password(password)
{
    // Empty body - initialization already done
}

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