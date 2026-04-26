#pragma once
#ifndef USERMENU_H
#define USERMENU_H

#include "InterfaceMenu.h"
#include <string>
using namespace std;

// Forward declarations — full headers are included in userMenu.cpp
class AttendanceManager;
class UserAccount;
class TrainerManager;
class WorkoutManager;
class PlanManagement;
class PaymentManagement;

class UserMenu : public InterfaceMenu {
private:
    bool   running;
    string loggedInMemberId;

    // These point to managers owned by GymSystem — UserMenu does NOT own them
    AttendanceManager* attendance;
    UserAccount* members;
    TrainerManager* trainers;
    WorkoutManager* workouts;
    PlanManagement* plans;
    PaymentManagement* payments;

public:
    UserMenu(string memberId,
        AttendanceManager* att, UserAccount* mem,
        TrainerManager* tr, WorkoutManager* wo,
        PlanManagement* pl, PaymentManagement* pay);
    ~UserMenu();

    void showMenu()    override;
    void handleInput() override;

    void viewMyProfile();
    void viewMyPlan();
    void viewMyTrainer();
    void viewMyWorkout();
    void viewMyPayments();
    void markAttendance();
};

#endif