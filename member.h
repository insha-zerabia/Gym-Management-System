#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using namespace std;

class Member
{
private:
	int age;
	string name;
	string memberId;
	string phoneNumber;
	string membershipType;
	string password;
public:
	Member(); //default
	Member(int age, string name, string memberId, string membershipType, string phoneNumber, string password);// parameterized
	Member(const Member& other);      // Copy constructor
	Member& operator=(const Member& other);  // Assignment operator
	~Member();//destructor

	// Setters
	void setAge(int);
	void setName(string);
	void setMemberId(string);
	void setPhoneNumber(string);
	void setMembershipType(string);
	void setPassword(string);


	//Getters
	int getAge() const;
	string getName() const;
	string getMemberId() const;
	string getPhoneNumber() const;
	string getMembershipType() const;
	string getPassword() const;

	void display() const;
	void update() const;
};

#endif
