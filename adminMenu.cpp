#include "adminMenu.h"
#include "attendance.h"
#include "userAccount.h"
#include "trainer.h"
#include "workout.h"
#include "plan.h"
#include "payment.h"
#include <iostream>
using namespace std;

AdminMenu::AdminMenu(AttendanceManager* att, UserAccount* mem,
    TrainerManager* tr, WorkoutManager* wo,
    PlanManagement* pl, PaymentManagement* pay)
{
    running = true;
    attendance = att;
    members = mem;
    trainers = tr;
    workouts = wo;
    plans = pl;
    payments = pay;
}

AdminMenu::~AdminMenu() {}

void AdminMenu::showMenu()
{
    system("cls");
    cout << "         ADMIN PANEL            \n\n\n\n\n";
    cout << "  Total Members  : " << members->getMemberCount() << "\n";
    cout << "  Total Trainers : " << trainers->getCount() << "\n";
    cout << " 1. Manage Members\n";
    cout << " 2. Manage Trainers\n";
    cout << " 3. Manage Plans & Payments\n";
    cout << " 4. Manage Workouts\n";
    cout << " 5. Attendance Management\n";
    cout << " 0. Logout\n";
    cout << " Choice: ";
}

void AdminMenu::handleInput()
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
        case 1: manageMembersMenu();    break;
        case 2: manageTrainersMenu();   break;
        case 3: managePlansMenu();      break;
        case 4: manageWorkoutsMenu();   break;
        case 5: manageAttendanceMenu(); break;
        case 0: running = false;        break;
        default:
            cout << " Invalid choice. Try again.\n";
            system("pause");
        }
    } while (running);
}

//MEMBER MANAGEMENT
void AdminMenu::manageMembersMenu()
{
    int choice;
    do {
        system("cls");
        cout << "      MEMBER MANAGEMENT         \n";
        cout << " 1. Add Member\n";
        cout << " 2. View All Members\n";
        cout << " 3. Search Member by ID\n";
        cout << " 4. Update Member\n";
        cout << " 5. Delete Member\n";
        cout << " 0. Back\n";
        cout << " Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            members->addMember();
            system("pause");
        }
        else if (choice == 2)
        {
            members->displayAllMembers();
            system("pause");
        }
        else if (choice == 3)
        {
            string id;
            cout << " Enter Member ID: "; cin >> id;
            members->searchMember(id);
            system("pause");
        }
        else if (choice == 4)
        {
            string id;
            cout << " Enter Member ID to update: "; cin >> id;
            members->updateMember(id);
            system("pause");
        }
        else if (choice == 5)
        {
            string id;
            cout << " Enter Member ID to delete: "; cin >> id;
            members->deleteMember(id);
            system("pause");
        }
        else if (choice != 0)
        {
            cout << " Invalid choice.\n";
            system("pause");
        }
    } while (choice != 0);
}

//TRAINER MANAGEMENT
void AdminMenu::manageTrainersMenu()
{
    int choice;
    do {
        system("cls");
        cout << "      TRAINER MANAGEMENT        \n";
        cout << "  1. Add Trainer\n";
        cout << "  2. View All Trainers\n";
        cout << "  3. View Active Trainers\n";
        cout << "  4. Search by ID\n";
        cout << "  5. Search by Name\n";
        cout << "  6. Update Trainer\n";
        cout << "  7. Deactivate Trainer\n";
        cout << "  8. Delete Trainer\n";
        cout << "  9. Assign Trainer to Member\n";
        cout << " 10. Change Trainer for Member\n";
        cout << " 11. Remove Trainer from Member\n";
        cout << " 12. View Member's Trainer\n";
        cout << "  0. Back\n";
        cout << " Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            trainers->addTrainer();
            system("pause");
        }
        else if (choice == 2)
        {
            trainers->viewAllTrainers();
            system("pause");
        }
        else if (choice == 3)
        {
            trainers->viewActiveTrainers();
            system("pause");
        }
        else if (choice == 4)
        {
            int id;
            cout << " Enter Trainer ID: "; cin >> id;
            trainers->searchTrainerByID(id);
            system("pause");
        }
        else if (choice == 5)
        {
            string keyword;
            cout << " Enter name keyword: "; cin >> keyword;
            trainers->searchTrainerByName(keyword);
            system("pause");
        }
        else if (choice == 6)
        {
            int id;
            cout << " Enter Trainer ID to update: "; cin >> id;
            trainers->updateTrainer(id);
            system("pause");
        }
        else if (choice == 7)
        {
            int id;
            cout << " Enter Trainer ID to deactivate: "; cin >> id;
            trainers->deactivateTrainer(id);
            system("pause");
        }
        else if (choice == 8)
        {
            int id;
            cout << " Enter Trainer ID to delete: "; cin >> id;
            trainers->deleteTrainer(id);
            system("pause");
        }
        else if (choice == 9)
        {
            string memberId; int tid;
            cout << " Enter Member ID   : "; cin >> memberId;
            cout << " Enter Trainer ID  : "; cin >> tid;
            trainers->assignTrainerToMember(memberId, tid);
            system("pause");
        }
        else if (choice == 10)
        {
            string memberId; int tid;
            cout << " Enter Member ID       : "; cin >> memberId;
            cout << " Enter New Trainer ID  : "; cin >> tid;
            trainers->changeTrainerForMember(memberId, tid);
            system("pause");
        }
        else if (choice == 11)
        {
            string memberId;
            cout << " Enter Member ID: "; cin >> memberId;
            trainers->removeTrainerFromMember(memberId);
            system("pause");
        }
        else if (choice == 12)
        {
            string memberId;
            cout << " Enter Member ID: "; cin >> memberId;
            trainers->viewMemberTrainer(memberId);
            system("pause");
        }
        else if (choice != 0)
        {
            cout << " Invalid choice.\n";
            system("pause");
        }
    } while (choice != 0);
}

