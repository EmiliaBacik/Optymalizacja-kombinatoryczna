#include "Modul1.hpp"
#include "Modul2.hpp"
#include "Modul3.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream> // dodana biblioteka do zapisu
using namespace std;

int negative_errors = 10; //uwaga - tylko na poczatku, ulegnie zmianie przy generowaniu spektrum!
int positive_errors = 20;
int n = 50;
int k = 8;
std::vector<char> first_oligonucleotide;
int first_oligonukleotide_id=0;

void Check_result(vector<int> path, vector<vector<char>> spectrum, vector<vector<int>> graph);

int main()
{
    srand(time(NULL));
    //Sequence_generator();  // generuje sekwencje
    //Spectrum_generator(); // wczytuje sekwencje z pliku i na jej podstawie robi spektrum
    vector<char> sequence = loadSequenceFromFile("sekwencja.txt");
    vector<vector<char>> spectrum = loadSpectrumFromFile("spektrum.txt");
    for (int i = 0; i < n; i++) // wyswietlanie sekwencji
        cout << sequence[i];
    cout << endl;
    cout << "negative errors: " << negative_errors << endl; //wyswietla wazne i dostepne dla nas informacje
    cout << "positive errors: " << positive_errors << endl;
    cout << "first oligonucleotide: ";
    for (int i = 0; i < first_oligonucleotide.size(); i++)
        cout << first_oligonucleotide[i];
    cout << endl << "and id: " << first_oligonukleotide_id+1 << endl;
    for (int i = 0; i < spectrum.size(); i++) //wyswietlenie gotowego spektrum
    {
        for (int j = 0; j < spectrum[i].size(); j++)
            cout << spectrum[i][j];
        cout << endl;
    }                                  //do tego miejsca haha
    cout << endl;
    vector<vector<int>> graph = Graph_maker(spectrum); //macierz sasiedztwa: 0-brak krawedzi, 1,2,3-waga krawedzi

    vector<int> path1 = Weak_algorithm(graph);
    cout << endl;
    for (int i = 0; i < path1.size(); i++)
        cout << path1[i] + 1 << " ";
    Check_result(path1, spectrum, graph);
    vector<int> path2 = Heuristic_algorithm(graph);
    cout << endl;
    for (int i = 0; i < path2.size(); i++)
        cout << path2[i] + 1 << " ";
    Check_result(path2, spectrum, graph);
    return 0;
}

void Check_result(vector<int> path, vector<vector<char>> spectrum,vector<vector<int>> graph)
{
    cout << endl << " Result: ";
    for (int i = 0; i < k; i++)
        cout << first_oligonucleotide[i];
    for (int i = 1; i < path.size(); i++)
        if (graph[path[i - 1]][path[i]] == 1)
            cout << spectrum[path[i]][k - 1];
        else if (graph[path[i - 1]][path[i]] == 2)
            cout << spectrum[path[i]][k - 2] << spectrum[path[i]][k - 1];
        else if (graph[path[i - 1]][path[i]] == 3)
            cout << spectrum[path[i]][k - 3] << spectrum[path[i]][k - 2] << spectrum[path[i]][k - 1];
        else
            for (int j = 0; j < k; j++)
                cout << spectrum[path[i]][j];

}