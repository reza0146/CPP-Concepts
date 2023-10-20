/*
https://www.geeksforgeeks.org/move-constructors-in-c-with-examples/
https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170
*/

/*
Put breakpoints at lines 77 and 79 and see what is called. Be careful that because constructor is called in the initializer list of the copy constructor, 
you may see constructor calls that are actually part of the copy constructor call
*/

// #include <iostream>
// #include <vector>
// using namespace std;
 
// // Move Class
// class Move {
// private:
//     // Declaring the raw pointer as
//     // the data member of the class
//     int* data;
 
// public:
//     // Constructor
//     Move(int d)
//     {
//         // Declare object in the heap
//         data = new int;
//         *data = d;
 
//         cout << "Constructor is called for "
//              << d << "\t" << data << endl;
//     };
 
//     // Copy Constructor to delegated
//     // Copy constructor
//     Move(const Move& source)
//         : Move{ *source.data }
//     {
 
//         // Copying constructor copying
//         // the data by making deep copy
//         cout << "Copy Constructor is called - "
//              << "Deep copy for "
//              << *source.data << " from " << source.data << " to "
//              << data
//              << endl;
//     }
 
//     // Destructor
//     ~Move()
//     {
//         if (data != nullptr)
 
//             // If the pointer is not
//             // pointing to nullptr
//             cout << "Destructor is called for "
//                  << *data << "\t" << data << endl;
//         else
 
//             // If the pointer is
//             // pointing to nullptr
//             cout << "Destructor is called"
//                  << " for nullptr"
//                  << endl;
 
//         // Free the memory assigned to
//         // data member of the object
//         delete data;
//     }
// };
 
// // Driver Code
// int main()
// {
//     // Create vector of Move Class
//     vector<Move> vec;
 
//     // Inserting object of Move class
//     vec.push_back(Move{ 10 });
//     vec.push_back(Move{ 20 });
//     // vec.push_back(Move{30});
//     return 0;
// }

/*
Now we add the move constructor. You can see that when the Move objects are being passed to the push_back method, the move constructor is called instead of the copy 
constructor. This avoids creating temporary memory allocations and decreases overhead. Using move constructors is a great way to increase efficiency.

Be careful that the argument of a move constructor cannot be a const, becasue we change the source object.
*/

#include <iostream>
#include <vector>
using namespace std;
 
// Move Class
class Move {
private:
    // Declaring the raw pointer as
    // the data member of the class
    int* data;
 
public:
    // Constructor
    Move(int d)
    {
        // Declare object in the heap
        data = new int;
        *data = d;
 
        cout << "Constructor is called for "
             << d << "\t" << data << endl;
    };
 
    // Copy Constructor to delegated
    // Copy constructor
    Move(const Move& source)
        : Move{ *source.data }
    {
 
        // Copying constructor copying
        // the data by making deep copy
        cout << "Copy Constructor is called - "
             << "Deep copy for "
             << *source.data << " from " << source.data << " to "
             << data
             << endl;
    }

    // Move constructor 
    Move(Move&& source) : 
      data(source.data) {
        // or you could do this instead of the initializer list:
        // data = source.data;
        cout << "Move Constructor for "
             << *source.data << "\t" << data << endl;
        source.data = nullptr; // If we don't do this, any change we make to the moved object will be done on the source object. (it will be like passing by reference)
    }
 
    // Destructor
    ~Move()
    {
        if (data != nullptr)
 
            // If the pointer is not
            // pointing to nullptr
            cout << "Destructor is called for "
                 << *data << "\t" << data << endl;
        else
 
            // If the pointer is
            // pointing to nullptr
            cout << "Destructor is called"
                 << " for nullptr"
                 << endl;
 
        // Free the memory assigned to
        // data member of the object
        delete data;
    }
};
 
// Driver Code
// int main()
// {
//     // Create vector of Move Class
//     vector<Move> vec;
 
//     // Inserting object of Move class
//     vec.push_back(Move{ 10 });
//     vec.push_back(Move{ 20 });
//     // vec.push_back(Move{30});
//     return 0;
// }

/*
A move constructor is called when the object you are passing to a method is an ravlue. rvalues are objects that do not have an assigned name and only have a memory address.
Otherwise a copy constructor will be called. We can call the move constructor by using std::move on an lvalue object. std::move converts an lvalue to rvalue.
For the above code:
*/

int main()
{
    // Create vector of Move Class
    vector<Move> vec;
    Move m1(5);
 
    // Inserting object of Move class
    vec.push_back(Move{ 10 });
    vec.push_back(Move{ 20 }); // Move{20} is an rvalue. It's temporary and we do not need to keep it. So the move constructor is called and the Move{20} will go in a valid but unspecified state.
    vec.push_back(m1); // m1 is lvalue. we do not want to lose m1 after this function call. So, m1 will be copied and passed to the function. 
    vec.push_back(std::move(m1));
    vec.push_back(Move{30});
    return 0;
}

/*
Do c++ compilers provide move constructors and move assignment operator?
See here for an answer. Read carefully. https://stackoverflow.com/questions/32225874/do-compilers-provide-default-move-assignment-operators-and-move-constructors
*/
