#include <bits/stdc++.h>
#include <fstream>
using namespace std;

struct node {
	int x;
	int y;
};

void generate_coordinates() {
	
}

void rectify_dimensions(int* length, int* breadth, int* side) {
	int rem_l = *length % *side;
	int rem_b = *breadth % *side;
	if (rem_l != 0) *length = *length - rem_l;
	if (rem_b != 0) *breadth = *breadth - rem_b;
}

void generate_coordinates(int l, int b, int a, float rem_l, float rem_b, vector<float> &x, vector<float> &y) {
	for (int i=0; i<=b; i+=a) {
		for (int j=0; j<=l; j+=a) {
			x.push_back((j+rem_l));
			y.push_back((i+rem_b));
		}
	}
}

void generate_elements(int l, int b, int a, vector<vector<int>> &node_map) {
	int n_l = (l / a);
	int n_b = (b / a);
	int nodes[n_l][n_b];
	int node_index = 0;
	for (int i=0; i<=n_b; i+=1) {
		for (int j=0; j<=n_l; j+=1) {
			nodes[i][j] = node_index;
			node_index += 1;
		}
	}
	for (int i=0; i<n_b; i+=1) {
		for(int j=0; j<n_l; j+=1) {
			vector<int> coordinates;
			int idx = nodes[i][j];
			coordinates.push_back(idx);
			coordinates.push_back(idx+1);
			coordinates.push_back(idx+n_b+2);
			coordinates.push_back(idx+n_b+1);
			node_map.push_back(coordinates);
		}
	}
}

string display_results(vector<float> x, vector<float> y, vector<vector<int>> node_map) {
	string file = "";
	int node_count = x.size();
	int element_count = node_map.size();
	file += "No of Nodes: " + to_string(node_count) + "\n";
	file += "Nodes Data: \n";
	file += "Node No \t X Coordinate \t Y Coordinate \n";
	for (int i=0; i<node_count; i+=1) {
		file += to_string(i) + " \t " + to_string(x[i]) + " \t " + to_string(y[i]) + "\n";
	}
	file += "\n";
	file += "No of Elements: " + to_string(element_count) + "\n";
	file += "Element No \t Node 1 \t Node 2 \t Node 3 \t Node 4 \t \n";
	for (int i=0; i<element_count; i++) {
		vector<int> element = node_map[i];
		file += to_string(i);
		for (int j=0; j<4; j+=1) {
			file += "\t" + to_string(element[j]);
		}
		file += "\n";
	}
	cout << file;
	return file;
}

int main() {
	int l,b,a, length, breadth, side;
	float rem_l, rem_b;
	vector<float> x;
	vector<float> y;
	vector<vector<int>> node_map;
	cout << "Enter Length and Breadth of the Rectangle" << endl;
	cin >> length >> breadth;
	cout << "Enter Side Length of the Square Element" << endl;
	cin >> side;
	l = length;
	b = breadth;
	a = side;
	rectify_dimensions(&l, &b, &a);
	rem_l = (length - l)/2.0;
	rem_b = (breadth - b)/2.0;
	cout << endl;
	generate_coordinates(l, b, a, rem_l, rem_b, x, y);
	generate_elements(l, b, a, node_map);
	string file = display_results(x,y,node_map);
	ofstream out("results.txt");
	out << file;
	out.close();
}
