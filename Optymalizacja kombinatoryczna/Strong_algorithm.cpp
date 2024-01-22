#include "Modul3.hpp"
#include "Modul2.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <set>

using namespace std;
vector<vector<double>> pheromone_matrix;
extern int negative_errors;
extern int positive_errors;
extern int first_oligonukleotide_id;
extern int parametr_not_chosen;
int s_one_not_chosen = 0;
int repetition_chosen = 0;
vector<bool> s_was_visited;
vector<vector<int>> paths;
int parametr_number_of_ants = 150; //DO ZMIAN PRZY TESTACH!!! LICZBA MRÓWEK
int parametr_of_nonconformity = 80; //od 1 =1% czy cos w tym stylu do 100 =100%/ prawdopodobienstwo ze mrowka wybierze nowa sciezke (zamiast podazac za feromonami) //bedzie sie zmienial z czasem dzialania programu!!
int parametr_of_time = 30;

vector<int> Heuristic_algorithm(vector<vector<int>> graph)
{
	cout << endl << "Heuristic algorithm is working";
	Make_pheromone_matrix(graph);
	vector<vector<int>> first_paths;
	for (int i = 0; i < parametr_number_of_ants; i++) //wypuszczamy mrówki ca³kowicie losowo i zapisujemy rozwi¹zanie od ka¿dej z nich
	{
		vector<int> tmp = Weak_algorithm(graph);
		first_paths.push_back(tmp);
	}
	vector<vector<int>> solution = Rate_solution(first_paths, graph);
	solution.clear();
	first_paths.clear();
	clock_t t = clock();
	clock_t x = 0;
	while (((x - t) / CLOCKS_PER_SEC) < parametr_of_time)
	{
		paths.clear();
		vector<vector<int>> everypath;
		for (int i = 0; i < parametr_number_of_ants; i++)
		{
			for (int j = 0; j < graph.size(); j++)
				s_was_visited.push_back(false);
			vector<int> path;	
			Strong_find_next(path, graph, first_oligonukleotide_id);
			everypath.push_back(path);
			s_was_visited.clear(); //zerowanie pamieci
			s_one_not_chosen = 0;
			repetition_chosen = 0;
		}
		solution = Rate_solution(everypath, graph);
		for (int j = 0; j < solution.size(); j++)
			paths.push_back(solution[j]);
		everypath.clear();
		Pheromone_pairing;
		Smoothing_values;
		parametr_of_nonconformity = parametr_of_nonconformity - 5;
		x = clock();
	}
	return paths[0];
}

void Make_pheromone_matrix(vector<vector<int>> graph) //wype³nia zerami macierz o wielkoœci macierzy reprezentuj¹cej graf
{
	for (int i = 0; i < graph.size(); i++)
	{
		vector<double> tmp;
		for (int j = 0; j < graph[i].size(); j++)
			tmp.push_back(0.0);
		pheromone_matrix.push_back(tmp);
	}
}

vector<vector<int>> Rate_solution(vector<vector<int>> paths, vector<vector<int>> graph)
{
	vector<int> quotation;
	vector<vector<int>> solution;
	for (int i = 0; i < paths.size(); i++)
	{
		int tmp = 0;
		tmp = tmp + 2 * paths[i].size(); //dostaje tyle punktów jak¹ ma d³ugoœæ
		int counter=0; //licznik krawedzi nierownych 1
		for (int j = 0; j < paths[i].size() - 1; j++) //dostaje punkty za krawedzi 1 traci gdy krawedz!=1
		{
			
			if (graph[paths[i][j]][paths[i][j + 1]] == 1)
				tmp++;
			else if (graph[paths[i][j]][paths[i][j + 1]] == 2)
				counter++;
			else if (graph[paths[i][j]][paths[i][j + 1]] == 3) {
				counter = counter + 2;
				tmp=tmp-2; }
			else {
				counter = counter + 3;
				tmp = tmp - 10; }
		}
		int difference2 = counter - negative_errors; // czy dobra iloœæ b³êdów negatywnych
		if (difference2 == 0)
			tmp = tmp + 1.5 * tmp;
		else if (difference2 <= 10)
			tmp = tmp + 0.2 * tmp;
		else
			tmp = tmp - 0.3 * tmp;
		int difference3 = graph.size() - paths[i].size(); //liczba nieodwiedzonych wierzcholkow czy rowna bledom pozytywnym
		if (difference3 > positive_errors)
			difference3 = difference3 - positive_errors;
		else
			difference3 = positive_errors - difference3;
		if (difference3 == 0)
			tmp = tmp + 1.5 * tmp;
		else if (difference3 <= 10)
			tmp = tmp + 0.2 * tmp;
		else
			tmp = tmp - 0.3 * tmp;
		quotation.push_back(tmp);
	}

	for (int i = 0; i < 10; i++)
	{
		int best = 0;
		for (int j = 0; j < quotation.size(); j++)
			if (quotation[j] > best)
				best = j;
		solution.push_back(paths[best]);
		quotation[best] = -100;
	}
	double add_value= 1.0;
	for (int i = 0; i <10; i++) //odklada wartosci na macierz feromonowa
	{
		for (int j = 0; j < solution[i].size() - 1; j++)
		{
			pheromone_matrix[solution[i][j]][solution[i][j+1]] =+ add_value;
		}
		add_value = add_value - 0.1;
	}
	return solution;
}

