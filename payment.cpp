#include "payment.h"
#include <iostream>
#include<fstream>
using namespace std;
Payment::Payment()
{
paymentID=0;
memberID=0;
amount=0;
isPaid=false;
}
void Payment::recordOfPayment(int memberID, double amount)
{
this->memberID=memberID;
this->amount=amount;
this->isPaid=true;
static int id=1;
paymentID=id++;

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
if(count<100)
{
    Payments[count++]=p;
}
else{
    cout<<"Payment list is full."<<endl;
}
}
void PaymentManagement::showPaymentHistory(int memberID)
{
for(int i=0;i<count;i++)
{
    if(Payments[i].getMemberID()==memberID)
    {
        cout<<"Amount: "<<Payments[i].getAmount()<<", Status: "<<(Payments[i].getStatus()?"Paid ": "Unpaid ")<<endl;
    }
}
}
void PaymentManagement::checkUnpaidMembers()
{
for(int i=0;i<count;i++)
{
    if(!Payments[i].getStatus())
    {
        cout<<"Unpaid member ID: "<<Payments[i].getMemberID()<<endl;
    }
}
}
void PaymentManagement::createReport()
{
double total=0;
for(int i=0;i<count;i++)
{
    if(Payments[i].getStatus())
    {
        total+=Payments[i].getAmount();
    }
}
cout<<"Total: "<<total<<endl;
}
void PaymentManagement::loadPayments()
{
ifstream file("payments.txt");
count =0;
int memberID;
double amount;
bool status;
while(file>>memberID>>amount>>status)
{
    Payment p;
    p.recordOfPayment(memberID,amount);
    if(!status)
    {
        p=Payment();
    }
    Payments[count++]=p;
}
file.close();
}
void PaymentManagement::savePayments()
{
ofstream file("payments.txt");
    for(int i=0;i<count;i++)
    {
        file<<Payments[i].getMemberID()<<" "<<Payments[i].getAmount()<<" "<<Payments[i].getStatus()<<endl;
    }
file.close();
}