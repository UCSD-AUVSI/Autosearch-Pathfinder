from autosearch import *
from pathfinder import *
a  = GPSCoord ( metersToGps(0), metersToGps(0) , 0 )
b = GPSCoord ( metersToGps(10), metersToGps(10) , 0 )
c = GPSCoord ( metersToGps(0), metersToGps(10) , 0 )
d = GPSCoord ( metersToGps(10), metersToGps(0) , 0 )
search = AutoSearch((a,c,b,d))
PathFinder().build_path(search)
