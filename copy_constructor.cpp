/*
A copy constructor is called whenever an object of the same type needs to be created. You can explicitly call a copy constructor by 
this syntax newObj(sourceObj). The copy constructor will be called with this syntax when you create and initialize an object using another object of same class: 
className newObj = sourceObj.
*/ 

/*
Rule of five: when a class defines one of the following, it should define all five.
Destructor
Copy constructor
Copy assignment operator
Move constructor
Move assignment operator
*/

/*
The syntax for defining a copy constructor is ClassName(cosnt ClassName &old_obj). The copy constructor always accepts a reference to the source object. 
If you do not define a copy constructor, the compiler defines a default one [unless you have defined a custom function from the rule of five list]
*/

/*
A user-defined copy constructor is generally needed when an object owns pointers or non-shareable references, 
such as to a file, in which case a destructor, a copy assignment operator, a move constructor and a move assignment operator should also be written.
*/

/*
When is the copy constructor called? 
In C++, a Copy Constructor "may" be called in the following cases: 
When an object of the class is returned by value. 
When an object of the class is passed (to a function) by value as an argument. 
When an object is constructed based on another object of the same class. 
When the compiler generates a temporary object.
It is, however, not guaranteed that a copy constructor will be called in all these cases, 
because the C++ Standard allows the compiler to optimize the copy away in certain cases, one example is the return value optimization (sometimes referred to as RVO).
In some of the above scenarios a move constructor or move assignment operator may be called. Move semantics is generally more efficient than copy semantics because a temporary
object will not be created for copying resources.
*/

/*
If we don’t define our own copy constructor, the C++ compiler creates a default copy constructor for each class which does a member-wise copy between objects.
We need to define our own copy constructor only if an object has pointers or any runtime allocation of the resource like a file handle, a network connection, etc.
*/

/*
Which of the following two statements calls the copy constructor and which one calls the assignment operator? 
MyClass t1, t2;
MyClass t3 = t1;  // ----> (1)
t2 = t1;          // -----> (2) 
A copy constructor is called when a new object is created from an existing object, as a copy of the existing object. 
The assignment operator is called when an already initialized object is assigned a new value from another existing object. 
In the above example (1) calls the copy constructor and (2) calls the assignment operator.
*/

// class Person {
//  public:
//   std::string name;
//   int age;

//   Person(std::string nname, int nage) : name(nname), age(nage) {}
//   Person(const Person &old_person) {
//     name = old_person.name;
//     age = 0; // Doing this to make it a unique copy constructor. A default one will copy all data members.
//   }
//   void display() {
//     std::cout << name << "\t" << age << "\n";
//   }

// };

// void test_func(Person passed_person) {
//   passed_person.display();
// }

// int main() {
//   Person rp("Alex", 27);
//   Person rp_copy(rp); 
//   // or 
//   // Person rp_copy = rp;

//   rp.display();
//   rp_copy.display();
//   test_func(rp); // rp is passed by value. The copy constructor will be called to create the passed_person in local scope of test_func.
// }

/*
We need to define our own copy constructor only if an object has pointers or any runtime allocation of the resource like a file handle, a network connection, etc.
See the example below. One of the class members is a pointer. If we do not define a copy constructor, when str2 is copied from str1, the str2.s will be set to be str1.s. 
This means that str2.s will point to the same value as str1.s. Basically, any change that happens on str2 will also be applied to str1. So, str2 will not be a "copy".
To make a real copy of str1, we need to define a copy constructor that allocates new memory for the copy being created. 
*/

/*
A copy constructor can be made private. When we make a copy constructor private in a class, objects of that class become non-copyable. 
we can either write our own copy constructor like the below String example or make a private copy constructor so that users get compiler errors rather than surprises at runtime.
*/

#include <cstring>
#include <iostream>
using namespace std;
 
class String {
private:
    char* s;
    int size;
 
public:
    String(const char* str = NULL); // constructor
    // ~String() { delete[] s; } // destructor
    // String(const String&); // copy constructor
    void print()
    {
        cout << s << endl;
    } // Function to print string
    void change(const char*); // Function to change
};
 
// In this the pointer returns the CHAR ARRAY
// in the same sequence of string object but
// with an additional null pointer '\0'
String::String(const char* str)
{
    size = strlen(str);
    s = new char[size + 1];
    strcpy(s, str);
}
 
void String::change(const char* str)
{
    delete[] s;
    size = strlen(str);
    s = new char[size + 1];
    strcpy(s, str);
}
 
// String::String(const String& old_str)
// {
//     size = old_str.size;
//     s = new char[size + 1];
//     strcpy(s, old_str.s);
// }
 
int main()
{
    String str1("GeeksQuiz");
    String str2 = str1;
 
    str1.print(); // what is printed ?
    str2.print();
 
    str2.change("GeeksforGeeks");
 
    str1.print(); // what is printed now ?
    str2.print();
    return 0;
}


/*Read more
https://learn.microsoft.com/en-us/cpp/cpp/copy-constructors-and-copy-assignment-operators-cpp?view=msvc-170
*/