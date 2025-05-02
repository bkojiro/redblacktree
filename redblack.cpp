//TREE OUTLINE FROM MY BINARY SEARCH ALGORITHM, IMPLEMENTATION OF RED BLACK TREE NEW

#include <iostream>
#include <cstring>
#include <fstream>
#include "Node.h"

using namespace std;

void fixIns(Node* &cur, Node* &root);
void caseThree(Node* &cur, Node* &root);
void caseFour(Node* &cur);
void caseFive(Node* &cur, Node* &root);
void insert(Node* &current, int a, Node* &root);
void remove(Node* M, Node* &root, int x);
void fixRem(Node* N, Node* &root);
void print(Node* current, int depth);
void search(Node* current, int x);

int main() {
  Node* root = new Node();
  bool active = true;
  while(active) {
    cout << "Enter INSERT, REMOVE, PRINT, SEARCH, or QUIT" << endl << "> ";
    char action[10];
    cin.get(action, 11);
    cin.ignore();
    if (strcmp(action, "INSERT") == 0) {
      //ask either by console or file
      cout << "Insert by console ('c') or file ('f')?" << endl << "> ";
      char in;
      cin >> in;
      cin.ignore();
      if (in == 'c') {
	    //insert by console
	    cout << "Enter a number" << endl << "> ";
	    int a;
	    cin >> a;
	    cin.ignore();
        insert(root, a, root);
      } else if (in == 'f') {
	    //insert by file
	    ifstream numbers;
	    numbers.open("numbers.txt");
	    int x;
	    while (numbers >> x) {
	      //insert x into tree
	      insert(root, x, root);
	    }
      }
    } else if (strcmp(action, "REMOVE") == 0) {
      //remove a number covering the three cases + deleting root
      cout << "What number would you like to remove?" << endl << "> ";
      int x;
      cin >> x;
      cin.ignore();
      remove(root, root, x);//DO THIS FOR SECOND PART OF PROJECT
    } else if (strcmp(action, "PRINT") == 0) {
      //visualization of tree
      print(root, 0);
    } else if (strcmp(action, "SEARCH") == 0) {
      //see if tree has a number
      cout << "What number would you like to search for?" << endl << "> ";
      int x;
      cin >> x;
      cin.ignore();
      search(root, x);
    } else if (strcmp(action, "QUIT") == 0) {
      //terminate program
      active = false;
    }
  }
  return 0;
}

void fixIns(Node* &cur, Node* &root) {
  if (cur->getParent() == NULL && cur->getColor() == RED) { //case 1
    cur->setColor(BLACK);
  } else if (cur->getParent() != NULL) {
    caseThree(cur, root);
    caseFour(cur);
    caseFive(cur, root);
  }
}

void caseThree(Node* &cur, Node* &root) {
  if (cur->getUncle() != NULL && cur->getParent()->getParent() != NULL) {
    if (cur->getParent()->getColor() == RED && cur->getUncle()->getColor() == RED) {
      cur->getParent()->setColor(BLACK);
      cur->getUncle()->setColor(BLACK);
      Node* GP = cur->getParent()->getParent();
      GP->setColor(RED);
      fixIns(GP, root);
    }
  }
}

void caseFour(Node* &cur) {
  if (cur->getParent()->getParent() != NULL && cur->getParent()->getColor() == RED) {
    Node* GP = cur->getParent()->getParent();
    Node* P = cur->getParent();
    if (cur->getUncle() == NULL || cur->getUncle()->getColor() == BLACK) {
      if (GP->getLeft() == P &&
          P->getRight() == cur) { //parent is left, node is right
        Node* temp = cur->getLeft();
        P->setRight(temp);
        cur->setLeft(P);
        P->setParent(cur);
        cur->setParent(GP);
        GP->setLeft(cur);
        cur = P;
      } else if (GP->getRight() == P &&
                 P->getLeft() == cur) { //parent is right, node is left
        Node* temp = cur->getRight();
        P->setLeft(temp);
        cur->setRight(P);
        P->setParent(cur);
        cur->setParent(GP);
        GP->setRight(cur);
        cur = P;
      }
    }
  }
}

