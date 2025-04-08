#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    // ok adding one for clear and isBalanced
    // should be recursive
    void helperforClear(Node<Key, Value>* node);
   // void helperforBalanced(Node<)
   int helperforBalanced(Node<Key, Value>* node) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/


// implement helpers!
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::helperforClear(Node<Key, Value>* node)
{
  // first do the base case duh
  if(node == nullptr)
  {
    //return nullptr;
    //  its voide so just return
    return;
  }
  // call it recursivley with the left and the right
  helperforClear(node->getLeft());
  helperforClear(node->getRight());
  // clean up! 
  delete node;
  
}
//template<typename Key, typename Value>
//int BinarySearchTree<Key, Value>::helperforBalanced(Node<Key, Value>* node) const
//{
 // if(node == nullptr)
 //{
    //return nullptr;
   // return 0;
 // }
 // int left = helperforBalanced(node->getLeft());
 // if(left == -1)
 // {
  //  return -1;
  ///}
  //int right = helperforBalanced(node->getRight());
 // if(right == -1)
 // {
  //  return -1;
//  }

  //if(std::abs(left - right) > 1)
  //{
  //  return -1;
 // }
 // return 1+std::max(left,right);
//}

template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    // setc current to the poiinter
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    // just set it to nullptr
    current_ = nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    // so just return comp between this and rhs
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    // wouldnt this just be the same as the one before?
    // i guess true is if theyre different now
    return current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if(current_ == nullptr) // if its null then just return the pointer 
    {
      return *this;
    }
    // needs to handle two different cases depending on 
    // if there is a right child
   // if(current_->right != nullptr)
   //if(current_->right_ != nullptr)
   if(current_->getRight() != nullptr)
    {
      //current_ = current_->right;
     // current_ = current_->right_;
     current_ = current_->getRight();
      //while(current_->left != nullptr)
      //while(current_->left_ != nullptr)
      while(current_->getLeft() != nullptr)
      {
        //current_ = current_->left;
        //current_ = current_->left_;
        current_ = current_->getLeft();
      }
    }
    else
    {
      //Node<Key, Value* parent = current_->parent;
      //Node<Key, Value* parent = current_->parent_;
      //Node<Key, Value>* parent = current_->parent_;
      Node<Key, Value>* parent = current_->getParent();
      //while(parent != nullptr && current_ == parent->right)
      //while(parent != nullptr && current_ == parent->right_)
      while(parent != nullptr && current_ == parent->getRight())
      {
        current_ = parent;
        //parent = parent->parent;
        //parent = parent->parent_;
        parent = parent->getParent();
      }
      current_ = parent;
      

    }
    
    return *this;


}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    // just needs to set to NULL
    // needs to take constant time
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    // just a little destructor 
    // Constructor and destructor : Your destructor will probably just call the clear function. The constructor should take constant time.
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // base case always
   // if(root_ == nullptr)
   // {
      //return nullptr;
     // root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second)
   // }
   // nvm! looking like i should use a helper
   //if(root == nullptr)
   if(root_ == nullptr)
   {
    // if the tree is empty then create a new node and set to root and set the parent to null
    root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
    return;
   }
   // initializr a pointer to the root
   Node<Key, Value>* current = root_; 
   while(current != nullptr)  // as long as the root isnt null, so it loops until there is an empty spot to insert 
   {
    if(keyValuePair.first < current->getKey())// if the new pair is less than the key of the current, move to the left child
    {
      if(current->getLeft() == nullptr) // if the left child is empty then we found a spot to insert 
      {
        // so create a new node with the key-value pair and add as the left child
        current->setLeft(new Node<Key,Value>(keyValuePair.first, keyValuePair.second, current));
        return;
      }
      else
      {
        current = current->getLeft();
      }
    }
    else if(keyValuePair.first > current->getKey()) // does the same but checks if its greater, if so then we go to the right child
    {
      if(current->getRight() == nullptr)
      {
        current->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current));
        return;
      }
      else
      {
        current = current->getRight();
      }
    }
    else
    {
      current->setValue(keyValuePair.second);
      return;
    }
   }
   
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    //Node<Key, Value>* removing = internalFind(key);
    //if(removing == nullptr)
   // {
     // throw std::out_of_range("Key not found");
    //}
  //  if(removing->getLeft() == nullptr && removing->getRight() == nullptr)
    //{
     // if(removing->getParent() != nullptr)
      //{
        //if(removing == removing->getParent()->getLeft())
      //  {
       //  removing->getParent()->setLeft(nullptr);
     //  }
      //  else
      // {
       //   removing->getParent()->setRight(nullptr);
      //  }
    //  }
   //   else
    //  {
      //  root_ = nullptr;
    //  }
    //  delete removing;
   // }
   // else if(removing->getLeft() == nullptr || removing->getRight() == nullptr)
   // {
     // Node<Key, Value>* child = (removing->getLeft() != nullptr) ? removing->getLeft() : removing->getRight();
     // if(removing->getParent() != nullptr)
     // {
      //  if(removing == removing->getParent()->getLeft())
     //   {
      //    removing->getParent()->setLeft(child);
      //  }
       // else
      //  {
        //  removing->getParent()->setRight(child);
      //  }
     // }
     // else
      //{
       // root_ = child;
     // }
     // if(child != nullptr)
     // {
       // child->setParent(removing->getParent());
     // }
     // delete removing;
   // }
   // else
   // {
     // Node<Key, Value>* successor = getSmallestNode(removing->getRight());
    // Node<Key, Value>* successor = removing->getRight();
     //while(successor->getLeft() != nullptr)
    // {
    // successor = successor->getLeft();
     //}
      ////removing->getItem() = successor->getItem();
      //remove(successor->getKey());
    //  std::pair<const Key, Value> successorItem = successor->getItem();
    //  removing->setItem(successorItem);
   // }
   Node<Key, Value>* removing = root_; // initialize a pointer to the root that is set as the node we are removing 
   Node<Key, Value>* parent = nullptr; // set a new parent node to null

  // loop so long as the current node is not null and the key doesnt match 
   while(removing != nullptr && removing->getKey() != key)
   {
    parent = removing; // parent is set to the current node
    if(key<removing->getKey()) // again, if key is smaller move to the left
    {
      removing=removing->getLeft();
    }
    else
    {
      removing = removing->getRight();
    }
   }
   if(removing == nullptr) // if no key is found in the tree
   {
    std::cout<<"Key not found";
    return;
   }
   // then we check for the case in which the node has no children
   if(removing->getLeft() == nullptr && removing->getRight() == nullptr)
   {
    if(removing == root_) // base case if the current node to be removed is the root
    {
      root_ = nullptr;
    }
    else if(parent->getLeft() == removing) // if it is the left child of the parent, parent left pointer gets set to null
    {
      parent->setLeft(nullptr);
    }
    else
    {
      parent->setRight(nullptr);
    }
    delete removing; // clear space
   }
   // next check for the case in which the node has one child 
   else if(removing->getLeft() == nullptr || removing->getRight() == nullptr) 
   {
    // set the child ptr to the non-null pointer child left or right
    Node<Key, Value>* child = (removing->getLeft() != nullptr) ? removing->getLeft() : removing->getRight();
    if(removing == root_) // base
    {
      root_ = child;
    }
    else if(parent->getLeft() == removing)// if the node is the left child the parents left pointer is the node to remove
    {
      parent->setLeft(child);
    }
    else
    {
      parent->setRight(child); // right otherwise
    }
    delete removing;
   }
   // case in which the node has two children
   else
   {
    // set the successor to the right child of the node thats gonna be removed
    Node<Key, Value>* successor = removing->getRight();
    // set a pointer to track the parent of the successor
    Node<Key, Value>* successorParent = removing;
    while(successor->getLeft() != nullptr) // find the left-most child to be removed
    {
      successorParent = successor; //update parent
      successor=successor->getLeft(); // move to the left child of the successor
    }
   // const std::pair<const Key, Value>& successorItem = successor->getItem();
    //removing->getItem() = successorItem;
    nodeSwap(removing, successor); // once we find the successor, swap the node and successor key-value pair
    //Node<Key, Value>* deletingthisNode = removing;
    if(successorParent != removing)
    {
      successorParent->setLeft(successor->getRight());
    }
    else
    {
      successorParent->setRight(successor->getRight());
    }
    //delete successor;
    //delete deletingthisNode;
    delete removing;
   }

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // another mandatory helper function
    // base case:
    //if(cuurrent == nullptr)
    if(current == nullptr)
    {
        return nullptr;
    }
    // need to check 2 cases - left and non-left subtree
    if(current->getLeft() != nullptr)// if the node has a left subtree, then its predesccor is the rightmost node in that subtree
    {
        //Node<key, Value* predor = current->getLeft();
        Node<Key, Value>* predecessor = current->getLeft();
        while(predecessor->getRight() != nullptr) // loop until were as far right as possible 
        {
            predecessor = predecessor->getRight();
        }
        return predecessor;
    }
    
    //Node<key, Value* parent = current->getParent();
    //Node<Key, Value* parent = current->getParent();
    // if there is no left subtree, we move up until we find a node where current is the right subtree of parent
    Node<Key, Value>* parent = current->getParent();
    while(parent != nullptr && current == parent->getLeft())
    {
        current = parent;
        parent = parent->getParent();
    }
    return parent;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    // use a helper function for this
    // ok so now we just call the helper
    //helperforclear(root_);
    helperforClear(root_);
   root_ = nullptr;
   

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // ok going to do these before i continue with the rest
    // so the smallest is the leftmost node
   // Node<key, Value* current = root_;
   Node<Key, Value>* current = root_;
    if(current == nullptr)
    {
        return nullptr;
    }
    while(current -> getLeft() != nullptr)
    {
        current = current->getLeft();
    }
    return current;
}   



/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    // first do same current declaration
   //Node<key, Value* current = root_;
   Node<Key, Value>* current = root_;
    while(current != nullptr)
    {
        if(key < current->getKey())
        {
            //current = current-> getleft();
            current = current->getLeft();
        }
        else if( key > current->getKey())
        {
            current = current->getRight();
        }
        else
        {
            return current;
        }
    }
    return nullptr;
}


// helper for balanced
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::helperforBalanced(Node<Key, Value>* node) const
{
  if(node == nullptr)
  {
    //return nullptr;
    return 0;
  }
  int left = helperforBalanced(node->getLeft());
  if(left == -1)
  {
    return -1;
  }
  int right = helperforBalanced(node->getRight());
  if(right == -1)
  {
    return -1;
  }

  if(std::abs(left - right) > 1)
  {
    return -1;
  }
  return 1+std::max(left,right);
}
/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    // write a helper function
    // now call it 
    return helperforBalanced(root_) != -1;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
