/*
* Name: Joshua Shor
* Student ID: 200968955
* Email: shor002@cougars.csusm.edu
*
Write a C++ program to implement the Depth First Search (DFS),
Breadth First Search (BFS), and hasCycle methods of a directed graph.
Use adjacency list to implement a directed graph.
Create and use your own list (for adjacency list) and queue
(for BFS) data structures.

*/

#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

//functions and classes
struct edge {
	int adj_vtx; // index of adjacent vertex
	struct edge* next; // the link to the next node in the list.
};


//making queue class for BFS
template <class Qu>
class Queue {
private:
	Qu* arr;
	int head, rear, cap;

public:
	Queue(int size) {
		cap = size;
		head = -1;
		rear = -1;
		arr = new Qu[cap];

	}
	Qu frnt() {
		return arr[head];
	}
	void pushBack(Qu data) {
		rear++;
		rear %= cap;
		arr[rear] = data;
		if (head == -1)head = rear;
	}
	void popFrnt() {
		if (head == rear)
			head = rear = -1;
		else {
			head++;
			head %= cap;
		}
	}
	bool empty() {
		return head == -1;
	}
	bool full() {
		return (rear + 1) % cap == head;
	}
};

//creating list for adjacency list
class Node {
public:
	int data;
	Node* next;
	Node()
	{
		data = 0;
		next = NULL;
	}
	Node(int data)
	{
		this->data = data;
		this->next = NULL;
	}
};

class A_List {
	Node* head;
public:
	A_List() :head(NULL) {}
	void a_pushBack(int i);
};

void A_List::a_pushBack(int i) {
	Node* node = new Node(i);

	if (head == NULL) {
		head = node;
		return;
	}

	Node* curr = head;
	while (curr) {
		if (!curr->next) {
			curr->next = node;
			return;
		}
		curr = curr->next;
	}
}


class Graph {
	int v;							// No. of vertices
	//edge** adj;	//kept running into errors with this
					//no time to fix anymore
	list<int>* adj;
	void DFSUtil(int v, bool visted[]); // A function used by DFS
	bool hasCycleUtil(int v, bool vis[], bool* bktrk);
public:
	Graph(int V); //Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void BFS(int s); // prints BFS traversal of the complete graph
	void DFS(int v); // prints DFS traversal of the complete graph
	bool hasCycle(); // Check whether the graph has a cycle.
};

Graph::Graph(int v)
{
	this->v = v;
	//adj = new edge*;
	adj = new list<int>[v];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

//Depth First Search
void Graph::DFS(int v)
{
	// Mark all the vertices as not visited
	bool* visited = new bool[v];
	for (int i = 0; i < v; i++)
		visited[i] = false;

	// Call the recursive helper function to print DFS traversal
	DFSUtil(v, visited);
}

void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;
	cout << v << "->";

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		if (!visited[*i]) {
			DFSUtil(*i, visited);
		}
	}
}

//Breadth First Search  
void Graph::BFS(int s)
{
	bool* visited = new bool[v];
	for (int i = 0; i < v; i++) {
		visited[i] = false;
	}
	Queue<int> q(v);
	visited[s] = true;
	q.pushBack(s);

	while (!q.empty())
	{
		s = q.frnt();
		cout << s << ' ';
		cout << "->";
		q.popFrnt();

		for (int i = 0; i < v; i++) {
			if (!visited[i])
			{
				visited[i] = true;
				q.pushBack(i);
			}
		}
	}
}

bool Graph::hasCycle() {
	bool* visited = new bool[v];
	bool* backTrack = new bool[v];
	for (int i = 0; i < v; i++) {
		visited[i] = false;
		backTrack[i] = false;
	}
	for (int i = 0; i < v; i++) {
		if (hasCycleUtil(i, visited, backTrack));
		return true;
	}


	return false;
}

bool Graph::hasCycleUtil(int v, bool vis[], bool* backTrack) {
	vis[v] = true;
	backTrack[v] = true;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); i++) {
		if (!vis[*i] && hasCycleUtil(*i, vis, backTrack)) {
			return true;
		}
		else {
			return false;
		}
	}
}


int main() {

	bool foundCycleDFS;

	cout << "hello!" << endl;

	// Create a graph given in the above diagram

	cout << "BSF TEST!" << endl;
	Graph bfsgraf(4);
	bfsgraf.addEdge(0, 1);
	bfsgraf.addEdge(0, 2);
	bfsgraf.addEdge(1, 3);
	bfsgraf.addEdge(2, 3);
	bfsgraf.addEdge(4, 3);
	bfsgraf.addEdge(3, 2);
	bfsgraf.addEdge(0, 2);
	bfsgraf.BFS(5);


	cout << "\nDFS TEST!" << endl;
	Graph dfsgraf(4);
	dfsgraf.addEdge(0, 1);
	dfsgraf.addEdge(0, 2);
	dfsgraf.addEdge(1, 3);
	dfsgraf.addEdge(2, 0);
	dfsgraf.addEdge(2, 3);
	dfsgraf.addEdge(3, 3);
	dfsgraf.DFS(2);

	foundCycleDFS = dfsgraf.hasCycle();

	if (foundCycleDFS)
		cout << "\ngraph is cyclic" << endl;
	else
		cout << "\ngraph is not cyclic" << endl;


	return 0;
}