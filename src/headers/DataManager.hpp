#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include <string>

#include "Item.hpp"

class DataManager
{
private:
  std::vector<Item> items;
  int itemsNum;
  float maxWeight;
  int pupulationSize;

  int binaryPosition(float weight);
public:
  // DataManager(/* args */);
  void add(std::string name, float weight, float price);
  Item randomTake(float upBoard);
  void loadFile(std::string path);
  // ~DataManager();
};

#endif