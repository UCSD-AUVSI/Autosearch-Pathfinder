#pragma once
ref class AdjacencyList
{
	def __init__(self,array):
		self.arr = array
		
	def push(self,node):
		self.arr.append(node)
		
	def node_at(self,i,j):
		# print "Array length: %d, Index: %d" %(len(self.arr),y*self.width+x)
		for node in self.arr:
			if node.i == i and node.j == j:
				return node
		return None
	
	def __str__(self):
		return "Array: %s"%(self.arr)
	
	def __repr__(self):
		return "Array: %s"%(self.arr)
}

