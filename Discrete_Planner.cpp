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


bool is_valid(int world_state[6][6], pair<int, int> cur_pose) {
	if (world_state[cur_pose.first][cur_pose.second] == 0
		&& cur_pose.first>=0 && cur_pose.first<6
		&& cur_pose.second >= 0 && cur_pose.second<6) {
		return true;
	}
	return false;
};

bool is_reached(pair<int, int>goal_pose, pair<int, int>cur_pose) {
	if (goal_pose == cur_pose) {
		//cout << "Goal Reached";
		return true;
	}
	return false;
};


vector<pair<int, int>> trace(cell cell_table[6][6], cell q, cell source) {
	vector<pair<int, int>> path;
	stack<pair<int, int>> tmp;
	pair<int, int> cur_pose = make_pair(q.i, q.j);
	while (q.parent_i != source.i || q.parent_j != source.j) {
		q = cell_table[q.parent_i][q.parent_j];
		cur_pose = make_pair(q.i,q.j);
		tmp.push(cur_pose);
	}
	path.push_back(make_pair(source.i, source.j));
	while (!tmp.empty()) {
		path.push_back(tmp.top());
		tmp.pop();
	}
	return path;
};

vector<pair<int, int>> Optimal_Planner::search(int world_state[6][6], pair<int, int> robot_pose, pair<int, int> goal_pose) {
	if (!is_valid(world_state, robot_pose) || !is_valid(world_state, goal_pose)) {
		cout << "robot_pose or goal_pose is invalid" << endl;
		return {};
	}

	if (!isnt_blocked(robot_pose, world_state) || !isnt_blocked(goal_pose, world_state)) {
		cout << "robot_pose or goal_pose is blocked" << endl;
		return {};
	}

	vector<pair<int, int>> path;
	cell source;
	source.i = robot_pose.first;
	source.j = robot_pose.second;
	source.parent_i = robot_pose.first;
	source.parent_j = robot_pose.second;

	cell cell_table[6][6];
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			cell_table[i][j].i = i;
			cell_table[i][j].j = j;
			cell_table[i][j].parent_i = -1;
			cell_table[i][j].parent_j = -1;
		}
	}

	bool visited[6][6];
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (world_state[i][j] == 1) {
				visited[i][j] = true;
			}
			else {
				visited[i][j] = false;
			}
		}
	}

	queue<cell> q;
	q.push(source);
	cell_table[source.i][source.j] = source;
	visited[source.i][source.j] = true;

	while (!q.empty()) {
		cell p = q.front();
		q.pop();
		if (p.i == goal_pose.first&& p.j == goal_pose.second) {
			visited[p.i][p.j] = true;
			path = trace(cell_table,p,source);
			cout << "op path found!"<<endl;
			return path;
		}
		//move up
		if ((p.i - 1) >= 0 && visited[p.i - 1][p.j] == false) {
			cell next;
			next.i = p.i - 1;
			next.j = p.j;
			next.parent_i = p.i;
			next.parent_j = p.j;
			cell_table[next.i][next.j] = next;
			q.push(next);
			visited[p.i - 1][p.j] = true;
		}
		//move down
		if ((p.i + 1) < 6 && visited[p.i + 1][p.j] == false) {
			cell next;
			next.i = p.i + 1;
			next.j = p.j;
			next.parent_i = p.i;
			next.parent_j = p.j;
			cell_table[next.i][next.j] = next;
			q.push(next);
			visited[p.i + 1][p.j] = true;
		}
		//move left
		if ((p.j - 1) >= 0 && visited[p.i][p.j - 1] == false) {
			cell next;
			next.i = p.i;
			next.j = p.j - 1;
			next.parent_i = p.i;
			next.parent_j = p.j;
			cell_table[next.i][next.j] = next;
			q.push(next);
			visited[p.i][p.j - 1] = true;
		}
		//move right
		if ((p.j + 1) < 6 && visited[p.i][p.j + 1] == false) {
			cell next;
			next.i = p.i;
			next.j = p.j + 1;
			next.parent_i = p.i;
			next.parent_j = p.j;
			cell_table[next.i][next.j] = next;
			q.push(next);
			visited[p.i][p.j + 1] = true;
		}
	}
	cout << "op path not found" << endl;
	return {};
}

vector<pair<int, int>> check_memory(vector<pair<int, int>> visited_table, unsigned int memory) {
	if (visited_table.size() >= memory) {
		visited_table.erase(visited_table.begin());
	}
	return visited_table;
}

bool isnt_blocked(pair<int, int > option, int world_state[6][6]) {
	if (world_state[option.first][option.second] == 1) {
		return false;
	}
	return true;
}

vector<pair<int, int>> Random_Planner::search(int world_state[6][6], pair<int, int> robot_pose, pair<int, int> goal_pose) {
	if (!is_valid(world_state, robot_pose) || !is_valid(world_state, goal_pose)) {
		cout << "robot_pose or goal_pose is invalid" << endl;
		return {};
	}

	if (!isnt_blocked(robot_pose, world_state) || !isnt_blocked(goal_pose, world_state)) {
		cout << "robot_pose or goal_pose is blocked" << endl;
		return {};
	}

	vector<pair<int, int>> path;
	int max_step_number = 50;
	unsigned int memory = sqrt(max_step_number);
	int count = 0;

	//initialization of the table that keeps track of all unit information
	path.push_back(robot_pose);
	pair<int, int> current;
	current = robot_pose;
	vector<pair<int, int>> visited_table;
	visited_table.push_back(current);
	while (count < max_step_number) {
		int i = current.first, j = current.second;
		pair<int,int> decision;
		vector<pair<int, int>> options;
		pair<int, int> top, down, left, right;
		top.first = i - 1, top.second = j;
		down.first = i + 1, down.second = j;
		left.first = i, left.second = j - 1;
		right.first = i, right.second = j + 1;
		if (is_valid(world_state,top) && isnt_blocked(top,world_state)) {
			options.push_back(top);
		}
		if (is_valid(world_state, down) && isnt_blocked(down, world_state)) {
			options.push_back(down);
		}
		if (is_valid(world_state, left) && isnt_blocked(left, world_state)) {
			options.push_back(left);
		}
		if (is_valid(world_state, right) && isnt_blocked(right, world_state)) {
			options.push_back(right);
		}

		vector<pair<int, int>> copy;
		copy = options;
		for (int i = 0; i < copy.size(); ++i) {
				vector<pair<int, int>>::iterator it;
				it = find(visited_table.begin(), visited_table.end(), options[i]);
				if (it!=visited_table.end()) {
					copy.erase(copy.begin() + i);
				}
			}
			if (copy.size() > 0) {
				decision = copy[rand() % copy.size()];
				path.push_back(decision);
				visited_table = check_memory(visited_table, memory);
				visited_table.push_back(decision);
				current = decision;
				count++;
				if (is_reached(goal_pose, current)) {
					cout << "rd path found" << endl;
					return path;
				}
			}
			else {
				decision = options[rand() % options.size()];
				path.push_back(decision);
				visited_table = check_memory(visited_table,memory);
				visited_table.push_back(decision);
				current = decision;
				count++;
				if (is_reached(goal_pose, current)) {
					cout << "rd path found" << endl;
					return path;
				}
			}
	}
	cout << "rd path not found" << endl;
	return {};
}
