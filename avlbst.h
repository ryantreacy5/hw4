#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    // need a helper function because otherwise we have to do a million lines
    // so adding a helper for rebalancing and rotating 
    // all the rotations
    AVLNode<Key, Value>* rotateRight(AVLNode<Key, Value>* node);
    AVLNode<Key, Value>* rotateLeft(AVLNode<Key, Value>* node);
    AVLNode<Key, Value>* rotateleftRight(AVLNode<Key, Value>* node);
    AVLNode<Key, Value>* rotaterightLeft(AVLNode<Key, Value>* node);

};

// rotateRight helper function
//template<Class Key, class Value>
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* leftChild)
{
  // base case if nothing to rotate
  if(leftChild == nullptr || leftChild->getLeft() == nullptr)
  {
    return leftChild;
  }
  // grab left child and the left childs right subtree
  AVLNode<Key, Value>* rightChild = leftChild->getLeft();
  AVLNode<Key, Value>* temp = rightChild->getRight();

  // left child becomes the new parent of node
  // and the left childs right subtree becomes the nodes left child
  rightChild->setRight(leftChild);
  leftChild->setParent(rightChild);
  leftChild->setLeft(temp);

  if(temp)
  {
    temp->setParent(leftChild);
  }
  //rightChild->setParent(leftChild->setParent());
  //rightChild->setParent(leftChild->getParent());
 // leftChild->setParent(rightChild);
  //if(rightChild->getParent())
 //{
   //if(rightChild->getParent()->getLeft() == leftChild)
    //{
     // rightChild->getParent()->setLeft(rightChild);
   // }
   // else
   // {
    //  rightChild->getParent()->setRight(rightChild);
    //}
    Node<Key, Value>*parent = leftChild->getParent();
    rightChild->setParent(parent); // reconnect leftchild to nodes former parent
    if(parent) // this is the case in which the node to be rotated is the root
    {
      if(parent->getLeft() == leftChild)
      {
        parent->setLeft(rightChild);
      }
      else
      {
        parent->setRight(rightChild);
      }
    }
    else
    {
      this->root_ = rightChild;
    }
 // }
  //else
 // {
   // this->root_ = rightChild;
 // }
  leftChild->setBalance(0);
  rightChild->setBalance(0);

  return rightChild; // new subtree root
}
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* rightChild)
{
  // ok this is gonna be the same as rotateRight but with right and left switched 
  if(rightChild == nullptr || rightChild->getRight() == nullptr)
  {
    return rightChild;
  }
  AVLNode<Key, Value>* leftChild = rightChild->getRight();
  AVLNode<Key, Value>* temp = leftChild->getLeft();
  leftChild->setLeft(rightChild);
  rightChild->setParent(leftChild);
  rightChild->setRight(temp);
  if(temp)
  {
    temp->setParent(rightChild);
  }
  ///leftChild->setParent(rightChild->setParent());
  //leftChild->setParent(rightChild->getParent());
  //rightChild->setParent(leftChild);
 // if(leftChild->getParent())
  //{
    //if(leftChild->getParent->getRight == rightChild)
    //if(leftChild->getParent()->getRight() == rightChild)
   // {
    //  leftChild->getParent()->setRight(leftChild);
   // }
    //else
   // {
      //leftChild->getParent()->setLeft(leftChild);
   // }
  //}
  Node<Key, Value>*parent = rightChild->getParent();
  leftChild->setParent(parent);
  if(parent)
  {
    if(parent->getLeft() == rightChild)
    {
      parent->setLeft(leftChild);
    }
    else
    {
      parent->setRight(leftChild);
    }
  }
  else
  {
    this->root_ = leftChild;
  }
  leftChild->setBalance(0);
  rightChild->setBalance(0);

  return leftChild;
}

