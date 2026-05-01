#include "plan.h"
#include <iostream>
#include <fstream>
using namespace std;

Plan::Plan() : ID(0), name(""), period(0), fee(0) {}

Plan::Plan(int ID, string name, int period, double fee)
    : ID(ID), name(name), period(period), fee(fee) {}

Plan::Plan(const Plan& o)
    : ID(o.ID), name(o.name), period(o.period), fee(o.fee) {}

Plan& Plan::operator=(const Plan& o)
{
    if (this != &o) 
    {
        ID = o.ID;
        name = o.name;
        period = o.period;
        fee = o.fee;
    }
    return *this;
}

void Plan::setID(int v) { ID = v; }
void Plan::setName(string v) { name = v; }
void Plan::setPeriod(int v) { period = v; }
void Plan::setFee(double v) { fee = v; }

int    Plan::getID()     const { return ID; }
string Plan::getName()   const { return name; }
int    Plan::getPeriod() const { return period; }
double Plan::getFee()    const { return fee; }

ostream& operator<<(ostream& os, const Plan& p)
{
    os << "PlanID: " << p.ID << " | " << p.name
        << " | " << p.period << " days | Rs." << p.fee;
    return os;
}


PlanManagement::PlanManagement() : count(0), assignCount(0)
{
    loadPlans();
    loadAssignments();
}

void PlanManagement::addPlan(Plan p)
{
    if (count < 100) plans[count++] = p;
    else cout << "Plan list is full." << endl;
}

void PlanManagement::viewPlans() const
{
    if (count == 0) { cout << " No plans found.\n"; return; }
    for (int i = 0; i < count; i++)
        cout << " ID: " << plans[i].getID()
        << " | Name: " << plans[i].getName()
        << " | Period: " << plans[i].getPeriod() << " days"
        << " | Fee: Rs." << plans[i].getFee() << "\n";
}

void PlanManagement::updatePlan(int ID)
{
    for (int i = 0; i < count; i++)
    {
        if (plans[i].getID() == ID)
        {
            string name; int period; double fee;
            cout << " New name   : "; cin >> name;
            cout << " New period : "; cin >> period;
            cout << " New fee    : "; cin >> fee;
            plans[i].setName(name);
            plans[i].setPeriod(period);
            plans[i].setFee(fee);
            cout << " Plan updated.\n";
            return;
        }
    }
    cout << " Plan not found.\n";
}

void PlanManagement::deletePlan(int ID)
{
    for (int i = 0; i < count; i++)
    {
        if (plans[i].getID() == ID)
        {
            for (int j = i; j < count - 1; j++)
                plans[j] = plans[j + 1];
            count--;
            cout << " Plan deleted.\n";
            return;
        }
    }
    cout << " Plan not found.\n";
}

void PlanManagement::assignPlanToMember(string memberId, int planId)
{
    bool exists = false;
    for (int i = 0; i < count; i++)
        if (plans[i].getID() == planId) { exists = true; break; }
    if (!exists) { cout << " Plan ID " << planId << " not found.\n"; return; }

    for (int i = 0; i < assignCount; i++)
    {
        if (memberPlanIds[i] == memberId)
        {
            memberPlanNums[i] = planId;
            saveAssignments();
            cout << " Plan updated for member " << memberId << ".\n";
            return;
        }
    }
    if (assignCount >= 200) { cout << " Assignment list full.\n"; return; }
    memberPlanIds[assignCount] = memberId;
    memberPlanNums[assignCount] = planId;
    assignCount++;
    saveAssignments();
    cout << " Plan " << planId << " assigned to member " << memberId << ".\n";
}

void PlanManagement::viewMemberPlan(string memberId) const
{
    for (int i = 0; i < assignCount; i++)
    {
        if (memberPlanIds[i] == memberId)
        {
            int pid = memberPlanNums[i];
            for (int j = 0; j < count; j++)
            {
                if (plans[j].getID() == pid)
                {
                    cout << " Plan ID : " << plans[j].getID() << "\n";
                    cout << " Name    : " << plans[j].getName() << "\n";
                    cout << " Period  : " << plans[j].getPeriod() << " days\n";
                    cout << " Fee     : Rs." << plans[j].getFee() << "\n";
                    return;
                }
            }
        }
    }
    cout << " No plan assigned to member " << memberId << ".\n";
}

int PlanManagement::getMemberPlanId(string memberId) const
{
    for (int i = 0; i < assignCount; i++)
        if (memberPlanIds[i] == memberId)
            return memberPlanNums[i];
    return -1;
}

void PlanManagement::saveAssignments() const
{
    ofstream file("plan_assignments.txt");
    file << assignCount << "\n";
    for (int i = 0; i < assignCount; i++)
        file << memberPlanIds[i] << " " << memberPlanNums[i] << "\n";
    file.close();
}

void PlanManagement::loadAssignments()
{
    ifstream file("plan_assignments.txt");
    if (!file) return;
    file >> assignCount;
    for (int i = 0; i < assignCount; i++)
        file >> memberPlanIds[i] >> memberPlanNums[i];
    file.close();
}

void PlanManagement::loadPlans()
{
    ifstream file("plans.txt");
    if (!file) return;
    count = 0;
    int ID, period; string name; double fee;
    while (file >> ID >> name >> period >> fee && count < 100)
        plans[count++] = Plan(ID, name, period, fee);
    file.close();
}

void PlanManagement::savePlans()
{
    ofstream file("plans.txt");
    for (int i = 0; i < count; i++)
        file << plans[i].getID() << " "
        << plans[i].getName() << " "
        << plans[i].getPeriod() << " "
        << plans[i].getFee() << "\n";
    file.close();
}