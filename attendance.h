#pragma once
#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
using std::string;

class AttendanceRecord {
private:
    string memberId;
    string date;
    string checkInTime;
    string checkOutTime;
    bool checkedOut;

public:
    AttendanceRecord();
    AttendanceRecord(string memberId, string date, string checkIn);
    AttendanceRecord(const AttendanceRecord& other);
    AttendanceRecord& operator=(const AttendanceRecord& other);
    ~AttendanceRecord();

    // Setters
    void setMemberId(string id);
    void setDate(string d);
    void setCheckInTime(string t);
    void setCheckOutTime(string t);
    void setCheckedOut(bool val);

    // Getters
    string getMemberId() const;
    string getDate() const;
    string getCheckInTime() const;
    string getCheckOutTime() const;
    bool isCheckedOut() const;

    void display() const;
    void saveToFile(std::ofstream& ofs) const;
    void loadFromFile(std::ifstream& ifs);
};

class AttendanceManager {
private:
    AttendanceRecord records[500];
    int count;

    string getCurrentDate() const;
    string getCurrentTime() const;

public:
    AttendanceManager();
    ~AttendanceManager();

    void checkIn(string memberId);
    void checkOut(string memberId);
    void viewMemberAttendance(string memberId) const;
    void viewAllAttendance() const;
    void generateSummary() const;

    void loadFromFile();
    void saveToFile() const;
};

#endif