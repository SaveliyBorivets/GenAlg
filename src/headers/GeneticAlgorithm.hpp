#ifndef GEN_H
#define GEN_H


#include "Backpack.hpp"
#include "Crossover.hpp"
#include "Mutation.hpp"

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>


// Метод отбора
enum class SelectionType {
    Tournament,
    Roulette
};

class GeneticAlgorithm {
private:
    std::mt19937 gen;
    DataManager Data;
    std::vector<Backpack> population; // Популяция
    std::vector<float> fitnesses; // Пригодности
    Crossover crossover; // Класс скрещивания
    Mutation mutation; // Класс мутаций
    SelectionType selectionMethod; // Метод отбора
    std::vector<float> averageFitnessHistory; // Средняя пригодность по поколениям
    std::vector<float> bestFitnessHistory; // Лучшая пригодность по поколениям
    float bestCostOfAllTime;
    int generationCount = 0; // Счётчик поколений

    std::pair<Backpack, Backpack> selectParents();
    void evaluateFitness();
    Backpack tournamentSelection();
    Backpack rouletteSelection();
    float AverageFitness();
    float BestFitness();

public:
    GeneticAlgorithm(DataManager data);

    std::string getCeurrentPopulation();
    std::string getInfo();
    int getGenCount();
    std::vector<float> getAverageFitness();
    std::vector<float> getBestFitness();
    float getBestCostOfAllTime();

    void runGeneration();
    void run();
    void restart(DataManager data);
    
    // Сеттеры
    void setCrossoverType(CrossoverType t);
    void setMutationType(MutationType t);
    void setSelectionType(SelectionType t);
};

#endif