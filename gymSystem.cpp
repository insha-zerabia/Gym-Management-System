#include "gymSystem.h"
#include <iostream>
using namespace std;

GymSystem::GymSystem()
{
    currentMenu = nullptr; 
}

GymSystem::~GymSystem() 
{
    if (currentMenu != nullptr)
    {
        delete currentMenu;
        currentMenu = nullptr;
    }
}

void GymSystem::run() 
{
    int choice;
    do {
        showStartMenu();
        cin >> choice;

        if (choice == 1)
        {
            if (adminLogin() == 1) 
            {
                currentMenu = new AdminMenu();
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
                currentMenu = new UserMenu(memberId);
                currentMenu->handleInput();

                delete currentMenu;
                currentMenu = nullptr;
            }
        }

    } while (choice != 0);
}

void GymSystem::showStartMenu()
{
    system("cls");
    cout << "    GYM MANAGEMENT SYSTEM       " << endl;
    cout << " 1. Login as Admin              " << endl;
    cout << " 2. Login as Member             " << endl;
    cout << " 0. Exit                        " << endl;
    cout << " Choice: ";
}

int GymSystem::adminLogin()
{
    string id, pass;
    system("cls");
    cout << "    Admin Login" << endl;
    cout << "ID:       "; cin >> id;
    cout << "Password: "; cin >> pass;

    // Temporary hardcoded check...will connect to file later
    if (id == "admin" && pass == "1234") {
        cout << "\nSuccessfully Logged in as Admin" << endl;
        system("pause");
        return 1;
    }
    cout << "\nInvalid credentials.Don't Scam me .." << endl;
    system("pause");
    return 0;
}

string GymSystem::memberLogin() 
{
    string id, pass;
    system("cls");
    cout << "    Member Login" << endl;
    cout << "Member ID: "; cin >> id;
    cout << "Password:  "; cin >> pass;

    //Temporary hardcoded check...Aiman will replace this when her file handling is done
    if (id == "M001" && pass == "1234") {
        cout << "\nLogin successful! Welcome." << endl;
        system("pause");
        return id;                                               //return the ID so UserMenu knows who logged in
    }
    cout << "\nInvalid credentials." << endl;
    system("pause");
    return ""; 
}