//PLANS & PAYMENTS  (Zemal's module)
void AdminMenu::managePlansMenu()
{
    system("cls");
    cout << " Plans & Payments module is pending (Zemal's module).\n";
    cout << " This will be connected once plan.cpp and payment.cpp are complete.\n";
    system("pause");
}

//WORKOUT MANAGEMENT
void AdminMenu::manageWorkoutsMenu()
{
    int choice;
    do {
        system("cls");
        cout << "      WORKOUT MANAGEMENT        \n";
        cout << "  1. Add Workout Plan\n";
        cout << "  2. View All Workout Plans\n";
        cout << "  3. View Workout Detail\n";
        cout << "  4. Search Workout\n";
        cout << "  5. Update Workout\n";
        cout << "  6. Delete Workout\n";
        cout << "  7. Manage Days & Exercises\n";
        cout << "  8. Assign Workout to Member\n";
        cout << "  9. Change Member's Workout\n";
        cout << " 10. Remove Workout from Member\n";
        cout << " 11. View Member's Workout\n";
        cout << " 12. View All Member Schedules\n";
        cout << "  0. Back\n";
        cout << " Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            workouts->addWorkout();
            system("pause");
        }
        else if (choice == 2)
        {
            workouts->viewAllWorkouts();
            system("pause");
        }
        else if (choice == 3)
        {
            int id;
            cout << " Enter Workout ID: "; cin >> id;
            workouts->viewWorkoutDetail(id);
            system("pause");
        }
        else if (choice == 4)
        {
            string keyword;
            cout << " Enter keyword: "; cin >> keyword;
            workouts->searchWorkout(keyword);
            system("pause");
        }
        else if (choice == 5)
        {
            int id;
            cout << " Enter Workout ID to update: "; cin >> id;
            workouts->updateWorkout(id);
            system("pause");
        }
        else if (choice == 6)
        {
            int id;
            cout << " Enter Workout ID to delete: "; cin >> id;
            workouts->deleteWorkout(id);
            system("pause");
        }
        else if (choice == 7)
        {
            int id;
            cout << " Enter Workout ID to manage: "; cin >> id;
            workouts->manageDays(id);
        }
        else if (choice == 8)
        {
            string memberId; int wid;
            cout << " Enter Member ID   : "; cin >> memberId;
            cout << " Enter Workout ID  : "; cin >> wid;
            workouts->assignWorkoutToMember(memberId, wid);
            system("pause");
        }
        else if (choice == 9)
        {
            string memberId; int wid;
            cout << " Enter Member ID       : "; cin >> memberId;
            cout << " Enter New Workout ID  : "; cin >> wid;
            workouts->changeWorkoutForMember(memberId, wid);
            system("pause");
        }
        else if (choice == 10)
        {
            string memberId;
            cout << " Enter Member ID: "; cin >> memberId;
            workouts->removeWorkoutFromMember(memberId);
            system("pause");
        }
        else if (choice == 11)
        {
            string memberId;
            cout << " Enter Member ID: "; cin >> memberId;
            workouts->viewMemberWorkout(memberId);
            system("pause");
        }
        else if (choice == 12)
        {
            workouts->viewAllMemberSchedules();
            system("pause");
        }
        else if (choice != 0)
        {
            cout << " Invalid choice.\n";
            system("pause");
        }
    } while (choice != 0);
}

//ATTENDANCE MANAGEMENT
void AdminMenu::manageAttendanceMenu()
{
    int choice;
    do {
        system("cls");
        cout << "    ATTENDANCE MANAGEMENT       \n";
        cout << " 1. View All Attendance Records\n";
        cout << " 2. Generate Summary\n";
        cout << " 3. Manual Check-In for Member\n";
        cout << " 4. Manual Check-Out for Member\n";
        cout << " 5. View a Member's Attendance\n";
        cout << " 0. Back\n";
        cout << " Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            attendance->viewAllAttendance();
            system("pause");
        }
        else if (choice == 2)
        {
            attendance->generateSummary();
            system("pause");
        }
        else if (choice == 3)
        {
            string id;
            cout << " Enter Member ID to check in: "; cin >> id;
            attendance->checkIn(id);
            system("pause");
        }
        else if (choice == 4)
        {
            string id;
            cout << " Enter Member ID to check out: "; cin >> id;
            attendance->checkOut(id);
            system("pause");
        }
        else if (choice == 5)
        {
            string id;
            cout << " Enter Member ID: "; cin >> id;
            attendance->viewMemberAttendance(id);
            system("pause");
        }
        else if (choice != 0)
        {
            cout << " Invalid choice.\n";
            system("pause");
        }
    } while (choice != 0);
}