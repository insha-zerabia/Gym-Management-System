#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <fstream>
#include <cstring>

class Trainer {
private:
    int trainerID;
    char name[50];
    char specialization[50];
    char contactNumber[20];

public:
    // Constructors
    Trainer();
    Trainer(int id, const char* name, const char* spec, const char* contact);
    Trainer(const Trainer& other);

    // Destructor
    ~Trainer();

    // Getters & Setters
    int getTrainerID() const;
    void setTrainerID(int id);

    void getName(char* buffer) const;
    void setName(const char* name);

    void getSpecialization(char* buffer) const;
    void setSpecialization(const char* spec);

    void getContactNumber(char* buffer) const;
    void setContactNumber(const char* contact);

    // Display info
    void display() const;

    // File functions
    void saveToFile(std::ofstream& ofs) const;
    void loadFromFile(std::ifstream& ifs);

    // Operator overloading
    bool operator==(const Trainer& rhs) const;

    // New functions
    void UpdateTrainerInfo(); // To update trainer details
    static Trainer* searchTrainerByID(Trainer trainers[], int count, int id);
};

#endif // TRAINER_H