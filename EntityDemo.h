#ifndef ENTITY_DEMO_H
#define ENTITY_DEMO_H

#include "BaseClasses.h"
#include <iostream>
#include <vector>

// Demonstration of all entity classes
class EntityDemo {
public:
    static void demonstrateAllEntities() {
        cout << endl << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "        ENTITY CLASSES DEMONSTRATION" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;

        // Example Student Entity
        cout << "~~~STUDENT ENTITY~~~ " << endl;
        Student ali("S001", "Ali ");
        ali.enrollCourse("CS101");
        ali.enrollCourse("Math101");
        ali.enrollCourse("Physics101");
        ali.display();
        cout << endl;
        cout << "Enrolling in CS201..." << endl;
        ali.enrollCourse("CS201");
        ali.display();
        cout << endl;
        cout << "Dropping Physics101..." << endl;
        ali.dropCourse("Physics101");
        ali.display();

        // Example Course Entity
        cout << endl;
        cout << "~~~COURSE ENTITY~~~ " << endl;
        Course cs201("CS201", "Data Structures");
        cs201.addPrerequisite("CS101");
        cs201.assignFaculty("Dr. Sheroz");
        cs201.assignRoom("Room301");
        cs201.display();

        Course cs301("CS301", "Algorithms");
        cs301.addPrerequisite("CS201");
        cs301.addPrerequisite("Math201");
        cs301.assignFaculty("Dr. Junaid");
        cs301.assignRoom("Lab101");
        cs301.display();

        // Example Faculty Entity
        cout << endl;
        cout << "~~~FACULTY ENTITY~~~ " << endl;;
        Faculty drSheroz("F001", "Dr. Sheroz");
        drSheroz.assignCourse("CS101");
        drSheroz.assignCourse("CS201");
        drSheroz.assignCourse("CS301");
        drSheroz.display();

        Faculty drEshan("F002", "Dr. Eshan");
        drEshan.assignCourse("Math101");
        drEshan.assignCourse("Math201");
        drEshan.display();

        // Example Room Entity
        cout << endl;
        cout << "~~~ROOM ENTITY~~~" << endl;
        Room room301("R301", "Room 301", "Classroom", 50);
        room301.addFacility("Projector");
        room301.addFacility("Whiteboard");
        room301.addFacility("Air Conditioning");
        room301.display();
        cout << endl;
        cout << "Assigning CS201 to Room 301..." << endl;
        room301.assignCourse("CS201", "MWF 10:00-11:00");
        room301.display();
        cout << endl;
        cout << "Checking availability:" << endl;
        cout << "  Available at MWF 10:00? "
            << (room301.isAvailableAt("MWF 10:00-11:00") ? "Yes" : "No") << endl;
        cout << "  Available at TTh 14:00? "
            << (room301.isAvailableAt("TTh 14:00-15:30") ? "Yes" : "No") << endl;
        cout << endl;
        cout << "Clearing assignment..." << endl;
        room301.clearAssignment();
        room301.display();

        // Example Lab Entity (Inherits from Room)
        cout << "~~~LAB ENTITY (Specialized Room)~~~ " << endl;
        Lab lab101("L101", "Computer Lab 1", 40, 40);
        lab101.installSoftware("Visual Studio, Python, MATLAB");
        lab101.display();
        cout << endl;
        cout << "Assigning CS301 lab session..." << endl;
        lab101.assignCourse("CS301-Lab", "TTh 14:00-15:30");
        lab101.display();

        // Example Practical Scenario - Complete Course Setup
        cout << endl;
        cout << "    PRACTICAL SCENARIO: Complete Course Setup " << endl;
        cout << endl;
        cout << "1. Creating CS101 Course:" << endl;
        Course cs101("CS101", "Introduction to Programming");
        cs101.assignFaculty("Dr. Sheroz");
        cs101.assignRoom("Room 301");
        cs101.display();
        cout << endl;
        cout << "2. Setting up Room:" << endl;
        Room room301_2("R301", "Room 301", "Classroom", 60);
        room301_2.addFacility("Projector");
        room301_2.assignCourse("CS101", "MWF 09:00-10:00");
        room301_2.display();
        cout << endl;
        cout << "3. Assigning Faculty:" << endl;
        Faculty drSmith_2("F001", "Dr. Sheroz");
        drSmith_2.assignCourse("CS101");
        drSmith_2.display();
        cout << endl;
        cout << "4. Enrolling Students:" << endl;
        Student student1("S001", "Ali");
        Student student2("S002", "Babar");
        Student student3("S003", "Chand");

        student1.enrollCourse("CS101");
        student2.enrollCourse("CS101");
        student3.enrollCourse("CS101");

        student1.display();
        student2.display();
        student3.display();

        // Example Room Capacity Check
        cout << endl;
        cout << "~~~ROOM CAPACITY VALIDATION~~~ " << endl;
        Room smallRoom("R201", "Room 201", "Classroom", 30);
        smallRoom.display();
        cout << endl;
        cout << "Capacity checks:" << endl;
        cout << "  Can accommodate 25 students? "
            << (smallRoom.canAccommodate(25) ? "Yes ?" : "No ?") << endl;
        cout << "  Can accommodate 35 students? "
            << (smallRoom.canAccommodate(35) ? "Yes ?" : "No ?") << endl;

        // Example Lab Software Requirements
        cout << endl;
        cout << "~~~LAB SOFTWARE MANAGEMENT~~~ " << endl;
        Lab aiLab("L201", "AI Research Lab", 25, 25);
        aiLab.installSoftware("TensorFlow, PyTorch, Jupyter, CUDA Toolkit");
        aiLab.addFacility("GPU Workstations");
        aiLab.addFacility("High-Speed Network");
        aiLab.display();
        cout << endl;
        cout << "Checking facilities:" << endl;
        cout << "  Has GPU Workstations? "
            << (aiLab.hasFacility("GPU Workstations") ? "Yes ?" : "No ?") << endl;
        cout << "  Has Computers? "
            << (aiLab.hasFacility("Computers") ? "Yes ?" : "No ?") << endl;
        cout << endl;
        cout << " All Entity Classes Demonstrated!" << endl;
    }
};

#endif