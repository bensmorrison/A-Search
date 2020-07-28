/*------------------------------------

Charles Vanderlick
Benjamin Morrison
Assignment 2 - A*

------------------------------------*/

#include "AStarInterface.hpp"

//find point and return that point
point AStar::assign(string name, vector<point> locations){
    for(int i = 0; i < locations.size(); i++){
        if(strcmp(locations.at(i).name.c_str(),name.c_str()) == 0)//when we find apoint we return it
            return locations.at(i);
    }
    return locations.at(0);//find point and return that point
}

//will find the position of a point in our vector using a points name and scan each location we have to find it
int AStar::GetNum(string name, vector<point> locations){
    for(int i = 0; i < locations.size(); i++){
        if(strcmp(locations.at(i).name.c_str(),name.c_str()) == 0){
            return i;//if we find the location that matches up we return its vector position
        }
    }
    return 0;
}

//checks if a point has been visited yet or not
bool AStar::isVisited(string name, vector<point> locations){
    for(int i = 0; i < locations.size(); i++){//check all locations we have been to using the locations vector
        if(strcmp(locations.at(i).name.c_str(),name.c_str()) == 0){//if the point has a 1 for visited we have seen it already
            if(locations.at(i).visited == 1){
                return true;
            }
        }
    }
    return false;//if we find that its unvisited we return false
}

bool AStar::hadHeuristic(string name, vector<point> openCities)
{
    for(int i = 0; i < openCities.size(); i++)
    {//check all locations we have been to using the locations vector
        if(strcmp(openCities.at(i).name.c_str(),name.c_str()) == 0)
        {//if the point has a 1 for visited we have seen it already
            if(openCities.at(i).heuristic != 0){
                return true;
            }
        }
    }
    return false;//if we find that there is no heuristic
}

bool AStar::existingOpenCity(string name, vector<point> openCities)
{
    for(int i = 0; i < openCities.size(); i++)
    {//check all locations we have been to using the locations vector
        if((openCities.at(i).name) == name)
        {//if the point has a 1 for visited we have seen it already
                return true; // if we find the city already in openCities
        }
    }
    return false;//if we find that the input city is not present
}

bool AStar::toExclude(string name, vector <point> &ExcludedPointVec)
{
    //check all locations we have been to using the locations vector
    for(int i = 0; i < ExcludedPointVec.size(); i++)
        if (ExcludedPointVec.at(i).name.c_str() == name)
            return true;
    
    return false;//if we find that its unvisited we return false
}

//will tell us if the user entered a valid point
bool AStar::isValid(string name,vector<point> locations){
    //if we find the point return true else return false
    for(int y = 0; y < locations.size();y++){
            if(locations.at(y).name == name){
                return true;
        }
    }
    return false;
}

int AStar::distanceCalc(double x1, double x2, double y1, double y2)
{
    return sqrt(abs((x2 - x1)*(x2 - x1)) + abs((y2 - y1)*(y2 - y1)));
}

//used to print the final path held in a vector of points starting at index zero until the end of the path
void AStar::printPath(vector<point> path, int heuristic)
{
    cout << endl << "Final Path: " << endl << endl;
    double finalTotal = 0, total = 0;
    
    // iterates through vector containing the final path to be printed
    for(int i = 0; i < path.size() - 1; i++)
    {
        // get our euclidian distance
        total = distanceCalc(path.at(i).x, path.at(i+1).x, path.at(i).y, path.at(i+1).y);
        
        // print points names and the distance between them
        cout << path.at(i).name << " to " << path.at(i+1).name << " " << "length: ";
        if(heuristic == 1)
            cout << 1 << endl;
        
        else
            cout << total << endl;
        
        if(heuristic == 1)
            finalTotal++;
        else
            finalTotal += total;
    }
    
    //print final path length once we finished processing all of our segments
    cout << "\nTotal path length: " << finalTotal << endl << endl;
}

