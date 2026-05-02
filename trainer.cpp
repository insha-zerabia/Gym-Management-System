#include "trainer.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;


// default constructor which sets all fields to empty defaults
Trainer::Trainer()
    : trainerID(0), name(""), specialization(""), contactNumber(""),
    email(""), availability(""), experienceYears(0), isActive(true) {
}

// parameterized constructor which builds a trainer from given values
Trainer::Trainer(int id, string n, string spec, string contact,
    string em, string avail, int exp)
    : trainerID(id), name(n), specialization(spec), contactNumber(contact),
    email(em), availability(avail), experienceYears(exp), isActive(true) {
}

// copy constructor which makes a new Trainer as an exact copy of another
Trainer::Trainer(const Trainer& o)
    : trainerID(o.trainerID), name(o.name), specialization(o.specialization),
    contactNumber(o.contactNumber), email(o.email), availability(o.availability),
    experienceYears(o.experienceYears), isActive(o.isActive) {
}

// assignment operator which copies all fields from rhs into this trainer
Trainer& Trainer::operator=(const Trainer& o) {
    if (this != &o) {           // guard against self-assignment (e.g. t = t)
        trainerID = o.trainerID;
        name = o.name;
        specialization = o.specialization;
        contactNumber = o.contactNumber;
        email = o.email;
        availability = o.availability;
        experienceYears = o.experienceYears;
        isActive = o.isActive;
    }
    return *this;               // return the updated object
}

// destructor
Trainer::~Trainer() {}

// getters where each returns the matching private field
int    Trainer::getTrainerID()       const { return trainerID; }
string Trainer::getName()            const { return name; }
string Trainer::getSpecialization()  const { return specialization; }
string Trainer::getContactNumber()   const { return contactNumber; }
string Trainer::getEmail()           const { return email; }
string Trainer::getAvailability()    const { return availability; }
int    Trainer::getExperienceYears() const { return experienceYears; }
bool   Trainer::getIsActive()        const { return isActive; }

// setters where each updates the matching private field
void Trainer::setTrainerID(int v) { trainerID = v; }
void Trainer::setName(string v) { name = v; }
void Trainer::setSpecialization(string v) { specialization = v; }
void Trainer::setContactNumber(string v) { contactNumber = v; }
void Trainer::setEmail(string v) { email = v; }
void Trainer::setAvailability(string v) { availability = v; }
void Trainer::setExperienceYears(int v) { experienceYears = v; }
void Trainer::setIsActive(bool v) { isActive = v; }

// compares two trainers by ID then returns true if they are the same trainer
bool Trainer::operator==(const Trainer& rhs) const {
    return trainerID == rhs.trainerID;
}


void Trainer::display() const {
    cout << "  \n";
    cout << "   Trainer ID    : " << left << setw(16) << trainerID << "\n";
    cout << "   Name          : " << left << setw(16) << name << "\n";
    cout << "   Specialization: " << left << setw(16) << specialization << "\n";
    cout << "    Contact       : " << left << setw(16) << contactNumber << "\n";
    cout << "    Email         : " << left << setw(16) << email << "\n";
    cout << "    Availability  : " << left << setw(16) << availability << "\n";
    cout << "    Experience    : " << left << setw(13) << experienceYears << " yr\n";
    cout << "   Status        : " << left << setw(16) << (isActive ? "Active" : "Inactive") << "\n";
    cout << "  \n";
}

// prints a single compact summary line
void Trainer::displayCompact() const {
    cout << "  [T" << setw(3) << setfill('0') << trainerID << setfill(' ') << "] "
        << left << setw(20) << name
        << " | " << left << setw(15) << specialization
        << " | " << experienceYears << " yrs"
        << (isActive ? "" : " [INACTIVE]") << "\n";
}

// writes all trainer fields line by line to an open file stream
void Trainer::saveToFile(ofstream& ofs) const {
    ofs << trainerID << "\n"
        << name << "\n"
        << specialization << "\n"
        << contactNumber << "\n"
        << email << "\n"
        << availability << "\n"
        << experienceYears << "\n"
        << isActive << "\n";
}

