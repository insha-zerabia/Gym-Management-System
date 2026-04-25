#include "trainer.h"
#include <iostream>
using namespace std;

// Default constructor
Trainer::Trainer() : trainerID(0) {
    strcpy(name, sizeof(name), "");
    strcpy(specialization, sizeof(specialization), "");
    strcpy(contactNumber, sizeof(contactNumber), "");
}

// Parameterized constructor
Trainer::Trainer(int id, const char* n, const char* spec, const char* contact)
    : trainerID(id) {
    strcpy(name, sizeof(name), n);
    strcpy(specialization, sizeof(specialization), spec);
    strcpy(contactNumber, sizeof(contactNumber), contact);
}

// Copy constructor
Trainer::Trainer(const Trainer& other)
    : trainerID(other.trainerID) {
    strcpy(name, sizeof(name), other.name);
    strcpy(specialization, sizeof(specialization), other.specialization);
    strcpy(contactNumber, sizeof(contactNumber), other.contactNumber);
}

// Destructor
Trainer::~Trainer() {}

// Getters & Setters
int Trainer::getTrainerID() const { return trainerID; }
void Trainer::setTrainerID(int id) {
    trainerID = id;
}

void Trainer::getName(char* buffer) const {
    strcpy(buffer, 50, name);
}
void Trainer::setName(const char* n) {
    strcpy(name, sizeof(name), n);
}

void Trainer::getSpecialization(char* buffer) const {
    strcpy(buffer, 50, specialization);
}
void Trainer::setSpecialization(const char* spec) {
    strcpy(specialization, sizeof(specialization), spec);
}

void Trainer::getContactNumber(char* buffer) const {
    strcpy(buffer, 20, contactNumber);
}
void Trainer::setContactNumber(const char* contact) {
    strcpy(contactNumber, sizeof(contactNumber), contact);
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
    ifs.ignore(); // Ignore newline after ID
    ifs.getline(name, 50);
    ifs.getline(specialization, 50);
    ifs.getline(contactNumber, 20);
}

// Operator overload
bool Trainer::operator==(const Trainer& rhs) const {
    return trainerID == rhs.trainerID;
}

// ------------------------------
// New Function 1: Update Trainer Info
void Trainer::UpdateTrainerInfo() {
    char buffer[50];

    cout << "Updating Trainer ID: " << trainerID << endl;

    cout << "Enter new Name: ";
    cin.getline(buffer, 50);
    setName(buffer);

    cout << "Enter new Specialization: ";
    cin.getline(buffer, 50);
    setSpecialization(buffer);

    cout << "Enter new Contact Number: ";
    cin.getline(buffer, 20);
    setContactNumber(buffer);

    cout << "Trainer information updated.\n";
}

// ------------------------------
// New Function 2: Search Trainer by ID (static function)
Trainer* Trainer::searchTrainerByID(Trainer trainers[], int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (trainers[i].getTrainerID() == id)
            return &trainers[i];
    }
    return nullptr; // Not found
}