// prints out a representation of the map (adjacency list)
void AStar::printGraph(map <string,vector<point> > &adjacencyList)
{
    cout << "Graph representation: \n\n";
    
    typedef map <string,vector<point> >::const_iterator MapIterator;
    for (MapIterator iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++)
    {
        cout << iter->first;
        
        typedef vector<point>::const_iterator ListIterator;
        
        for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
            cout << " -> " << list_iter->name ;
        
        cout << endl;
    }
    cout << endl;
}

void AStar::printAStarPath(vector <point> FinalPath, map<string, vector<point> > &adjacencyList, vector <Edge> Edges, int heuristic){
	//create vector to hold new final path
	vector <point> newFinalPath;
	
	//create iterator for map
	map <string,vector<point> >::iterator iter;
	
	//add starting point to our vector
	newFinalPath.push_back(FinalPath.at(0));
	
	//find points in map that are adjacent to current point which is starting point
	iter = adjacencyList.find(FinalPath.at(0).name);
	
	//reset our points to unvisited to perform our search to grab our path to print
	for(int y = 0; y < FinalPath.size();y++){
		FinalPath.at(y).visited = 0;	
	}
	
	//set the starting point to visited
	FinalPath.at(0).visited = 1;
	
	while(1){
		//int variable to keep track of if we have to back track or not
		int flag = 0;
		for(int x = 0; x < iter->second.size(); x++){
			//check if their is a valid place to go
			if(isValid(iter->second.at(x).name,FinalPath) == true && isEdge(iter->second.at(x).name,iter->first,Edges) == true){
				if(isVisited(iter->second.at(x).name,FinalPath) == true){
					continue;
				}else{
					flag = 1;
					//if we find the final point add it to the path and break
					if(iter->second.at(x).name == FinalPath.at(FinalPath.size() - 1).name){
						flag = 2;
						newFinalPath.push_back(iter->second.at(x));
						break;
					}
				}
			}
			if(iter->second.at(x).name == FinalPath.at(FinalPath.size() - 1).name){
						flag = 2;
						newFinalPath.push_back(iter->second.at(x));
						break;
			}
		}
		if(flag == 0){//we have to step back
			newFinalPath.pop_back();
			iter = adjacencyList.find(newFinalPath.at(newFinalPath.size() - 1).name);
			continue;
		}
		if(flag == 1){//we have an open point we can traverse
			for(int x = 0; x < iter->second.size(); x++){
				if(isValid(iter->second.at(x).name,FinalPath) == true && isVisited(iter->second.at(x).name,FinalPath) == false && isEdge(iter->second.at(x).name,iter->first,Edges) == true){
					//take the point and traverse it as the next point
					int position = GetNum(iter->second.at(x).name,FinalPath);
					FinalPath.at(position).visited = 1;
					newFinalPath.push_back(FinalPath.at(position));
					iter = adjacencyList.find(FinalPath.at(position).name);
					break;
				}
			}
		}
		if(flag == 2){			
			break;
		}
	}
	//print final path
	printPath(newFinalPath, heuristic);
}

// Populate the locations from locations.txt
void AStar::PopulateLocations(vector <point> &locations, ifstream &File2)
{
    //string that holds the line from the text file each time to read in locations
    string tempLine;
    
    //stream to pick the stream apart
    stringstream str;
    
    //create locations and put into vector
    while(getline(File2,tempLine)){
        if(tempLine == "END")
            break;
        
        str << tempLine.c_str();//grab the string
        string name, x, y;
        str >> name >> x >> y;//put values into our strings
        
        //record these points into their object each time we loop by saving the current data in our strings
        point newPoint;
        newPoint.name = name;
        newPoint.x = atoi(x.c_str());
        newPoint.y = atoi(y.c_str());
        newPoint.visited = 0;
        newPoint.heuristic = 0;
        newPoint.distTraveled = 0;
        newPoint.totalDistanceTraveled = 0;
        //add the newly read point to the vector for locations
        locations.push_back(newPoint);
        
        //reset input stream
        cin.clear();
        str.clear();
    }
}

