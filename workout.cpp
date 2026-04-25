#include "workout.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;


Exercise::Exercise()
    : name(""), sets(0), reps(0), duration(""), notes("") {
}

Exercise::Exercise(string n, int s, int r, string dur, string nt)
    : name(n), sets(s), reps(r), duration(dur), notes(nt) {
}

Exercise::Exercise(const Exercise& o)
    : name(o.name), sets(o.sets), reps(o.reps),
    duration(o.duration), notes(o.notes) {
}

Exercise& Exercise::operator=(const Exercise& o) {
    if (this != &o) {
        name = o.name; sets = o.sets; reps = o.reps;
        duration = o.duration; notes = o.notes;
    }
    return *this;
}

// Getters
string Exercise::getName()     const { return name; }
int    Exercise::getSets()     const { return sets; }
int    Exercise::getReps()     const { return reps; }
string Exercise::getDuration() const { return duration; }
string Exercise::getNotes()    const { return notes; }

// Setters
void Exercise::setName(string v) { name = v; }
void Exercise::setSets(int v) { sets = v; }
void Exercise::setReps(int v) { reps = v; }
void Exercise::setDuration(string v) { duration = v; }
void Exercise::setNotes(string v) { notes = v; }

void Exercise::display() const {
    cout << "    Exercise : " << name << "\n"
        << "    Sets     : " << sets << "\n"
        << "    Reps     : " << reps << "\n"
        << "    Duration : " << duration << "\n"
        << "    Notes    : " << notes << "\n";
}

void Exercise::saveToFile(ofstream& ofs) const {
    ofs << name << "\n" << sets << "\n" << reps << "\n"
        << duration << "\n" << notes << "\n";
}

void Exercise::loadFromFile(ifstream& ifs) {
    getline(ifs, name);
    ifs >> sets >> reps; ifs.ignore();
    getline(ifs, duration);
    getline(ifs, notes);
}


WorkoutDay::WorkoutDay()
    : dayNumber(0), focus(""), exerciseCount(0) {
}

WorkoutDay::WorkoutDay(int day, string f)
    : dayNumber(day), focus(f), exerciseCount(0) {
}

WorkoutDay::WorkoutDay(const WorkoutDay& o)
    : dayNumber(o.dayNumber), focus(o.focus),
    exerciseCount(o.exerciseCount) {
    for (int i = 0; i < exerciseCount; i++)
        exercises[i] = o.exercises[i];
}

WorkoutDay& WorkoutDay::operator=(const WorkoutDay& o) {
    if (this != &o) {
        dayNumber = o.dayNumber;
        focus = o.focus;
        exerciseCount = o.exerciseCount;
        for (int i = 0; i < exerciseCount; i++)
            exercises[i] = o.exercises[i];
    }
    return *this;
}

// Getters
int    WorkoutDay::getDayNumber()     const { return dayNumber; }
string WorkoutDay::getFocus()         const { return focus; }
int    WorkoutDay::getExerciseCount() const { return exerciseCount; }

// Setters
void WorkoutDay::setDayNumber(int v) { dayNumber = v; }
void WorkoutDay::setFocus(string v) { focus = v; }

void WorkoutDay::addExercise(Exercise e) {
    if (exerciseCount < 20)
        exercises[exerciseCount++] = e;
    else
        cout << "  Exercise list for this day is full.\n";
}

void WorkoutDay::updateExercise(int index) {
    if (index < 0 || index >= exerciseCount) {
        cout << "  Invalid exercise index.\n";
        return;
    }
    string val;
    int n;
    cout << "  Updating Exercise " << index + 1 << "\n";
    cout << "  Name [" << exercises[index].getName() << "]: ";
    cin.ignore(); getline(cin, val);
    if (!val.empty()) exercises[index].setName(val);

    cout << "  Sets [" << exercises[index].getSets() << "]: ";
    cin >> n; if (n > 0) exercises[index].setSets(n);

    cout << "  Reps [" << exercises[index].getReps() << "]: ";
    cin >> n; if (n > 0) exercises[index].setReps(n);
    cin.ignore();

    cout << "  Duration [" << exercises[index].getDuration() << "]: ";
    getline(cin, val);
    if (!val.empty()) exercises[index].setDuration(val);

    cout << "  Notes [" << exercises[index].getNotes() << "]: ";
    getline(cin, val);
    if (!val.empty()) exercises[index].setNotes(val);
}

