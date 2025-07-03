#include "../headers/Crossover.hpp"

Crossover::Crossover(float prob, CrossoverType t) : probability(prob), type(t) {
  std::random_device rd;
  gen.seed(rd());
}

std::pair<Backpack, Backpack> Crossover::cross(const Backpack& parent1, const Backpack& parent2) {
  std::uniform_real_distribution<float> chance(0.0, 1.0);
  if (chance(gen) > probability)
    return {parent1, parent2};
  switch (type) {
    case CrossoverType::OnePoint:
      return onePoint(parent1, parent2);
    case CrossoverType::TwoPoint:
      return twoPoint(parent1, parent2);
    case CrossoverType::Uniform:
      return uniform(parent1, parent2);
  }
  return {parent1, parent2};
}

std::pair<Backpack, Backpack> Crossover::onePoint(const Backpack& parent1, const Backpack& parent2) {
  const auto& sol1 = parent1.getSolution(); 
  const auto& sol2 = parent2.getSolution();  
  int size = sol1.size();
  std::uniform_int_distribution<int> dist(1, size - 1);
  int point = dist(gen);
  std::vector<int> solution1(size, 0), solution2(size, 0);
  for (int i = 0; i < size; i++) {
    if (i < point) {
      solution1[i] = sol1[i];
      solution2[i] = sol2[i];
    } 
    else {
      solution1[i] = sol2[i];
      solution2[i] = sol1[i];
    }
  }
  Backpack child1(solution1), child2(solution2);
  return {child1, child2};
}

std::pair<Backpack, Backpack> Crossover::twoPoint(const Backpack& parent1, const Backpack& parent2) {
  const auto& sol1 = parent1.getSolution();
  const auto& sol2 = parent2.getSolution();
  int size = sol1.size();
  std::uniform_int_distribution<int> dist(0, size - 1);
  int point1 = dist(gen);
  int point2 = dist(gen);
  if (point1 > point2) std::swap(point1, point2);
  std::vector<int> solution1(size, 0), solution2(size, 0);
  for (int i = 0; i < size; i++) {
    if (i >= point1 && i <= point2) {
      solution1[i] = sol1[i];
      solution2[i] = sol2[i];
    } 
    else {
      solution1[i] = sol2[i];
      solution2[i] = sol1[i];
    }
  }
  Backpack child1(solution1), child2(solution2);
  return {child1, child2};
}

std::pair<Backpack, Backpack> Crossover::uniform(const Backpack& parent1, const Backpack& parent2) {
  const auto& sol1 = parent1.getSolution(); 
  const auto& sol2 = parent2.getSolution();
  int size = sol1.size();
  std::vector<int> solution1(size, 0), solution2(size, 0);
  std::uniform_int_distribution<int> coin(0, 1);
  for (int i = 0; i < size; i++) {
    if (coin(gen) == 0) {
      solution1[i] = sol1[i];
      solution2[i] = sol2[i];
    } 
    else {
      solution1[i] = sol2[i];
      solution2[i] = sol1[i];
    }
  }
  Backpack child1(solution1), child2(solution2);
  return {child1, child2};
}

#include <iostream>
void Crossover::setType(CrossoverType t) {
  type = t;
}

CrossoverType Crossover::getType() {
  return type;
}
