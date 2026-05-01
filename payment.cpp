#include "payment.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

//Helper to get current date
static string getTodayDate()
{
    time_t now = time(nullptr);
    char buf[20];
    tm t;
    localtime_s(&t, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t);
    return string(buf);
}

Payment::Payment() : paymentID(0), memberID(""), date(""), amount(0), isPaid(false) {}

void Payment::recordOfPayment(string mID, double amt, string d)
{
    this->memberID = mID;
    this->amount = amt;
    this->isPaid = true;
    this->date = d.empty() ? getTodayDate() : d;
    static int id = 1;
    paymentID = id++;
}

string Payment::getMemberID() const { return memberID; }
double Payment::getAmount()   const { return amount; }
string Payment::getDate()     const { return date; }
bool   Payment::getStatus()   const { return isPaid; }

PaymentManagement::PaymentManagement() : count(0) {}

void PaymentManagement::addPayment(Payment p)
{
    if (count < 100) Payments[count++] = p;
    else cout << "Payment list is full." << endl;
}

void PaymentManagement::showPaymentHistory(string memberID)
{
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (Payments[i].getMemberID() == memberID)
        {
            cout << "Date: " << Payments[i].getDate()
                << "  Amount: " << Payments[i].getAmount()
                << "  Status: " << (Payments[i].getStatus() ? "Paid" : "Unpaid") << endl;
            found = true;
        }
    }
    if (!found) cout << "No payment records found for member " << memberID << "." << endl;
}

void PaymentManagement::checkUnpaidMembers()
{
    for (int i = 0; i < count; i++)
        if (!Payments[i].getStatus())
            cout << "Unpaid Member ID: " << Payments[i].getMemberID() << endl;
}

void PaymentManagement::createReport()
{
    double total = 0;
    for (int i = 0; i < count; i++)
        if (Payments[i].getStatus())
            total += Payments[i].getAmount();
    cout << "Total Collected: " << total << endl;
}

void PaymentManagement::loadPayments()
{
    ifstream file("payments.txt");
    if (!file) return;
    count = 0;
    string mID, date;
    double amount;
    bool   status;
    while (file >> mID >> amount >> status >> date)
    {
        Payment p;
        p.recordOfPayment(mID, amount, date);
        if (!status) { Payment empty; p = empty; }             //mark unpaid if needed
        Payments[count++] = p;
    }
    file.close();
}

void PaymentManagement::savePayments()
{
    ofstream file("payments.txt");
    for (int i = 0; i < count; i++)
        file << Payments[i].getMemberID() << " "
        << Payments[i].getAmount() << " "
        << Payments[i].getStatus() << " "
        << Payments[i].getDate() << endl;
    file.close();
}