#ifndef plan_h
#define plan_h
#include <string>
using namespace std;

class Plan {
private:
    int    ID;
    string name;
    int    period;
    double fee;

public:
    Plan();
    Plan(int ID, string name, int period, double fee);
    Plan(const Plan& other);
    Plan& operator=(const Plan& other);

    void setID(int ID);
    void setName(string name);
    void setPeriod(int period);
    void setFee(double fee);

    int    getID()     const;
    string getName()   const;
    int    getPeriod() const;
    double getFee()    const;

    friend ostream& operator<<(ostream& os, const Plan& p);
};

class PlanManagement {
private:
    Plan   plans[100];
    int    count;

    string memberPlanIds[200];
    int    memberPlanNums[200];
    int    assignCount;

public:
    PlanManagement();
    void addPlan(Plan p);
    void viewPlans()        const;
    void updatePlan(int ID);
    void deletePlan(int ID);
    void loadPlans();
    void savePlans();

    void assignPlanToMember(string memberId, int planId);
    void viewMemberPlan(string memberId)  const;
    int  getMemberPlanId(string memberId) const;

    void saveAssignments() const;
    void loadAssignments();
};
#endif