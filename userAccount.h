#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include"member.h"
#include<string>

class UserAccount
{
private:
	Member** members;
	int memberCount;

public:
	UserAccount(); //default
	UserAccount(Member** men, string, string);

	//functions
	void addMember();
	void displayMember();
	void updateMember();
	void deleteMember();
	void searchMember(string);

	~UserAccount();


};





#endif