#include "workout.h"
using namespace std;

// Default constructor
Workout::Workout() : workoutID(0) {
    strcpy(name, "");
    strcpy(description, "");
}

// Parameterized constructor
Workout::Workout(int id, const char* n, const char* desc)
    : workoutID(id) {
    strcpy(name, n);
    strcpy(description, desc);
}

// Copy constructor
Workout::Workout(const Workout& other)
    : workoutID(other.workoutID) {
    strcpy(name, other.name);
    strcpy(description, other.description);
}

// Destructor
Workout::~Workout() {}

// Getters & Setters
int Workout::getWorkoutID() const { return workoutID; }
void Workout::setWorkoutID(int id) { workoutID = id; }

void Workout::getName(char* buffer) const {
    strcpy(buffer, name);
}
void Workout::setName(const char* n) {
    strcpy(name, n);
}

void Workout::getDescription(char* buffer) const {
    strcpy(buffer, description);
}
void Workout::setDescription(const char* desc) {
    strcpy(description, desc);
}

// Display info
void Workout::display() const {
    cout << "Workout ID: " << workoutID << endl
        << "Name: " << name << endl
        << "Description: " << description << endl;
}

// File functions
void Workout::saveToFile(ofstream& ofs) const {
    ofs << workoutID << endl
        << name << endl
        << description << endl;
}

void Workout::loadFromFile(ifstream& ifs) {
    ifs >> workoutID;
    ifs.ignore();
    ifs.getline(name, 50);
    ifs.getline(description, 100);
}