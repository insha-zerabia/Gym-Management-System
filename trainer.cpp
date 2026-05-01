#include "trainer.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

Trainer::Trainer()
    : trainerID(0), name(""), specialization(""), contactNumber(""),
    email(""), availability(""), experienceYears(0), isActive(true) {
}

Trainer::Trainer(int id, string n, string spec, string contact,
    string em, string avail, int exp)
    : trainerID(id), name(n), specialization(spec), contactNumber(contact),
    email(em), availability(avail), experienceYears(exp), isActive(true) {
}

Trainer::Trainer(const Trainer& o)
    : trainerID(o.trainerID), name(o.name), specialization(o.specialization),
    contactNumber(o.contactNumber), email(o.email), availability(o.availability),
    experienceYears(o.experienceYears), isActive(o.isActive) {
}

Trainer& Trainer::operator=(const Trainer& o) {
    if (this != &o) { 
        trainerID = o.trainerID;
        name = o.name;
        specialization = o.specialization;
        contactNumber = o.contactNumber;
        email = o.email;
        availability = o.availability;
        experienceYears = o.experienceYears;
        isActive = o.isActive;
    }
    return *this; //returns current 
}
Trainer::~Trainer() {}

// Getters
int    Trainer::getTrainerID()       const { return trainerID; }
string Trainer::getName()            const { return name; }
string Trainer::getSpecialization()  const { return specialization; }
string Trainer::getContactNumber()   const { return contactNumber; }
string Trainer::getEmail()           const { return email; }
string Trainer::getAvailability()    const { return availability; }
int    Trainer::getExperienceYears() const { return experienceYears; }
bool   Trainer::getIsActive()        const { return isActive; }

// Setters
void Trainer::setTrainerID(int v) { trainerID = v; }
void Trainer::setName(string v) { name = v; }
void Trainer::setSpecialization(string v) { specialization = v; }
void Trainer::setContactNumber(string v) { contactNumber = v; }
void Trainer::setEmail(string v) { email = v; }
void Trainer::setAvailability(string v) { availability = v; }
void Trainer::setExperienceYears(int v) { experienceYears = v; }
void Trainer::setIsActive(bool v) { isActive = v; }

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

void Trainer::displayCompact() const {
    cout << "  [T" << setw(3) << setfill('0') << trainerID << setfill(' ') << "] "
        << left << setw(20) << name
        << " | " << left << setw(15) << specialization
        << " | " << experienceYears << " yrs"
        << (isActive ? "" : " [INACTIVE]") << "\n";
}

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

void Trainer::loadFromFile(ifstream& ifs) {
    ifs >> trainerID; ifs.ignore();
    getline(ifs, name);
    getline(ifs, specialization);
    getline(ifs, contactNumber);
    getline(ifs, email);
    getline(ifs, availability);
    ifs >> experienceYears >> isActive;
    ifs.ignore();
}

MemberTrainerAssignment::MemberTrainerAssignment()
    : memberId(""), trainerID(0), assignedDate("") {
}

MemberTrainerAssignment::MemberTrainerAssignment(string mid, int tid, string date)
    : memberId(mid), trainerID(tid), assignedDate(date) {
}

// Save assignment to file
void MemberTrainerAssignment::saveToFile(ofstream& ofs) const {
    ofs << memberId << endl
        << trainerID << endl
        << assignedDate << endl;
}

// Load assignment from file
void MemberTrainerAssignment::loadFromFile(ifstream& ifs) {
    getline(ifs, memberId);          // read member ID
    ifs >> trainerID;
    ifs.ignore();                    // skip newline
    getline(ifs, assignedDate);      // read date
}

// Constructor initializes and loads data
TrainerManager::TrainerManager() : trainerCount(0), assignCount(0) {
    loadFromFile();       // load trainers
    loadAssignments();    // load assignments
}

// Get current system date
string TrainerManager::currentDate() const {
    time_t now = time(nullptr);
    char buf[20];
    struct tm t;

#ifdef _WIN32
    localtime_s(&t, &now);   // Windows safe version
#else
    localtime_r(&now, &t);   // Linux/Mac version
#endif

    strftime(buf, sizeof(buf), "%Y-%m-%d", &t); // format date
    return string(buf);
}

// Add a new trainer
void TrainerManager::addTrainer() {
    if (trainerCount >= 100) {
        cout << "  Trainer list full." << endl;
        return;
    }

    int id = trainerCount + 1;
    string name, spec, contact, email, avail;
    int exp;

    cout << endl << "  Add New Trainer" << endl;
    cout << "  Auto-assigned ID  : T"
        << setw(3) << setfill('0') << id << setfill(' ') << endl;

    cin.ignore(); // clear buffer

    cout << "  Name              : "; getline(cin, name);
    cout << "  Specialization    : "; getline(cin, spec);
    cout << "  Contact Number    : "; getline(cin, contact);
    cout << "  Email             : "; getline(cin, email);
    cout << "  Availability      : "; getline(cin, avail);
    cout << "  Experience (years): "; cin >> exp;
    cin.ignore();

    // Store trainer
    trainers[trainerCount++] = Trainer(id, name, spec, contact, email, avail, exp);

    saveToFile(); // save data

    cout << "  Trainer added successfully with ID: T"
        << setw(3) << setfill('0') << id << setfill(' ') << endl;
}

