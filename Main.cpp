#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "functionPrototypes.h"

const int delta[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int main ()
{
    vector<vector<State>> Mygrid; 
    ReadBoardFile("MyFiles/board.txt",Mygrid); 

    int startp[2] = {0, 0};     //x1,y1
    int goalp[2] = {4, 5};      //x2,y2

    vector<vector<State>> path = Search(Mygrid,startp,goalp);
    PrintBoard(path);  
}

void ReadBoardFile(string filepath,vector<vector<State>> & refMygrid)
{
  string rdata ;
  fstream myfile;
  myfile.open(filepath);
  if(myfile.is_open())
  {
    while(getline(myfile,rdata)) 
    {
      refMygrid.push_back(Parseline(rdata)); 
    }
  }
  myfile.close();
}

vector<State> Parseline(string rdata)
{
  vector<State> Myrow;
  int Mynumbers;
  char coma;
  istringstream Mystring;
  Mystring.str(rdata);

  while(Mystring >> Mynumbers >> coma)        // >> The extraction operator
  {
    if(Mynumbers == 0)
      {Myrow.push_back(State::kEmpty);}
    else
      {Myrow.push_back(State::kObstacle);}
  }
  return Myrow;
}

void PrintBoard(vector<vector<State>> & refMygrid)
{
    for(int i=0;i<refMygrid.size();i++)
    {
      for(int j=0;j<refMygrid[i].size();j++)
      {
        cout << CellString(refMygrid[i][j]);
      }
      cout << "\n";

    }
}

string CellString(State cell) 
{
  switch(cell) 
  {
    case State::kObstacle: 
      return "⛰   ";
    case State::kPath: 
      return "🚗   ";
    case State::kStart: 
      return "🚦   ";
    case State::kFinish: 
      return "🏁   ";
    default: 
      return "0   ";  
  }
}

vector<vector<State>> Search(vector<vector<State>> & refMygrid,int* startp,int* goalp)
{ 
    vector<vector<int>> LOpenNodes;
    //intialize first node
    int hvalue = Heuristic(startp[0],startp[1],goalp[0],goalp[1]);
    int gvalue = 0;
    int xco = startp[0];
    int yco = startp[1];
    AddToOpen(xco,yco,gvalue,hvalue,LOpenNodes,refMygrid);

    while(LOpenNodes.size()>0)
    {
      CellSort(&LOpenNodes);

      auto selectedCell = LOpenNodes.back();
      LOpenNodes.pop_back();

      xco = selectedCell[0];
      yco = selectedCell[1];
      refMygrid[xco][yco] = State::kPath;

      if (xco == goalp[0] && yco == goalp[1]) 
      {
        refMygrid[startp[0]][startp[1]] = State::kStart;
        refMygrid[goalp[0]][goalp[1]] = State::kFinish;
        return refMygrid;
      }
      ExpandNeighbors(selectedCell,LOpenNodes,refMygrid,goalp);
    }
    cout << "no path found"<<endl;
    return refMygrid;
}

int Heuristic(int x1,int y1,int x2, int y2)
{
  return abs(x2-x1)+abs(y2-y1);
}

void AddToOpen(int xco,int yco,int gvalue,int hvalue,vector<vector<int>> & refLOpenNodes,vector<vector<State>> & refMygrid) 
{
  refLOpenNodes.push_back({xco,yco,gvalue,hvalue});
  refMygrid[xco][yco] = State::kClosed;
}
bool Compare(vector<int> node1, vector<int> node2)
{
  int f1 = node1[2]+node1[3];
  int f2 = node2[2]+node2[3];
  if (f1 > f2) 
    return true; 
  else 
    return false;  //return (f1>f2)? true: false;
}

void CellSort(vector<vector<int>> * pLOpenNodes) {
  sort(pLOpenNodes->begin(), pLOpenNodes->end(), Compare);
}

bool CheckValidCell(int xco,int yco,vector<vector<State>> & refMygrid)
{
  return ((xco >= 0) && (xco < refMygrid.size()) && (yco >= 0) && (yco < refMygrid[0].size()) && (refMygrid[xco][yco] == State::kEmpty)); 
}

void ExpandNeighbors(vector<int> & refselectedCell,vector<vector<int>> & refLOpenNodes,vector<vector<State>> & refMygrid,int * goalp)
{
  int xco = refselectedCell[0];
  int yco = refselectedCell[1];
  int gvalue = refselectedCell[2];

  for(int i=0;i<4;i++)
  {
    int neixco = xco + delta[i][0];
    int neiyco = yco + delta[i][1];

    if(CheckValidCell(neixco,neiyco,refMygrid))
    {
      int neigvalue = gvalue+1;
      int neihvalue = Heuristic(neixco,neiyco,goalp[0],goalp[1]);
      AddToOpen(neixco,neiyco,neigvalue,neihvalue,refLOpenNodes,refMygrid);
    }
  }
}