#pragma once
#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "InterfaceMenu.h"
#include <string>
using namespace std;

// Forward declarations full headers are included in adminMenu.cpp
class AttendanceManager;
class UserAccount;
class TrainerManager;
class WorkoutManager;
class PlanManagement;
class PaymentManagement;

class AdminMenu : public InterfaceMenu {
private:
    bool running;

    // These point to managers owned by GymSystem — AdminMenu does NOT own them
    AttendanceManager* attendance;
    UserAccount* members;
    TrainerManager* trainers;
    WorkoutManager* workouts;
    PlanManagement* plans;
    PaymentManagement* payments;

public:
    AdminMenu(AttendanceManager* att, UserAccount* mem,TrainerManager* tr, WorkoutManager* wo,
        PlanManagement* pl, PaymentManagement* pay);
    ~AdminMenu();

    void showMenu()    override;
    void handleInput() override;

    void manageMembersMenu();
    void manageTrainersMenu();
    void managePlansMenu();
    void manageWorkoutsMenu();
    void manageAttendanceMenu();
};

#endif