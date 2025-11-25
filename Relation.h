#ifndef MODULE6_RELATIONS_H
#define MODULE6_RELATIONS_H

#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <vector>
#include "BaseClasses.h"
using namespace std;

// Relations
template <typename T>
class Relations {
private:
    set<pair<T, T>> relations;
    set<T> domain;

public:
    void addRelation(T a, T b) {
        relations.insert({ a, b });
        domain.insert(a);
        domain.insert(b);
    }

    bool hasRelation(T a, T b) const {
        return relations.find({ a, b }) != relations.end();
    }

    set<pair<T, T>> getRelations() const { return relations; }
    set<T> getDomain() const { return domain; }

    bool isReflexive() const {
        for (const auto& elem : domain) {
            if (!hasRelation(elem, elem)) return false;
        }
        return true;
    }

    bool isSymmetric() const {
        for (const auto& rel : relations) {
            if (!hasRelation(rel.second, rel.first)) return false;
        }
        return true;
    }

    bool isTransitive() const {
        for (const auto& r1 : relations) {
            for (const auto& r2 : relations) {
                if (r1.second == r2.first) {
                    if (!hasRelation(r1.first, r2.second)) return false;
                }
            }
        }
        return true;
    }

    bool isEquivalenceRelation() const {
        return isReflexive() && isSymmetric() && isTransitive();
    }

    map<T, set<T>> getEquivalenceClasses() const {
        map<T, set<T>> classes;
        set<T> processed;

        for (const auto& elem : domain) {
            if (processed.find(elem) != processed.end()) continue;

            set<T> eqClass;
            for (const auto& other : domain) {
                if (hasRelation(elem, other)) {
                    eqClass.insert(other);
                    processed.insert(other);
                }
            }

            if (!eqClass.empty()) {
                classes[elem] = eqClass;
            }
        }

        return classes;
    }

    static Relations<T> compose(const Relations<T>& R1, const Relations<T>& R2) {
        Relations<T> result;
        for (const auto& r1 : R1.getRelations()) {
            for (const auto& r2 : R2.getRelations()) {
                if (r1.second == r2.first) {
                    result.addRelation(r1.first, r2.second);
                }
            }
        }
        return result;
    }

    void display() const {
        cout << "\nRelation: { ";
        for (const auto& r : relations) {
            cout << "(" << r.first << "," << r.second << ") ";
        }
        cout << "}"<< endl;
        cout << "Reflexive: " << (isReflexive() ? "Yes" : "No") << endl;
        cout << "Symmetric: " << (isSymmetric() ? "Yes" : "No") << endl;
        cout << "Transitive: " << (isTransitive() ? "Yes" : "No") << endl;
        cout << "Equivalence: " << (isEquivalenceRelation() ? "Yes" : "No") << "\n";
    }

    // INTERACTIVE: View Student-Course Relations
    static void viewStudentCourseRelations(const vector<Student>& students,
        const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     STUDENT-COURSE RELATIONS"<< endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        Relations<string> studentCourse;

        // Build relation from actual data
        for (const auto& student : students) {
            auto enrolledCourses = student.getCourses();
            for (const auto& courseId : enrolledCourses) {
                studentCourse.addRelation(student.getId(), courseId);
            }
        }

        if (studentCourse.getRelations().empty()) {
            cout << "[INFO] No student-course enrollments yet."<< endl;
            return;
        }
        cout << endl;
        cout << "[SUCCESS] Student-Course Relation (R):"<< endl;
        cout << "R = { ";
        for (const auto& rel : studentCourse.getRelations()) {
            cout << "(" << rel.first << ", " << rel.second << ") ";
        }
        cout << "}"<< endl;
        cout << endl;
        cout << "[INFO] Interpretation:"<< endl;
        for (const auto& rel : studentCourse.getRelations()) {
            // Find student and course names
            string studentName = rel.first;
            string courseName = rel.second;

            for (const auto& s : students) {
                if (s.getId() == rel.first) {
                    studentName = s.getName();
                    break;
                }
            }

            for (const auto& c : courses) {
                if (c.getId() == rel.second) {
                    courseName = c.getName();
                    break;
                }
            }

            cout << "  " << studentName << " enrolled in " << courseName << endl;
        }
        cout << endl;
        cout << "[INFO] Relation Properties:"<<endl;
        studentCourse.display();
    }

