#ifndef Modul1_hpp
#define Modul1_hpp
#include <iostream>
#include <vector>

//Instance_generator
void Sequence_generator();
void Spectrum_generator();
void Quick_sort(std::vector<std::vector<char>>& spectrum, int left, int right);
void saveSequenceToFile(const std::vector<char>& sequence, const std::string& fileName);
void saveSpectrumToFile(const std::vector<std::vector<char>>& spectrum, const std::string& fileName);
std::vector<char> loadSequenceFromFile(const std::string& fileName);

//Graph_maker
std::vector<std::vector<char>> loadSpectrumFromFile(const std::string& fileName);
std::vector<std::vector<int>> Graph_maker(std::vector<std::vector<char>> spectrum);
int Imposition(std::vector<char> A, std::vector<char> B);

#endif
