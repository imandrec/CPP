#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int MAX = 100;

class Graph
{
	int graphMatrix[7][7]{
					{0,1,0,0,0,0,0},
					{0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0}
					}; // This matrix help us to perfiorm the prims algorithm
	int PQnumber = 0;
	int V, E;
	vector< pair<int, pair<int, int>> > edges;
	int* root, * Rank;
	
public:
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
		edges.push_back({ 5, {0, 1} });
		edges.push_back({ 3, {0, 2} });
		edges.push_back({ 4, {1, 2} });
		edges.push_back({ 2, {1, 4} });
		edges.push_back({ 5, {1, 3} });
		edges.push_back({ 5, {2, 3} });
		edges.push_back({ 6, {2, 5} });
		edges.push_back({ 6, {3, 4} });
		edges.push_back({ 6, {3, 5} });
		edges.push_back({ 3, {4, 5} });
		edges.push_back({ 5, {4, 6} });
		edges.push_back({ 4, {5, 6} });
		

		// Allocate memory 
		root = new int[V + 1];
		Rank = new int[V + 1];
		for (int i = 0; i <= V; i++)
		{
			Rank[i] = 0;
			root[i] = i;
		}

		
		for (vector< pair<int, pair<int, int>> >::iterator it = edges.begin(); it != edges.end(); it++)
		{
			graphMatrix[it->second.first][it->second.second] = it->first;
			graphMatrix[it->second.second][it->second.first] = it->first;
		}
	}

	int isfind(int num)
	{
		if (num != root[num])
			root[num] = isfind(root[num]);
		return root[num];
	}

	void mergeOrUnionOf2Sets(int first, int second)
	{

		if (Rank[isfind(first)] > Rank[isfind(second)])
			root[isfind(second)] = isfind(first);
		else
			root[isfind(first)] = isfind(second);
		if (Rank[isfind(first)] == Rank[isfind(second)])
			Rank[isfind(second)]++;
	}
	
	
	void kruskalMST() {
		int totalCost = 0; 
		sort(edges.begin(), edges.end());

		cout << "\nEdges of Minimum spanning tree with kruskal Algorithm\n";
		

		vector< pair<int, pair<int, int>> >::iterator it;
		for (it = edges.begin(); it != edges.end(); it++)
		{
			int set_u = isfind(it->second.first);
			int set_v = isfind(it->second.second);

			// it->second.second == it->second.first cycle present 
			if (set_u != set_v)
			{
				cout <<"\t"<< char(97 + it->second.first) << " - " << char(97 + it->second.second) << " = "<<it->first << endl;

				totalCost += it->first;
				mergeOrUnionOf2Sets(set_u, set_v);
			}
		}
		cout << "Total cost of minimum spanning tree with kruskal Algorithm : " << totalCost << endl << endl;
	}

	
	bool allvisited(bool arr[7]) {
		for (int i = 0; i < 7; i++) {
			if (!arr[i]) {
				return false;
			}
		}
		return true;
	}
	void prims(int source)
	{
		cout << "\n\n\nEdges of Minimum spanning tree with prims Algorithm\n";

		
		priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> > priorityQueue;
		bool visited[7] = {false};
		bool inQueue[7] = { false };

		visited[source] = true; //Mark the starting node as a visited node
		for (int j = 0; j < V; j++) { // Put all the edges of a node in the priority queue
			if (graphMatrix[source][j] != 0) {
				priorityQueue.push(make_pair(graphMatrix[source][j], make_pair(source, j)));
			}
		}


		int cost = 0;
		
		while (!priorityQueue.empty()) {
			source = priorityQueue.top().second.second;
			

			if (!allvisited(visited) && !visited[source]) {
				cout << char(97 + priorityQueue.top().second.first) << " - " << char(97 + priorityQueue.top().second.second) << " = " << priorityQueue.top().first << endl;
				cost += priorityQueue.top().first;
				priorityQueue.pop();
				visited[source] = true;
				for (int j = 0; j < V; j++) { // Put all the edges of a node in the priority queue
					if (graphMatrix[source][j] != 0) {
						if (!visited[j]) {
							priorityQueue.push(make_pair(graphMatrix[source][j], make_pair(source, j)));
						}
					}
				}
			}
			else if(allvisited(visited)) {
				cout << "Total cost of minimum spanning tree with prims Algorithm : " << cost << endl << endl;
				return;
			}
			else if (visited[source]) {
				priorityQueue.pop();
			}

		}
				
		


	}
	
	
};



int main()
{
	Graph g(7, 12);
	g.kruskalMST(); // Q3
	g.prims(0); // Q4

	return 0;
}
