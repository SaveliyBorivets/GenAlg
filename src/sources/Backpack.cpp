#include "../headers/Backpack.hpp"

Backpack::Backpack(std::vector<int> sol) {
  solution = sol;
}

Backpack::Backpack(DataManager data) {
  float totalPrice = 0;
  float totalWeight = 0;
  std::vector<Item> items = data.getItems();
  solution = std::vector<int>(items.size(), 0);
  int pos;
  while ((pos = data.randomTake(data.getMaxCapacity() - totalWeight)) != -1) {
    solution[pos] += 1;
    totalWeight += items[pos].weight;
  }
}

void Backpack::delItem(int pos, DataManager data) {
  if (solution[pos] == 0) {
    return;
  }
  solution[pos] -= 1;
}

void Backpack::addItem(int pos, DataManager data) {
  solution[pos] += 1;
}

void Backpack::editSolution(int pos, int amount) {
  solution[pos] = amount;
}

std::vector<int> Backpack::getSolution() const {
  return solution;
}

float Backpack::getFitnessValue1(DataManager data) const {
  float totalVal = 0, weight = 0;
  std::vector<Item> items = data.getItems();
  for (size_t i = 0; i < items.size(); i++) {
    if (weight + items[i].weight * solution[i] <= data.getMaxCapacity()) {
      totalVal += items[i].price * solution[i];
      weight += items[i].weight * solution[i];
    }
  }
  return totalVal;
}

float Backpack::getFitnessValue2(DataManager data) const {
  float totalVal = 0, weight = 0;
  std::vector<Item> items = data.getItems();
  for (size_t i = 0; i < items.size(); i++) {
    totalVal += items[i].price * solution[i];
    weight += items[i].weight * solution[i];
    if (weight > data.getMaxCapacity()) {
      return 0;
    }
  }
  return totalVal;
}

// void Backpack::printBackpack() {
//   for (size_t i = 0; i < solution; ++i) {

//   }
// }