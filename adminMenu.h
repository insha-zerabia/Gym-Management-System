#pragma once
#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "InterfaceMenu.h"
#include "attendance.h"  

// AdminMenu INHERITS from IMenu
// This satisfies the INHERITANCE OOP requirement
class AdminMenu : public InterfaceMenu {
private:
    bool running;
    AttendanceManager attendance;
public:
    AdminMenu();
    ~AdminMenu();

    // These MUST be implemented because IMenu declared them pure virtual
    // This satisfies POLYMORPHISM
    void showMenu() override;
    void handleInput() override;

    // Admin-specific sub-menu handlers
    void manageMembersMenu();
    void manageTrainersMenu();
    void managePlansMenu();
    void manageWorkoutsMenu();
    void manageAttendanceMenu();
};

#endif