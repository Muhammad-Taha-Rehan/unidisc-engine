#ifndef MODULE5_SETS_H
#define MODULE5_SETS_H

#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include "BaseClasses.h"
using namespace std;

// Set Operations
template <typename T>
class SetOperations {
public:
    static set<T> setUnion(const set<T>& A, const set<T>& B) {
        set<T> result = A;
        result.insert(B.begin(), B.end());
        return result;
    }

    static set<T> setIntersection(const set<T>& A, const set<T>& B) {
        set<T> result;
        set_intersection(A.begin(), A.end(), B.begin(), B.end(),
            inserter(result, result.begin()));
        return result;
    }

    static set<T> setDifference(const set<T>& A, const set<T>& B) {
        set<T> result;
        set_difference(A.begin(), A.end(), B.begin(), B.end(),
            inserter(result, result.begin()));
        return result;
    }

    static bool isSubset(const set<T>& A, const set<T>& B) {
        return includes(B.begin(), B.end(), A.begin(), A.end());
    }

    static vector<set<T>> powerSet(const set<T>& S) {
        vector<T> elements(S.begin(), S.end());
        int n = elements.size();
        int powerSetSize = 1 << n;

        vector<set<T>> result;
        for (int i = 0; i < powerSetSize; i++) {
            set<T> subset;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    subset.insert(elements[j]);
                }
            }
            result.push_back(subset);
        }
        return result;
    }

    static set<pair<T, T>> cartesianProduct(const set<T>& A, const set<T>& B) {
        set<pair<T, T>> result;
        for (const auto& a : A) {
            for (const auto& b : B) {
                result.insert({ a, b });
            }
        }
        return result;
    }

    static void displaySet(const set<T>& S, const string& name = "Set") {
        cout << name << ": { ";
        for (const auto& e : S) cout << e << " ";
        cout << "}"<<endl;
    }

    // View Students as Set
    static void viewStudentsAsSet(const vector<Student>& students) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     STUDENTS AS SET"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        set<string> studentSet;
        for (const auto& s : students) {
            studentSet.insert(s.getId());
        }
        cout << endl;
        cout << "[INFO] Student Set (by ID):"<<endl;
        cout << "{ ";
        for (const auto& id : studentSet) {
            cout << id << " ";
        }
        cout << "}"<<endl;
        cout << "Cardinality: |S| = " << studentSet.size() << endl;

        // Power set (only if small enough)
        if (studentSet.size() <= 4) {
            auto pset = powerSet(studentSet);
            cout << endl;
            cout << "[INFO] Power Set (2^" << studentSet.size() << " = "
                << pset.size() << " subsets):" << endl;
            for (size_t i = 0; i < pset.size(); i++) {
                cout << "  P" << i << ": { ";
                for (const auto& elem : pset[i]) cout << elem << " ";
                cout << "}"<<endl;
            }
        }
        else {
            cout << endl;
            cout << "[INFO] Power set too large to display (2^"
                << studentSet.size() << " = " << (1 << studentSet.size()) << " subsets)"<<endl;
        }
    }

    // Find Students in Multiple Courses
    static void findStudentsInCourses(const vector<Student>& students) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     STUDENTS IN MULTIPLE COURSES"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        if (students.empty()) {
            cout << "[ERROR] No students available!"<<endl;
            return;
        }

        // Get unique courses
        set<string> allCourses;
        for (const auto& s : students) {
            auto courses = s.getCourses();
            allCourses.insert(courses.begin(), courses.end());
        }

        if (allCourses.size() < 2) {
            cout << "[INFO] Need at least 2 different courses for intersection!"<<endl;
            return;
        }
        cout << endl;
        cout << "[INFO] Available Courses:" << endl;;
        vector<string> courseVec(allCourses.begin(), allCourses.end());
        for (size_t i = 0; i < courseVec.size(); i++) {
            cout << "  " << (i + 1) << ". " << courseVec[i] << endl;
        }
        cout << endl;
        cout << "Select first course: ";
        int c1;
        cin >> c1;
        cout << "Select second course: ";
        int c2;
        cin >> c2;

        if (c1 < 1 || c1 >(int)courseVec.size() ||
            c2 < 1 || c2 >(int)courseVec.size()) {
            cout << "[ERROR] Invalid selection!"<<endl;
            return;
        }

        string course1 = courseVec[c1 - 1];
        string course2 = courseVec[c2 - 1];

        // Build sets
        set<string> studentsInCourse1, studentsInCourse2;

        for (const auto& s : students) {
            if (s.isEnrolledIn(course1)) {
                studentsInCourse1.insert(s.getId());
            }
            if (s.isEnrolledIn(course2)) {
                studentsInCourse2.insert(s.getId());
            }
        }
        cout << endl;
        cout << "[SUCCESS] Results:"<<endl;
        displaySet(studentsInCourse1, "Students in " + course1);
        displaySet(studentsInCourse2, "Students in " + course2);

        auto intersection = setIntersection(studentsInCourse1, studentsInCourse2);
        displaySet(intersection, "Intersection (Both courses)");

        auto unionSet = setUnion(studentsInCourse1, studentsInCourse2);
        displaySet(unionSet, "Union (Either course)");

        auto diff = setDifference(studentsInCourse1, studentsInCourse2);
        displaySet(diff, "Difference (Only " + course1 + ")");
    }

    // INTERACTIVE: Set Operations on Entities
    static void performSetOperations(const vector<Student>& students,
        const vector<Course>& courses,
        const vector<Faculty>& faculties,
        const vector<Room>& rooms) {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "     SET OPERATIONS ON ENTITIES"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << "  1. Students Set" << endl;
        cout << "  2. Courses Set"<<endl;
        cout << "  3. Faculty Set"<<endl;
        cout << "  4. Rooms Set"<<endl;
        cout << "  5. Cartesian Product (Students * Courses)"<<endl<<endl;
        cout << "  Choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            set<string> S;
            for (const auto& s : students) S.insert(s.getId());
            displaySet(S, "Students");
            cout << "Cardinality: |S| = " << S.size() << endl;
            break;
        }
        case 2: {
            set<string> C;
            for (const auto& c : courses) C.insert(c.getId());
            displaySet(C, "Courses");
            cout << "Cardinality: |C| = " << C.size() << endl;
            break;
        }
        case 3: {
            set<string> F;
            for (const auto& f : faculties) F.insert(f.getId());
            displaySet(F, "Faculty");
            cout << "Cardinality: |F| = " << F.size() << endl;
            break;
        }
        case 4: {
            set<string> R;
            for (const auto& r : rooms) R.insert(r.getId());
            displaySet(R, "Rooms");
            cout << "Cardinality: |R| = " << R.size() << endl;
            break;
        }
        case 5: {
            set<string> S, C;
            for (const auto& s : students) S.insert(s.getId());
            for (const auto& c : courses) C.insert(c.getId());

            auto cartesian = cartesianProduct(S, C);
            cout << endl;
            cout << "[SUCCESS] Cartesian Product S * C:"<<endl;
            cout << "Size: |S * C| = " << cartesian.size()
                << " (= " << S.size() << " *" << C.size() << ")"<<endl<<endl;

            if (cartesian.size() <= 20) {
                cout << "Pairs:"<<endl;
                for (const auto& p : cartesian) {
                    cout << "  (" << p.first << ", " << p.second << ")"<<endl;
                }
            }
            else {
                cout << "First 10 pairs:"<<endl;
                int count = 0;
                for (const auto& p : cartesian) {
                    cout << "  (" << p.first << ", " << p.second << ")"<<endl;
                    if (++count >= 10) break;
                }
                cout << "  ... and " << (cartesian.size() - 10) << " more"<<endl;
            }
            break;
        }
        default:
            cout << "[ERROR] Invalid choice!"<<endl;
        }
    }

    // MODULE MENU
    static void showMenu(const vector<Student>& students,
        const vector<Course>& courses,
        const vector<Faculty>& faculties,
        const vector<Room>& rooms) {
        while (true) {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "     MODULE 5: SET OPERATIONS" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
            cout << "  1. View Students as Set"<<endl;
            cout << "  2. Find Students in Multiple Courses (Intersection)"<<endl;
            cout << "  3. Set Operations on All Entities"<<endl;
            cout << "  4. Run Demonstration (Hard-coded Examples)"<<endl;
            cout << "  0. Back to Main Menu"<<endl;
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
                viewStudentsAsSet(students);
                break;
            case 2:
                findStudentsInCourses(students);
                break;
            case 3:
                performSetOperations(students, courses, faculties, rooms);
                break;
            case 4:
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
        cout << "     MODULE 5: DEMONSTRATION"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        set<string> A = { "CS101", "CS201", "Math101" };
        set<string> B = { "CS201", "Math101", "Physics101" };

        displaySet(A, "Set A (Courses)");
        displaySet(B, "Set B (Courses)");

        auto u = setUnion(A, B);
        displaySet(u, "Union (A v B)");

        auto i = setIntersection(A, B);
        displaySet(i, "Intersection (A ^ B)");

        auto d = setDifference(A, B);
        displaySet(d, "Difference (A - B)");

        set<string> small = { "A", "B" };
        auto ps = powerSet(small);
        cout << endl;
        cout << "Power Set of {A, B} (2^2 = 4 subsets):"<<endl;
        for (size_t i = 0; i < ps.size(); i++) {
            cout << "  ";
            displaySet(ps[i], "P" + to_string(i));
        }
        cout << endl << endl;
        cout << "[SUCCESS] Module 5 Complete!"<<endl;
    }
};

#endif