#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include <string>

#include "Item.hpp"

enum class FitnessType {
  Cutting,
  Gentle
};

class DataManager
{
private:
  std::vector<Item> items;
  float maxCapacity;
  int populationSize;
  FitnessType fitness;
  int binarySearch(float weight);
public:
  // DataManager(/* args */);
  void add(float weight, float price);
  int randomTake(float upBoard);
  void randomLoad();
  std::string loadFile(std::string path);
  std::string stringParse(std::string info);
  std::vector<Item> getItems();

  void setFitness(FitnessType fitn);
  
  FitnessType getFitness();
  float getMaxCapacity();
  int getPopulationSize();
  int getItemsNum();
  // ~DataManager();
};

#endif