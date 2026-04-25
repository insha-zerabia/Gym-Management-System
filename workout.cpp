#include "workout.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// Default constructor
Exercise::Exercise() : sets(0), reps(0) {}

// Parameterized constructor
Exercise::Exercise(string n, int s, int r, string dur, string nt)
    : name(n), sets(s), reps(r), duration(dur), notes(nt) {
}

// Copy constructor
Exercise::Exercise(const Exercise& o)
    : name(o.name), sets(o.sets), reps(o.reps),
    duration(o.duration), notes(o.notes) {
}

// Assignment operator
Exercise& Exercise::operator=(const Exercise& o) {
    if (this != &o) {
        name = o.name;
        sets = o.sets;
        reps = o.reps;
        duration = o.duration;
        notes = o.notes;
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

// Display exercise details
void Exercise::display() const {
    cout << "      • " << left << setw(22) << name;

    // Show duration OR sets/reps
    if (!duration.empty())
        cout << " | " << duration;
    else
        cout << " | " << sets << " sets x " << reps << " reps";

    // Show notes if available
    if (!notes.empty()) cout << " | Note: " << notes;

    cout << endl;
}

// Save exercise to file
void Exercise::saveToFile(ofstream& ofs) const {
    ofs << name << endl
        << sets << endl
        << reps << endl
        << duration << endl
        << notes << endl;
}

// Load exercise from file
void Exercise::loadFromFile(ifstream& ifs) {
    getline(ifs, name);           // read name
    ifs >> sets >> reps;
    ifs.ignore();                 // skip newline
    getline(ifs, duration);       // read duration
    getline(ifs, notes);          // read notes
}

// Default constructor for WorkoutDay
WorkoutDay::WorkoutDay() : dayNumber(0), exerciseCount(0) {}

// Parameterized constructor
WorkoutDay::WorkoutDay(int day, string f)
    : dayNumber(day), focus(f), exerciseCount(0) {
}

// Copy constructor
WorkoutDay::WorkoutDay(const WorkoutDay& o)
    : dayNumber(o.dayNumber), focus(o.focus), exerciseCount(o.exerciseCount) {
    for (int i = 0; i < exerciseCount; i++)
        exercises[i] = o.exercises[i];
}

// Assignment operator
WorkoutDay& WorkoutDay::operator=(const WorkoutDay& o) {
    if (this != &o) {
        dayNumber = o.dayNumber;
        focus = o.focus;
        exerciseCount = o.exerciseCount;

        // Copy exercises
        for (int i = 0; i < exerciseCount; i++)
            exercises[i] = o.exercises[i];
    }
    return *this;
}

// Getters
int    WorkoutDay::getDayNumber()    const { return dayNumber; }
string WorkoutDay::getFocus()        const { return focus; }
int    WorkoutDay::getExerciseCount()const { return exerciseCount; }

// Setters
void WorkoutDay::setDayNumber(int v) { dayNumber = v; }
void WorkoutDay::setFocus(string v) { focus = v; }

// Add new exercise to the day
void WorkoutDay::addExercise(Exercise e) {
    if (exerciseCount >= 20) {
        cout << "  Max 20 exercises per day." << endl;
        return;
    }

    exercises[exerciseCount++] = e;
}

// Update an existing exercise
void WorkoutDay::updateExercise(int idx) {
    if (idx < 0 || idx >= exerciseCount) {
        cout << "  Invalid exercise index." << endl;
        return;
    }

    Exercise& e = exercises[idx];
    string val;
    int n;

    cin.ignore(); // clear buffer

    // Update name
    cout << "  Name [" << e.getName() << "]: ";
    getline(cin, val);
    if (!val.empty()) e.setName(val);

    // Update duration
    cout << "  Duration (blank for sets/reps) [" << e.getDuration() << "]: ";
    getline(cin, val);
    e.setDuration(val);

    // If duration empty, update sets/reps
    if (val.empty()) {
        cout << "  Sets [" << e.getSets() << "]: ";
        cin >> n;
        if (n) e.setSets(n);

        cout << "  Reps [" << e.getReps() << "]: ";
        cin >> n;
        if (n) e.setReps(n);

        cin.ignore();
    }

    // Update notes
    cout << "  Notes [" << e.getNotes() << "]: ";
    getline(cin, val);
    if (!val.empty()) e.setNotes(val);

    cout << "  Exercise updated." << endl;
}
// Remove an exercise by index
void WorkoutDay::removeExercise(int idx) {
    if (idx < 0 || idx >= exerciseCount) {
        cout << "  Invalid index." << endl;
        return;
    }

    // Shift elements left
    for (int j = idx; j < exerciseCount - 1; j++)
        exercises[j] = exercises[j + 1];

    exerciseCount--;
    cout << "  Exercise removed." << endl;
}

// Get exercise at index
const Exercise& WorkoutDay::getExercise(int idx) const {
    return exercises[idx];
}

// Display all exercises for the day
void WorkoutDay::display() const {
    // Array for day names
    string dayNames[] = { "", "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };

    // Resolve day name
    string dname = (dayNumber >= 1 && dayNumber <= 7)
        ? dayNames[dayNumber]
        : "Day " + to_string(dayNumber);

    cout << "    Day " << dayNumber << " - " << dname
        << " | Focus: " << focus << endl;

    // Check if no exercises
    if (exerciseCount == 0)
        cout << "      (No exercises added)" << endl;
    else
        // Display each exercise
        for (int i = 0; i < exerciseCount; i++) {
            cout << "      " << (i + 1) << ". ";
            exercises[i].display();
        }
}

// Save WorkoutDay to file
void WorkoutDay::saveToFile(ofstream& ofs) const {
    ofs << dayNumber << endl
        << focus << endl
        << exerciseCount << endl;

    for (int i = 0; i < exerciseCount; i++)
        exercises[i].saveToFile(ofs);
}

// Load WorkoutDay from file
void WorkoutDay::loadFromFile(ifstream& ifs) {
    ifs >> dayNumber;
    ifs.ignore();

    getline(ifs, focus);

    ifs >> exerciseCount;
    ifs.ignore();

    // Load each exercise
    for (int i = 0; i < exerciseCount; i++)
        exercises[i].loadFromFile(ifs);
}

// Default constructor
Workout::Workout() : workoutID(0), durationWeeks(0), dayCount(0) {}

// Parameterized constructor
Workout::Workout(int id, string n, string desc, string g, string diff, int dur)
    : workoutID(id), name(n), description(desc), goal(g),
    difficulty(diff), durationWeeks(dur), dayCount(0) {
}

// Copy constructor
Workout::Workout(const Workout& o)
    : workoutID(o.workoutID), name(o.name), description(o.description),
    goal(o.goal), difficulty(o.difficulty), durationWeeks(o.durationWeeks),
    dayCount(o.dayCount) {

    // Copy days
    for (int i = 0; i < dayCount; i++)
        days[i] = o.days[i];
}

// Assignment operator
Workout& Workout::operator=(const Workout& o) {
    if (this != &o) {
        workoutID = o.workoutID;
        name = o.name;
        description = o.description;
        goal = o.goal;
        difficulty = o.difficulty;
        durationWeeks = o.durationWeeks;
        dayCount = o.dayCount;

        // Copy days
        for (int i = 0; i < dayCount; i++)
            days[i] = o.days[i];
    }
    return *this;
}

// Destructor
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

// Add a new workout day
void Workout::addDay() {
    if (dayCount >= 7) {
        cout << "  Max 7 days per workout plan." << endl;
        return;
    }

    int dayNum;
    string focus;

    // Input day details
    cout << "  Day number (1=Mon ... 7=Sun): ";
    cin >> dayNum;
    cin.ignore();

    cout << "  Focus (e.g. Chest & Triceps): ";
    getline(cin, focus);

    // Add new day
    days[dayCount++] = WorkoutDay(dayNum, focus);

    // Add exercises to this day
    char more = 'y';

    while (more == 'y' || more == 'Y') {
        string exName, dur, notes;
        int sets = 0, reps = 0;

        cout << "    Exercise name: ";
        getline(cin, exName);

        cout << "    Duration (leave blank for sets/reps): ";
        getline(cin, dur);

        // If duration not given, use sets/reps
        if (dur.empty()) {
            cout << "    Sets: ";
            cin >> sets;

            cout << "    Reps: ";
            cin >> reps;
            cin.ignore();
        }

        cout << "    Notes (optional): ";
        getline(cin, notes);

        // Add exercise to current day
        days[dayCount - 1].addExercise(
            Exercise(exName, sets, reps, dur, notes)
        );

        cout << "  Add another exercise? (y/n): ";
        cin >> more;
        cin.ignore();
    }

    cout << "  Day added." << endl;
}

// Update a specific day in workout
void Workout::updateDay(int dayNumber) {
    // Find the day
    WorkoutDay* d = findDay(dayNumber);
    if (!d) {
        cout << "  Day " << dayNumber << " not found in this plan." << endl;
        return;
    }

    int c;

    // Menu loop
    do {
        cout << endl << "  --- Day " << dayNumber << " (" << d->getFocus() << ") ---" << endl;
        cout << "  1. Change Focus" << endl;
        cout << "  2. Add Exercise" << endl;
        cout << "  3. Update Exercise" << endl;
        cout << "  4. Remove Exercise" << endl;
        cout << "  5. View Day" << endl;
        cout << "  0. Back" << endl << "  Choice: ";

        cin >> c;

        string val;
        int idx;

        switch (c) {
        case 1:
            cin.ignore();
            cout << "  New Focus [" << d->getFocus() << "]: ";
            getline(cin, val);
            if (!val.empty()) d->setFocus(val);
            break;

        case 2: {
            // Add new exercise
            string exName, dur, notes;
            int sets = 0, reps = 0;

            cin.ignore();
            cout << "  Exercise name: ";
            getline(cin, exName);

            cout << "  Duration (blank for sets/reps): ";
            getline(cin, dur);

            // Use sets/reps if duration empty
            if (dur.empty()) {
                cout << "  Sets: ";
                cin >> sets;

                cout << "  Reps: ";
                cin >> reps;
                cin.ignore();
            }

            cout << "  Notes: ";
            getline(cin, notes);

            d->addExercise(Exercise(exName, sets, reps, dur, notes));
            cout << "  Exercise added." << endl;
            break;
        }

        case 3:
            // Update exercise
            d->display();
            cout << "  Exercise number to update: ";
            cin >> idx;
            d->updateExercise(idx - 1);
            break;

        case 4:
            // Remove exercise
            d->display();
            cout << "  Exercise number to remove: ";
            cin >> idx;
            d->removeExercise(idx - 1);
            break;

        case 5:
            // View day
            d->display();
            break;
        }

    } while (c != 0);
}

// Remove a day from workout
void Workout::removeDay(int dayNumber) {
    for (int i = 0; i < dayCount; i++) {
        if (days[i].getDayNumber() == dayNumber) {

            // Shift days left
            for (int j = i; j < dayCount - 1; j++)
                days[j] = days[j + 1];

            dayCount--;
            cout << "  Day " << dayNumber << " removed." << endl;
            return;
        }
    }

    cout << "  Day not found." << endl;
}

// Find day by number
WorkoutDay* Workout::findDay(int dayNumber) {
    for (int i = 0; i < dayCount; i++)
        if (days[i].getDayNumber() == dayNumber)
            return &days[i];

    return nullptr;
}

// Display summary (one-line view)
void Workout::displaySummary() const {
    cout << "  [W" << setw(3) << setfill('0') << workoutID << setfill(' ') << "] "
        << left << setw(22) << name
        << " | " << left << setw(12) << goal
        << " | " << left << setw(13) << difficulty
        << " | " << durationWeeks << " wk(s)" << endl;
}

// Display full workout details
void Workout::display() const {
    cout << endl;

    cout << "   Workout ID  : " << left << setw(22) << workoutID << endl;
    cout << "   Name        : " << left << setw(22) << name << endl;
    cout << "   Description : " << left << setw(22) << description << endl;
    cout << "   Goal        : " << left << setw(22) << goal << endl;
    cout << "   Difficulty  : " << left << setw(22) << difficulty << endl;
    cout << "   Duration    : " << left << setw(19) << durationWeeks << " wk(s)" << endl;

    cout << endl;

    // Check if schedule exists
    if (dayCount == 0) {
        cout << "  (No daily schedule added yet)" << endl;
    }
    else {
        cout << "  Weekly Schedule: " << endl;

        // Display each day
        for (int i = 0; i < dayCount; i++)
            days[i].display();
    }
}

// Save workout to file
void Workout::saveToFile(ofstream& ofs) const {
    ofs << workoutID << endl
        << name << endl
        << description << endl
        << goal << endl
        << difficulty << endl
        << durationWeeks << endl
        << dayCount << endl;

    // Save each day
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
    for (int i = 0; i < dayCount; i++) days[i].loadFromFile(ifs);
}

// Default constructor
MemberWorkoutAssignment::MemberWorkoutAssignment()
    : memberId(""), workoutID(0), startDate(""), progressNote("") {
}

// Parameterized constructor
MemberWorkoutAssignment::MemberWorkoutAssignment(string mid, int wid, string date)
    : memberId(mid), workoutID(wid), startDate(date), progressNote("") {
}

// Save assignment data to file
void MemberWorkoutAssignment::saveToFile(ofstream& ofs) const {
    ofs << memberId << endl
        << workoutID << endl
        << startDate << endl
        << progressNote << endl;
}

// Load assignment data from file
void MemberWorkoutAssignment::loadFromFile(ifstream& ifs) {
    getline(ifs, memberId);
    ifs >> workoutID;
    ifs.ignore();
    getline(ifs, startDate);
    getline(ifs, progressNote);
}

// Constructor initializes and loads saved data
WorkoutManager::WorkoutManager() : workoutCount(0), assignCount(0) {
    loadFromFile();
    loadAssignments();
}

// Get current system date in YYYY-MM-DD format
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

// Add a new workout plan
void WorkoutManager::addWorkout() {
    if (workoutCount >= 100) {
        cout << "  Workout list full." << endl;
        return;
    }

    int id = workoutCount + 1;
    string name, desc, goal, diff;
    int dur;

    cout << endl << "  === Create Workout Plan ===" << endl;
    cout << "  Auto-assigned ID : W"
        << setw(3) << setfill('0') << id << setfill(' ') << endl;

    cin.ignore();

    cout << "  Name             : ";
    getline(cin, name);

    cout << "  Description      : ";
    getline(cin, desc);

    cout << "  Goal (e.g. Weight Loss / Muscle Gain / Endurance): ";
    getline(cin, goal);

    cout << "  Difficulty (Beginner / Intermediate / Advanced)  : ";
    getline(cin, diff);

    cout << "  Duration (weeks) : ";
    cin >> dur;
    cin.ignore();

    // Store workout
    workouts[workoutCount++] = Workout(id, name, desc, goal, diff, dur);

    // Optional: add schedule immediately
    char add;
    cout << "  Add daily schedule now? (y/n): ";
    cin >> add;
    cin.ignore();

    if (add == 'y' || add == 'Y')
        manageDays(id);

    saveToFile();
    cout << "  Workout plan saved." << endl;
}

// Display all workouts
void WorkoutManager::viewAllWorkouts() const {
    if (workoutCount == 0) {
        cout << "  No workout plans available." << endl;
        return;
    }

    cout << endl << "  === All Workout Plans ===" << endl;
    cout << "  " << string(70, '-') << endl;

    for (int i = 0; i < workoutCount; i++)
        workouts[i].displaySummary();

    cout << "  " << string(70, '-') << endl;
}

// Display full workout details
void WorkoutManager::viewWorkoutDetail(int id) const {
    for (int i = 0; i < workoutCount; i++) {
        if (workouts[i].getWorkoutID() == id) {
            workouts[i].display();
            return;
        }
    }

    cout << "  Workout ID " << id << " not found." << endl;
}

// Search workout by keyword (name or goal)
void WorkoutManager::searchWorkout(string keyword) const {
    cout << endl << "  === Search Results for \"" << keyword << "\" ===" << endl;

    bool found = false;

    for (int i = 0; i < workoutCount; i++) {
        string n = workouts[i].getName();
        string g = workouts[i].getGoal();

        // Convert to lowercase for comparison
        string nLow = n, gLow = g, kLow = keyword;
        for (char& c : nLow) c = tolower(c);
        for (char& c : gLow) c = tolower(c);
        for (char& c : kLow) c = tolower(c);

        // Match keyword
        if (nLow.find(kLow) != string::npos ||
            gLow.find(kLow) != string::npos) {

            workouts[i].displaySummary();
            found = true;
        }
    }

    if (!found)
        cout << "  No workout found matching \"" << keyword << "\"." << endl;
}

// Update workout details
void WorkoutManager::updateWorkout(int id) {
    // Find workout by ID
    Workout* w = findByID(id);

    if (!w) {
        cout << "  Workout not found." << endl;
        return;
    }

    int c;

    // Menu loop for updating workout
    do {
        cout << endl << "  === Update Workout: " << w->getName() << " ===" << endl;
        cout << "  1. Edit Basic Info (name/description/goal/difficulty/duration)" << endl;
        cout << "  2. Manage Daily Schedule" << endl;
        cout << "  0. Back" << endl << "  Choice: ";

        cin >> c;

        if (c == 1) {
            // Edit basic workout info
            string val;
            int n;

            cin.ignore();

            cout << "  Name [" << w->getName() << "]: ";
            getline(cin, val);
            if (!val.empty()) w->setName(val);

            cout << "  Description [" << w->getDescription() << "]: ";
            getline(cin, val);
            if (!val.empty()) w->setDescription(val);

            cout << "  Goal [" << w->getGoal() << "]: ";
            getline(cin, val);
            if (!val.empty()) w->setGoal(val);

            cout << "  Difficulty [" << w->getDifficulty() << "]: ";
            getline(cin, val);
            if (!val.empty()) w->setDifficulty(val);

            cout << "  Duration weeks (0=keep) [" << w->getDurationWeeks() << "]: ";
            cin >> n;
            if (n) w->setDurationWeeks(n);
            cin.ignore();

            saveToFile();
            cout << "  Basic info updated." << endl;
        }
        else if (c == 2) {
            // Manage workout days
            manageDays(id);
            saveToFile();
        }

    } while (c != 0);
}

// Delete workout by ID
void WorkoutManager::deleteWorkout(int id) {
    for (int i = 0; i < workoutCount; i++) {
        if (workouts[i].getWorkoutID() == id) {

            // Shift array left
            for (int j = i; j < workoutCount - 1; j++)
                workouts[j] = workouts[j + 1];

            workoutCount--;
            saveToFile();

            cout << "  Workout deleted." << endl;
            return;
        }
    }

    cout << "  Workout not found." << endl;
}

// Manage workout days (add/update/remove/view)
void WorkoutManager::manageDays(int wid) {
    Workout* w = findByID(wid);

    if (!w) {
        cout << "  Workout not found." << endl;
        return;
    }

    int c;

    // Menu loop for day management
    do {
        cout << endl << "  === Schedule Manager: " << w->getName() << " ===" << endl;
        cout << "  1. Add Day" << endl;
        cout << "  2. Update Day" << endl;
        cout << "  3. Remove Day" << endl;
        cout << "  4. View Full Schedule" << endl;
        cout << "  0. Done" << endl << "  Choice: ";

        cin >> c;

        int day;

        switch (c) {
        case 1:
            // Add new day
            w->addDay();
            saveToFile();
            break;

        case 2:
            // Update existing day
            cout << "  Day number to update: ";
            cin >> day;
            w->updateDay(day);
            saveToFile();
            break;

        case 3:
            // Remove day
            cout << "  Day number to remove: ";
            cin >> day;
            w->removeDay(day);
            saveToFile();   // fixed missing save call
            break;

        case 4:
            // Show full schedule
            w->display();
            break;
        }

    } while (c != 0);
}

// Assign workout to a member
void WorkoutManager::assignWorkoutToMember(string memberId, int wid) {
    if (!workoutExists(wid)) {
        cout << "  Workout not found." << endl;
        return;
    }

    // Check if member already has assignment
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            cout << "  Member already has Workout W"
                << setw(3) << setfill('0') << assignments[i].workoutID
                << setfill(' ')
                << " assigned. Use 'Change Workout' to reassign." << endl;
            return;
        }
    }

    if (assignCount >= 200) {
        cout << "  Assignment list full." << endl;
        return;
    }

    // Add assignment
    assignments[assignCount++] = MemberWorkoutAssignment(memberId, wid, currentDate());
    saveAssignments();

    Workout* w = findByID(wid);

    cout << "  Workout W"
        << setw(3) << setfill('0') << wid << setfill(' ')
        << " (" << (w ? w->getName() : "?") << ") assigned to member "
        << memberId << " starting " << currentDate() << "." << endl;
}

// Change existing workout assignment
void WorkoutManager::changeWorkoutForMember(string memberId, int newWid) {
    if (!workoutExists(newWid)) {
        cout << "  Workout not found." << endl;
        return;
    }

    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {

            int old = assignments[i].workoutID;

            // Update assignment
            assignments[i].workoutID = newWid;
            assignments[i].startDate = currentDate();
            assignments[i].progressNote = "";

            saveAssignments();

            Workout* w = findByID(newWid);

            cout << "  Member " << memberId << " workout changed from W"
                << setw(3) << setfill('0') << old << " to W"
                << setw(3) << setfill('0') << newWid << setfill(' ')
                << " (" << (w ? w->getName() : "?") << ")." << endl;

            return;
        }
    }

    // If no previous assignment, create new one
    assignWorkoutToMember(memberId, newWid);
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
    cout << "  No workout assigned to this member.\n";
}

