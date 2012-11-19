// pathfinder.cpp : 定义控制台应用程序的入口点。
//

#include "Autosearch.h"
#include "Pathfinder.h"
#include <array>
#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::pair;
using std::string;
using namespace System;


array<double> Pathfinder::buildPath(double width, double height, Autosearch^ data){
	width_meters = convertToInt(data -> width_meters);
	height_meters = convertToInt(data -> height_meters);

	array_height = convertToInt(height_meters/ PATH_WIDTH) + 1;
	array_width = convertToInt(width_meters/ PATH_WIDTH) + 1;


	cout<< "There are " << array_height * array_height <<" nodes."<<endl;
	cout<< "Array width: " << array_width <<endl;
	cout<< "Array height: " << array_height <<endl;

	this -> autoSearch = data;

	//break field into triangles
	triangle_array = build_array();
	//build graph out of vertices
	adj_list = build_triangles(triangle_array); 
	// make path out of graph
	path = make_path(adj_list);
	create_image(path, autoSearch -> array,'map_nofix.jpg');
	fix_path(path, autoSearch -> array, autoSearch -> perimeters, autoSearch -> center);
	create_image(path, autoSearch -> array,'map.jpg');
	create_file(path,autoSearch,'path.txt');
	create_image_from_file(autoSearch ,autoSearch ->array, 'path.txt','filemap.jpg');


	return path;
}

/** build_array
Inputs: A height and width of the field (in meters)
Outputs: An array that corresponds to the field. */

array<array<double> > Pathfinder::build_array(int width, int height){
	//create a two dimensional array storing the coordinates on the field
	array<array<int> > result(width, array<int> height);

	printf("Array width: %d Array height %d\n", array_width,array_height);

	//for debug purpose
	assert(result[0] == height);

	pair<int, int> meterCoodinates;

	for(int j = 0; j < height; j++){
		for(int i = 0; i < width; i++){
			meterCoodinates = arrayToMeters(i,j);
			int x = meterCoodinates.first;
			int y = meterCoodinates.second;
			if (isInField(x,y)){
				cout<< "i: " <<i<<"j: "<<j<<endl;
				result[i][j] = 1;
			else{
				cout<<"i: "<<i<<"j: "<<j<<endl;
				result[i][j] = 0;
			}

			return result;
			}
		}
	}
}

/** create_image
Inputs: The path that the plane will travel.
Outputs: An image that corresponds to the path,
that can be overlayed over the autoSearch image. 
*/
Bitmap Pathfinder::create_image(array<Node^ >^ pathArr, array<int>^ map, String^ filename){
	Bitmap^ image = gcnew(filename);

	image = draw_map(map);
	Node^ prev_node = 0;
	Graphics^ g = gcnew Graphics.FromImage(image);
	Pen^ pen = gcnew Pen(Color.Blue);
	Font^ font = gcnew Font(FontFamily.GenericSansSerif,14,FontStyle.Bold);
	Brushes^ brush = gcnew Brushes.Black;

	
	for(int i = 0; i< path->Length; i++){
		Node^ node = path[i];
	
		if (prev_node == 0){
			prev_node = node;
			g.DrawString("Start",font,brush,Point(prev_node -> x,height_meters
							- 1 - prev_node->y));
			continue;
		}
		Point^ start = gcnew Point(prev_node->x, height_meters - 1 -prev_node->y);
		Point^ stop = gcnew Point(node->x,height_meters - 1 - node->y);

		prev_node = node;
	}
	g.DrawString("End",font,brush,stop);
	image.Save(filename);
	cout<< "Done!"<<endl;
	
}


Bitmap^ draw_map(array<int> map){
	int x = 0
		int y = 0
		Bitmap^ image = gcnew Bitmap(width_meters,height_meters);

	for(int index = 0; index < map->Length; index++){
		int element = map[index];
		int x = (int)(index % width_meters);
		int y = height_meters - 1 - (int)(index / width_meters);

		cout<<"X: "<<x<<"Y:"<<y<<"MaxX: "
			<<width_meters,"MaxY: "<<height_meters<<endl;

		if ( element == NOT_SEEN ){
			image.SetPixel(x,y,System.Drawing.Color.Transparent);
		}
		else if ( element == SEEN){
			image.SetPixel(x,y,System.Drawing.Color.Red);
		}
		else if ( element == OUT_OF_BOUNDS){
			image.SetPixel(x,y,System.Drawing.Color.DimGray);
		}
	}
	return image;
}







