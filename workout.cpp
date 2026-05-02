#include "workout.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

// exercise class

// sets all fields to empty or zero
Exercise::Exercise()
    : name(""), sets(0), reps(0), duration(""), notes("") {
}

// builds an exercise using the given values
Exercise::Exercise(string n, int s, int r, string dur, string nt)
    : name(n), sets(s), reps(r), duration(dur), notes(nt) {
}

// makes a copy of another exercise
Exercise::Exercise(const Exercise& o)
    : name(o.name), sets(o.sets), reps(o.reps),
    duration(o.duration), notes(o.notes) {
}

// copies all fields from another exercise into this one
Exercise& Exercise::operator=(const Exercise& o) {
    if (this != &o) {
        name = o.name; sets = o.sets; reps = o.reps;
        duration = o.duration; notes = o.notes;
    }
    return *this;
}

// getters
string Exercise::getName()     const { return name; }
int    Exercise::getSets()     const { return sets; }
int    Exercise::getReps()     const { return reps; }
string Exercise::getDuration() const { return duration; }
string Exercise::getNotes()    const { return notes; }

// setters
void Exercise::setName(string v) { name = v; }
void Exercise::setSets(int v) { sets = v; }
void Exercise::setReps(int v) { reps = v; }
void Exercise::setDuration(string v) { duration = v; }
void Exercise::setNotes(string v) { notes = v; }

// prints all exercise details to the screen
void Exercise::display() const {
    cout << "    Exercise : " << name << "\n"
        << "    Sets     : " << sets << "\n"
        << "    Reps     : " << reps << "\n"
        << "    Duration : " << duration << "\n"
        << "    Notes    : " << notes << "\n";
}

// saves exercise fields to a file one line at a time
void Exercise::saveToFile(ofstream& ofs) const {
    ofs << name << "\n" << sets << "\n" << reps << "\n"
        << duration << "\n" << notes << "\n";
}

// reads exercise fields from file in the same order they were saved
void Exercise::loadFromFile(ifstream& ifs) {
    getline(ifs, name);
    ifs >> sets >> reps; ifs.ignore();
    getline(ifs, duration);
    getline(ifs, notes);
}

// workout day class

// sets day number to 0 and exercise count to 0
WorkoutDay::WorkoutDay()
    : dayNumber(0), focus(""), exerciseCount(0) {
}

// sets the day number and focus area
WorkoutDay::WorkoutDay(int day, string f)
    : dayNumber(day), focus(f), exerciseCount(0) {
}

// copies all exercises from another workout day
WorkoutDay::WorkoutDay(const WorkoutDay& o)
    : dayNumber(o.dayNumber), focus(o.focus),
    exerciseCount(o.exerciseCount) {
    for (int i = 0; i < exerciseCount; i++)
        exercises[i] = o.exercises[i];
}

// copies all fields and exercises from another workout day into this one
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

// getters
int    WorkoutDay::getDayNumber()     const { return dayNumber; }
string WorkoutDay::getFocus()         const { return focus; }
int    WorkoutDay::getExerciseCount() const { return exerciseCount; }

// setters
void WorkoutDay::setDayNumber(int v) { dayNumber = v; }
void WorkoutDay::setFocus(string v) { focus = v; }

// adds an exercise to this day, maximum 20 exercises allowed
void WorkoutDay::addExercise(Exercise e) {
    if (exerciseCount < 20)
        exercises[exerciseCount++] = e;
    else
        cout << "  Exercise list for this day is full.\n";
}

// lets the user edit a specific exercise by its position in the list
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
    getline(cin, val); if (!val.empty()) exercises[index].setDuration(val);

    cout << "  Notes [" << exercises[index].getNotes() << "]: ";
    getline(cin, val); if (!val.empty()) exercises[index].setNotes(val);
}

// removes an exercise by position and shifts the rest left to close the gap
void WorkoutDay::removeExercise(int index) {
    if (index < 0 || index >= exerciseCount) {
        cout << "  Invalid exercise index.\n";
        return;
    }
    for (int i = index; i < exerciseCount - 1; i++)
        exercises[i] = exercises[i + 1]; // shift left
    exerciseCount--;
    cout << "  Exercise removed.\n";
}

// returns a read only reference to an exercise at the given position
const Exercise& WorkoutDay::getExercise(int index) const {
    return exercises[index];
}

// prints the day number, focus and all exercises
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

// saves the day number, focus, exercise count and each exercise to file
void WorkoutDay::saveToFile(ofstream& ofs) const {
    ofs << dayNumber << "\n" << focus << "\n" << exerciseCount << "\n";
    for (int i = 0; i < exerciseCount; i++)
        exercises[i].saveToFile(ofs);
}

