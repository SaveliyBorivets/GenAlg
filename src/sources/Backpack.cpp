#include "../headers/Backpack.hpp"

Backpack::Backpack(std::vector<int> sol, DataManager data) {
  solution = sol;
  totalPrice = 0;
  totalWeight = 0;
  std::vector<Item> items = data.getItems();
  for (int i = 0; i < items.size(); ++i) {
    totalPrice += items[i].price * sol[i];
    totalWeight += items[i].weight * sol[i];
  }
}

Backpack::Backpack(DataManager data) {
  totalPrice = 0;
  totalWeight = 0;
  std::vector<Item> items = data.getItems();
  solution = std::vector<int>(items.size(), 0);
  int pos;
  while ((pos = data.randomTake(data.getMaxWeight() - totalWeight)) != -1) {
    solution[pos] += 1;
    totalPrice += items[pos].price;
    totalWeight += items[pos].weight;
  }
}

void Backpack::delItem(int pos, DataManager data) {
  if (solution[pos] == 0) {
    return;
  }
  solution[pos] -= 1;
  totalPrice -= data.getItems()[pos].price;
  totalWeight -= data.getItems()[pos].weight;
}

void Backpack::addItem(int pos, DataManager data) {
  solution[pos] += 1;
  totalPrice += data.getItems()[pos].price;
  totalWeight += data.getItems()[pos].weight;
}

std::vector<int> Backpack::getSolution() const {
  return solution;
}

float Backpack::getTotalPrice() const {
  return totalPrice;
}

float Backpack::getTotalWeight() const {
  return totalWeight;
}

float Backpack::getFitnessValue1(DataManager data) const {
  float totalVal = 0, weight = 0;
  std::vector<Item> items = data.getItems();
  for (int i = 0; i < items.size(); i++) {
    if (weight <= data.getMaxWeight()) {
      totalVal += items[i].price * solution[i];
      weight += items[i].price * solution[i];
    }
  }
  return totalVal;
}

float Backpack::getFitnessValue2(DataManager data) const {
  float totalVal = 0, weight = 0;
  std::vector<Item> items = data.getItems();
  for (int i = 0; i < items.size(); i++) {
    totalVal += items[i].price * solution[i];
    weight += items[i].price * solution[i];
    if (weight > data.getMaxWeight()) {
      return 0;
    }
  }
  return totalVal;
}