void caseFive(Node* &cur, Node* &root) {
  if (cur->getParent()->getParent() != NULL && cur->getParent()->getColor() == RED) {
    Node* GP = cur->getParent()->getParent();
    Node* P = cur->getParent();
    if (cur->getUncle() == NULL || cur->getUncle()->getColor() == BLACK) {
      bool changeRoot = false;
      if (GP == root) changeRoot = true;//change where the root is pointing to
      if (GP->getLeft() == P &&
          P->getLeft() == cur) { //parent is left, node is left
        GP->setColor(RED);
        P->setColor(BLACK);
        GP->setLeft(P->getRight());
        P->setRight(GP);
        P->setParent(GP->getParent());
        GP->setParent(P);
        if (changeRoot) {
          root = P;
        } else {
          if (P->getParent()->getRight() == GP) {
            P->getParent()->setRight(P);
          } else if (P->getParent()->getLeft() == GP) {
            P->getParent()->setLeft(P);
          }
        }
      } else if (GP->getRight() == P &&
                 P->getRight() == cur) { //parent is right, node is right
        GP->setColor(RED);
        P->setColor(BLACK);
        GP->setRight(P->getLeft());
        P->setLeft(GP);
        P->setParent(GP->getParent());
        GP->setParent(P);
        if (changeRoot) {
          root = P;
        } else {
          if (P->getParent()->getRight() == GP) {
            P->getParent()->setRight(P);
          } else if (P->getParent()->getLeft() == GP) {
            P->getParent()->setLeft(P);
          }
        }
      }
    }
  }
}

void insert(Node* &current, int a, Node* &root) {
  if (current->getValue() == 0) { //insert at root
    current->setValue(a);
    current->setColor(BLACK);
  } else if (a >= current->getValue()) {
    //go to right if greater/equal to current
    if (current->getRight() != NULL) {
      Node* right = current->getRight();
      insert(right, a, root);
    } else {
      Node* temp = new Node();
      temp->setValue(a);
      temp->setParent(current);
      current->setRight(temp);
      fixIns(temp, root);
    }
  } else if (a < current->getValue()) {
    //go to left!
    if (current->getLeft() != NULL) {
      Node* left = current->getLeft();
      insert(left, a, root);
    } else {
      Node* temp = new Node();
      temp->setValue(a);
      temp->setParent(current);
      current->setLeft(temp);
      fixIns(temp, root);
    }
  }
}

void remove(Node* M, Node* &root, int x) {
  if (M != NULL) {
    if (M->getValue() == x) {
      //find replacement
      if (M->getLeft() == NULL && M->getRight() == NULL) { //no children
	if (M == root) {
	  M->setValue(0);
	} else {
	  Node* P = M->getParent();
	  if (P->getRight() == M) {
	    P->setRight(NULL);
	  } else {
	    P->setLeft(NULL);
	  }
	  delete M;
	}
      } else {
	Node* C = M;
	if (M->getLeft() != NULL) { //has a left child
	  C = M->getLeft();
	  while (C->getRight() != NULL) {
	    C = M->getRight();
	  }
	} else if (M->getRight() != NULL) { //no left, has right child
	  C = M->getRight();
	}
	if (M->getColor() == RED && C->getColor() == BLACK) {
	  Node* P = M->getParent();
	  C->setParent(P);
	  if (C != M->getRight()) {
            C->setRight(M->getRight());
            M->getRight()->setParent(C);
          }
	  if (M != root) { //if M was not root
	    if (P->getRight() == M) {
	      P->setRight(C);
	    } else if (P->getLeft() == M) {
	      P->setLeft(C);
	    }
	  } else {
	    root = C;
	  }
	  delete M;
	} else if (M->getColor() == BLACK && C->getColor() == RED) {
	  Node* P = M->getParent();
	  C->setColor(BLACK);
	  C->setParent(P);
	  if (C != M->getRight()) {
	    C->setRight(M->getRight());
	    M->getRight()->setParent(C);
	  }
	  if (M != root) { //if M was not root
	    if (P->getRight() == M) {
	      P->setRight(C);
	    } else if (P->getLeft() == M) {
	      P->setLeft(C);
	    }
	  } else {
	    root = C;
	  }
	  delete M;
	} else if (M->getColor() == BLACK && C->getColor() == BLACK) {
	  if ((M->getRight() == C && M->getLeft() == NULL) ||
	      (M->getLeft() == C && M->getRight() == NULL)) { //one non-leaf child
	    if (M == root) { //case1
	      C->setParent(NULL);
	      delete M;
	      root = C;
	    } else {
	      //move C into M and rename as N
	      Node* P = M->getParent();
	      C->setParent(P);
	      if (P->getRight() == M) {
		P->setRight(C);
	      } else if (P->getLeft() == M) {
		P->setLeft(C);
	      }
	      Node* N = C;
	      fixRem(N, root);
	    }
	  }
	}
      }
    } else if (x >= M->getValue()) {
      remove(M->getRight(), root, x);
    } else if (x < M->getValue()) {
      remove(M->getLeft(), root, x);
    }
  }
}