// reads the day number, focus, exercise count and each exercise from file
void WorkoutDay::loadFromFile(ifstream& ifs) {
    ifs >> dayNumber; ifs.ignore();
    getline(ifs, focus);
    ifs >> exerciseCount; ifs.ignore();
    for (int i = 0; i < exerciseCount; i++)
        exercises[i].loadFromFile(ifs);
}

// workout class

// sets all fields to empty or zero
Workout::Workout()
    : workoutID(0), name(""), description(""), goal(""),
    difficulty(""), durationWeeks(0), dayCount(0) {
}

// builds a workout plan using the given values
Workout::Workout(int id, string n, string desc, string g,
    string diff, int weeks)
    : workoutID(id), name(n), description(desc), goal(g),
    difficulty(diff), durationWeeks(weeks), dayCount(0) {
}

// copies all days from another workout
Workout::Workout(const Workout& o)
    : workoutID(o.workoutID), name(o.name), description(o.description),
    goal(o.goal), difficulty(o.difficulty),
    durationWeeks(o.durationWeeks), dayCount(o.dayCount) {
    for (int i = 0; i < dayCount; i++)
        days[i] = o.days[i];
}

// copies all fields and days from another workout into this one
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

// nothing to clean up since no heap memory is used
Workout::~Workout() {}

// getters
int    Workout::getWorkoutID()     const { return workoutID; }
string Workout::getName()          const { return name; }
string Workout::getDescription()   const { return description; }
string Workout::getGoal()          const { return goal; }
string Workout::getDifficulty()    const { return difficulty; }
int    Workout::getDurationWeeks() const { return durationWeeks; }
int    Workout::getDayCount()      const { return dayCount; }

// setters
void Workout::setWorkoutID(int v) { workoutID = v; }
void Workout::setName(string v) { name = v; }
void Workout::setDescription(string v) { description = v; }
void Workout::setGoal(string v) { goal = v; }
void Workout::setDifficulty(string v) { difficulty = v; }
void Workout::setDurationWeeks(int v) { durationWeeks = v; }

// asks the user for a day number and focus then adds a new day, max 7 days
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

// lets the user change the focus of an existing day
void Workout::updateDay(int dayNumber) {
    WorkoutDay* d = findDay(dayNumber);
    if (!d) { cout << "  Day not found.\n"; return; }
    string val;
    cout << "  New Focus [" << d->getFocus() << "]: ";
    cin.ignore(); getline(cin, val);
    if (!val.empty()) d->setFocus(val);
    cout << "  Day updated.\n";
}

// removes a day by its number and shifts the remaining days left
void Workout::removeDay(int dayNumber) {
    for (int i = 0; i < dayCount; i++) {
        if (days[i].getDayNumber() == dayNumber) {
            for (int j = i; j < dayCount - 1; j++)
                days[j] = days[j + 1]; // shift left
            dayCount--;
            cout << "  Day " << dayNumber << " removed.\n";
            return;
        }
    }
    cout << "  Day not found.\n";
}

// looks through the days array and returns a pointer to the matching day or nullptr
WorkoutDay* Workout::findDay(int dayNumber) {
    for (int i = 0; i < dayCount; i++)
        if (days[i].getDayNumber() == dayNumber)
            return &days[i];
    return nullptr;
}

// prints all workout details including every day and its exercises
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

// prints a short one line summary used in list views
void Workout::displaySummary() const {
    cout << "  [W" << workoutID << "] " << name
        << " | " << goal << " | " << difficulty
        << " | " << durationWeeks << " wks | "
        << dayCount << " days\n";
}

// saves all workout fields and each day to file
void Workout::saveToFile(ofstream& ofs) const {
    ofs << workoutID << "\n" << name << "\n" << description << "\n"
        << goal << "\n" << difficulty << "\n"
        << durationWeeks << "\n" << dayCount << "\n";
    for (int i = 0; i < dayCount; i++)
        days[i].saveToFile(ofs);
}

// reads all workout fields and each day from file
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

// member workout assignment class

// sets all fields to empty or zero
MemberWorkoutAssignment::MemberWorkoutAssignment()
    : memberId(""), workoutID(0), startDate(""), progressNote("") {
}

// links a member to a workout with a start date
MemberWorkoutAssignment::MemberWorkoutAssignment(string mid, int wid, string date)
    : memberId(mid), workoutID(wid), startDate(date), progressNote("") {
}

// getters
string MemberWorkoutAssignment::getMemberId()     const { return memberId; }
int    MemberWorkoutAssignment::getWorkoutID()    const { return workoutID; }
string MemberWorkoutAssignment::getStartDate()    const { return startDate; }
string MemberWorkoutAssignment::getProgressNote() const { return progressNote; }

