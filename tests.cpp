/// @file tests.cpp
/// @author NO NAME
/// @date October 2, 2023
/// @brief Provided testing file to implement Catch 1.x framework tests. 
///   The example below uses the Catch testing framework version that uses
///   a single .hpp file. Initial file authored by:
///   Adam T Koehler, PhD - University of Illinois Chicago

// The tutorial for Catch 1.x can be found at:
// https://github.com/catchorg/Catch2/blob/Catch1.x/docs/tutorial.md

// This tells Catch to provide a main() - do not remove
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "shape.h"
#include "canvaslist.h"

using namespace std;

// TEST CASE FOR THE BASIC SHAPE CLASS IN MILESTONE 1
TEST_CASE("Basic Shape Class Tests (Milestone 1)") {

  // MAKES SURE DEFAULT CONSTRUCTOR SETS X AND Y TO 0
  SECTION("Default Constructor") {
    Shape shape;
    REQUIRE(shape.getX() == 0);
    REQUIRE(shape.getY() == 0);
    REQUIRE(shape.printShape() == "It's a Shape at x: 0, y: 0");
  }

  // MAKES SURE PARAMETERIZED CONSTRUCTOR WORKS CORRECTLY
  SECTION("Parameter Constructor") {
    // creates new shape object with random points
    Shape *shape = new Shape(1, 2);

    // cleans up the dynamically allocated memory
    delete shape;
  }

  // MAKES SURE THIS FUNCTION PROPERLY COPIES 
  SECTION("Copy Function") {
    // creates a shape object with random points
    Shape shape1(1, 2);

    // uses copy function to copy over points from shape1
    Shape *shape2 = shape1.copy();

    // makes sure that the x and y points for shape1 and shape2 are identical
    REQUIRE(shape1.getX() == shape2->getX());
    REQUIRE(shape1.getY() == shape2->getY());

    // cleans up the dynamically allocated memory
    delete shape2;
  }

  // MAKES SURE ALL SETTERS/GETTERS SET AND RETURN THE CORRECT VALUE
  SECTION("Setters/Getters") {

    // creates new object and sets x and y with points
    Shape shape;
    shape.setX(3);
    shape.setY(4);

    // makes sure that the getters correctly get the values from the setters and print out those values
    REQUIRE(shape.getX() == 3);
    REQUIRE(shape.getY() == 4);
    REQUIRE(shape.printShape() == "It's a Shape at x: 3, y: 4");
  }
}

