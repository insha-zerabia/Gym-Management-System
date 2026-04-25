#include "plan.h"
#include <iostream>
using namespace std;
Plan::Plan() {}
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

}
void PlanManagement::viewPlans()
{

}
void PlanManagement::updatePlan(int ID)
{

}
void PlanManagement::loadPlans()
{

}
void PlanManagement::savePlans()
{
    
}