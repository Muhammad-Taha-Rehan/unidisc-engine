#ifndef MODULE3_INDUCTION_H
#define MODULE3_INDUCTION_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <limits>
#include "BaseClasses.h"
using namespace std;

//Induction & Strong Induction Module
class InductionVerifier {
private:
    map<string, set<string>> prerequisites;

public:
    void addPrerequisite(const string& course, const string& prereq) {
        prerequisites[course].insert(prereq);
    }

    // VERIFY USING MATHEMATICAL INDUCTION
    bool verifyPrerequisiteChain(const vector<string>& chain) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     MATHEMATICAL INDUCTION PROOF"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << endl;
        cout << "[INFO] Prerequisite Chain to Verify:"<<endl;
        cout << "Chain: ";
        for (const auto& course : chain) cout << course << " ? ";
        cout << "END"<<endl<<endl;

        // Base case
        cout << "    BASE CASE (n=1)"<<endl;
        cout << "Course: " << chain[0] << endl;

        if (prerequisites[chain[0]].empty()) {
            cout << "Prerequisites: None"<<endl;
            cout << "[SUCCESS]  Base case holds - First course has no prerequisites"<<endl;
        }
        else {
            cout << "Prerequisites: ";
            for (const auto& p : prerequisites[chain[0]]) cout << p << " ";
            cout << endl;
            cout << "[ERROR]  Base case fails - First course has prerequisites!"<<endl;
            return false;
        }

        // Inductive step
        cout << endl;
        cout << "    INDUCTIVE HYPOTHESIS"<<endl;
        cout << "Assume: Student can take all courses up to position k"<<endl;
        cout << endl;
        cout << "    INDUCTIVE STEP "<<endl;
        cout << "Prove: Student can take course at position k+1"<<endl<<endl;

        bool valid = true;
        for (size_t i = 1; i < chain.size(); i++) {
            cout << "    Step " << i << ": Verify " << chain[i] << "     "<<endl;

            if (prerequisites[chain[i]].empty()) {
                cout << "Prerequisites: None"<<endl;
                cout << "[SUCCESS]  Can be taken at any time"<<endl<<endl;
            }
            else {
                cout << "Prerequisites required: { ";
                for (const auto& prereq : prerequisites[chain[i]]) {
                    cout << prereq << " ";
                }
                cout << "}"<<endl;

                // Check if all prerequisites appear before this in chain
                bool allSatisfied = true;
                for (const auto& prereq : prerequisites[chain[i]]) {
                    bool found = false;
                    for (size_t j = 0; j < i; j++) {
                        if (chain[j] == prereq) {
                            found = true;
                            cout << "  ? " << prereq << " satisfied at position " << (j + 1) << endl;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "  ? " << prereq << " NOT satisfied!"<<endl;
                        allSatisfied = false;
                        valid = false;
                    }
                }

                if (allSatisfied) {
                    cout << "[SUCCESS]  All prerequisites satisfied by inductive hypothesis"<<endl<<endl;
                }
                else {
                    cout << "[ERROR]  Prerequisite violation detected!"<<endl<<endl;
                }
            }
        }

        cout << "    CONCLUSION "<<endl;
        if (valid) {
            cout << "[SUCCESS]  By mathematical induction, the chain is VALID"<<endl;
            cout << "Every course's prerequisites are satisfied before enrollment."<<endl;
        }
        else {
            cout << "[ERROR]  PROOF FAILS - Chain violates prerequisite constraints"<<endl;
        }

        return valid;
    }

    // VERIFY USING STRONG INDUCTION
    bool verifyWithStrongInduction(const string& course, const set<string>& completed) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     STRONG INDUCTION VERIFICATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout<<endl;
        cout << "[INFO] Target Course: " << course << endl;
        cout << "[INFO] Completed Courses: { ";
        for (const auto& c : completed) cout << c << " ";
        cout << "}"<<endl<<endl;

        cout << "    STRONG INDUCTION PRINCIPLE "<<endl;
        cout << "To prove P(n), we can assume P(1), P(2), ..., P(n-1) are ALL true"<<endl;
        cout << "(Unlike regular induction which only assumes P(k))"<<endl<<endl;

        return verifyStrongHelper(course, completed, 0);
    }

