#include "gymSystem.h"  
#include <iostream>
using namespace std;

int main() 
{
   GymSystem gym;
   gym.run();
   PlanManagement daq;
   daq.loadPlans();
   daq.addPlan(Plan(1, "Basic", 30, 1000));
   daq.viewPlans();
   daq.savePlans(); 
   PaymentManagement pay;
   
   Payment p;
   p.recordOfPayment(101, 1000);
   pay.addPayment(p);
   pay.showPaymentHistory(101);
   pay.createReport();
   return 0;
}