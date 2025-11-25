#ifndef MODULE7_FUNCTIONS_H
#define MODULE7_FUNCTIONS_H

#include <map>
#include <set>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <vector>
#include "BaseClasses.h"
using namespace std;

//Functions
template <typename T, typename U>
class Functions {
private:
    map<T, U> mapping;
    set<T> domain;
    set<U> codomain;
    string functionName;

public:
    Functions(string name = "f") : functionName(name) {}

    void addMapping(T input, U output) {
        mapping[input] = output;
        domain.insert(input);
        codomain.insert(output);
    }

    void removeMapping(T input) {
        if (mapping.find(input) != mapping.end()) {
            mapping.erase(input);
            domain.erase(input);
        }
    }

    U apply(T input) const {
        auto it = mapping.find(input);
        if (it == mapping.end()) {
            throw runtime_error("Input not in domain");
        }
        return it->second;
    }

    bool isDefined(T input) const {
        return mapping.find(input) != mapping.end();
    }

    set<T> getDomain() const { return domain; }
    set<U> getCodomain() const { return codomain; }
    map<T, U> getMapping() const { return mapping; }
    string getName() const { return functionName; }

    set<U> getRange() const {
        set<U> range;
        for (const auto& p : mapping) {
            range.insert(p.second);
        }
        return range;
    }

    // Check injective
    bool isInjective() const {
        set<U> outputs;
        for (const auto& p : mapping) {
            if (outputs.find(p.second) != outputs.end()) {
                return false;
            }
            outputs.insert(p.second);
        }
        return true;
    }

    // Check surjective 
    bool isSurjective() const {
        return getRange() == codomain;
    }

    // Check bijective
    bool isBijective() const {
        return isInjective() && isSurjective();
    }

    // Function composition
    template <typename V>
    static Functions<T, V> compose(const Functions<T, U>& f, const Functions<U, V>& g) {
        Functions<T, V> result("gof");

        for (const auto& pair : f.getMapping()) {
            T input = pair.first;
            U intermediate = pair.second;

            if (g.isDefined(intermediate)) {
                V output = g.apply(intermediate);
                result.addMapping(input, output);
            }
        }

        return result;
    }

    // Inverse function
    Functions<U, T> inverse() const {
        if (!isBijective()) {
            throw runtime_error("Function must be bijective to have an inverse!");
        }

        Functions<U, T> inv("f^-1");
        for (const auto& pair : mapping) {
            inv.addMapping(pair.second, pair.first);
        }
        return inv;
    }

    void display() const {
        cout << endl;
        cout << "Function " << functionName << ":"<<endl;
        for (const auto& p : mapping) {
            cout << "  " << functionName << "(" << p.first << ") = " << p.second << endl;
        }
        cout << endl;
        cout << "Properties:"<<endl;
        cout << "  Domain size: |Domain| = " << domain.size() << endl;
        cout << "  Codomain size: |Codomain| = " << codomain.size() << endl;
        cout << "  Range size: |Range| = " << getRange().size() << endl;
        cout << "  Injective (1-to-1): " << (isInjective() ? "YES ?" : "NO ?") << endl;
        cout << "  Surjective (onto): " << (isSurjective() ? "YES ?" : "NO ?") << endl;
        cout << "  Bijective: " << (isBijective() ? "YES ?" : "NO ?") << endl;
    }

