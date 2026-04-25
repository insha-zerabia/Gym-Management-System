#include "workout.h"
using namespace std;

// Default constructor
Workout::Workout() : workoutID(0) {
    strcpy_s(name, "");
    strcpy_s(description, "");
}

// Parameterized constructor
Workout::Workout(int id, const char* n, const char* desc)
    : workoutID(id) {
    strcpy_s(name, n);
    strcpy_s(description, desc);
}

// Copy constructor
Workout::Workout(const Workout& other)
    : workoutID(other.workoutID) {
    strcpy_s(name, other.name);
    strcpy_s(description, other.description);
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
    strcpy_s(name, n);
}

void Workout::getDescription(char* buffer) const {
    strcpy(buffer, description);
}
void Workout::setDescription(const char* desc) {
    strcpy_s(description, desc);
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

// Implementation of UpdateWorkoutInfo
void Workout::UpdateWorkoutInfo() {
    char buffer[100];

    cout << "Updating Workout ID: " << workoutID << endl;

    cout << "Enter new Name: ";
    cin.getline(buffer, 50);
    setName(buffer);

    cout << "Enter new Description: ";
    cin.getline(buffer, 100);
    setDescription(buffer);

    cout << "Workout information updated.\n";
}

// Implementation of searchWorkoutByID
Workout* Workout::searchWorkoutByID(Workout workouts[], int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (workouts[i].getWorkoutID() == id)
            return &workouts[i];
    }
    return nullptr; // Not found
}