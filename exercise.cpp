#include <iostream>
#include <algorithm>

using namespace std;

//Item for the bag
struct Item {
	int val, wght;

	// Constructor
	Item(int value, int weight)
	{
		val = value;
		wght = weight;
	}
};

//bool cmp function
bool cmp(struct Item a, struct Item b)
{
	int r1 = (int)a.val / (int)a.wght;
	int r2 = (int)b.val / (int)b.wght;
	return r1 > r2;
}

// main function
int Knapsack(int capacity, struct Item arr[], int n)
{
	// sort Item
	sort(arr, arr + n, cmp);

	int result = 0.0; 

	// Looping through all Items
	for (int i = 0; i < n; i++) {
	    
		if (arr[i].wght <= capacity) {
			capacity = capacity - arr[i].wght;
			result = result + arr[i].val;
		}

		// If we can't add current Item, add fractional part(double)
		else {
			result
				+= arr[i].val
				* ((double)capacity / (double)arr[i].wght);
			break;
		}
	}

	return result;
}

// Main function
int main()
{
	int capacity = 50; 
	Item arr[] = { { 60, 10 }, { 100, 20 }, { 120, 30 } }; //Value,weight

	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "Maximum value we can obtain = " << Knapsack(capacity, arr, n);
	return 0;
}
