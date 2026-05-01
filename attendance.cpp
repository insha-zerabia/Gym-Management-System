#include "attendance.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

AttendanceRecord::AttendanceRecord()
    : memberId(""), date(""), checkInTime(""), checkOutTime(""), checkedOut(false) {}

AttendanceRecord::AttendanceRecord(string id, string d, string ci)
    : memberId(id), date(d), checkInTime(ci), checkOutTime(""), checkedOut(false) {}

AttendanceRecord::AttendanceRecord(const AttendanceRecord& o)
    : memberId(o.memberId), date(o.date), checkInTime(o.checkInTime),
    checkOutTime(o.checkOutTime), checkedOut(o.checkedOut) {}

AttendanceRecord& AttendanceRecord::operator=(const AttendanceRecord& o)
{
    if (this != &o)
    {
        memberId = o.memberId;
        date = o.date;
        checkInTime = o.checkInTime;
        checkOutTime = o.checkOutTime;
        checkedOut = o.checkedOut;
    }
    return *this;
}

AttendanceRecord::~AttendanceRecord() {}

// Setters
void AttendanceRecord::setMemberId(string id)
{
    memberId = id; 
}
void AttendanceRecord::setDate(string d)
{
    date = d; 
}
void AttendanceRecord::setCheckInTime(string t) 
{
    checkInTime = t; 
}
void AttendanceRecord::setCheckOutTime(string t)
{
    checkOutTime = t; 
}
void AttendanceRecord::setCheckedOut(bool val)
{
    checkedOut = val; 
}

// Getters
string AttendanceRecord::getMemberId()   const 
{
    return memberId; 
}
string AttendanceRecord::getDate()       const 
{
    return date; 
}
string AttendanceRecord::getCheckInTime()  const
{
    return checkInTime; 
}
string AttendanceRecord::getCheckOutTime() const 
{
    return checkOutTime; 
}
bool   AttendanceRecord::isCheckedOut()  const
{
    return checkedOut; 
}

void AttendanceRecord::display() const 
{
    cout << "Member: " << memberId << "  Date: " << date << "  In: " << checkInTime << "  Out: "
        << (checkedOut ? checkOutTime : "Still inside") << endl;
}

void AttendanceRecord::saveToFile(ofstream& ofs) const
{
    ofs << memberId << "\n"<< date << "\n"<< checkInTime << "\n"<< checkOutTime << "\n"<< checkedOut << "\n";
}

void AttendanceRecord::loadFromFile(ifstream& ifs)
{
    getline(ifs, memberId);
    getline(ifs, date);
    getline(ifs, checkInTime);
    getline(ifs, checkOutTime);
    ifs >> checkedOut;
    ifs.ignore();
}


AttendanceManager::AttendanceManager() : count(0)
{
    loadFromFile();
}
AttendanceManager::~AttendanceManager() {}

string AttendanceManager::getCurrentDate() const
{
    time_t now = time(nullptr);
    char buf[20];
    tm t;
    localtime_s(&t, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t);
    return string(buf);
}

string AttendanceManager::getCurrentTime() const 
{
    time_t now = time(nullptr);
    char buf[20];
    tm t;
    localtime_s(&t, &now);
    strftime(buf, sizeof(buf), "%H:%M:%S", &t);
    return string(buf);
}

void AttendanceManager::checkIn(string memberId)
{
    string today = getCurrentDate();                    //to check if already checked in today without checking out
    for (int i = count - 1; i >= 0; i--) {
        if (records[i].getMemberId() == memberId && records[i].getDate() == today && !records[i].isCheckedOut())
        {
            cout << "You are already checked in today at "
                << records[i].getCheckInTime() << endl;
            return;
        }
    }
    if (count >= 500) 
    {
        cout << "Attendance log full." << endl;
        return;
    }
    records[count] = AttendanceRecord(memberId, today, getCurrentTime());
    count++;
    cout << "Check-in recorded at " << getCurrentTime() << endl;
    saveToFile();
}

void AttendanceManager::checkOut(string memberId) 
{
    string today = getCurrentDate();
    for (int i = count - 1; i >= 0; i--)
    {
        if (records[i].getMemberId() == memberId &&records[i].getDate() == today && !records[i].isCheckedOut())
        {
            records[i].setCheckOutTime(getCurrentTime());
            records[i].setCheckedOut(true);
            cout << "Check-out recorded at " << getCurrentTime() << endl;
            saveToFile();
            return;
        }
    }
    cout << "No active check-in found for today. Please check in first." << endl;
}

void AttendanceManager::viewMemberAttendance(string memberId) const 
{
    cout << "\n    Attendance for Member: " << memberId << "  \n";
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (records[i].getMemberId() == memberId) 
        {
            records[i].display();
            found = true;
        }
    }
    if (!found) cout << "No attendance records found.\n";
}

void AttendanceManager::viewAllAttendance() const
{
    cout << "\n     All Attendance Records    \n";
    if (count == 0)
    {
        cout << "No records yet.\n";
        return; 
    }
    for (int i = 0; i < count; i++) 
        records[i].display();
}

void AttendanceManager::generateSummary() const
{
    cout << "\n    Attendance Summary\n";
    cout << "Total records: " << count << "\n";
    int inside = 0;
    for (int i = 0; i < count; i++)
        if (!records[i].isCheckedOut()) inside++;
    cout << "Currently inside gym: " << inside << "\n";
}

void AttendanceManager::saveToFile() const 
{
    ofstream ofs("attendance.txt");
    if (!ofs)
    {
        cout << "Error saving attendance.\n"; 
        return; 
    }
    ofs << count << "\n";
    for (int i = 0; i < count; i++) 
        records[i].saveToFile(ofs);
}

void AttendanceManager::loadFromFile()
{
    ifstream ifs("attendance.txt");
    if (!ifs) return;                                              //no file yet, start fresh
    ifs >> count;
    ifs.ignore();
    for (int i = 0; i < count; i++)
        records[i].loadFromFile(ifs);
}