// Display all trainers
void TrainerManager::viewAllTrainers() const {
    if (trainerCount == 0) {
        cout << "  No trainers registered." << endl;
        return;
    }

    cout << endl << "  All Trainers" << endl;

    for (int i = 0; i < trainerCount; i++)
        trainers[i].display();
}

// Display only active trainers
void TrainerManager::viewActiveTrainers() const {
    cout << endl << "  Active Trainers" << endl;
    cout << "  " << string(60, '-') << endl;

    bool any = false;

    for (int i = 0; i < trainerCount; i++) {
        if (trainers[i].getIsActive()) {
            trainers[i].displayCompact();
            any = true;
        }
    }

    if (!any)
        cout << "  No active trainers." << endl;

    cout << "  " << string(60, '-') << endl;
}

// Search trainer by ID
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

// Search trainer by name (case insensitive)
void TrainerManager::searchTrainerByName(string keyword) const {
    cout << endl << "  Search Results for \"" << keyword << "\"" << endl;

    bool found = false;

    for (int i = 0; i < trainerCount; i++) {
        string n = trainers[i].getName();

        // Convert both strings to lowercase
        string nLow = n, kLow = keyword;
        for (char& c : nLow) c = tolower(c);
        for (char& c : kLow) c = tolower(c);

        // Check if keyword exists in name
        if (nLow.find(kLow) != string::npos) {
            trainers[i].displayCompact();
            found = true;
        }
    }

    if (!found)
        cout << "  No trainer found matching \"" << keyword << "\"." << endl;
}

// Update trainer details
void TrainerManager::updateTrainer(int id) {
    // Find trainer
    Trainer* t = findByID(id);
    if (!t) { cout << "  Trainer not found." << endl; return; }

    cout << endl << "  Update Trainer (press Enter to keep current value)" << endl;

    string val;
    int n;

    cin.ignore(); // clear buffer

    // Update name
    cout << "  Name [" << t->getName() << "]: ";
    getline(cin, val);
    if (!val.empty()) t->setName(val);

    // Update specialization
    cout << "  Specialization [" << t->getSpecialization() << "]: ";
    getline(cin, val);
    if (!val.empty()) t->setSpecialization(val);

    // Update contact
    cout << "  Contact [" << t->getContactNumber() << "]: ";
    getline(cin, val);
    if (!val.empty()) t->setContactNumber(val);

    // Update email
    cout << "  Email [" << t->getEmail() << "]: ";
    getline(cin, val);
    if (!val.empty()) t->setEmail(val);

    // Update availability
    cout << "  Availability [" << t->getAvailability() << "]: ";
    getline(cin, val);
    if (!val.empty()) t->setAvailability(val);

    // Update experience
    cout << "  Experience years (0 = keep) [" << t->getExperienceYears() << "]: ";
    cin >> n;
    if (n > 0) t->setExperienceYears(n);
    cin.ignore();

    saveToFile(); // save changes
    cout << "  Trainer updated successfully." << endl;
}

// Deactivate trainer
void TrainerManager::deactivateTrainer(int id) {
    // Find trainer
    Trainer* t = findByID(id);
    if (!t) { cout << "  Trainer not found." << endl; return; }

    t->setIsActive(false); // mark inactive
    saveToFile();

    cout << "  Trainer T" << setw(3) << setfill('0') << id << setfill(' ')
        << " deactivated (records preserved)." << endl;
}

