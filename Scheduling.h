#ifndef MODULE1_SCHEDULING_H
#define MODULE1_SCHEDULING_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
#include <limits>
#include "BaseClasses.h"
using namespace std;

// Course & Scheduling Module
class CourseScheduler {
private:
    map<string, set<string>> prerequisites;
    map<string, set<string>> adjacencyList;
    set<string> allCourses;

public:
    void addCourse(const string& courseId) {
        allCourses.insert(courseId);
        if (prerequisites.find(courseId) == prerequisites.end()) {
            prerequisites[courseId] = set<string>();
        }
    }

    void addPrerequisite(const string& course, const string& prereq) {
        prerequisites[course].insert(prereq);
        adjacencyList[prereq].insert(course);
        allCourses.insert(course);
        allCourses.insert(prereq);
    }

    vector<string> getValidSequence() {
        map<string, int> inDegree;
        for (const auto& course : allCourses) {
            inDegree[course] = prerequisites[course].size();
        }

        queue<string> q;
        for (const auto& course : allCourses) {
            if (inDegree[course] == 0) {
                q.push(course);
            }
        }

        vector<string> result;
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            result.push_back(current);

            for (const auto& dependent : adjacencyList[current]) {
                inDegree[dependent]--;
                if (inDegree[dependent] == 0) {
                    q.push(dependent);
                }
            }
        }

        if (result.size() != allCourses.size()) {
            cout << "[ERROR] Circular dependency detected!"<<endl;
            return {};
        }

