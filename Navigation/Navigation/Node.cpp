#include "StdAfx.h"
#include "Node.h"


Node::Node(double i, double j, int id, Pathfinder^ pathfinder){
	this->i = i;
	this->j = j;
	this->id = id;
	this->pathfinder = pathfinder;
	this->coordinates = this->pathfinder->array_to_meters(i,j);
	this->children(6,0);
}

Node::set_children(vector<Node^ >^ children){
	this->children = children;
}

String^ Node::__str__(){
	return "ID: %d, I: %d, J: %d, X: %d, Y: %d, Children: %s\n"
		%(this->id,this->i,this->j,this->x,this->y,this->children);
}

String^ Node::__repr__(){
	return "ID: %d, I: %d, J: %d, X: %d, Y: %d, Children: %s\n"
		%(this->id,this->i,this->j,this->x,this->y,[child.id for child in this->children if child != None]);
}