// Construct the graph
void AStar::PopulateGraph(map<string, vector<point> > &adjacencyList, vector <point> &locations, ifstream &File1)
{
    //string that holds the line from the text file each time to read in locations
    string tempLine;
    
    //stream to pick the stream apart
    stringstream str;
    
    while(getline(File1,tempLine)){//create a loop to grab each line one at a time again
        vector <point> bucket;//holds the connections for the current point
        
        if(tempLine == "END")//if we read the end break
            break;
        
        str << tempLine.c_str();
        string name, numConn, connect;
        str >> name >> numConn;
        
        for(int i = 0; i < atoi(numConn.c_str());i++){//loop each connection on the line
            str >> connect;//create a point from it by finding the one already stored in our location vector
            point tempPoint;
            tempPoint.name = connect;
            //scan location vector to find this point and grab its values
            for(int x = 0; x < locations.size();x++){
                if(locations.at(x).name == connect){
                    tempPoint.x = locations.at(x).x;
                    tempPoint.y = locations.at(x).y;
                    tempPoint.visited = 0;
                    tempPoint.heuristic = 0;
                    tempPoint.distTraveled = 0;
                    tempPoint.totalDistanceTraveled = 0;
                    //push onto the buckets vector here
                    bucket.push_back(tempPoint);
                }
            }
            //scan vector to get our location data and then add the location to the vector for that locations current connections
            cin.clear();
            str.clear();
        }
        //add to map right here
        adjacencyList[name] = bucket;
        bucket.clear();
        cin.clear();
        str.clear();
    }
}

void AStar::getDestCord(map <string,vector<point> > &adjacencyList, string endName, int &x2, int &y2)
{
    point tempPoint;
    typedef map <string,vector<point> >::const_iterator MapIterator;
    
    for (MapIterator iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++)
    {
        typedef vector<point>::const_iterator ListIterator;
        
        for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
            if(endName == list_iter->name)
            {
                x2 = list_iter->x;
                y2 = list_iter->y;
            }
    }
}

void AStar::getCoordsFromKey(string city, vector <point> &locations, int &tempx, int &tempy)
{
    for(int i = 0; i < locations.size(); i++)
        if(city == locations.at(i).name)
        {
            tempx = locations.at(i).x;
            tempy = locations.at(i).y;
            break;
        }
}

void AStar::getDistTraveledFromKey(string city, vector <point> &openCities, int &totalTempDistanceTraveled)
{
    for(int i = 0; i < openCities.size(); i++)
        if(city == openCities.at(i).name)
        {
            totalTempDistanceTraveled = openCities.at(i).distTraveled;
            break;
        }
}

int AStar::getTotalDistanceTraveled(string temptemp, int currCity, vector <point> &openCities)
{
    for(int i = 0; i < openCities.size(); i++)
        if(temptemp == openCities.at(i).name)
            return (openCities.at(i).totalDistanceTraveled + currCity);
        
    return 0;
}

void AStar::markOpenCitiesAsVisited(vector<point> &openCities, string addedCity)
{
    if(openCities.size() == 0)
        return;
    
    for(int i = 0; i < openCities.size(); i++)
        if(addedCity == openCities.at(i).name)
            openCities.at(i).visited = 1;
}

void AStar::stepByStep(vector<point> openCities, string currCity, vector <point> ExcludedPointVec)
{
    cout << "City Selected: " << currCity << endl << endl;
    cout << "Possible cities to travel to: ";
    
    for(int i = 0; i < openCities.size(); ++i)
    {
        if(openCities.at(i).visited == 0)
            cout << openCities.at(i).name << " ";
        
        for(int a = 0; a < ExcludedPointVec.size(); ++a)
            if(openCities.at(i).name == ExcludedPointVec.at(a).name)
                cout << "<- Do not include ";
    }
    
    cout << endl << endl << "******************************" << endl << endl;
}