        return result;
    }

    bool canTakeCourse(const string& course, const set<string>& completedCourses) {
        for (const auto& prereq : prerequisites[course]) {
            if (completedCourses.find(prereq) == completedCourses.end()) {
                return false;
            }
        }
        return true;
    }

    vector<string> getAvailableCourses(const set<string>& completedCourses) {
        vector<string> available;
        for (const auto& course : allCourses) {
            if (completedCourses.find(course) == completedCourses.end() &&
                canTakeCourse(course, completedCourses)) {
                available.push_back(course);
            }
        }
        return available;
    }

    //  Check Missing Prerequisites
    vector<string> getMissingPrerequisites(const string& course,
        const set<string>& completedCourses) {
        vector<string> missing;
        for (const auto& prereq : prerequisites[course]) {
            if (completedCourses.find(prereq) == completedCourses.end()) {
                missing.push_back(prereq);
            }
        }
        return missing;
    }

    //  Validate Enrollment 
    bool validateEnrollment(Student& student, const string& courseId,
        const vector<Course>& allCoursesData) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     ENROLLMENT VALIDATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << endl;
        cout << "[INFO] Student: " << student.getName() << " (" << student.getId() << ")"<<endl;
        cout << "[INFO] Requesting: " << courseId << endl;

        // Get student completed courses
        set<string> completed = student.getCourses();

        // Check prerequisites
        auto missing = getMissingPrerequisites(courseId, completed);

        if (missing.empty()) {
            cout << endl;
            cout << "[SUCCESS] All prerequisites satisfied!"<<endl;
            cout << "[SUCCESS] Student can enroll in " << courseId << endl;
            return true;
        }
        else {
            cout << endl;
            cout << "[ERROR] Cannot enroll! Missing prerequisites:"<<endl;
            for (const auto& m : missing) {
                cout << "  - " << m;
                // Find course name
                for (const auto& c : allCoursesData) {
                    if (c.getId() == m) {
                        cout << " (" << c.getName() << ")";
                        break;
                    }
                }
                cout << endl;
            }
            cout << endl;
            cout << "[INFO] Student must complete these courses first!"<<endl;
            return false;
        }
    }

    // INTERACTIVE: View Course Prerequisites
    static void viewPrerequisitesInteractive(const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     COURSE PREREQUISITES"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (courses.empty()) {
            cout << "[ERROR] No courses available!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Courses:" << endl;
        cout << "[INFO] Available Courses:" << endl;
        for (size_t i = 0; i < courses.size(); i++) {
            cout << "  " << (i + 1) << ". " << courses[i].getId()
                << " - " << courses[i].getName() << endl;
        }
        cout << endl;
        cout << "Select course to view prerequisites (1-" << courses.size() << "): ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice >(int)courses.size()) {
            cout << "[ERROR] Invalid choice!"<<endl;
            return;
        }

        const Course& selected = courses[choice - 1];
        cout << endl;
        cout << "[SUCCESS] Course: " << selected.getName()
            << " (" << selected.getId() << ")" << endl;

        auto prereqs = selected.getPrerequisites();
        if (prereqs.empty()) {
            cout << "[INFO] No prerequisites required!"<<endl;
        }
        else {
            cout << "[INFO] Prerequisites:"<<endl;
            for (const auto& p : prereqs) {
                cout << "  - " << p;
                for (const auto& c : courses) {
                    if (c.getId() == p) {
                        cout << " (" << c.getName() << ")";
                        break;
                    }
                }
                cout << endl;
            }
        }
    }

    // Check Enrollment Eligibility
    static void checkEnrollmentEligibility(vector<Student>& students,
        const vector<Course>& courses) {
        cout << endl << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     CHECK ENROLLMENT ELIGIBILITY"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (students.empty()) {
            cout << "[ERROR] No students available!"<<endl;
            return;
        }

        if (courses.empty()) {
            cout << "[ERROR] No courses available!"<<endl;
            return;
        }

        // Select student
        cout << endl;
        cout << "[INFO] Select Student:"<<endl;
        for (size_t i = 0; i < students.size(); i++) {
            cout << "  " << (i + 1) << ". " << students[i].getName()
                << " (" << students[i].getId() << ")"<<endl;
        }
        cout << "Choice: ";
        int studentChoice;
        cin >> studentChoice;

        if (studentChoice < 1 || studentChoice >(int)students.size()) {
            cout << "[ERROR] Invalid choice!"<<endl;
            return;
        }

        Student& student = students[studentChoice - 1];

        // Select course
        cout << endl;
        cout << "[INFO] Select Course to Enroll:"<<endl;
        for (size_t i = 0; i < courses.size(); i++) {
            cout << "  " << (i + 1) << ". " << courses[i].getId()
                << " - " << courses[i].getName() << endl;
        }
        cout << "Choice: ";
        int courseChoice;
        cin >> courseChoice;

        if (courseChoice < 1 || courseChoice >(int)courses.size()) {
            cout << "[ERROR] Invalid choice!"<<endl;
            return;
        }

        const Course& course = courses[courseChoice - 1];

        // Build scheduler with prerequisites
        CourseScheduler scheduler;
        for (const auto& c : courses) {
            scheduler.addCourse(c.getId());
            for (const auto& p : c.getPrerequisites()) {
                scheduler.addPrerequisite(c.getId(), p);
            }
        }

        // Validate
        bool canEnroll = scheduler.validateEnrollment(student, course.getId(), courses);

        if (canEnroll) {
            char confirm;
            cout << endl;
            cout << "Enroll student? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                student.enrollCourse(course.getId());
                cout << "[SUCCESS] Enrolled!"<<endl;
            }
        }
    }

    // INTERACTIVE: Get Available Courses for Student
    static void getAvailableCoursesInteractive(const vector<Student>& students,
        const vector<Course>& courses) {

        cout << endl << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     AVAILABLE COURSES FOR STUDENT"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (students.empty() || courses.empty()) {
            cout << "[ERROR] No data available!"<<endl;
            return;
        }

        // Select student
        cout << endl;
        cout << "[INFO] Select Student:"<<endl;
        for (size_t i = 0; i < students.size(); i++) {
            cout << "  " << (i + 1) << ". " << students[i].getName()
                << " (" << students[i].getId() << ")"<<endl;
        }
        cout << "Choice: ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice >(int)students.size()) {
            cout << "[ERROR] Invalid choice!"<<endl;
            return;
        }

        const Student& student = students[choice - 1];
        cout << endl;
        cout << "[INFO] Student: " << student.getName() << endl;
        cout << "[INFO] Completed Courses:"<<endl;
        auto completed = student.getCourses();
        if (completed.empty()) {
            cout << "  (None - freshman student)"<<endl;
        }
        else {
            for (const auto& c : completed) {
                cout << "  - " << c << endl;
            }
        }

        // Build scheduler
        CourseScheduler scheduler;
        for (const auto& c : courses) {
            scheduler.addCourse(c.getId());
            for (const auto& p : c.getPrerequisites()) {
                scheduler.addPrerequisite(c.getId(), p);
            }
        }

        auto available = scheduler.getAvailableCourses(completed);
        cout << endl;
        cout << "[SUCCESS] Available Courses:"<<endl;
        if (available.empty()) {
            cout << "  (None - all courses require prerequisites or already taken)"<<endl;
        }
        else {
            for (const auto& a : available) {
                cout << "  - " << a;
                for (const auto& c : courses) {
                    if (c.getId() == a) {
                        cout << " - " << c.getName();
                        break;
                    }
                }
                cout << "\n";
            }
        }
    }

    void display() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "    MODULE 1: COURSE SCHEDULING "<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        for (const auto& course : allCourses) {
            cout << course << " requires: ";
            if (prerequisites[course].empty()) {
                cout << "None";
            }
            else {
                for (const auto& prereq : prerequisites[course]) {
                    cout << prereq << " ";
                }
            }
            cout << endl;
        }
    }

    // MODULE MENU
    static void showMenu(vector<Student>& students, const vector<Course>& courses) {
        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 1: COURSE SCHEDULING"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. View All Courses & Prerequisites"<<endl;
            cout << "  2. Generate Valid Course Sequence" << endl;
            cout << "  3. Check if Student Can Enroll in Course" << endl;
            cout << "  4. Get Available Courses for Student";
            cout << "  5. View Course Prerequisites" << endl;
            cout << "  6. Run Demonstration (Hard-coded Examples)" << endl;
            cout << "  0. Back to Main Menu" << endl<<endl;
            cout << "    Choice: ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (choice == 0) break;

            switch (choice) {
            case 1: {
                cout << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "     ALL COURSES & PREREQUISITES"<<endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << endl;
                for (const auto& c : courses) {
                    cout << endl << c.getId() << " - " << c.getName() << endl;
                    auto prereqs = c.getPrerequisites();
                    if (prereqs.empty()) {
                        cout << "  Prerequisites: None"<<endl;
                    }
                    else {
                        cout << "  Prerequisites: ";
                        for (const auto& p : prereqs) cout << p << " ";
                        cout << endl;
                    }
                }
                break;
            }
            case 2: {
                CourseScheduler scheduler;
                for (const auto& c : courses) {
                    scheduler.addCourse(c.getId());
                    for (const auto& p : c.getPrerequisites()) {
                        scheduler.addPrerequisite(c.getId(), p);
                    }
                }
                scheduler.display();
                auto seq = scheduler.getValidSequence();
                cout << endl;
                cout << "[SUCCESS] Recommended Sequence:"<<endl;
                for (size_t i = 0; i < seq.size(); i++) {
                    cout << "  Semester " << (i + 1) << ": " << seq[i] << endl;
                }
                break;
            }
            case 3:
                checkEnrollmentEligibility(students, courses);
                break;
            case 4:
                getAvailableCoursesInteractive(students, courses);
                break;
            case 5:
                viewPrerequisitesInteractive(courses);
                break;
            case 6:
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
        cout << endl << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     MODULE 1: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        CourseScheduler scheduler;
        scheduler.addCourse("CS101");
        scheduler.addCourse("CS201");
        scheduler.addCourse("CS301");
        scheduler.addCourse("Math101");
        scheduler.addCourse("Math201");

        scheduler.addPrerequisite("CS201", "CS101");
        scheduler.addPrerequisite("CS301", "CS201");
        scheduler.addPrerequisite("CS301", "Math201");
        scheduler.addPrerequisite("Math201", "Math101");

        scheduler.display();
        cout << endl;
        cout << "[SUCCESS] Valid Course Sequence:"<<endl;
        auto sequence = scheduler.getValidSequence();
        for (size_t i = 0; i < sequence.size(); i++) {
            cout << "  Semester " << (i + 1) << ": " << sequence[i] << endl;
        }
        cout << endl;
        cout << "[INFO] Student with CS101, Math101 can take:"<<endl;
        set<string> completed = { "CS101", "Math101" };
        auto available = scheduler.getAvailableCourses(completed);
        for (const auto& course : available) {
            cout << "  - " << course << endl;
        }
        cout << endl;
        cout << "[SUCCESS] Module 1 Complete!"<<endl;
    }
};

#endif