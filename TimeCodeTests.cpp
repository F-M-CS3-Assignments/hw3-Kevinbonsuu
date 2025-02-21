
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"

// Test function for converting hours, minutes, and seconds into total seconds
void TestComponentsToSeconds(){
    cout << "Testing ComponentsToSeconds" << endl;
    long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
    assert(t == 11862);
    t = TimeCode::ComponentsToSeconds(0, 59, 59);
    assert(t == 3599);
    t = TimeCode::ComponentsToSeconds(100, 0, 0);
    assert(t == 360000);
    cout << "PASSED!" << endl << endl;
}

// Test default constructor, ensuring TimeCode initializes to 0:0:0
void TestDefaultConstructor(){
    cout << "Testing Default Constructor" << endl;
    TimeCode tc;
    assert(tc.ToString() == "0:0:0");
    cout << "PASSED!" << endl << endl;
}

// Test constructor with various input combinations
void TestComponentConstructor(){
    cout << "Testing Component Constructor" << endl;
    TimeCode tc = TimeCode(0, 0, 0);
    assert(tc.ToString() == "0:0:0");
	TimeCode tc2 = TimeCode(3, 45, 30);
    assert(tc2.ToString() == "3:45:30");
    TimeCode tc3 = TimeCode(3, 71, 3801);
    assert(tc3.ToString() == "5:14:21");
    TimeCode tc4 = TimeCode(0, 0, 3661);
    assert(tc4.ToString() == "1:1:1");
	TimeCode tc6 = TimeCode(24, 60, 60);
    assert(tc6.ToString() == "25:1:0");
	TimeCode tc7 = TimeCode(99, 99, 99);
    assert(tc7.ToString() == "100:40:39");
    cout << "PASSED!" << endl << endl;
}

// Test function to extract hour, minute, second components
void TestGetComponents(){
    cout << "Testing GetComponents" << endl;
    unsigned int h, m, s;
    TimeCode tc = TimeCode(5, 2, 18);
    tc.GetComponents(h, m, s);
    assert(h == 5 && m == 2 && s == 18);
    TimeCode tc2 = TimeCode(100, 0, 0);
    tc2.GetComponents(h, m, s);
    assert(h == 100 && m == 0 && s == 0);
	TimeCode tc3 = TimeCode(23, 59, 59);
    tc3.GetComponents(h, m, s);
    assert(h == 23 && m == 59 && s == 59);
	TimeCode tc4 = TimeCode(12, 30, 90);
    tc4.GetComponents(h, m, s);
    assert(h == 12 && m == 31 && s == 30);
    cout << "PASSED!" << endl << endl;
}

// Test subtraction operator with proper error handling
void TestSubtract(){
    cout << "Testing Subtract" << endl;
    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(0, 50, 0);
    TimeCode tc3 = tc1 - tc2;
    assert(tc3.ToString() == "0:10:0");
    // Test case where subtraction results in negative time (should throw an error)
    TimeCode tc4 = TimeCode(1, 15, 45);
    try{
        TimeCode tc5 = tc1 - tc4;
        assert(false);
    }
    catch(const invalid_argument& e){}
    
    TimeCode tc6 = TimeCode(3, 40, 30);
    TimeCode tc7 = TimeCode(1, 20, 15);
    TimeCode tc8 = tc6 - tc7;
    assert(tc8.ToString() == "2:20:15");
    
    TimeCode tc9 = TimeCode(10, 0, 0);
    TimeCode tc10 = TimeCode(5, 30, 0);
    TimeCode tc11 = tc9 - tc10;
    assert(tc11.ToString() == "4:30:0");
    
    cout << "PASSED!" << endl << endl;
}

// Test function to set minutes and check error handling
void TestSetMinutes(){
    cout << "Testing SetMinutes" << endl;
    TimeCode tc = TimeCode(8, 5, 9);
    tc.SetMinutes(15);
    assert(tc.ToString() == "8:15:9");
    //  Invalid minute value should trigger exception
    try{
        tc.SetMinutes(80);
        assert(false);
    }
    catch (const invalid_argument &e){}
    assert(tc.ToString() == "8:15:9");
    cout << "PASSED!" << endl << endl;
}

//  Test various edge cases for normalization
void TestEdgeCases(){
    cout << "Testing Edge Cases" << endl;
    TimeCode tc1(0, 0, 3661);
    assert(tc1.ToString() == "1:1:1");
    TimeCode tc2(100, 0, 0);
    assert(tc2.ToString() == "100:0:0");
    TimeCode tc3(0, 59, 61);
    assert(tc3.ToString() == "1:0:1");
    TimeCode tc4(200, 30, 90);
    assert(tc4.ToString() == "200:31:30");
    cout << "PASSED!" << endl;
}

// Test arithmetic operators: addition, subtraction, multiplication, and division
void TestArithmeticOperations(){
    cout << "Testing Arithmetic Operations" << endl;
    TimeCode tc1(1, 0, 0);
    TimeCode tc2(0, 30, 0);
    assert((tc1 + tc2).ToString() == "1:30:0");
    assert((tc1 - tc2).ToString() == "0:30:0");
    assert((tc1 * 2).ToString() == "2:0:0");
    assert((tc1 / 2).ToString() == "0:30:0");
    cout << "PASSED!" << endl;
}

// Test comparison operators (>, >=, <, <=, ==, !=)
void TestComparisons(){
    cout << "Testing Comparisons" << endl;
    TimeCode tc1(2, 0, 0);
    TimeCode tc2(1, 59, 59);
    assert(tc1 > tc2);
    assert(tc1 >= tc2);
    assert(tc2 < tc1);
    assert(tc2 <= tc1);
    assert(tc1 != tc2);
    TimeCode tc3(2, 0, 0);
    assert(tc1 == tc3);
    cout << "PASSED!" << endl;
}

// Main function to execute all tests
int main(){
    TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestGetComponents();
    TestSubtract();
    TestSetMinutes();
    TestEdgeCases();
    TestArithmeticOperations();
    TestComparisons();
    cout << "PASSED ALL TESTS!!!" << endl;
    return 0;
}