// setters
void MemberWorkoutAssignment::setWorkoutID(int wid) { workoutID = wid; }
void MemberWorkoutAssignment::setStartDate(string date) { startDate = date; }
void MemberWorkoutAssignment::setProgressNote(string note) { progressNote = note; }

// saves member id, workout id, start date and progress note to file
void MemberWorkoutAssignment::saveToFile(ofstream& ofs) const {
    ofs << memberId << "\n"
        << workoutID << "\n"
        << startDate << "\n"
        << progressNote << "\n";
}

// reads member id, workout id, start date and progress note from file
void MemberWorkoutAssignment::loadFromFile(ifstream& ifs) {
    getline(ifs, memberId);
    ifs >> workoutID; ifs.ignore();
    getline(ifs, startDate);
    getline(ifs, progressNote);
}

// workout manager class

// returns todays date as a yyyy mm dd string using the system clock
string WorkoutManager::currentDate() const {
    time_t now = time(nullptr);
    char buf[20];
    struct tm t; // standard library struct for holding date and time fields
#ifdef _WIN32
    localtime_s(&t, &now); // thread safe version for windows
#else
    localtime_r(&now, &t); // thread safe version for linux and mac
#endif
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t);
    return string(buf);
}

// sets counts to zero then loads saved data from disk
WorkoutManager::WorkoutManager() : workoutCount(0), assignCount(0) {
    loadFromFile();    // load workouts from workouts.txt
    loadAssignments(); // load assignments from workout_assignments.txt
}

// asks the user for details and adds a new workout plan to the array
void WorkoutManager::addWorkout() {
    if (workoutCount >= 100) {
        cout << "  Workout list full.\n";
        return;
    }
    int id = workoutCount + 1; // next id is based on current count
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

// prints a short summary of every workout in the list
void WorkoutManager::viewAllWorkouts() const {
    if (workoutCount == 0) { cout << "  No workout plans found.\n"; return; }
    cout << "\n  All Workout Plans\n";
    cout << "  " << string(60, '-') << "\n";
    for (int i = 0; i < workoutCount; i++)
        workouts[i].displaySummary();
    cout << "  " << string(60, '-') << "\n";
}

// finds a workout by id and prints its full details
void WorkoutManager::viewWorkoutDetail(int id) const {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id) {
            workouts[i].display();
            return;
        }
    cout << "  Workout W" << id << " not found.\n";
}

// searches for workouts whose name contains the keyword, not case sensitive
void WorkoutManager::searchWorkout(string keyword) const {
    cout << "\n  Search results for \"" << keyword << "\"\n";
    bool found = false;
    string kLow = keyword;
    for (char& c : kLow) c = tolower(c); // convert keyword to lowercase

    for (int i = 0; i < workoutCount; i++) {
        string nLow = workouts[i].getName();
        for (char& c : nLow) c = tolower(c); // convert workout name to lowercase
        if (nLow.find(kLow) != string::npos) {
            workouts[i].displaySummary();
            found = true;
        }
    }
    if (!found) cout << "  No matching workout found.\n";
}

// lets the user edit any field of a workout, pressing enter keeps the current value
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

// permanently deletes a workout and shifts the remaining ones left
void WorkoutManager::deleteWorkout(int id) {
    for (int i = 0; i < workoutCount; i++) {
        if (workouts[i].getWorkoutID() == id) {
            for (int j = i; j < workoutCount - 1; j++)
                workouts[j] = workouts[j + 1]; // shift left to fill gap
            workoutCount--;
            saveToFile();
            cout << "  Workout W" << id << " deleted.\n";
            return;
        }
    }
    cout << "  Workout not found.\n";
}

// shows a sub menu for adding, updating and removing days and exercises inside a workout
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
            d->removeExercise(idx - 1); // convert to zero based index
            saveToFile();
        }
    } while (choice != 0);
}

// links a workout to a member, each member can only have one workout at a time
void WorkoutManager::assignWorkoutToMember(string memberId, int workoutID) {
    if (!workoutExists(workoutID)) {
        cout << "  Workout W" << workoutID << " does not exist.\n";
        return;
    }
    // stop if the member already has a workout assigned
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            cout << "  Member already has workout W"
                << assignments[i].getWorkoutID() << " assigned. Use 'Change' to reassign.\n";
            return;
        }
    }
    if (assignCount >= 200) { cout << "  Assignment list full.\n"; return; }

    // create a new assignment with todays date
    assignments[assignCount++] = MemberWorkoutAssignment(memberId, workoutID, currentDate());
    saveAssignments();
    cout << "  Workout W" << workoutID << " assigned to member " << memberId << ".\n";
}

