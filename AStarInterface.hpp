/*------------------------------------

Charles Vanderlick
Benjamin Morrison
Assignment 2 - A*

------------------------------------*/

#ifndef A_Interface_hpp
#define A_Interface_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>

using namespace std;

/* class containing the city (point) information */
class point
{
public:
    string name, heurGivenBy;
    int x, y, visited, heuristic, distTraveled, totalDistanceTraveled;
};

class Edge{
	public:
	string start;
	string end;
};

/* class containing the A* functions */
class AStar
{
public:
    int GetNum(string name, vector<point> locations);
    void printPath(vector<point> x, int steps);
    point assign(string name, vector<point> locations);
    bool isVisited(string name, vector<point> locations);
    bool isValid(string name,vector<point> locations);
    int distanceCalc(double x1, double x2, double y1, double y2);
    void printGraph(map <string,vector<point> > &adjacencyList);
    void AStarSearch(map <string,vector<point> > &adjacencyList, vector <point> &locations, vector <point> &FinalPath, vector <point> &ExcludedPointVec, string startName, string endName, int heuristic, int steps, int x2, int y2);
    void PopulateLocations(vector <point> &locations, ifstream &File2);
    void PopulateGraph(map <string,vector<point> > &adjacencyList, vector <point> &locations, ifstream &File1);
    void GetUserInput(string &startName, string &endName, vector <point> &locations, vector <point> &ExcludedPointName, int &heuristic, int &steps, char &exclude, map <string,vector<point> > &adjacencyList);
    bool toExclude(string name, vector <point> &ExcludedPointVec);
    void getDestCord(map <string,vector<point> > &adjacencyList, string endName, int &x2, int &y2);
    void markOpenCitiesAsVisited(vector<point> &openCities, string addedCity);
    void getCoordsFromKey(string city, vector <point> &locations, int &tempx, int &tempy);
    bool hadHeuristic(string name, vector<point> openCities);
    bool existingOpenCity(string name, vector<point> openCities);
    void getDistTraveledFromKey(string city, vector <point> &locations, int &totalTempDistanceTraveled);
    int getTotalDistanceTraveled(string city, int currCity, vector <point> &openCities);
    void printAStarPath(vector <point> FinalPath, map<string, vector<point> > &adjacencyList, vector <Edge> Edges, int steps);
    void formatAStar(map <string,vector<point> > adjacencyList, vector <point> FinalPath, string startName);
    bool isEdge(string startName, string endName, vector <Edge> Edges);
    void stepByStep(vector<point> openCities, string currCity, vector <point> ExcludedPointVec);
};

#endif /* A_Interface_hpp */
