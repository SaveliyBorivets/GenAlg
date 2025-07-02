#include <iostream>

#include "src/headers/DataManager.hpp"
#include "src/headers/Backpack.hpp"

int main() {
  DataManager dm;
  dm.loadFile("./data.txt");

  Backpack backpack(dm);
  for (int i = 0; i < backpack.getSolution().size(); i++) {
//    std::cout << backpack.getSolution()[i] << " ";
    std::cout << dm.getItems()[i].price << " ";
  }
  std::cout << std::endl;
  std::cout << backpack.getFitnessValue1(dm) << std::endl;
  std::cout << backpack.getFitnessValue2(dm) << std::endl;
}