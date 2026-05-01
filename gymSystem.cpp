#include "gymSystem.h"
#include "adminMenu.h"
#include "userMenu.h"
#include <iostream>
using namespace std;

GymSystem::GymSystem() : currentMenu(nullptr), members("members.txt")
{
    // All managers load their own files in their constructors automatically
}

GymSystem::~GymSystem()
{
    if (currentMenu != nullptr)
    {
        delete currentMenu;
        currentMenu = nullptr;
    }
}

void GymSystem::loadAllData()
{
    // Each manager already loads data in its own constructor.
    // This function is a good place for a startup confirmation message.
    cout << "All data loaded successfully.\n";
}

void GymSystem::saveAllData()
{
    attendance.saveToFile();
    members.saveToFile();
    trainers.saveToFile();
    trainers.saveAssignments();
    workouts.saveToFile();
    workouts.saveAssignments();
    plans.savePlans();
    plans.saveAssignments();
    payments.savePayments();
    cout << "All data saved successfully.\n";
}

void GymSystem::showStartMenu()
{
    system("cls");
    cout << "    GYM MANAGEMENT SYSTEM       \n";
    cout << " 1. Login as Admin              \n";
    cout << " 2. Login as Member             \n";
    cout << " 0. Exit                        \n";
    cout << " Choice: ";
}


void GymSystem::run()
{
    loadAllData();
    int choice;

    do {
        showStartMenu();

        if (!(cin >> choice))   // handles letters or symbols typed by mistake
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        if (choice == 1)
        {
            if (adminLogin() == 1)
            {
                currentMenu = new AdminMenu(&attendance, &members,
                    &trainers, &workouts,
                    &plans, &payments);
                currentMenu->handleInput();
                delete currentMenu;
                currentMenu = nullptr;
            }
        }
        else if (choice == 2)
        {
            string memberId = memberLogin();
            if (memberId != "")
            {
                currentMenu = new UserMenu(memberId,
                    &attendance, &members,
                    &trainers, &workouts,
                    &plans, &payments);
                currentMenu->handleInput();
                delete currentMenu;
                currentMenu = nullptr;
            }
        }
        else if (choice != 0)
        {
            cout << "Invalid choice. Please enter 0, 1, or 2.\n";
            system("pause");
        }

    } while (choice != 0);

    saveAllData();
}


int GymSystem::adminLogin()
{
    string id, pass;
    system("cls");
    cout << "          ADMIN LOGIN           \n";
    cout << " ID       : "; cin >> id;
    cout << " Password : "; cin >> pass;

    if (id == "admin" && pass == "1234")
    {
        cout << "\n Login successful. Welcome, Admin!\n";
        system("pause");
        return 1;
    }
    cout << "\n Invalid credentials. Access denied.\n";
    system("pause");
    return 0;
}

string GymSystem::memberLogin()
{
    string id, pass;
    system("cls");
    cout << "         MEMBER LOGIN           \n";
    cout << " Member ID : "; cin >> id;
    cout << " Password  : "; cin >> pass;

    // Now calls Aiman's login() — no more hardcoded check
    Member* m = members.login(id, pass);
    if (m != nullptr)
    {
        system("pause");
        return id;
    }
    system("pause");
    return "";
}