TEST_CASE("Canvas List Class Tests (Milestone 2)") {
  SECTION("Default Constructor") {

    // makes sure that initial size is 0 and list is empty
    CanvasList canvas;
    REQUIRE(canvas.size() == 0);
    REQUIRE(canvas.isempty() == true);
  }

  SECTION("Copy Constructor") {

    // creates the original canvas and adds shapes to it
    CanvasList original;
    original.push_back(new Shape(1, 2));
    original.push_back(new Shape(3, 4));

    // creates copy canvas and makes sure size matches the original canvas
    CanvasList copy(original);
    REQUIRE(original.size() == copy.size());

    // initialize pinters to both original and copy nodes
    ShapeNode* origNode = original.front();
    ShapeNode* copyNode = copy.front();

    // makes sure the values of x,y match for both the original and copy nodes
    while (origNode != nullptr && copyNode != nullptr) {
      REQUIRE(copyNode->value->getX() == origNode->value->getX());
      REQUIRE(copyNode->value->getY() == origNode->value->getY());
      origNode = origNode->next;
      copyNode = copyNode->next;
      
    }
  }

  SECTION("Assignment Operator") {

    // creates original canvas and adds shape to it
    CanvasList origList;
    origList.push_back(new Shape(10, 11));

    // creates empty canvas and uses assingment operator to copy original
    CanvasList copyList;
    copyList = origList;

    // makes sure size between copy and original are same 
    REQUIRE(copyList.size() == origList.size());

    
    ShapeNode* origNode = origList.front();
    ShapeNode* copyNode = copyList.front();

    // traverses through copy and original nodes and makes sure x,y are same
    while (origNode != nullptr && copyNode != nullptr) {
      REQUIRE(copyNode->value != origNode->value);

      REQUIRE(copyNode->value->getX() == origNode->value->getX());
      REQUIRE(copyNode->value->getY() == origNode->value->getY());

      origNode = origNode->next;
      copyNode = copyNode->next;
    }
  }

  SECTION("clear Function") {

    // adds shapes to new canvasList
    CanvasList canvas;
    canvas.push_back(new Shape(1, 2));
    canvas.push_back(new Shape(7, 8));
  
    // makes sure canvas size is 0 after you clear it
    canvas.clear();
    REQUIRE(canvas.size() == 0);

  }

  SECTION("insertAfter Function") {

    // adds shape to canvas
    CanvasList canvas;
    canvas.push_back(new Shape(10, 20));
    canvas.push_back(new Shape(5, 7));

    // gets initial size of the canvas
    int initSize = canvas.size();

    // creates a new shape to add 
    Shape* newShape = new Shape(3, 4);

    // tests insertAfter function by adding new shape 
    canvas.insertAfter(0, newShape);

    // makes sure canvas size is now the initial size plus 1 for the added shape
    REQUIRE(canvas.size() == initSize + 1);

  }

  SECTION("push_front Function") {
    CanvasList canvas;

    // creates 3 new shapes
    Shape* shape1 = new Shape(1, 2);
    Shape* shape2 = new Shape(2, 3);
    Shape* shape3 = new Shape(4, 7);

    // pushes shapes to the front of list
    canvas.push_front(shape1);
    canvas.push_front(shape2);
    canvas.push_front(shape3);

    // makes sure size of canvas is 3 and that the most recent push_front shape is at the beginning of list
    REQUIRE(canvas.size() == 3);
    REQUIRE(canvas.shapeAt(0)->getX() == shape3->getX());
    REQUIRE(canvas.shapeAt(0)->getY() == shape3->getY());
    REQUIRE(canvas.shapeAt(1)->getX() == shape2->getX());
    REQUIRE(canvas.shapeAt(1)->getY() == shape2->getY());
    REQUIRE(canvas.shapeAt(2)->getX() == shape1->getX());
    REQUIRE(canvas.shapeAt(2)->getY() == shape1->getY());
    
  }

  SECTION("push_back Function") {
    CanvasList canvas;

    // creates 3 new shapes
    Shape* shape1 = new Shape();
    Shape* shape2 = new Shape();
    Shape* shape3 = new Shape();

    // pushes shapes to the end of list
    canvas.push_back(shape1);
    canvas.push_back(shape2);
    canvas.push_back(shape3);

    // makes sure size of canvas is 3 and that every shape that is pushed back is at end of list
    REQUIRE(canvas.size() == 3);
    REQUIRE(canvas.shapeAt(0) == shape1);
    REQUIRE(canvas.shapeAt(1) == shape2);
    REQUIRE(canvas.shapeAt(2) == shape3);

  }

  SECTION("removeAt Function") {
    CanvasList canvas;

    // creates 3 new shapes
    Shape* shape1 = new Shape();
    Shape* shape2 = new Shape();
    Shape* shape3 = new Shape();

    // pushes shapes to the end of list
    canvas.push_back(shape1);
    canvas.push_back(shape2);
    canvas.push_back(shape3);

    // removes 2/3 elements in canvas1 list
    canvas.removeAt(1);
    canvas.removeAt(1);

    // makes sure size of canvas is correct when you remove a few elements or if you remove all elements
    // makes sure elements remaining are correct
    REQUIRE(canvas.size() == 1);
    REQUIRE(canvas.shapeAt(0) == shape1);

  }

  SECTION("removeEveryOther Function") {
    CanvasList canvas;
    
    // creates 5 new shapes
    Shape* shape1 = new Shape();
    Shape* shape2 = new Shape();
    Shape* shape3 = new Shape();
    Shape* shape4 = new Shape();
    Shape* shape5 = new Shape();

    // pushes all shapes back to canvas list
    canvas.push_back(shape1);
    canvas.push_back(shape2);
    canvas.push_back(shape3);
    canvas.push_back(shape4);
    canvas.push_back(shape5);

    // calls the function
    canvas.removeEveryOther();

    // checks that correct shapes were removed (shapes 2 and 4) and that the remaining 3 shapes are in correct index
    REQUIRE(canvas.size() == 3);
    REQUIRE(canvas.shapeAt(0)->getX() == shape1->getX());
    REQUIRE(canvas.shapeAt(0)->getY() == shape1->getY());
    REQUIRE(canvas.shapeAt(1)->getX() == shape3->getX());
    REQUIRE(canvas.shapeAt(1)->getY() == shape3->getY());
    REQUIRE(canvas.shapeAt(2)->getX() == shape5->getX());
    REQUIRE(canvas.shapeAt(2)->getY() == shape5->getY());
    
  }

  SECTION("pop_front Function") {
    CanvasList canvas;

    // creates new shapes and pushes them into canvas list
    Shape* shape1 = new Shape();
    Shape* shape2 = new Shape();
    Shape* shape3 = new Shape();
    canvas.push_back(shape1);
    canvas.push_back(shape2);
    canvas.push_back(shape3);

    // gets access to the popped shape
    Shape* frontShapePopped = canvas.pop_front();

    // makes sure the popped shape was the front element and the size of canvas remaining is 2
    REQUIRE(canvas.size() == 2);
    REQUIRE(frontShapePopped == shape1);
    REQUIRE(canvas.shapeAt(0) == shape2);
    REQUIRE(canvas.shapeAt(1) == shape3);

    // deallocates memory
    delete frontShapePopped;
  }

  SECTION("pop_back Function") {
    CanvasList canvas;

    // creates new shapes and pushes them into canvas list
    Shape* shape1 = new Shape();
    Shape* shape2 = new Shape();
    Shape* shape3 = new Shape();
    canvas.push_back(shape1);
    canvas.push_back(shape2);
    canvas.push_back(shape3);

    // gets access to the popped shape
    Shape* backShapePopped = canvas.pop_back();

    // makes sure the popped shape was the back element and the size of canvas remaining is 1
    REQUIRE(canvas.size() == 2);
    REQUIRE(backShapePopped == shape3);
    REQUIRE(canvas.shapeAt(0) == shape1);
    REQUIRE(canvas.shapeAt(1) == shape2);

    // deallocates memory
    delete backShapePopped;
  }

  SECTION("front Function") {
    CanvasList canvas;

    // creates new shapes and pushes them into canvas list
    Shape* shape1 = new Shape();
    Shape* shape2 = new Shape();
    canvas.push_back(shape1);
    canvas.push_back(shape2);

    // gets access to the front shape in list
    ShapeNode* frontNode = canvas.front();

    // makes sure the front node is what was returned back
    REQUIRE(frontNode != nullptr);
    REQUIRE(frontNode->value == shape1);

  }

  SECTION("isempty Function") {
    // creates empty canvas and canvas to be filled with shapes
    CanvasList emptyCanvas;
    CanvasList canvas;

    canvas.push_back(new Shape());
    canvas.push_back(new Shape());

    // makes sure empty canvas is empty and canvas with shapes returns false on isempty call
    REQUIRE(emptyCanvas.isempty() == true);
    REQUIRE(canvas.isempty() == false);

    // deallocates memory for each shape in canvas
    while (!canvas.isempty()) {
      delete canvas.pop_front();
    }
  }

  SECTION("size Function") {
    CanvasList canvas1;
    CanvasList canvas2;
    CanvasList canvas3;

    // pushes back 3 new shapes in canvas 2
    canvas2.push_back(new Shape());
    canvas2.push_back(new Shape());
    canvas2.push_back(new Shape());

    // pushes 3 shapes back to canvas 3 then removes the first one and then removes every other
    canvas3.push_back(new Shape());
    canvas3.push_back(new Shape());
    canvas3.push_back(new Shape());
    canvas3.removeAt(0);
    canvas3.removeEveryOther();

    // makes sure all 3 of the canvasLists have correct size
    REQUIRE(canvas1.size() == 0);
    REQUIRE(canvas2.size() == 3);
    REQUIRE(canvas3.size() == 1);

    // deallocates memory for canvas 2 and 3
    while (!canvas2.isempty()) {
      delete canvas2.pop_front();
    }
    while (!canvas3.isempty()) {
      delete canvas3.pop_front();
    }
  }

  SECTION("find Function") {
    CanvasList canvas;

    // creates 3 shapes with new points and adds them to canvas
    Shape *shape1 = new Shape(1, 2);
    Shape *shape2= new Shape(3, 4);
    Shape *shape3 = new Shape(5, 6);
    canvas.push_back(shape1);
    canvas.push_back(shape2);
    canvas.push_back(shape3);

    // finds index at 3, 4 (should get back index 1)
    int idx = canvas.find(3, 4);

    // makes sure the index is 1
    REQUIRE(idx == 1);

    // tries to find a point that does not exist in canvas
    int idxNotFound = canvas.find(7, 8);

    // should return -1 since point was not found
    REQUIRE(idxNotFound == -1);

    // deallocates memory
    while (!canvas.isempty()) {
      delete canvas.pop_front();
    }
  }

  SECTION("shapeAt Function") {
    CanvasList canvas;

    // creates 3 new shapes and adds them to canvas
    Shape *shape1 = new Shape();
    Shape *shape2 = new Shape();
    Shape *shape3 = new Shape();
    canvas.push_back(shape1);
    canvas.push_back(shape2);
    canvas.push_back(shape3);

    // gets the shapes at their index
    Shape *shapeIdx0 = canvas.shapeAt(0);
    Shape *shapeIdx1 = canvas.shapeAt(1);
    Shape *shapeIdx2 = canvas.shapeAt(2);

    // makes sure the shapes at the index match the correct shape
    REQUIRE(shapeIdx0 == shape1);
    REQUIRE(shapeIdx1 == shape2);
    REQUIRE(shapeIdx2 == shape3);

    // makes sure an invalid shape index returns a nullptr
    Shape* invalidShape = canvas.shapeAt(3);
    REQUIRE(invalidShape == nullptr);

    // deallocates memory
    while (!canvas.isempty()) {
      delete canvas.pop_front();
    }
  }
}

