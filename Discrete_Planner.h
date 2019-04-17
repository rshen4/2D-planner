// FILE:          Discrete_Planner.h
// SUBMITTED BY:  Rui Shen
//                All code is my own except where credited to others.
// PURPOSE:
// This program inplements two different 2D path planner: random planner
// and optimal planner
//
// OVERALL METHOD:
// Both planners share the same interface:
// search(world_state, robot_pose, goal_pose) return path
// This is realized though creating a base class "Discrete_Planner" and a
// virtual member function. 
// Both planners receive the same input and return a path as a vector of 
// tuples. When a path is not found, they return an empty vector;
//
// Optimal_Planner:
// Time complexity: O(V) V is the total number of nodes.
// Since the graph is unweighted, the optimal plannar implements BFS on
// matrix cells to find the shortest path. BFS is implemented using queue.
//
// Random_Planner: 
// Time complexity: O(M*sqrt(M)) M is maximum step number.
// The random planner makes a "decision" randomly based on given "options".
// "options" contains adjacent nodes that are not visited in its “memory”
// However, when the only unblocked adjacent node is also visited in "memory"
// this node will become the decision;


#include "stdafx.h"
#include <utility> 
#include<vector>
#include<iostream>
#include<set>
#include <queue> 
#include <functional>
#include<stack>
#include<math.h>
#include<conio.h>

using namespace std;

struct unit {
	int parent_i, parent_j;
};

struct cell {
public:
	int i, j, parent_i, parent_j;
};

class Discrete_Planner {
public:
	virtual vector<pair<int, int>> search(int world_state[6][6], pair<int, int> robot_pose, pair<int, int> goal_pose) {
		cout << "please specify planner type" << endl;
		return {};
	}
};

class Random_Planner : public Discrete_Planner {
	vector<pair<int, int>> search(int world_state[6][6], pair<int, int> robot_pose, pair<int, int> goal_pose);
};

class Optimal_Planner : public Discrete_Planner {
	vector<pair<int, int>> search(int world_state[6][6], pair<int, int> robot_pose, pair<int, int> goal_pose);
};

//check if a node is on the map
bool is_valid(int world_state[6][6], pair<int, int> robot_pose);

//test if the goal is reached
bool is_reached(pair<int, int>goal_pose, pair<int, int>cur_pose);

//This function would delete the first memorized node and memory limit is reached.
vector<pair<int, int>> check_memory(vector<pair<int, int>> visited_table, unsigned int memory);

//test if the chosen node is blocked (!=0)
bool isnt_blocked(pair<int, int > option, int world_state[6][6]);

//generate a path based on parent nodes of visited nodes.
vector<pair<int, int>> trace(cell cell_table[6][6], cell q, cell source);