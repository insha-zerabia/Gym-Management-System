#include "adminMenu.h"
#include <iostream>
using namespace std;

AdminMenu::AdminMenu()
{
    running = true;
}

AdminMenu::~AdminMenu() {}

void AdminMenu::showMenu() 
{
    system("cls");
    cout << "         ADMIN PANEL" << endl;
    cout << " 1. Manage Members" << endl;
    cout << " 2. Manage Trainers" << endl;
    cout << " 3. Manage Plans & Payments" << endl;
    cout << " 4. Manage Workouts" << endl;
    cout << " 5. Attendance" << endl;
    cout << " 0. Logout" << endl;
    cout << " Choice: ";
}

void AdminMenu::handleInput()
{
    running = true;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1: manageMembersMenu();    break;
        case 2: manageTrainersMenu();   break;
        case 3: managePlansMenu();      break;
        case 4: manageWorkoutsMenu();   break;
        case 5: manageAttendanceMenu(); break;
        case 0: running = false;        break;
        default:
            cout << "Invalid choice. Try again." << endl;
            system("pause");
        }
    } while (running);
}

void AdminMenu::manageMembersMenu()
{
    //Aiman's module will be called here later
    cout << "\n[Members - Aiman's module goes here]\n";
    system("pause");
}

void AdminMenu::manageTrainersMenu() 
{
    // Zymal's module will be called here later
    cout << "\n[Trainers - Zymal's module goes here]\n";
    system("pause");
}

void AdminMenu::managePlansMenu() 
{
    // Zemal's module will be called here later
    cout << "\n[Plans & Payments - Zemal's module goes here]\n";
    system("pause");
}

void AdminMenu::manageWorkoutsMenu()
{
    // Zymal's module will be called here later
    cout << "\n[Workouts - Zymal's module goes here]\n";
    system("pause");
}

void AdminMenu::manageAttendanceMenu()
{
    int choice;
    do {
        system("cls");
        cout << " ATTENDANCE\n";
        cout << " 1. View all attendance\n";
        cout << " 2. Generate summary\n";
        cout << " 0. Back\n Choice: ";
        cin >> choice;
        if (choice == 1) { attendance.viewAllAttendance(); system("pause"); }
        if (choice == 2) { attendance.generateSummary();   system("pause"); }
    } while (choice != 0);
}