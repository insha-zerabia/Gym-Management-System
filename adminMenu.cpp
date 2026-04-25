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
        cout << "    ATTENDANCE MANAGEMENT\n";
        cout << " 1. View All Attendance Records\n";
        cout << " 2. Generate Summary\n";
        cout << " 3. Manual Check-In for Member\n";
        cout << " 4. Manual Check-Out for Member\n";
        cout << " 0. Back\n";
        cout << " Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            attendance.viewAllAttendance();
            system("pause");
        }
        else if (choice == 2)
        {
            attendance.generateSummary();
            system("pause");
        }
        else if (choice == 3)
        {
            string id;
            cout << "Enter Member ID to check in: ";
            cin >> id;
            attendance.checkIn(id);
            system("pause");
        }
        else if (choice == 4)
        {
            string id;
            cout << "Enter Member ID to check out: ";
            cin >> id;
            attendance.checkOut(id);
            system("pause");
        }

    } while (choice != 0);
}