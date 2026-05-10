#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include"member.h"
#include<string>

class UserAccount
{

private:
    Member** members;       
    int      memberCount;  
    int      capacity;      
    string   dataFile;      

    // Internal helpers
    void     growArray();                        
    int      findIndexById(string id) const;     

    //File I/O 
    void loadFromFile();
    

public:
    void showMemberOwnProfile(string id) const;
    void saveToFile() const;
    UserAccount(string filename = "members.txt");
    ~UserAccount();

    //Admin-side operations
    void addMember();
    void displayAllMembers()        const;
    void searchMember(string id)    const;
    void updateMember(string id);
    void deleteMember(string id);


    //User-side operations 
    // Returns pointer to the logged-in Member, or nullptr on failure
    Member* login(string id, string password) const;


    // Show the logged-in member's own profile
    void showOwnProfile(const Member* loggedIn) const;

    int  getMemberCount() const 
    {
        return memberCount; 
    }
    bool memberExists(const string& id) const
    {
        return findIndexById(id) != -1;
    }
};
#endif