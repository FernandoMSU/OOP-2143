1. Abstract Classes and Interfaces
Abstract Classes- An abstract class serves as a blueprint for other classes. It cannot be instantiated and may contain abstract methods (methods without implementation) as well as implemented methods.
Derived classes are required to implement the abstract methods
#include <iostream>
using namespace std;

// Abstract class
class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing a Circle" << endl;
    }
};

int main() {
    Shape* shape = new Circle();
    shape->draw();
    delete shape;
    return 0;
}

Interface- Generally defines the set of methods (or messages) that an instance of a class that has that interface could respond to.




2. Abstraction
Abstraction is the process of hiding implementation details and showing only the necessary features of an object. In C++, abstraction is achieved through abstract classes and interfaces.

#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual void startEngine() = 0; // Pure virtual function
};

class Car : public Vehicle {
public:
    void startEngine() override {
        cout << "Car engine started!" << endl;
    }
};

int main() {
    Vehicle* myCar = new Car();
    myCar->startEngine();
    delete myCar;
    return 0;
}




3. Access Modifiers (Public, Private, Protected)
Access modifiers determine the accessibility of members (attributes and methods) of a class.

Public: Members are accessible from outside the class.
Private: Members are accessible only within the class.
Protected: Members are accessible within the class and by derived classes.

#include <iostream>
using namespace std;

class Example {
private:
    int privateVar; // Accessible only within the class
protected:
    int protectedVar; // Accessible within the class and derived classes
public:
    int publicVar; // Accessible from anywhere

    Example() : privateVar(10), protectedVar(20), publicVar(30) {}

    void showValues() {
        cout << "Private: " << privateVar << ", Protected: " << protectedVar << ", Public: " << publicVar << endl;
    }
};

class Derived : public Example {
public:
    void showProtected() {
        cout << "Protected: " << protectedVar << endl;
    }
};

int main() {
    Example obj;
    obj.publicVar = 50;
    obj.showValues();

    Derived d;
    d.showProtected();
    return 0;
}




4. Attributes / Properties
Attributes (or properties) are variables that belong to a class and define its state. In C++, these are typically declared within a class.




5. Class Variables
A class variable (static variable) is shared across all instances of a class. It is declared using the static keyword and belongs to the class rather than any specific instance.
#include <iostream>
using namespace std;

class Example {
public:
    static int count; // Static variable declaration

    Example() {
        count++;
    }
};

// Define static variable outside the class
int Example::count = 0;

int main() {
    Example obj1, obj2, obj3;
    cout << "Total objects created: " << Example::count << endl;
    return 0;
}




6. Classes and Objects
Class: A blueprint for creating objects. It encapsulates data (attributes) and behavior (methods).
Object: An instance of a class that contains actual values and can interact with other objects

#include <iostream>
using namespace std;

class Car {
public:
    string brand;
    int year;

    void display() {
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
};

int main() {
    Car myCar;
    myCar.brand = "Toyota";
    myCar.year = 2020;
    myCar.display();
    return 0;
}




7. Collections and Iterators:
Collections are data structures used to store and manage a group of objects. In C++, the Standard Template Library (STL) provides many collection types like arrays, vectors, lists, sets, and maps. Iterators are used to traverse through these collections.

Example:

#include <iostream>
#include <vector>

int main() {
    // Using a vector as a collection
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Using an iterator to loop through the vector
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";  // Dereferencing the iterator to access the value
    }
    std::cout << std::endl;
    return 0;
}




8. Composition:
Composition refers to an object having references or pointers to other objects as part of its data. It represents a "has-a" relationship. In C++, this is achieved by defining an object as a member of another class.

Example:

#include <iostream>
using namespace std;

class Engine {
public:
    void start() { cout << "Engine starting...\n"; }
};

class Car {
private:
    Engine engine;  // Composition: Car has an Engine

public:
    void startCar() {
        engine.start();  // Calling Engine's method
        cout << "Car is now running.\n";
    }
};

int main() {
    Car myCar;
    myCar.startCar();  // Starting the car, which internally starts the engine
    return 0;
}