// Delete trainer permanently
void TrainerManager::deleteTrainer(int id) {
    for (int i = 0; i < trainerCount; i++) {
        if (trainers[i].getTrainerID() == id) {

            // Shift elements left
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

// Assign trainer to member
void TrainerManager::assignTrainerToMember(string memberId, int trainerID) {
    // Check trainer
    Trainer* t = findByID(trainerID);
    if (!t) { cout << "  Trainer not found." << endl; return; }
    if (!t->getIsActive()) { cout << "  Cannot assign: trainer is inactive." << endl; return; }

    // Check existing assignment
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            cout << "  Member already has Trainer T"
                << setw(3) << setfill('0') << assignments[i].trainerID
                << setfill(' ') << " assigned." << endl;

            cout << "  Use 'Change Trainer' to reassign." << endl;
            return;
        }
    }

    // Check capacity
    if (assignCount >= 200) {
        cout << "  Assignment list full." << endl;
        return;
    }

    // Add assignment
    assignments[assignCount++] = MemberTrainerAssignment(memberId, trainerID, currentDate());
    saveAssignments();

    cout << "  Trainer T" << setw(3) << setfill('0') << trainerID << setfill(' ')
        << " (" << t->getName() << ") assigned to member " << memberId
        << " on " << currentDate() << "." << endl;
}

// Change trainer for member
void TrainerManager::changeTrainerForMember(string memberId, int newTrainerID) {
    // Validate trainer
    Trainer* t = findByID(newTrainerID);
    if (!t) { cout << "  New trainer not found." << endl; return; }
    if (!t->getIsActive()) { cout << "  Cannot assign: trainer is inactive." << endl; return; }

    // Search assignment
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {

            int old = assignments[i].trainerID;

            // Update assignment
            assignments[i].trainerID = newTrainerID;
            assignments[i].assignedDate = currentDate();

            saveAssignments();

            cout << "  Member " << memberId << " trainer changed from T"
                << setw(3) << setfill('0') << old << " to T"
                << setw(3) << setfill('0') << newTrainerID << setfill(' ')
                << " (" << t->getName() << ")." << endl;

            return;
        }
    }

    // If no assignment exists
    assignTrainerToMember(memberId, newTrainerID);
}

// Remove trainer assignment from a member
void TrainerManager::removeTrainerFromMember(string memberId) {
    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            // Shift remaining assignments left
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

// View trainer assigned to a specific member
void TrainerManager::viewMemberTrainer(string memberId) const {
    cout << endl << "  === Assigned Trainer for Member: " << memberId << " ===" << endl;

    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].memberId == memberId) {
            int tid = assignments[i].trainerID;

            cout << "  Assigned on : " << assignments[i].assignedDate << endl;

            // Find trainer details
            for (int j = 0; j < trainerCount; j++) {
                if (trainers[j].getTrainerID() == tid) {
                    trainers[j].display();
                    return;
                }
            }

            // Trainer record missing
            cout << "  Trainer ID " << tid << " (details not found)." << endl;
            return;
        }
    }

    cout << "  No trainer assigned yet." << endl;
}

// View all members assigned to a trainer
void TrainerManager::viewTrainerMembers(int trainerID) const {
    cout << endl << "  === Members assigned to Trainer T"
        << setw(3) << setfill('0') << trainerID << setfill(' ') << " ===" << endl;

    bool found = false;

    for (int i = 0; i < assignCount; i++) {
        if (assignments[i].trainerID == trainerID) {
            cout << "  Member: " << assignments[i].memberId
                << "  (since " << assignments[i].assignedDate << ")" << endl;
            found = true;
        }
    }

    if (!found)
        cout << "  No members assigned to this trainer." << endl;
}

// Get trainer ID assigned to a member (0 if none)
int TrainerManager::getAssignedTrainerID(string memberId) const {
    for (int i = 0; i < assignCount; i++)
        if (assignments[i].memberId == memberId)
            return assignments[i].trainerID;

    return 0;   // 0 = none
}

// Find trainer by ID (returns pointer or nullptr)
Trainer* TrainerManager::findByID(int id) {
    for (int i = 0; i < trainerCount; i++)
        if (trainers[i].getTrainerID() == id)
            return &trainers[i];

    return nullptr;
}

// Check if trainer exists
bool TrainerManager::trainerExists(int id) const {
    for (int i = 0; i < trainerCount; i++)
        if (trainers[i].getTrainerID() == id)
            return true;

    return false;
}

// Save all trainers to file
void TrainerManager::saveToFile() const {
    ofstream ofs("trainers.txt");

    if (!ofs) {
        cout << "  Error saving trainers." << endl;
        return;
    }

    ofs << trainerCount << endl;

    for (int i = 0; i < trainerCount; i++)
        trainers[i].saveToFile(ofs);
}

// Load trainers from file
void TrainerManager::loadFromFile() {
    ifstream ifs("trainers.txt");

    if (!ifs) return;

    ifs >> trainerCount;
    ifs.ignore();

    for (int i = 0; i < trainerCount; i++)
        trainers[i].loadFromFile(ifs);
}

// Save trainer-member assignments to file
void TrainerManager::saveAssignments() const {
    ofstream ofs("trainer_assignments.txt");

    if (!ofs) {
        cout << "  Error saving assignments." << endl;
        return;
    }

    ofs << assignCount << endl;

    for (int i = 0; i < assignCount; i++)
        assignments[i].saveToFile(ofs);
}

// Load trainer-member assignments from file
void TrainerManager::loadAssignments() {
    ifstream ifs("trainer_assignments.txt");

    if (!ifs) return;

    ifs >> assignCount;
    ifs.ignore();

    for (int i = 0; i < assignCount; i++)
        assignments[i].loadFromFile(ifs);
}