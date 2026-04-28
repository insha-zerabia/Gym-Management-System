#include "plan.h"
#include <iostream>
#include<fstream>
using namespace std;
Plan::Plan() {
    ID=0;
    name="";
    period=0;
    fee=0;
}
Plan::Plan(int ID, string name, int period, double fee)
{
    this->ID=ID;
    this->name=name;
this->period=period;
this->fee=fee;
}
void Plan::setID(int ID)
{
    this->ID=ID;
}
void Plan::setName(string name)
{
this->name=name;
}
void Plan::setPeriod(int period)
{
    this->period=period;
}
void Plan::setFee(double fee)
{
    this->fee=fee;
}
int Plan::getID() const{
    return ID;
}
string Plan::getName() const
{
    return name;
}
int Plan::getPeriod() const{
    return period;
}
double Plan::getFee() const{
    return fee;
}
PlanManagement::PlanManagement()
{
    count=0;
}
void PlanManagement::addPlan(Plan p)
{
if (count<100)
{
    plans[count++]=p;
}
else{
    cout<<"list is full"<<endl;
}
}
void PlanManagement::viewPlans()
{
for(int i=0;i<count;i++)
{
    cout<<" ID: "<<plans[i].getID()<<endl<<"Name:"<<plans[i].getName()<<endl<<"Period: "<<plans[i].getPeriod()<<endl<<"Fee: "<<plans[i].getFee()<<endl;
}
}
void PlanManagement::updatePlan(int ID)
{
for(int i=0;i<count;i++)
{
if(plans[i].getID() ==ID)
{
    string name;
    int period;
    double fee;
    cout<<"Enter new name: ";
    cin>>name;
    cout<<"Enter period: ";
    cin>>period;
    cout<<"Enter fee: ";
    cin>>fee;
    plans[i].setName(name);
    plans[i].setPeriod(period);
    plans[i].setFee(fee);
    cout<<"Plan is updated."<<endl;
    return;
}
}
cout<<"Plan is not found. "<<endl;
}
void PlanManagement::loadPlans()
{
ifstream file("plans.txt");
count=0;
int ID, period;
string name;
double fee;
while(file>> ID >>name>>period>>fee)
{
plans[count++]=Plan(ID,name,period,fee);
}
file.close();
}
void PlanManagement::savePlans()
{
ofstream file("plans.txt");
for(int i=0;i<count;i++)
{
    file<<plans[i].getID()<<" "<<plans[i].getName()<<" "<<plans[i].getPeriod()<<" "<<plans[i].getFee()<<endl;
}
file.close();
}