// replaces a members current workout with a new one, or creates a new assignment if none exists
void WorkoutManager::changeWorkoutForMember(string memberId, int newWorkoutID) {
    if (!workoutExists(newWorkoutID)) {
        cout << "  Workout W" << newWorkoutID << " not found.\n";
        return;
    }
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            int old = assignments[i].getWorkoutID(); // save old id for the message
            assignments[i].setWorkoutID(newWorkoutID);
            assignments[i].setStartDate(currentDate());
            saveAssignments();
            cout << "  Member " << memberId << " workout changed from W"
                << old << " to W" << newWorkoutID << ".\n";
            return;
        }
    }
    // no existing assignment so create a fresh one
    assignWorkoutToMember(memberId, newWorkoutID);
}

// removes the workout assignment for a member and shifts the array left
void WorkoutManager::removeWorkoutFromMember(string memberId) {
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            for (int j = i; j < assignCount - 1; j++)
                assignments[j] = assignments[j + 1]; // shift left to fill gap
            assignCount--;
            saveAssignments();
            cout << "  Workout removed from member " << memberId << ".\n";
            return;
        }
    }
    cout << "  No workout assigned to member " << memberId << ".\n";
}

// shows the workout currently assigned to a member along with full details
void WorkoutManager::viewMemberWorkout(string memberId) const {
    cout << "\n  Workout for Member: " << memberId << "\n";
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            int wid = assignments[i].getWorkoutID();
            cout << "  Assigned  : " << assignments[i].getStartDate() << "\n";

            // show progress note if one has been written
            if (!assignments[i].getProgressNote().empty())
                cout << "  Progress  : " << assignments[i].getProgressNote() << "\n";

            // find and display the full workout record
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

// updates the progress note for a members current workout assignment
void WorkoutManager::updateProgressNote(string memberId, string note) {
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            assignments[i].setProgressNote(note);
            saveAssignments();
            cout << "  Progress note updated.\n";
            return;
        }
    }
    cout << "  No workout assigned to member " << memberId << ".\n";
}

// lists all member workout assignments with their start dates
void WorkoutManager::viewAllMemberSchedules() const {
    cout << "\n  All Member Workout Assignments\n";
    if (assignCount == 0) { cout << "  No assignments.\n"; return; }
    for (int i = 0; i < assignCount; i++)
        cout << "  Member: " << assignments[i].getMemberId()
        << " -> W" << assignments[i].getWorkoutID()
        << " (since " << assignments[i].getStartDate() << ")\n";
}

// returns the workout id assigned to a member, or 0 if none is assigned
int WorkoutManager::getAssignedWorkoutID(string memberId) const {
    for (int i = 0; i < assignCount; i++)
        if (assignments[i].getMemberId() == memberId)
            return assignments[i].getWorkoutID();
    return 0; // 0 means no workout is assigned
}

// searches the workouts array and returns a pointer to the matching one or nullptr
Workout* WorkoutManager::findByID(int id) {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id)
            return &workouts[i];
    return nullptr;
}

// returns true if a workout with the given id exists
bool WorkoutManager::workoutExists(int id) const {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id)
            return true;
    return false;
}

// writes the full workout list to workouts.txt, overwrites the file each time
void WorkoutManager::saveToFile() const {
    ofstream ofs("workouts.txt");
    if (!ofs) { cout << "  Error saving workouts.\n"; return; }
    ofs << workoutCount << "\n"; // first line tells how many workouts follow
    for (int i = 0; i < workoutCount; i++)
        workouts[i].saveToFile(ofs);
}

// reads the workout list back from workouts.txt into the array
void WorkoutManager::loadFromFile() {
    ifstream ifs("workouts.txt");
    if (!ifs) return; // file does not exist yet, this is fine on first run
    ifs >> workoutCount; ifs.ignore();
    for (int i = 0; i < workoutCount; i++)
        workouts[i].loadFromFile(ifs);
}

// writes all member workout assignments to workout_assignments.txt
void WorkoutManager::saveAssignments() const {
    ofstream ofs("workout_assignments.txt");
    if (!ofs) { cout << "  Error saving workout assignments.\n"; return; }
    ofs << assignCount << "\n"; // first line tells how many assignments follow
    for (int i = 0; i < assignCount; i++)
        assignments[i].saveToFile(ofs);
}

// reads all member workout assignments back from workout_assignments.txt
void WorkoutManager::loadAssignments() {
    ifstream ifs("workout_assignments.txt");
    if (!ifs) return; // file does not exist yet, this is fine on first run
    ifs >> assignCount; ifs.ignore();
    for (int i = 0; i < assignCount; i++)
        assignments[i].loadFromFile(ifs);
}