void AStar::formatAStar(map <string,vector<point> > adjacencyList, vector <point> FinalPath, string startName)
{
    bool cityFound = false;
    
    map <string,vector<point> > tempList;
    tempList = adjacencyList;
    
    typedef map <string,vector<point> >::const_iterator MapIterator;
    for (MapIterator iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++)
    {
        for(int i = 0; i < FinalPath.size(); i++)
            if(iter->first == FinalPath.at(i).name)
                cityFound = true;
        
        if(cityFound == false)
            tempList.erase(iter->first);
        
        cityFound = false;
    }
    
    cityFound = false;

    //loops keys
    for (MapIterator iter2 = tempList.begin(); iter2 != tempList.end(); iter2++)
    {
        typedef vector<point>::const_iterator ListIterator;
        //loops values
        for (ListIterator list_iter = iter2->second.begin(); list_iter != iter2->second.end(); list_iter++)
        {
            for(int s = 0; s < FinalPath.size(); s++)
                if(list_iter->name == FinalPath.at(s).name)
                    cityFound = true;
            
            if(cityFound == false)
                tempList.erase(list_iter->name);
            
            cityFound = false;
        }
    }
}

void AStar::AStarSearch(map <string,vector<point> > &adjacencyList, vector <point> &locations, vector <point> &FinalPath, vector <point> &ExcludedPointVec, string startName, string endName, int heuristic, int steps, int x2, int y2)
{
    AStar astar;
    
    map <string,vector<point> >::iterator iter;
    
    double counter = 0;
    
    //vector for keeping all city possibilities
    vector<point> openCities;
   
    // find the starting city and set it to currPoint
    iter = adjacencyList.find(startName);
    point currPoint;
    currPoint = astar.assign(startName, locations);
    
    // add the first city (starting city) to the final path vector
    FinalPath.push_back(currPoint);
    
    // contains the index of the current city
    int pos1 = astar.GetNum(currPoint.name,locations);
    
    // marks the current city as visited
    locations.at(pos1).visited = 1;
    
    //used so we can do our comparison of strings and have a starting value
    string alpha = "ZZ", currCity;
    int tempx = 0, tempy = 0, tempLowest = 100000, tempCurrent = 0, distanceTraveled = 0, tempDistanceTraveled = 0, chosenDistanceTraveled = 0, totalTempDistancetraveled = 0, totalDistanceTraveled = 0;
    bool firstIter = true;
    
    while(1)
    {
        int flag = 0;//will tell us if our node has a path that hasnt been visited yet
        
        /*--------------------------------------------------------------
        scans the entire bucket to see if all have been visited or not.
         --------------------------------------------------------------*/
        for(int x = 0; x < iter->second.size(); ++x)
        {
            // if current city has been visited, go to the next one
            if(astar.isVisited(iter->second.at(x).name, locations) == true)
                continue;
            
            // there is a city in the current bucket that has NOT been visited
            else
            {
                // set flag to indicate that there are cities to visit...
                flag = 1;
                
                // check if an unvisited city is already in "open" cities. if not, add it
                if(existingOpenCity(iter->second.at(x).name, openCities) == false)
                {
                    // add these cities to the vector of "open" cities
                    openCities.push_back(iter->second.at(x));
                }
                
                // however, if that unvisited city is the endpoint, we are done.
                if(iter->second.at(x).name == endName)
                {
                    if(steps == 1)
                        astar.stepByStep(openCities, iter->first, ExcludedPointVec);
                    
                    cout << "Final city " << endName << " found!" << endl;
                    
                    FinalPath.push_back(iter->second.at(x));
                    flag = 2;
                    break;
                }
            }
        }
        
        /*--------------------------------------------------------------
        end city has been found, print out the vector containing path
        --------------------------------------------------------------*/
        if(flag == 2)
        {
            astar.formatAStar(adjacencyList, FinalPath, startName);
            break;
        }
        
        /*--------------------------------------------------------------
        not all cities have been visited, so we pick the next one
        --------------------------------------------------------------*/
        else if(flag == 1)
        {
            // finds the next point we will move too
            // this searches the entire bucket...
            for(int x = 0; x < iter->second.size(); ++x)
            {
                // skip visited cities...
                if(astar.isVisited(iter->second.at(x).name,locations))
                    iter->second.at(x).visited = 1;

                else
                {
                    //need to get the coordinates from this city (which is a string), store in tempx & tempy
                    currCity = iter->first;
                    astar.getCoordsFromKey(currCity, locations, tempx, tempy);
                    
                    // Loop through the "open" cities and pick one with smallest straight line distance
                    for (int a = 0; a < openCities.size(); ++a)
                    {
                        if(openCities.at(a).visited == 1)
                            continue;
                        
                        // dont count if city is to be exluded
                        if(astar.toExclude(openCities.at(a).name, ExcludedPointVec))
                            continue;
                        
                        // if the heuristic hasnt been calculated yet, calculate it
                        if((astar.hadHeuristic(openCities.at(a).name, openCities) == false))
                        {
                            if(heuristic == 2)
                                {
                                // get the temp distance traveled (i.e. the distance from the origin point to the proposed new point)
                                tempDistanceTraveled = astar.distanceCalc(tempx, openCities.at(a).x, tempy, openCities.at(a).y);
                                
                                // add tempDistanceTraveled to the distTraveled for that point (used later on for calculating heuristic)
                                openCities.at(a).distTraveled = tempDistanceTraveled;
                                
                                // function to get the coordinates from the origin city (currCity)
                                astar.getDistTraveledFromKey(currCity, openCities, totalTempDistancetraveled);
                                
                                // if statement necessary to add total distance traveled for first iteration
                                // otherwise it comes to 0
                                if(firstIter == true)
                                    totalDistanceTraveled = tempDistanceTraveled;
          
                                else
                                    totalDistanceTraveled = astar.getTotalDistanceTraveled(currCity, openCities.at(a).distTraveled, openCities);
                                
                                // set total distance traveled
                                openCities.at(a).totalDistanceTraveled = totalDistanceTraveled;
                                
                                // get the temp variables for the open cities
                                // calculate estimated distance to endpoint
                                tempCurrent = astar.distanceCalc(openCities.at(a).x, x2, openCities.at(a).y, y2) + totalDistanceTraveled;
                                
                                // add heuristic value to the city
                                openCities.at(a).heuristic = tempCurrent;
                                
                                // record from which origin city the heuristic was calculated.
                                openCities.at(a).heurGivenBy = currCity;
                            }
                            
                            else if(heuristic == 1)
                            {
                                tempDistanceTraveled = 1;
                                openCities.at(a).distTraveled = tempDistanceTraveled;
                                astar.getDistTraveledFromKey(currCity, openCities, totalTempDistancetraveled);
                                
                                if(firstIter == true)
                                    totalDistanceTraveled = tempDistanceTraveled;
                                
                                else
                                    totalDistanceTraveled = astar.getTotalDistanceTraveled(currCity, openCities.at(a).distTraveled, openCities);
                                
                                tempCurrent = 1 + totalDistanceTraveled;
                                openCities.at(a).heuristic = tempCurrent;
                                openCities.at(a).heurGivenBy = currCity;
                            }
                        }
                        
                        int temptempDistanceTraveled = 0;
                        int tempTotalDistanceTraveled = 0;
                        int temptempCurrent = 0;
                        string tempHeurGivenBy;
                        
                        // need to add condition to determine if currCity is adjacent.
                        if(openCities.at(a).heurGivenBy != currCity && astar.hadHeuristic(openCities.at(a).name, openCities))
                        {
                            temptempDistanceTraveled = openCities.at(a).distTraveled;
                            tempTotalDistanceTraveled = openCities.at(a).totalDistanceTraveled;
                            temptempCurrent = openCities.at(a).heuristic;
                            tempHeurGivenBy = openCities.at(a).heurGivenBy;
                            
                            for(int x = 0; x < iter->second.size(); ++x)
                            {
                                if((iter->second.at(x).name == openCities.at(a).name))
                                {
                                    tempDistanceTraveled = astar.distanceCalc(tempx, openCities.at(a).x, tempy, openCities.at(a).y);
                                    openCities.at(a).distTraveled = tempDistanceTraveled;
                                    astar.getDistTraveledFromKey(currCity, openCities, totalTempDistancetraveled);

                                    if(firstIter == true)
                                        totalDistanceTraveled = tempDistanceTraveled;

                                    else
                                        totalDistanceTraveled = astar.getTotalDistanceTraveled(currCity, openCities.at(a).distTraveled, openCities);

                                    openCities.at(a).totalDistanceTraveled = totalDistanceTraveled;
                                    tempCurrent = astar.distanceCalc(openCities.at(a).x, x2, openCities.at(a).y, y2) + totalDistanceTraveled;
                                    openCities.at(a).heuristic = tempCurrent;
                                    openCities.at(a).heurGivenBy = currCity;
                                    
                                    if(tempCurrent > temptempCurrent)
                                    {
                                        openCities.at(a).distTraveled = temptempDistanceTraveled;
                                        openCities.at(a).totalDistanceTraveled = tempTotalDistanceTraveled;
                                        openCities.at(a).heuristic = temptempCurrent;
                                        openCities.at(a).heurGivenBy = tempHeurGivenBy;
                                    }
                                }
                            }
                        }
                        
                        // if the heuristic number is lowest, grab that city name
                        if(openCities.at(a).heuristic < tempLowest)
                        {
                            alpha = openCities.at(a).name;
                            tempLowest = openCities.at(a).heuristic;
                            chosenDistanceTraveled = totalTempDistancetraveled;
                        }
                        
                    }
                }
            }
            
            //set currPoint to new point that has the name of the string alpha passed in
            currPoint = astar.assign(alpha,locations);
            
            // if step by step is chosen, print out the steps per iteration
            if(steps == 1)
                astar.stepByStep(openCities, currCity, ExcludedPointVec);
            
            // when a city is picked, mark it as visited from "open cities"
            astar.markOpenCitiesAsVisited(openCities, alpha);
            
            //add the point to the final path
            FinalPath.push_back(currPoint);
            
            //will set our point to now visited
            int pos = astar.GetNum(currPoint.name,locations);
            locations.at(pos).visited = 1;
            
            // set iterator to the point that was chosen to then find the next city.
            iter = adjacencyList.find(currPoint.name);

            // update total distance traveled
            distanceTraveled += chosenDistanceTraveled;
            
            firstIter = false;
            tempLowest = 100000;
            
        }
        
        // if youve reached a dead end
        else
        {
            //mark as visited
            int pos = astar.GetNum(currPoint.name,locations);
            locations.at(pos).visited = 1;
            
            //remove the element most recent since we have to back track
            FinalPath.pop_back();
            
            //our current point becomes the previous one
            currPoint = FinalPath.back();
            
            //we now will check that points paths again and choose a new one to take
            iter = adjacencyList.find(currPoint.name);
        }
        
        counter++;
        
        if(counter > (adjacencyList.size()*4))
        {
            cout << "Path could not be found\n";
            exit(1);
        }
    }
    
    
	vector <Edge> Edges;
	for(int z = 0; z < openCities.size();z++){
		Edge tempEdge;
		if(openCities.at(z).visited == 1){
			tempEdge.start = openCities.at(z).name;
			tempEdge.end = openCities.at(z).heurGivenBy;
			Edges.push_back(tempEdge);
		}
	}
    
	printAStarPath(FinalPath,adjacencyList,Edges, heuristic);
	
}

