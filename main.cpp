#include <iostream>

#include "src/headers/GeneticAlgorithm.hpp"

int main() {
  DataManager dm;
  // dm.loadFile("./data.txt");
  dm.randomLoad();
  dm.setFitness(FitnessType::Cutting);
  std::cout << dm.getInfo();
  GeneticAlgorithm go(dm);
  std::cout << go.getInfo();
  std::cout << go.getCeurrentPopulation();
  // go.run();
//   Backpack backpack(dm);
//   for (size_t i = 0; i < backpack.getSolution().size(); i++) {
// //    std::cout << backpack.getSolution()[i] << " ";
//     std::cout << dm.getItems()[i].price << " ";
//   }
//   std::cout << std::endl;
//   std::cout << backpack.getFitnessValue1(dm) << std::endl;
//   std::cout << backpack.getFitnessValue2(dm) << std::endl;
}