# 🎓 UNIDISC ENGINE - University Discrete Structures Management System

> A comprehensive computational framework that models FAST University's operations using discrete mathematics structures, implementing course scheduling, student enrollment, faculty assignments, and resource management with formal verification.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Modules](#project-modules)
- [System Architecture](#system-architecture)
- [Installation](#installation)
- [Usage](#usage)
- [Module Details](#module-details)
- [Screenshots](#screenshots)
- [Testing](#testing)
- [Contributing](#contributing)
- [Team](#team)
- [License](#license)

---

## 🌟 Overview

**UNIDISC ENGINE** is an advanced academic management system that leverages discrete mathematics concepts to solve real-world university operational challenges. The project demonstrates the practical application of:

- **Mathematical Induction** for prerequisite chain verification
- **Logic & Inference** for rule enforcement
- **Set Theory** for entity relationships
- **Relations & Functions** for assignment mappings
- **Graph Theory** for course scheduling
- **Combinatorics** for student grouping

### 🎯 Project Goals

1. Create a high-level computational framework for university operations
2. Enforce complex rules and dependencies using discrete structures
3. Verify correctness through automated proofs and consistency checks
4. Optimize performance for large-scale academic datasets
5. Provide an intuitive CLI for system interaction

---

## ✨ Features

### Core Capabilities

- ✅ **Intelligent Course Scheduling** - Topological sorting with prerequisite validation
- ✅ **Student Grouping** - Combinatorial analysis for project teams and lab sessions
- ✅ **Prerequisite Verification** - Mathematical induction proofs for course chains
- ✅ **Logic-Based Rule Engine** - Forward chaining inference with conflict detection
- ✅ **Set Operations** - Union, intersection, difference, power sets for data analysis
- ✅ **Relationship Modeling** - Reflexive, symmetric, transitive relation checks
- ✅ **Function Mapping** - Injective, surjective, bijective assignment validation
- ✅ **Automated Proof Generation** - Step-by-step formal verification
- ✅ **Consistency Checking** - Multi-dimensional conflict detection
- ✅ **Performance Optimization** - Memoization, bitsets, algorithm benchmarking

### System Features

- 🎨 **Interactive CLI** - User-friendly menu-driven interface
- 🧪 **Comprehensive Testing** - 50+ unit tests covering all modules
- 📊 **Real-time Analytics** - Entity statistics and relationship visualization
- 🔧 **Entity Management** - CRUD operations for students, courses, faculty, rooms
- 📈 **Scalability** - Optimized for handling large university datasets

---

## 📦 Project Modules

| Module | Description | Status |
|--------|-------------|--------|
| **Module 1** | Course & Scheduling (Topological Sort) | ✅ Complete |
| **Module 2** | Student Combinations (nCr, nPr) | ✅ Complete |
| **Module 3** | Induction & Strong Induction | ✅ Complete |
| **Module 4** | Logic & Inference Engine | ✅ Complete |
| **Module 5** | Set Operations | ✅ Complete |
| **Module 6** | Relations (Equivalence, Partial Orders) | ✅ Complete |
| **Module 7** | Functions (Composition, Inverse) | ✅ Complete |
| **Module 8** | Automated Proof & Verification | ✅ Complete |
| **Module 9** | Consistency Checker | ✅ Complete |
| **Module 10** | Algorithmic Efficiency | ✅ Complete |
| **Module 11** | CLI Interface | ✅ Complete |
| **Module 12** | Unit Testing | ✅ Complete |

---

## 🏗️ System Architecture

```
UNIDISC ENGINE
│
├── 📁 Core Entities
│   ├── Student (ID, Name, Enrolled Courses)
│   ├── Course (ID, Name, Prerequisites, Faculty, Room)
│   ├── Faculty (ID, Name, Assigned Courses)
│   └── Room/Lab (ID, Type, Capacity, Facilities)
│
├── 📁 Discrete Structure Modules
│   ├── Scheduling (Graph Theory, Topological Sort)
│   ├── Combinations (Permutations, Counting)
│   ├── Induction (Mathematical Proofs)
│   ├── Logic (Inference Rules, Forward Chaining)
│   ├── Sets (Union, Intersection, Power Sets)
│   ├── Relations (Properties, Composition)
│   ├── Functions (Mappings, Properties)
│   └── Proofs (Automated Verification)
│
├── 📁 System Components
│   ├── Consistency Checker (Conflict Detection)
│   ├── Efficiency Optimizer (Memoization, Bitsets)
│   ├── CLI Interface (Menu System)
│   └── Unit Testing (Validation Suite)
│
└── 📁 Data Store
    └── UniversityDataStore (Centralized Data Management)
```

---

## 🚀 Installation

### Prerequisites

- **C++ Compiler** (GCC 7.0+ or MSVC 2017+)
- **C++17 Standard** support
- **Operating System**: Windows, Linux, or macOS

### Build Instructions

#### Option 1: Using g++ (Linux/macOS)

```bash
# Clone the repository
git clone https://github.com/Muhammad-Taha-Rehan/unidisc-engine.git
cd unidisc-engine

# Compile
g++ -std=c++17 -o unidisc Main.cpp

# Run
./unidisc
```

#### Option 2: Using MSVC (Windows)

```cmd
# Clone the repository
git clone https://github.com/Muhammad-Taha-Rehan/unidisc-engine.git
cd unidisc-engine

# Compile
cl /EHsc /std:c++17 Main.cpp

# Run
Main.exe
```

#### Option 3: Using CMake

```bash
# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .

# Run
./unidisc
```

---


## 📚 Module Details

### Module 1: Course Scheduling
**Discrete Concept:** Graph Theory, Topological Sort

- Generate valid course sequences respecting prerequisites
- Validate student enrollment based on completed courses
- Detect circular dependencies
- Check available courses for students

**Key Algorithms:**
- Kahn's Algorithm (Topological Sort)
- In-degree calculation for prerequisite graphs

---

### Module 2: Student Combinations
**Discrete Concept:** Combinatorics, Counting Principles

- Assign students to project groups using nCr
- Calculate lab session distributions
- Assign students to electives
- Generate all possible team combinations

**Key Formulas:**
- nCr = n! / (r! × (n-r)!)
- nPr = n! / (n-r)!

---

### Module 3: Induction Verification 
**Discrete Concept:** Mathematical Induction, Strong Induction

- Verify multi-term prerequisite chains
- Prove course sequence validity
- Check student progress using strong induction
- Generate valid sequences automatically

**Proof Structure:**
1. Base Case: P(1)
2. Inductive Hypothesis: Assume P(k)
3. Inductive Step: Prove P(k+1)
4. Conclusion: ∀n, P(n)

---

### Module 4: Logic & Inference
**Discrete Concept:** Propositional Logic, Inference Rules

- Parse IF-THEN rules
- Forward chaining inference engine
- Conflict detection in rule base
- Faculty and room assignment rules

**Supported Rules:**
- IF condition THEN conclusion
- Modus Ponens
- Transitive inference

---

### Module 5: Set Operations 
**Discrete Concept:** Set Theory

- Union: A ∪ B
- Intersection: A ∩ B
- Difference: A - B
- Power Set: P(A)
- Cartesian Product: A × B
- Subset checking

**Applications:**
- Students enrolled in multiple courses
- Course-student relationships
- Faculty-course mappings

---

### Module 6: Relations
**Discrete Concept:** Binary Relations

- Check reflexive, symmetric, transitive properties
- Equivalence relation detection
- Partial order verification
- Relation composition
- Indirect conflict detection

**Relation Types:**
- Student-Course (enrollment)
- Faculty-Course (teaching)
- Course-Room (assignment)

---

### Module 7: Functions 
**Discrete Concept:** Functions, Mappings

- Map students → courses
- Map courses → faculty
- Map faculty → rooms
- Check injectivity (one-to-one)
- Check surjectivity (onto)
- Check bijectivity
- Function composition
- Inverse functions

---

### Module 8: Automated Proofs 
**Discrete Concept:** Proof Techniques

- Generate step-by-step proofs
- Mathematical induction proofs
- Strong induction proofs
- Logic rule verification
- Course chain validation

---

### Module 9: Consistency Checker
**Discrete Concept:** Constraint Satisfaction

- Time conflict detection
- Room double-booking prevention
- Faculty scheduling conflicts
- Prerequisite violation detection
- Credit overload checking

---

### Module 10: Efficiency & Benchmarking 
**Discrete Concept:** Algorithm Optimization

- Memoization (Fibonacci, Combinations)
- Bitset operations (memory efficiency)
- Vector optimization (reserve vs no reserve)
- Recursion vs iteration comparison
- Performance benchmarking

**Techniques:**
- Dynamic Programming
- Bit Manipulation
- Time Complexity Analysis

---


### Test Coverage

- ✅ Set Operations (4 tests)
- ✅ Combinations (4 tests)
- ✅ Relations (3 tests)
- ✅ Functions (3 tests)
- ✅ Logic (5 tests)
- ✅ Prerequisites (2 tests)
- ✅ Consistency (2 tests)
- ✅ Scheduling (2 tests)

**Total: 25+ comprehensive tests**

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### Contribution Guidelines

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/amazing-feature
   ```
3. **Commit your changes**
   ```bash
   git commit -m "Add amazing feature"
   ```
4. **Push to the branch**
   ```bash
   git push origin feature/amazing-feature
   ```
5. **Open a Pull Request**

### Areas for Improvement

- [ ] GUI implementation (Qt/wxWidgets)
- [ ] Database integration (SQLite/MySQL)
- [ ] Export to PDF reports
- [ ] Graphical visualization of relations
- [ ] Web-based interface
- [ ] Multi-language support
- [ ] Advanced scheduling algorithms
- [ ] Machine learning predictions

---

## 👥 Team

| Name | Role | Contribution | GitHub |
|------|------|--------------|--------|
| **[Muhammad Taha Rehan]** | Project Lead | Integration, Entities, Base Classes, Module 4, 5, 6, 7 | [@Muhammad-Taha-Rehan](https://github.com/Muhammad-Taha-Rehan) |
| **[Abdul Rehman]** | Developer | Module 1, 2, 3, 9, 10, 11, 12 | [@Abdul3005](https://github.com/Abdul3005) |


### Acknowledgments

- **Course Instructor:** Dr. Amer Rashid
- **University:** FAST University
- **Course:** Discrete Structures
- **Semester:** 3rd

---

---

## 📞 Contact

- **Project Repository:** [https://github.com/Muhammad-Taha-Rehan/unidisc-engine](https://github.com/Muhammad-Taha-Rehan/unidisc-engine)
- **Issues:** [https://github.com/Muhammad-Taha-Rehan/unidisc-engine/issues](https://github.com/yMuhammad-Taha-Rehan/unidisc-engine/issues)
- **Email:** miantaharehan77@gmail.com

---

## 🌟 Show Your Support

Give a ⭐️ if this project helped you understand discrete structures better!

---

---

## 🔄 Version History

### v1.0.0 (Current)
- ✅ All 12 modules implemented
- ✅ Comprehensive testing suite
- ✅ Interactive CLI
- ✅ Full documentation

### Future Releases
- v1.1.0 - GUI implementation
- v1.2.0 - Database integration
- v2.0.0 - Web interface

---

## 📊 Project Statistics

```
Language: C++
Lines of Code: ~5000+
Files: 15+ header files + Main.cpp
Modules: 12 complete modules
Test Cases: 25+ comprehensive tests
Concepts Covered: 20+ discrete math topics
```

---

<div align="center">

**Built with ❤️ using Discrete Mathematics**

**FAST University | Discrete Structures Project | 2025**

[⬆ Back to Top](#-unidisc-engine---university-discrete-structures-management-system)

</div>
