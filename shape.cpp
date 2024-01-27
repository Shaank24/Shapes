// This file contains all implementation functions for shape.h
// It actually creates the description/information for the shapes

// must include in order to use class declarations in shape.h
#include "shape.h"
using namespace std;

// BASIC SHAPE CLASS STARTS HERE
Shape::Shape() : x(0), y(0) {}

Shape::Shape(int x, int y) : x(x), y(y) {}

Shape::~Shape() {}

Shape* Shape::copy() {
    return new Shape(x, y);
}

int Shape::getX() const{
    return x;
}

int Shape::getY() const{
    return y;
}

void Shape::setX(int x) {
    this->x = x;
}

void Shape::setY(int y) {
    this->y = y;
}

string Shape::printShape() const {
    return "It's a Shape at x: " + to_string(x) + ", y: " + to_string(y);
}
// BASIC SHAPE CLASS ENDS HERE

// RECTANGLE CLASS STARTS HERE
Rect::Rect() : width(0), height(0) {}

Rect::Rect(int w, int h) : width(w), height(h) {}

Rect::Rect(int x, int y, int w, int h) : Shape(x, y), width(w), height(h) {}

Rect::~Rect() {}

Rect* Rect::copy() {
    return new Rect(x, y, width, height);
}

int Rect::getWidth() const {
    return width;
}

int Rect::getHeight() const {
    return height;
}

void Rect::setWidth(int w) {
    width = w;
}

void Rect::setHeight(int h) {
    height = h;
}

string Rect::printShape() const {
    return "It's a Rectangle at x: " + to_string(x) + ", y: " + to_string(y) + " with width: " + to_string(width) + " and height: " + to_string(height);
}
// RECTANGLE CLASS ENDS HERE

// CIRCLE CLASS STARTS HERE
Circle::Circle() : radius(0) {}

Circle::Circle(int r) : radius(r) {}

Circle::Circle(int x, int y, int r){
    this->x = x;
    this->y = y;
    this->radius = r;
}

Circle::~Circle() {}

Circle* Circle::copy() {
    return new Circle(x, y, radius);
}

int Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(int r) {
    radius = r;
}

string Circle::printShape() const {
    return "It's a Circle at x: " + to_string(getX()) + ", y: " + to_string(getY()) + ", radius: " + to_string(radius);
}
// CIRCLE CLASS ENDS HERE

// RIGHT TRIANGLE CLASS STARTS HERE
RightTriangle::RightTriangle() : base(0), height(0) {}

RightTriangle::RightTriangle(int b, int h) : base(b), height(h) {}

RightTriangle::RightTriangle(int x, int y, int b, int h) : Shape(x,y), base(b), height(h) {}

RightTriangle::~RightTriangle() {}

RightTriangle* RightTriangle::copy() {
    return new RightTriangle(x, y, base, height);
}

int RightTriangle::getBase() const {
    return base;
}

int RightTriangle::getHeight() const {
    return height;
}

void RightTriangle::setBase(int b) {
    base = b;
}

void RightTriangle::setHeight(int h) {
    height = h;
}

string RightTriangle::printShape() const {
    return "It's a Right Triangle at x: " + to_string(getX()) + ", y: " + to_string(getY()) + " with base: " + to_string(base) + " and height: " + to_string(height);
}
// RIGHT TRIANGLE CLASS ENDS HERE