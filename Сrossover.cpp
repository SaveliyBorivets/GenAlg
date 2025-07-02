#include "Crossover.hpp"

// Конструктор
Crossover::Crossover(float prob, CrossoverType t)
    : probability(prob), type(t) {
    random_device rd;
    gen.seed(rd());
}

// Скрещивание
pair<Backpack, Backpack> Crossover::cross(Backpack& parent1, Backpack& parent2) {

    // Вероятность скрестить родителей
    uniform_real_distribution<float> chance(0.0, 1.0);
    if (chance(gen) > probability)
        return {parent1, parent2}; // Скрещивания не произошло

    // Выбор типа скрещивания
    switch (type) {
        case CrossoverType::OnePoint:
            return onePoint(parent1, parent2);
        case CrossoverType::TwoPoint:
            return twoPoint(parent1, parent2);
        case CrossoverType::Uniform:
            return uniform(parent1, parent2);
    }
}

// Одноточечное скрещивание
pair<Backpack, Backpack> Crossover::onePoint(Backpack& parent1, Backpack& parent2) {

    // Получение точки скрещивания
    int size = parent1.items.size();
    uniform_int_distribution<int> dist(1, size - 1);
    int point = dist(gen);

    // Получение детей
    Backpack child1, child2;
    child1.items.resize(size);
    child2.items.resize(size);
    for (int i = 0; i < size; i++) {
        if (i < point) {
            child1.items[i] = parent1.items[i];
            child2.items[i] = parent2.items[i];
        } 
        else {
            child1.items[i] = parent2.items[i];
            child2.items[i] = parent1.items[i];
        }
    }

    return {child1, child2};
}


// Двухточечное скрещивание
pair<Backpack, Backpack> Crossover::twoPoint(Backpack& parent1, Backpack& parent2) {

    // Получение точек скрещивания
    int size = parent1.items.size();
    uniform_int_distribution<int> dist(0, size - 1);
    int point1 = dist(gen);
    int point2 = dist(gen);
    if (point1 > point2) swap(point1, point2);

    // Получение детей
    Backpack child1, child2;
    child1.items.resize(size);
    child2.items.resize(size);
    for (int i = 0; i < size; i++) {
        if (i >= point1 && i <= point2) {
            child1.items[i] = parent2.items[i];
            child2.items[i] = parent1.items[i];
        } 
        else {
            child1.items[i] = parent2.items[i];
            child2.items[i] = parent1.items[i];
        }
    }
    return {child1, child2};
}

// Равномерное скрещивание
pair<Backpack, Backpack> Crossover::uniform(Backpack& parent1, Backpack& parent2) {

    int size = parent1.items.size();
    Backpack child1, child2;
    child1.items.resize(size);
    child2.items.resize(size);
    
    // Скрещивание
    uniform_int_distribution<int> coin(0, 1);
    for (int i = 0; i < size; i++) {
        if (coin(gen) == 0) {
            child1.items[i] = parent1.items[i];
            child2.items[i] = parent2.items[i];
        } 
        else {
            child1.items[i] = parent2.items[i];
            child2.items[i] = parent1.items[i];
        }
    }

    return {child1, child2};
}
