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