void Strong_find_next(vector<int>& path, vector<vector<int>> graph, int vertex)
{
	path.push_back(vertex);
	s_was_visited[vertex] = true;
	if (path.size() >= graph.size() - positive_errors) {
		return;
	}

	int draw = rand() % 100;
	int test = 0;
	
	for (int i = 0; i < pheromone_matrix[vertex].size(); i++)
	{
		if (pheromone_matrix[vertex][i] > 0 && s_was_visited[i] == false)
		{
			test = 1;
			break;
		}
			
	}
	if (draw > parametr_of_nonconformity && test==1) //podazy za feromonami
	{
		vector<int> possible_next_vertex;
		
		vector<double> matrix_tmp;
		for(int i=0; i<pheromone_matrix[vertex].size(); i++)
			matrix_tmp.push_back(pheromone_matrix[vertex][i]); //kopia macierzy feromonow
		int best;
		while (!matrix_tmp.empty())	
		{
			best = 0;
			for (int i = 0; i < matrix_tmp.size(); i++)
			{
				if (matrix_tmp[i] > matrix_tmp[best] && s_was_visited[i]==false)
					best = i;
			}
			if (matrix_tmp[best] != 0 && s_was_visited[best]==false)
			{
				possible_next_vertex.push_back(best); //dodaje kolejne wierzcholki od tego z najwieksza iloscia feromonow do tego z najmniejsza
				matrix_tmp[best] = 0;
			}
			else
				matrix_tmp.clear();
		}
		int tmp = 0;
		if (possible_next_vertex.size() > 1)
			tmp = Find_number_of_probability(possible_next_vertex.size());
		else
			tmp = 0;
		if (possible_next_vertex.size() == 0)
			return;
		Strong_find_next(path, graph, possible_next_vertex[tmp]);
		return;
	}
	else //znajdzie nowa odnoge
	{
	vector<int> possible_next_vertex;
	for (int j = 1; j <= 3; j++) //interesuja nas tylko krawedzie 1, 2 i 3
	{
		if (s_one_not_chosen == parametr_not_chosen) //gdy wybrano zbyt wiele gorszych œcie¿ek pod rz¹d - algorytm kr¹¿y bez sensu
		{
			Strong_suboptimum_path(path, graph, vertex);
			return;
		}
		if (j == 2)
			s_one_not_chosen++;
		for (int i = 0; i < graph[vertex].size(); i++)
			if (graph[vertex][i] == j && s_was_visited[i] == false)
			possible_next_vertex.push_back(i);
		if (possible_next_vertex.size() == 1)
		{
			if (j == 1)
				s_one_not_chosen = 0; //zerujemy licznik
			Strong_find_next(path, graph, possible_next_vertex[0]);
			return;
		}
		else if (possible_next_vertex.size() > 1)
		{
			if (j == 1)
				s_one_not_chosen = 0; //zerujemy licznik
			int tmp;
			if (possible_next_vertex.size() > 1)
				tmp = rand() % possible_next_vertex.size();
			else
				tmp = 0;
			Strong_find_next(path, graph, possible_next_vertex[tmp]);
			return;
		}

		possible_next_vertex.clear();

	}
	return;
	}
}

