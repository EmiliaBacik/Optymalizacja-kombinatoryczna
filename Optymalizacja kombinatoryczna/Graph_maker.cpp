#include "Modul1.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

extern std::vector<char> first_oligonucleotide;
extern int first_oligonukleotide_id;

vector<vector<int>> Graph_maker(vector<vector<char>> spectrum)
{
    vector<vector<int>> graph(spectrum.size()); //reprezentacja - macierz sasiedztwa
    for (int i = 0; i < spectrum.size(); i++) //inicjalizacja, wypelnianie zerami
        for (int j = 0; j < spectrum.size(); j++)
            graph[i].push_back(0);
    for (int i = 0; i < spectrum.size(); i++) //szukanie krawedzi miedzy wierzcholkami
        for (int j = 0; j < spectrum.size(); j++)
        {
            if (i == j)
                continue;
            int weight = Imposition(spectrum[i], spectrum[j]);
            graph[i][j] = weight;
        }
    /*for (int i = 0; i < spectrum.size(); i++) //wyswietla macierz
    {
        for (int j = 0; j < spectrum.size(); j++)
            cout << graph[i][j];
        cout << endl;
    }*/
    return graph;
}
int Imposition(vector<char> A, vector<char> B)
{
    int identical = 0;
    for (int i = 0; i < A.size() - 1; i++) //sprawdzenie nalozenia 1
    {
        if (A[i + 1] == B[i])
            identical++;
        else
            break;
    }
    if (identical == A.size() - 1)
        return 1;
    else
        identical = 0;
    for (int i = 0; i < A.size() - 2; i++) //sprawdzenie nalozenia 2
    {
        if (A[i + 2] == B[i])
            identical++;
        else
            break;
    }
    if (identical == A.size() - 2)
        return 2;
    else
        identical = 0;
    for (int i = 0; i < A.size() - 3; i++) //sprawdzenie nalozenia 3
    {
        if (A[i + 3] == B[i])
            identical++;
        else
            break;
    }
    if (identical == A.size() - 3)
        return 3;
    return 0;
}
std::vector<std::vector<char>> loadSpectrumFromFile(const std::string& fileName) // Funkcja do wczytania dwuwymiarowego wektora z pliku
{
    std::vector<std::vector<char>> spectrum;
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::vector<char> row(line.begin(), line.end());
            spectrum.push_back(row);
        }
        for (int i = 0; i < spectrum.size(); i++) { //znajdywanie pierwszego oligonukleotydu
            if (spectrum[i] == first_oligonucleotide)
                first_oligonukleotide_id = i; }
        inFile.close();
        std::cout << "Spektrum zostalo wczytane z pliku " << fileName << std::endl;
    }
    else {
        std::cerr << "Blad podczas otwierania pliku " << fileName << std::endl;
    }
    return spectrum;
}
