/*
https://www.geeksforgeeks.org/move-assignment-operator-in-cpp-11/
https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170
*/

/*
Move assignment operator is called whenever the object to the right of an assignment operator (=) is an rvalue. 
One way to convert an lvalue object to rvalue is using std::move() function. This will cause the assignment operator to call the move assignment operator instead of 
the copy assignment operator. 
ObjBeingFilled = std::move(objBeingMoved)

This command will move the resources from objBeingMoved to objBeingFilled and puts the source object in a valid but unspecified state.
It's a great way to replace variables with minumum memory overhead.

It is like a copy assignment operator but instead of copying the data,
this moves the ownership of the given data to the destination object without making any additional copies. 
The source object is left in a valid but unspecified state.

Syntax is:
T& operator=(T&& source) noexcept {
  
  return *this;
};
*/


#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class DynamicArray {
 private:
  size_t size_;
  int* data_;
 public:
  // Constructor
  DynamicArray() : size_(0), data_(nullptr) {};

  DynamicArray(size_t sz): size_(sz), data_(new int[size_]) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = 0;
    }
    std::cout << "Constructor on " << data_ << "\t" << size_ << "\n";
  }
  
  // Move Assignment Operator 
  DynamicArray& operator=(DynamicArray&& source) noexcept {

    // Check for self-assignment
    if (this != &source) {
      // Free the existing resource
      std::cout << "Move assignment from " << source.data_ << "\t" << "to " << data_ << "\n";
      delete[] data_;

      //Move resources  
      size_ = source.size_;
      data_ = source.data_;

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      source.size_ = 0;
      source.data_ = nullptr;
    }
    return *this;
  } 

  /*
  Move Constructor (we called the move assignment operator to remove code redundancy)
  I'm not sure if the initializer list below is needed because anyways we are deleting the current resource in the move assignment
  operator definition.
  */

  DynamicArray(DynamicArray&& source) noexcept : size_(0), data_(nullptr) {
    std::cout << "Move constructor " << "\n";
    *this = std::move(source); // The move constructor also calls the move assignment operator.
  }

  // Copy Constructor
  DynamicArray(const DynamicArray& other): DynamicArray(other.size_) {
    std::cout << "Copy constructor" << "\n"; // The copy constructor also calls the constructor
    data_ = other.data_;
  }
  
  // Copy Assignment Operator 
  DynamicArray& operator=(const DynamicArray& other) {
    std::cout << "Copy assignment" << "\n";
    if (this != &other) {
      size_ = other.size_;
      data_ = other.data_;
    }
    return *this;
  }

  // Destructor
  ~DynamicArray() {
    std::cout << "Destructor " << data_ << "\n";
    if (data_ != nullptr) {
      delete[] data_;
    }
    }
 
 void display() {
  for (size_t i = 0; i < size_; ++i) {
    std::cout << data_[i] << " ";
  }
  std::cout << "\n";
 }
};

DynamicArray func() {
  DynamicArray arr(2);
  return arr;
}


int main() {

  // Scenario 1: we call the move assignment operator explicitly:
  // DynamicArray arr1(5);
  // DynamicArray arr2(10);

  // std::cout << "Before move" << std::endl;
  // arr1.display();
  // arr2.display();

  // arr1 = std::move(arr2);

  // std::cout << "After move" << std::endl;
  // arr1.display();
  // arr2.display();


  // Scenario 2: Move assignment operator is called implicitly by the compiler:
  DynamicArray arr_test(5);
  arr_test = func();
  arr_test.display();

   
}
