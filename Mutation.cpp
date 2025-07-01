#include "Mutations.hpp"

Mutations::Mutations(float prob, MutationType type)
    : IsMutation(prob), mutation(type) {
    random_device rd;
    gen.seed(rd());
}

void Mutations::mutateAddOrRemove(vector<int>& items) {
    if (items.empty()) return;

    uniform_int_distribution<int> mut(0, 1);
    int way = mut(gen);

    uniform_int_distribution<int> ind(0, items.size() - 1);
    int index = ind(gen);

    if (way == 0) {
        if (items[index] == 0) {
            items[index] += 1;
            return;
        }
        items[index] -= 1;
    } else {
        items[index] += 1;
    }
}

void Mutations::mutateChange(vector<int>& items) {
    if (items.size() < 2) return;

    uniform_int_distribution<int> ind(0, items.size() - 1);
    int index1 = ind(gen);
    int index2 = ind(gen);
    while (index1 == index2) {
        index2 = ind(gen);
    }

    uniform_int_distribution<int> mut(0, 1);
    int way = mut(gen);

    if (way == 0) {
        if (items[index2] > 0) {
            items[index2] -= 1;
            items[index1] += 1;
        }
    } else {
        if (items[index1] > 0) {
            items[index1] -= 1;
            items[index2] += 1;
        }
    }
}

void Mutations::getMutation(Backpack& backpack) {
    uniform_real_distribution<float> chance(0.0, 1.0);
    if (chance(gen) > IsMutation) return;

    switch (mutation) {
        case MutationType::add_remove:
            mutateAddOrRemove(backpack.items);
            break;
        case MutationType::change:
            mutateChange(backpack.items);
            break;
    }
}
