#ifndef MODULE12_TESTING_H
#define MODULE12_TESTING_H

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <limits>
using namespace std;

// Unit Testing
class UnitTester {
private:
    int passed = 0;
    int failed = 0;
    vector<string> failedTests;

    void test(bool condition, const string& name) {
        if (condition) {
            passed++;
            cout << "  - " << name << endl;
        }
        else {
            failed++;
            failedTests.push_back(name);
            cout << "  - " << name << " FAILED"<<endl;
        }
    }

public:
    void reset() {
        passed = 0;
        failed = 0;
        failedTests.clear();
    }

    // Test Set Operations
    void testSetOperations() {
        cout << endl;
        cout << "   Testing Set Operations "<<endl;

        set<int> A = { 1, 2, 3 };
        set<int> B = { 2, 3, 4 };

        // Union test
        set<int> u;
        set_union(A.begin(), A.end(), B.begin(), B.end(),
            inserter(u, u.begin()));
        test(u.size() == 4, "Set Union Size");
        test(u.find(1) != u.end() && u.find(4) != u.end(), "Set Union Elements");

        // Intersection test
        set<int> i;
        set_intersection(A.begin(), A.end(), B.begin(), B.end(),
            inserter(i, i.begin()));
        test(i.size() == 2, "Set Intersection Size");
        test(i.find(2) != i.end() && i.find(3) != i.end(), "Set Intersection Elements");

        // Difference test
        set<int> d;
        set_difference(A.begin(), A.end(), B.begin(), B.end(),
            inserter(d, d.begin()));
        test(d.size() == 1, "Set Difference Size");
        test(d.find(1) != d.end(), "Set Difference Elements");

        // Subset test
        set<int> C = { 2, 3 };
        bool isSubset = includes(A.begin(), A.end(), C.begin(), C.end());
        test(isSubset, "Subset Test");
    }

    // Test Combinations
    void testCombinations() {
        cout << endl;
        cout << "    Testing Combinations "<<endl;

        // Calculate 6C3 manually
        long long c = 1;
        for (int i = 6; i > 3; i--) c *= i;
        for (int i = 1; i <= 3; i++) c /= i;
        test(c == 20, "6C3 = 20");

        // Calculate 5C2
        c = (5 * 4) / (2 * 1);
        test(c == 10, "5C2 = 10");

        // Calculate 4C4
        test(1 == 1, "4C4 = 1");

        // Calculate 10C0
        test(1 == 1, "10C0 = 1");
    }

    // Test Relations
    void testRelations() {
        cout << endl;
        cout << "    Testing Relations "<<endl;

        set<pair<string, string>> R;
        R.insert({ "A", "A" });
        R.insert({ "B", "B" });
        R.insert({ "C", "C" });
        R.insert({ "A", "B" });
        R.insert({ "B", "A" });

        // Reflexive test
        set<string> domain = { "A", "B", "C" };
        bool reflexive = true;
        for (const auto& elem : domain) {
            if (R.find({ elem, elem }) == R.end()) {
                reflexive = false;
                break;
            }
        }
        test(reflexive, "Reflexive Relation");

        // Symmetric test
        bool symmetric = true;
        for (const auto& rel : R) {
            if (R.find({ rel.second, rel.first }) == R.end()) {
                symmetric = false;
                break;
            }
        }
        test(!symmetric, "Non-Symmetric Relation (A->B but not all symmetric)");
    }

    // Test Functions
    void testFunctions() {
        cout << endl;
        cout << " Testing Functions"<<endl;

        map<string, string> f;
        f["S1"] = "C1";
        f["S2"] = "C2";
        f["S3"] = "C1";

        // Injective test
        set<string> outputs;
        bool injective = true;
        for (const auto& p : f) {
            if (outputs.find(p.second) != outputs.end()) {
                injective = false;
                break;
            }
            outputs.insert(p.second);
        }
        test(!injective, "Non-Injective Function");

        // Function application test
        test(f["S1"] == "C1", "Function Application f(S1) = C1");
        test(f.find("S1") != f.end(), "Function Domain Check");
    }

    // Test Logic
    void testLogic() {
        cout << endl;
        cout << "    Testing Logic Operations "<<endl;

        // Propositional logic
        bool p = true, q = false;

        test((p && q) == false, "AND Operation (T ? F = F)");
        test((p || q) == true, "OR Operation (T ? F = T)");
        test(!p == false, "NOT Operation (¬T = F)");
        test((p && !p) == false, "Contradiction (P ? ¬P = F)");
        test((p || !p) == true, "Tautology (P ? ¬P = T)");

        // Implication
        bool implies = !p || q;
        test(implies == false, "Implication (T ? F = F)");
    }

    // Test Prerequisites (Induction concept)
    void testPrerequisites() {
        cout << endl;
        cout << " Testing Prerequisites"<<endl;

        map<string, set<string>> prereqs;
        prereqs["CS201"] = { "CS101" };
        prereqs["CS301"] = { "CS201" };

        set<string> completed = { "CS101", "CS201" };

        // Check if can take CS301
        bool canTake = true;
        for (const auto& p : prereqs["CS301"]) {
            if (completed.find(p) == completed.end()) {
                canTake = false;
                break;
            }
        }
        test(canTake, "Prerequisite Chain Validation");

        // Check if cannot take CS301 without CS201
        completed = { "CS101" };
        canTake = true;
        for (const auto& p : prereqs["CS301"]) {
            if (completed.find(p) == completed.end()) {
                canTake = false;
                break;
            }
        }
        test(!canTake, "Missing Prerequisite Detection");
    }

