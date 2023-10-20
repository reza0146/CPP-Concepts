/*
A Copy assignment operator is called when an already initialized object is assigned a new value from another existing object. 
Syntax: 
T obj1, obj2;
obj2 = obj1; 
or
obj2.operator=(obj1);
*/

/*
Do not confuse this with copy constructor because they both can be called when an equal sign is used. Copy constructor is called when new object is being declared. 
There are other situations that a copy constructor gets called.
T obj1;
T obj2 = obj1; 
or 
obj2(obj1);
*/

/*
The compiler defines default assignment operator for user-defined classes. But, in some cases we need to overload the default operator= method. [Rule of Five]
See below for an example of the default assignment operator.
*/

// #include <iostream>
// class Person {
//   public:
//   Person() = default;
//   Person(std::string nname, int nage) : name(nname), age(nage) {}
//   std::string name;
//   int age;
// };

// int main() {
//   Person a("alex", 27);
//   Person b;
//   b.operator=(a);
//   std::cout << b.name;

//   return 0;
// }

/*
The syntax for overloading the assignment operator: [https://en.cppreference.com/w/cpp/language/operator_assignment]

T& operator=(const T2& other)
Note that T2 can be any type including T. (Yes, you can do = between two classes of different types as long as you have it defined.) You can overload assignment operator
and have different version of assignment operator.
*/

// // C++ program for Assignment Operator overloading 
// #include <iostream> 
// using namespace std; 
  
// class Complex { 
// private: 
//     int real, img; // real, imaginary 
  
// public: 
//     // Parameterized Constructor 
//     Complex(int r, int i) 
//     { 
//         real = r; 
//         img = i; 
//     } 
  
//     Complex& operator=(const Complex& C) 
//     { 
//         real = C.real; 
//         img = C.img; 
//         return *this;
//     } 
  
//     // function to print 
//     void print() { cout << real << "+i" << img << endl; } 
// }; 
  
// int main() 
// { 
//     // Assigning by overloading constructor 
//     Complex C1(2, 3), C2(4, 6); 
    
//     cout << "BEFORE OVERLOADING ASSIGNMENT OPERATOR"<< endl; 
//     cout << "C1 complex number: "; 
    
//     C1.print();     
    
//     cout << "C2 complex number: "; 
    
//     C2.print();      
    
//     // overloading assignment operator to copy values 
//     C1 = C2; 
    
//     cout << "AFTER OVERLOADING ASSIGNMENT OPERATOR" << endl; 
//     cout << "C1 complex number: "; 
    
//     C1.print();     
    
//     cout << "C2 complex number: "; 
    
//     C2.print(); 
    
//     return 0; 
// }

/*
When should we write our own assignment operator in C++?
The answer is same as Copy Constructor. 
If a class doesn’t contain pointers, then there is no need to write assignment operator and copy constructor. 
The compiler creates a default copy constructor and assignment operators for every class. 
The compiler created copy constructor and assignment operator may not be sufficient when we have pointers 
or any run time allocation of resource like file handle, a network connection..etc.
*/

// #include<iostream> 
// using namespace std; 
  
// // A class without user defined assignment operator 
// class Test 
// { 
//     int *ptr; 
// public: 
//     Test (int i = 0)      { ptr = new int(i); } 
//     void setValue (int i) { *ptr = i; } 
//     // ~Test() {delete ptr;}
//     void print()          { cout << *ptr << endl; } 
// }; 
  
// int main() 
// { 
//     Test t1(5); 
//     Test t2; 
//     t2 = t1; 
//     t1.setValue(10); 
//     t2.print(); 
//     return 0; 
// } 

/*
Output of above program is “10”. If we take a look at main(), we modified ‘t1’ using setValue() function, but the changes are also reflected in object ‘t2’. 
This type of unexpected changes cause problems.
Since there is no user defined assignment operator in the above program, compiler creates a default assignment operator, which copies ‘ptr’ of right hand side to left hand side.
So both ‘ptr’s start pointing to the same location.
*/

/*
We can handle the above problem in two ways.
1) Do not allow assignment of one object to other object. We can create our own dummy assignment operator and make it private.
2) Write your own assignment operator that does deep copy.
Same is true for Copy Constructor.
*/

#include<iostream> 
using namespace std; 
  
// A class without user defined assignment operator 
class Test 
{ 
    int *ptr; 
public: 
    Test (int i = 0)      { ptr = new int(i); } 
    // Test(const Test& other); // copy constructor  
    // Test &operator=(const Test& other); // assignment operator
    // ~Test() {delete ptr;}
    void setValue (int i) { *ptr = i; } 
    void print()          { cout << *ptr << endl; } 
}; 

// Test::Test(const Test& other) {
//   ptr = new int(*other.ptr);
// }

// Test &Test::operator=(const Test& other) {
//   // Check for self-assignment
//   if (this != &other) {
//     *ptr = *(other.ptr);
//   }  
//   return *this;
// }

int main() 
{ 
    Test t1(5); 
    Test t3 = t1; // Copy constructor called. 
    
    Test t2; 
    t2 = t1; // Assignment operator called.

    t1.setValue(10); 
    t2.print(); 
    t3.print();
    return 0; 
} 

/*
We should also add a copy constructor to the above class, so that the statements like “Test t3 = t4;” also don’t cause any problem.
Note the if condition in assignment operator. While overloading assignment operator, we must check for self assignment. 
Otherwise assigning an object to itself may lead to unexpected results (See this).
Self assignment check is not necessary for the above ‘Test’ class, because ‘ptr’ always points to one integer and we may reuse the same memory.
But in general, it is a recommended practice to do self-assignment check.
*/

/* Read more
https://learn.microsoft.com/en-us/cpp/cpp/copy-constructors-and-copy-assignment-operators-cpp?view=msvc-170
*/