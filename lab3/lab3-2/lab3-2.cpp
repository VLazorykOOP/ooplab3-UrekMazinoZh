#include <iostream>

using namespace std;

class Vector {
private:
    unsigned int* data;
    unsigned int size;
    int state; // ��� �����: 0 - ������, ������ - �������

public:
    static int objectCount; 

    // ����������� ��� ���������
    Vector() : size(1), state(0) {
        data = new unsigned int[size];
        if (!data) state = 1; // ������� �������� ���'��
        else data[0] = 0;
        objectCount++;
    }

    // ����������� � ����� ���������� - ����� �������
    Vector(unsigned int n) : size(n), state(0) {
        data = new unsigned int[size];
        if (!data) state = 1; // ������� �������� ���'��
        else {
            for (unsigned int i = 0; i < size; i++) {
                data[i] = 0;
            }
        }
        objectCount++;
    }

    // ����������� �� ����� ����������� - ����� ������� �� �������� �����������
    Vector(unsigned int n, unsigned int value) : size(n), state(0) {
        data = new unsigned int[size];
        if (!data) state = 1; // ������� �������� ���'��
        else {
            for (unsigned int i = 0; i < size; i++) {
                data[i] = value;
            }
        }
        objectCount++;
    }

    // ����������� ����
    Vector(const Vector& other) : size(other.size), state(other.state) {
        data = new unsigned int[size];
        if (!data) state = 1; // ������� �������� ���'��
        else {
            for (unsigned int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        objectCount++;
    }

    // �������� ���������
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            state = other.state;
            data = new unsigned int[size];
            if (!data) state = 1; // ������� �������� ���'��
            else {
                for (unsigned int i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
        }
        return *this;
    }

    // ����������
    ~Vector() {
        delete[] data;
        objectCount--;
    }

    // ������� ��������� �������� �������� ������
    void setElement(unsigned int index, unsigned int value = 0) {
        if (index < size) {
            data[index] = value;
            state = 0;
        }
        else {
            state = 2; // ����� �� ��� ������
        }
    }

    // ������� ��������� �������� �������� ������
    unsigned int getElement(unsigned int index) const {
        if (index < size) {
            return data[index];
        }
        else {
            return 0; // ���������� �������� �� ������ ������
        }
    }

    // ������� �����
    void print() const {
        for (unsigned int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // ������� ���������
    Vector operator+(const Vector& other) const {
        Vector result(size, 0);
        for (unsigned int i = 0; i < size; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // ������� ��������
    Vector operator-(const Vector& other) const {
        Vector result(size, 0);
        for (unsigned int i = 0; i < size; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // ������� �������� �� ���� �����
    Vector operator*(unsigned short scalar) const {
        Vector result(size, 0);
        for (unsigned int i = 0; i < size; i++) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    // ������� ���������
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

    // ������� ��� ��������� �����
    int getState() const {
        return state;
    }
};

// ����������� �������� �����
int Vector::objectCount = 0;

int main() {

    // ����������� ��� ���������
    Vector v1;
    cout << "Vector 1: ";
    v1.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // ����������� � ����� ����������
    Vector v2(5);
    cout << "Vector 2: ";
    v2.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // ����������� �� ����� �����������
    Vector v3(3, 10);
    cout << "Vector 3: ";
    v3.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // ����������� ���� �� �������� ���������
    Vector v4 = v3;
    cout << "Vector 4 (copy of Vector 3): ";
    v4.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    Vector v5;
    v5 = v2;
    cout << "Vector 5 (assigned Vector 2): ";
    v5.print();
    cout << "Object Count: " << Vector::objectCount << endl;

    // ������� ��������� �� ��������� �������� �������� ������
    v2.setElement(2, 7);
    cout << "Element at index 2 in Vector 2: " << v2.getElement(2) << endl;

    // ������� �����, ���������, ��������, ��������
    cout << "Vector 2 + Vector 3: ";
    (v2 + v3).print();

    cout << "Vector 3 - Vector 2: ";
    (v3 - v2).print();

    cout << "Vector 3 * 2: ";
    (v3 * 2).print();

    // ������� ���������
    cout << "Is Vector 2 > Vector 3? " << (v2 > v3) << endl;
    cout << "Is Vector 3 < Vector 2? " << (v3 < v2) << endl;
    cout << "Are Vector 2 and Vector 3 equal? " << (v2 == v3) << endl;

    // ������������ ������� �������
    Vector v6(2, 5);
    cout << "Vector 6: ";
    v6.print();
    cout << "Object Count: " << Vector::objectCount << endl;
    v6.setElement(5, 3);
    cout << "State of Vector 6: " << v6.getState() << endl; // ��������� �����

    return 0;
}
