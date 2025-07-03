#include "../headers/Mutation.hpp"

Mutation::Mutation(float prob, MutationType type) : IsMutation(prob), mutation(type) {
  std::random_device rd;
  gen.seed(rd());
}

void Mutation::mutateAddOrRemove(Backpack& backpack) {
  std::vector<int> items = backpack.getSolution();
  if (items.empty()) return;
  std::uniform_int_distribution<int> mut(0, 1);
  int way = mut(gen);
  std::uniform_int_distribution<int> ind(0, items.size() - 1);
  int index = ind(gen);
  if (way == 0) {
    if (items[index] == 0) {
      backpack.editSolution(index, items[index] + 1);
      return;
    }
    backpack.editSolution(index, items[index] - 1);
  } else {
    backpack.editSolution(index, items[index] + 1);
  }
}

void Mutation::mutateChange(Backpack& backpack) {
  std::vector<int> items = backpack.getSolution();
  if (items.size() < 2) return;
  std::uniform_int_distribution<int> ind(0, items.size() - 1);
  int index1 = ind(gen);
  int index2 = ind(gen);
  while (index1 == index2) {
    index2 = ind(gen);
  }
  backpack.editSolution(index1, items[index2]);
  backpack.editSolution(index2, items[index1]);
}

void Mutation::getMutation(Backpack& backpack) {
  std::uniform_real_distribution<float> chance(0.0, 1.0);
  if (chance(gen) > IsMutation) return;
  std::vector<int> solution = backpack.getSolution();
  switch (mutation) {
    case MutationType::ADD_REMOVE:
      mutateAddOrRemove(backpack);
      break;
    case MutationType::CHANGE:
      mutateChange(backpack);
      break;
  }
}

void Mutation::setType(MutationType t) {
  mutation = t;
}

MutationType Mutation::getType() {
  return mutation;
}