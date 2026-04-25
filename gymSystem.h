#ifndef GYMSYSTEM_H
#define GYMSYSTEM_H

#include "InterfaceMenu.h"
#include "adminMenu.h"
#include "userMenu.h"
#include <string>

class GymSystem {
private:
    InterfaceMenu* currentMenu;
    void loadAllData();
    void saveAllData();

public:
    GymSystem();
    ~GymSystem();

    void run();
    void showStartMenu();

    int  adminLogin();
    string memberLogin();                      //returns member ID if successful, "" if failed
};

#endif