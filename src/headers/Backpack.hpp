#ifndef BACKPACK_H
#define BACKPACK_H

#include <vector>
#include <cstddef>

#include "DataManager.hpp"

class Backpack
{
private:
  std::vector<int> solution;
  float totalPrice;
  float totalWeight;
public:
  Backpack(std::vector<int> solution, DataManager data);
  Backpack(DataManager data);
  void delItem(int pos, DataManager data);
  void addItem(int pos, DataManager data);
  void editSolution(int pos, int amount);
  std::vector<int> getSolution() const;
  float getTotalPrice() const;
  float getTotalWeight() const;
  // ценность вещей которые можно поместить в рюкзак
  float getFitnessValue1(DataManager data) const;
  // если перебор по весу приспособленность = 0
  float getFitnessValue2(DataManager data) const;
  // ~Backpack();
};

#endif