#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include "user.h"
using namespace std;

class Member : public User
{
private:
	int age;
	string name;
	string memberId;
	string phoneNumber;
	string membershipType;

public:
		void displayDashboard() const override;
		string getRole() const override;

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


	//Getters
	int getAge() const;
	string getName() const;
	string getMemberId() const;
	string getPhoneNumber() const;
	string getMembershipType() const;

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
