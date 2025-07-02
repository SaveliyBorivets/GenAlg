#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "Backpack.hpp"
#include "DataManager.hpp"

#include <vector>
#include <random>

// Типы скрещивания
enum class CrossoverType {
    OnePoint,      // Одноточечное
    TwoPoint,      // Двухточечное
    Uniform        // Равномерное
};

class Crossover {
private:
    CrossoverType type; 
    std::mt19937 gen;
    std::pair<Backpack, Backpack> onePoint(const Backpack& parent1, const Backpack& parent2, DataManager& data); // Одноточечное скрещивание
    std::pair<Backpack, Backpack> twoPoint(const Backpack& parent1, const Backpack& parent2, DataManager& data); // Двухточечное скрещивание
    std::pair<Backpack, Backpack> uniform(const Backpack& parent1, const Backpack& parent2, DataManager& data); // Равномерное скрещивание
public:
    float probability; 
    Crossover(float prob, CrossoverType t);
    std::pair<Backpack, Backpack> cross(const Backpack& parent1, const Backpack& parent2, DataManager& data); // Скрещивание
};

#endif