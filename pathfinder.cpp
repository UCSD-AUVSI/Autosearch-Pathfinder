/* dont do dfs_recursive, create_image */


from scipy import *

#include "StdAfx.h"
#include "Autosearch.h"
#include "MasterHeader.h"
#include "PlaneWatcher.h"
#include "intelligenceController.h"
#include "SkynetController.h"
#include "TelemetryStructures.h"
#include "GeoReference.h"
#include "Pathfinder.h"
#include <vector>

include <math.h>
include <limits.h>
include <stdio.h>
include <stdlib.h>

using namespace std;

using namespace System;
using namespace System::Threading;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Drawing;
using namespace Communications;
using namespace Vision;
using namespace Intelligence;

#define PADDING = 5
#define PATH_WIDTH = 61 // Path width in meters
#define OFFSET = PATH_WIDTH // 2 # Offset of even rows
#define FIELD_BORDER = 20 // In meters, the closest the plane should ever get to the edge of the field

ref class PathFinder { 
public:   
	Pathfinder(Autosearch^ autosearch)::autosearch(autosearch) {}
	
	vector<GPSCoord> buildPath() {
		widthMeters = (int)autosearch->width_meters;
		heightMeters = (int)autosearch->height_meters;
		
		arrayHeight = (int)(autosearch->array_height/PATH_WIDTH) + 1
		arrayWidth = (int)autosearch->array_width/PATH_WIDTH + 1
		
		printf("There are %d nodes.", arrayHeight*array_height)
		printf("Array width: %d", arrayWidth);
		printf("Array height: %d", arrayHeight);

		this.autosearch = autosearch;

		int triangleArray [arrayWidth][arrayHeight] = buildArray(); //break field into triangles
		int adjList 

// ---------------------------------------------------------------------------------------------------->> 11/12/12


	}

	int** buildArray() {
		int result [arrayWidth][ArrayHeight];
		assert(len(result[0]) == arrayHeight;
		for (int j = 0; j < arrayHeight; j++) {
			for (int i = 0; j < arrayWidth; i++) {
				int xy[2] = arrayToMeters(i, j);
				if (isInField(xy[0], xy[1])) {
					result[i][j] = 1;
				}
				else {
					result[i][j] = 0;
				}
			}
		}
		return result;

	}

	int* arrayToMeters (int i, int j) {

		if (j % 2 == 1) {
			int x = i * PATH_WIDTH + 2 * OFFSET;
		}
		else {
			int x = i * PATH_WIDTH + OFFSET;
		}
	 	int y = j * PATH_WIDTH + OFFSET;
	 	int result[2] = {x, y};
	 	return result;
	}

	bool isInField(int x, int y) {
		return autosearch.searchAround(x,y,PATH_WIDTH/2);
	}

	void buildTriangles(int** triangleArray)) {

		int* children; // maybe change
		int id = -1;
		vector<int> nodes;	// maybe change
		for (int j = 0; j < arrayHeight; j++) {
			for (int i = 0; i < arrayWidth; i++) {
				if (triangleArray[i][j] == 1){
					id++;
					Node node = Node(i, j, id); // maybe change
					nodes.push_back(node); // maybe change
				}
			}
		}

//------------------------------------------------------------------------------------------------------>> 11/12/12


	}

private:
	Autosearch ^ autosearch;
	int widthMeters;
	int heightMeters;

	int arrayHeight;
	int arrayWidth;

	CreateFile(vector<GPSCoord> path, Autosearch ^ autosearch, String filename) {
		//File ^f = fopen(filename, "w");
	}
}