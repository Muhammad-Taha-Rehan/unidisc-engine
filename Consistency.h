#ifndef MODULE9_CONSISTENCY_H
#define MODULE9_CONSISTENCY_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <limits>
#include "BaseClasses.h"
using namespace std;

//Consistency Checker
class ConsistencyChecker {
private:
    map<string, set<string>> studentCourses;
    map<string, string> courseTimes;
    map<string, int> courseCredits;
    map<string, set<string>> coursePrereqs;
    map<string, string> courseRooms;
    map<string, string> courseFaculty;

public:
    void enrollStudent(const string& student, const string& course) {
        studentCourses[student].insert(course);
    }

    void setCourseTime(const string& course, const string& time) {
        courseTimes[course] = time;
    }

    void setCourseCredits(const string& course, int credits) {
        courseCredits[course] = credits;
    }

    void addPrereq(const string& course, const string& prereq) {
        coursePrereqs[course].insert(prereq);
    }

    void setCourseRoom(const string& course, const string& room) {
        courseRooms[course] = room;
    }

    void setCourseFaculty(const string& course, const string& faculty) {
        courseFaculty[course] = faculty;
    }

    // Check time conflicts for a student
    vector<string> checkTimeConflicts(const string& student) {
        vector<string> conflicts;
        vector<string> courses(studentCourses[student].begin(),
            studentCourses[student].end());

        for (size_t i = 0; i < courses.size(); i++) {
            for (size_t j = i + 1; j < courses.size(); j++) {
                if (courseTimes[courses[i]] == courseTimes[courses[j]] &&
                    !courseTimes[courses[i]].empty()) {
                    conflicts.push_back(courses[i] + " & " + courses[j] +
                        " overlap at " + courseTimes[courses[i]]);
                }
            }
        }
        return conflicts;
    }

    // Check if student is overloaded
    bool checkOverload(const string& student, int max = 18) {
        int total = 0;
        for (const auto& c : studentCourses[student]) {
            total += courseCredits[c];
        }
        return total > max;
    }

    int getTotalCredits(const string& student) {
        int total = 0;
        for (const auto& c : studentCourses[student]) {
            total += courseCredits[c];
        }
        return total;
    }

    // Check prerequisite violations
    vector<string> checkPrerequisiteViolations(const string& student) {
        vector<string> violations;
        auto enrolled = studentCourses[student];

        for (const auto& course : enrolled) {
            for (const auto& prereq : coursePrereqs[course]) {
                if (enrolled.find(prereq) == enrolled.end()) {
                    violations.push_back(course + " requires " + prereq + " (not taken)");
                }
            }
        }
        return violations;
    }

    // Check room conflicts
    vector<string> checkRoomConflicts() {
        vector<string> conflicts;
        map<string, vector<string>> roomAssignments;

        for (const auto& entry : courseRooms) {
            roomAssignments[entry.second].push_back(entry.first);
        }

        for (const auto& entry : roomAssignments) {
            if (entry.second.size() > 1) {
                // Check if they have same time
                for (size_t i = 0; i < entry.second.size(); i++) {
                    for (size_t j = i + 1; j < entry.second.size(); j++) {
                        string c1 = entry.second[i];
                        string c2 = entry.second[j];
                        if (courseTimes[c1] == courseTimes[c2] && !courseTimes[c1].empty()) {
                            conflicts.push_back("Room " + entry.first + ": " +
                                c1 + " and " + c2 + " at " + courseTimes[c1]);
                        }
                    }
                }
            }
        }
        return conflicts;
    }

    // Check faculty conflicts
    vector<string> checkFacultyConflicts() {
        vector<string> conflicts;
        map<string, vector<string>> facultyAssignments;

        for (const auto& entry : courseFaculty) {
            facultyAssignments[entry.second].push_back(entry.first);
        }

        for (const auto& entry : facultyAssignments) {
            if (entry.second.size() > 1) {
                // Check if same time
                for (size_t i = 0; i < entry.second.size(); i++) {
                    for (size_t j = i + 1; j < entry.second.size(); j++) {
                        string c1 = entry.second[i];
                        string c2 = entry.second[j];
                        if (courseTimes[c1] == courseTimes[c2] && !courseTimes[c1].empty()) {
                            conflicts.push_back("Faculty " + entry.first + ": " +
                                c1 + " and " + c2 + " at " + courseTimes[c1]);
                        }
                    }
                }
            }
        }
        return conflicts;
    }

