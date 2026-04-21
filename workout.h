#ifndef WORKOUT_H
#define WORKOUT_H

#include <iostream>
#include <fstream>
#include <cstring>

class Workout {
private:
    int workoutID;
    char name[50];
    char description[100];

public:
    // Constructors
    Workout();
    Workout(int id, const char* name, const char* desc);
    Workout(const Workout& other);

    // Destructor
    ~Workout();

    // Getters & Setters
    int getWorkoutID() const;
    void setWorkoutID(int id);

    void getName(char* buffer) const;
    void setName(const char* name);

    void getDescription(char* buffer) const;
    void setDescription(const char* desc);

    // Display info
    void display() const;

    // File functions
    void saveToFile(std::ofstream& ofs) const;
    void loadFromFile(std::ifstream& ifs);
};

#endif // WORKOUT_H
