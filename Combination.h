#ifndef MODULE2_COMBINATIONS_H
#define MODULE2_COMBINATIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "BaseClasses.h"
using namespace std;

// MODULE 2 Student Group Combination Module
class StudentCombinations {
private:
    static long long factorial(int n) {
        if (n <= 1) return 1;
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

public:
    // Calculate nCr
    static long long nCr(int n, int r) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;
        return factorial(n) / (factorial(r) * factorial(n - r));
    }

    // Calculate nPr 
    static long long nPr(int n, int r) {
        if (r > n) return 0;
        return factorial(n) / factorial(n - r);
    }

    // Generate all combinations
    static vector<vector<string>> generateCombinations(
        const vector<string>& students, int r) {

        vector<vector<string>> result;
        int n = students.size();
        vector<int> indices(r);

        for (int i = 0; i < r; i++) {
            indices[i] = i;
        }

        while (true) {
            vector<string> combo;
            for (int i = 0; i < r; i++) {
                combo.push_back(students[indices[i]]);
            }
            result.push_back(combo);

            int i = r - 1;
            while (i >= 0 && indices[i] == n - r + i) {
                i--;
            }

            if (i < 0) break;

            indices[i]++;
            for (int j = i + 1; j < r; j++) {
                indices[j] = indices[j - 1] + 1;
            }
        }

        return result;
    }

    // Assign to Project Groups 
    static void assignProjectGroupsInteractive(const vector<Student>& students) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     ASSIGN STUDENTS TO PROJECT GROUPS            "<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (students.empty()) {
            cout << "[ERROR] No students available!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Students (" << students.size() << "):"<<endl;
        for (size_t i = 0; i < students.size(); i++) {
            cout << "  " << (i + 1) << ". " << students[i].getName()
                << " (" << students[i].getId() << ")"<<endl;
        }

        int groupSize;
        cout << endl;
        cout << "Enter group size (2-" << students.size() << "): ";
        cin >> groupSize;

        if (groupSize < 2 || groupSize >(int)students.size()) {
            cout << "[ERROR] Invalid group size!"<<endl;
            return;
        }

        long long totalGroups = nCr(students.size(), groupSize);
        cout << endl;
        cout << "[SUCCESS] Possible groups: " << totalGroups << endl;

        vector<string> studentNames;
        for (const auto& s : students) {
            studentNames.push_back(s.getName());
        }

        auto combinations = generateCombinations(studentNames, groupSize);
        cout << endl;
        cout << "[INFO] Showing first 10 groups:" << endl;
        for (size_t i = 0; i < min(size_t(10), combinations.size()); i++) {
            cout << "  Group " << (i + 1) << ": ";
            for (const auto& name : combinations[i]) {
                cout << name << ", ";
            }
            cout << endl;
        }

