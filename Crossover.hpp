#pragma once
#include "backpack.hpp"
#include <vector>
#include <random>

using namespace std;

// Типы скрещивания
enum class CrossoverType {
    OnePoint,      // Одноточечное
    TwoPoint,      // Двухточечное
    Uniform        // Равномерное
};

class Crossover {
private:
    CrossoverType type; // Выбранный тип скрещивания
    mt19937 gen;

    pair<Backpack, Backpack> onePoint(const Backpack& parent1, const Backpack& parent2); // Одноточечное скрещивание
    pair<Backpack, Backpack> twoPoint(const Backpack& parent1, const Backpack& parent2); // Двухточечное скрещивание
    pair<Backpack, Backpack> uniform(const Backpack& parent1, const Backpack& parent2); // Равномерное скрещивание

public:
    float probability; // Вероятность скрещивания (0.0-1.0)
    Crossover(float prob, CrossoverType t); // Конструктор

    pair<Backpack, Backpack> cross(const Backpack& parent1, const Backpack& parent2); // Скрещивание
};