// reads trainer fields from file in the same order they were saved
void Trainer::loadFromFile(ifstream& ifs) {
    ifs >> trainerID; ifs.ignore();   // read id
    getline(ifs, name);
    getline(ifs, specialization);
    getline(ifs, contactNumber);
    getline(ifs, email);
    getline(ifs, availability);
    ifs >> experienceYears >> isActive;
    ifs.ignore();                     // discard newline after last numeric field
}


// default constructor blank assignment that has no trainer linked
MemberTrainerAssignment::MemberTrainerAssignment()
    : memberId(""), trainerID(0), assignedDate("") {
}

// parameterized constructor which creates a link between a member, a trainer, and a date
MemberTrainerAssignment::MemberTrainerAssignment(string mid, int tid, string date)
    : memberId(mid), trainerID(tid), assignedDate(date) {
}

// getters
string MemberTrainerAssignment::getMemberId()     const { return memberId; }
int    MemberTrainerAssignment::getTrainerID()    const { return trainerID; }
string MemberTrainerAssignment::getAssignedDate() const { return assignedDate; }

// setters
void MemberTrainerAssignment::setTrainerID(int tid) { trainerID = tid; }      // updates linked trainer
void MemberTrainerAssignment::setAssignedDate(string date) { assignedDate = date; }  // updates the assignment date

// writes member ID, trainer ID, and date to file
void MemberTrainerAssignment::saveToFile(ofstream& ofs) const {
    ofs << memberId << endl
        << trainerID << endl
        << assignedDate << endl;
}

// reads member ID, trainer ID, and date from file
void MemberTrainerAssignment::loadFromFile(ifstream& ifs) {
    getline(ifs, memberId);      // read member ID string
    ifs >> trainerID;
    ifs.ignore();                // skip newline after trainer ID
    getline(ifs, assignedDate);  // read date string
}

// constructor which initializes counts to zero then loads saved data from disk
TrainerManager::TrainerManager() : trainerCount(0), assignCount(0) {
    loadFromFile();    // fill trainers[] from trainers.txt
    loadAssignments(); // fill assignments[] from trainer_assignments.txt
}

