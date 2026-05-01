#pragma once
#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User();
    User(string username, string password);
    User(const User& other);
    User& operator=(const User& other);
    virtual ~User();

    string getUsername() const;
    string getPassword() const;
    void   setUsername(string u);
    void   setPassword(string p);

    virtual void displayDashboard() const = 0;   
    virtual string getRole()        const = 0;
};

#endif