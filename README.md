# Gym-Management-System
C++ Gym Management System implementing core OOP concepts and file handling to manage members, trainers, memberships, fees and reports for admin and users.

Module 1 (Handled by Aiman Nauman) – Member & User Account Management 
Files: member.h, member.cpp, maybe userAccount.h, userAccount.cpp 
Responsibilities: 
• Add, view, search, update, delete member records 
• Store member login credentials (ID + password) 
• Member login verification (for User side) 
• Show logged‑in member’s own profile and membership details 
• Read/write member data and login data from files 
Module 2 (Handled by Zymal Rizwan) – Trainer & Workout Management 
Files: trainer.h, trainer.cpp, workout.h, workout.cpp 
Responsibilities: 
• Add, view, update, delete trainer records 
• Assign/change trainer for a member 
• Create workout plans and assign them to members 
• View/update workout schedule for each member 
• For User side: show member’s assigned trainer + workout plan 
• Store/load trainer and workout data using files 
Module 3 (Handled by Hanzala Madni) – Membership Plan, Fee & Payment, Reports 
Files: plan.h, plan.cpp, payment.h, payment.cpp 
Responsibilities: 
• Create membership plans (name, duration, monthly fee) 
• Assign and modify membership plan for each member 
• Record monthly payments and maintain payment history 
• Check unpaid members and generate simple fee reports 
• For User side: show membership plan, last payment, and pending status 
• File handling for plans and payments 
• Member will first select the membership plan 
Module 4 (Handled by Insha Zerabia) – Core System, Menus, GUI, Attendance & Integration 
Files: gymSystem.h, gymSystem.cpp, attendance.h, attendance.cpp, main.cpp 
Responsibilities: 
• Design overall class structure and how all modules connect 
• Implement start screen: 
o Login as Admin / Login as User / Exit 
• Implement complete Admin menu (calling functions from all modules) 
• Implement complete User menu (profile, plan, trainer, workout, payments, 
attendance) 
• Handle navigation logic between all menus and sub‑menus 
• Implement attendance tracking (check‑in/check‑out, basic summary) 
• Coordinate all file loading/saving when program starts/exits 
• Make the interface more user‑friendly (menu layout or basic GUI elements) 
