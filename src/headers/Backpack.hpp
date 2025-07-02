#ifndef BACKPACK_H
#define BACKPACK_H

#include <vector>

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
  const std::vector<int> getSolution();
  const float getTotalPrice();
  const float getTotalWeight();
  // ценность вещей которые можно поместить в рюкзак
  const float getFitnessValue1(DataManager data);
  // если перебор по весу приспособленность = 0
  const float getFitnessValue2(DataManager data);
  // ~Backpack();
};

#endif