#include <iostream>

/* Some Intro
    * Imagine you have a base class and a derived class from the base class. A base class pointer can point to content with the type
    of any of its derived classes. 
    * When you call class methods on objects, the bindning between the method and the object (which method will be called) is normally done at 
    compile time (early biniding).
*/

/*
When a method is called with keyword virtual, the binding between that method and pointers invoking that method will be done at runtime (late binding).

    * Virtual functions should be accessed using a pointer or reference of base class type to achieve runtime polymorphism.
    * They are always defined in the base class and overridden in a derived class. It is not mandatory for the derived class to override (or re-define the virtual function), 
    * The prototype of virtual functions should be the same in the base as well as the derived class. Prototype means the return type, the name, the arguments.
    in that case, the base class version of the function is used.
    * Virtual functions cannot be static.
    * A class can have a virtual destructor but not a virtual constructor.
*/

/*
Limitations: 
    * Slower function calls
    * More difficult to debug
*/


/*
To see another more practical example of how virtual functions can be useful see: https://www.geeksforgeeks.org/virtual-functions-and-runtime-polymorphism-in-cpp/
Specifically see this example in the above page: Real-Life Example to Understand the Implementation of Virtual Function

Virtual functions allow us to create a list of base class pointers and "call methods of any of the derived classes" without even knowing the kind of derived class object. 


*/

// Source: https://www.geeksforgeeks.org/virtual-function-cpp/

class Base {
    public:
    virtual void print() {
        std::cout << "print : base class definition called\n";
    }

    void show() {
        std::cout << "show : base class defintion called\n";
    }
};

class Derived : public Base {
    public:
    void print() {
        std::cout << "print : derived class definition called\n";
    }

    void show() {
        std::cout << "show : derived class definition called\n";
    }
};

int main() {
    Base* b_ptr = new Base; // Base class pointer
    Derived d; // Derived class object

    b_ptr->print(); // Runtime binding
    b_ptr->show(); // Compile binding

    delete b_ptr;
    b_ptr = &d; // now b_ptr is pointing to a d object.

    b_ptr->print(); // Runtime binding: b_ptr is pointing to a d object. As print is defined as virtual, it will be bounded at the runtime based on the current 
    // runtime type of the object that b_ptr is pointing to.
    b_ptr->show(); // Compile binding. At compilation time, the b_ptr is a Base pointer, so it will be binded to the base class version although at runtime 
    // bptr is pointing to a d type object.
}


// Another example
// #include <iostream>
// using namespace std;
 
// class base {
// public:
//     void fun_1() { cout << "base-1\n"; }
//     virtual void fun_2() { cout << "base-2\n"; }
//     virtual void fun_3() { cout << "base-3\n"; }
//     virtual void fun_4() { cout << "base-4\n"; }
// };
 
// class derived : public base {
// public:
//     void fun_1() { cout << "derived-1\n"; }
//     void fun_2() { cout << "derived-2\n"; }
//     void fun_4(int x) { cout << "derived-4\n"; }
// };
 
// int main()
// {
//     base* p;
//     derived obj1;
//     p = &obj1;
 
//     // Early binding because fun1() is non-virtual
//     // in base
//     p->fun_1();
 
//     // Late binding (RTP)
//     p->fun_2();
 
//     // Late binding (RTP)
//     p->fun_3();
 
//     // Late binding (RTP)
//     p->fun_4();
 
//     // p->fun_4(5);
//     // Early binding : fun_4(int) in the derived class is different from the virtual function fun_4() in the base class as prototypes of both functions are different.
//     // but this function call is
//     // illegal (produces error) because pointer
//     // is of base type and function is of
//     // derived class
 
//     return 0;
// }

