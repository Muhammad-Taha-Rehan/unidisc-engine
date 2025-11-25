#ifndef MODULE4_LOGIC_H
#define MODULE4_LOGIC_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>
#include "BaseClasses.h"
using namespace std;

//  Logic & Inference Engine
class LogicEngine {
private:
    map<string, bool> facts;

    struct Rule {
        string condition;
        string conclusion;
        string description;
        string originalRule;

        Rule(string c, string con, string d = "", string orig = "")
            : condition(c), conclusion(con), description(d), originalRule(orig) {
        }
    };

    vector<Rule> rules;

public:
    void addFact(const string& fact, bool value = true) {
        facts[fact] = value;
    }

    bool isFact(const string& fact) const {
        auto it = facts.find(fact);
        return it != facts.end() && it->second;
    }

    void addRule(const string& condition, const string& conclusion,
        const string& desc = "", const string& original = "") {
        rules.push_back(Rule(condition, conclusion, desc, original));
    }

    // RULE PARSING 
    bool parseRule(const string& ruleString) {
        cout << endl;
        cout << "[INFO] Parsing: \"" << ruleString << "\"\n";

        // Find "IF" and "THEN"
        size_t ifPos = ruleString.find("IF ");
        size_t thenPos = ruleString.find(" THEN ");

        if (ifPos == string::npos || thenPos == string::npos) {
            cout << "[ERROR] Invalid format! Use: IF <condition> THEN <conclusion>"<<endl;
            return false;
        }

        // Extract condition and conclusion
        string condition = ruleString.substr(ifPos + 3, thenPos - ifPos - 3);
        string conclusion = ruleString.substr(thenPos + 6);

        // Trim whitespace
        condition.erase(0, condition.find_first_not_of(" \t"));
        condition.erase(condition.find_last_not_of(" \t") + 1);
        conclusion.erase(0, conclusion.find_first_not_of(" \t"));
        conclusion.erase(conclusion.find_last_not_of(" \t") + 1);

        // Convert to internal format (replace spaces with underscores)
        replace(condition.begin(), condition.end(), ' ', '_');
        replace(conclusion.begin(), conclusion.end(), ' ', '_');

        addRule(condition, conclusion, "Parsed rule", ruleString);
        cout << "[SUCCESS] Parsed as: IF '" << condition << "' THEN '" << conclusion << "'\n";
        return true;
    }

