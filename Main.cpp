#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include "BaseClasses.h"
#include "EntityDemo.h"
#include "Scheduling.h"
#include "Combination.h"
#include "Induction.h"
#include "Logic.h"
#include "Set.h"
#include "Relation.h"
#include "Function.h"
#include "AutomatedProof.h"
#include "Consistency.h"
#include "AlgorithmEfficiency.h"
#include "CLI.h"
#include "UnitTesting.h"

using namespace std;

// Global data structures for university system
class UniversityDataStore {
public:
    vector<Student> students;
    vector<Course> courses;
    vector<Faculty> faculties;
    vector<Room> rooms;
    vector<Lab> labs;

    // Initialize with comprehensive default data
    void initializeDefaultData() {
        cout << endl;

        // Add sample students
        students.push_back(Student("S001", "Ali"));
        students.push_back(Student("S002", "Babar"));
        students.push_back(Student("S003", "Chand"));
        students.push_back(Student("S004", "Danish"));
        students.push_back(Student("S005", "Eshal"));
        students.push_back(Student("S006", "Faris"));
        students.push_back(Student("S007", "Ghous"));
        students.push_back(Student("S008", "Hayyan"));

        // Add comprehensive course catalog
        courses.push_back(Course("CS101", "Introduction to Programming"));
        courses.push_back(Course("CS201", "Data Structures"));
        courses.push_back(Course("CS301", "Algorithms"));
        courses.push_back(Course("CS401", "Database Systems"));
        courses.push_back(Course("Math101", "Calculus I"));
        courses.push_back(Course("Math201", "Calculus II"));
        courses.push_back(Course("Math301", "Linear Algebra"));
        courses.push_back(Course("Physics101", "Physics I"));
        courses.push_back(Course("English101", "English Composition"));

        // Set prerequisites
        courses[1].addPrerequisite("CS101");      
        courses[2].addPrerequisite("CS201");      
        courses[2].addPrerequisite("Math201");   
        courses[3].addPrerequisite("CS201");      
        courses[5].addPrerequisite("Math101");    
        courses[6].addPrerequisite("Math201");    

        // Assign faculty to courses
        courses[0].assignFaculty("F001");
        courses[1].assignFaculty("F001");
        courses[2].assignFaculty("F002");
        courses[4].assignFaculty("F003");
        courses[5].assignFaculty("F003");

        // Assign rooms to courses
        courses[0].assignRoom("R101");
        courses[1].assignRoom("R102");
        courses[2].assignRoom("L201");
        courses[4].assignRoom("R101");

        // Add sample faculty
        faculties.push_back(Faculty("F001", "Dr. Sheroz"));
        faculties.push_back(Faculty("F002", "Dr. Eshan"));
        faculties.push_back(Faculty("F003", "Dr. Muzamil"));
        faculties.push_back(Faculty("F004", "Dr. Saim"));

        // Assign courses to faculty
        faculties[0].assignCourse("CS101");
        faculties[0].assignCourse("CS201");
        faculties[1].assignCourse("CS301");
        faculties[2].assignCourse("Math101");
        faculties[2].assignCourse("Math201");

        // Add sample rooms
        rooms.push_back(Room("R101", "Room 101", "Classroom", 50));
        rooms.push_back(Room("R102", "Room 102", "Classroom", 40));
        rooms.push_back(Room("R103", "Room 103", "Classroom", 60));
        rooms.push_back(Room("AUD", "Main Auditorium", "Auditorium", 200));

        // Add sample labs
        labs.push_back(Lab("L201", "Computer Lab 1", 30, 30));
        labs.push_back(Lab("L202", "Computer Lab 2", 25, 25));
        labs.push_back(Lab("L301", "Advanced AI Lab", 20, 20));

        labs[0].installSoftware("Visual Studio, Python, Java");
        labs[1].installSoftware("MATLAB, R, Python");
        labs[2].installSoftware("TensorFlow, PyTorch, CUDA");

        // Enroll some students in courses
        students[0].enrollCourse("CS101");
        students[0].enrollCourse("Math101");
        students[1].enrollCourse("CS101");
        students[1].enrollCourse("English101");
        students[2].enrollCourse("CS201");
        students[2].enrollCourse("Math201");
        students[3].enrollCourse("CS101");
        students[4].enrollCourse("Math101");
        students[4].enrollCourse("Physics101");
    }

