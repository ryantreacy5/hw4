#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool depthCheck(Node* node, int depth, int& leafHeight)
{
  if(node == NULL)
  {
    return true;
  }
  // next we need to check of its a lead node by checking the next node
  //if(node->next == nullptr && node->right == nullptr)
  if(node-> left == nullptr && node->right == nullptr)
  {
    //if(leafHeight == 0)
    if(leafHeight == -1)
    {
      //depth = leafHeight;
      leafHeight = depth;
    }
    return depth == leafHeight;
  }
  //return depthCheck(node->left, depth+1, leafHeight) && return depthCheck(node->right, depth+1, leafHeight);
  return depthCheck(node->left, depth+1, leafHeight) && depthCheck(node->right, depth+1, leafHeight);
}


bool equalPaths(Node * root)
{
    // Add your code below
    // ok first step in recursion is base case per usual: 
   // if(root == NULL)
   // {
       // return; wait its a bool it needs to return true or false
     //  return true;
  // }   
    // in class he said it is extremely similar to the pseudocode
    // from slides: Three general traversal orderings
    //Pre-order [Process root then visit subtrees]
    //In-order [Visit left subtree, process root, visit right subtree]
    //Post-order [Visit left subtree, visit right subtree, process root]
    // useful principle: should handle only one element
    // then use recursion to handle the remaining elements
    // and finally combine the solutions to the recursive calls with the one element being handled
   // if(root->left == NULL && root->right == NULL)
   // {
    //  return true;
    //}
   // if(root->left == NULL && root->right != NULL)
   // {
     // return false;
   // }
   // if(root->left != NULL && root->right == NULL)
   // {
   //  return false;
  //  }
   int depth = -1;
   return depthCheck(root, 0, depth);
   
    //return equalPaths(root->left) && equalPaths(root->right);

    

}

