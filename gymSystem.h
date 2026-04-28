#ifndef GYMSYSTEM_H
#define GYMSYSTEM_H

#include "attendance.h"
#include "userAccount.h"
#include "trainer.h"
#include "workout.h"
#include "plan.h"
#include "payment.h"
#include <string>
using namespace std;

class InterfaceMenu;   

class GymSystem {
private:
    InterfaceMenu* currentMenu;

    //ONE copy of every manager shared with menus via pointers
    AttendanceManager attendance;
    UserAccount       members;
    TrainerManager    trainers;
    WorkoutManager    workouts;
    PlanManagement    plans;
    PaymentManagement payments;

    void loadAllData();
    void saveAllData();

public:
    GymSystem();
    ~GymSystem();

    void   run();
    void   showStartMenu();
    int    adminLogin();
    string memberLogin();
};

#endif