9. Constructors and Destructors:
Constructors are special member functions that initialize objects.
Destructors are special member functions that clean up resources when an object is destroyed.
Example:

#include <iostream>
using namespace std;

class MyClass {
public:
    MyClass() {  // Constructor
        cout << "Object created!" << endl;
    }

    ~MyClass() {  // Destructor
        cout << "Object destroyed!" << endl;
    }
};

int main() {
    MyClass obj;  // Constructor will be called here
    // Destructor will be called automatically when obj goes out of scope
    return 0;
}




10. Design Patterns:
Design patterns are reusable solutions to common software design problems. Here are examples of some design patterns:

Singleton: Ensures a class has only one instance and provides a global point of access to it.
Example: Singleton Pattern in C++:

#include <iostream>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    Singleton() {}  // Private constructor

public:
    static Singleton* getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;




11. Factory: Provides an interface for creating objects in a superclass but allows subclasses to alter the type of created objects.
Example: Factory Pattern in C++:

#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() { cout << "Drawing Circle\n"; }
};

class Square : public Shape {
public:
    void draw() { cout << "Drawing Square\n"; }
};

class ShapeFactory {
public:
    static Shape* getShape(const string& shapeType) {
        if (shapeType == "Circle")
            return new Circle();
        else if (shapeType == "Square")
            return new Square();
        return nullptr;
    }
};




12. Observer: A behavioral design pattern where an object (subject) maintains a list of its dependents (observers) and notifies them of state changes.
Example: Observer Pattern in C++:

#include <iostream>
#include <vector>
using namespace std;

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    
    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

class ConcreteObserver : public Observer {
private:
    string name;
public:
    ConcreteObserver(const string& n) : name(n) {}
    void update() override {
        cout << name << " has been notified!" << endl;
    }
};




13. Encapsulation:
Encapsulation is the concept of restricting direct access to some of an object's components and providing a controlled interface to access them.

Example:

#include <iostream>
using namespace std;

class BankAccount {
private:
    double balance;

public:
    BankAccount(double initialBalance) : balance(initialBalance) {}

    // Getter and setter for balance (Encapsulation)
    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0)
            balance += amount;
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance)
            balance -= amount;
    }
};




14. Exception Handling:
Exception handling in C++ allows you to respond to runtime errors and manage them without crashing the program. You use try, catch, and throw blocks for this purpose.

Definition:

try: Block of code to test for errors.
catch: Block of code to handle errors.
throw: Used to raise an exception.
Example:

#include <iostream>
#include <stdexcept>
using namespace std;

double divide(int a, int b) {
    if (b == 0)
        throw runtime_error("Division by zero is not allowed.");
    return a / double(b);
}




15. File I/O in OOP (Object-Oriented Programming):
File I/O allows you to read from and write to files. In C++, file operations are handled through the <fstream> library, which provides classes such as ifstream (for reading) and ofstream (for writing).

Example:

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileHandler {
public:
    void writeFile(const string& filename, const string& data) {
        ofstream outFile(filename);  // Open file for writing
        if (outFile.is_open()) {
            outFile << data;  // Write data to file
            outFile.close();
            cout << "Data written to file successfully.\n";
        } else {
            cout << "Failed to open file for writing.\n";
        }
    }

    void readFile(const string& filename) {
        ifstream inFile(filename);  // Open file for reading
        string line;
        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                cout << line << endl;  // Read and display each line
            }
            inFile.close();
        } else {
            cout << "Failed to open file for reading.\n";
        }
    }
};





16. Friends:
In C++, a friend function or class is a function or class that is granted access to the private and protected members of another class. The friend keyword is used to allow this special access.

Example:

#include <iostream>
using namespace std;

class Box {
private:
    double width;

public:
    Box(double w) : width(w) {}

    // Friend function
    friend void displayWidth(Box& b);
};

// Friend function definition
void displayWidth(Box& b) {
    cout << "Width of the box: " << b.width << endl;  // Can access private members
}




17. Generics and Templates:
In C++, templates allow you to write generic functions and classes that can work with any data type. This is similar to generics in other languages.

Example:

#include <iostream>
using namespace std;