TEST_CASE("Rectangle Class (Milestone 3)") {
  SECTION("Default Constructor") {
    // makes sure default constructor properly initializes height and width to 0
    Rect rectangle;
    REQUIRE(rectangle.getWidth() == 0);
    REQUIRE(rectangle.getHeight() == 0);
  }

  SECTION("Parameter Constructor") {
    // makes sure parameter constructor sets width and height to correct amount
    Rect rectangle(5, 7);
    REQUIRE(rectangle.getWidth() == 5);
    REQUIRE(rectangle.getHeight() == 7);
  }

  SECTION("Parameter Constructor with Width/Height") {
    // sets all points with correct value
    Rect rectangle(10, 15, 5, 3);
    REQUIRE(rectangle.getX() == 10);
    REQUIRE(rectangle.getY() == 15);
    REQUIRE(rectangle.getWidth() == 5);
    REQUIRE(rectangle.getHeight() == 3);

  }

  SECTION("Copy Constructor") {

    // makes sure copy rectangle has all same values as the rectangle it was copied from
    Rect rectangle(10, 15, 20, 25);
    Rect *copyRect = rectangle.copy();

    REQUIRE(copyRect->getX() == 10);
    REQUIRE(copyRect->getY() == 15);
    REQUIRE(copyRect->getWidth() == 20);
    REQUIRE(copyRect->getHeight() == 25);

    delete copyRect;
  }

  SECTION("Getters/Setters") {
    // makes sure getters/setters work correctly
    Rect rectangle(10, 20);
    rectangle.setWidth(5);
    rectangle.setHeight(10);
    REQUIRE(rectangle.getWidth() == 5);
    REQUIRE(rectangle.getHeight() == 10);

  }

  SECTION("printShape Function") {

    // makes sure print statement is accurate
    Rect rectangle(50, 100, 150, 200);

    string expectedOutput = "It's a Rectangle at x: 50, y: 100 with width: 150 and height: 200";

    REQUIRE(rectangle.printShape() == expectedOutput);
  }
}