void WorkoutManager::viewMemberWorkout(string memberId) const {
    cout << "\n  === Workout Plan for Member: " << memberId << " ===\n";
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            int wid = assignments[i].workoutID;
            cout << "  Started    : " << assignments[i].startDate << "\n";
            if (!assignments[i].progressNote.empty())
                cout << "  Progress   : " << assignments[i].progressNote << "\n";
            for (int j = 0; j < workoutCount; j++) {
                if (workouts[j].getWorkoutID() == wid) {
                    workouts[j].display();
                    return;
                }
            }
            cout << "  Workout ID " << wid << " (details missing).\n";
            return;
        }
    }
    cout << "  No workout plan assigned yet.\n";
}
// Update progress note for a member's workout
void WorkoutManager::updateProgressNote(string memberId, string note) {
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            assignments[i].progressNote = note;
            saveAssignments();
            cout << "  Progress note updated." << endl;
            return;
        }
    }
    cout << "  No workout assigned to this member." << endl;
}

// Display all member workout assignments
void WorkoutManager::viewAllMemberSchedules() const {
    if (assignCount == 0) {
        cout << "  No workout assignments yet." << endl;
        return;
    }

    cout << endl << "  === All Member Workout Assignments ===" << endl;
    cout << "  " << string(65, '-') << endl;

    // Table header
    cout << "  " << left << setw(12) << "Member"
        << setw(10) << "WorkoutID"
        << setw(15) << "Start Date"
        << "Progress Note" << endl;

    cout << "  " << string(65, '-') << endl;

    // Display each assignment
    for (int i = 0; i < assignCount; i++) {
        cout << "  " << left << setw(12) << assignments[i].memberId
            << setw(10) << ("W" + to_string(assignments[i].workoutID))
            << setw(15) << assignments[i].startDate
            << (assignments[i].progressNote.empty() ? "-" : assignments[i].progressNote)
            << endl;
    }
}

