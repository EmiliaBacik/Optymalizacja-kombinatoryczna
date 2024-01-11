#include "Modul1.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

extern int negative_errors; //uwaga - tylko na poczatku, ulegnie zmianie przy generowaniu spektrum!
extern int positive_errors;
extern int n;
extern int k;
extern std::vector<char> first_oligonucleotide;
extern int first_oligonukleotide_id;

void saveSequenceToFile(const std::vector<char>& sequence, const std::string& fileName)  // zapisuje sekwencje do pliku
{
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (char nucleotide : sequence) {
            outFile << nucleotide;
        }
        outFile.close();
    }
}
void saveSpectrumToFile(const std::vector<std::vector<char>>& spectrum, const std::string& fileName) // zapisuje spektrum do pliku
{
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (const auto& row : spectrum) {
            for (char element : row) {
                outFile << element;
            }
            outFile << '\n';  // Nowy wiersz po ka¿dym rzêdzie
        }
        outFile.close();
    }
}
void Quick_sort(vector<vector<char>>& spectrum, int left, int right)  // sortuje alfabetycznie spektrum
{
    int i = left;
    int j = right;
    vector<char> x = spectrum[(left + right) / 2];
    do
    {
        while (spectrum[i] < x)
            i++;
        while (spectrum[j] > x)
            j--;
        if (i <= j)
        {
            spectrum[i].swap(spectrum[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (left < j) Quick_sort(spectrum, left, j);
    if (right > i) Quick_sort(spectrum, i, right);
}
bool operator <(const vector<char>& x, const vector<char>& y) //przerzuciłam obie funkcje tu bo dotyczą bezpośrednio funkcji Quick_sort
{
    if (x == y)
        return false;
    int n = 0;
    if (x.size() > y.size())
        n = y.size();
    else
        n = x.size();
    for (int i = 0; i < n; i++)
    {
        if (x[i] == y[i])
            continue;
        else
        {
            char tmp = x[i];
            switch (tmp)
            {
            case 'A':
                return true;
                break;
            case 'C':
                if (y[i] == 'A')
                    return false;
                else
                    return true;
                break;
            case 'G':
                if (y[i] == 'T')
                    return true;
                else
                    return false;
                break;
            case 'T':
                return false;
                break;
            }
        }
    }
    if (x.size() < y.size())
        return true;
    else
        return false;
}
bool operator >(const vector<char>& x, const vector<char>& y)
{
    if (x == y)
        return false;
    int n = 0;
    if (x.size() > y.size())
        n = y.size();
    else
        n = x.size();
    for (int i = 0; i < n; i++)
    {
        if (x[i] == y[i])
            continue;
        else
        {
            char tmp = x[i];
            switch (tmp)
            {
            case 'A':
                return false;
                break;
            case 'C':
                if (y[i] == 'A')
                    return true;
                else
                    return false;
                break;
            case 'G':
                if (y[i] == 'T')
                    return false;
                else
                    return true;
                break;
            case 'T':
                return true;
                break;
            }
        }
    }
    if (x.size() > y.size())
        return true;
    else
        return false;
}
void Sequence_generator()
{
    vector<char> sequence;
    srand(time(NULL));
    for (int i = 0; i < n; i++) //losowanie sekwencji
    {
        int tmp = rand() % 4;
        switch (tmp)
        {
        case 0:
            sequence.push_back('A');
            break;
        case 1:
            sequence.push_back('C');
            break;
        case 2:
            sequence.push_back('G');
            break;
        case 3:
            sequence.push_back('T');
            break;
        }
    }
    //for (int i = 0; i < n; i++) // wyswietlanie sekwencji
      //  cout << sequence[i];
    //cout << endl;
    saveSequenceToFile(sequence, "sekwencja.txt"); // zapis sekwencji do pliku
    //for (int i = 0; i < k; i++) //zapis pierwszego oligonukleotydu
      //  first_oligonucleotide.push_back(sequence[i]);
    return;
}
void Spectrum_generator()
{
    int negative_errors_still = negative_errors;
    int positive_errors_still = positive_errors;
    vector<char> sequence = loadSequenceFromFile("sekwencja.txt");
    vector<vector<char>> spectrum;
    for (int i = 0; i < n - k + 1; i++) //tworzenie spektrum
    {
        vector<char> tmp;
        for (int j = 0; j < k; j++)
            tmp.push_back(sequence[i + j]);
        bool was_earlier = false;
        for (int j = 0; j < spectrum.size(); j++)
            if (spectrum[j] == tmp) //zauwazenie powtorzenia w spektrum
            {
                was_earlier = true;
                break;
            }
        if (!was_earlier)
            spectrum.push_back(tmp);
        else
        {
            negative_errors++;
        }
    }
    while (negative_errors_still > 0) //dodanie bledow negatywnych
    {
        int tmp = rand() % (spectrum.size() - 1);
        tmp++; //uniemozliwiam wybranie pierwszego k-meru
        spectrum[tmp].clear();
        for (int j = tmp; j < spectrum.size() - 1; j++)
            spectrum[j].swap(spectrum[j + 1]);
        spectrum.pop_back();
        negative_errors_still--;
    }
    while (positive_errors_still > 0) //dodanie bledow pozytywnych
    {
        int tmp = rand() % (spectrum.size() - 1);
        vector<char> oligonucleotide;
        for (int j = 0; j < k; j++)
        {
            int drow = rand() % 5; //szansa na wystapienie bledu na danej pozycji = 1/5
            if (drow == 0)
            {
                int choose = rand() % 4;
                switch (choose)
                {
                case 0:
                    oligonucleotide.push_back('A');
                    break;
                case 1:
                    oligonucleotide.push_back('C');
                    break;
                case 2:
                    oligonucleotide.push_back('G');
                    break;
                case 3:
                    oligonucleotide.push_back('T');
                    break;
                }
            }
            else
                oligonucleotide.push_back(spectrum[tmp][j]);
        }
        bool was_earlier = false;
        for (int j = 0; j < spectrum.size(); j++)
            if (spectrum[j] == oligonucleotide) //zauwazenie powtorzenia w spektrum
            {
                was_earlier = true;
                break;
            }
        if (!was_earlier)
        {
            spectrum.push_back(oligonucleotide);
            positive_errors_still--;
        }
    }
    Quick_sort(spectrum, 0, spectrum.size() - 1); //sortowanie alfabetyczne spektrum (utrata informacji o kolejnosci oligonukleotydow)

    for (int i = 0; i < spectrum.size(); i++) //znajdywanie pierwszego oligonukleotydu
    {
        if (spectrum[i] == first_oligonucleotide)
            first_oligonukleotide_id = i;
    }

    saveSpectrumToFile(spectrum, "spektrum.txt"); // zapis spektrum do pliku
    return;
}
std::vector<char> loadSequenceFromFile(const std::string& fileName)  // wczytywanie sekwencji
{
    std::vector<char> sequence;
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        char nucleotide;
        while (inFile >> nucleotide) {
            sequence.push_back(nucleotide);
        }
        for (int i = 0; i < k; i++) //zapis pierwszego oligonukleotydu
            first_oligonucleotide.push_back(sequence[i]);
        inFile.close();
        std::cout << "Sekwencja zostala wczytana z pliku " << fileName << std::endl;
    }
    else {
        std::cerr << "Blad podczas otwierania pliku " << fileName << std::endl;
    }
    return sequence;
}