TEST_CASE("Circle Class (Milestone 4)") {
  SECTION("Default Constructor") {
    Circle circ;

    // makes sure radius initialized to 0
    REQUIRE(circ.getRadius() == 0);

  }

  SECTION("Parameter Constructor") {
    Circle circ(5);

    // makes sure parameters work
    REQUIRE(circ.getRadius() == 5);
  }

  SECTION("Multiple Parameter Constructor") {
    Circle circ(1, 2, 10);

    // makes sure all parameters set the proper values
    REQUIRE(circ.getX() == 1);
    REQUIRE(circ.getY() == 2);
    REQUIRE(circ.getRadius() == 10);
  }

  SECTION("Copy Constructor") {
    Circle circ(15, 20, 25);
    Circle *copyCirc = circ.copy();

    // makes sure copy circle gets the same values from the original circle
    REQUIRE(copyCirc->getX() == 15);
    REQUIRE(copyCirc->getY() == 20);
    REQUIRE(copyCirc->getRadius() == 25);

    delete copyCirc;
  }

  SECTION("Getter/Setter") {
    Circle circ;

    // makes sure getter/setter set and get the correct value
    circ.setRadius(5);
    REQUIRE(circ.getRadius() == 5);
    circ.setRadius(15);
    REQUIRE(circ.getRadius() == 15);
  }

  SECTION("printShape Function") {
    Circle circ(500, 200, 10);

    string expectedOutput = "It's a Circle at x: 500, y: 200, radius: 10";

    REQUIRE(circ.printShape() == expectedOutput);
  }
}

