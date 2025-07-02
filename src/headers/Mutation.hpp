#ifndef MUTATION_H
#define MUTATION_H

#include "Backpack.hpp"

#include <vector>
#include <random>

// Тип мутации
enum class MutationType {
    ADD_REMOVE, // Удаление/вставка
    CHANGE      // Обмен
};

class Mutations {
private:
    MutationType mutation; // Выбранный тип мутации
    std::mt19937 gen;
    void mutateAddOrRemove(Backpack& backpack);
    void mutateChange(Backpack& backpack);
public:
    float IsMutation; // Вероятность применения мутации (0.0–1.0)
    Mutations(float prob, MutationType type);
    void getMutation(Backpack& backpack);
};

#endif