#include "Instance_generator.hpp"
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
int k = 4;
std::vector<char> first_oligonucleotide;

//TESTY2
int main()
{
    cout << "start i testy" << endl;
    Sequence_generator();  // generuje sekwencje
    Spectrum_generator(); // wczytuje sekwencje z pliku i na jej podstawie robi spektrum
    vector<vector<char>> spectrum = loadSpectrumFromFile("spektrum.txt");
    vector<char> sequence = loadSequenceFromFile("sekwencja.txt");
    for (int i = 0; i < k; i++) //zapis pierwszego oligonukleotydu
        first_oligonucleotide.push_back(sequence[i]);
    for (int i = 0; i < n; i++) // wyswietlanie sekwencji
        cout << sequence[i];
    cout << endl;
    cout << "negative errors: " << negative_errors << endl; //wyswietla wazne i dostepne dla nas informacje
    cout << "positive errors: " << positive_errors << endl;
    cout << "first oligonucleotide: ";
    for (int i = 0; i < first_oligonucleotide.size(); i++)
        cout << first_oligonucleotide[i];
    cout << endl << endl;
    for (int i = 0; i < spectrum.size(); i++) //wyswietlenie gotowego spektrum
    {
        for (int j = 0; j < spectrum[i].size(); j++)
            cout << spectrum[i][j];
        cout << endl;
    }                                  //do tego miejsca haha
    cout << endl;
    vector<vector<int>> graph = Graph_maker(spectrum); //macierz sasiedztwa: 0-brak krawedzi, 1,2,3-waga krawedzi
    return 0;
}

