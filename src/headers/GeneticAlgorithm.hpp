#pragma once

#include "Backpack.hpp"
#include "Crossover.hpp"
#include "Mutation.hpp"

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
    DataManager Data;
    vector<Backpack> population; // Популяция
    vector<float> fitnesses; // Пригодности
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
    GeneticAlgorithm(DataManager data);

    int getGenCount();
    vector<float> getAverageFitness();
    vector<float> getBestFitness();

    void runGeneration();
    void run();
};