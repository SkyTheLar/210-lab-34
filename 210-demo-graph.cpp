/************************************************

COMSC 210 | Lab 34 | Skylar Robinson | IDE: Used Eclipse

*************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Neighborhood Roads:" << endl
        	 << "=====================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << "House " << i << " has roads connecting to:\n";
            for (Pair v : adjList[i])
                cout << "\tHouse " << v.first << " (Travel time: " << v.second << " minutes)\n";
        }
        cout << endl;
    }
};

void DFS(Graph);
void BFS(Graph);

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,8},{0,2,21},{1,2,6},{1,3,5},{1,4,4},{2,7,11},{2,8,8},{3,4,9},{5,6,10},
		{5,7,15},{5,8,5},{6,7,3},{6,8,7}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    DFS(graph);
    BFS(graph);

    return 0;
}

void DFS(Graph g) {
	vector<int> visited = {0};
	vector<int> search;
	stack<int> toVisit;
	cout << "Trick-or-treat path (DPS) starting from House 0:\n";
	cout << "=======================================\n";
	search.push_back(0); //0 is always the first node
	cout << "Stopping at House 0\n";
	for (Pair p : g.adjList[0]) {
		cout << "\tNext house: House " << p.first << endl;
		toVisit.push(p.first);
		visited.push_back(p.first);
	}
	while (!toVisit.empty()) {
		int next = toVisit.top();
		//add node to list
		cout << "Stopping at House " << next << endl;
		search.push_back(toVisit.top());
		//remove node from queue
		toVisit.pop();
		//add unvisited adjacent nodes to the queue
		for (Pair p : g.adjList[next]) {
			auto it = find(visited.begin(), visited.end(), p.first);
			if (it == visited.end()) {
				cout << "\tNext house: House " << p.first << endl;
				toVisit.push(p.first);
				visited.push_back(p.first);
			}
		}
	}
	cout << endl;
}

void BFS(Graph g) {
	vector<int> visited = {0};
	vector<int> search;
	deque<int> toVisit;
	cout << "Asking neighbors for your lost package (BPS) starting from House 0:\n";
	cout << "=======================================\n";
	search.push_back(0); //0 is always the first node
	cout << "Searching House 0\n";
	for (Pair p : g.adjList[0]) {
		cout << "\tNext house: House " << p.first << endl;
		toVisit.push_back(p.first);
		visited.push_back(p.first);
	}
	while (!toVisit.empty()) {
		int next = toVisit.front();
		//add node to list
		search.push_back(toVisit.front());
		cout << "Searching House " << next << endl;
		//remove node from queue
		toVisit.pop_front();
		//add unvisited adjacent nodes to the queue
		for (Pair p : g.adjList[next]) {
			auto it = find(visited.begin(), visited.end(), p.first);
			if (it == visited.end()) {
				cout << "\tNext house: House " << p.first << endl;
				toVisit.push_back(p.first);
				visited.push_back(p.first);
			}
		}
	}
}