void WorkoutDay::removeExercise(int index) {
    if (index < 0 || index >= exerciseCount) {
        cout << "  Invalid exercise index.\n";
        return;
    }
    for (int i = index; i < exerciseCount - 1; i++)
        exercises[i] = exercises[i + 1];
    exerciseCount--;
    cout << "  Exercise removed.\n";
}

const Exercise& WorkoutDay::getExercise(int index) const {
    return exercises[index];
}

void WorkoutDay::display() const {
    cout << "\n  Day " << dayNumber << " - Focus: " << focus << "\n";
    if (exerciseCount == 0) {
        cout << "    No exercises added yet.\n";
        return;
    }
    for (int i = 0; i < exerciseCount; i++) {
        cout << "  [" << i + 1 << "]\n";
        exercises[i].display();
    }
}

void WorkoutDay::saveToFile(ofstream& ofs) const {
    ofs << dayNumber << "\n" << focus << "\n" << exerciseCount << "\n";
    for (int i = 0; i < exerciseCount; i++)
        exercises[i].saveToFile(ofs);
}

void WorkoutDay::loadFromFile(ifstream& ifs) {
    ifs >> dayNumber; ifs.ignore();
    getline(ifs, focus);
    ifs >> exerciseCount; ifs.ignore();
    for (int i = 0; i < exerciseCount; i++)
        exercises[i].loadFromFile(ifs);
}


Workout::Workout()
    : workoutID(0), name(""), description(""), goal(""),
    difficulty(""), durationWeeks(0), dayCount(0) {
}

Workout::Workout(int id, string n, string desc, string g,
    string diff, int weeks)
    : workoutID(id), name(n), description(desc), goal(g),
    difficulty(diff), durationWeeks(weeks), dayCount(0) {
}

Workout::Workout(const Workout& o)
    : workoutID(o.workoutID), name(o.name), description(o.description),
    goal(o.goal), difficulty(o.difficulty),
    durationWeeks(o.durationWeeks), dayCount(o.dayCount) {
    for (int i = 0; i < dayCount; i++)
        days[i] = o.days[i];
}

Workout& Workout::operator=(const Workout& o) {
    if (this != &o) {
        workoutID = o.workoutID; name = o.name;
        description = o.description; goal = o.goal;
        difficulty = o.difficulty; durationWeeks = o.durationWeeks;
        dayCount = o.dayCount;
        for (int i = 0; i < dayCount; i++)
            days[i] = o.days[i];
    }
    return *this;
}

Workout::~Workout() {}

// Getters
int    Workout::getWorkoutID()     const { return workoutID; }
string Workout::getName()          const { return name; }
string Workout::getDescription()   const { return description; }
string Workout::getGoal()          const { return goal; }
string Workout::getDifficulty()    const { return difficulty; }
int    Workout::getDurationWeeks() const { return durationWeeks; }
int    Workout::getDayCount()      const { return dayCount; }

// Setters
void Workout::setWorkoutID(int v) { workoutID = v; }
void Workout::setName(string v) { name = v; }
void Workout::setDescription(string v) { description = v; }
void Workout::setGoal(string v) { goal = v; }
void Workout::setDifficulty(string v) { difficulty = v; }
void Workout::setDurationWeeks(int v) { durationWeeks = v; }

void Workout::addDay() {
    if (dayCount >= 7) {
        cout << "  A workout plan can have at most 7 days.\n";
        return;
    }
    int dayNum;
    string focus;
    cout << "  Day Number (1-7): "; cin >> dayNum; cin.ignore();
    cout << "  Focus (e.g. Chest, Legs): "; getline(cin, focus);
    days[dayCount++] = WorkoutDay(dayNum, focus);
    cout << "  Day " << dayNum << " added.\n";
}

void Workout::updateDay(int dayNumber) {
    WorkoutDay* d = findDay(dayNumber);
    if (!d) { cout << "  Day not found.\n"; return; }
    string val;
    cout << "  New Focus [" << d->getFocus() << "]: ";
    cin.ignore(); getline(cin, val);
    if (!val.empty()) d->setFocus(val);
    cout << "  Day updated.\n";
}

void Workout::removeDay(int dayNumber) {
    for (int i = 0; i < dayCount; i++) {
        if (days[i].getDayNumber() == dayNumber) {
            for (int j = i; j < dayCount - 1; j++)
                days[j] = days[j + 1];
            dayCount--;
            cout << "  Day " << dayNumber << " removed.\n";
            return;
        }
    }
    cout << "  Day not found.\n";
}