    // INTERACTIVE: View Faculty-Course Relations
    static void viewFacultyCourseRelations(const vector<Faculty>& faculties,
        const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     FACULTY-COURSE RELATIONS"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        Relations<string> facultyCourse;

        // Build relation
        for (const auto& faculty : faculties) {
            auto assignedCourses = faculty.getCourses();
            for (const auto& courseId : assignedCourses) {
                facultyCourse.addRelation(faculty.getId(), courseId);
            }
        }

        // Also check from course side
        for (const auto& course : courses) {
            if (!course.getFaculty().empty()) {
                facultyCourse.addRelation(course.getFaculty(), course.getId());
            }
        }

        if (facultyCourse.getRelations().empty()) {
            cout << "[INFO] No faculty-course assignments yet."<<endl;
            return;
        }
        cout << endl;
        cout << "[SUCCESS] Faculty-Course Relation:"<<endl;
        cout << "R = { ";
        for (const auto& rel : facultyCourse.getRelations()) {
            cout << "(" << rel.first << ", " << rel.second << ") ";
        }
        cout << "}"<<endl;
        cout << endl;
        cout << "[INFO] Assignments:"<<endl;
        for (const auto& rel : facultyCourse.getRelations()) {
            string facultyName = rel.first;
            string courseName = rel.second;

            for (const auto& f : faculties) {
                if (f.getId() == rel.first) {
                    facultyName = f.getName();
                    break;
                }
            }

            for (const auto& c : courses) {
                if (c.getId() == rel.second) {
                    courseName = c.getName();
                    break;
                }
            }

            cout << "  " << facultyName << " teaches " << courseName << endl;
        }

        facultyCourse.display();
    }

    // INTERACTIVE: View Course-Room Relations
    static void viewCourseRoomRelations(const vector<Course>& courses,
        const vector<Room>& rooms) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     COURSE-ROOM RELATIONS"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        Relations<string> courseRoom;

        // Build relation from course assignments
        for (const auto& course : courses) {
            if (!course.getRoom().empty()) {
                courseRoom.addRelation(course.getId(), course.getRoom());
            }
        }

        // Build from room assignments
        for (const auto& room : rooms) {
            if (!room.getAssignedCourse().empty()) {
                courseRoom.addRelation(room.getAssignedCourse(), room.getId());
            }
        }

        if (courseRoom.getRelations().empty()) {
            cout << "[INFO] No course-room assignments yet."<<endl;
            return;
        }
        cout << endl;
        cout << "[SUCCESS] Course-Room Relation:"<<endl;
        cout << "R = { ";
        for (const auto& rel : courseRoom.getRelations()) {
            cout << "(" << rel.first << ", " << rel.second << ") ";
        }
        cout << "}"<<endl;
        cout << endl;
        cout << "[INFO] Assignments:"<<endl;
        for (const auto& rel : courseRoom.getRelations()) {
            string courseName = rel.first;
            string roomName = rel.second;

            for (const auto& c : courses) {
                if (c.getId() == rel.first) {
                    courseName = c.getName();
                    break;
                }
            }

            for (const auto& r : rooms) {
                if (r.getId() == rel.second) {
                    roomName = r.getName();
                    break;
                }
            }

            cout << "  " << courseName << " assigned to " << roomName << endl;
        }

