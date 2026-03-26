#ifndef GYMSYSTEM_H
#define GYMSYSTEM_H

class GymSystem {
public:
    GymSystem();

    void run();
    void showStartMenu();
    void adminMenu();
    void memberMenu();

    void handleMemberManagement();
    void handleTrainerManagement();
    void handlePlanAndPayment();
    void handleWorkoutManagement();
    void handleAttendance();

    int adminLogin();
    int memberLogin();
};

#endif