TEST_CASE("Right Triangle Class (MILESTONE 5)") {
  SECTION("Default Constructor") {
    RightTriangle right;

    // makes sure basic call initializes values to 0
    REQUIRE(right.getBase() == 0);
    REQUIRE(right.getHeight() == 0);
  }
  SECTION("2 Parameter Constructor") {

    // makes sure the 2 parameters only changes base and height
    RightTriangle right(5, 10);
    REQUIRE(right.getX() == 0);
    REQUIRE(right.getY() == 0);
    REQUIRE(right.getBase() == 5);
    REQUIRE(right.getHeight() == 10);

  }
  SECTION("4 Parameter Constructor") {

    // makes sure 4 parameters changes x, y, base, height in that order
    RightTriangle right(1, 2, 5, 10);
    REQUIRE(right.getX() == 1);
    REQUIRE(right.getY() == 2);
    REQUIRE(right.getBase() == 5);
    REQUIRE(right.getHeight() == 10);
  }
  SECTION("Copy Constructor") {

    // makes sure copy correctly copies over the values
    RightTriangle right(15, 20, 25, 30);
    RightTriangle *copyRight = right.copy();

    // makes sure copy circle gets the same values from the original circle
    REQUIRE(copyRight->getX() == 15);
    REQUIRE(copyRight->getY() == 20);
    REQUIRE(copyRight->getBase() == 25);
    REQUIRE(copyRight->getHeight() == 30);

    delete copyRight;
  }
  SECTION("Getters/Setters") {
    RightTriangle right;
    REQUIRE(right.getBase() == 0);
    REQUIRE(right.getHeight() == 0);

    // makes sure getter/setter set and get the correct value
    right.setBase(5);
    right.setHeight(10);
    REQUIRE(right.getBase() == 5);
    REQUIRE(right.getHeight() == 10);
  }
  SECTION("printShape Function") {
    RightTriangle right(100, 50, 10, 37);

    string expectedOutput = "It's a Right Triangle at x: 100, y: 50 with base: 10 and height: 37";

    REQUIRE(right.printShape() == expectedOutput);
  }
}

TEST_CASE("Combined Output 1") {
  CanvasList myCanvas;

  Shape *s = new Shape(1, 3);
	Shape *p = new Rect(5, 5, 4, 6);
	Shape *b = new RightTriangle(10, 11, 3, 7);
  Shape *x = new Circle(9, 1, 8);

	myCanvas.push_back(s);
  REQUIRE(myCanvas.shapeAt(0) == s);
  REQUIRE(myCanvas.size() == 1);

  myCanvas.push_front(p);
  REQUIRE(myCanvas.shapeAt(0) == p);
  REQUIRE(myCanvas.shapeAt(1) == s);
  REQUIRE(myCanvas.size() == 2);

  myCanvas.insertAfter(0, b);
  REQUIRE(myCanvas.shapeAt(0) == p);
  REQUIRE(myCanvas.shapeAt(1) == b);
  REQUIRE(myCanvas.shapeAt(2) == s);
  REQUIRE(myCanvas.size() == 3);

  myCanvas.push_front(x);
  REQUIRE(myCanvas.shapeAt(0) == x);
  REQUIRE(myCanvas.shapeAt(1) == p);
  REQUIRE(myCanvas.shapeAt(2) == b);
  REQUIRE(myCanvas.shapeAt(3) == s);
  REQUIRE(myCanvas.size() == 4);

  myCanvas.removeEveryOther();
  REQUIRE(myCanvas.shapeAt(0) == x);
  REQUIRE(myCanvas.shapeAt(1) == b);
  REQUIRE(myCanvas.size() == 2);

  myCanvas.removeAt(0);
  REQUIRE(myCanvas.shapeAt(0) == b);
  REQUIRE(myCanvas.size() == 1);
}

