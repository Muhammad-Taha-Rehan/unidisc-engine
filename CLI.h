#ifndef MODULE11_CLI_H
#define MODULE11_CLI_H

#include <iostream>
#include <limits>
#include <string>
using namespace std;

// CLI Interface
class CLI {
public:
    static void displayMainMenu() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "          UNIDISC ENGINE - FAST NUCES" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl << endl;
        cout << "  [CORE MODULES]"<<endl;
        cout << "  1.  Module 1: Course Scheduling"<<endl;
        cout << "  2.  Module 2: Student Combinations"<<endl;
        cout << "  3.  Module 3: Induction Verification"<<endl;
        cout << "  4.  Module 4: Logic & Inference"<<endl;
        cout << "  5.  Module 5: Set Operations"<<endl;
        cout << "  6.  Module 6: Relations"<<endl;
        cout << "  7.  Module 7: Functions"<<endl;
        cout << "  8.  Module 8: Automated Proofs"<<endl;
        cout << "  9.  Module 9: Consistency Checker"<<endl;
        cout << " 10.  Module 10: Efficiency Benchmarking" << endl << endl;
        cout << "  [SYSTEM]"<<endl;
        cout << " 11.  Module 12: Unit Testing"<<endl;
        cout << " 12.  Run ALL Modules"<<endl;
        cout << " 13.  Entity Management"<<endl;
        cout << " 14.  View System Data"<<endl<<endl;
        cout << " 0.  Exit"<<endl;
        cout << endl;
        cout << "  Choice: ";
    }

    static void displayWelcome() {
        cout << endl ;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "       WELCOME TO UNIDISC ENGINE"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl << endl ;
    }

    static void pause() {
        cout << endl;
        cout << "  Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void displayModuleHeader(const string& moduleName, int marks) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "  " << moduleName;
        int spaces = 50 - moduleName.length();
        for (int i = 0; i < spaces; i++) cout << " ";
        cout << endl;
        cout << "  Marks: " << marks;
        spaces = 43 - to_string(marks).length();
        for (int i = 0; i < spaces; i++) cout << " ";
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    static void displaySuccess(const string& message) {
        cout << "\n [SUCCESS] " << message << "\n";
    }

    static void displayError(const string& message) {
        cout << "\n [ERROR] " << message << "\n";
    }

    static void displayInfo(const string& message) {
        cout << "\n [INFO] " << message << "\n";
    }

    static void displayWarning(const string& message) {
        cout << "\n [WARNING] " << message << "\n";
    }

    static void displayProgress(const string& message) {
        cout << "\n " << message << "...\n";
    }

    static void displaySeparator() {
        cout << "\n" << string(60, '=') << "\n";
    }

    static void displaySubMenu(const string& title, const vector<string>& options) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "  " << title;
        int spaces = 50 - title.length();
        for (int i = 0; i < spaces; i++) cout << " ";
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;;

        for (size_t i = 0; i < options.size(); i++) {
            cout << "  " << (i + 1) << ". " << options[i] << "\n";
        }
        cout << "  0. Back\n";
        cout << "\n  Choice: ";
    }

    static int getIntInput(const string& prompt, int min, int max) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= min && value <= max) {
                return value;
            }
            cout << "[ERROR] Please enter a number between " << min << " and " << max << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    static string getStringInput(const string& prompt) {
        string value;
        cout << prompt;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, value);
        return value;
    }

    static bool confirmAction(const string& message) {
        cout << "\n" << message << " (y/n): ";
        char response;
        cin >> response;
        return (response == 'y' || response == 'Y');
    }

    static void displayStatistics(int total, int completed, int remaining) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "              SYSTEM STATISTICS                     "<< endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "  Total Marks:      " << total << "\n";
        cout << "  Completed:        " << completed << "\n";
        cout << "  Remaining:        " << remaining << "\n";
        cout << "  Progress:         ";

        int percentage = (completed * 100) / total;
        int bars = percentage / 5;
        cout << "[";
        for (int i = 0; i < 20; i++) {
            if (i < bars) cout << "| |";
            else cout << " ";
        }
        cout << "] " << percentage << "%\n";
    }

    static void demonstrate() {
        clearScreen();
        displayModuleHeader("MODULE 11: CLI INTERFACE", 10);

        displayInfo("Interactive Command-Line Interface System");
        displaySeparator();

        cout << "\n[FEATURES IMPLEMENTED]\n";
        displaySuccess("Main menu navigation");
        displaySuccess("Sub-menu system for all modules");
        displaySuccess("Input validation and error handling");
        displaySuccess("User-friendly prompts and messages");
        displaySuccess("Progress indicators and statistics");
        displaySuccess("Formatted output with Unicode symbols");

        displaySeparator();

        cout << "\n[MENU STRUCTURE]\n";
        cout << "  Main Menu\n";
        cout << "    -> 12 Module Menus\n";
        cout << "        -> Interactive Functions\n";
        cout << "        -> Demonstrations\n";
        cout << "        -> Back to Main\n";
        cout << "    -> Entity Management\n";
        cout << "    -> System Data View\n";
        cout << "    -> Exit\n";

        displaySeparator();
        displaySuccess("Module 11 Complete!");
    }
};

#endif