private:
    bool verifyStrongHelper(const string& course, const set<string>& completed, int depth) {
        string indent(depth * 2, ' ');

        cout << indent << "Checking: " << course << endl;

        // Base case
        if (prerequisites[course].empty()) {
            cout << indent << "  [SUCCESS]  No prerequisites"<<endl;
            return true;
        }

        // Check each prerequisite
        cout << indent << "  Prerequisites: { ";
        for (const auto& p : prerequisites[course]) cout << p << " ";
        cout << "}"<<endl;

        for (const auto& prereq : prerequisites[course]) {
            cout << indent << " - " << prereq;

            if (completed.find(prereq) != completed.end()) {
                cout << "  (completed)"<<endl;
            }
            else {
                cout << "  (not completed)"<<endl;
                cout << indent << "    Using strong induction to verify " << prereq << ":"<<endl;

                if (!verifyStrongHelper(prereq, completed, depth + 1)) {
                    return false;
                }
            }
        }

        cout << indent << "  [SUCCESS]  All prerequisites verified"<<endl;
        return true;
    }

public:
    // Verify Chain for Specific Courses
    static void verifyChainInteractive(const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     VERIFY PREREQUISITE CHAIN"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (courses.empty()) {
            cout << "[ERROR] No courses available!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Courses:"<<endl;
        for (size_t i = 0; i < courses.size(); i++) {
            cout << "  " << (i + 1) << ". " << courses[i].getId()
                << " - " << courses[i].getName() << endl;
        }
        cout << endl;
        cout << "[INFO] Select courses for chain (enter 0 to finish):"<<endl;
        vector<string> chain;

        while (true) {
            cout << "Add course (1-" << courses.size() << ", 0 to finish): ";
            int choice;
            cin >> choice;

            if (choice == 0) break;

            if (choice < 1 || choice >(int)courses.size()) {
                cout << "[ERROR] Invalid choice!"<<endl;
                continue;
            }

            chain.push_back(courses[choice - 1].getId());
            cout << "[SUCCESS] Added " << courses[choice - 1].getId() << " to chain"<<endl;
        }

        if (chain.empty()) {
            cout << "[ERROR] No courses selected!"<<endl;
            return;
        }

        // Build prerequisites
        InductionVerifier verifier;
        for (const auto& c : courses) {
            for (const auto& p : c.getPrerequisites()) {
                verifier.addPrerequisite(c.getId(), p);
            }
        }

        // Verify
        verifier.verifyPrerequisiteChain(chain);
    }

    // Check Student's Progress
    static void checkStudentProgress(const vector<Student>& students,
        const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     CHECK STUDENT PROGRESS WITH INDUCTION" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (students.empty()) {
            cout << "[ERROR] No students available!"<<endl;
            return;
        }
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
        auto completed = student.getCourses();
        cout << endl;
        cout << "[INFO] Student: " << student.getName() << endl;
        cout << "[INFO] Completed Courses: { ";
        for (const auto& c : completed) cout << c << " ";
        cout << "}"<<endl;

        if (completed.empty()) {
            cout << endl;
            cout << "[INFO] Freshman student - no courses completed yet"<<endl;
            cout << "[INFO] Can take any course with no prerequisites"<<endl;

            // Show available courses
            cout << endl;
            cout << "[INFO] Available courses:"<<endl;
            for (const auto& c : courses) {
                if (c.getPrerequisites().empty()) {
                    cout << "  ? " << c.getId() << " - " << c.getName() << endl;
                }
            }
            return;
        }

        // Now select a target course
        cout << endl;
        cout << "[INFO] Select target course to verify:"<<endl;
        for (size_t i = 0; i < courses.size(); i++) {
            cout << "  " << (i + 1) << ". " << courses[i].getId()
                << " - " << courses[i].getName() <<endl;
        }

        cout << "Choice : ";
        int courseChoice;
        cin >> courseChoice;

        if (courseChoice < 1 || courseChoice >(int)courses.size()) {
            cout << "[ERROR] Invalid choice!"<<endl;
            return;
        }

        const Course& targetCourse = courses[courseChoice - 1];

        // Build verifier
        InductionVerifier verifier;
        for (const auto& c : courses) {
            for (const auto& p : c.getPrerequisites()) {
                verifier.addPrerequisite(c.getId(), p);
            }
        }

        // Use strong induction to verify
        bool canTake = verifier.verifyWithStrongInduction(targetCourse.getId(), completed);
        cout << endl;
        cout << "    FINAL RESULT "<<endl;
        if (canTake) {
            cout << "[SUCCESS]  Student CAN take " << targetCourse.getName() << endl;
            cout << "All prerequisites satisfied (verified by strong induction)"<<endl;
        }
        else {
            cout << "[ERROR]  Student CANNOT take " << targetCourse.getName() << endl;
            cout << "Missing prerequisites detected"<<endl;
        }
    }

    // INTERACTIVE: Generate Valid Sequence
    static void generateValidSequence(const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     GENERATE VALID SEQUENCE USING INDUCTION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (courses.empty()) {
            cout << "[ERROR] No courses available!"<<endl;
            return;
        }

        InductionVerifier verifier;
        for (const auto& c : courses) {
            for (const auto& p : c.getPrerequisites()) {
                verifier.addPrerequisite(c.getId(), p);
            }
        }

        // Build a valid sequence using topological sort principle
        set<string> completed;
        vector<string> sequence;
        cout << endl;
        cout << "[INFO] Building valid sequence..."<<endl<<endl;

        bool changed = true;
        int semester = 1;

        while (changed && sequence.size() < courses.size()) {
            changed = false;

            cout << "Semester " << semester << ":" << endl;;

            for (const auto& c : courses) {
                // Skip if already in sequence
                if (find(sequence.begin(), sequence.end(), c.getId()) != sequence.end()) {
                    continue;
                }

                // Check if can take
                bool canTake = true;
                for (const auto& prereq : c.getPrerequisites()) {
                    if (completed.find(prereq) == completed.end()) {
                        canTake = false;
                        break;
                    }
                }

                if (canTake) {
                    sequence.push_back(c.getId());
                    completed.insert(c.getId());
                    cout << "   " << c.getId() << " - " << c.getName() << endl;
                    changed = true;
                }
            }

            if (changed) {
                cout << endl;
                semester++;
            }
        }

        cout << "    VERIFICATION BY INDUCTION "<<endl;
        cout << "Generated sequence: ";
        for (const auto& c : sequence) cout << c << "  ";
        cout << "END"<<endl<<endl;

        verifier.verifyPrerequisiteChain(sequence);
    }

    //MENU
    static void showMenu(const vector<Student>& students,
        const vector<Course>& courses) {
        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 3: INDUCTION & STRONG INDUCTION"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. Verify Prerequisite Chain (Mathematical Induction)" << endl;;
            cout << "  2. Check Student Progress (Strong Induction)"<<endl;
            cout << "  3. Generate Valid Course Sequence"<<endl;
            cout << "  4. Run Demonstration (Hard-coded Examples)"<<endl;
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
                verifyChainInteractive(courses);
                break;
            case 2:
                checkStudentProgress(students, courses);
                break;
            case 3:
                generateValidSequence(courses);
                break;
            case 4:
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
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     MODULE 3: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        InductionVerifier verifier;
        verifier.addPrerequisite("CS201", "CS101");
        verifier.addPrerequisite("CS301", "CS201");
        verifier.addPrerequisite("CS301", "Math201");
        verifier.addPrerequisite("Math201", "Math101");

        // Test regular induction
        cout << "    EXAMPLE 1: Valid Chain "<<endl;
        vector<string> chain = { "CS101", "Math101", "CS201", "Math201", "CS301" };
        verifier.verifyPrerequisiteChain(chain);

        // Test invalid chain
        cout << endl<<endl;
        cout << "     EXAMPLE 2: Invalid Chain"<<endl;
        vector<string> badChain = { "CS101", "CS301", "CS201" }; // CS301 before CS201!
        verifier.verifyPrerequisiteChain(badChain);

        // Test strong induction
        cout << endl << endl;
        cout << "     EXAMPLE 3: Strong Induction "<<endl;
        set<string> completed = { "CS101", "Math101", "CS201" };
        verifier.verifyWithStrongInduction("CS301", completed);
        cout << endl;
        cout << "[SUCCESS] Module 3 Complete!"<<endl;
    }
};

#endif