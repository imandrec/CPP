#include<iostream>
using namespace std;

//Create node
struct Node {
    int data;
    Node* next;
    Node(int d)
    {
        data = d;
        next = NULL;
    }
};

//Define Queue
struct Queue {
    Node* front, * rear;
    Queue()
    {
        front = rear = NULL;
    }

    void enQueue(int x)
    {
        Node* temp = new Node(x);

        // If queue is empty, front and rear are the same
        if (rear == NULL) {
            front = rear = temp;
            return;
        }

        // Add the new node at the end
        rear->next = temp;
        rear = temp;
    }

    // Function to remove a value
    void deQueue()
    {
        if (front == NULL)
            return;

        // Move node to the next
        Node* temp = front;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete (temp);
    }
};

int main()
{

    Queue q;
    q.enQueue(1);
    q.enQueue(2);
    q.deQueue();
    q.enQueue(3);
    q.enQueue(4);
    q.deQueue();
    cout << "Queue Front : " << (q.front)->data << endl;
    cout << "Queue Rear : " << (q.rear)->data;
}