    // Map Students to Courses
    static void mapStudentsToCourses(const vector<Student>& students,
        const vector<Course>& courses) {
        cout << endl;
        cout << "     MAP STUDENTS - COURSES"<<endl;
        cout << endl;

        if (students.empty() || courses.empty()) {
            cout << "[ERROR] Need students and courses data!"<<endl;
            return;
        }

        Functions<string, string> f("Student?Course");
        cout << endl;
        cout << "[INFO] Building function from enrollment data..."<<endl;

        // each student maps to their PRIMARY course (first enrolled)
        for (const auto& student : students) {
            auto enrolled = student.getCourses();
            if (!enrolled.empty()) {
                // Map to first course
                f.addMapping(student.getId(), *enrolled.begin());
            }
        }

        if (f.getMapping().empty()) {
            cout << "[INFO] No enrollments found. Creating sample mapping..."<<endl;

            // Create sample mapping
            for (size_t i = 0; i < min(students.size(), courses.size()); i++) {
                f.addMapping(students[i].getId(), courses[i].getId());
            }
        }
        cout << endl;
        cout << "[SUCCESS] Function: Student -> Course (Primary Enrollment)"<<endl;

        // Display with actual names
        for (const auto& pair : f.getMapping()) {
            string studentName = pair.first;
            string courseName = pair.second;

            for (const auto& s : students) {
                if (s.getId() == pair.first) {
                    studentName = s.getName();
                    break;
                }
            }

            for (const auto& c : courses) {
                if (c.getId() == pair.second) {
                    courseName = c.getName();
                    break;
                }
            }

            cout << "  f(" << pair.first << ": " << studentName << ") = "
                << pair.second << ": " << courseName << endl;
        }

        f.display();

        // Analysis
        cout << endl;
        cout << "[INFO] Function Analysis:"<<endl;
        if (f.isInjective()) {
            cout << "   Injective: Each student has unique primary course"<<endl;
        }
        else {
            cout << "    Not Injective: Multiple students enrolled in same course"<<endl;
            cout << "    (This is expected - courses have multiple students)"<<endl;
        }

        if (f.isSurjective()) {
            cout << "    Surjective: All courses have at least one student"<<endl;
        }
        else {
            cout << "    Not Surjective: Some courses have no students"<<endl;
        }
    }

    // INTERACTIVE: Map Courses to Faculty
    static void mapCoursesToFaculty(const vector<Course>& courses,
        const vector<Faculty>& faculties) {
        cout << endl;
        cout << "     MAP COURSES - FACULTY                        "<<endl;
        cout << endl;

        if (courses.empty() || faculties.empty()) {
            cout << "[ERROR] Need courses and faculty data!"<<endl;
            return;
        }

        Functions<string, string> f("Course?Faculty");
        cout << endl;
        cout << "[INFO] Building function from course assignments..."<<endl;

        // Build from course data
        for (const auto& course : courses) {
            if (!course.getFaculty().empty()) {
                f.addMapping(course.getId(), course.getFaculty());
            }
        }

        // Build from faculty data
        for (const auto& faculty : faculties) {
            auto assigned = faculty.getCourses();
            for (const auto& courseId : assigned) {
                if (!f.isDefined(courseId)) {
                    f.addMapping(courseId, faculty.getId());
                }
            }
        }

        if (f.getMapping().empty()) {
            cout << "[INFO] No assignments found. Creating sample mapping..."<<endl;

            for (size_t i = 0; i < min(courses.size(), faculties.size()); i++) {
                f.addMapping(courses[i].getId(), faculties[i].getId());
            }
        }
        cout << endl;
        cout << "[SUCCESS] Function: Course -> Faculty"<<endl;

        // Display with names
        for (const auto& pair : f.getMapping()) {
            string courseName = pair.first;
            string facultyName = pair.second;

            for (const auto& c : courses) {
                if (c.getId() == pair.first) {
                    courseName = c.getName();
                    break;
                }
            }

            for (const auto& fac : faculties) {
                if (fac.getId() == pair.second) {
                    facultyName = fac.getName();
                    break;
                }
            }

            cout << "  f(" << pair.first << ": " << courseName << ") = "
                << pair.second << ": " << facultyName << endl;
        }

        f.display();

        // Analysis
        cout << endl;
        cout << "[INFO] Function Analysis:"<<endl;
        if (f.isInjective()) {
            cout << "    Injective: Each course has unique faculty (good!)"<<endl;
            cout << "    No faculty teaches multiple courses"<<endl;
        }
        else {
            cout << "    Not Injective: Some faculty teach multiple courses"<<endl;

            // Find which faculty teach multiple courses
            map<string, vector<string>> facultyCourses;
            for (const auto& pair : f.getMapping()) {
                facultyCourses[pair.second].push_back(pair.first);
            }

            for (const auto& entry : facultyCourses) {
                if (entry.second.size() > 1) {
                    cout << "    Faculty " << entry.first << " teaches "
                        << entry.second.size() << " courses: ";
                    for (const auto& c : entry.second) cout << c << " ";
                    cout << endl;
                }
            }
        }
    }

