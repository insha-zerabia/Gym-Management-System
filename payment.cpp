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
    this->paymentID = 0;   
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
    {
        if (!Payments[i].getStatus())
        {
            // check if we already printed this member
            bool alreadyShown = false;
            for (int j = 0; j < i; j++)
            {
                if (Payments[j].getMemberID() == Payments[i].getMemberID()
                    && !Payments[j].getStatus())
                {
                    alreadyShown = true;
                    break;
                }
            }
            if (!alreadyShown)
            {
                cout << "Unpaid Member ID: " << Payments[i].getMemberID()
                    << "  Amount Due: Rs." << Payments[i].getAmount() << "\n";
                found = true;
            }
        }
    }
    if (!found)
        cout << "No unpaid members.\n";
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
        p.setMemberID(mID);
        p.setAmount(amount);
        p.setIsPaid(status);
        p.setDate(date);
        p.setPaymentID(nextPaymentID++);
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
        << Payments[i].getDate() << "\n";
    file.close();
}

void Payment::recordPendingPayment(string mID, double amt, string d)
{
    this->memberID = mID;
    this->amount = amt;
    this->isPaid = false;
    this->date = d.empty() ? getTodayDate() : d;
    this->paymentID = 0;  
}

int PaymentManagement::getPendingCount() const
{
    int n = 0;
    for (int i = 0; i < count; i++)
        if (!Payments[i].getStatus()) n++;
    return n;
}

void Payment::setPaymentID(int id) { paymentID = id; }
void Payment::setIsPaid(bool status) { isPaid = status; }
void Payment::setMemberID(string id) { memberID = id; }
void Payment::setAmount(double amt) { amount = amt; }
void Payment::setDate(string d) { date = d; }

void PaymentManagement::markAsPaid(string memberID)
{
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (Payments[i].getMemberID() == memberID && !Payments[i].getStatus())
        {
            Payments[i].setIsPaid(true);
            cout << "Payment of Rs." << Payments[i].getAmount()
                << " marked as paid for member " << memberID << ".\n";
            found = true;
            break;   // mark only the oldest unpaid one first
        }
    }
    if (!found)
        cout << "No unpaid payment found for member " << memberID << ".\n";

    savePayments();
}