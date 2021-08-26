#pragma once

#include <string>
#include <vector>

using namespace std;

enum class State     
{
  kEmpty, 
  kObstacle, 
  kClosed, 
  kPath, 
  kStart, 
  kFinish
};

void ReadBoardFile(string ,vector<vector<State>> & );
vector<State> Parseline(string );
void PrintBoard(vector<vector<State>> & );
string CellString(State );
vector<vector<State>> Search(vector<vector<State>> & ,int* ,int* );
int Heuristic(int ,int ,int , int );
void AddToOpen(int ,int ,int ,int ,vector<vector<int>> & ,vector<vector<State>> & );
bool Compare(vector<int> , vector<int> );
void CellSort(vector<vector<int>> * );
bool CheckValidCell(int ,int ,vector<vector<State>> & );
void ExpandNeighbors(vector<int> & ,vector<vector<int>> & ,vector<vector<State>> & ,int * );