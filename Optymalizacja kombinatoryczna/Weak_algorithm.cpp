#include "Modul2.hpp"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

extern int negative_errors;
extern int positive_errors;
extern int first_oligonukleotide_id;
vector<bool> was_visited;

vector<int> Weak_algorithm(vector<vector<int>> graph)
{
    srand(time(NULL));
    for (int i = 0; i < graph.size(); i++)
        was_visited.push_back(false);
    vector<int> path;
    Find_next(path, graph, first_oligonukleotide_id);
    cout << endl << endl;
    for (int i = 0; i < path.size(); i++)
        cout << path[i]+1 << " ";

    return path;
}

void Find_next(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex)
{
    path.push_back(vertex);
    was_visited[vertex] = true;
    vector<int> possible_next_vertex;
    for (int j = 1; j <= 3; j++)
    {
        for (int i = 0; i < graph[vertex].size(); i++)
            if (graph[vertex][i] == j && !was_visited[i])
                possible_next_vertex.push_back(i);
        if (possible_next_vertex.size() == 1)
        {
            Find_next(path, graph, possible_next_vertex[0]);
            return;
        }
        if (possible_next_vertex.size() > 1)
        {
            int tmp = rand() % possible_next_vertex.size();
            Find_next(path, graph, possible_next_vertex[tmp]);
            return;
        }
        possible_next_vertex.clear();
        
    }

    return;
}