        if (combinations.size() > 10) {
            cout << "  ... and " << (combinations.size() - 10) << " more groups"<<endl;
        }
    }

    // INTERACTIVE: Assign to Lab Sessions
    static void assignLabSessionsInteractive(const vector<Student>& students,
        const vector<Lab>& labs) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "       ASSIGN STUDENTS TO LAB SESSIONS"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (students.empty()) {
            cout << "[ERROR] No students available!"<<endl;
            return;
        }

        if (labs.empty()) {
            cout << "[ERROR] No labs available!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Labs:" << endl;
        for (size_t i = 0; i < labs.size(); i++) {
            cout << "  " << (i + 1) << ". " << labs[i].getName()
                << " (Capacity: " << labs[i].getCapacity()
                << ", Computers: " << labs[i].getComputerCount() << ")"<<endl;
        }
        cout << endl;
        cout << "Select lab (1-" << labs.size() << "): ";
        int labChoice;
        cin >> labChoice;

        if (labChoice < 1 || labChoice >(int)labs.size()) {
            cout << "[ERROR] Invalid lab selection!" << endl;
            return;
        }

        const Lab& selectedLab = labs[labChoice - 1];
        int capacity = selectedLab.getCapacity();
        cout << endl;
        cout << "[SUCCESS] Assigning " << students.size()
            << " students to " << selectedLab.getName() << endl;

        int sessionsNeeded = (students.size() + capacity - 1) / capacity;
        cout << "[INFO] Sessions needed: " << sessionsNeeded << endl<<endl;

        int session = 1;
        for (size_t i = 0; i < students.size(); i += capacity) {
            cout << "Lab Session " << session << ":"<<endl;
            for (size_t j = i; j < min(i + capacity, students.size()); j++) {
                cout << "  - " << students[j].getName()
                    << " (" << students[j].getId() << ")"<<endl;
            }
            cout << endl;
            session++;
        }
    }

    // Assign to Electives
    static void assignElectivesInteractive(const vector<Student>& students,
        const vector<Course>& electives) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     ASSIGN STUDENTS TO ELECTIVES"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (students.empty()) {
            cout << "[ERROR] No students available!"<<endl;
            return;
        }

        if (electives.empty()) {
            cout << "[ERROR] No elective courses available!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Electives:" << endl;
        for (size_t i = 0; i < electives.size(); i++) {
            cout << "  " << (i + 1) << ". " << electives[i].getName()
                << " (" << electives[i].getId() << ")"<<endl;
        }

        int maxPerElective;
        cout << endl;
        cout << "Enter max students per elective: ";
        cin >> maxPerElective;

        if (maxPerElective < 1) {
            cout << "[ERROR] Invalid number!" << endl;
            return;
        }
        cout << endl;
        cout << "[SUCCESS] Distribution:"<<endl;

        size_t electiveIdx = 0;
        int count = 0;

        for (size_t i = 0; i < students.size(); i++) {
            if (count == 0) {
                cout << endl << electives[electiveIdx].getName() << ":"<<endl;
            }

            cout << "  - " << students[i].getName()
                << " (" << students[i].getId() << ")"<<endl;
            count++;

            if (count >= maxPerElective) {
                electiveIdx = (electiveIdx + 1) % electives.size();
                count = 0;
            }
        }
    }

    // CALCULATE COMBINATIONS
    static void calculateCombinations() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     COMBINATION CALCULATOR"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        int n, r;
        cout << endl;
        cout << "Enter n (total items): ";
        cin >> n;
        cout << "Enter r (items to choose): ";
        cin >> r;

        if (n < 0 || r < 0) {
            cout << "[ERROR] Values must be non-negative!"<<endl;
            return;
        }
        cout << endl;
        cout << "[RESULTS]"<<endl;
        cout << "  " << n << "C" << r << " (Combinations) = " << nCr(n, r) << endl;
        cout << "  " << n << "P" << r << " (Permutations) = " << nPr(n, r) << endl;
        cout << endl;
        cout << "[INFO] Meaning:"<<endl;
        cout << "  - " << nCr(n, r) << " ways to choose " << r
            << " items from " << n << " (order doesn't matter)"<<endl;
        cout << "  - " << nPr(n, r) << " ways to arrange " << r
            << " items from " << n << " (order matters)"<<endl;
    }

    // MODULE MENU
    static void showMenu(const vector<Student>& students,
        const vector<Course>& courses,
        const vector<Lab>& labs) {
        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 2: STUDENT COMBINATIONS"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. Assign Students to Project Groups"<<endl;
            cout << "  2. Assign Students to Lab Sessions"<<endl;
            cout << "  3. Assign Students to Electives"<<endl;
            cout << "  4. Calculate Combinations (nCr, nPr)"<<endl;
            cout << "  5. Run Demonstration (Hard-coded Examples)"<<endl;
            cout << "  0. Back to Main Menu"<<endl;
            cout << endl;
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
                assignProjectGroupsInteractive(students);
                break;
            case 2: {
                // Convert Room to Lab if needed
                vector<Lab> labList;
                for (const auto& lab : labs) {
                    labList.push_back(lab);
                }
                if (labList.empty()) {
                    cout << "[INFO] No labs defined. Using sample data."<<endl;
                    labList.push_back(Lab("L1", "Lab 1", 30, 30));
                    labList.push_back(Lab("L2", "Lab 2", 25, 25));
                }
                assignLabSessionsInteractive(students, labList);
                break;
            }
            case 3: {
                // Filter elective courses
                vector<Course> electives;
                for (const auto& c : courses) {
                    if (c.getId().find("ELECT") != string::npos ||
                        c.getName().find("Elective") != string::npos) {
                        electives.push_back(c);
                    }
                }
                if (electives.empty()) {
                    cout << "[INFO] No electives defined. Using sample courses."<<endl;
                    electives.push_back(Course("ELECT1", "Web Development"));
                    electives.push_back(Course("ELECT2", "Mobile Apps"));
                    electives.push_back(Course("ELECT3", "AI & ML"));
                }
                assignElectivesInteractive(students, electives);
                break;
            }
            case 4:
                calculateCombinations();
                break;
            case 5:
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

    // DEMONSTRATION 
    static void demonstrate() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     MODULE 2: DEMONSTRATION" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        vector<string> students = { "Ali", "Babar", "Chand", "Danish", "Eshal", "Faris" };
        cout << endl;
        cout << "[SUCCESS] Combination Calculations:" << endl;
        cout << "  6C3 = " << nCr(6, 3) << " (ways to form groups of 3)"<<endl;
        cout << "  6C2 = " << nCr(6, 2) << " (ways to form pairs)"<<endl;
        cout << "  6P3 = " << nPr(6, 3) << " (ordered arrangements of 3)"<<endl;
        cout << endl;
        cout << "     Project Group Assignment "<<endl;
        cout << "Students: ";
        for (const auto& s : students) cout << s << ", ";
        cout << endl;
        cout << "Group size: 3"<<endl;
        cout << "Total possible groups: " << nCr(6, 3) << endl<<endl;

        auto combinations = generateCombinations(students, 3);
        cout << "First 5 groups:"<<endl;
        for (size_t i = 0; i < 5; i++) {
            cout << "  Group " << (i + 1) << ": ";
            for (const auto& name : combinations[i]) {
                cout << name << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "[SUCCESS] Module 2 Complete!" << endl;
    }
};

#endif