Bitmap create_image_from_file(Autosearch^ autosearch, array<double> mapArr,
	String^ pathfile, String^ imagefile){

		double y = 0;
		double x = 0;

		Bitmap image(filename);
		image = Bitmap(mapArr->Length, mapArr[0]->Length);

		//	image = Image.new("RGB", (len(array),len(array[0])))

		pix = image.load()
			draw = ImageDraw.Draw(image)


			//sizeArr[0] col or sizeArr
			for(int i = 0; i< sizeArr; i++){
				int y=0;

				for(int j = 0; j<sizeArr[0], j++){
					//for each element in the col
					int element = sizeArr[i][j];

					cout<< "X: " <<x<<"Y:"<<y<<"MaxX:"
						<<mapArr[0]->Length<<"MaxY:"<<mapArr->Length<<endl;

					if ( element == 0 ){
						pix[x,y] = (255,255,255);
					}
					else if ( element == 1){
						pix[x,y] =(166,166,166);
					}
					else if( element == 2){
						pix[x,y] = (166,166,166);
					}
					y+=1;
				}

				x+=1;
				//open??
				path = open(pathfile,'r')

					prev_loc = 0;
				count = 0;

				//coord???
				for (coord in path){

					lat = float(coord[coord.find('(')+1:coord.find(',')])
						lon = float(coord[coord.find(',')+1:coord.find(')')])
						x,y = autosearch.gpsToArrayCoord(lat,lon)
						x = int(x)
						y = int(y)
						if ( prev_loc == None){
							prev_loc = (x,y);
							draw.text((x,y),str(count),'#FF0000');
						}
						else{
							draw.line([prev_loc,(x,y)],'#000000');
							draw.text((x,y),str(count),'#FF0000');
							prev_loc = (x,y);
						}
						count += 1;
						path.close();
						image.save(imagefile,'jpeg');

				}
			}
}	


void create_file(Autosearch^ autosearch,String^ filename){
	std::ofstream out;
	out.open(filename, std::ios::out);
	for(int i = 0; i< path->Length; i++){
		Node^ node = path[i];
		GPSCoord^ gps = autosearch ->arrayCoordToGps(node->x,node->y);
		out<<gps[0]<<", "<<gps[1]<<"\n";
		out.close();
	}
}	

/** is_in_field
Inputs: An array coordinate for the autosearch array
Outputs: If a field segment within path_width / 2 return true.
Otherwise returns false */

bool is_in_field(double x, double y){
	//searchAround is not defined in the autoSearch.h
	return autoSearch ->searchAround(x,y,PATH_WIDTH/2);
}

/** fix_path
Inputs: The path, the autoSearch map, and an array of the
lines that make up the perimeter
Outputs: None
Effects: Moves all nodes so that they are inside the
searchable area */

