// This file contains all the implementation functions used in canvaslist.h
// It allows us to interact with the canvas and classes

#include "canvaslist.h"
#include <iostream>
using namespace std;

// Default constructor : initializes empty canvasList
CanvasList::CanvasList() : listSize(0), listFront(nullptr) {}

// Copy Constructor : creates new canvasList which is copied from another canvasList
CanvasList::CanvasList(const CanvasList &copyConst) : listSize(0), listFront(nullptr) {
    ShapeNode *curr = copyConst.listFront;
    while (curr != nullptr) {
        // creates a new shape as the copy and adds it to list
        push_back(curr->value->copy());
        curr = curr->next;
    }
}

// Assignment operator : assigns contents of different canvasList to this canvasList
CanvasList& CanvasList::operator=(const CanvasList &newCopyConst) {
    if (this == &newCopyConst) {
        return *this;
    }
    // clears the current list
    clear();

    ShapeNode *curr = newCopyConst.listFront;

    while (curr != nullptr) {

        // creates new shape as a copy and adds it to list
        push_back(curr->value->copy());
        curr = curr->next;
    }

    return *this;
}

// Destructor that deallocates memory for all shapes and nodes in list
CanvasList::~CanvasList() {
    clear();
}

// clears the list and deallocates memory for all shapes and nodes in lsit
void CanvasList::clear() {
    while (listFront) {
        ShapeNode *temp = listFront;
        listFront = listFront->next;
        delete temp->value;
        delete temp;
    }
    listSize = 0;
}


// inserts shape after given index
// does nothing if the index is out of range
void CanvasList::insertAfter(int idx, Shape *shape) {

    // handles if index is out of range
    if (idx < 0 || idx >= listSize) {
        return;
    }

    listSize++;
    
    // creates new node to add to list
    ShapeNode *newNode = new ShapeNode();
    
    // copies shape pointer into the new node
    newNode->value = shape;

    if (idx == listSize - 1) {      
        
        newNode->next = nullptr;

        // finds last node in list
        ShapeNode *lastNode = listFront;
        while (lastNode->next != nullptr) {
            lastNode = lastNode->next;
        }

        // sets last node's next to point to the new node
        lastNode->next = newNode;
    }
    else {
        // inserts after any index in range exluding 0
        ShapeNode *prevNode = listFront;
        for (int i = 0; i < idx; i++) {
            prevNode = prevNode->next;
        }
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
}

// pushes shape to front of list
void CanvasList::push_front(Shape *shape) {
    
    // creates new node and sets value
    ShapeNode *newNode = new ShapeNode();
    newNode->value = shape;

    // sets the new node as the head of linked list
    newNode->next = listFront;
    listFront = newNode;

    // increments the list size
    listSize++;
}

// pushes shape to back of list
void CanvasList::push_back(Shape *shape) {

    // creates new node
    ShapeNode *newNode = new ShapeNode();
    newNode->value = shape;
    newNode->next = nullptr;

    // if the list is empty the new node is now the front of the list
    if (isempty()) {
        listFront = newNode;
    }
    else {
        // finds last node in last and makes it the new node
        ShapeNode *lastNode = listFront;
        while (lastNode->next != nullptr) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }

    // increments list size
    listSize++;
}

// removes shape at given index
// does nothing if index out of range
void CanvasList::removeAt(int idx) {
    if (idx < 0 || idx >= listSize) {
        return;
    }

    if (idx == 0) {
        // creates temp at front of list
        ShapeNode *temp = listFront;

        // sets front of list to the 2nd node
        listFront = listFront->next;

        // // deallocates memory for first node
        delete temp->value;
        delete temp;
    }
    else {

        // gets front node
        ShapeNode *prevNode = front();

        // traverse through node
        for (int i = 0; i < idx - 1; i++) {
            prevNode = prevNode->next;
        }

        // stores node to delete
        ShapeNode *temp = prevNode->next;

        // updates previous node's next pointer
        prevNode->next = temp->next;

        // deallocates memory for removed node
        delete temp->value;
        delete temp;
    }
    listSize--;
}

// removes every other shape in list
// first removal is index 1
void CanvasList::removeEveryOther() {
    // starts beginning node at the front of the list
    ShapeNode *curr = listFront;
    ShapeNode *prev = nullptr;

    int idx = 0;

    while (curr != nullptr) {

        // handles every other node starting at index 1
        if (idx % 2 != 0) {
            if (prev != nullptr) {
                prev->next = curr->next;
            }
            else {
                listFront = curr->next;
            }
            ShapeNode *temp = curr;
            curr = curr->next;
            delete temp->value;
            delete temp;
            listSize--;
        }
        else {
            prev = curr;
            curr = curr->next;
        }

        idx++;
    }
}

// pops and returns the front of list shape
// returns nullpointer if list is empty
// return pointer to the shape if list is 1
Shape* CanvasList::pop_front() {
    // checks if list is empty
    if (isempty()) {
        return nullptr;
    }

    // stores node and value of the front node
    ShapeNode *temp = listFront;
    Shape *shape = temp->value;

    // starts list on 2nd node
    listFront = listFront->next;

    // deallocates memory for the 1st node
    delete temp;

    listSize--;

    return shape;
}

// pops and returns back of list shape
// return nullpointer if list is empty
// returns pointer to shape if list is 1
Shape* CanvasList::pop_back() {


    // checks if list is empty
    if (isempty()) {
        return nullptr;
    }

    if (listSize == 1) {
        ShapeNode *temp = listFront;
        listFront = nullptr;
        Shape *shape = temp->value;
        delete temp;
        listSize--;
        return shape;
    }

    ShapeNode *curr = listFront;
    ShapeNode *prev = nullptr;
    while (curr->next != nullptr) {
        prev = curr;
        curr = curr->next;
    }

    // stores value of shape
    prev->next = nullptr;
    Shape *shape = curr->value;
    delete curr;
    listSize--;

    return shape;
}

// returns front node of list
ShapeNode* CanvasList::front() const {
    return listFront;
}

// checks if list is empty
bool CanvasList::isempty() const {
    return listSize == 0;
}

// returns size of list
int CanvasList::size() const {
    return listSize;
}

// finds index of shape with given points
// returns -1 if shape not found
// return index if shape is found
int CanvasList::find(int x, int y) const {
    
    // starts current node at front of list
    ShapeNode *curr = listFront;
    int idx = 0;
    while (curr != nullptr) {
        // checks if x,y values match given x,y points
        if (curr->value->getX() == x && curr->value->getY() == y) {
            return idx;
        }
        curr = curr->next;
        idx++;
    }

    // returns -1 if shape was not found
    return -1;
}


// returns pointer to shape at given index
// returns nullpointer if index is out of range
Shape* CanvasList::shapeAt(int idx) const {

    if (idx < 0 || idx >= listSize) {
        return nullptr;
    }
    
    // starts current node at front
    ShapeNode *curr = listFront;

    // traverses through list to find node at given index
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }

    // returns pointer to shape at given index
    return curr->value;

}

// draws all shapes in list
void CanvasList::draw() const {
    ShapeNode *curr = listFront;

    while (curr != nullptr) {
        // calls printShape function for each shape to get shape's info
        cout << curr->value->printShape() << endl;
        curr = curr->next;
    }
}

// prints all addresses and info of all shapes in list
void CanvasList::printAddresses() const {
    ShapeNode *curr = listFront;
    while (curr != nullptr) {
        // prints out pointer address and the pointer's value(shape) address
        cout << "Node Address: " << curr << "    Shape Address: " << curr->value << endl;
        curr = curr->next;
    }
}
