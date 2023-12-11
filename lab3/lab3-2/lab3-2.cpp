#include <iostream>

using namespace std;

class Vector {
private:
    unsigned int* data;
    unsigned int size;
    int state; // Код стану: 0 - успішно, інакше - помилка

public:
    static int objectCount; 

    // Конструктор без параметрів
    Vector() : size(1), state(0) {
        data = new unsigned int[size];
        if (!data) state = 1; // Помилка виділення пам'яті
        else data[0] = 0;
        objectCount++;
    }

    // Конструктор з одним параметром - розмір вектора
    Vector(unsigned int n) : size(n), state(0) {
        data = new unsigned int[size];
        if (!data) state = 1; // Помилка виділення пам'яті
        else {
            for (unsigned int i = 0; i < size; i++) {
                data[i] = 0;
            }
        }
        objectCount++;
    }

    // Конструктор із двома параметрами - розмір вектора та значення ініціалізації
    Vector(unsigned int n, unsigned int value) : size(n), state(0) {
        data = new unsigned int[size];
        if (!data) state = 1; // Помилка виділення пам'яті
        else {
            for (unsigned int i = 0; i < size; i++) {
                data[i] = value;
            }
        }
        objectCount++;
    }

    // Конструктор копій
    Vector(const Vector& other) : size(other.size), state(other.state) {
        data = new unsigned int[size];
        if (!data) state = 1; // Помилка виділення пам'яті
        else {
            for (unsigned int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        objectCount++;
    }

    // Операція присвоєння
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            state = other.state;
            data = new unsigned int[size];
            if (!data) state = 1; // Помилка виділення пам'яті
            else {
                for (unsigned int i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
        }
        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
        objectCount--;
    }

    // Функція присвоєння значення елементу масиву
    void setElement(unsigned int index, unsigned int value = 0) {
        if (index < size) {
            data[index] = value;
            state = 0;
        }
        else {
            state = 2; // Вихід за межі масиву
        }
    }

    // Функція отримання значення елементу масиву
    unsigned int getElement(unsigned int index) const {
        if (index < size) {
            return data[index];
        }
        else {
            return 0; // Повернення значення за межами масиву
        }
    }

    // Функція друку
    void print() const {
        for (unsigned int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Функція додавання
    Vector operator+(const Vector& other) const {
        Vector result(size, 0);
        for (unsigned int i = 0; i < size; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Функція віднімання
    Vector operator-(const Vector& other) const {
        Vector result(size, 0);
        for (unsigned int i = 0; i < size; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Функція множення на ціле число
    Vector operator*(unsigned short scalar) const {
        Vector result(size, 0);
        for (unsigned int i = 0; i < size; i++) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    // Функції порівняння
    bool operator>(const Vector& other) const {
        for (unsigned int i = 0; i < size; i++) {
            if (data[i] <= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const Vector& other) const {
        for (unsigned int i = 0; i < size; i++) {
            if (data[i] >= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const Vector& other) const {
        for (unsigned int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    // Функція для отримання стану
    int getState() const {
        return state;
    }
};

// Ініціалізація статичної змінної
int Vector::objectCount = 0;

int main() {

    // Конструктор без параметрів
    Vector v1;
    cout << "Vector 1: ";
    v1.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // Конструктор з одним параметром
    Vector v2(5);
    cout << "Vector 2: ";
    v2.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // Конструктор із двома параметрами
    Vector v3(3, 10);
    cout << "Vector 3: ";
    v3.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // Конструктор копій та операція присвоєння
    Vector v4 = v3;
    cout << "Vector 4 (copy of Vector 3): ";
    v4.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    Vector v5;
    v5 = v2;
    cout << "Vector 5 (assigned Vector 2): ";
    v5.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // Функції присвоєння та отримання значення елементу масиву
    v2.setElement(2, 7);
    cout << "Element at index 2 in Vector 2: " << v2.getElement(2) << endl;

    // Функції друку, додавання, віднімання, множення
    cout << "Vector 2 + Vector 3: ";
    (v2 + v3).print();

    cout << "Vector 3 - Vector 2: ";
    (v3 - v2).print();

    cout << "Vector 3 * 2: ";
    (v3 * 2).print();

    // Функції порівняння
    cout << "Is Vector 2 > Vector 3? " << (v2 > v3) << endl;
    cout << "Is Vector 3 < Vector 2? " << (v3 < v2) << endl;
    cout << "Are Vector 2 and Vector 3 equal? " << (v2 == v3) << endl;

    // Демонстрація обробки помилок
    Vector v6(2, 5);
    cout << "Vector 6: ";
    v6.print();
    cout << "Object Count: " << Vector::objectCount << endl;
    v6.setElement(5, 3);
    cout << "State of Vector 6: " << v6.getState() << endl; // Отримання стану

    return 0;
}
