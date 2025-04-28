#include <iostream>
#include "Node.h"

using namespace std;

Node::Node() {
  value = 0;
  color = RED;
  left = NULL;
  right = NULL;
  parent = NULL;
}

Node::~Node() {
  value = 0;
  //parent = NULL;
  left = NULL;
  right = NULL;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

int Node::getValue() {
  return value;
}

void Node::setLeft(Node* node) {
  left = node;
}

void Node::setRight(Node* node) {
  right = node;
}

void Node::setValue(int a) {
  value = a;
}

void Node::setColor(Color newCol) {
  color = newCol;
}

Color Node::getColor() {
  return color;
}

void Node::setParent(Node* node) {
  parent = node;
}

Node* Node::getParent() {
  return parent;
}

Node* Node::getUncle() {
  if (parent != NULL) { //make sure not head
    if (parent->getParent() != NULL) { //make sure theres a grandpa
      Node* GP = parent->getParent();
      if (GP->getRight() == parent) {
	return GP->getLeft();
      } else if (GP->getLeft() == parent) {
	return GP->getRight();
      }
    }
  }
  return NULL;
}

Node* Node::getSibling() {
  if (parent != NULL) {
    Node* S = NULL;
    if (parent->getRight() == this) {
      S = parent->getLeft();
    } else if (parent->getLeft() == this) {
      S = parent->getRight();
    }
    return S;
  }
  return NULL;
}
