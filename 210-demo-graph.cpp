/************************************************

COMSC 210 | Lab 34 | Skylar Robinson | IDE: Used Eclipse

*************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
using namespace std;

const int SIZE = 7;

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
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

vector<int> DFS(Graph);
vector<int> BFS(Graph);

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "DFS starting from vertex 0:\n";
    vector<int> dSearch = DFS(graph);
    for (int i : dSearch)
    	cout << i << " ";

    cout << "\nBFS starting from vertex 0:\n";
    vector<int> bSearch = BFS(graph);
    for (int i : bSearch)
    	cout << i << " ";

    return 0;
}

vector<int> DFS(Graph g) {
	vector<int> search;
	stack<int> toVisit;
	search.push_back(0); //0 is always the first node
	for (Pair p : g.adjList[0]) {
		toVisit.push(p.first);
	}
	while (!toVisit.empty()) {
		int next = toVisit.top();
		//check if node is already in list, if not add it
		auto it = find(search.begin(), search.end(), toVisit.top());
			if (it == search.end())
				search.push_back(toVisit.top());
		//remove node from queue
		toVisit.pop();
		//add unvisited adjacent nodes to the queue
		for (Pair p : g.adjList[next]) {
			auto it = find(search.begin(), search.end(), p.first);
			if (it == search.end())
				toVisit.push(p.first);
		}
	}
	return search;
}

vector<int> BFS(Graph g) {
	vector<int> search;
	deque<int> toVisit;
	search.push_back(0); //0 is always the first node
	for (Pair p : g.adjList[0]) {
		toVisit.push_back(p.first);
	}
	while (!toVisit.empty()) {
		int next = toVisit.front();
		//check if node is already in list, if not add it
		auto it = find(search.begin(), search.end(), toVisit.front());
			if (it == search.end())
				search.push_back(toVisit.front());
		//remove node from queue
		toVisit.pop_front();
		//add unvisited adjacent nodes to the queue
		for (Pair p : g.adjList[next]) {
			auto it = find(search.begin(), search.end(), p.first);
			if (it == search.end())
				toVisit.push_back(p.first);
		}
	}
	return search;
}
