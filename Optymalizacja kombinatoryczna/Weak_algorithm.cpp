#include "Modul2.hpp"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

extern int negative_errors;
extern int positive_errors;
extern int first_oligonukleotide_id;
extern int n;
extern int k;
vector<bool> was_visited;
int one_not_chosen = 0; //licznik wybrania gorszych krawedzi pod rzad
int parametr_not_chosen = 2; //!!!do zmian!!! - po ilu gorszych krawêdziach nale¿y przeskoczyæ w inne miejsce w algorytmie

vector<int> Weak_algorithm(vector<vector<int>> graph)
{
    for (int i = 0; i < graph.size(); i++)
        was_visited.push_back(false);
    vector<int> path;
    Find_next(path, graph, first_oligonukleotide_id);
    was_visited.clear(); //zerowanie pamieci
    one_not_chosen = 0;
    return path;
}

void Find_next(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex)
{
    
    path.push_back(vertex);
    was_visited[vertex] = true;
    if (path.size() >= graph.size()-positive_errors) {
        return; }
        
    vector<int> possible_next_vertex;
    for (int j = 1; j <= 3; j++) //interesuja nas tylko krawedzie 1, 2 i 3
    {
        if (one_not_chosen == parametr_not_chosen) //gdy wybrano zbyt wiele gorszych œcie¿ek pod rz¹d - algorytm kr¹¿y bez sensu
        {
            Suboptimum_path(path, graph, vertex);
            return;
        }
        if (j == 2)
            one_not_chosen++;
        for (int i = 0; i < graph[vertex].size(); i++)
            if (graph[vertex][i] == j && !was_visited[i])
                possible_next_vertex.push_back(i);
        if (possible_next_vertex.size() == 1)
        {
            if (j == 1)
                one_not_chosen = 0; //zerujemy licznik
            Find_next(path, graph, possible_next_vertex[0]);
            return;
        }
        else if (possible_next_vertex.size() > 1)
        {
            if (j == 1)
                one_not_chosen = 0; //zerujemy licznik
            int tmp = rand() % possible_next_vertex.size();
            Find_next(path, graph, possible_next_vertex[tmp]);
            return;
        }
         
        possible_next_vertex.clear();
        
    } 
    return; //gdy nastêpuje zagnie¿d¿enie - algorytm nie widzi ¿adnej œcie¿ki
}

void Suboptimum_path(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex)
{
    one_not_chosen = 0;
    vector<int> choose;
    int V = 0;
    for (int i = 0; i < was_visited.size(); i++)
        if (was_visited[i] == false)
        {
            V++;
            choose.push_back(i);
        }
            
    int tmp = rand() % V; //losowanie jeszcze nieodwiedzonego wierzcholka
    int i = choose[tmp];
    was_visited[vertex] = false; //zeby algorytm dijkstry dzialal
    vector<int> sub_path = Dijkstras_algorithm(path, graph, vertex, i);
    was_visited[vertex] = true;
    for (int i = 1; i < sub_path.size()-1; i++)
    {
        was_visited[sub_path[i]] = true;
        path.push_back(sub_path[i]);
    }
    Find_next(path, graph, sub_path[sub_path.size() - 1]);
    return;
}


std::vector<int> Dijkstras_algorithm(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex, int wanted) //wersja szukajaca najkrotszej drogi do jednego wierzcholka, nie wszystkich
{
    vector<bool> S; //czy wierzcholek w zbiorze sprawdzonych?
    int vertex_in_S = 0;
    vector<bool> Q; //czy wierzcholek w zbiorze niesprawdzinych?
    int vertex_in_Q = 0;
    vector<int> d; //tablica z kosztami dojscia
    vector<int> p;
    for (int i = 0; i < graph.size(); i++) {
        S.push_back(false);
        if (was_visited[i] == false) {   //mamy mniej wierzcholkow na starcie
            vertex_in_Q++;
            Q.push_back(true); }
        else {
            vertex_in_S++;
            Q.push_back(false); }
        d.push_back((graph.size()-1) * 30);
        p.push_back(-1); //-1 oznacza brak sciezki
    }
    d[vertex] = 0;
    while (vertex_in_Q != 0)
    {
        int u = 0; //wierzcholek o najkrotszej sciezce z Q
        while (u != Q.size() && Q[u] == false)
            u++;
        for (int i = 0; i < d.size(); i++)
            if (d[i] < d[u] && Q[i] == true)
                u = i;
        if (u >= Q.size())
            break;
        Q[u] = false; //przenosimy do S
        S[u] = true;
        vertex_in_Q--;
        vertex_in_S++;
        vector<int> queue;
        for (int i = 0; i < graph.size(); i++) //znajdujemy nastepniki u
            if (graph[u][i] != 0)
                queue.push_back(i);
        int iteracje = queue.size();
        for (int i = 0; i < iteracje; i++)
        {
            int w = queue[queue.size() - 1];
            queue.pop_back();
            if (Q[w] == false)
                continue;
            int weight = graph[u][w];
            if (weight == 0)
                weight = 4; //jesli krawedz nie istnieje ustaw duza xD
            if (d[w] > d[u] + weight)
            {
                d[w] = d[u] + weight;
                p[w] = u;
            }
        }
    }
    
    vector<int> result_reverse;
    int x = wanted;
    result_reverse.push_back(wanted);
    while (p[x] != -1)
    {
        x = p[x];
        result_reverse.push_back(x);
    }
    vector<int> result;
    for (int i = result_reverse.size() - 1; i >= 0; i--)
        result.push_back(result_reverse[i]);
    return result;
}




