#include <iostream>

using namespace std;

struct Node{
   int data;

   Node * left;
   Node * right;
};

class BinarySearchTree{
   public:
        Node * root;

        BinarySearchTree(){
           root = nullptr;
        }

        Node * InsertNode(Node * n, const int d){
          //if root is null, insert the first value
          if(n == nullptr){
             n = new Node();

             n->data = d;
             n->left = nullptr;
             n->right = nullptr;
          }else{
             //if node is not null, go to the appropriate node: left or right.
             if(d < n->data){
               n->left = InsertNode(n->left, d);
             }else{
               n->right = InsertNode(n->right, d);
             }
          }

          return n;
        }

         //this is a recursive function
         void TraversalInOrder(Node * node){
            if(node != nullptr) {
                //1. go left
                TraversalInOrder(node->left);
                //2. process Current Node
                cout << node->data << " ";
                //go right
                TraversalInOrder(node->right);
            }

            return;
         }


          //this is a recursive function
          void TraversalPostOrder(Node * node){
             if(node != nullptr){
               //1. go left
               //2. go right
               //3. process the current node
             }

          }

          //this is a recursive function for PreOrderTraversal
          void TraversalPreOrder(Node * node){
              if(node != nullptr){
                //1. process the node
                //2. go to left
                //3. go to right
              }
          }


          //this is a recursive function for search a key
          Node * SearchKey(Node * root, int key){

                if(root == nullptr || root->data == key) return root;

                if(root->data > key){
                     //go left
                     root = SearchKey(root->left, key);
                }else{
                     // go right
                     root =  SearchKey(root->right, key);
                }

                return root;
          }

           //Delete a node
           Node * DeleteKey(Node * root, int key){
               //To be Implemented


           }

           //SUCCESSOR
            Node * Successor(Node * root, int key){
                //To be Implemented


            }

            //PREDECESSOR
            Node * Predecessor(Node * root, int key){
                  //To be Implemented


            }


            //Minimum
            Node * Minumum(Node * root){
                  //To be Implemented


            }

            //Maximum
            Node * Maximum(Node * root){
                   //To be Implemented


             }
};
