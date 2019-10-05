/*
RUN: g++ -std=c++17 abstraction_polymorphism.cpp && ./a.out
Just to shoqw how abstraction and polymorphism is interconnected
*/

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class Polygon {
public:
    Polygon(double width, double height) : width(width), height(height) {}
    virtual double area() = 0;
    void printArea(){
        cout << this->area() << endl;
    }
protected:
    double width, height;
};

class Rectangle : public Polygon {
public:
    Rectangle(double width, double height) : Polygon(width, height) {}
    double area() override {
        return width * height ;
    }
};
class Triangle : public Polygon {
public:
    Triangle(double width, double height) : Polygon(width, height) {}
    double area() override {
        return 0.5 * width * height ;
    }
};



int main() {

    auto poly1 = std::make_unique<Rectangle>(2, 4);
    std::unique_ptr<Polygon> poly2 = std::make_unique<Triangle>(2, 4);

    poly1->printArea();
    poly2->printArea();

    return 0;
}