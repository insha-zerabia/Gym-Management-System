#include "payment.h"
#include <iostream>
using namespace std;
Payment::Payment()
{

}
void Payment::recordOfPayment(int memberID, double amount)
{

}
int Payment::getMemberID() const
{
    return memberID;
}
double Payment::getAmount() const
{
    return amount;
}
bool Payment::getStatus() const
{
    return isPaid;
}
PaymentManagement::PaymentManagement()
{
    count=0;
}
void PaymentManagement::addPayment(Payment p)
{

}
void PaymentManagement::showPaymentHistory(int memberID)
{

}
void PaymentManagement::checkUnpaidMembers()
{

}
void PaymentManagement::createReport()
{

}
void PaymentManagement::loadPayments()
{

}
void PaymentManagement::savePayments()
{
    
}