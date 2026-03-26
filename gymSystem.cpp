#include "gymSystem.h"
#include <iostream>
using namespace std;

GymSystem::GymSystem() {
  
}

void GymSystem::run()
{
    int choice;
    do {
        showStartMenu();
        cin >> choice;

        if (choice == 1) {
            if (adminLogin() == 1) adminMenu();
        }
        else if (choice == 2) {
            if (memberLogin() == 1) memberMenu();
        }
    } while (choice != 0);
}

void GymSystem::showStartMenu() 
{
    system("cls");
    cout << "1. Login as Admin" << endl;
    cout << "2. Login as Member" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}

int GymSystem::adminLogin()
{
    char id[20], pass[20];
    cout << "\nID: "; cin >> id;
    cout << "Pass: "; cin >> pass;

    if (id[0] == 'a' && pass[0] == '1')                        //admin/1234 simple check
    { 
        cout << "Login successfully!" << endl;
        return 1;
    }
    cout << "can,t login";
    return 0;
}

int GymSystem::memberLogin()
{
    char id[20], pass[20];
    cout << "\nID: "; cin >> id;
    cout << "Pass: "; cin >> pass;

    if (id[0] == 'm' && pass[0] == '1')                        //member/1234 simple check
    {
        cout << "Login successfully!" << endl;
        return 1;
    }
    cout << "can,t login";
    return 0;
}

void GymSystem::adminMenu() 
{
    int choice;
    do {
        system("cls");
        cout << "  ADMIN  " << endl;
        cout << "1. Members" << endl;
        cout << "2. Trainers" << endl;
        cout << "3. Plans" << endl;
        cout << "4. Workouts" << endl;
        cout << "5. Attendance" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: "; cin >> choice;

        if (choice == 1) handleMemberManagement();
        else if (choice == 2) handleTrainerManagement();
        else if (choice == 3) handlePlanAndPayment();
        else if (choice == 4) handleWorkoutManagement();
        else if (choice == 5) handleAttendance();
    } while (choice != 0);
}

void GymSystem::memberMenu()
{
    cout << "\nWe need to write code for that ... " << endl;
    system("pause");
}

void GymSystem::handleMemberManagement()
{
    cout << "Members (Aiman)" << endl; system("pause");
}

void GymSystem::handleTrainerManagement()
{
    cout << "Trainers (Zymal)" << endl; system("pause");
}

void GymSystem::handlePlanAndPayment()
{
    cout << "Plans (Hanzala)" << endl; system("pause");
}

void GymSystem::handleWorkoutManagement()
{
    cout << "Workouts (Zymal)" << endl; system("pause");
}

void GymSystem::handleAttendance() 
{
    cout << "Attendance marked!" << endl; system("pause");
}