void fix_path(array<double>path, array<double> mapArr, array<double> perimeters, Point^ center){
	for (idx,node in enumerate(path)){

		bool should_move = 0;

		for(x_offset in range(-FIELD_BORDER,FIELD_BORDER){
			for (y_offset in range(-FIELD_BORDER,FIELD_BORDER){
				x,y = self.array_to_meters(node.i,node.j);
					x += x_offset;
				y += y_offset;

				if ( x < 0 or x >= self.width_meters){
					continue;
				}
				if ( y < 0 or y >= self.height_meters){
					continue;
				}

				if (mapArr[x][y] == OUT_OF_BOUNDS){
					should_move = 1;
				}
			}
		}

		if (should_move){
			node.x,node.y = self.get_closest_valid_point((node.x,node.y),mapArr,perimeters,center,idx);
		}
	}
}



/** get_closest_valid_point
Inputs: The coordinates of a node that is outside of the AutoSearch map,
the lines that make up the perimeter of the map, and the coordinates of
the center of the map
Outputs: The closest point on the map nearest to the node */


point get_closest_valid_point(Point^ point, array<double> mapArr, 
	array<pair<double, double>, pa perimeters, Point^ center,int index){
		//confusion here, is "array" in the pyhton code supposed to be the mapArr????

		int length = 0
			Point^ new_location = 0;

		for(int i = 0; i< perimeters->Length; i++){
			double perimeter = perimeters[i];

			//perimeter[0] or perimeters????
			Point^ ap(perimeter[0],point);

			double x1 = perimeter[0][0] - perimeter[1][0];
			double x2 = ap[0][0] - ap[1][0];
			double y1 = perimeter[0][1] - perimeter[1][1];
			double y2 = ap[0][1] - ap[1][1];

			double dot_product12 = x1 * x2 + y1 * y2;
			double dot_product11 = x1 * x1 + y1 * y1;
			double proj = (dot_product12 / dot_product11 * x1, dot_product12 / dot_product11 * y1);

			double resultant_vector = (0-proj[0]-x2, 0-proj[1]-y2);
			double resultant_vector_length = sqrt(pow(resultant_vector[0],2)+pow(resultant_vector[1],2));
			Point^ final_point = (point[0]+(resultant_vector[0]*1.05),point[1]+(resultant_vector[1]*1.05));


			cout<< "Point: " <<final_point<<endl;

			//wait! is Point^ supposed to be act as an array in Python!>??!
			if (mapArr->Length > final_point[0] && mapArr[0]->Length > final_point[1] 
			&& mapArr[final_point[0]][final_point[1]] == 1){
				if (resultant_vector_length < length || length == 0){
					length = resultant_vector_length;
					new_location = final_point;
				}
			}

			if (new_location != 0){
				printf("Moved %s to %s (tangent method)", point,new_location);
				return gcnew Point(new_location[0]/PATH_WIDTH, new_location[1]/PATH_WIDTH);
			}


			Point^ center_vector(center[0]-point[0],center[1]-point[1]);

			slope,fixed_point = 0,None
				double slope  = 0;
			Point^ fixed_point = 0;

			if(abs(center_vector[1]) > abs(center_vector[0]){
				if center[1] > point[1]{
					step = 1;
				}
				else{
					step = -1;
				}

				slope = center_vector[0]/center_vector[1];
				//confused
				for y in range(point[1],int(center[1]),step){
					x = int(point[0] + slope * (y - point[1]));
					if x < 0 or x >= len(array) or y < 0 or y >= len(array[0]):
					continue;
					if array[x][y] != 0:
					fixed_point = (x,y);
					break;
				}
			}

			else{
				if center[0] > point[0]{
					step = 1;
				}
				else{
					step = -1;
				}

				slope = center_vector[1]/center_vector[0];
				for x in range(point[0],int(center[0]),step){
					y = int(point[1] + slope * (x - point[0]))
						if( x < 0 or x >= len(array) || y < 0 or y >= len(array[0])){
							continue;
						}
						if (mapArr[x][y] != 0){
							fixed_point = (x,y);
							break;
						}
				}
			}

			if(fixed_point != None){
				//x, y coordinate of fixed_point
				double x = fixed_point[0];
				double y = fixed_point[1];

				slope = center_vector[1]/center_vector[0];
				offset_x = sqrt((FIELD_BORDER**2)/(1 + slope**2));
				if (x > center[0]){
					offset_x *= -1;
				}

				offset_y = offset_x * slope;

				printf("Node: %d Moved %s to %s (center method)", index,point,(x + offset_x,y + offset_y));
				return x + offset_x,y + offset_y;

				else{
					printf("Node: %d Failed to move point %s", index,point);
					return point;
				}

			}



			GPSCoord^ array_to_gps(double i, double j){
				x,y = self.array_to_meters(i,j);

				return autoSearch->arrayCoordToGps(x,y);
			}

			/** build_triangles
			Inputs: The map array
			Outputs: An adjacency list */

			array<double> build_triangles(array<double> triangle_array){

				array<double> children;
				int id = -1
					//nodes is for array of nodes
					array<Node^ > nodes;

				for(int j = 0; j< array_height; j++){
					for(int i = 0; i<array_width; i++){
						if( triangle_array[i][j] == 1){
							id += 1;
							//self?
							node = Node(i,j,id);
							//[node]????
							nodes += [node];
						}
					}
				}

				AdjacencyList adj_list(nodes);

				for j in range(self.array_height){
					for i in range(self.array_width){

						node = adj_list.node_at(i,j);
						if ( triangle_array[i][j] == 0 or node == None ){
							continue;
						}
						else{
							children = [None for x in range(6)];
						}

						array<double> odd_vertices = [(i-1,j),(i,j+1),(i+1,j+1),(i+1,j),(i+1,j-1),(i,j-1)];
						array<double> even_vertices = [(i-1,j),(i-1,j+1),(i,j+1),(i+1,j),(i,j-1),(i-1,j-1)];
						if ( j % 2 == 0){
							vertices = even_vertices;
						}
						else{
							vertices = odd_vertices;
						}
						for(idx,(i_s,j_s) in enumerate(vertices)){
							if ( j_s >= 0 and j_s < self.array_height and i_s >= 0 and i_s < self.array_width and triangle_array[i_s][j_s] == 1 ){
								children[idx] = adj_list.node_at(i_s,j_s);
							}
						}
						node ->set_children(children);
					}
				}
				return adj_list;
			}

			/** make_path
			Inputs: The adjacency list
			Outputs: An array with GPS waypoints ordered in an efficient way */
			GPSCoord^ make_path(array<double> adj_list){
				//path = []????

				for(int i = 0; i< adj_list->arr->Length; i++)
					Node^ n = adj_list.arr[i]
				n ->visited = 0;
			}

			for(int i = 0; i< adj_list->arr->Length; i++)
				Node^ n = adj_list.arr[i]
			if(!n->visited){
				printf("CALLING dfs");
				path += dfs(n,0);
			}
		}

		for(int i = 0; i< path->Length; i++){
			int id = path[i]->id;
			printf("%d", id);
		}
		return path;
}

/** dfs (Depth First Search)
Inputs: The node to start the search, and the optimal direction for the
search
Outputs: A path that hits unvisited nodes using the most optimal
direction */

array<double> dfs_recursive(node,direction){
	//node has to have toString()?
	cout<<"visiting node"<<node<<endl;
	bool should_continue = 1;

	if ( node->visited ){
		printf("Node visited already, nodeID:%d", node->id);
		//what is exactly returned?
		return [];
	}

	node.visited = 1;
	//confused
	path = [node];

	//temp node
	Node^ n;
	//confused
	bool flag;
	while( flag = True in [n.visited for n in node.children if n != None]){
		if(!flag){
			break
		}

		should_continue = 0;
		for(int i = 0; i< node->children->Length; i++){
			n = node->children[i];
			if(n != None and not n.visited){
				should_continue = 1;
			}
		}
		if(!should_continue){
			cout<<"Break!"<<endl;
			break;
		}
		printf("found unvisited node, nodeId: %d",node->id);

		try{
			best,new_direction = self.pick_best(node,direction)
		}
		catch(PathFinishedException& e){
			break;
		}

		//confused: best?
		path += dfs(best,new_direction);

		return path;
	}

	array<double> dfs(self,node,direction){
		array<array<double> >
			path = []
		stack = []

		typedef nodeIntPair pair<Node^, int> ;

		try{
			while(1){
				if (!node ->visited){
					node ->visited = 1;
					//append??
					path -> append(node);
				}
				try{
					// confusion whattt?
					nodeIntPair node_w_direction = pick_best(node,direction);
					stack.append(child);
					node = child;
				}
				catch(PathFinishedException& e){
					node = stack.pop()
				}
			}
		}
		catch(IndexError& e){
			//pass
		}
		return path;
	}

	/** pick_best
	Picks the best node to go to after visiting a certain node
	Inputs:	The current node and direction
	Outputs: The best node to go from here, and the new direction */

	Node^ pick_best(node,direction){
		/*
		for index in [(direction + offset) % 6 for offset in [-2,-1,0,1,2,3]]:
		if (node.children[index] != None and node.children[index].visited == False):
		#print node.children[x].visited,node.children[x].id
		#print "direction: ",direction," new direction: ",index
		return node.children[index], index
		raise PathFinishedException()
		*/
		for(int i = -2; i<4; i++)
			int index = (direction+i) % 6;
		if (node.children[index] != 0 && node.children[index] ->visited == 0){
			cout<< node.children[x] ->visited<<"  "<< node.children[x] -> id;
			cout<< "direction: "<<direction<< " new direction: "<<index<<endl;
			return node.children[index], index;
		}
	}

	//confusion raise?
	raise PathFinishedException();


	for(int i = 0, i< 4; i++){
		if ( node.children[(direction+i) % 6] == 0){
			//confusion pass??
			pass;
		}
		else if( node.children[(direction+i) % 6].visited == False ){
			cout<<"Found unvisited node!"<<endl;
			return node.children[(direction+i) % 6], (direction+i) % 6;
		}
		if ( node.children[(direction-i) % 6] == None ){
			//confusion
			pass;
		}
		else if( node.children[(direction-i) % 6] ->visited == 0 ){
			cout<< "Found unvsisted node!"<<endl;
			return node.children[(direction-i) % 6], (direction-i) % 6;
		}
		cout<< "All nodes visited!"<<endl;
	}
	//confusion
	raise PathFinishedException()
}


/** arrayToMeters
Inputs: The index of an element in triangle_array
Outputs: The meter coordinate of the center of the index 
*/
pair<double, double> Pathfinder::arrayToMeters (double i, double j){
	if ( j % 2 == 1 ){
		x = i * PATH_WIDTH + 2 * OFFSET;
	}
	else{
		x = i * PATH_WIDTH + OFFSET;
		y = j * PATH_WIDTH + OFFSET;
	}
	return pair<double, double> meterCood(x,y);
}


/** isInField
Inputs: An array coordinate for the autosearch array
Outputs: If a field segment within path_width / 2 return true.
Otherwise returns false
*/
//currectly the searchAround method in class Autosearch is not found
bool isInField(double x, double y){
	return Autosearch::searchAround(x,y,PATH_WIDTH/2);
}


class PathFinishedException(Exception){
	pass
}

class NodeFixed(Exception){
	pass
}