    void displayAllEntities() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "         UNIVERSITY DATA OVERVIEW"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << endl;
        cout << "    STUDENTS (" << students.size() << ")  "<<endl;
        for (const auto& s : students) {
            cout << "  [" << s.getId() << "] " << s.getName();
            auto enrolled = s.getCourses();
            if (!enrolled.empty()) {
                cout << " (Enrolled: " << enrolled.size() << " courses)";
            }
            cout << endl;
        }
        cout << endl;
        cout << "    COURSES (" << courses.size() << ") "<<endl;
        for (const auto& c : courses) {
            cout << "  [" << c.getId() << "] " << c.getName();
            auto prereqs = c.getPrerequisites();
            if (!prereqs.empty()) {
                cout << " (Prereq: ";
                for (const auto& p : prereqs) cout << p << " ";
                cout << ")";
            }
            cout << endl;
        }
        cout << endl;
        cout << "    FACULTY (" << faculties.size() << ") "<<endl;
        for (const auto& f : faculties) {
            cout << "  [" << f.getId() << "] " << f.getName();
            auto assigned = f.getCourses();
            if (!assigned.empty()) {
                cout << " (Teaching: " << assigned.size() << " courses)";
            }
            cout << endl;
        }
        cout << endl;
        cout << "    ROOMS (" << rooms.size() << ") "<<endl;
        for (const auto& r : rooms) {
            cout << "  [" << r.getId() << "] " << r.getName()
                << " (" << r.getType() << ", Cap: " << r.getCapacity() << ")"<<endl;
        }
        cout << endl;
        cout << "    LABS (" << labs.size() << ") "<<endl;
        for (const auto& l : labs) {
            cout << "  [" << l.getId() << "] " << l.getName()
                << " (Computers: " << l.getComputerCount() << ")"<<endl;
        }
    }

    // Entity management functions
    void addStudent(const string& id, const string& name) {
        students.push_back(Student(id, name));
        CLI::displaySuccess("Student added: " + name + " (" + id + ")");
    }

    void addCourse(const string& id, const string& name) {
        courses.push_back(Course(id, name));
        CLI::displaySuccess("Course added: " + name + " (" + id + ")");
    }

    void enrollStudent(const string& studentId, const string& courseId) {
        Student* student = findStudent(studentId);
        Course* course = findCourse(courseId);

        if (student && course) {
            student->enrollCourse(courseId);
            CLI::displaySuccess(student->getName() + " enrolled in " + course->getName());
        }
        else {
            CLI::displayError("Student or Course not found");
        }
    }

    Student* findStudent(const string& id) {
        for (auto& s : students) {
            if (s.getId() == id) return &s;
        }
        return nullptr;
    }

    Course* findCourse(const string& id) {
        for (auto& c : courses) {
            if (c.getId() == id) return &c;
        }
        return nullptr;
    }

    Faculty* findFaculty(const string& id) {
        for (auto& f : faculties) {
            if (f.getId() == id) return &f;
        }
        return nullptr;
    }

    Room* findRoom(const string& id) {
        for (auto& r : rooms) {
            if (r.getId() == id) return &r;
        }
        return nullptr;
    }
};

// Global data store
UniversityDataStore dataStore;

// Entity Management Menu
void manageEntities() {
    while (true) {
        CLI::clearScreen();
        vector<string> options = {
            "View All Entities",
            "Add New Student",
            "Add New Course",
            "Enroll Student in Course",
            "Add Faculty Member",
            "Assign Faculty to Course",
            "View Specific Entity Details",
            "Entity Demonstrations"
        };

        CLI::displaySubMenu("ENTITY MANAGEMENT", options);

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) break;

        CLI::clearScreen();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            dataStore.displayAllEntities();
            CLI::pause();
            break;

        case 2: {
            string id = CLI::getStringInput("Enter Student ID: ");
            string name = CLI::getStringInput("Enter Student Name: ");
            dataStore.addStudent(id, name);
            CLI::pause();
            break;
        }

        case 3: {
            string id = CLI::getStringInput("Enter Course ID: ");
            string name = CLI::getStringInput("Enter Course Name: ");
            dataStore.addCourse(id, name);
            CLI::pause();
            break;
        }

        case 4: {
            string studentId = CLI::getStringInput("Enter Student ID: ");
            string courseId = CLI::getStringInput("Enter Course ID: ");
            dataStore.enrollStudent(studentId, courseId);
            CLI::pause();
            break;
        }

        case 5: {
            string id = CLI::getStringInput("Enter Faculty ID: ");
            string name = CLI::getStringInput("Enter Faculty Name: ");
            dataStore.faculties.push_back(Faculty(id, name));
            CLI::displaySuccess("Faculty added: " + name);
            CLI::pause();
            break;
        }

        case 6: {
            string facultyId = CLI::getStringInput("Enter Faculty ID: ");
            string courseId = CLI::getStringInput("Enter Course ID: ");
            Faculty* f = dataStore.findFaculty(facultyId);
            Course* c = dataStore.findCourse(courseId);
            if (f && c) {
                f->assignCourse(courseId);
                c->assignFaculty(facultyId);
                CLI::displaySuccess("Assignment complete");
            }
            else {
                CLI::displayError("Faculty or Course not found");
            }
            CLI::pause();
            break;
        }

        case 7: {
            cout << "\n1. View Student\n2. View Course\n3. View Faculty\n4. View Room\n";
            cout << "Choice: ";
            int entityChoice;
            cin >> entityChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string id = CLI::getStringInput("Enter ID: ");

            if (entityChoice == 1) {
                Student* s = dataStore.findStudent(id);
                if (s) s->display();
                else CLI::displayError("Student not found");
            }
            else if (entityChoice == 2) {
                Course* c = dataStore.findCourse(id);
                if (c) c->display();
                else CLI::displayError("Course not found");
            }
            else if (entityChoice == 3) {
                Faculty* f = dataStore.findFaculty(id);
                if (f) f->display();
                else CLI::displayError("Faculty not found");
            }
            else if (entityChoice == 4) {
                Room* r = dataStore.findRoom(id);
                if (r) r->display();
                else CLI::displayError("Room not found");
            }
            CLI::pause();
            break;
        }

        case 8:
            EntityDemo::demonstrateAllEntities();
            CLI::pause();
            break;

        default:
            CLI::displayError("Invalid choice");
            CLI::pause();
        }
    }
}

