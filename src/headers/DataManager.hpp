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
  int populationSize;

  int binarySearch(float weight);
public:
  // DataManager(/* args */);
  void add(float weight, float price);
  int randomTake(float upBoard);
  void loadFile(std::string path);
  void stringParse(std::string info);
  std::vector<Item> getItems();
  float getMaxWeight();
  // ~DataManager();
};

#endif