    void performCheck() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          COMPREHENSIVE CONSISTENCY CHECK"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        bool allGood = true;

        // Check each student
        for (const auto& s : studentCourses) {
            cout << endl;
            cout << "    Student: " << s.first << "    "<<endl;

            // Time conflicts
            auto conflicts = checkTimeConflicts(s.first);
            if (!conflicts.empty()) {
                allGood = false;
                cout << "    Time conflicts:"<<endl;
                for (const auto& c : conflicts) cout << "    " << c << endl;
            }

            // Credit overload
            int total = getTotalCredits(s.first);
            cout << "  Credits: " << total;
            if (checkOverload(s.first)) {
                allGood = false;
                cout << "   OVERLOAD (max 18)"<<endl;
            }
            else {
                cout << endl;
            }

            // Prerequisite violations
            auto prereqViolations = checkPrerequisiteViolations(s.first);
            if (!prereqViolations.empty()) {
                allGood = false;
                cout << "    Prerequisite violations:"<<endl;
                for (const auto& v : prereqViolations) {
                    cout << "    " << v << endl;
                }
            }
        }

        // Check room conflicts
        auto roomConflicts = checkRoomConflicts();
        if (!roomConflicts.empty()) {
            allGood = false;
            cout << endl;
            cout << "    Room Conflicts"<<endl;
            for (const auto& c : roomConflicts) {
                cout << "  ! " << c << endl;
            }
        }

        // Check faculty conflicts
        auto facultyConflicts = checkFacultyConflicts();
        if (!facultyConflicts.empty()) {
            allGood = false;
            cout << "     Faculty Conflicts"<<endl;
            for (const auto& c : facultyConflicts) {
                cout << "  ! " << c << endl;
            }
        }