WorkoutDay* Workout::findDay(int dayNumber) {
    for (int i = 0; i < dayCount; i++)
        if (days[i].getDayNumber() == dayNumber)
            return &days[i];
    return nullptr;
}

void Workout::display() const {
    cout << "\n  Workout ID   : " << workoutID << "\n"
        << "  Name         : " << name << "\n"
        << "  Description  : " << description << "\n"
        << "  Goal         : " << goal << "\n"
        << "  Difficulty   : " << difficulty << "\n"
        << "  Duration     : " << durationWeeks << " weeks\n"
        << "  Days planned : " << dayCount << "\n";
    for (int i = 0; i < dayCount; i++)
        days[i].display();
}

void Workout::displaySummary() const {
    cout << "  [W" << workoutID << "] " << name
        << " | " << goal << " | " << difficulty
        << " | " << durationWeeks << " wks | "
        << dayCount << " days\n";
}

void Workout::saveToFile(ofstream& ofs) const {
    ofs << workoutID << "\n" << name << "\n" << description << "\n"
        << goal << "\n" << difficulty << "\n"
        << durationWeeks << "\n" << dayCount << "\n";
    for (int i = 0; i < dayCount; i++)
        days[i].saveToFile(ofs);
}

void Workout::loadFromFile(ifstream& ifs) {
    ifs >> workoutID; ifs.ignore();
    getline(ifs, name);
    getline(ifs, description);
    getline(ifs, goal);
    getline(ifs, difficulty);
    ifs >> durationWeeks >> dayCount; ifs.ignore();
    for (int i = 0; i < dayCount; i++)
        days[i].loadFromFile(ifs);
}


MemberWorkoutAssignment::MemberWorkoutAssignment()
    : memberId(""), workoutID(0), startDate(""), progressNote("") {
}

MemberWorkoutAssignment::MemberWorkoutAssignment(string mid, int wid, string date)
    : memberId(mid), workoutID(wid), startDate(date), progressNote("") {
}

void MemberWorkoutAssignment::saveToFile(ofstream& ofs) const {
    ofs << memberId << "\n" << workoutID << "\n"
        << startDate << "\n" << progressNote << "\n";
}

void MemberWorkoutAssignment::loadFromFile(ifstream& ifs) {
    getline(ifs, memberId);
    ifs >> workoutID; ifs.ignore();
    getline(ifs, startDate);
    getline(ifs, progressNote);
}


string WorkoutManager::currentDate() const {
    time_t now = time(nullptr);
    char buf[20];
    struct tm t;
#ifdef _WIN32
    localtime_s(&t, &now);
#else
    localtime_r(&now, &t);
#endif
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t);
    return string(buf);
}

WorkoutManager::WorkoutManager() : workoutCount(0), assignCount(0) {
    loadFromFile();
    loadAssignments();
}

void WorkoutManager::addWorkout() {
    if (workoutCount >= 100) {
        cout << "  Workout list full.\n";
        return;
    }
    int id = workoutCount + 1;
    string name, desc, goal, diff;
    int weeks;

    cout << "\n  Add New Workout Plan\n";
    cout << "  Auto-assigned ID : W" << id << "\n";
    cin.ignore();
    cout << "  Name             : "; getline(cin, name);
    cout << "  Description      : "; getline(cin, desc);
    cout << "  Goal             : "; getline(cin, goal);
    cout << "  Difficulty       : "; getline(cin, diff);
    cout << "  Duration (weeks) : "; cin >> weeks; cin.ignore();

    workouts[workoutCount++] = Workout(id, name, desc, goal, diff, weeks);
    saveToFile();
    cout << "  Workout plan W" << id << " added successfully.\n";
}

void WorkoutManager::viewAllWorkouts() const {
    if (workoutCount == 0) { cout << "  No workout plans found.\n"; return; }
    cout << "\n  All Workout Plans\n";
    cout << "  " << string(60, '-') << "\n";
    for (int i = 0; i < workoutCount; i++)
        workouts[i].displaySummary();
    cout << "  " << string(60, '-') << "\n";
}

void WorkoutManager::viewWorkoutDetail(int id) const {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id) {
            workouts[i].display();
            return;
        }
    cout << "  Workout W" << id << " not found.\n";
}

