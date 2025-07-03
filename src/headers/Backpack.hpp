#ifndef BACKPACK_H
#define BACKPACK_H

#include <vector>
#include <cstddef>

#include "DataManager.hpp"

class Backpack
{
private:
  std::vector<int> solution;
public:
  Backpack(std::vector<int> solution);
  Backpack(DataManager data);
  void delItem(int pos);
  void addItem(int pos);
  void editSolution(int pos, int amount);
  std::vector<int> getSolution() const;
  // ценность вещей которые можно поместить в рюкзак
  float getFitnessValue1(DataManager data) const;
  // если перебор по весу приспособленность = 0
  float getFitnessValue2(DataManager data) const;
  // ~Backpack();
  void printBackpack();
};

#endif