    // Map Faculty to Rooms
    static void mapFacultyToRooms(const vector<Faculty>& faculties,
        const vector<Room>& rooms,
        const vector<Course>& courses) {
        cout << endl;
        cout << "     MAP FACULTY -> ROOMS"<<endl;
        cout << endl;

        if (faculties.empty() || rooms.empty()) {
            cout << "[ERROR] Need faculty and room data!"<<endl;
            return;
        }

        Functions<string, string> f("Faculty?Room");
        cout << endl;
        cout << "[INFO] Building function via Course assignments..."<<endl;
        cout << "[INFO] Faculty ? Course ? Room composition"<<endl;

        // Build Faculty  Room through courses
        for (const auto& faculty : faculties) {
            auto assignedCourses = faculty.getCourses();

            for (const auto& courseId : assignedCourses) {
                // Find this course's room
                for (const auto& course : courses) {
                    if (course.getId() == courseId && !course.getRoom().empty()) {
                        // Map faculty to this room
                        if (!f.isDefined(faculty.getId())) {
                            f.addMapping(faculty.getId(), course.getRoom());
                        }
                        break;
                    }
                }
            }
        }

        if (f.getMapping().empty()) {
            cout << "[INFO] No faculty-room mappings found via courses."<<endl;
            cout << "[INFO] Creating sample mapping..."<<endl;

            for (size_t i = 0; i < min(faculties.size(), rooms.size()); i++) {
                f.addMapping(faculties[i].getId(), rooms[i].getId());
            }
        }
        cout << endl;
        cout << "[SUCCESS] Function: Faculty - Room"<<endl;

        // Display
        for (const auto& pair : f.getMapping()) {
            string facultyName = pair.first;
            string roomName = pair.second;

            for (const auto& fac : faculties) {
                if (fac.getId() == pair.first) {
                    facultyName = fac.getName();
                    break;
                }
            }

            for (const auto& r : rooms) {
                if (r.getId() == pair.second) {
                    roomName = r.getName();
                    break;
                }
            }

            cout << "  f(" << pair.first << ": " << facultyName << ") = "
                << pair.second << ": " << roomName <<endl;
        }

        f.display();
    }

    // Verify Function Properties
    static void verifyFunctionProperties(const vector<Student>& students,
        const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     VERIFY FUNCTION PROPERTIES"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        // Create a test function
        Functions<string, string> f("Test Function");
        cout << endl;
        cout << "[INFO] Creating test function from student enrollments..."<<endl;

        for (const auto& s : students) {
            auto enrolled = s.getCourses();
            if (!enrolled.empty()) {
                f.addMapping(s.getId(), *enrolled.begin());
            }
        }

        if (f.getMapping().empty()) {
            cout << "[ERROR] No data to create function!"<<endl;
            return;
        }

        f.display();

        // Test properties
        cout << endl;
        cout << "[INFO] Testing Function Properties:"<<endl;

        // Injection test
        cout << "1. INJECTION TEST (One-to-One):"<<endl;
        cout << "   Definition: Different inputs ? Different outputs"<<endl;
        cout << "   f(x?) = f(x?) implies x? = x?"<<endl;
        if (f.isInjective()) {
            cout << "   Result: ? INJECTIVE"<<endl;
            cout << "   Each output has unique input"<<endl;
        }
        else {
            cout << "   Result: ? NOT INJECTIVE"<<endl;
            cout << "   Multiple students map to same course\n";
        }

        // Surjection test
        cout << "\n2. SURJECTION TEST (Onto):"<<endl;
        cout << "   Definition: Every output is mapped to"<<endl;
        cout << "   Range = Codomain"<<endl;
        cout << "   Range size: " << f.getRange().size() << endl;
        cout << "   Codomain size: " << f.getCodomain().size() << endl;
        if (f.isSurjective()) {
            cout << "   Result: ? SURJECTIVE"<<endl;
        }
        else {
            cout << "   Result: ? NOT SURJECTIVE"<<endl;
            cout << "   Some courses have no students"<<endl;
        }

        // Bijection test
        cout << "\n3. BIJECTION TEST (One-to-One & Onto):"<<endl;
        cout << "   Definition: Injective AND Surjective"<<endl;
        if (f.isBijective()) {
            cout << "   Result: ? BIJECTIVE"<<endl;
            cout << "   Function has an inverse!"<<endl;
        }
        else {
            cout << "   Result: ? NOT BIJECTIVE"<<endl;
            cout << "   Function does not have an inverse"<<endl;
        }
    }