void WorkoutManager::searchWorkout(string keyword) const {
    cout << "\n  Search results for \"" << keyword << "\"\n";
    bool found = false;
    string kLow = keyword;
    for (char& c : kLow) c = tolower(c);

    for (int i = 0; i < workoutCount; i++) {
        string nLow = workouts[i].getName();
        for (char& c : nLow) c = tolower(c);
        if (nLow.find(kLow) != string::npos) {
            workouts[i].displaySummary();
            found = true;
        }
    }
    if (!found) cout << "  No matching workout found.\n";
}

void WorkoutManager::updateWorkout(int id) {
    Workout* w = findByID(id);
    if (!w) { cout << "  Workout not found.\n"; return; }

    string val; int n;
    cout << "\n  Update Workout W" << id << " (Enter to keep current)\n";
    cin.ignore();
    cout << "  Name [" << w->getName() << "]: ";
    getline(cin, val); if (!val.empty()) w->setName(val);

    cout << "  Description [" << w->getDescription() << "]: ";
    getline(cin, val); if (!val.empty()) w->setDescription(val);

    cout << "  Goal [" << w->getGoal() << "]: ";
    getline(cin, val); if (!val.empty()) w->setGoal(val);

    cout << "  Difficulty [" << w->getDifficulty() << "]: ";
    getline(cin, val); if (!val.empty()) w->setDifficulty(val);

    cout << "  Duration weeks (0=keep) [" << w->getDurationWeeks() << "]: ";
    cin >> n; if (n > 0) w->setDurationWeeks(n); cin.ignore();

    saveToFile();
    cout << "  Workout updated.\n";
}

void WorkoutManager::deleteWorkout(int id) {
    for (int i = 0; i < workoutCount; i++) {
        if (workouts[i].getWorkoutID() == id) {
            for (int j = i; j < workoutCount - 1; j++)
                workouts[j] = workouts[j + 1];
            workoutCount--;
            saveToFile();
            cout << "  Workout W" << id << " deleted.\n";
            return;
        }
    }
    cout << "  Workout not found.\n";
}

void WorkoutManager::manageDays(int workoutID) {
    Workout* w = findByID(workoutID);
    if (!w) { cout << "  Workout not found.\n"; return; }

    int choice;
    do {
        cout << "\n  Manage Days for Workout W" << workoutID << "\n"
            << "  1. Add Day\n"
            << "  2. Update Day Focus\n"
            << "  3. Remove Day\n"
            << "  4. Add Exercise to Day\n"
            << "  5. Remove Exercise from Day\n"
            << "  0. Back\n"
            << "  Choice: ";
        cin >> choice;

        if (choice == 1) {
            w->addDay();
            saveToFile();
        }
        else if (choice == 2) {
            int dayNum;
            cout << "  Day Number: "; cin >> dayNum;
            w->updateDay(dayNum);
            saveToFile();
        }
        else if (choice == 3) {
            int dayNum;
            cout << "  Day Number to remove: "; cin >> dayNum;
            w->removeDay(dayNum);
            saveToFile();
        }
        else if (choice == 4) {
            int dayNum;
            cout << "  Day Number: "; cin >> dayNum;
            WorkoutDay* d = w->findDay(dayNum);
            if (!d) { cout << "  Day not found.\n"; continue; }

            string n, dur, nt; int s, r;
            cin.ignore();
            cout << "  Exercise Name: "; getline(cin, n);
            cout << "  Sets         : "; cin >> s;
            cout << "  Reps         : "; cin >> r; cin.ignore();
            cout << "  Duration     : "; getline(cin, dur);
            cout << "  Notes        : "; getline(cin, nt);
            d->addExercise(Exercise(n, s, r, dur, nt));
            saveToFile();
        }
        else if (choice == 5) {
            int dayNum, idx;
            cout << "  Day Number: "; cin >> dayNum;
            WorkoutDay* d = w->findDay(dayNum);
            if (!d) { cout << "  Day not found.\n"; continue; }
            d->display();
            cout << "  Exercise index to remove (1-based): "; cin >> idx;
            d->removeExercise(idx - 1);
            saveToFile();
        }
    } while (choice != 0);
}

