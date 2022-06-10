#include <iostream>
#include "BinarySearchTree.cpp"

using namespace std;

int main(){

   BinarySearchTree * tree = new BinarySearchTree();

   int numbers[] = {50, 76, 21, 4, 32, 64, 15, 52};

   for(int i = 0 ; i < 8; i++){
       tree->root = tree->InsertNode(tree->root, numbers[i]);
   }

   tree->TraversalInOrder(tree->root);

   cout << endl;

   tree->TraversalPostOrder(tree->root);

   cout << endl;

   tree->TraversalPreOrder(tree->root);

   cout << endl;

   std::cout << "Min value : " << tree->Minumum(tree->root)->data;

   cout << endl;

   std::cout << "Max value :" << tree->Maximum(tree->root)->data;

   cout << endl;

   int key = 64;
   Node * searchKey = tree->SearchKey(tree->root, key);

   if(searchKey != nullptr){
      cout << "Found the key: " << searchKey->data << endl;
   } else{
      cout << "Not Found the key: " << key << endl;
  }

   std::cout << "Successor : " << tree->Successor(tree->root, key)->left->data;

   cout << endl;

   std::cout << "Predecessor : " << tree->Predecessor(tree->root,key)->right->data;

   cout << endl;

    tree->DeleteKey(tree->root,key);

    std::cout << "Deleted key : " << key;

   cout << endl;

    tree->TraversalInOrder(tree->root);

   cout << endl;

   //delete tree; //deallocate the search tree

   return 0;
}