void Strong_suboptimum_path(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex)
{
	s_one_not_chosen = 0;
	vector<int> choose;
	int V = 0;
	for (int i = 0; i < s_was_visited.size(); i++)
		if (s_was_visited[i] == false)
		{
			V++;
			choose.push_back(i);
		}

	int tmp = rand() % V; //losowanie jeszcze nieodwiedzonego wierzcholka
	int i = choose[tmp];
	s_was_visited[vertex] = false; //zeby algorytm dijkstry dzialal
	vector<int> sub_path = Strong_dijkstras_algorithm(path, graph, vertex, i);
	s_was_visited[vertex] = true;
	for (int i = 1; i < sub_path.size() - 1; i++)
	{
		s_was_visited[sub_path[i]] = true;
		path.push_back(sub_path[i]);
	}
	Strong_find_next(path, graph, sub_path[sub_path.size() - 1]);
	return;
}

int Find_number_of_probability(int number)
{
	int solution=0;
	for(int i = number; i > 0; i--)
		solution = solution + i;
	int tmp = rand() % solution;
	tmp++;
	for (int i = 0; i < number; i++)
	{
		int x = 0;
		int y = 0;
		for (int j = 0; j <= i; j++)
			x = x + j;
		y = x - i;
		if ((tmp < solution - (number * i) + y + 1) && (tmp >= solution - (number * (i + 1)) + x + 1))
			if (number - i - 1 <= number)
				return (number - i - 1);
			else
				return 0;
	}
	return 0; //jeœli error
}

std::vector<int> Strong_dijkstras_algorithm(std::vector<int>& path, std::vector<std::vector<int>> graph, int vertex, int wanted) //wersja szukajaca najkrotszej drogi do jednego wierzcholka, nie wszystkich
{
	vector<bool> S; //czy wierzcholek w zbiorze sprawdzonych?
	int vertex_in_S = 0;
	vector<bool> Q; //czy wierzcholek w zbiorze niesprawdzinych?
	int vertex_in_Q = 0;
	vector<int> d; //tablica z kosztami dojscia
	vector<int> p;
	for (int i = 0; i < graph.size(); i++) {
		S.push_back(false);
		if (s_was_visited[i] == false) {   //mamy mniej wierzcholkow na starcie
			vertex_in_Q++;
			Q.push_back(true);
		}
		else {
			vertex_in_S++;
			Q.push_back(false);
		}
		d.push_back((graph.size() - 1) * 30);
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

void Pheromone_pairing()
{
	for (int i = 0; i < pheromone_matrix.size(); i++)
		for (int j = 0; j < pheromone_matrix[i].size(); j++)
			pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.1 * pheromone_matrix[i][j];
	return;
}

void Smoothing_values()
{
	int average = 0;
	for (int i = 0; i < pheromone_matrix.size(); i++)
		for (int j = 0; j < pheromone_matrix[i].size(); j++)
			if(i!=j)
				average = average + pheromone_matrix[i][j];
	average = average / (pheromone_matrix.size() * pheromone_matrix.size() - pheromone_matrix.size());
	for (int i = 0; i < pheromone_matrix.size(); i++)
		for (int j = 0; j < pheromone_matrix[i].size(); j++)
		{
			if (i == j)
				continue;
			int difference;
			if (pheromone_matrix[i][j] > average)
			{
				difference = pheromone_matrix[i][j] - average;
				if (difference == 0)
					continue;
				else if (difference < 5)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.05 * pheromone_matrix[i][j];
				else if(difference <10)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.1 * pheromone_matrix[i][j];
				else if(difference<20)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.2 * pheromone_matrix[i][j];
				else if(difference<30)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.3 * pheromone_matrix[i][j];
				else if(difference<40)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.4 * pheromone_matrix[i][j];
				else if(difference<50)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.5 * pheromone_matrix[i][j];
				else if(difference<80)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.7 * pheromone_matrix[i][j];
				else 
					pheromone_matrix[i][j] = pheromone_matrix[i][j] - 0.9 * pheromone_matrix[i][j];
			}
			else
			{
				difference = average - pheromone_matrix[i][j];
				if (difference == 0)
					continue;
				else if (difference < 5)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.05 * pheromone_matrix[i][j];
				else if (difference < 10)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.1 * pheromone_matrix[i][j];
				else if (difference < 20)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.2 * pheromone_matrix[i][j];
				else if (difference < 30)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.3 * pheromone_matrix[i][j];
				else if (difference < 40)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.4 * pheromone_matrix[i][j];
				else if (difference < 50)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.5 * pheromone_matrix[i][j];
				else if (difference < 80)
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.7 * pheromone_matrix[i][j];
				else
					pheromone_matrix[i][j] = pheromone_matrix[i][j] + 0.9 * pheromone_matrix[i][j];
			}
		}
	return;
}