#include "trainer.h"
using namespace std;

// Default constructor
Trainer::Trainer() : trainerID(0) {
    strcpy(name, "");
    strcpy(specialization, "");
    strcpy(contactNumber, "");
}

// Parameterized constructor
Trainer::Trainer(int id, const char* n, const char* spec, const char* contact)
    : trainerID(id) {
    strcpy(name, n);
    strcpy(specialization, spec);
    strcpy(contactNumber, contact);
}

// Copy constructor
Trainer::Trainer(const Trainer& other)
    : trainerID(other.trainerID) {
    strcpy(name, other.name);
    strcpy(specialization, other.specialization);
    strcpy(contactNumber, other.contactNumber);
}

// Destructor
Trainer::~Trainer() {}

// Getters & Setters
int Trainer::getTrainerID() const { return trainerID; }
void Trainer::setTrainerID(int id) { trainerID = id; }

void Trainer::getName(char* buffer) const {
    strcpy(buffer, name);
}
void Trainer::setName(const char* n) {
    strcpy(name, n);
}

void Trainer::getSpecialization(char* buffer) const {
    strcpy(buffer, specialization);
}
void Trainer::setSpecialization(const char* spec) {
    strcpy(specialization, spec);
}

void Trainer::getContactNumber(char* buffer) const {
    strcpy(buffer, contactNumber);
}
void Trainer::setContactNumber(const char* contact) {
    strcpy(contactNumber, contact);
}

// Display info
void Trainer::display() const {
    cout << "Trainer ID: " << trainerID << endl
        << "Name: " << name << endl
        << "Specialization: " << specialization << endl
        << "Contact: " << contactNumber << endl;
}

// File functions
void Trainer::saveToFile(ofstream& ofs) const {
    ofs << trainerID << endl
        << name << endl
        << specialization << endl
        << contactNumber << endl;
}

void Trainer::loadFromFile(ifstream& ifs) {
    ifs >> trainerID;
    ifs.ignore();
    ifs.getline(name, 50);
    ifs.getline(specialization, 50);
    ifs.getline(contactNumber, 20);
}

// Operator overload
bool Trainer::operator==(const Trainer& rhs) const {
    return trainerID == rhs.trainerID;
}