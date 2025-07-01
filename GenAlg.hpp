#pragma once
#include "Backpack.hpp"
#include "Crossover.hpp"
#include "Mutations.hpp"
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// Метод отбора
enum class SelectionType {
    Tournament,
    Roulette
};

class GeneticAlgorithm {
private:
    mt19937 gen;

    vector<Backpack> population; // Популяция
    Crossover crossover; // Класс скрещивания
    Mutations mutation; // Класс мутаций
    SelectionType selectionMethod; // Метод отбора
    vector<float> averageFitnessHistory; // Средняя пригодность по поколениям
    vector<float> bestFitnessHistory; // Лучшая пригодность по поколениям
    int generationCount = 0; // Счётчик поколений
    int maxGenerations; // Критерий остановки

    pair<Backpack, Backpack> selectParents();
    void evaluateFitness();
    Backpack tournamentSelection();
    Backpack rouletteSelection();
    float AverageFitness();
    float BestFitness();

public:
    GeneticAlgorithm(int popSize, int maxGen, Crossover cros, Mutations mut, SelectionType selType);

    int get_genCount();
    vector<float> get_averageFitness();
    vector<float> get_bestFitness();

    void runGeneration();
    void run();
};