// Get workout ID assigned to a member
int WorkoutManager::getAssignedWorkoutID(string memberId) const {
    for (int i = 0; i < assignCount; i++)
        if (assignments[i].memberId == memberId)
            return assignments[i].workoutID;

    return 0;
}

// Find workout by ID
Workout* WorkoutManager::findByID(int id) {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id)
            return &workouts[i];

    return nullptr;
}

// Check if workout exists
bool WorkoutManager::workoutExists(int id) const {
    for (int i = 0; i < workoutCount; i++)
        if (workouts[i].getWorkoutID() == id)
            return true;

    return false;
}

// Save all workouts to file
void WorkoutManager::saveToFile() const {
    ofstream ofs("workouts.txt");

    if (!ofs) {
        cout << "  Error saving workouts." << endl;
        return;
    }

    ofs << workoutCount << endl;

    for (int i = 0; i < workoutCount; i++)
        workouts[i].saveToFile(ofs);
}

// Load workouts from file
void WorkoutManager::loadFromFile() {
    ifstream ifs("workouts.txt");

    if (!ifs) return;

    ifs >> workoutCount;
    ifs.ignore();

    for (int i = 0; i < workoutCount; i++)
        workouts[i].loadFromFile(ifs);
}

// Save assignments to file
void WorkoutManager::saveAssignments() const {
    ofstream ofs("workout_assignments.txt");

    if (!ofs) {
        cout << "  Error saving workout assignments." << endl;
        return;
    }

    ofs << assignCount << endl;

    for (int i = 0; i < assignCount; i++)
        assignments[i].saveToFile(ofs);
}
// Load assignments from file
void WorkoutManager::loadAssignments() {
    ifstream ifs("workout_assignments.txt");

    if (!ifs) return;

    ifs >> assignCount;
    ifs.ignore();

    for (int i = 0; i < assignCount; i++)
        assignments[i].loadFromFile(ifs);
}