// Template for a generic function
template <typename T>
T add(T a, T b) {
    return a + b;
}




18. Inheritance:
Inheritance is a mechanism in OOP where a new class derives properties and behaviors (methods) from an existing class. It supports the "is-a" relationship.

Example:

#include <iostream>
using namespace std;

class Animal {
public:
    void eat() {
        cout << "Eating...\n";
    }
};

class Dog : public Animal {  // Inheriting from Animal class
public:
    void bark() {
        cout << "Barking...\n";
    }
};




19. Instance Variable:
An instance variable is a variable that is specific to an instance (or object) of a class. It holds data unique to that instance.

Example:

#include <iostream>
using namespace std;

class Person {
public:
    string name;  // Instance variable

    Person(string n) : name(n) {}
};




20. Member Variable:
Member variables are variables declared inside a class. They can be either instance variables (specific to an object) or static variables (shared across all instances).

Example of Instance and Static Member Variables:

#include <iostream>
using namespace std;

class Counter {
private:
    static int count;  // Static member variable

public:
    Counter() {
        count++;  // Increment count for each instance created
    }

    static void displayCount() {
        cout << "Count: " << count << endl;
    }
};

int Counter::count = 0;  // Initializing static variable




21. Memory Management (Garbage Collection, Pointers):
In C++, memory management is done manually. Pointers are used to store memory addresses, and you can allocate and deallocate memory dynamically using new and delete. C++ does not have built-in garbage collection like Java, so memory must be explicitly freed.

Example:

#include <iostream>
using namespace std;

class MyClass {
public:
    MyClass() {
        cout << "Object created!" << endl;
    }

    ~MyClass() {
        cout << "Object destroyed!" << endl;
    }
};

Garbage Collection in C++: There is no automatic garbage collection in C++. It is the programmer's responsibility to free the memory using delete. However, modern C++ encourages the use of smart pointers (std::unique_ptr, std::shared_ptr) to manage memory automatically.




22. Method Overloading:
Method overloading occurs when multiple methods have the same name but different parameters (different number, types, or order of parameters). It is resolved at compile time (static polymorphism).

Example:

#include <iostream>
using namespace std;

class Print {
public:
    void show(int i) {
        cout << "Integer: " << i << endl;
    }

    void show(double d) {
        cout << "Double: " << d << endl;
    }

    void show(string s) {
        cout << "String: " << s << endl;
    }
};




23. Method:
A method is simply a function that is defined within a class and operates on objects of that class.

Example:

#include <iostream>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }

    int subtract(int a, int b) {
        return a - b;
    }
};




24. Multiple Inheritance:
Multiple inheritance occurs when a class inherits from more than one class. This allows a class to inherit features from multiple base classes.

Example:

#include <iostream>
using namespace std;

class Animal {
public:
    void eat() {
        cout << "Eating...\n";
    }
};

class Mammal {
public:
    void walk() {
        cout << "Walking...\n";
    }
};

class Dog : public Animal, public Mammal {  // Multiple inheritance
public:
    void bark() {
        cout << "Barking...\n";
    }
};




25. Multithreading in OOP:
Multithreading allows multiple threads of execution to run concurrently, improving program efficiency. In C++, multithreading is supported by the <thread> library.

Example:

#include <iostream>
#include <thread>
using namespace std;

void printHello() {
    cout << "Hello from thread!" << endl;
}





26. Object Relationships (Association, Aggregation, Composition):
Association: A relationship between two classes where one object of a class can interact with objects of another class.
Aggregation: A "has-a" relationship where one class contains objects of another class, but the contained objects can exist independently.
Composition: A "contains-a" relationship where one class contains objects of another class, and the contained objects cannot exist without the container.
Example:

#include <iostream>
using namespace std;

class Engine {
public:
    void start() {
        cout << "Engine started!" << endl;
    }
};

class Car {
private:
    Engine engine;  // Composition: Car has an Engine

public:
    void startCar() {
        engine.start();  // Calls Engine's method
        cout << "Car is running!" << endl;
    }
};




27. Object-Oriented Design Principles:
Key principles include:

Encapsulation: Wrapping data and methods into a single unit (class).
Abstraction: Hiding complex implementation details, exposing only essential features.
Inheritance: Reusing functionality from a base class.
Polymorphism: Using a unified interface for different data types.




28. Operator Overloading:
Operator overloading allows you to define custom behaviors for operators (e.g., +, -, <<, etc.) for user-defined types.

Example:

#include <iostream>
using namespace std;

class Complex {
private:
    int real, imag;

public:
    Complex(int r, int i) : real(r), imag(i) {}

    // Overloading the + operator
    Complex operator+(const Complex& obj) {
        return Complex(real + obj.real, imag + obj.imag);
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};




29. Overloading:
Overloading can refer to both method overloading (same method name, different parameters) and operator overloading (defining new behaviors for operators).

Method Overloading Example:

#include <iostream>
using namespace std;

class Printer {
public:
    void print(int i) {
        cout << "Printing integer: " << i << endl;
    }

    void print(double d) {
        cout << "Printing double: " << d << endl;
    }
};




30. Polymorphism:
Polymorphism allows you to use a single interface to represent different types. It can be either compile-time (method overloading and operator overloading) or runtime (using virtual functions).

Example (Runtime Polymorphism):

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() {
        cout << "Animal makes sound\n";
    }
};

class Dog : public Animal {
public:
    void sound() override {
        cout << "Dog barks\n";
    }
};




31. Public / Private / Protected:
Public: Members can be accessed from anywhere.
Private: Members can only be accessed within the class itself.
Protected: Members can be accessed by the class and derived classes.
Example:

#include <iostream>
using namespace std;

class MyClass {
private:
    int privateVar;

public:
    MyClass() : privateVar(10) {}

    void show() {
        cout << "Private variable: " << privateVar << endl;
    }
};




32. SOLID Principles:
The SOLID principles are a set of five design principles that help in writing clean and maintainable object-oriented code:

S - Single Responsibility Principle (SRP): A class should have only one reason to change.
O - Open/Closed Principle (OCP): A class should be open for extension but closed for modification.
L - Liskov Substitution Principle (LSP): Objects of a derived class should be able to replace objects of the base class without affecting the correctness of the program.
I - Interface Segregation Principle (ISP): Clients should not be forced to depend on interfaces they do not use.
D - Dependency Inversion Principle (DIP): High-level modules should not depend on low-level modules. Both should depend on abstractions.




33. Static (Methods and Variables):
Static Variables: Shared by all instances of a class.
Static Methods: Can be called without an instance of the class.
Example:

#include <iostream>
using namespace std;

class Counter {
public:
    static int count;  // Static member variable

    Counter() {
        count++;
    }

    static void displayCount() {
        cout << "Count: " << count << endl;
    }
};

int Counter::count = 0;  // Initialize static variable




34. Testing in OOP:
Unit Testing: The process of testing individual units of code (like methods or functions) to ensure they work as expected.
Test-Driven Development (TDD): A development process where you write tests before you write the actual code.
Example using a simple unit test:

#include <iostream>
#include <cassert>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
};

int main() {
    Calculator calc;
    // Unit Test: Test the add function
    assert(calc.add(2, 3) == 5);
    assert(calc.add(-1, 1) == 0);
    cout << "All tests passed!" << endl;
    return 0;
}




35. UML Diagrams and Modeling:
UML (Unified Modeling Language) is used to visualize the design of a system. Common diagrams include:

Class Diagrams: Show the classes, their attributes, methods, and relationships.
Sequence Diagrams: Represent object interactions over time.
Use Case Diagrams: Represent the interaction between users and the system.
Example of a simple Class Diagram for the Dog and Animal classes:

+-----------------+        +-------------------+
|    Animal      |        |       Dog         |
|-----------------|        |-------------------|
| - sound()      |<-------| + sound()         |
|-----------------|        +-------------------+




36. Virtual (with Definition and Example Code in C++):
The virtual keyword in C++ is used to allow derived classes to override methods of the base class. It is key to achieving runtime polymorphism.

Example:

#include <iostream>
using namespace std;

class Base {
public:
    virtual void display() {  // Virtual method
        cout << "Base class";
