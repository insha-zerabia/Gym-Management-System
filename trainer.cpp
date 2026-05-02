#include "trainer.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// trainer class

// sets all fields to empty or zero, trainer starts as active
Trainer::Trainer()
    : trainerID(0), name(""), specialization(""), contactNumber(""),
    email(""), availability(""), experienceYears(0), isActive(true) {
}

// builds a trainer using the given values, trainer starts as active
Trainer::Trainer(int id, string n, string spec, string contact,
    string em, string avail, int exp)
    : trainerID(id), name(n), specialization(spec), contactNumber(contact),
    email(em), availability(avail), experienceYears(exp), isActive(true) {
}

// makes a copy of another trainer
Trainer::Trainer(const Trainer& o)
    : trainerID(o.trainerID), name(o.name), specialization(o.specialization),
    contactNumber(o.contactNumber), email(o.email), availability(o.availability),
    experienceYears(o.experienceYears), isActive(o.isActive) {
}

// copies all fields from another trainer into this one
Trainer& Trainer::operator=(const Trainer& o) {
    if (this != &o) {           // guard against self assignment like t = t
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

// nothing to clean up since no heap memory is used
Trainer::~Trainer() {}

// getters
int    Trainer::getTrainerID()       const { return trainerID; }
string Trainer::getName()            const { return name; }
string Trainer::getSpecialization()  const { return specialization; }
string Trainer::getContactNumber()   const { return contactNumber; }
string Trainer::getEmail()           const { return email; }
string Trainer::getAvailability()    const { return availability; }
int    Trainer::getExperienceYears() const { return experienceYears; }
bool   Trainer::getIsActive()        const { return isActive; }

// setters
void Trainer::setTrainerID(int v) { trainerID = v; }
void Trainer::setName(string v) { name = v; }
void Trainer::setSpecialization(string v) { specialization = v; }
void Trainer::setContactNumber(string v) { contactNumber = v; }
void Trainer::setEmail(string v) { email = v; }
void Trainer::setAvailability(string v) { availability = v; }
void Trainer::setExperienceYears(int v) { experienceYears = v; }
void Trainer::setIsActive(bool v) { isActive = v; }

// returns true if both trainers have the same id
bool Trainer::operator==(const Trainer& rhs) const {
    return trainerID == rhs.trainerID;
}

// prints all trainer details to the screen in a formatted block
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

// prints a short one line summary used in list views
void Trainer::displayCompact() const {
    cout << "  [T" << setw(3) << setfill('0') << trainerID << setfill(' ') << "] "
        << left << setw(20) << name
        << " | " << left << setw(15) << specialization
        << " | " << experienceYears << " yrs"
        << (isActive ? "" : " [INACTIVE]") << "\n";
}

// saves all trainer fields to a file one line at a time
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
    ifs >> trainerID; ifs.ignore();   // read id then discard the newline after it
    getline(ifs, name);
    getline(ifs, specialization);
    getline(ifs, contactNumber);
    getline(ifs, email);
    getline(ifs, availability);
    ifs >> experienceYears >> isActive;
    ifs.ignore();                     // discard the newline after the last number
}

// member trainer assignment class

// sets all fields to empty or zero
MemberTrainerAssignment::MemberTrainerAssignment()
    : memberId(""), trainerID(0), assignedDate("") {
}

// links a member to a trainer with an assigned date
MemberTrainerAssignment::MemberTrainerAssignment(string mid, int tid, string date)
    : memberId(mid), trainerID(tid), assignedDate(date) {
}

// getters
string MemberTrainerAssignment::getMemberId()     const { return memberId; }
int    MemberTrainerAssignment::getTrainerID()    const { return trainerID; }
string MemberTrainerAssignment::getAssignedDate() const { return assignedDate; }

// setters
void MemberTrainerAssignment::setTrainerID(int tid) { trainerID = tid; }
void MemberTrainerAssignment::setAssignedDate(string date) { assignedDate = date; }

// saves member id, trainer id and assigned date to file
void MemberTrainerAssignment::saveToFile(ofstream& ofs) const {
    ofs << memberId << endl
        << trainerID << endl
        << assignedDate << endl;
}

// reads member id, trainer id and assigned date from file
void MemberTrainerAssignment::loadFromFile(ifstream& ifs) {
    getline(ifs, memberId);
    ifs >> trainerID;
    ifs.ignore();                // skip the newline after trainer id
    getline(ifs, assignedDate);
}

// trainer manager class

// sets counts to zero then loads saved data from disk
TrainerManager::TrainerManager() : trainerCount(0), assignCount(0) {
    loadFromFile();    // load trainers from trainers.txt
    loadAssignments(); // load assignments from trainer_assignments.txt
}

// returns todays date as a yyyy mm dd string using the system clock
string TrainerManager::currentDate() const {
    time_t now = time(nullptr); // get current time as seconds since epoch
    char buf[20];
    struct tm t; // standard library struct for holding date and time fields

#ifdef _WIN32
    localtime_s(&t, &now);  // thread safe version for windows
#else
    localtime_r(&now, &t);  // thread safe version for linux and mac
#endif

    strftime(buf, sizeof(buf), "%Y-%m-%d", &t); // format into yyyy-mm-dd
    return string(buf);
}

// asks the user for details and adds a new trainer to the array
void TrainerManager::addTrainer() {
    if (trainerCount >= 100) {   // stop if the array is full
        cout << "  Trainer list full." << endl;
        return;
    }

    int id = trainerCount + 1;   // next id is based on current count
    string name, spec, contact, email, avail;
    int exp;

    cout << endl << "  Add New Trainer" << endl;
    cout << "  Auto-assigned ID  : T"
        << setw(3) << setfill('0') << id << setfill(' ') << endl;

    cin.ignore(); // flush leftover newline from previous input

    // collect all trainer info from the user
    cout << "  Name              : "; getline(cin, name);
    cout << "  Specialization    : "; getline(cin, spec);
    cout << "  Contact Number    : "; getline(cin, contact);
    cout << "  Email             : "; getline(cin, email);
    cout << "  Availability      : "; getline(cin, avail);
    cout << "  Experience (years): "; cin >> exp;
    cin.ignore();

    trainers[trainerCount++] = Trainer(id, name, spec, contact, email, avail, exp);
    saveToFile();                // save to disk right away

    cout << "  Trainer added successfully with ID: T"
        << setw(3) << setfill('0') << id << setfill(' ') << endl;
}

// prints full details of every trainer in the list
void TrainerManager::viewAllTrainers() const {
    if (trainerCount == 0) {
        cout << "  No trainers registered." << endl;
        return;
    }
    cout << endl << "  All Trainers" << endl;
    for (int i = 0; i < trainerCount; i++)
        trainers[i].display();
}

// prints a short summary of only the active trainers
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

// finds a trainer by id and prints their full details
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

// searches for trainers whose name contains the keyword, not case sensitive
void TrainerManager::searchTrainerByName(string keyword) const {
    cout << endl << "  Search Results for \"" << keyword << "\"" << endl;

    bool found = false;
    for (int i = 0; i < trainerCount; i++) {
        string n = trainers[i].getName();

        // convert both strings to lowercase so the compare ignores case
        string nLow = n, kLow = keyword;
        for (char& c : nLow) c = tolower(c);
        for (char& c : kLow) c = tolower(c);

        if (nLow.find(kLow) != string::npos) { // keyword found somewhere in the name
            trainers[i].displayCompact();
            found = true;
        }
    }

    if (!found)
        cout << "  No trainer found matching \"" << keyword << "\"." << endl;
}

// lets the user edit any field of a trainer, pressing enter keeps the current value
void TrainerManager::updateTrainer(int id) {
    Trainer* t = findByID(id);   // find the trainer by id
    if (!t) { cout << "  Trainer not found." << endl; return; }

    cout << endl << "  Update Trainer (press Enter to keep current value)" << endl;

    string val;
    int n;
    cin.ignore(); // flush leftover newline

    // show current value for each field, only update if the user types something
    cout << "  Name [" << t->getName() << "]: ";
    getline(cin, val); if (!val.empty()) t->setName(val);

    cout << "  Specialization [" << t->getSpecialization() << "]: ";
    getline(cin, val); if (!val.empty()) t->setSpecialization(val);

    cout << "  Contact [" << t->getContactNumber() << "]: ";
    getline(cin, val); if (!val.empty()) t->setContactNumber(val);

    cout << "  Email [" << t->getEmail() << "]: ";
    getline(cin, val); if (!val.empty()) t->setEmail(val);

    cout << "  Availability [" << t->getAvailability() << "]: ";
    getline(cin, val); if (!val.empty()) t->setAvailability(val);

    cout << "  Experience years (0 = keep) [" << t->getExperienceYears() << "]: ";
    cin >> n;
    if (n > 0) t->setExperienceYears(n); // entering 0 means keep the old value
    cin.ignore();

    saveToFile();
    cout << "  Trainer updated successfully." << endl;
}

// marks a trainer as inactive without deleting their record
void TrainerManager::deactivateTrainer(int id) {
    Trainer* t = findByID(id);
    if (!t) { cout << "  Trainer not found." << endl; return; }

    t->setIsActive(false); // set inactive flag, data is kept
    saveToFile();

    cout << "  Trainer T" << setw(3) << setfill('0') << id << setfill(' ')
        << " deactivated (records preserved)." << endl;
}

// permanently removes a trainer and shifts the remaining ones left
void TrainerManager::deleteTrainer(int id) {
    for (int i = 0; i < trainerCount; i++) {
        if (trainers[i].getTrainerID() == id) {

            // shift everything after the deleted slot one step to the left
            for (int j = i; j < trainerCount - 1; j++)
                trainers[j] = trainers[j + 1];

            trainerCount--;
            saveToFile();
            cout << "  Trainer deleted." << endl;
            return;
        }
    }
    cout << "  Trainer not found." << endl;
}

// links a trainer to a member, each member can only have one trainer at a time
void TrainerManager::assignTrainerToMember(string memberId, int trainerID) {
    Trainer* t = findByID(trainerID);
    if (!t) { cout << "  Trainer not found." << endl; return; }
    if (!t->getIsActive()) { cout << "  Cannot assign: trainer is inactive." << endl; return; }

    // stop if the member already has a trainer assigned
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            cout << "  Member already has Trainer T"
                << setw(3) << setfill('0') << assignments[i].getTrainerID()
                << setfill(' ') << " assigned." << endl;
            cout << "  Use 'Change Trainer' to reassign." << endl;
            return;
        }
    }

    if (assignCount >= 200) { // stop if the assignment array is full
        cout << "  Assignment list full." << endl;
        return;
    }

    // create a new assignment with todays date
    assignments[assignCount++] = MemberTrainerAssignment(memberId, trainerID, currentDate());
    saveAssignments();

    cout << "  Trainer T" << setw(3) << setfill('0') << trainerID << setfill(' ')
        << " (" << t->getName() << ") assigned to member " << memberId
        << " on " << currentDate() << "." << endl;
}

