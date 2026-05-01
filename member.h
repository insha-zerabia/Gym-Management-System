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
	Member(int age, string name, string memberId, string phoneNumber, string membershipType, string password);// parameterized
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

	// Display full record
	// (admin view — shows password hash marker, not plain text)
	void display() const;

	// Display own profile
	// (user/member view — no password shown)
	void displayOwnProfile() const;

	// Let the member interactively update their own fields
	void update() ;
};

#endif