// returns today's date as a "YYYY-MM-DD" string
string TrainerManager::currentDate() const {
    time_t now = time(nullptr); // get current time as seconds
    char buf[20]; // create a place to store the date as a string
    struct tm t; //prepare a structure to hold date and time parts

#ifdef _WIN32
    localtime_s(&t, &now);  // Get local time safely on Windows
#else
    localtime_r(&now, &t);  // Get local time safely on Linux/Mac
#endif

    strftime(buf, sizeof(buf), "%Y-%m-%d", &t); // Make date string like 2024-04-27
    return string(buf); // Return the date as a string

    // prompts the user for details and adds a new trainer to the array
    void TrainerManager::addTrainer() {
        if (trainerCount >= 100) {   // array is full, cannot add more
            cout << "  Trainer list full." << endl;
            return;
        }

        int id = trainerCount + 1;   // autogenerate next sequential ID
        string name, spec, contact, email, avail;
        int exp;

        cout << endl << "  Add New Trainer" << endl;
        cout << "  Auto-assigned ID  : T"
            << setw(3) << setfill('0') << id << setfill(' ') << endl;

        cin.ignore();

        // Collect all trainer info from the user
        cout << "  Name              : "; getline(cin, name);
        cout << "  Specialization    : "; getline(cin, spec);
        cout << "  Contact Number    : "; getline(cin, contact);
        cout << "  Email             : "; getline(cin, email);
        cout << "  Availability      : "; getline(cin, avail);
        cout << "  Experience (years): "; cin >> exp;
        cin.ignore();

        trainers[trainerCount++] = Trainer(id, name, spec, contact, email, avail, exp); // store in array
        saveToFile();

        cout << "  Trainer added successfully with ID: T"
            << setw(3) << setfill('0') << id << setfill(' ') << endl;
    }

    // Loops through all trainers and prints their full details
    void TrainerManager::viewAllTrainers() const {
        if (trainerCount == 0) {
            cout << "  No trainers registered." << endl;
            return;
        }

        cout << endl << "  All Trainers" << endl;

        for (int i = 0; i < trainerCount; i++)
            trainers[i].display();
    }

    // Prints a compact list of only the active trainers
    void TrainerManager::viewActiveTrainers() const {
        cout << endl << "  Active Trainers" << endl;
        cout << "  " << string(60, '-') << endl;

        bool any = false;

        for (int i = 0; i < trainerCount; i++) {
            if (trainers[i].getIsActive()) {  // skip inactive trainers
                trainers[i].displayCompact();
                any = true;
            }
        }

        if (!any)
            cout << "  No active trainers." << endl;

        cout << "  " << string(60, '-') << endl;
    }

    // Searches the array for a trainer matching the given ID and displays them
    void TrainerManager::searchTrainerByID(int id) const {
        for (int i = 0; i < trainerCount; i++) {
            if (trainers[i].getTrainerID() == id) {
                cout << endl << "  Trainer Found" << endl;
                trainers[i].display();
                return;
            }
        }
        cout << "  Trainer with ID " << id << " not found." << endl;
    }

    // Searches for trainers whose name contains the keyword (case-insensitive)
    void TrainerManager::searchTrainerByName(string keyword) const {
        cout << endl << "  Search Results for \"" << keyword << "\"" << endl;

        bool found = false;

        for (int i = 0; i < trainerCount; i++) {
            string n = trainers[i].getName();

            // Lowercase both strings so the comparison ignores case
            string nLow = n, kLow = keyword;
            for (char& c : nLow) c = tolower(c);
            for (char& c : kLow) c = tolower(c);

            if (nLow.find(kLow) != string::npos) { // keyword found somewhere inside the name
                trainers[i].displayCompact();
                found = true;
            }
        }

        if (!found)
            cout << "  No trainer found matching \"" << keyword << "\"." << endl;
    }

    // Lets the user edit any field of an existing trainer (Enter = keep current value)
    void TrainerManager::updateTrainer(int id) {
        Trainer* t = findByID(id);   // locate the trainer by ID
        if (!t) { cout << "  Trainer not found." << endl; return; }

        cout << endl << "  Update Trainer (press Enter to keep current value)" << endl;

        string val;
        int n;

        cin.ignore();

        // For each field: show current value, read new input, only update if not empty
        cout << "  Name [" << t->getName() << "]: ";
        getline(cin, val);
        if (!val.empty()) t->setName(val);

        cout << "  Specialization [" << t->getSpecialization() << "]: ";
        getline(cin, val);
        if (!val.empty()) t->setSpecialization(val);

        cout << "  Contact [" << t->getContactNumber() << "]: ";
        getline(cin, val);
        if (!val.empty()) t->setContactNumber(val);

        cout << "  Email [" << t->getEmail() << "]: ";
        getline(cin, val);
        if (!val.empty()) t->setEmail(val);

        cout << "  Availability [" << t->getAvailability() << "]: ";
        getline(cin, val);
        if (!val.empty()) t->setAvailability(val);

        cout << "  Experience years (0 = keep) [" << t->getExperienceYears() << "]: ";
        cin >> n;
        if (n > 0) t->setExperienceYears(n); // 0 means user wants to keep the old value
        cin.ignore();

        saveToFile(); // write updated data to disk
        cout << "  Trainer updated successfully." << endl;
    }

    // Marks a trainer as inactive (soft delete – data is kept, trainer just won't appear in active lists)
    void TrainerManager::deactivateTrainer(int id) {
        Trainer* t = findByID(id);
        if (!t) { cout << "  Trainer not found." << endl; return; }

        t->setIsActive(false); // flag as inactive without removing the record
        saveToFile();

        cout << "  Trainer T" << setw(3) << setfill('0') << id << setfill(' ')
            << " deactivated (records preserved)." << endl;
    }

    // Permanently removes a trainer from the array by shifting remaining entries left
    void TrainerManager::deleteTrainer(int id) {
        for (int i = 0; i < trainerCount; i++) {
            if (trainers[i].getTrainerID() == id) {

                // Overwrite the deleted slot by shifting everything after it one step left
                for (int j = i; j < trainerCount - 1; j++)
                    trainers[j] = trainers[j + 1];

                trainerCount--;  // shrink the active count
                saveToFile();

                cout << "  Trainer deleted." << endl;
                return;
            }
        }
        cout << "  Trainer not found." << endl;
    }

    // Links a trainer to a member where each member can only have one trainer at a time
    void TrainerManager::assignTrainerToMember(string memberId, int trainerID) {
        Trainer* t = findByID(trainerID);
        if (!t) { cout << "  Trainer not found." << endl; return; }
        if (!t->getIsActive()) { cout << "  Cannot assign: trainer is inactive." << endl; return; }

        // Block if member already has a trainer assigned
        for (int i = 0; i < assignCount; i++) {
            if (assignments[i].getMemberId() == memberId) {
                cout << "  Member already has Trainer T"
                    << setw(3) << setfill('0') << assignments[i].getTrainerID()
                    << setfill(' ') << " assigned." << endl;
                cout << "  Use 'Change Trainer' to reassign." << endl;
                return;
            }
        }

        if (assignCount >= 200) {  // assignment array is full
            cout << "  Assignment list full." << endl;
            return;
        }

        // Create and store the new assignment with today's date
        assignments[assignCount++] = MemberTrainerAssignment(memberId, trainerID, currentDate());
        saveAssignments();

        cout << "  Trainer T" << setw(3) << setfill('0') << trainerID << setfill(' ')
            << " (" << t->getName() << ") assigned to member " << memberId
            << " on " << currentDate() << "." << endl;
    }

    // Swaps a member's current trainer for a new one (or creates first assignment if none exists)
    void TrainerManager::changeTrainerForMember(string memberId, int newTrainerID) {
        Trainer* t = findByID(newTrainerID);
        if (!t) { cout << "  New trainer not found." << endl; return; }
        if (!t->getIsActive()) { cout << "  Cannot assign: trainer is inactive." << endl; return; }

        for (int i = 0; i < assignCount; i++) {
            if (assignments[i].getMemberId() == memberId) {
                int old = assignments[i].getTrainerID(); // remember old trainer ID for the log

                // Update the existing assignment in place
                assignments[i].setTrainerID(newTrainerID);
                assignments[i].setAssignedDate(currentDate());

                saveAssignments();

                cout << "  Member " << memberId << " trainer changed from T"
                    << setw(3) << setfill('0') << old << " to T"
                    << setw(3) << setfill('0') << newTrainerID << setfill(' ')
                    << " (" << t->getName() << ")." << endl;
                return;
            }
        }

        // No existing assignment found so create a fresh one instead
        assignTrainerToMember(memberId, newTrainerID);
    }

    // Removes the trainer assignment for a member by shifting the array left
    void TrainerManager::removeTrainerFromMember(string memberId) {
        for (int i = 0; i < assignCount; i++) {
            if (assignments[i].getMemberId() == memberId) {

                // Fill the gap by shifting everything after it one step left
                for (int j = i; j < assignCount - 1; j++)
                    assignments[j] = assignments[j + 1];

                assignCount--;
                saveAssignments();
                cout << "  Trainer removed from member " << memberId << "." << endl;
                return;
            }
        }
        cout << "  No trainer assigned to member " << memberId << "." << endl;
    }

    // Shows which trainer is currently assigned to a given member, with full details
    void TrainerManager::viewMemberTrainer(string memberId) const {
        cout << endl << "  === Assigned Trainer for Member: " << memberId << " ===" << endl;

        for (int i = 0; i < assignCount; i++) {
            if (assignments[i].getMemberId() == memberId) {
                int tid = assignments[i].getTrainerID();

                cout << "  Assigned on : " << assignments[i].getAssignedDate() << endl;

                // Look up and display the trainer's full record
                for (int j = 0; j < trainerCount; j++) {
                    if (trainers[j].getTrainerID() == tid) {
                        trainers[j].display();
                        return;
                    }
                }

                // Assignment exists but trainer record is missing (data inconsistency)
                cout << "  Trainer ID " << tid << " (details not found)." << endl;
                return;
            }
        }

        cout << "  No trainer assigned yet." << endl;
    }

    // Lists all members that are currently assigned to a specific trainer
    void TrainerManager::viewTrainerMembers(int trainerID) const {
        cout << endl << "  === Members assigned to Trainer T"
            << setw(3) << setfill('0') << trainerID << setfill(' ') << " ===" << endl;

        bool found = false;

        for (int i = 0; i < assignCount; i++) {
            if (assignments[i].getTrainerID() == trainerID) {
                cout << "  Member: " << assignments[i].getMemberId()
                    << "  (since " << assignments[i].getAssignedDate() << ")" << endl;
                found = true;
            }
        }

        if (!found)
            cout << "  No members assigned to this trainer." << endl;
    }

    // Returns the trainer ID linked to a member, or 0 if none is assigned
    int TrainerManager::getAssignedTrainerID(string memberId) const {
        for (int i = 0; i < assignCount; i++)
            if (assignments[i].getMemberId() == memberId)
                return assignments[i].getTrainerID();

        return 0; // 0 signals "no trainer assigned"
    }

    // Scans the trainers array and returns a pointer to the matching trainer, or nullptr
    Trainer* TrainerManager::findByID(int id) {
        for (int i = 0; i < trainerCount; i++)
            if (trainers[i].getTrainerID() == id)
                return &trainers[i];

        return nullptr; // not found
    }

    // Returns true if a trainer with the given ID exists in the array
    bool TrainerManager::trainerExists(int id) const {
        for (int i = 0; i < trainerCount; i++)
            if (trainers[i].getTrainerID() == id)
                return true;

        return false;
    }

    // Writes the full trainer list to trainers.txt (overwrites the file each time)
    void TrainerManager::saveToFile() const {
        ofstream ofs("trainers.txt");

        if (!ofs) {
            cout << "  Error saving trainers." << endl;
            return;
        }

        ofs << trainerCount << endl; // first line = how many trainers follow

        for (int i = 0; i < trainerCount; i++)
            trainers[i].saveToFile(ofs); // each trainer writes its own fields
    }

    // Reads the trainer list back from trainers.txt into the array
    void TrainerManager::loadFromFile() {
        ifstream ifs("trainers.txt");

        if (!ifs) return; // file doesn't exist yet

        ifs >> trainerCount; // first line tells us how many records to read
        ifs.ignore();

        for (int i = 0; i < trainerCount; i++)
            trainers[i].loadFromFile(ifs); // each trainer reads its own fields
    }

    // Writes all member-trainer assignments to trainer_assignments.txt
    void TrainerManager::saveAssignments() const {
        ofstream ofs("trainer_assignments.txt");

        if (!ofs) {
            cout << "  Error saving assignments." << endl;
            return;
        }

        ofs << assignCount << endl; // first line = number of assignments

        for (int i = 0; i < assignCount; i++)
            assignments[i].saveToFile(ofs);
    }

    // Reads all member-trainer assignments back from trainer_assignments.txt
    void TrainerManager::loadAssignments() {
        ifstream ifs("trainer_assignments.txt");

        if (!ifs) return; // no file yet 

        ifs >> assignCount; // first line = number of assignments to read
        ifs.ignore();

        for (int i = 0; i < assignCount; i++)
            assignments[i].loadFromFile(ifs);
    }
