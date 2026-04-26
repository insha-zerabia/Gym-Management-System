#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include"member.h"
#include<string>

class UserAccount
{

private:
    Member** members;       // dynamic array of Member pointers
    int      memberCount;   // current number of members
    int      capacity;      // allocated capacity of the array
    string   dataFile;      // file path for persistent storage

    // Internal helpers
    void     growArray();                        // doubles capacity when full
    int      findIndexById(string id) const;     // returns index or -1

    //File I/O 
    void loadFromFile();
    

public:
    void saveToFile() const;
    // Constructor / Destructor
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