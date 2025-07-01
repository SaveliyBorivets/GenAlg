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
  void delItem(int pos);
  void addItem(int pos);
  std::vector<int> getSolution();
  float getTotalPrice();
  float getTotalWeight();
  // ценность вещей которые можно поместить в рюкзак
  float getValueV1(DataManager data);
  // если перебор по весу приспособленность = 0
  float getValueV2(DataManager data);
  // ~Backpack();
};

#endif