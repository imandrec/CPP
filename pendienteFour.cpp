#include <iostream>
using namespace std;

// Check what is the maximum of 2 int
int max(int a, int b) { return (a > b) ? a : b; }

// Returns the maximum value we can put in a knapsack
int knapSack(int Capacity, int Weight[], int Value[], int n)
{

	if (n == 0 || Capacity == 0)
		return 0;

	// If weight of an item is greater than capacity we cant include the item
	if (Weight[n - 1] > Capacity)
		return knapSack(Capacity, Weight, Value, n - 1);

	// Return the maximum of two cases:
	// (1) nth item included
	// (2) not included
	else
		return max(
			Value[n - 1] + knapSack(Capacity - Weight[n - 1],
			Weight, Value, n - 1),
			knapSack(Capacity, Weight, Value, n - 1));
}

//Main function
int main()
{
	int Value[] = { 60, 100, 120 };
	int Weight[] = { 10, 20, 30 };
	int Capacity = 50;
	int n = sizeof(Value) / sizeof(Value[0]);
	cout << "The optime solution is: " << knapSack(Capacity, Weight, Value, n);
	return 0;
}
