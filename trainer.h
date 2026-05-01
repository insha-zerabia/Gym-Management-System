#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include <fstream>
using namespace std;

// stores data of trainers
class Trainer {
private:
    int    trainerID; 
    string name;
    string specialization;   
    string contactNumber;
    string email;
    string availability;     
    int    experienceYears;
    bool   isActive;
    string name;
public:
    // Constructors / Destructor
    Trainer();
    Trainer(int id, string name, string spec, string contact,
        string email, string availability, int expYears);
    Trainer(const Trainer& other);
    Trainer& operator=(const Trainer& other);
    ~Trainer();

    // Getters
    int    getTrainerID()      const;
    string getName()           const;
    string getSpecialization() const;
    string getContactNumber()  const;
    string getEmail()          const;
    string getAvailability()   const;
    int    getExperienceYears()const;
    bool   getIsActive()       const;

    // Setters
    void setTrainerID(int v);
    void setName(string v);
    void setSpecialization(string v);
    void setContactNumber(string v);
    void setEmail(string v);
    void setAvailability(string v);
    void setExperienceYears(int v);
    void setIsActive(bool v);

    // Operator overload
    bool operator==(const Trainer& rhs) const;

    // Display / File I/O
    void display()                     const;
    void displayCompact()              const;   // one-line summary for lists
    void saveToFile(ofstream& ofs)     const;
    void loadFromFile(ifstream& ifs);
};


//  MemberTrainerAssignment  links one member to one trainer

struct MemberTrainerAssignment {
    string memberId;
    int    trainerID;
    string assignedDate;

    MemberTrainerAssignment();
    MemberTrainerAssignment(string mid, int tid, string date);
    void saveToFile(ofstream& ofs)  const;
    void loadFromFile(ifstream& ifs);
};
//  TrainerManager manages all trainers + assignments

class TrainerManager {
private:
    Trainer                  trainers[100];
    int                      trainerCount;
    MemberTrainerAssignment  assignments[200];
    int                      assignCount;

    string currentDate() const;

public:
    TrainerManager();

    // Trainer CRUD
    void addTrainer();
    void viewAllTrainers()        const;
    void viewActiveTrainers()     const;
    void searchTrainerByID(int id) const;
    void searchTrainerByName(string keyword) const;
    void updateTrainer(int id);
    void deactivateTrainer(int id);   // soft delete – keeps history
    void deleteTrainer(int id);

    // Assignment which assign/change trainer for a member
    void assignTrainerToMember(string memberId, int trainerID);
    void changeTrainerForMember(string memberId, int newTrainerID);
    void removeTrainerFromMember(string memberId);
    void viewMemberTrainer(string memberId)     const;
    void viewTrainerMembers(int trainerID)      const;   // who is assigned to this trainer
    int  getAssignedTrainerID(string memberId)  const;

    
    Trainer* findByID(int id);
    bool     trainerExists(int id) const;

    // File I/O
    void saveToFile()   const;
    void loadFromFile();
    void saveAssignments()   const;
    void loadAssignments();

    int getCount() const { return trainerCount; }
};

#endif // TRAINER_H