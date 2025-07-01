#pragma once
#include "backpack.hpp"
#include <vector>
#include <random>

using namespace std;

// 🎲 Тип мутации
enum class MutationType {
    add_remove, // Удаление/вставка
    change      // Обмен
};

class Mutations {
private:
    MutationType mutation; // Выбранный тип мутации
    mt19937 gen;

    void mutateAddOrRemove(vector<int>& items);
    void mutateChange(vector<int>& items);

public:
    float IsMutation; // Вероятность применения мутации (0.0–1.0)

    Mutations(float prob, MutationType type);

    void getMutation(Backpack& backpack);
};
