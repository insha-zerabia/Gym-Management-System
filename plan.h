#ifndef plan_h
#define plan_h
#include<string>
using namespace std;
class Plan{
int ID;
string name;
int period;
double fee;
public:
Plan();
Plan(int ID,string name,int period, double fee);
void setID(int ID);
void setName(string name);
void setPeriod(int period);
void setFee(double fee);
int getID() const;
string getName() const;
int getPeriod() const;
double getFee() const;

};
class PlanManagement{
    Plan plans[100];
    int count;
    public:
    PlanManagement();
    void addPlan(Plan p);
    void viewPlans();
    void updatePlan(int ID);
    void loadPlans();
    void savePlans();
};
#endif