#include "BST.h"

// constructor, initialize class variables and pointers here if need.
BST::BST(){
}

//deconstructor,
BST::~BST(){
}

shared_ptr<bst_node> BST::InitNode(int data){
  //create new node
  bst_node* new_node = new bst_node;
  //assign given data parameter to new node
  new_node->data = data;
  //declare empty pointers
  new_node->left = nullptr;
  new_node->right = nullptr;
  //shared_ptr<bst_node> ret;  
  return shared_ptr<bst_node>(new_node);
}

void BST::Insert(shared_ptr<bst_node> new_node){
  //check if subt is empty
  if (root_ptr_ == nullptr) {
    root_ptr_ = new_node;
  }
  //else move down branches to find insertion point
  else {
    shared_ptr<bst_node> current = root_ptr_;
    while(current != nullptr) {
      //if new node is less than current node, move down to left
      if (new_node->data < current->data) {
        if (current->left == nullptr) {
          current->left = new_node;
          break;
        }
        else {
          current = current->left;
        }
      }
      //else node must be more than current node
      //move down to right
      else {
        if(current->right == nullptr) {
          current->right = new_node;
          break;
        }
        else {
          current = current->right;
        }
      }
    }
  }
}

void BST::InsertData(int data){
  shared_ptr<bst_node> new_node = InitNode(data);
  Insert(new_node);
}

void BST::Remove(int data){
  shared_ptr<bst_node> parent = nullptr;
  shared_ptr<bst_node> current = root_ptr_;
  //traverse bst nodes
  while (current != nullptr) {
    //check if current node is to be removed
    if (data == current->data) {
      //check if root node is to be removed
      if (current == root_ptr_) {
        //check if root node has no children
        if (current->left == nullptr && current->right == nullptr) {
          root_ptr_ = nullptr;
        }
        //check if root only has right child
        else if(current->left == nullptr){
          root_ptr_ = current->right;
        }
        //check if root only has left child
        else if(current->right == nullptr) {
          root_ptr_ = current->left;
        }
        //else root must have both left and right
        else {
          //new pointer set to right child of current node
          shared_ptr<bst_node> successor = current->right;
          //new empty pointer
          shared_ptr<bst_node> successor_parent = nullptr;
          //traverse subt reassigning pointers down left branches
          while (successor->left != nullptr) {
            successor_parent = successor;
            successor = successor->left;
          }
          //set last node to have empty left child
          if(successor_parent != nullptr) {
            successor_parent->left = nullptr;
          }
          successor->left = current->left;
          successor->right = current->right;
          root_ptr_ = successor;
        }
      }
      //else a non-root node is to be removed
      else{
        //check if the node has no children
        if (current->left == nullptr && current->right == nullptr) {
          if(parent->left == current) {
            parent->left = nullptr;
          }
          else {
            parent->right = nullptr;
          }
        }
        //check if the node has only right child
        else if (current->left == nullptr) {
          if (parent->left == current) {
            parent->left = current->right;
          }
          else {
            parent->right = current->right;
          }
        }
        //check if the node has only left child
        else if (current->right == nullptr) {
          if (parent->left == current) {
            parent->left = current->left;
          }
          else {
            parent->right = current->left;
          }
        }
        //else the node must have both left and right children
        else {
          //new pointer set to right child of current node
          shared_ptr<bst_node> successor = current->right;
          //new empty pointer
          shared_ptr<bst_node> successor_parent = nullptr;
          //traverse subt reassigning pointers down left branches
          while (successor->left != nullptr) {
            successor_parent = successor;
            successor = successor->left;
          }
          //set last node to have empty left child
          if (successor_parent != nullptr) {
            successor_parent->left = nullptr;
          }
          successor->left = current->left;
          successor->right = current->right;
          if (parent->left == current) {
            parent->left = successor;
          }
          else {
            parent->right = successor;
          }
        }
      }
      break;
    }
    else if (data < current->data) {
      parent = current;
      current = current->left;
    }
    else {
      parent = current;
      current = current->right;
    }
  }
}

bool BST::Contains(shared_ptr<bst_node> subt, int data){
  //check if subt is empty
  if (subt == nullptr){
    return false;
  }
  //if current node is equal to subt, return true
  if (data == subt->data) {
    return true;
  }
  //if subt node data is larger, call Contains again on left child
  else if(data < subt->data) {
    return Contains(subt->left, data);
  }
  //if subt node data is smaller, call Contains again on right child
  else {
    return Contains(subt->right, data);
  }
}

shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data){
  if (subt == nullptr || subt->data == data) {
    return subt;
  }
  if (data < subt->data) {
    return GetNode(subt->left, data);
  }
  else {
    return GetNode(subt->right, data);
  }
}

int BST::Size(shared_ptr<bst_node> subt){
  //check if subt is empty
  if (subt == nullptr){
    return 0;
  }
  //if subt is not empty, count 1 level and move down both branches
  //recursively call Size on new subtrees
  else {
    return 1 + Size(subt->left) + Size(subt->right);
  }
}

void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec){
  if(subt == nullptr) {
    return;
  }
  ToVector(subt->left, vec);
  vec.push_back(subt->data);
  ToVector(subt->right, vec);
  
}

// This function is implemented for you
// Returns the root pointer
shared_ptr<bst_node> BST::GetRoot(){
  return root_ptr_;
}

// This function is implemented for you
// sets a given pointer as the top pointer
void BST::SetRoot(shared_ptr<bst_node> root_ptr){
  root_ptr_ = root_ptr;
}