// now rotateleftRight
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateleftRight(AVLNode<Key, Value>* node)
{
  /// just two step rotations, rotate left left and node right
  node->setLeft(rotateLeft(node->getLeft()));
  return rotateRight(node);
}
// rotaterightLeft
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotaterightLeft(AVLNode<Key, Value>* node)
{
  // mirror of rotateelftRight
  node->setRight(rotateRight(node->getRight()));
  return rotateLeft(node);
}
/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(this->root_ == nullptr) // if empty tree, jsut make root
    {
      this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
      return;
    }
    // traverse from the root
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* parent = nullptr;
  // if key exists, update it
    while(current != nullptr)
    {
      parent = current;
      if(current->getLeft() != nullptr && new_item.first < current->getKey())
      {
        current = current->getLeft();
      }
      else if(current->getRight() != nullptr && new_item.first > current->getKey())
      {
        current = current->getRight();
      }
      else
      {
        current->setValue(new_item.second);
        return;
      }
    }
    AVLNode<Key, Value>* nextNode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
    if(new_item.first < parent->getKey())
    {
      parent->setLeft(nextNode);
    }
    else
    {
      parent->setRight(nextNode); // insert the new node as a child of parent
    }
    current = nextNode->getParent();
    while(current != nullptr)
    {
      if(new_item.first < current->getKey())
      {
        //current->updateBalance(1);
        current->updateBalance(-1);
      }
      else
      {
        current->updateBalance(1);
      }
      if(current->getBalance() < -1)
      {
        //if(new_item.first < current->getLeft->getKey())
        //
        if(new_item.first < current->getLeft()->getKey())
        {
          current = rotateRight(current);
        }
        else
        {
          current = rotateleftRight(current);
        }
      }
      else if(current->getBalance() > 1)
      {
        if(new_item.first > current->getRight()->getKey())
        {
          current = rotateLeft(current);
        }
        else
        {
          current = rotaterightLeft(current);
        }
      }
      current = current->getParent();
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // create a node to remove
    AVLNode<Key, Value>* removing = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* parent = nullptr;
    while(removing != nullptr)
    {
      if(key < removing->getKey()) // pretty much same implementation as bst.h
      {
        parent = removing;
        removing = removing->getLeft();
      }
      else if(key > removing->getKey())
      {
        parent = removing;
        removing = removing->getRight();
      }
      else
      {
        break;
      }
    }
    if(removing == nullptr)
    {
      return;
    }
    if(removing->getLeft() == nullptr && removing->getRight() == nullptr)
    {
      if(parent == nullptr)
      {
        this->root_ = nullptr;
      }
      else if(parent->getLeft()==removing)
      {
        parent->setLeft(nullptr);
      }
      else
      {
        parent->setRight(nullptr);
      }
      delete removing;
      removing = nullptr;
    }
    else if(removing->getLeft() == nullptr || removing->getRight() == nullptr)
    {
      AVLNode<Key, Value>* child = (removing->getLeft() != nullptr) ? removing->getLeft() : removing->getRight();
      if(parent == nullptr)
      {
        this->root_ = child;
      }
      else if(parent->getLeft()==removing)
      {
        parent->setLeft(child);
      }
      else
      {
        parent->setRight(child);
      }
      child->setParent(parent);
      delete removing;
      removing = nullptr;
    }
    else
    {
      AVLNode<Key, Value>* predecessor=removing->getLeft();
      while(predecessor->getRight() != nullptr)
      {
        predecessor = predecessor->getRight();
      }
      nodeSwap(removing, predecessor);
      remove(key);
      return;
    }
   AVLNode<Key, Value>* current = parent;
    while(current != nullptr)
    {
      if(key < current->getKey())
      {
        current->updateBalance(-1);
      }
      else
      {
        current->updateBalance(1);
      }
      if(current != nullptr && current->getBalance() < -1)
      {
        if(current->getLeft()->getBalance() <= 0)
        {
          current = rotateRight(current);
        }
        else
        {
          current = rotateleftRight(current);
        }
      }
      else if(current != nullptr && current->getBalance() > 1)
      {
      
        if(current->getRight()->getBalance() >= 0)
        {
          current = rotateLeft(current);
        }
        else
        {
          current = rotaterightLeft(current);
        }
      }
      
    if(current->getParent() == nullptr)
    {
      this->root_ = current;
    }
    current = current->getParent();
    }
    
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