TEST_CASE("Combined Output 2") {
  CanvasList myCanvas;

  Shape *s = new Shape(1, 3);
	Shape *p = new Rect(5, 5, 4, 6);
	Shape *b = new RightTriangle(10, 11, 3, 7);
  Shape *x = new Circle(9, 1, 8);

	myCanvas.push_back(x);
  REQUIRE(myCanvas.shapeAt(0) == x);
  REQUIRE(myCanvas.size() == 1);

  myCanvas.insertAfter(0, b);
  REQUIRE(myCanvas.shapeAt(0) == x);
  REQUIRE(myCanvas.shapeAt(1) == b);
  REQUIRE(myCanvas.size() == 2);

  myCanvas.removeEveryOther();
  REQUIRE(myCanvas.shapeAt(0) == x);
  REQUIRE(myCanvas.size() == 1);
}

TEST_CASE("Combined Output 3") {
    CanvasList myCanvas;

    Shape *a = new Shape(1, 3);
    Shape *b = new Rect(5, 5, 4, 6);
    Shape *c = new RightTriangle(10, 11, 3, 7);
    Shape *d = new Circle(9, 1, 8);
    Shape *e = new Shape(1, 8);
    Shape *f = new Rect(1, 1, 8, 2);
    Shape *g = new RightTriangle(19, 11, 8, 13);
    Shape *h = new Circle(9, 1, 8);
    Shape *i = new Shape(9, 1);
    Shape *j = new Rect(2, 1, 8, 3);
    Shape *k = new RightTriangle(9, 1, 8, 12);
    Shape *l = new Circle(0, 1, 3);

    myCanvas.push_back(a);
    REQUIRE(myCanvas.shapeAt(0) == a);
    REQUIRE(myCanvas.size() == 1);

    myCanvas.push_front(b);
    REQUIRE(myCanvas.shapeAt(0) == b);
    REQUIRE(myCanvas.shapeAt(1) == a);
    REQUIRE(myCanvas.size() == 2);

    myCanvas.insertAfter(0, c);
    REQUIRE(myCanvas.shapeAt(0) == b);
    REQUIRE(myCanvas.shapeAt(1) == c);
    REQUIRE(myCanvas.shapeAt(2) == a);
    REQUIRE(myCanvas.size() == 3);

    myCanvas.clear();
    REQUIRE(myCanvas.size() == 0);
    REQUIRE(myCanvas.isempty() == true);

    myCanvas.push_back(d);
    myCanvas.push_front(e);
    myCanvas.push_back(f);
    myCanvas.push_back(g);
    myCanvas.push_back(h);
    myCanvas.push_back(i);
    myCanvas.push_back(j);
    myCanvas.push_front(k);
    myCanvas.push_back(l);

    REQUIRE(myCanvas.shapeAt(0) == k);
    REQUIRE(myCanvas.shapeAt(1) == e);
    REQUIRE(myCanvas.shapeAt(8) == l);
    REQUIRE(myCanvas.size() == 9);
    REQUIRE(myCanvas.pop_back() == l);
    REQUIRE(myCanvas.size() == 8);
    REQUIRE(myCanvas.pop_front() == k);
    REQUIRE(myCanvas.size() == 7);
    REQUIRE(myCanvas.find(1, 8) == 0);

    myCanvas.removeAt(0);
    REQUIRE(myCanvas.shapeAt(0) == d);
    REQUIRE(myCanvas.size() == 6);

    myCanvas.removeEveryOther();
    REQUIRE(myCanvas.shapeAt(0) == d);
    REQUIRE(myCanvas.shapeAt(1) == g);
    REQUIRE(myCanvas.shapeAt(2) == i);
    REQUIRE(myCanvas.size() == 3);
    
    myCanvas.clear();
    REQUIRE(myCanvas.size() == 0);
}