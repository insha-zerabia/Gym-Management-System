#ifndef payment_h
#define payment_h
#include <string>
using namespace std;

class Payment {
private:
    int    paymentID;
    string memberID;
    string date;
    double amount;
    bool   isPaid;

public:
    Payment();
    Payment(const Payment& other);
    Payment& operator=(const Payment& other);

    void setPaymentID(int id);
    void setIsPaid(bool status);
    void setMemberID(string id);
    void setAmount(double amt);
    void setDate(string d);
    void   recordOfPayment(string memberID, double amount, string date);
    string getMemberID() const;
    double getAmount()   const;
    string getDate()     const;
    bool   getStatus()   const;
    void recordPendingPayment(string memberID, double amount, string date);
};

class PaymentManagement {
private:
    Payment Payments[100];
    int count;
    int nextPaymentID;
public:
    PaymentManagement();
    void addPayment(Payment p);
    void showPaymentHistory(string memberID);
    void checkUnpaidMembers();
    void createReport();
    void loadPayments();
    void savePayments();
    int getPendingCount() const;
    void markAsPaid(string memberID);
};
#endif