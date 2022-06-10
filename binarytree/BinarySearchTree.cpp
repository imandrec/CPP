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
                std::cout << node->data << " ";
                //go right
                TraversalInOrder(node->right);
            }

            return;
         }


          //this is a recursive function
          void TraversalPostOrder(Node * node){
             if(node != nullptr){
               //1. go left
               TraversalPostOrder(node->left);
               //2. go right
               TraversalPostOrder(node->right);
               //3. process the current node
               std::cout << node->data << " ";
             }

          }

          //this is a recursive function for PreOrderTraversal
          void TraversalPreOrder(Node * node){
              if(node != nullptr){
                //1. process the node
                std::cout << node->data << " ";
                //2. go to left
                TraversalPreOrder(node->left);
                //3. go to right
                TraversalPreOrder(node->right);
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
      Node* DeleteKey(Node* root, int key) {
		
		if (root == NULL) return root;
		if (key < root->data)
			root->left = DeleteKey(root->left, key);
		else if (key > root->data)
			root->right = DeleteKey(root->right, key);
		else 
		{
			if (root->left == NULL) {
				Node* temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == NULL) {
				Node* temp = root->left;
				free(root);
				return temp;
			}
			Node* temp = Minumum(root->right);
			root->data = temp->data;
			root->right = DeleteKey(root->right, temp->data);
		}
		return root;
	}
           //SUCCESSOR
            Node * Successor(Node * root, int key){
                //To be Implemented
               

            if (!root) return nullptr;
            if (root->data == key)
		      {
               Node* temp = root->right;
		         while (temp->left) 
                  temp = temp->left;
               root = temp;
            }
		         return root;
            }

            //PREDECESSOR
            Node * Predecessor(Node * root, int key){
                  //To be Implemented

               if (!root) return nullptr;
               if (root->data == key)
		         {root = root->left;
		         while (root->right) root = root->right;}
		         return root;
            }


            //Minimum
            Node * Minumum(Node * root){
                  //To be Implemented
               Node* current = root;
               while (current && current->left != NULL)
                  current = current->left;
               return current;
            }

            //Maximum
            Node * Maximum(Node * root){
                   //To be Implemented
                Node* current = root;
               while (current && current->right != NULL)
                  current = current->right;
               return current;

             }
};
