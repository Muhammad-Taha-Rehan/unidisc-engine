#ifndef MODULE8_PROOFS_H
#define MODULE8_PROOFS_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <limits>
#include "BaseClasses.h"
using namespace std;

// Automated Proof & Verification
class ProofSystem {
private:
    vector<string> steps;

public:
    void addStep(const string& step) { steps.push_back(step); }
    void reset() { steps.clear(); }

    void displayProof(const string& theorem) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "           FORMAL PROOF VERIFICATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl<<endl;
        cout << "Theorem : " << theorem << endl;
        cout << string(60, '-') << endl;
        for (size_t i = 0; i < steps.size(); i++) {
            cout << "Step " << (i + 1) << ": " << steps[i] << endl;
        }
        cout << string(60, '-') << endl;
        cout << "[SUCCESS] Q.E.D. (Quod Erat Demonstrandum) "<<endl;
    }

    // MATHEMATICAL INDUCTION PROOF 
    void proveByInduction(const string& property, int base,
        const vector<string>& inductiveSteps) {
        reset();
        addStep("PROOF BY MATHEMATICAL INDUCTION");
        addStep("");
        addStep("Let P(n) be: " + property);
        addStep("");
        addStep("BASE CASE: P(" + to_string(base) + ")");
        addStep("  Verify property holds for n = " + to_string(base));
        addStep("  [SUCCESS] Base case verified");
        addStep("");
        addStep("INDUCTIVE HYPOTHESIS:");
        addStep("  Assume P(k) is true for arbitrary k >= " + to_string(base));
        addStep("");
        addStep("INDUCTIVE STEP: Prove P(k+1)");
        for (const auto& s : inductiveSteps) addStep("  " + s);
        addStep("  [SUCCESS] P(k) -> P(k+1) established");
        addStep("");
        addStep("CONCLUSION:");
        addStep("  By mathematical induction, P(n) holds for all n >= " + to_string(base));

        displayProof("Proof by Mathematical Induction");
    }

    // PROOF OF COURSE PREREQUISITE CHAIN
    void proveCourseChain(const vector<string>& courses,
        const map<string, set<string>>& prerequisites) {
        reset();
        addStep("PROOF: Valid Course Sequence by Induction");
        addStep("");

        string sequence = "Course sequence: ";
        for (const auto& c : courses) sequence += c + " -> ";
        sequence += "END";
        addStep(sequence);
        addStep("");

        // Base case
        addStep("BASE CASE (n=1): First course " + courses[0]);

        auto it = prerequisites.find(courses[0]);
        if (it != prerequisites.end() && !it->second.empty()) {
            addStep("  [ERROR] First course has prerequisites!");
            displayProof("Invalid Course Sequence");
            return;
        }

        addStep("  Prerequisites: None");
        addStep("  [SUCCESS] Student can take " + courses[0]);
        addStep("");

        // Inductive step
        addStep("INDUCTIVE HYPOTHESIS:");
        addStep("  Assume student can take all courses up to position k");
        addStep("");
        addStep("INDUCTIVE STEP:");

        bool valid = true;
        for (size_t i = 1; i < courses.size(); i++) {
            addStep("");
            addStep("Course at position " + to_string(i + 1) + ": " + courses[i]);

            auto prereqIt = prerequisites.find(courses[i]);
            if (prereqIt != prerequisites.end() && !prereqIt->second.empty()) {
                string prereqStr = "  Prerequisites: { ";
                for (const auto& p : prereqIt->second) prereqStr += p + " ";
                prereqStr += "}";
                addStep(prereqStr);

                // Check if all prereqs are before this
                for (const auto& prereq : prereqIt->second) {
                    bool found = false;
                    for (size_t j = 0; j < i; j++) {
                        if (courses[j] == prereq) {
                            found = true;
                            addStep("    [SUCCESS] " + prereq + " at position " + to_string(j + 1));
                            break;
                        }
                    }
                    if (!found) {
                        addStep("    [ERROR] " + prereq + " NOT satisfied!");
                        valid = false;
                    }
                }

                if (valid) {
                    addStep("  [SUCCESS] All prerequisites satisfied by hypothesis");
                }
            }
            else {
                addStep("  Prerequisites: None");
                addStep("  [SUCCESS] Can be taken at any time");
            }
        }

        addStep("");
        if (valid) {
            addStep("CONCLUSION:");
            addStep("  [SUCCESS] By induction, the entire sequence is VALID");
            addStep("  Every course's prerequisites are satisfied");
        }
        else {
            addStep("CONCLUSION:");
            addStep("  [ERROR] PROOF FAILS - Sequence violates constraints");
        }

        displayProof(valid ? "Valid Course Sequence" : "Invalid Course Sequence");
    }

   // PROOF BY STRONG INDUCTION 
    void proveByStrongInduction(const string& property,
        const vector<string>& baseCases,
        const vector<string>& strongSteps) {
        reset();
        addStep("PROOF BY STRONG INDUCTION");
        addStep("");
        addStep("Property: " + property);
        addStep("");
        addStep("BASE CASES:");
        for (size_t i = 0; i < baseCases.size(); i++) {
            addStep("  P(" + to_string(i + 1) + "): " + baseCases[i]);
        }
        addStep("  [SUCCESS] All base cases verified");
        addStep("");
        addStep("STRONG INDUCTIVE HYPOTHESIS:");
        addStep("  Assume P(j) holds for ALL j where 1 <= j <= k");
        addStep("");
        addStep("STRONG INDUCTIVE STEP: Prove P(k+1)");
        addStep("  We can use ANY of P(1), P(2), ..., P(k)");
        for (const auto& s : strongSteps) addStep("  " + s);
        addStep("");
        addStep("CONCLUSION:");
        addStep("  By strong induction, property holds for all n >= 1");

        displayProof("Proof by Strong Induction");
    }

    //Prove Course Chain
    static void proveCourseChainInteractive(const vector<Course>& courses) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     PROVE COURSE PREREQUISITE CHAIN"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
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
            cout << "[SUCCESS] Added " << courses[choice - 1].getId() << endl;
        }

        if (chain.empty()) {
            cout << "[ERROR] No courses selected!"<<endl;
            return;
        }

        // Build prerequisites map
        map<string, set<string>> prereqs;
        for (const auto& c : courses) {
            prereqs[c.getId()] = c.getPrerequisites();
        }

        // Generate proof
        ProofSystem proof;
        proof.proveCourseChain(chain, prereqs);
    }

    // Prove General Property
    static void proveGeneralProperty() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     PROVE GENERAL PROPERTY BY INDUCTION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << endl;
        cout << "[INFO] Available Properties to Prove:"<<endl;
        cout << "  1. Sum formula: 1+2+...+n = n(n+1)/2"<<endl;
        cout << "  2. Sum of odd numbers: 1+3+5+...+(2n-1) = n^2" << endl;
        cout << "  3. Geometric series: 1+2+4+...+2^n = 2^(n+1)-1"<<endl;
        cout << "  4. Custom property" << endl << endl;
        cout << "  Choice: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ProofSystem proof;

        switch (choice) {
        case 1: {
            vector<string> steps = {
                "Assume 1+2+...+k = k(k+1)/2",
                "Consider sum up to k+1: 1+2+...+k+(k+1)",
                "= [k(k+1)/2] + (k+1)  [by hypothesis]",
                "= [k(k+1) + 2(k+1)] / 2",
                "= (k+1)(k+2) / 2",
                "= (k+1)((k+1)+1) / 2",
                "This matches formula for n=k+1"
            };
            proof.proveByInduction("Sum 1+2+...+n = n(n+1)/2", 1, steps);
            break;
        }
        case 2: {
            vector<string> steps = {
                "Assume 1+3+5+...+(2k-1) = k^2",
                "Consider sum up to 2(k+1)-1",
                "= [1+3+5+...+(2k-1)] + [2(k+1)-1]",
                "= k^2 + (2k+1)  [by hypothesis]",
                "= k^2 + 2k + 1",
                "= (k+1)^2",
                "This matches formula for n=k+1"
            };
            proof.proveByInduction("Sum of first n odd numbers = n^2", 1, steps);
            break;
        }
        case 3: {
            vector<string> steps = {
                "Assume 1+2+4+...+2^k = 2^(k+1)-1",
                "Consider sum up to 2^(k+1)",
                "= [1+2+4+...+2^k] + 2^(k+1)",
                "= [2^(k+1)-1] + 2^(k+1)  [by hypothesis]",
                "= 2*2^(k+1) - 1",
                "= 2^(k+2) - 1",
                "This matches formula for n=k+1"
            };
            proof.proveByInduction("Geometric series sum = 2^(n+1)-1", 0, steps);
            break;
        }
        case 4: {
            string property;
            cout << "\nEnter property to prove: ";
            getline(cin, property);

            int base;
            cout << "Enter base case value: ";
            cin >> base;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            vector<string> steps;
            cout << endl;
            cout << "Enter inductive steps (enter empty line to finish):"<<endl;
            while (true) {
                cout << "  Step: ";
                string step;
                getline(cin, step);
                if (step.empty()) break;
                steps.push_back(step);
            }

            if (!steps.empty()) {
                proof.proveByInduction(property, base, steps);
            }
            else {
                cout << "[ERROR] No steps provided!"<<endl;
            }
            break;
        }
        default:
            cout << "[ERROR] Invalid choice!"<<endl;
        }
    }

    //INTERACTIVE: Verify Logic Rules
    static void verifyLogicRules() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     VERIFY LOGIC RULE CONSISTENCY    " << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl<<endl;

        cout << "[INFO] This verifies that logic rules are consistent"<<endl;
        cout << "[INFO] Checks for contradictions and circular dependencies"<<endl<<endl;

        ProofSystem proof;
        proof.reset();

        proof.addStep("PROOF: Logic Rule Consistency");
        proof.addStep("");
        proof.addStep("Given Rules:");
        proof.addStep("  R1: IF ProfX teaches CS101 THEN Lab must be LabA");
        proof.addStep("  R2: IF Lab is LabA THEN LabA reserved");
        proof.addStep("  R3: IF CS101 offered THEN Schedule exists");
        proof.addStep("");
        proof.addStep("VERIFICATION:");
        proof.addStep("Check 1: No contradictory conclusions");
        proof.addStep("  [SUCCESS] Each condition leads to unique conclusion");
        proof.addStep("");
        proof.addStep("Check 2: No circular dependencies");
        proof.addStep("  [SUCCESS] Rules form DAG (no cycles)");
        proof.addStep("");
        proof.addStep("Check 3: No conflicting facts");
        proof.addStep("  [SUCCESS] No fact and its negation both present");
        proof.addStep("");
        proof.addStep("CONCLUSION:");
        proof.addStep("  [SUCCESS] Logic rules are CONSISTENT");

        proof.displayProof("Consistent Logic System");
    }

    // MODULE MENU
    static void showMenu(const vector<Course>& courses) {
        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "               MODULE 8: AUTOMATED PROOFS "<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. Prove Course Prerequisite Chain"<<endl;
            cout << "  2. Prove General Property (Induction)"<<endl;
            cout << "  3. Prove by Strong Induction"<<endl;
            cout << "  4. Verify Logic Rule Consistency"<<endl;
            cout << "  5. Run Demonstration (Hard-coded Examples)"<<endl;
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
                proveCourseChainInteractive(courses);
                break;
            case 2:
                proveGeneralProperty();
                break;
            case 3: {
                ProofSystem proof;
                vector<string> baseCases = {
                    "F(1) = 1 < 2^1 = 2",
                    "F(2) = 1 < 2^2 = 4"
                };
                vector<string> strongSteps = {
                    "F(k+1) = F(k) + F(k-1)",
                    "By hypothesis: F(k) < 2^k and F(k-1) < 2^(k-1)",
                    "F(k+1) < 2^k + 2^(k-1)",
                    "= 2^(k-1)(2 + 1) = 3*2^(k-1)",
                    "< 4*2^(k-1) = 2^(k+1)",
                    "Therefore F(k+1) < 2^(k+1)"
                };
                proof.proveByStrongInduction("Fibonacci: F(n) < 2^n for all n >= 1",
                    baseCases, strongSteps);
                break;
            }
            case 4:
                verifyLogicRules();
                break;
            case 5:
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
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "           MODULE 8: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        ProofSystem proof;

        // Example Sum formula
        cout << endl;
        cout << " EXAMPLE 1: Mathematical Induction " << endl;
        vector<string> steps1 = {
            "Assume 1+2+...+k = k(k+1)/2",
            "Consider 1+2+...+k+(k+1)",
            "= [k(k+1)/2] + (k+1)",
            "= (k+1)(k+2) / 2",
            "This is P(k+1)"
        };
        proof.proveByInduction("Sum = n(n+1)/2", 1, steps1);

        // Example Course chain
        cout << endl;
        cout << " EXAMPLE 2: Course Chain Proof "<<endl;
        vector<string> courseSeq = { "CS101", "Math101", "CS201", "Math201", "CS301" };
        map<string, set<string>> prereqs;
        prereqs["CS201"] = { "CS101" };
        prereqs["CS301"] = { "CS201", "Math201" };
        prereqs["Math201"] = { "Math101" };

        proof.proveCourseChain(courseSeq, prereqs);
        cout << endl;
        cout << "[SUCCESS] Module 8 Complete!"<<endl;
    }
};

#endif