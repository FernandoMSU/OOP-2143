#include <iostream>
#include <numeric>  // For std::gcd
#include <cmath>    // For std::abs

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;
  
    // Helper function to simplify the fraction
    void simplify() {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0) { // Ensure denominator is positive
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Function to calculate Least Common Multiple (LCM)
    static int lcm(int a, int b) {
        return std::abs(a * b) / std::gcd(a, b);
    }

public:
    // Constructor
    Fraction(int num, int den) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        simplify();
    }

    // Overloaded addition operator
    Fraction operator+(const Fraction& other) const {
        int common_denominator = lcm(denominator, other.denominator);
        int adjusted_numerator1 = numerator * (common_denominator / denominator);
        int adjusted_numerator2 = other.numerator * (common_denominator / other.denominator);
        int result_numerator = adjusted_numerator1 + adjusted_numerator2;
        return Fraction(result_numerator, common_denominator);
    }

    // Overloaded subtraction operator
    Fraction operator-(const Fraction& other) const {
        int common_denominator = lcm(denominator, other.denominator);
        int adjusted_numerator1 = numerator * (common_denominator / denominator);
        int adjusted_numerator2 = other.numerator * (common_denominator / other.denominator);
        int result_numerator = adjusted_numerator1 - adjusted_numerator2;
        return Fraction(result_numerator, common_denominator);
    }

    // Overloaded multiplication operator
    Fraction operator*(const Fraction& other) const {
        int result_numerator = numerator * other.numerator;
        int result_denominator = denominator * other.denominator;
        return Fraction(result_numerator, result_denominator);
    }

    // Overloaded division operator
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Cannot divide by zero.");
        }
        int result_numerator = numerator * other.denominator;
        int result_denominator = denominator * other.numerator;
        return Fraction(result_numerator, result_denominator);
    }

    // Overloaded equality operator (==)
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Overload output operator (<<) for printing fractions
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }
};

int main() {
    try {
        Fraction frac1(1, 2);
        Fraction frac2(3, 4);

        Fraction result_add = frac1 + frac2;  // Calls the overloaded + operator
        Fraction result_sub = frac1 - frac2;  // Calls the overloaded - operator
        Fraction result_mul = frac1 * frac2;  // Calls the overloaded * operator
        Fraction result_div = frac1 / frac2;  // Calls the overloaded / operator

        cout << "Addition: " << result_add << endl;
        cout << "Subtraction: " << result_sub << endl;
        cout << "Multiplication: " << result_mul << endl;
        cout << "Division: " << result_div << endl;
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
//Chat GPT helped with missing code I had trouble solving. 
