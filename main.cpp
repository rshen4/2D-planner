// FILE:          main.cpp
// SUBMITTED BY:  Rui Shen
//                All code is my own except where credited to others.
// PURPOSE:
// This file is to test and compare the correctness of both planners;
//
// Result:
// Both planners correctly generate a path for test2 and returned an
// empty vector when the goal is blocked(test1)
// In test2, optimal planner is able to find the shortest path
// when the goal or start is out of bound(>5||<0), the program can throw 
// an error message and return an empty vector

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
#include "Discrete_Planner.h"

using namespace std;

int main()
{
	int test1[6][6] = {
	{ 0,0,1,0,0,0 },
	{ 0,0,1,0,0,0 },
	{ 0,0,0,0,1,0 },
	{ 0,0,0,0,1,0 },
	{ 0,0,1,1,1,1 },
	{ 0,0,0,0,1,0 }
	};
	int test2[6][6] = {
	{ 0,0,1,0,0,0 },
	{ 0,0,1,0,0,0 },
	{ 0,0,0,0,1,0 },
	{ 0,0,0,0,1,0 },
	{ 0,0,1,1,1,0 },
	{ 0,0,0,0,0,0 }
	};
	vector<pair<int, int>> path_rd;
	vector<pair<int, int>> path_op;
	pair<int, int> robot_pose;
	robot_pose.first = 0;
	robot_pose.second = 0;
	pair<int, int> goal_pose;
	goal_pose.first = 5;
	goal_pose.second = 5;
	Discrete_Planner *dpptr;
	Random_Planner rd;
	Optimal_Planner op;
	dpptr = &rd;

	//change test name to conduct different test
	path_rd = dpptr->search(test2, robot_pose, goal_pose);

	cout << "rd path:" << endl;
	for (unsigned int i = 0; i < path_rd.size(); ++i) {
		cout << path_rd[i].first << "," << path_rd[i].second << endl;
	}
	cout << "rd_steps:" << path_rd.size() << endl;
	dpptr = &op;

	//change test name to conduct different test
	path_op = dpptr->search(test2, robot_pose, goal_pose);

	cout << "op path:" << endl;
	for (unsigned int i = 0; i < path_op.size(); ++i) {
		cout << path_op[i].first << "," << path_op[i].second << endl;
	}
	cout << "op_steps:" << path_op.size() << endl;
	_getch();
	return 0;
}

