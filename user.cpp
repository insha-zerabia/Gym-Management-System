#include "user.h"
#include <iostream>
using namespace std;

User::User() : username(""), password("") {}

User::User(string u, string p) : username(u), password(p) {}

User::User(const User& o) : username(o.username), password(o.password) {}

User& User::operator=(const User& o)
{
    if (this != &o) { username = o.username; password = o.password; }
    return *this;
}

User::~User() {}

string User::getUsername() const
{
    return username; 
}
string User::getPassword() const 
{
    return password; 
}
void   User::setUsername(string u)
{
    username = u; 
}
void   User::setPassword(string p) 
{
    password = p; 
}