    // INTERACTIVE: Function Composition
    static void demonstrateComposition(const vector<Student>& students,
        const vector<Course>& courses,
        const vector<Faculty>& faculties) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     FUNCTION COMPOSITION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << endl;
        cout << "[INFO] Creating composition: Student ? Course ? Faculty"<<endl;
        cout << "[INFO] (g ? f)(x) = g(f(x))"<<endl<<endl;

        // f: Student  Course
        Functions<string, string> f("f:S->C");
        for (const auto& s : students) {
            auto enrolled = s.getCourses();
            if (!enrolled.empty()) {
                f.addMapping(s.getId(), *enrolled.begin());
            }
        }

        // g: Course  Faculty
        Functions<string, string> g("g:C->F");
        for (const auto& c : courses) {
            if (!c.getFaculty().empty()) {
                g.addMapping(c.getId(), c.getFaculty());
            }
        }

        if (f.getMapping().empty() || g.getMapping().empty()) {
            cout << "[ERROR] Insufficient data for composition!"<<endl;
            return;
        }

        cout << "Function f (Student -> Course):"<<endl;
        for (const auto& p : f.getMapping()) {
            cout << "  f(" << p.first << ") = " << p.second << endl;
        }
        cout << endl;
        cout << "Function g (Course -> Faculty):"<<endl;
        for (const auto& p : g.getMapping()) {
            cout << "  g(" << p.first << ") = " << p.second << endl;
        }

        // Compose
        auto composed = Functions<string, string>::compose(f, g);
        cout << endl;
        cout << "[SUCCESS] Composed Function (g o f): Student ? Faculty"<<endl;
        for (const auto& p : composed.getMapping()) {
            string studentName = p.first;
            string facultyName = p.second;

            for (const auto& s : students) {
                if (s.getId() == p.first) studentName = s.getName();
            }
            for (const auto& fac : faculties) {
                if (fac.getId() == p.second) facultyName = fac.getName();
            }

            cout << "  (gof)(" << p.first << ": " << studentName << ") = "
                << p.second << ": " << facultyName << endl;
        }

        composed.display();
    }

    // MODULE MENU
    static void showMenu(const vector<Student>& students,
        const vector<Course>& courses,
        const vector<Faculty>& faculties,
        const vector<Room>& rooms) {
        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 7: FUNCTIONS"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. Map Students - Courses"<<endl;
            cout << "  2. Map Courses - Faculty"<<endl;
            cout << "  3. Map Faculty - Rooms"<<endl;
            cout << "  4. Verify Function Properties (Injection/Surjection)"<<endl;
            cout << "  5. Function Composition (Student?Course?Faculty)"<<endl;
            cout << "  6. Run Demonstration"<<endl;
            cout << "  0. Back to Main Menu"<<endl<<endl;
            cout << "  Choice: ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (choice == 0) break;

            switch (choice) {
            case 1:
                mapStudentsToCourses(students, courses);
                break;
            case 2:
                mapCoursesToFaculty(courses, faculties);
                break;
            case 3:
                mapFacultyToRooms(faculties, rooms, courses);
                break;
            case 4:
                verifyFunctionProperties(students, courses);
                break;
            case 5:
                demonstrateComposition(students, courses, faculties);
                break;
            case 6:
                demonstrate();
                break;
            default:
                cout << "[ERROR] Invalid choice!"<<endl;
            }
            cout << endl;
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    static void demonstrate() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     MODULE 7: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        Functions<string, string> f("Course-Faculty");
        f.addMapping("CS101", "Dr. Sheroz");
        f.addMapping("CS201", "Dr. Junaid");
        f.addMapping("Math101", "Dr. Wahab");
        cout << endl;
        cout << "[SUCCESS] Sample Function:"<<endl;
        f.display();
        cout << endl;
        cout << "[SUCCESS] Module 7 Complete!"<<endl;
    }
};

#endif