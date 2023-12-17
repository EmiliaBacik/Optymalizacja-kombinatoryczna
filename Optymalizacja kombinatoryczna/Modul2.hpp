#ifndef Modul2_hpp
#define Modul2_hpp
#include <iostream>
#include <vector>


std::vector<int> Weak_algorithm(std::vector<std::vector<int>> graph);
void Find_next(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex);
void Suboptimum_path(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex);
std::vector<int> Dijkstras_algorithm(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex, int wanted);

#endif