void fixRem(Node* N, Node* &root) {
  Node* P = N->getParent();
  if (N->getSibling() != NULL) {
    Node* S = N->getSibling();
  if (S->getColor() == RED &&
      P->getColor() == BLACK) { //case2
    P->setParent(S);
    P->setColor(RED);
    S->setColor(BLACK);
    if (P->getLeft() == N) { //N is on the left
      P->setRight(S->getLeft());
      S->getLeft()->setParent(P);
      S->setLeft(P);
    } else if (P->getRight() == N) { //N is on the right
      P->setLeft(S->getRight());
      S->getRight()->setParent(P);
      S->setRight(P);
    }
  }
  if (S->getColor() == BLACK &&
      P->getColor() == BLACK &&
      (S->getRight() == NULL || S->getRight()->getColor() == BLACK) &&
      (S->getLeft() == NULL || S->getLeft()->getColor() == BLACK)) { //case3
    S->setColor(RED);
    fixRem(P, root);
  }
  if (P->getColor() == RED &&
      (S->getRight() == NULL || S->getRight()->getColor() == BLACK) &&
      (S->getLeft() == NULL || S->getLeft()->getColor() == BLACK)) { //case4
    P->setColor(BLACK);
    S->setColor(RED);
    return;
  }
  //case5
  if (P->getLeft() == S &&
      S->getColor() == BLACK &&
      S->getRight() != NULL && S->getRight()->getColor() == RED &&
      S->getLeft() != NULL && S->getLeft()->getColor() == BLACK) { //S is on the left
    Node* SR = S->getRight();
    Node* SL = S->getLeft();
    SR->setParent(P);
    S->setRight(SR->getLeft());
    SR->setLeft(S);
    S->setParent(SR);
    SR->setColor(BLACK);
    S->setColor(RED);
  } else if (P->getRight() == S &&
	     S->getColor() == BLACK &&
	     S->getLeft() != NULL && S->getLeft()->getColor() == RED &&
	     S->getRight() != NULL && S->getRight()->getColor() == BLACK) { //S is on the right
    Node* SR = S->getRight();
    Node* SL = S->getLeft();
    SL->setParent(P);
    S->setLeft(SL->getRight());
    SL->setRight(S);
    S->setParent(SL);
    SL->setColor(BLACK);
    S->setColor(RED);
  }
  //work on case 6/7
}

void print(Node* current, int depth) {
  if (current->getRight() != NULL) {
    print(current->getRight(), depth + 1);
  }
  for (int a = 0; a < depth; a++) {
    cout << '\t';
  }
  if (current->getColor() == BLACK) {
    cout << "\e[34m" << current->getValue() << "\e[37m" << endl;
  } else {
    cout << "\e[31m" << current->getValue() << "\e[37m" << endl;
  }
  if (current->getLeft() != NULL) {
    print(current->getLeft(), depth + 1);
  }
}

void search(Node* current, int x) {
  if (current != NULL) { 
    if (current->getValue() == x) {
      cout << "Number found" << endl;
    } else if (x >= current->getValue()) {
      search(current->getRight(), x);
    } else if (x < current->getValue()) {
      search(current->getLeft(), x);
    }
  } else {
    cout << "Number not found" << endl;
  }
}
