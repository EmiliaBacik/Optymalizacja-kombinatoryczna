#include "Modul1.hpp"
#include "Modul2.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream> // dodana biblioteka do zapisu
using namespace std;

int negative_errors = 4; //uwaga - tylko na poczatku, ulegnie zmianie przy generowaniu spektrum!
int positive_errors = 3;
int n = 15;
int k = 5;
std::vector<char> first_oligonucleotide;
int first_oligonukleotide_id=0;


int main()
{
    Sequence_generator();  // generuje sekwencje
    Spectrum_generator(); // wczytuje sekwencje z pliku i na jej podstawie robi spektrum
    vector<vector<char>> spectrum = loadSpectrumFromFile("spektrum.txt");
    vector<char> sequence = loadSequenceFromFile("sekwencja.txt");
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
    //vector<int> path2 = Heuristic_algorithm(graph);
    return 0;
}