        courseRoom.display();
    }

    // CRITICAL: DETECT INDIRECT CONFLICTS
    static void detectIndirectConflicts(const vector<Student>& students,
        const vector<Course>& courses,
        const vector<Room>& rooms) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     DETECT INDIRECT CONFLICTS (CRITICAL!)"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << endl;
        cout << "[INFO] Checking for conflicts through relation composition..."<<endl<<endl;

        bool foundConflict = false;

        // CONFLICT TYPE 1: Time Conflicts via Relations
        cout << "    CHECK 1: Time Conflicts Through Relations "<<endl;

        // Build Student  Course relation
        Relations<string> studentCourse;
        for (const auto& s : students) {
            for (const auto& c : s.getCourses()) {
                studentCourse.addRelation(s.getId(), c);
            }
        }

        // Build Course  Room relation
        Relations<string> courseRoom;
        map<string, string> courseToTime; // Course  Time slot

        for (const auto& c : courses) {
            if (!c.getRoom().empty()) {
                courseRoom.addRelation(c.getId(), c.getRoom());
            }
        }

        for (const auto& r : rooms) {
            if (!r.getAssignedCourse().empty() && !r.getTimeSlot().empty()) {
                courseToTime[r.getAssignedCourse()] = r.getTimeSlot();
            }
        }

        // Compose: Student  Course  Room
        auto studentRoom = Relations<string>::compose(studentCourse, courseRoom);

        cout << "[INFO] Student ? Room (via course enrollment):"<<endl;
        for (const auto& rel : studentRoom.getRelations()) {
            cout << "  Student " << rel.first << " ? Room " << rel.second << endl;
        }

        // Check if same student enrolled in courses with same room at same time
        map<string, vector<string>> studentCourses;
        for (const auto& s : students) {
            for (const auto& c : s.getCourses()) {
                studentCourses[s.getId()].push_back(c);
            }
        }

        for (const auto& entry : studentCourses) {
            const string& studentId = entry.first;
            const vector<string>& coursesEnrolled = entry.second;

            for (size_t i = 0; i < coursesEnrolled.size(); i++) {
                for (size_t j = i + 1; j < coursesEnrolled.size(); j++) {
                    string c1 = coursesEnrolled[i];
                    string c2 = coursesEnrolled[j];

                    // Check if both courses have time slots
                    if (courseToTime.find(c1) != courseToTime.end() &&
                        courseToTime.find(c2) != courseToTime.end()) {

                        if (courseToTime[c1] == courseToTime[c2]) {
                            cout << endl;
                            cout << "[ERROR] INDIRECT CONFLICT DETECTED!"<<endl;
                            cout << "  Student: " << studentId << endl;
                            cout << "  Course 1: " << c1 << " at " << courseToTime[c1] << endl;
                            cout << "  Course 2: " << c2 << " at " << courseToTime[c2] << endl;
                            cout << "  Conflict: Both courses at same time!"<<endl;
                            foundConflict = true;
                        }
                    }
                }
            }
        }

        if (!foundConflict) {
            cout << "[SUCCESS] No time conflicts detected."<<endl;
        }

        //  CONFLICT TYPE 2: Room Conflicts 
        cout << "    CHECK 2: Room Double-Booking "<<endl;

        map<string, vector<pair<string, string>>> roomAssignments; 

        for (const auto& r : rooms) {
            if (!r.getAssignedCourse().empty() && !r.getTimeSlot().empty()) {
                roomAssignments[r.getId()].push_back({ r.getAssignedCourse(), r.getTimeSlot() });
            }
        }

        for (const auto& c : courses) {
            if (!c.getRoom().empty()) {
                // Check if this room is already assigned
                for (const auto& roomAssign : roomAssignments) {
                    for (const auto& assign : roomAssign.second) {
                        if (roomAssign.first == c.getRoom() &&
                            assign.first != c.getId()) {
                            // Potential conflict same room, different course
                            cout << "[WARNING] Room " << c.getRoom()
                                << " assigned to multiple courses:"<<endl;
                            cout << "  - " << assign.first << " at " << assign.second << endl;
                            cout << "  - " << c.getId() << endl;
                            foundConflict = true;
                        }
                    }
                }
            }
        }

        if (!foundConflict) {
            cout << "[SUCCESS] No room conflicts detected."<<endl;
        }

        // CONFLICT TYPE 3: Transitive Prerequisite Conflicts
        cout << "     CHECK 3: Prerequisite Chain Conflicts "<<endl;

        Relations<string> prerequisiteRelation;

        // Build prerequisite relation
        for (const auto& c : courses) {
            for (const auto& prereq : c.getPrerequisites()) {
                prerequisiteRelation.addRelation(c.getId(), prereq);
            }
        }

        // Check if any student enrolled in course without completing prerequisites
        for (const auto& s : students) {
            auto completed = s.getCourses();

            for (const auto& enrolledCourse : completed) {
                // Find this course
                for (const auto& c : courses) {
                    if (c.getId() == enrolledCourse) {
                        // Check prerequisites
                        for (const auto& prereq : c.getPrerequisites()) {
                            if (completed.find(prereq) == completed.end()) {
                                cout << endl;
                                cout << "[ERROR] PREREQUISITE CONFLICT!"<<endl;
                                cout << "  Student: " << s.getId() << " (" << s.getName() << ")"<<endl;
                                cout << "  Enrolled in: " << c.getId() << endl;
                                cout << "  Missing prerequisite: " << prereq << endl;
                                foundConflict = true;
                            }
                        }
                        break;
                    }
                }
            }
        }

        if (!foundConflict) {
            cout << "[SUCCESS] No prerequisite conflicts."<<endl;
        }

        // SUMMARY 
        cout << endl << endl;
        if (foundConflict) {
            cout << "[ERROR] CONFLICTS DETECTED THROUGH RELATIONS!"<<endl;
            cout << "Indirect conflicts found via relation composition."<<endl;
        }
        else {
            cout << "[SUCCESS] NO INDIRECT CONFLICTS DETECTED!"<<endl;
            cout << "All relations are consistent." << endl;
        }
        cout << endl << endl;
    }

    // MODULE MENU
    static void showMenu(const vector<Student>& students,
        const vector<Course>& courses,
        const vector<Faculty>& faculties,
        const vector<Room>& rooms) {
        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 6: RELATIONS"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. View Student-Course Relations"<<endl;
            cout << "  2. View Faculty-Course Relations"<<endl;
            cout << "  3. View Course-Room Relations"<<endl;
            cout << "  4. Check Relation Properties"<<endl;
            cout << "  5. Compose Relations"<<endl;
            cout << "  6. Detect Indirect Conflicts (CRITICAL!)"<<endl;
            cout << "  7. Run Demonstration"<<endl;
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
                viewStudentCourseRelations(students, courses);
                break;
            case 2:
                viewFacultyCourseRelations(faculties, courses);
                break;
            case 3:
                viewCourseRoomRelations(courses, rooms);
                break;
            case 4: {
                Relations<string> R;
                R.addRelation("A", "A");
                R.addRelation("B", "B");
                R.addRelation("A", "B");
                R.addRelation("B", "A");
                cout << "\n[INFO] Example Relation:"<<endl;
                R.display();
                break;
            }
            case 5: {
                cout << endl;
                cout << "[INFO] Composing Student o Course o Room:"<<endl;
                Relations<string> SC, CR;
                for (const auto& s : students) {
                    for (const auto& c : s.getCourses()) {
                        SC.addRelation(s.getId(), c);
                    }
                }
                for (const auto& c : courses) {
                    if (!c.getRoom().empty()) {
                        CR.addRelation(c.getId(), c.getRoom());
                    }
                }
                auto composed = Relations<string>::compose(SC, CR);
                cout << "[SUCCESS] Composed Relation (Student o Room):"<<endl;
                composed.display();
                break;
            }
            case 6:
                detectIndirectConflicts(students, courses, rooms);
                break;
            case 7:
                demonstrate();
                break;
            default:
                cout << "[ERROR] Invalid choice!"<<endl;
            }

            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    static void demonstrate() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     MODULE 6: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        Relations<string> prereq;
        prereq.addRelation("CS101", "CS101");
        prereq.addRelation("CS201", "CS201");
        prereq.addRelation("CS301", "CS301");
        prereq.addRelation("CS101", "CS201");
        prereq.addRelation("CS201", "CS301");
        prereq.addRelation("CS101", "CS301");
        cout << endl;
        cout << "[SUCCESS] Prerequisite Relation (Partial Order):"<<endl;
        prereq.display();
        cout << endl;
        cout << "[SUCCESS] Module 6 Complete!"<<endl;
    }
};

#endif