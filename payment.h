#ifndef payment_h
#define payment_h
#include <string>
using namespace std;
class Payment{
int paymentID;
int memberID;
string date;
double amount;
bool isPaid;
public:
Payment();
void recordOfPayment(int memberID, double amount);
int getMemberID() const;
double getAmount() const;
bool getStatus() const;
};
class PaymentManagement{
Payment Payments[100];
int count;
public:
void addPayment(Payment p);
void showPaymentHistory(int memberID);
void checkUnpaidMembers();
void createReport();
void loadPayments();
void savePayments();
};
#endif