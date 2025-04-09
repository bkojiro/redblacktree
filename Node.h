#ifndef NODE_H
#define NODE_H

#include <iostream>

enum Color {BLACK, RED};

using namespace std;

class Node {
 public:
  Node();
  ~Node();
  Node* getLeft();
  Node* getRight();
  int getValue();
  void setLeft(Node* node);
  void setRight(Node* node);
  void setValue(int a);
  void setColor(Color newCol);
  Color getColor();
 private:
  int value;
  Color color;
  Node* left;
  Node* right;
};

#endif