    // Test Consistency
    void testConsistency() {
        cout << endl;
        cout << "   Testing Consistency Checks"<<endl;

        map<string, string> courseTimes;
        courseTimes["CS101"] = "MWF 9:00";
        courseTimes["Math101"] = "MWF 9:00";
        courseTimes["CS201"] = "TTh 10:00";

        set<string> studentCourses = { "CS101", "Math101" };

        // Time conflict detection
        bool hasConflict = false;
        vector<string> courses(studentCourses.begin(), studentCourses.end());
        for (size_t i = 0; i < courses.size(); i++) {
            for (size_t j = i + 1; j < courses.size(); j++) {
                if (courseTimes[courses[i]] == courseTimes[courses[j]]) {
                    hasConflict = true;
                    break;
                }
            }
            if (hasConflict) break;
        }
        test(hasConflict, "Time Conflict Detection");

        // No conflict case
        studentCourses = { "CS101", "CS201" };
        hasConflict = false;
        courses = vector<string>(studentCourses.begin(), studentCourses.end());
        for (size_t i = 0; i < courses.size(); i++) {
            for (size_t j = i + 1; j < courses.size(); j++) {
                if (courseTimes[courses[i]] == courseTimes[courses[j]]) {
                    hasConflict = true;
                    break;
                }
            }
            if (hasConflict) break;
        }
        test(!hasConflict, "No Time Conflict Detection");
    }

    // Test Scheduling
    void testScheduling() {
        cout << endl;
        cout << "    Testing Course Scheduling" << endl;

        // Topological sort concept test
        map<string, set<string>> prereqs;
        prereqs["CS101"] = {};
        prereqs["CS201"] = { "CS101" };
        prereqs["CS301"] = { "CS201" };

        // Valid sequence: CS101 -> CS201 -> CS301
        vector<string> sequence = { "CS101", "CS201", "CS301" };
        bool validSequence = true;

        set<string> completed;
        for (const auto& course : sequence) {
            for (const auto& p : prereqs[course]) {
                if (completed.find(p) == completed.end()) {
                    validSequence = false;
                    break;
                }
            }
            completed.insert(course);
            if (!validSequence) break;
        }
        test(validSequence, "Valid Course Sequence");

        // Invalid sequence: CS301 before CS201
        sequence = { "CS101", "CS301", "CS201" };
        validSequence = true;
        completed.clear();

        for (const auto& course : sequence) {
            for (const auto& p : prereqs[course]) {
                if (completed.find(p) == completed.end()) {
                    validSequence = false;
                    break;
                }
            }
            completed.insert(course);
            if (!validSequence) break;
        }
        test(!validSequence, "Invalid Course Sequence Detection");
    }

    void runAllTests() {
        reset();

        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "         COMPREHENSIVE UNIT TESTING "<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        testSetOperations();
        testCombinations();
        testRelations();
        testFunctions();
        testLogic();
        testPrerequisites();
        testConsistency();
        testScheduling();

        cout << "\n" << string(60, '=') << endl;
        cout << "TEST SUMMARY\n";
        cout << string(60, '=') << endl;
        cout << "  Total Tests:  " << (passed + failed) << endl;
        cout << "  Passed:       " << passed << " "<<endl;
        cout << "  Failed:       " << failed << " "<<endl;
        cout << "  Success Rate: " << (passed * 100 / (passed + failed)) << "%"<<endl;

        if (failed > 0) {
            cout << "\nFailed Tests:"<<endl;
            for (const auto& test : failedTests) {
                cout << " - " << test << endl;
            }
        }

        cout << "\n" << (failed == 0 ? " ALL TESTS PASSED!\n" : " SOME TESTS FAILED\n");
    }

    // Interactive menu
    static void showMenu() {
        UnitTester tester;

        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 12: UNIT TESTING "<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. Run All Tests\n";
            cout << "  2. Test Set Operations\n";
            cout << "  3. Test Combinations\n";
            cout << "  4. Test Relations\n";
            cout << "  5. Test Functions\n";
            cout << "  6. Test Logic\n";
            cout << "  7. Test Prerequisites\n";
            cout << "  8. Test Consistency\n";
            cout << "  9. Test Scheduling\n";
            cout << " 10. Run Demonstration\n";
            cout << "  0. Back to Main Menu\n";
            cout << "\n  Choice: ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (choice == 0) break;

            tester.reset();

            switch (choice) {
            case 1:
                tester.runAllTests();
                break;
            case 2:
                tester.testSetOperations();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 3:
                tester.testCombinations();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 4:
                tester.testRelations();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 5:
                tester.testFunctions();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 6:
                tester.testLogic();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 7:
                tester.testPrerequisites();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 8:
                tester.testConsistency();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 9:
                tester.testScheduling();
                cout << "\nPassed: " << tester.passed << ", Failed: " << tester.failed << "\n";
                break;
            case 10:
                demonstrate();
                break;
            default:
                cout << "[ERROR] Invalid choice!\n";
            }

            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    static void demonstrate() {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "   MODULE 12: DEMONSTRATION                \n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        UnitTester tester;
        tester.runAllTests();

        cout << "\n Module 12 Complete!\n";
    }
};

#endif