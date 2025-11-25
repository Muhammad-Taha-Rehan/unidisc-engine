#ifndef MODULE10_EFFICIENCY_H
#define MODULE10_EFFICIENCY_H

#include <iostream>
#include <chrono>
#include <set>
#include <vector>
#include <map>
#include <bitset>
using namespace std;
using namespace chrono;


// Algorithmic Efficiency & Benchmarking 
class EfficiencyBenchmark {
private:
    // Memoization cache for Fibonacci
    static map<int, long long> fiboCache;
    // Memoization cache for combinations
    static map<pair<int, int>, long long> combCache;

public:
    //FIBONACCI WITHOUT MEMOIZATION 
    static long long fibonacciSlow(int n) {
        if (n <= 1) return n;
        return fibonacciSlow(n - 1) + fibonacciSlow(n - 2);
    }

    // FIBONACCI WITH MEMOIZATION
    static long long fibonacciFast(int n) {
        if (n <= 1) return n;

        // first Check cache
        if (fiboCache.find(n) != fiboCache.end()) {
            return fiboCache[n];
        }

        // Compute and store in cache
        long long result = fibonacciFast(n - 1) + fibonacciFast(n - 2);
        fiboCache[n] = result;
        return result;
    }

    //COMBINATIONS WITHOUT MEMOIZATION
    static long long combinationSlow(int n, int r) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;
        return combinationSlow(n - 1, r - 1) + combinationSlow(n - 1, r);
    }

    // COMBINATIONS WITH MEMOIZATION
    static long long combinationFast(int n, int r) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;

        pair<int, int> key = { n, r };

        // Check cache
        if (combCache.find(key) != combCache.end()) {
            return combCache[key];
        }

        // Compute and cache
        long long result = combinationFast(n - 1, r - 1) + combinationFast(n - 1, r);
        combCache[key] = result;
        return result;
    }

    // BITSET OPERATIONS
    static void demonstrateBitsets() {

        cout <<endl<< "    Bitset Operations (Memory Efficient) "<<endl;

        // Use bitset for enrolled students,1 for enrolled, 0 for  not enrolled
        const int MAX_STUDENTS = 64;
        bitset<MAX_STUDENTS> enrolledCS101;
        bitset<MAX_STUDENTS> enrolledMath101;

        // Enroll some students 
        enrolledCS101.set(1); 
        enrolledCS101.set(5);  
        enrolledCS101.set(10); 
        enrolledCS101.set(15); 

        // Enroll some students 
        enrolledMath101.set(5);  
        enrolledMath101.set(10); 
        enrolledMath101.set(20); 

        cout << "CS101 Enrollment (bitset) :  " << enrolledCS101 << endl;
        cout << "Math101 Enrollment (bitset) : " << enrolledMath101 << endl;

        // Intersection 
        bitset<MAX_STUDENTS> both = enrolledCS101 & enrolledMath101;
        cout << "Students in BOTH courses (Intersection) :    " << both << endl;
        cout << "Count : " << both.count() << " Students"<<endl;

        // Union
        bitset<MAX_STUDENTS> either = enrolledCS101 | enrolledMath101;
        cout << "Students in Eiether Course :   " << either << endl;
        cout << "Count : " << either.count() << " Students"<<endl;

        // Difference 
        bitset<MAX_STUDENTS> onlyCS = enrolledCS101 & (~enrolledMath101);
        cout << "Students Only in CS101 :      " << onlyCS << endl;
        cout << "Count : " << onlyCS.count() << " students"<<endl;

        cout << endl<<"  Bitsets use " << MAX_STUDENTS / 8 << " bytes vs "
            << MAX_STUDENTS * sizeof(bool) << " bytes for bool array"<<endl;
    }

    // VECTOR OPTIMIZATION
    static void demonstrateVectorOptimization() {
        cout <<endl<< "    Vector Optimization (Reserve vs No Reserve) "<<endl;

        const int SIZE = 100000;

        // Without reserve
        auto start = high_resolution_clock::now();
        vector<int> v1;
        for (int i = 0; i < SIZE; i++) {
            v1.push_back(i);
        }
        auto end = high_resolution_clock::now();
        auto time1 = duration_cast<microseconds>(end - start).count();

        // With reserve
        start = high_resolution_clock::now();
        vector<int> v2;
        v2.reserve(SIZE);
        for (int i = 0; i < SIZE; i++) {
            v2.push_back(i);
        }
        end = high_resolution_clock::now();
        auto time2 = duration_cast<microseconds>(end - start).count();

        cout << "Without reserve : " << time1 << " us"<<endl;
        cout << "With reserve :    " << time2 << " us"<<endl;
        cout << "Speedup : " << (double)time1 / time2 << "x faster"<<endl;
    }

    // RECURSION & ITERATION
    static long long factorialRecursive(int n) {
        if (n <= 1) return 1;
        return n * factorialRecursive(n - 1);
    }

    static long long factorialIterative(int n) {
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    // BENCHMARKING
    static void benchmarkSetOperations() {
        cout <<endl<< "    Set Operations Performance    "<<endl;
        set<int> s1, s2;
        for (int i = 0; i < 10000; i++) {
            s1.insert(i);
            s2.insert(i + 5000);
        }

        auto start = high_resolution_clock::now();
        set<int> result;
        set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
            inserter(result, result.begin()));
        auto end = high_resolution_clock::now();

        cout << "Union of 10,000 element sets : "
            << duration_cast<microseconds>(end - start).count() << " us"<<endl;
        cout << "Result size : " << result.size() << " elements"<<endl;
    }

    static void benchmarkMemoization() {
        cout <<endl<< "~~~Memoization Performance Comparison~~~"<<endl;

        // Clear caches
        fiboCache.clear();
        combCache.clear();

        // Test Fibonacci
        cout <<endl<< "Fibonacci(35) :"<<endl;

        auto start = high_resolution_clock::now();
        long long result1 = fibonacciSlow(35);
        auto end = high_resolution_clock::now();
        auto timeSlow = duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        long long result2 = fibonacciFast(35);
        end = high_resolution_clock::now();
        auto timeFast = duration_cast<microseconds>(end - start).count();

        cout << "  Without memoization : " << timeSlow << " ms"<<endl;
        cout << "  With memoization :    " << timeFast << " us"<<endl;
        cout << "  Speedup : " << (timeSlow * 1000.0) / timeFast << "x faster !"<<endl;
        cout << "  Result : " << result2 << endl;

        // Test Combinations
        combCache.clear();
        cout <<endl<< "Combination C(20, 10) :"<<endl;

        start = high_resolution_clock::now();
        long long comb1 = combinationSlow(20, 10);
        end = high_resolution_clock::now();
        timeSlow = duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        long long comb2 = combinationFast(20, 10);
        end = high_resolution_clock::now();
        timeFast = duration_cast<microseconds>(end - start).count();

        cout << "  Without memoization : " << timeSlow << " ms"<<endl;
        cout << "  With memoization :    " << timeFast << " us"<<endl;
        cout << "  Speedup : " << (timeSlow * 1000.0) / timeFast << "x faster !"<<endl;
        cout << "  Result : " << comb2 << endl;
    }

    static void benchmarkRecursionVsIteration() {
        cout <<endl<< "~~~Recursion vs Iteration~~~"<<endl;

        int n = 20;

        auto start = high_resolution_clock::now();
        long long result1 = factorialRecursive(n);
        auto end = high_resolution_clock::now();
        auto timeRec = duration_cast<nanoseconds>(end - start).count();

        start = high_resolution_clock::now();
        long long result2 = factorialIterative(n);
        end = high_resolution_clock::now();
        auto timeIter = duration_cast<nanoseconds>(end - start).count();

        cout << "Factorial(" << n << ") :"<<endl;
        cout << "  Recursive : " << timeRec << " ns"<<endl;
        cout << "  Iterative : " << timeIter << " ns"<<endl;
        cout << "  Iteration is " << (double)timeRec / timeIter << "x faster"<<endl;
        cout << "  Result : " << result2 << endl;
    }

    // DEMONSTRATION
    static void demonstrate() {
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "        MODULE 10 : ALGORITHMIC EFFICIENCY"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        // Example Memoization
        benchmarkMemoization();

        // Example Bitsets
        demonstrateBitsets();

        // Example Vector Optimization
        demonstrateVectorOptimization();

        // Example Recursion & Iteration
        benchmarkRecursionVsIteration();

        // Example Set Operations
        benchmarkSetOperations();
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "            Module 10 Complete!"<<endl;
        cout << "     Demonstrated : Memoization, Bitsets, Vectors,"<<endl;
        cout << "   Recursion optimization, Performance benchmarking"<<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
};

//  static members 
map<int, long long> EfficiencyBenchmark::fiboCache;
map<pair<int, int>, long long> EfficiencyBenchmark::combCache;

#endif