#pragma once
ref class Node
{
public:
	Node(double i, double j, int id, Pathfinder^ pathfinder);
	void set_children(vector<Node^ >^ children);
	String^ __str__();
	String^ __repr__();

	bool visited;
		
private:
	
		double i;
		double j;
		int id;
		
		pair<double, double> coordinates(double x, double y);
		
		Pathfinder^ pathfinder;
		vector<Node^ > children;
	}

};

