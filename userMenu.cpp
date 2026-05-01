#include "userMenu.h"
#include "attendance.h"
#include "userAccount.h"
#include "trainer.h"
#include "workout.h"
#include "plan.h"
#include "payment.h"
#include <iostream>
using namespace std;

UserMenu::UserMenu(string memberId,
    AttendanceManager* att, UserAccount* mem,
    TrainerManager* tr, WorkoutManager* wo,
    PlanManagement* pl, PaymentManagement* pay)
{
    running = true;
    loggedInMemberId = memberId;
    attendance = att;
    members = mem;
    trainers = tr;
    workouts = wo;
    plans = pl;
    payments = pay;
}

UserMenu::~UserMenu() {}

void UserMenu::showMenu()
{
    system("cls");
    cout << "         MEMBER PORTAL          \n";
    cout << "  Logged in as: " << loggedInMemberId << "\n";
    cout << "================================\n";
    cout << " 1. View My Profile\n";
    cout << " 2. View My Membership Plan\n";
    cout << " 3. View My Trainer\n";
    cout << " 4. View My Workout\n";
    cout << " 5. View My Payments\n";
    cout << " 6. Mark Attendance\n";
    cout << " 0. Logout\n";
    cout << " Choice: ";
}

void UserMenu::handleInput()
{
    running = true;
    int choice;

    do {
        showMenu();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        switch (choice)
        {
        case 1: viewMyProfile();  break;
        case 2: viewMyPlan();     break;
        case 3: viewMyTrainer();  break;
        case 4: viewMyWorkout();  break;
        case 5: viewMyPayments(); break;
        case 6: markAttendance(); break;
        case 0: running = false;  break;
        default:
            cout << " Invalid choice.\n";
            system("pause");
        }
    } while (running);
}

void UserMenu::viewMyProfile()
{
    system("cls");
    cout << "           MY PROFILE           \n";
    members->showMemberOwnProfile(loggedInMemberId);  //uses displayOwnProfile,no password shown
    system("pause");
}

void UserMenu::viewMyPlan()
{
    system("cls");
    cout << "       MY MEMBERSHIP PLAN       \n";
    plans->viewMemberPlan(loggedInMemberId);
    system("pause");
}

void UserMenu::viewMyTrainer()
{
    system("cls");
    cout << "           MY TRAINER           \n";
    trainers->viewMemberTrainer(loggedInMemberId);   // calls Zymal's function
    system("pause");
}

void UserMenu::viewMyWorkout()
{
    system("cls");
    cout << "         MY WORKOUT PLAN        \n";
    workouts->viewMemberWorkout(loggedInMemberId);   // calls Zymal's function
    system("pause");
}

void UserMenu::viewMyPayments()
{
    system("cls");
    cout << "        MY PAYMENT HISTORY      \n";
    payments->showPaymentHistory(loggedInMemberId);
    system("pause");
}

void UserMenu::markAttendance()
{
    int choice;
    do {
        system("cls");
        cout << "           ATTENDANCE           \n";
        cout << " 1. Check In\n";
        cout << " 2. Check Out\n";
        cout << " 3. View My Attendance History\n";
        cout << " 0. Back\n";
        cout << " Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            attendance->checkIn(loggedInMemberId);
            system("pause");
        }
        else if (choice == 2)
        {
            attendance->checkOut(loggedInMemberId);
            system("pause");
        }
        else if (choice == 3)
        {
            attendance->viewMemberAttendance(loggedInMemberId);
            system("pause");
        }
        else if (choice != 0)
        {
            cout << " Invalid choice.\n";
            system("pause");
        }
    } while (choice != 0);
}