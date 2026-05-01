#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>
#include <fstream>
using namespace std;

class Exercise {
private:
    string name; //name of workout exericse
    int    sets; //rounds 
    int    reps; //repititions
    string duration; //total time
    string notes; 
    int time; //added time
public:
    Exercise();
    Exercise(string name, int sets, int reps, string duration, string notes);
    Exercise(const Exercise& other);
    Exercise& operator=(const Exercise& other);

    string getName()     const;
    int    getSets()     const;
    int    getReps()     const;
    string getDuration() const;
    string getNotes()    const;

    void setName(string v);
    void setSets(int v);
    void setReps(int v);
    void setDuration(string v);
    void setNotes(string v);

    void display()                  const;
    void saveToFile(ofstream& ofs)  const;
    void loadFromFile(ifstream& ifs);
};

// one day's schedule in a workout plan
class WorkoutDay {
private:
    int      dayNumber;
    string   focus;
    Exercise exercises[20];
    int      exerciseCount;

public:
    WorkoutDay();
    WorkoutDay(int day, string focus);
    WorkoutDay(const WorkoutDay& other);
    WorkoutDay& operator=(const WorkoutDay& other);

    int    getDayNumber()    const;
    string getFocus()        const;
    int    getExerciseCount()const;

    void setDayNumber(int v);
    void setFocus(string v);

    void addExercise(Exercise e);
    void updateExercise(int index);
    void removeExercise(int index);
    const Exercise& getExercise(int index) const;

    void display()                  const;
    void saveToFile(ofstream& ofs)  const;
    void loadFromFile(ifstream& ifs);
};

// full weekly workout plan
class Workout {
private:
    int        workoutID;
    string     name;
    string     description;
    string     goal;
    string     difficulty;
    int        durationWeeks;
    WorkoutDay days[7];
    int        dayCount;

public:
    Workout();
    Workout(int id, string name, string desc, string goal,
        string difficulty, int durationWeeks);
    Workout(const Workout& other);
    Workout& operator=(const Workout& other);
    ~Workout();

    int    getWorkoutID()     const;
    string getName()          const;
    string getDescription()   const;
    string getGoal()          const;
    string getDifficulty()    const;
    int    getDurationWeeks() const;
    int    getDayCount()      const;

    void setWorkoutID(int v);
    void setName(string v);
    void setDescription(string v);
    void setGoal(string v);
    void setDifficulty(string v);
    void setDurationWeeks(int v);

    void addDay();
    void updateDay(int dayNumber);
    void removeDay(int dayNumber);
    WorkoutDay* findDay(int dayNumber);

    void display()        const;
    void displaySummary() const;

    void saveToFile(ofstream& ofs)  const;
    void loadFromFile(ifstream& ifs);
};

class MemberWorkoutAssignment {
public:
    string memberId;
    int    workoutID;
    string startDate;
    string progressNote;

    MemberWorkoutAssignment();
    MemberWorkoutAssignment(string mid, int wid, string date);

    void saveToFile(ofstream& ofs)  const;
    void loadFromFile(ifstream& ifs);
};

// manages all plans + assignments
class WorkoutManager {
private:
    Workout                  workouts[100];
    int                      workoutCount;
    MemberWorkoutAssignment  assignments[200];
    int                      assignCount;

    string currentDate() const;

public:
    WorkoutManager();

    void addWorkout();
    void viewAllWorkouts()     const;
    void viewWorkoutDetail(int id) const;
    void searchWorkout(string keyword) const;
    void updateWorkout(int id);
    void deleteWorkout(int id);

    void manageDays(int workoutID);

    void assignWorkoutToMember(string memberId, int workoutID);
    void changeWorkoutForMember(string memberId, int newWorkoutID);
    void removeWorkoutFromMember(string memberId);
    void viewMemberWorkout(string memberId)  const;
    void updateProgressNote(string memberId, string note);
    void viewAllMemberSchedules()            const;
    int  getAssignedWorkoutID(string memberId) const;

    Workout* findByID(int id);
    bool     workoutExists(int id) const;

    void saveToFile()        const;
    void loadFromFile();
    void saveAssignments()   const;
    void loadAssignments();

    int getCount() const { return workoutCount; }
};

#endif