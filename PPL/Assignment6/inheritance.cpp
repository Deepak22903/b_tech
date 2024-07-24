#include <iostream>
#include <cmath>

using namespace std;

class Shape {
public:
    virtual double area() const = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}

    double area() const override {
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
};

class Square : public Shape {
private:
    double side;

public:
    Square(double s) : side(s) {}

    double area() const override {
        return side * side;
    }
};

class Polygon : public Shape {
protected:
    int sides;
    double sideLength;

public:
    Polygon(int s, double length) : sides(s), sideLength(length) {}

    double area() const override {
        return (sides * sideLength * sideLength) / (4 * tan(M_PI / sides));
    }
};

class Octagon : public Polygon {
public:
    Octagon(double sideLength) : Polygon(8, sideLength) {}
};

int main() {
    double radius, side1, side2, side3, squareSide, polygonSide, octagonSide;

    cout << "Enter the radius of the circle: ";
    cin >> radius;

    cout << "Enter the three side lengths of the triangle: ";
    cin >> side1 >> side2 >> side3;

    cout << "Enter the side length of the square: ";
    cin >> squareSide;

    cout << "Enter the number of sides for the polygon: ";
    cin >> polygonSide;

    cout << "Enter the side length of the octagon: ";
    cin >> octagonSide;

    Circle circle(radius);
    Triangle triangle(side1, side2, side3);
    Square square(squareSide);
    Polygon polygon(polygonSide, 4.0);
    Octagon octagon(octagonSide);

    cout << "Circle Area: " << circle.area() << endl;
    cout << "Triangle Area: " << triangle.area() << endl;
    cout << "Square Area: " << square.area() << endl;
    cout << "Polygon Area: " << polygon.area() << endl;
    cout << "Octagon Area: " << octagon.area() << endl;

    return 0;
}
