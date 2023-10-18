#include <iostream>
#include <utility>
#include <vector>
/* 
lvalue: a variable/object that has both a name and a memory address. 
    lvalues can appear on the left or right of an assignment operator (=).
    lvalue references are denother with one &.
    example: std::string hello("Hello"); // hello is an lvalue
rvalue: a variable/object that has only a memory address. 
    These are temporary objects that are created on the fly and destructed after being assigned/passed. 
    rvalues can appear only on the right of an assignment operator (=).
    rvalue references are denoted with double &&.
    example: std::string str;
    vec.pushback(str + str); // (str + str) is an rvalue.
*/

/*
std::move() is a function used for converting an lvalue reference to an rvalue reference. 
See here: https://en.cppreference.com/w/cpp/utility/move

move constructors were introduced to make passing objects more efficient. A move constructor steals the resoueces fro mthe source object and 
leaves the source object in a valud but unspecified state. They are used as a more efficient version of copy constructors whenever 
the object being copied is no longer needed (rvalues). It's important to note that whatever that is passed to a move constructor 
will be destroyred. 

The copy constructor uses the lvalue references which are marked with one ampersand (&) 
while the move constructor uses the rvalue references which are marked with two ampersands (&&).
*/

/*
Important notes:
    * Calling a std::move() on a const object has no effect. It doesn’t make any sense to steal or move the resources of a const object.
    * If Move semantics is not defined, copy semantics will be used as an alternative.
    * If there is no implementation taking rvalue reference as an argument, the implementation with const lavlue reference argument will be used instead.
    * If both of the implementations above are missing and there is only one implementation of a function with non constant lvalue argument, 
    that will be used.
*/


void v1(const std::string& str) {
    std::cout << "v1(const std::string& str)\n\t" << str << std::endl;
}

void v1(std::string&& str) {
    std::cout << "v1(std::string&& str)\n\t" << str << std::endl;
}

void v1(std::string& str) {
    std::cout << "v1(std::string& str)\n\t" << str << std::endl;
}


void v2(const std::string& str) {
    std::cout << "v2(const std::string& str)\n\t" << str << std::endl;
}

void v2(std::string& str) {
    std::cout << "v2(std::string& str)\n\t" << str << std::endl;
}


void v3(std::string& str) {
    std::cout << "v3(std::string& str)\n\t" << str << std::endl;
}

void v4(std::string&& str) {
    std::cout << "v4(std::string&& str)\n\t" << str << std::endl;
}

int main() {

    std::string hello("Hello");
    std::vector<std::string> vec;
    
    v1(hello);
    v1(std::string("Hello Again"));
    v1("Hi");
    v1(std::move(hello)); // v1 should implement code to move resources from hello. As it doesn't, hello will remain in memory.
    v1(std::move(hello + " Hi Again"));

    vec.push_back(std::move(hello)); // a move constructor is defined in the implementation of std::vector. That's why aftre this line
    // hello will be in valid but unspecified state. resources will be moved from hello to the vector. 
    std::cout << hello << std::endl;

    std::string hellov2("Hellov2");
    v2(hellov2);
    v2(std::move(hellov2)); // (const lvalue ref) version will be used.
    v2("Hiv2"); 

    std::string hellov3("Hellov3");
    v3(hellov3);
    v3(std::move(hellov3));

    const std::string  v4_const("Hellov4");
    // std::move(v4_const);
    // v4(std::move(v4_const)); // Will not work, becasue std::move will not take effect on the v4_const. In this case std::move will return lvalue ref
    // which cannot be passed as an rvalue ref. As v4 does not implement any overloaded version with const lvalue ref/lvalue ref arguments,
    // we see compiler errors.
    
}