void AStar::GetUserInput(string &startName, string &endName, vector <point> &locations, vector <point> &ExcludedPointVec, int &heuristic, int &steps, char &exclude,map <string,vector<point> > &adjacencyList)
{
    AStar astar;
    
    while(1)
    {
        int flag = 0;
        //get input from the user for a start or end point
        cout << "Please enter your starting point!" << endl;
        cin >> startName;
        cout << "Please enter an ending point!" << endl;
        cin >> endName;
        
        //condition for when the start and end cities are the same
        while(startName == endName)
        {
            cout << "The cities you entered are the same, please re-enter your choices.\n";
            cout << "Please enter your starting point: \n";
            cin >> startName;
            cout << "Please enter an ending point: \n";
            cin >> endName;
        }
        
        //if these locations entered exist we incriment the int flag by 1
        for(int y = 0; y < locations.size(); y++)
        {
            if((locations.at(y).name == startName) || (locations.at(y).name == endName))
                flag++;
        }
        
        if(flag == 2)//if the flag == 2 we have read in two valid locations and can break else we ask the user again
            break;
        else{
            cout << "One or more of these choices isnt in the graph please re-enter and try again!" << endl;
            continue;
        }
    }
    
    //read in users choice for heuristic
    while(heuristic != 1 && heuristic != 2)
    {
        cout << endl << "1 - Search for the path with fewest points\n2 - Search for the path with the lowest total cost" << endl;
        cout << "Please enter 1 or 2 to select an option: \n";
        cin >> heuristic;
    }
    
    //read in choice for steps or not
    while(steps != 1 && steps != 2)
    {
        cout << endl << "1 - Show all steps in process\n2 - Only show the final path" << endl;
        cout << "Please enter 1 or 2 to select an option: \n";
        cin >> steps;
    }
    
    while(1)
    {
        cout << endl << "Would you like to exclude any cities from the path [Y/N]?" << endl;
        cin >> exclude;
        if(exclude == 'Y' || exclude == 'N'){
            break;
        }else{
            cout << "Please enter either N or Y (capitialized)" << endl;
        }
    }
    
    //record all points the user wants to exclude
    if(exclude == 'Y')
    {
        string ExcludedPointName;
        while(exclude == 'Y'){//when user selects no than the loop will stop running and our exluded points with be in a vector
            cout << "Please enter a point to exclude from the search!" << endl;
            cin >> ExcludedPointName;
            
            //verify the point exists
            if(astar.isValid(ExcludedPointName,locations)){
                point p;
                p = astar.assign(ExcludedPointName, locations);
				map <string,vector<point> >::iterator iter;
    
				iter = adjacencyList.find(endName);
				int count = 0;
			
                //add to vector here
                ExcludedPointVec.push_back(p);
					//loop through our vector of the endpoint
				for(int z = 0; z < iter->second.size() ;z++){
					//loop through current excluded points and make sure we have one that allows us to find final point
					for(int w = 0; w < ExcludedPointVec.size();w++){
						if(iter->second.at(z).name == ExcludedPointVec.at(w).name){
							count++;
						}
					}
				}
				if(count == iter->second.size() || startName == ExcludedPointName){
					cout << "If we exluded this point their wont be a possible path please try again!" << endl;
					ExcludedPointVec.pop_back();//remove the bad point
					continue;
				}
            }else{
                cout << "Point does not exist or does not allow for a path on our given graph!" << endl;
            }
            //if so add the associated point to our dont include vector
            
            //ask if they want to exclude another or continue
            cout << "Would you like to enter another point to exclude [Y/N]?" << endl;
            cin >> exclude;
        }
    }
}


bool AStar::isEdge(string startName, string endName, vector <Edge> Edges){
	for(int x = 0; x < Edges.size();x++){
		if((Edges.at(x).start == startName && Edges.at(x).end == endName) || (Edges.at(x).start == endName && Edges.at(x).end == startName)){
			return true;
		}
	}
	return false;
}
