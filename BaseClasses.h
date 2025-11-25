#ifndef BASE_CLASSES_H
#define BASE_CLASSES_H

#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

// Base entity classes used in all other modules

class Student {
private:
    string id;
    string name;
    set<string> enrolledCourses;

public:
    Student(string id, string name) : id(id), name(name) {}

    string getId() const { return id; }
    string getName() const { return name; }
    set<string> getCourses() const { return enrolledCourses; }

    void enrollCourse(string courseId) { enrolledCourses.insert(courseId); }
    void dropCourse(string courseId) { enrolledCourses.erase(courseId); }
    bool isEnrolledIn(string courseId) const {
        return enrolledCourses.find(courseId) != enrolledCourses.end();
    }

    void display() const {
        cout << "Student: " << name << " (ID: " << id << ")"<<endl;
        cout << "Enrolled: ";
        for (const auto& c : enrolledCourses) cout << c << " ";
        cout << "\n";
    }
};

class Course {
private:
    string id;
    string name;
    set<string> prerequisites;
    string assignedFaculty;
    string assignedRoom;

public:
    Course(string id, string name) : id(id), name(name) {}

    string getId() const { return id; }
    string getName() const { return name; }
    set<string> getPrerequisites() const { return prerequisites; }
    string getFaculty() const { return assignedFaculty; }
    string getRoom() const { return assignedRoom; }

    void addPrerequisite(string prereqId) { prerequisites.insert(prereqId); }
    void assignFaculty(string facultyId) { assignedFaculty = facultyId; }
    void assignRoom(string roomId) { assignedRoom = roomId; }

    void display() const {
        cout << "Course: " << name << " (" << id << ")"<<endl;
        cout << "Prerequisites: ";
        for (const auto& p : prerequisites) cout << p << " ";
        cout << endl;
        cout << "Faculty: " << assignedFaculty << ", Room: " << assignedRoom << endl;
    }
};

class Faculty {
private:
    string id;
    string name;
    set<string> assignedCourses;

public:
    Faculty(string id, string name) : id(id), name(name) {}

    string getId() const { return id; }
    string getName() const { return name; }
    set<string> getCourses() const { return assignedCourses; }

    void assignCourse(string courseId) { assignedCourses.insert(courseId); }

    void display() const {
        cout << "Faculty: " << name << " (" << id << ")"<<endl;
        cout << "Courses: ";
        for (const auto& c : assignedCourses) cout << c << " ";
        cout << endl;
    }
};

class Room {
private:
    string id;
    string name;
    string type; // room types
    int capacity;
    string assignedCourse;
    string timeSlot;
    bool isAvailable;
    set<string> facilities; //facility type

public:
    Room(string id, string name, string type = "Classroom", int capacity = 30)
        : id(id), name(name), type(type), capacity(capacity),
        assignedCourse(""), timeSlot(""), isAvailable(true) {
    }

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    string getType() const { return type; }
    int getCapacity() const { return capacity; }
    string getAssignedCourse() const { return assignedCourse; }
    string getTimeSlot() const { return timeSlot; }
    bool getAvailability() const { return isAvailable; }
    set<string> getFacilities() const { return facilities; }

    // Setters
    void setType(string t) { type = t; }
    void setCapacity(int c) { capacity = c; }

    // Room assignment
    void assignCourse(string courseId, string time) {
        assignedCourse = courseId;
        timeSlot = time;
        isAvailable = false;
    }

    void clearAssignment() {
        assignedCourse = "";
        timeSlot = "";
        isAvailable = true;
    }

    // Facility management
    void addFacility(string facility) { facilities.insert(facility); }
    void removeFacility(string facility) { facilities.erase(facility); }
    bool hasFacility(string facility) const {
        return facilities.find(facility) != facilities.end();
    }

    // Check if room can accommodate
    bool canAccommodate(int numStudents) const {
        return numStudents <= capacity;
    }

    // Check availability at time
    bool isAvailableAt(string time) const {
        return isAvailable || (timeSlot != time);
    }

    void display() const {
        cout << "Room: " << name << " (" << id << ")"<<endl;
        cout << "Type: " << type << ", Capacity: " << capacity << endl;
        cout << "Status: " << (isAvailable ? "Available" : "Occupied") <<endl;
        if (!isAvailable) {
            cout << "Assigned to: " << assignedCourse << " at " << timeSlot << endl;
        }
        if (!facilities.empty()) {
            cout << "Facilities: ";
            for (const auto& f : facilities) cout << f << " ";
            cout << endl;
        }
    }
};

// Lab class specialized Room
class Lab : public Room {
private:
    int computerCount;
    string software; // Installed software

public:
    Lab(string id, string name, int capacity = 30, int computers = 30)
        : Room(id, name, "Lab", capacity), computerCount(computers), software("") {
        addFacility("Computers");
        addFacility("Network");
    }

    int getComputerCount() const { return computerCount; }
    string getSoftware() const { return software; }

    void installSoftware(string sw) { software = sw; }
    void setComputerCount(int count) { computerCount = count; }

    void display() const {
        Room::display();
        cout << "Computer Count: " << computerCount << endl;
        if (!software.empty()) {
            cout << "Installed Software: " << software << endl;
        }
    }
};

#endif