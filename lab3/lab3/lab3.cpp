#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class Square {
private:
    double side;
    string color;

public:
    // Конструктор за замовчуванням
    Square() : side(0), color("white") {}

    // Конструктор з параметрами
    Square(double s, const string& c) : side(s), color(c) {
        if (s <= 0) {
            throw invalid_argument("Side must be a positive number.");
        }
    }

    double calculateArea() const {
        return side * side;
    }

    double calculatePerimeter() const {
        return 4 * side;
    }

    double calculateCircumcircleRadius() const {
        return side * sqrt(2) / 2;
    }

    double calculateIncircleRadius() const {
        return side / 2;
    }

    // Функції-члени встановлення значення сторони та кольору
    void setSide(double s) {
        if (s <= 0) {
            throw invalid_argument("Side must be a positive number.");
        }
        side = s;
    }

    void setColor(const string& c) {
        color = c;
    }

    double getSide() const {
        return side;
    }

    string getColor() const {
        return color;
    }
    void print() const {
        cout << "Square - Side: " << side << ", Color: " << color << endl;
    }
};

int main() {
    try {
        Square square1(5, "blue");
        square1.print();

        cout << "Area: " << square1.calculateArea() << endl;
        cout << "Perimeter: " << square1.calculatePerimeter() << endl;
        cout << "Circumcircle Radius: " << square1.calculateCircumcircleRadius() << endl;
        cout << "Incircle Radius: " << square1.calculateIncircleRadius() << endl;

        square1.setSide(8);
        square1.setColor("red");

        cout << "\nAfter Modification:" << endl;
        square1.print();

        // Спроба створення квадрата з некоректною стороною
        Square square2(-3, "green"); // Генерує виключення invalid_argument

    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
