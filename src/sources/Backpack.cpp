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

void Backpack::delItem(int pos) {
  if (solution[pos] == 0) {
    return;
  }
  solution[pos] -= 1;
}

void Backpack::addItem(int pos) {
  solution[pos] += 1;
}

std::vector<int> Backpack::getSolution() {
  return solution;
}

float Backpack::getTotalPrice() {
  return totalPrice;
}

float Backpack::getTotalWeight() {
  return totalWeight;
}

float Backpack::getValueV1(DataManager data) {
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

float Backpack::getValueV2(DataManager data) {
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