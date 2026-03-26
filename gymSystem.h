#ifndef GYMSYSTEM_H
#define GYMSYSTEM_H

#include "member.h"
#include "trainer.h"
#include "plan.h"
#include "payment.h"
#include "workout.h"
#include "attendance.h"

class GymSystem {
public:
    GymSystem();

    void loadAllData();
    void saveAllData();

    void run();               
    void showStartMenu();                                    //Admin/User
    void adminMenu();
    void memberMenu();

    //part of module 1,2,3
    void handleMemberManagement();
    void handleTrainerManagement();
    void handlePlanAndPayment();
    void handleWorkoutManagement();
    void handleAttendance();

    // login
    bool adminLogin();
    bool memberLogin();

private:

};

#endif