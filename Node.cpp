#include <iostream>
#include "Node.h"

using namespace std;

Node::Node() {
  value = 0;
  color = RED;
  left = NULL;
  left->setColor(BLACK);
  right = NULL;
  right->setColor(BLACK);
}

Node::~Node() {
  value = 0;
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
  if (color == RED) node->setColor(BLACK);
  left = node;
}

void Node::setRight(Node* node) {
  if (color == RED) node->setColor(BLACK);
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
