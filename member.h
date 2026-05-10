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

	Member();
	Member(int age, string name, string memberId, string phoneNumber, string membershipType, string password);
	Member(const Member& other);     
	Member& operator=(const Member& other); 
	~Member();

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
	//(admin view
	void display() const;


	//Display own profile
	//member view — no password shown
	void displayOwnProfile() const;

	void update() ;
};

#endif
