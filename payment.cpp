#include "payment.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

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

Payment::Payment(const Payment& o)
    : paymentID(o.paymentID), memberID(o.memberID), date(o.date),
    amount(o.amount), isPaid(o.isPaid) {
}

Payment& Payment::operator=(const Payment& o)
{
    if (this != &o) {
        paymentID = o.paymentID;
        memberID = o.memberID;
        date = o.date;
        amount = o.amount;
        isPaid = o.isPaid;
    }
    return *this;
}

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

PaymentManagement::PaymentManagement() : count(0), nextPaymentID(1)
{
    loadPayments();
}

void PaymentManagement::addPayment(Payment p)
{
    if (count < 100)
    {
        p.setPaymentID(nextPaymentID++);
        Payments[count++] = p;
    }
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
                << "  Amount: Rs." << Payments[i].getAmount()
                << "  Status: " << (Payments[i].getStatus() ? "Paid" : "Unpaid")
                << endl;
            found = true;
        }
    }
    if (!found) cout << "No payment records found for member " << memberID << ".\n";
}

void PaymentManagement::checkUnpaidMembers()
{
    bool found = false;
    for (int i = 0; i < count; i++)
        if (!Payments[i].getStatus())
        {
            cout << "Unpaid Member ID: " << Payments[i].getMemberID() << endl;
            found = true;
        }
    if (!found) cout << "No unpaid members.\n";
}

void PaymentManagement::createReport()
{
    double total = 0;
    for (int i = 0; i < count; i++)
        if (Payments[i].getStatus())
            total += Payments[i].getAmount();
    cout << "Total Collected: Rs." << total << endl;
}

void PaymentManagement::loadPayments()
{
    ifstream file("payments.txt");
    if (!file) return;
    count = 0;
    string mID, date;
    double amount;
    bool   status;
    while (file >> mID >> amount >> status >> date && count < 100)
    {
        Payment p;
        p.recordOfPayment(mID, amount, date);
        Payments[count++] = p;
    }
    file.close();
    nextPaymentID = count + 1;
}

void PaymentManagement::savePayments()
{
    ofstream file("payments.txt");
    for (int i = 0; i < count; i++)
        file << Payments[i].getMemberID() << " "
        << Payments[i].getAmount() << " "
        << Payments[i].getStatus() << " "
        << Payments[i].getDate() << "\n";
    file.close();
}

void Payment::recordPendingPayment(string mID, double amt, string d)
{
    this->memberID = mID;
    this->amount = amt;
    this->isPaid = false;  
    this->date = d.empty() ? getTodayDate() : d;
    static int id = 100;   
    paymentID = id++;
}
int PaymentManagement::getPendingCount() const
{
    int n = 0;
    for (int i = 0; i < count; i++)
        if (!Payments[i].getStatus()) n++;
    return n;
}

void Payment::setPaymentID(int id) { paymentID = id; }