// replaces a members current trainer with a new one, or creates a new assignment if none exists
void TrainerManager::changeTrainerForMember(string memberId, int newTrainerID) {
    Trainer* t = findByID(newTrainerID);
    if (!t) { cout << "  New trainer not found." << endl; return; }
    if (!t->getIsActive()) { cout << "  Cannot assign: trainer is inactive." << endl; return; }

    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            int old = assignments[i].getTrainerID(); // save old id for the message

            // update the existing assignment in place
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

    // no existing assignment found so create a fresh one
    assignTrainerToMember(memberId, newTrainerID);
}

// removes the trainer assignment for a member and shifts the array left
void TrainerManager::removeTrainerFromMember(string memberId) {
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {

            // shift everything after the removed slot one step to the left
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

// shows the trainer currently assigned to a member along with their full details
void TrainerManager::viewMemberTrainer(string memberId) const {
    cout << endl << "  === Assigned Trainer for Member: " << memberId << " ===" << endl;

    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].getMemberId() == memberId) {
            int tid = assignments[i].getTrainerID();
            cout << "  Assigned on : " << assignments[i].getAssignedDate() << endl;

            // find and display the trainers full record
            for (int j = 0; j < trainerCount; j++) {
                if (trainers[j].getTrainerID() == tid) {
                    trainers[j].display();
                    return;
                }
            }

            // assignment exists but the trainer record is missing
            cout << "  Trainer ID " << tid << " (details not found)." << endl;
            return;
        }
    }
    cout << "  No trainer assigned yet." << endl;
}

