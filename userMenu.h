#pragma once
#ifndef USERMENU_H
#define USERMENU_H

#include "InterfaceMenu.h"
#include "attendance.h" 
#include <string>
using namespace std;

//INHERITS from IMenu
//Same parent but different behaviour -> POLYMORPHISM
class UserMenu : public InterfaceMenu {
private:
    bool running;
    string loggedInMemberId; 
    AttendanceManager attendance;

public:
    UserMenu();
    UserMenu(string memberId);                        //to know which member is logged in
    ~UserMenu();

    void showMenu() override;
    void handleInput() override;

    void viewMyProfile();
    void viewMyPlan();
    void viewMyTrainer();
    void viewMyWorkout();
    void viewMyPayments();
    void markAttendance();
};

#endif