        cout << endl << string(60, '=') << endl;
        cout << (allGood ? "  All checks passed!\n" : "! Issues found!\n");
    }

    // INTERACTIVE MENU
    static void showMenu(vector<Student>& students, vector<Course>& courses,
        vector<Faculty>& faculties, vector<Room>& rooms) {

        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "    MODULE 9: CONSISTENCY CHECKER"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. Check All Students for Conflicts"<<endl;
            cout << "  2. Check Specific Student"<<endl;
            cout << "  3. Check Room Conflicts"<<endl;
            cout << "  4. Check Faculty Conflicts"<<endl;
            cout << "  5. Check Prerequisite Violations"<<endl;
            cout << "  6. Run Complete System Check"<<endl;
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

            ConsistencyChecker checker;

            // Build checker from actual data
            for (const auto& s : students) {
                for (const auto& c : s.getCourses()) {
                    checker.enrollStudent(s.getId(), c);
                }
            }

            for (const auto& c : courses) {
                checker.setCourseCredits(c.getId(), 3); // Default 3 credits
                for (const auto& p : c.getPrerequisites()) {
                    checker.addPrereq(c.getId(), p);
                }
                if (!c.getRoom().empty()) {
                    checker.setCourseRoom(c.getId(), c.getRoom());
                }
                if (!c.getFaculty().empty()) {
                    checker.setCourseFaculty(c.getId(), c.getFaculty());
                }
            }

            for (const auto& r : rooms) {
                if (!r.getAssignedCourse().empty()) {
                    checker.setCourseTime(r.getAssignedCourse(), r.getTimeSlot());
                }
            }

            switch (choice) {
            case 1: {
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "    CHECKING ALL STUDENTS "<<endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                bool foundIssue = false;
                for (const auto& s : students) {
                    auto conflicts = checker.checkTimeConflicts(s.getId());
                    if (!conflicts.empty() || checker.checkOverload(s.getId())) {
                        foundIssue = true;
                        cout << endl << s.getName() << " (" << s.getId() << "):"<<endl;
                        for (const auto& c : conflicts) {
                            cout << "  ! " << c << endl;
                        }
                        if (checker.checkOverload(s.getId())) {
                            cout << "  ! Credit overload: " << checker.getTotalCredits(s.getId()) << " credits"<<endl;
                        }
                    }
                }
                if (!foundIssue) {
                    cout << "  No conflicts found for any student!"<<endl;
                }
                break;
            }

            case 2: {
                if (students.empty()) {
                    cout << "[ERROR] No students available!"<<endl;
                    break;
                }
                cout << endl;
                cout << "[INFO] Select Student:"<<endl;
                for (size_t i = 0; i < students.size(); i++) {
                    cout << "  " << (i + 1) << ". " << students[i].getName() << endl;
                }
                cout << "Choice: ";
                int idx;
                cin >> idx;
                if (idx < 1 || idx >(int)students.size()) {
                    cout << "[ERROR] Invalid choice!"<<endl;
                    break;
                }

                const auto& student = students[idx - 1];
                cout << endl;
                cout << "     " << student.getName() << "     "<<endl;
                cout << "Enrolled courses: " << student.getCourses().size() << endl;
                cout << "Total credits: " << checker.getTotalCredits(student.getId()) << "\n";

                auto conflicts = checker.checkTimeConflicts(student.getId());
                if (conflicts.empty()) {
                    cout << "  No time conflicts"<<endl;
                }
                else {
                    cout << "  Time conflicts:"<<endl;
                    for (const auto& c : conflicts) cout << "  " << c << endl;
                }

                auto violations = checker.checkPrerequisiteViolations(student.getId());
                if (violations.empty()) {
                    cout << "  All prerequisites satisfied"<<endl;
                }
                else {
                    cout << "! Prerequisite violations:"<<endl;
                    for (const auto& v : violations) cout << "  " << v << endl;
                }
                break;
            }

            case 3: {
                auto conflicts = checker.checkRoomConflicts();
                if (conflicts.empty()) {
                    cout << endl;
                    cout << " No room conflicts detected!"<<endl;
                }
                else {
                    cout << endl;
                    cout << "! Room conflicts detected:"<<endl;
                    for (const auto& c : conflicts) {
                        cout << "  " << c << endl;
                    }
                }
                break;
            }

            case 4: {
                auto conflicts = checker.checkFacultyConflicts();
                if (conflicts.empty()) {
                    cout << endl;
                    cout << "  No faculty conflicts detected!" << endl;
                }
                else {
                    cout << endl;
                    cout << "! Faculty conflicts detected:"<<endl;
                    for (const auto& c : conflicts) {
                        cout << "  " << c << endl;
                    }
                }
                break;
            }

            case 5: {
                cout << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "     PREREQUISITE VIOLATIONS " << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                bool foundViolation = false;
                for (const auto& s : students) {
                    auto violations = checker.checkPrerequisiteViolations(s.getId());
                    if (!violations.empty()) {
                        foundViolation = true;
                        cout << endl << s.getName() << ":"<<endl;
                        for (const auto& v : violations) {
                            cout << "  ! " << v << endl;
                        }
                    }
                }
                if (!foundViolation) {
                    cout << "  No prerequisite violations found!"<<endl;
                }
                break;
            }

            case 6:
                checker.performCheck();
                break;

            case 7:
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
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "    MODULE 9: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        ConsistencyChecker checker;

        // Setup demo data
        checker.setCourseTime("CS101", "MWF 9:00");
        checker.setCourseTime("Math101", "MWF 9:00");
        checker.setCourseCredits("CS101", 4);
        checker.setCourseCredits("Math101", 4);
        checker.setCourseCredits("CS201", 4);
        checker.setCourseCredits("Physics101", 3);
        checker.setCourseCredits("English101", 3);

        checker.addPrereq("CS201", "CS101");

        checker.enrollStudent("Ali", "CS101");
        checker.enrollStudent("Ali", "Math101");
        checker.enrollStudent("Ali", "CS201");
        checker.enrollStudent("Ali", "Physics101");
        checker.enrollStudent("Ali", "English101");

        checker.performCheck();
        cout << endl;
        cout << "  Module 9 Complete!"<<endl;
    }
};

#endif