    // Add Prerequisite Rule
    void addPrerequisiteRule(const vector<Course>& courses) {
        cout << endl;
        cout << "     ADD PREREQUISITE RULE"<<endl;
        cout << endl;

        if (courses.size() < 2) {
            cout << "[ERROR] Need at least 2 courses!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Courses:" << endl;
        for (size_t i = 0; i < courses.size(); i++) {
            cout << "  " << (i + 1) << ". " << courses[i].getId()
                << " - " << courses[i].getName() << endl;
        }
        cout << endl;
        cout << "Select course: " << endl;
        int courseIdx;
        cin >> courseIdx;

        if (courseIdx < 1 || courseIdx >(int)courses.size()) {
            cout << "[ERROR] Invalid selection!"<<endl;
            return;
        }

        cout << "Select prerequisite course: ";
        int prereqIdx;
        cin >> prereqIdx;

        if (prereqIdx < 1 || prereqIdx >(int)courses.size()) {
            cout << "[ERROR] Invalid selection!"<<endl;
            return;
        }

        const Course& course = courses[courseIdx - 1];
        const Course& prereq = courses[prereqIdx - 1];

        // Create rule
        string ruleStr = "IF student_enrolls_in_" + course.getId() +
            " THEN must_complete_" + prereq.getId();

        parseRule("IF student enrolls in " + course.getId() +
            " THEN must complete " + prereq.getId());

        cout << "[SUCCESS] Rule added!"<<endl;
    }

    // Add Faculty Assignment Rule
    void addFacultyAssignmentRule(const vector<Faculty>& faculties,
        const vector<Course>& courses,
        const vector<Room>& rooms) {
        cout << endl;
        cout << "     ADD FACULTY ASSIGNMENT RULE"<<endl;
        cout << endl;

        if (faculties.empty() || courses.empty() || rooms.empty()) {
            cout << "[ERROR] Need faculty, courses, and rooms data!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Faculty:"<<endl;
        for (size_t i = 0; i < faculties.size(); i++) {
            cout << "  " << (i + 1) << ". " << faculties[i].getName() << endl;
        }
        cout << endl;
        cout << "Select faculty: ";
        int facIdx;
        cin >> facIdx;

        if (facIdx < 1 || facIdx >(int)faculties.size()) {
            cout << "[ERROR] Invalid selection!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Courses:"<<endl;
        for (size_t i = 0; i < courses.size(); i++) {
            cout << "  " << (i + 1) << ". " << courses[i].getId() << endl;
        }
        cout << endl;
        cout << "Select course: ";
        int courseIdx;
        cin >> courseIdx;

        if (courseIdx < 1 || courseIdx >(int)courses.size()) {
            cout << "[ERROR] Invalid selection!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Rooms:"<<endl;
        for (size_t i = 0; i < rooms.size(); i++) {
            cout << "  " << (i + 1) << ". " << rooms[i].getName() << endl;
        }
        cout << endl;
        cout << "Select room that must be assigned: ";
        int roomIdx;
        cin >> roomIdx;

        if (roomIdx < 1 || roomIdx >(int)rooms.size()) {
            cout << "[ERROR] Invalid selection!" << endl;
            return;
        }

        const Faculty& faculty = faculties[facIdx - 1];
        const Course& course = courses[courseIdx - 1];
        const Room& room = rooms[roomIdx - 1];

        // Create rule
        string ruleText = "IF " + faculty.getName() + " teaches " + course.getId() +
            " THEN Lab must be " + room.getId();

        parseRule(ruleText);

        // Also add the fact
        string factName = faculty.getName() + "_teaches_" + course.getId();
        replace(factName.begin(), factName.end(), ' ', '_');
        replace(factName.begin(), factName.end(), '.', '_');
        addFact(factName);

        cout << "[SUCCESS] Rule and fact added!"<<endl;
    }

    // FORWARD CHAINING INFERENCE
    void infer() {
        bool changed = true;
        int iteration = 0;
        cout << endl;
        cout << "[INFO] Running inference engine..."<<endl;

        while (changed && iteration < 10) {
            changed = false;
            iteration++;

            for (const auto& rule : rules) {
                if (isFact(rule.condition) && !isFact(rule.conclusion)) {
                    addFact(rule.conclusion);
                    changed = true;
                    cout << "  Iteration " << iteration << ": '" << rule.condition
                        << "' - '" << rule.conclusion << "'\n";
                }
            }
        }

        if (iteration == 1) {
            cout << "[INFO] No new facts inferred."<<endl;
        }
        else {
            cout << "[SUCCESS] Inference complete after " << (iteration - 1) << " iterations"<<endl;
        }
    }

    // CONFLICT DETECTION
    vector<string> detectConflicts() {
        vector<string> conflicts;

        for (const auto& fact : facts) {
            if (!fact.second) continue;

            string negation = "NOT_" + fact.first;
            if (facts.find(negation) != facts.end() && facts[negation]) {
                conflicts.push_back("Both '" + fact.first + "' and '" + negation + "' are true");
            }
        }

        for (size_t i = 0; i < rules.size(); i++) {
            for (size_t j = i + 1; j < rules.size(); j++) {
                if (rules[i].condition == rules[j].condition &&
                    rules[i].conclusion != rules[j].conclusion) {
                    conflicts.push_back("Same condition leads to different conclusions");
                }
            }
        }

        return conflicts;
    }

    void displayFacts() const {
        cout << endl;
        cout << "[INFO] Known Facts:"<<endl;
        int count = 0;
        for (const auto& f : facts) {
            if (f.second) {
                cout << "  - " << f.first << endl;
                count++;
            }
        }
        if (count == 0) cout << "  (No facts established)"<<endl;
    }

    void displayRules() const {
        cout << endl;
        cout << "[INFO] Rules:"<<endl;
        for (size_t i = 0; i < rules.size(); i++) {
            cout << "  " << (i + 1) << ". ";
            if (!rules[i].originalRule.empty()) {
                cout << rules[i].originalRule;
            }
            else {
                cout << "IF " << rules[i].condition << " THEN " << rules[i].conclusion;
            }
            cout << endl;
        }
        if (rules.empty()) cout << "  (No rules defined)" << endl;
    }

    // MODULE MENU
    static void showMenu(const vector<Faculty>& faculties,
        const vector<Course>& courses,
        const vector<Room>& rooms) {
        LogicEngine engine;

        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 4: LOGIC & INFERENCE"<<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. Add Prerequisite Rule (from courses)"<<endl;
            cout << "  2. Add Faculty Assignment Rule"<<endl;
            cout << "  3. Add Custom Rule (manual input)"<<endl;
            cout << "  4. View All Rules"<<endl;
            cout << "  5. View All Facts"<<endl;
            cout << "  6. Run Inference Engine"<<endl;
            cout << "  7. Check for Conflicts"<<endl;
            cout << "  8. Run Demonstration"<<endl;
            cout << "  0. Back to Main Menu"<<endl<<endl;
            cout << "  Choice: ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 0) break;

            switch (choice) {
            case 1:
                engine.addPrerequisiteRule(courses);
                break;
            case 2:
                engine.addFacultyAssignmentRule(faculties, courses, rooms);
                break;
            case 3: {
                cout << endl;
                cout << "Enter rule (format: IF <condition> THEN <conclusion>):"<<endl;
                string rule;
                getline(cin, rule);
                engine.parseRule(rule);
                break;
            }
            case 4:
                engine.displayRules();
                break;
            case 5:
                engine.displayFacts();
                break;
            case 6:
                engine.infer();
                engine.displayFacts();
                break;
            case 7: {
                auto conflicts = engine.detectConflicts();
                cout << endl;
                cout << "[INFO] Checking conflicts..."<<endl;
                if (conflicts.empty()) {
                    cout << "[SUCCESS] No conflicts detected!"<<endl;
                }
                else {
                    cout << "[ERROR] Conflicts found:"<<endl;
                    for (const auto& c : conflicts) {
                        cout << "  - " << c << endl;
                    }
                }
                break;
            }
            case 8:
                demonstrate();
                break;
            default:
                cout << "[ERROR] Invalid choice!"<<endl;
            }
            cout << endl;
            cout << "Press Enter to continue...";
            cin.get();
        }
    }

    static void demonstrate() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     MODULE 4: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        LogicEngine engine;

        engine.parseRule("IF ProfX teaches CS101 THEN Lab must be LabA");
        engine.parseRule("IF Lab must be LabA THEN LabA reserved");
        engine.parseRule("IF CS101 offered THEN CS101 has schedule");

        engine.addFact("ProfX_teaches_CS101");
        engine.addFact("CS101_offered");

        engine.displayFacts();
        engine.displayRules();
        engine.infer();
        engine.displayFacts();

        auto conflicts = engine.detectConflicts();
        if (conflicts.empty()) {
            cout << endl;
            cout << "[SUCCESS] No conflicts detected!"<<endl;
        }
        cout << endl;
        cout << "[SUCCESS] Module 4 Complete!"<<endl;
    }
};

#endif