void WorkoutManager::assignWorkoutToMember(string memberId, int workoutID) {
    if (!workoutExists(workoutID)) {
        cout << "  Workout W" << workoutID << " does not exist.\n";
        return;
    }
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            cout << "  Member already has workout W"
                << assignments[i].workoutID << " assigned. Use 'Change' to reassign.\n";
            return;
        }
    }
    if (assignCount >= 200) { cout << "  Assignment list full.\n"; return; }
    assignments[assignCount++] = MemberWorkoutAssignment(memberId, workoutID, currentDate());
    saveAssignments();
    cout << "  Workout W" << workoutID << " assigned to member " << memberId << ".\n";
}

void WorkoutManager::changeWorkoutForMember(string memberId, int newWorkoutID) {
    if (!workoutExists(newWorkoutID)) {
        cout << "  Workout W" << newWorkoutID << " not found.\n";
        return;
    }
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            int old = assignments[i].workoutID;
            assignments[i].workoutID = newWorkoutID;
            assignments[i].startDate = currentDate();
            saveAssignments();
            cout << "  Member " << memberId << " workout changed from W"
                << old << " to W" << newWorkoutID << ".\n";
            return;
        }
    }
    assignWorkoutToMember(memberId, newWorkoutID);
}

void WorkoutManager::removeWorkoutFromMember(string memberId) {
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            for (int j = i; j < assignCount - 1; j++)
                assignments[j] = assignments[j + 1];
            assignCount--;
            saveAssignments();
            cout << "  Workout removed from member " << memberId << ".\n";
            return;
        }
    }
    cout << "  No workout assigned to member " << memberId << ".\n";
}

void WorkoutManager::viewMemberWorkout(string memberId) const {
    cout << "\n  Workout for Member: " << memberId << "\n";
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            int wid = assignments[i].workoutID;
            cout << "  Assigned  : " << assignments[i].startDate << "\n";
            if (!assignments[i].progressNote.empty())
                cout << "  Progress  : " << assignments[i].progressNote << "\n";
            for (int j = 0; j < workoutCount; j++)
                if (workouts[j].getWorkoutID() == wid) {
                    workouts[j].display();
                    return;
                }
            cout << "  Workout W" << wid << " details not found.\n";
            return;
        }
    }
    cout << "  No workout assigned yet.\n";
}

void WorkoutManager::updateProgressNote(string memberId, string note) {
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            assignments[i].progressNote = note;
            saveAssignments();
            cout << "  Progress note updated.\n";
            return;
        }
    }
    cout << "  No workout assigned to member " << memberId << ".\n";
}

void WorkoutManager::viewAllMemberSchedules() const {
    cout << "\n  All Member Workout Assignments\n";
    if (assignCount == 0) { cout << "  No assignments.\n"; return; }
    for (int i = 0; i < assignCount; i++)
        cout << "  Member: " << assignments[i].memberId
        << " -> W" << assignments[i].workoutID
        << " (since " << assignments[i].startDate << ")\n";
}

int WorkoutManager::getAssignedWorkoutID(string memberId) const {
    for (int i = 0; i < assignCount; i++)
        if (assignments[i].memberId == memberId)
            return assignments[i].workoutID;
    return 0;
}

Workout* WorkoutManager::findByID(int id) {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id)
            return &workouts[i];
    return nullptr;
}

bool WorkoutManager::workoutExists(int id) const {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id)
            return true;
    return false;
}

void WorkoutManager::saveToFile() const {
    ofstream ofs("workouts.txt");
    if (!ofs) { cout << "  Error saving workouts.\n"; return; }
    ofs << workoutCount << "\n";
    for (int i = 0; i < workoutCount; i++)
        workouts[i].saveToFile(ofs);
}

void WorkoutManager::loadFromFile() {
    ifstream ifs("workouts.txt");
    if (!ifs) return;
    ifs >> workoutCount; ifs.ignore();
    for (int i = 0; i < workoutCount; i++)
        workouts[i].loadFromFile(ifs);
}

void WorkoutManager::saveAssignments() const {
    ofstream ofs("workout_assignments.txt");
    if (!ofs) { cout << "  Error saving workout assignments.\n"; return; }
    ofs << assignCount << "\n";
    for (int i = 0; i < assignCount; i++)
        assignments[i].saveToFile(ofs);
}

void WorkoutManager::loadAssignments() {
    ifstream ifs("workout_assignments.txt");
    if (!ifs) return;
    ifs >> assignCount; ifs.ignore();
    for (int i = 0; i < assignCount; i++)
        assignments[i].loadFromFile(ifs);
}