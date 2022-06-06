#include <iostream>

using namespace std;

struct Node
{
   int data;
   Node *prev;
   Node *next;
};

struct MyList
{
   Node *head;
   // Node * tail;
};

bool IsEmpty(MyList list)
{
   if (list.head == nullptr)
      return true;
   else
      return false;
}

void Insert(MyList &list, int data)
{
   Node *node = new Node();

   node->data = data;
   node->prev = nullptr;
   node->next = list.head; // node->next points to NULL

   if (list.head == nullptr)
   {
      list.head = node;
      node->prev = nullptr;
   }
   else
   {
      // insert the new node at the beginning of the list
      list.head->prev = node;
      list.head = node;
      node->prev = nullptr;
   }
}

// Traverse the list from the head
void PrintAll(const MyList &list)
{
   Node *temp = list.head;

   if (temp == nullptr)
   {
      std::cout << "list is empty" << std::endl;
   }
   else
   {
      while (temp != nullptr)
      {
         std::cout << temp->data << std::endl;
         temp = temp->next;
      }

      std::cout << "*************************************" << std::endl;
   }
}

Node *Search(const MyList &list, int key)
{
   Node *temp = list.head;

   while (temp != nullptr && temp->data != key)
   {
      temp = temp->next;
   }

   return temp;
}

void Delete(MyList & list, int key)
{
   Node *temp = Search(list, key); // call search()

   if (temp != nullptr)
   {
      if (temp->prev != nullptr)
      {
         temp->prev->next = temp->next;
      }
      else
      {
         list.head = temp->next;
      }

      if (temp->next != nullptr)
      {
         temp->next->prev = temp->prev;
      }
   }
}

int main()
{

   MyList list;

   list.head = nullptr; // initialize the linked-list

   if (IsEmpty(list))
      std::cout << "List is empty" << std::endl;

   Insert(list, 10);

   Insert(list, 20);

   Insert(list, 30);

   Insert(list, 40);

   Insert(list, 50);

   PrintAll(list);

   int x = 24;
   Node *result = Search(list, x);

   if (result == nullptr)
      cout << "Cannot find " << x << endl;
   else
      cout << "Found " << result->data << endl;

   Delete(list, 200);
   PrintAll(list);

   Delete(list, 10);
   PrintAll(list);

   Delete(list, 40);
   PrintAll(list);

   Delete(list, 20);
   PrintAll(list);

   Delete(list, 30);
   PrintAll(list);

   return 0;
}
