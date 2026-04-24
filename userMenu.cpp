#include "userMenu.h"
#include <iostream>
using namespace std;

UserMenu::UserMenu() 
{
    running = true;
    loggedInMemberId = "";
}

UserMenu::UserMenu(string memberId) 
{
    running = true;
    loggedInMemberId = memberId;
}

UserMenu::~UserMenu() {}

void UserMenu::showMenu() 
{
    system("cls");
    cout << "         MEMBER PORTAL" << endl;
    cout << " 1. View My Profile             " << endl;
    cout << " 2. View My Membership Plan     " << endl;
    cout << " 3. View My Trainer             " << endl;
    cout << " 4. View My Workout             " << endl;
    cout << " 5. View My Payments            " << endl;
    cout << " 6. Mark Attendance             " << endl;
    cout << " 0. Logout                      " << endl;
    cout << " Choice: ";
}

void UserMenu::handleInput()
{
    running = true;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1: viewMyProfile();   break;
        case 2: viewMyPlan();      break;
        case 3: viewMyTrainer();   break;
        case 4: viewMyWorkout();   break;
        case 5: viewMyPayments();  break;
        case 6: markAttendance();  break;
        case 0: running = false;   break;
        default:
            cout << "Don't chose beyond ur limits ..oops my limits." << endl;
            system("pause");
        }
    } while (running);
}

void UserMenu::viewMyProfile()
{
    cout << "\n[My Profile - Aiman's module goes here]\n";
    system("pause");
}

void UserMenu::viewMyPlan()
{
    cout << "\n[My Plan - Zemal's module goes here]\n";
    system("pause");
}

void UserMenu::viewMyTrainer() 
{
    cout << "\n[My Trainer - Zymal's module goes here]\n";
    system("pause");
}

void UserMenu::viewMyWorkout()
{
    cout << "\n[My Workout - Zymal's module goes here]\n";
    system("pause");
}

void UserMenu::viewMyPayments()
{
    cout << "\n[My Payments - Zemal's module goes here]\n";
    system("pause");
}

void UserMenu::markAttendance() 
{
    cout << "\n[Attendance]\n";
    system("pause");
}