// lists all members currently assigned to a specific trainer
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

// returns the trainer id assigned to a member, or 0 if none is assigned
int TrainerManager::getAssignedTrainerID(string memberId) const {
    for (int i = 0; i < assignCount; i++)
        if (assignments[i].getMemberId() == memberId)
            return assignments[i].getTrainerID();
    return 0; // 0 means no trainer is assigned
}

// searches the trainers array and returns a pointer to the matching one or nullptr
Trainer* TrainerManager::findByID(int id) {
    for (int i = 0; i < trainerCount; i++)
        if (trainers[i].getTrainerID() == id)
            return &trainers[i];
    return nullptr; // not found
}

// returns true if a trainer with the given id exists
bool TrainerManager::trainerExists(int id) const {
    for (int i = 0; i < trainerCount; i++)
        if (trainers[i].getTrainerID() == id)
            return true;
    return false;
}

// writes the full trainer list to trainers.txt, overwrites the file each time
void TrainerManager::saveToFile() const {
    ofstream ofs("trainers.txt");
    if (!ofs) { cout << "  Error saving trainers." << endl; return; }

    ofs << trainerCount << endl; // first line tells how many trainers follow
    for (int i = 0; i < trainerCount; i++)
        trainers[i].saveToFile(ofs); // each trainer saves its own fields
}

// reads the trainer list back from trainers.txt into the array
void TrainerManager::loadFromFile() {
    ifstream ifs("trainers.txt");
    if (!ifs) return; // file does not exist yet, this is fine on first run

    ifs >> trainerCount; // first line tells how many records to read
    ifs.ignore();
    for (int i = 0; i < trainerCount; i++)
        trainers[i].loadFromFile(ifs);
}

// writes all member trainer assignments to trainer_assignments.txt
void TrainerManager::saveAssignments() const {
    ofstream ofs("trainer_assignments.txt");
    if (!ofs) { cout << "  Error saving assignments." << endl; return; }

    ofs << assignCount << endl; // first line tells how many assignments follow
    for (int i = 0; i < assignCount; i++)
        assignments[i].saveToFile(ofs);
}

// reads all member trainer assignments back from trainer_assignments.txt
void TrainerManager::loadAssignments() {
    ifstream ifs("trainer_assignments.txt");
    if (!ifs) return; // file does not exist yet

    ifs >> assignCount; // first line tells how many assignments to read
    ifs.ignore();
    for (int i = 0; i < assignCount; i++)
        assignments[i].loadFromFile(ifs);
}