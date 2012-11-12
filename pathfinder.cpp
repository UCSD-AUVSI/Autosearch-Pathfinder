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

include <math.h>
include <limits.h>
include <stdio.h>
include <stdlib.h>

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
	}

private:
	Autosearch ^ autosearch;
	int widthMeters;
	int heightMeters;

	CreateFile(vector<GPSCoord> path, Autosearch ^ autosearch, String filename) {
		//File ^f = fopen(filename, "w");
	}
}