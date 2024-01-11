#ifndef Modul3_hpp
#define Modul3_hpp
#include <iostream>
#include <vector>

std::vector<int> Heuristic_algorithm(std::vector<std::vector<int>> graph);
void Make_pheromone_matrix(std::vector<std::vector<int>> graph);
std::vector<std::vector<int>> Rate_solution(std::vector<std::vector<int>> paths, std::vector<std::vector<int>> graph);
void Strong_find_next(std::vector<int>& path,  std::vector<std::vector<int>> graph, int vertex);
void Strong_suboptimum_path(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex);
int Find_number_of_probability(int number);
std::vector<int> Strong_dijkstras_algorithm(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex, int wanted);
void Pheromone_pairing();
void Smoothing_values();
#endif