// Run all modules sequentially
void runAllModules() {
    CLI::clearScreen();
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "          RUNNING ALL 12 MODULES"<<endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;

    CLI::displayProgress("Module 1: Course Scheduling");
    CourseScheduler::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 2: Student Combinations");
    StudentCombinations::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 3: Induction Verification");
    InductionVerifier::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 4: Logic & Inference");
    LogicEngine::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 5: Set Operations");
    SetOperations<string>::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 6: Relations");
    Relations<string>::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 7: Functions");
    Functions<string, string>::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 8: Automated Proofs");
    ProofSystem::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 9: Consistency Checker");
    ConsistencyChecker::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 10: Efficiency Benchmarking");
    EfficiencyBenchmark::demonstrate();
    CLI::displaySeparator();

    CLI::displayProgress("Module 12: Unit Testing");
    UnitTester::demonstrate();
    CLI::displaySeparator();
    cout << endl;
    cout << "     ALL 12 MODULES COMPLETED SUCCESSFULLY!" << endl;
    cout << endl;
}

int main() {
    cout << "\033[38;2;0;255;255m";
    bool running = true;

    // Initialize data store
    dataStore.initializeDefaultData();

    // Display welcome screen
    CLI::displayWelcome();
    CLI::pause();

    while (running) {
        CLI::clearScreen();
        CLI::displayMainMenu();

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            CLI::displayError("Invalid input! Please enter a number.");
            CLI::pause();
            continue;
        }

        CLI::clearScreen();

        switch (choice) {
        case 1:
            CourseScheduler::showMenu(dataStore.students, dataStore.courses);
            break;

        case 2:
            StudentCombinations::showMenu(dataStore.students, dataStore.courses, dataStore.labs);
            break;

        case 3:
            InductionVerifier::showMenu(dataStore.students, dataStore.courses);
            break;

        case 4:
            LogicEngine::showMenu(dataStore.faculties, dataStore.courses, dataStore.rooms);
            break;

        case 5:
            SetOperations<string>::showMenu(dataStore.students, dataStore.courses,
                dataStore.faculties, dataStore.rooms);
            break;

        case 6:
            Relations<string>::showMenu(dataStore.students, dataStore.courses,
                dataStore.faculties, dataStore.rooms);
            break;

        case 7:
            Functions<string, string>::showMenu(dataStore.students, dataStore.courses,
                dataStore.faculties, dataStore.rooms);
            break;

        case 8:
            ProofSystem::showMenu(dataStore.courses);
            break;

        case 9:
            ConsistencyChecker::showMenu(dataStore.students, dataStore.courses,
                dataStore.faculties, dataStore.rooms);
            break;

        case 10:
            EfficiencyBenchmark::demonstrate();
            CLI::pause();
            break;

        case 11:
            UnitTester::showMenu();
            break;

        case 12:
            runAllModules();
            CLI::pause();
            break;

        case 13:
            manageEntities();
            break;

        case 14:
            dataStore.displayAllEntities();
            CLI::pause();
            break;

        case 0:
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "    Thank you for using UNIDISC ENGINE!"<<endl;
            cout << "    FAST University - Discrete Structures"<<endl;
            cout << "    All 12 Modules Implemented Successfully!"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl << endl;
            running = false;
            break;

        default:
            CLI::displayError("Invalid choice! Please select 0-14.");
            CLI::pause();
        }
    }

    return 0;
}