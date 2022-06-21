#include <iostream>
using namespace std;

// A utility function that returns
// maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapSack(int Capacity, int Weight[], int Value[], int n)
{

	// Base Case
	if (n == 0 || Capacity == 0)
		return 0;

	// If weight of the nth item is more
	// than Knapsack capacity W, then
	// this item cannot be included
	// in the optimal solution
	if (Weight[n - 1] > Capacity)
		return knapSack(Capacity, Weight, Value, n - 1);

	// Return the maximum of two cases:
	// (1) nth item included
	// (2) not included
	else
		return max(
			Value[n - 1]
			+ knapSack(Capacity - Weight[n - 1],
				Weight, Value, n - 1),
			knapSack(Capacity, Weight, Value, n - 1));
}

// Driver code
int main()
{
	int Value[] = { 60, 100, 120 };
	int Weight[] = { 10, 20, 30 };
	int Capacity = 50;
	int n = sizeof(Value) / sizeof(Value[0]);
	cout << knapSack(Capacity, Weight, Value, n);
	return 0;
}
