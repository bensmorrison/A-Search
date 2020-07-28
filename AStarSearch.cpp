/*------------------------------------
 
 Charles Vanderlick
 Benjamin Morrison
 Assignment 2 - A*
 
 ------------------------------------*/

#include "AStarInterface.hpp"

int main()
{
    AStar astar; //operator for class (holding all the functions)
    vector <point> locations; //vector holding locations initially to than be used to create connections
    vector <point> FinalPath; //vector that will hold final path to be printed to the user
    vector <point> ExcludedPointVec;  //vector to hold excluded points
    map <string,vector<point> > adjacencyList; //map to implement adj. list
    map <string,vector<point> >::iterator iter; //iterator for the map
    
    // declarations
    string startName, endName;
    int heuristic = 0, steps = 0, x2 = 0, y2 = 0;
    char exclude = 'Y';
    
    // open both files
    ifstream File1;
    ifstream File2;
    File1.open("connections.txt");
    File2.open("locations.txt");
    
    // populate the locations vector
    if(File2.is_open())
        astar.PopulateLocations(locations, File2);
    else
    {
        cout << "The file locations.txt failed to open. Please check that it is in the currect directory";
        cout << " or in the same directory as the executible." << endl;
        return -1;
    }
    
    // populate the Graph
    if(File1.is_open())
        astar.PopulateGraph(adjacencyList, locations, File1);
    else
    {
        cout << "The file connections.txt failed to open. Please check that it is in the currect directory";
        cout << " or in the same directory as the executible." << endl;
        return -1;
    }

    // print out the representation of the graph (using map as an adjacency list)
    astar.printGraph(adjacencyList);
    
    // function to get start city, end city, and all specifications to run search.
    astar.GetUserInput(startName, endName, locations, ExcludedPointVec, heuristic, steps, exclude,adjacencyList);
    
    // calculate the estimated distance of all cities given the beginning city
    astar.getDestCord(adjacencyList, endName, x2, y2);

    // Preform the A* search
    astar.AStarSearch(adjacencyList, locations, FinalPath, ExcludedPointVec, startName, endName, heuristic, steps, x2, y2);
    
    return 0;
}
