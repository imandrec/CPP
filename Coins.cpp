#include <limits.h>
#include <iostream>
#include <string>
using namespace std;

//Function to know minimum number of coins required
int minCoins(int coins[], int m, int V)
{
	if (V == 0) return 0;

	int res = INT_MAX;

	// Check every coin 
	for (int i = 0; i < m; i++)
	{
		if (coins[i] <= V)
		{
			int sub_res = minCoins(coins, m, V - coins[i]);

			// Check for INT_MAX
			if (sub_res != INT_MAX && sub_res + 1 < res)
				res = sub_res + 1;
		}
	}
	return res;
}

int main()
{
	int coins[] = { 1, 3, 5, 7 };
	int m = sizeof(coins) / sizeof(coins[0]);
	int V = 15;
	cout << "Demonimation: 1,3,5,7\nDesired change : " + to_string(V) + "\nCoins required: " << minCoins(coins, m, V);

	return 0;
}
