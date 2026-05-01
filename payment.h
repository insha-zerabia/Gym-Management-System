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

    void   recordOfPayment(string memberID, double amount, string date);
    string getMemberID() const;
    double getAmount()   const;
    string getDate()     const;
    bool   getStatus()   const;
};

class PaymentManagement {
private:
    Payment Payments[100];
    int count;
public:
    PaymentManagement();
    void addPayment(Payment p);
    void showPaymentHistory(string memberID);
    void checkUnpaidMembers();
    void createReport();
    void loadPayments();
    void savePayments();
};
#endif