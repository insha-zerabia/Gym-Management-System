#ifndef payment_h
#define payment_h
#include <string>
using namespace std;

class Payment{

private:
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
private:
Payment Payments[100];
int count;
public:
PaymentManagement();
void addPayment(Payment p);
void showPaymentHistory(int memberID);             //user can see his own payment history 
void checkUnpaidMembers();
void createReport();
void loadPayments();
void savePayments();
};
#endif