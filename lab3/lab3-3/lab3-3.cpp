#include <iostream>

using namespace std;

class Vector {
private:
    double* data;
    int size;
public:
    // Конструктори
    Vector() : data(new double[5] {}), size(5) {}

    Vector(int n) : data(new double[n] {}), size(n) {}

    Vector(int n, double value) : data(new double[n]), size(n) {
        for (int i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    // Конструктор копії
    Vector(const Vector& other) : data(new double[other.size]), size(other.size) {
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new double[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
    }

    // Функція для отримання елементу за індексом
    double getElement(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        else {
            cerr << "Error: Index out of bounds\n";
            return 0.0;
        }
    }

    // Функція для встановлення значення для елементу за індексом
    void setElement(int index, double value = 0.0) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
        else {
            cerr << "Error: Index out of bounds\n";
        }
    }

    // Функція друку вектора
    void print() const {
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

class Matrix {
private:
    Vector* vectors;
    int rows;
    int cols;
    int errorState;  // 0 - No error, 1 - Out of memory, 2 - Division by zero, 3 - Index out of bounds
public:
    // Конструктори
    Matrix() : vectors(new Vector[5]), rows(5), cols(5), errorState(0) {}

    Matrix(int n) : vectors(new Vector[n]), rows(n), cols(n), errorState(0) {}

    Matrix(int n, int m, double value) : vectors(new Vector[m]), rows(n), cols(m), errorState(0) {
        for (int i = 0; i < m; ++i) {
            vectors[i] = Vector(n, value);
        }
    }

    // Деструктор
    ~Matrix() {
        delete[] vectors;
    }

    // Функції друку матриці
    void print() const {
        for (int i = 0; i < rows; ++i) {
            vectors[i].print();
        }
    }

    // Функції арифметичних операцій
    Matrix add(const Matrix& other) const {
        if (rows == other.rows && cols == other.cols) {
            Matrix result(rows, cols, 0.0);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.vectors[i].setElement(j, vectors[i].getElement(j) + other.vectors[i].getElement(j));
                }
            }
            return result;
        }
        else {
            cerr << "Error: Matrix dimensions do not match for addition\n";
            return Matrix();
        }
    }

    Matrix multiply(const Matrix& other) const {
        if (cols == other.rows) {
            Matrix result(rows, other.cols, 0.0);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < other.cols; ++j) {
                    for (int k = 0; k < cols; ++k) {
                        result.vectors[i].setElement(j,
                            result.vectors[i].getElement(j) + vectors[i].getElement(k) * other.vectors[k].getElement(j));
                    }
                }
            }
            return result;
        }
        else {
            cerr << "Error: Matrix dimensions do not match for multiplication\n";
            return Matrix();
        }
    }

    Matrix subtract(const Matrix& other) const {
        if (rows == other.rows && cols == other.cols) {
            Matrix result(rows, cols, 0.0);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.vectors[i].setElement(j, vectors[i].getElement(j) - other.vectors[i].getElement(j));
                }
            }
            return result;
        }
        else {
            cerr << "Error: Matrix dimensions do not match for subtraction\n";
            return Matrix();
        }
    }

    Matrix divide(int scalar) const {
        if (scalar != 0) {
            Matrix result(rows, cols, 0.0);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.vectors[i].setElement(j, vectors[i].getElement(j) / scalar);
                }
            }
            return result;
        }
        else {
            cerr << "Error: Division by zero\n";
            return Matrix();
        }
    }

    // Функції порівняння
    bool operator>(const Matrix& other) const {
        return (rows * cols) > (other.rows * other.cols);
    }

    bool operator<(const Matrix& other) const {
        return (rows * cols) < (other.rows * other.cols);
    }

    bool operator!=(const Matrix& other) const {
        return (rows * cols) != (other.rows * other.cols);
    }
};

int main() {
    Vector v1;
    Vector v2(3);
    Vector v3(4, 2.5);
    Vector v4 = v3; 

    cout << "Vector 1: ";
    v1.print();

    cout << "Vector 2: ";
    v2.print();

    cout << "Vector 3: ";
    v3.print();

    cout << "Vector 4 (copy of Vector 3): ";
    v4.print();

    v2.setElement(1, 10.0);
    cout << "Vector 2 after setting element at index 1 to 10.0: ";
    v2.print();

    cout << "Element at index 2 in Vector 3: " << v3.getElement(2) << endl;

    Matrix m1;
    Matrix m2(2);
    Matrix m3(3, 4, 1.5);
    Matrix m4 = m3;  

    cout << "Matrix 1:\n";
    m1.print();

    cout << "Matrix 2:\n";
    m2.print();

    cout << "Matrix 3:\n";
    m3.print();

    cout << "Matrix 4 (copy of Matrix 3):\n";
    m4.print();

    Matrix resultAdd = m2.add(m3);
    cout << "Matrix 2 + Matrix 3:\n";
    resultAdd.print();

    Matrix resultMultiply = m2.multiply(m3);
    cout << "Matrix 2 * Matrix 3:\n";
    resultMultiply.print();

    Matrix resultSubtract = m3.subtract(m2);
    cout << "Matrix 3 - Matrix 2:\n";
    resultSubtract.print();

    Matrix resultDivide = m3.divide(2);
    cout << "Matrix 3 / 2:\n";
    resultDivide.print();

    // Тестування функцій порівняння
    cout << "Matrix 2 > Matrix 3: " << (m2 > m3) << endl;
    cout << "Matrix 2 < Matrix 3: " << (m2 < m3) << endl;
    cout << "Matrix 2 != Matrix 3: " << (m2 != m3) << endl;

    return 0;
}
