#include "../headers/DataManager.hpp"

#include <fstream>
#include <sstream>
#include <random>
#include <iostream>

int DataManager::binarySearch(float weight){
  int left = 0;
  int right = items.size();
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (items[mid].weight <= weight) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return left;
}

void DataManager::add(float price, float weight) {
  if (weight <= 0 || weight > maxCapacity || price <= 0) {
    return;
  }
  Item something;
  something.price = price;
  something.weight = weight;
  something.unitPrice = price / weight;
  int pos = binarySearch(weight);
  items.insert(items.begin() + pos, something);
}

int DataManager::randomTake(float upBoard) {
  std::random_device rd;
  std::mt19937 gen(rd());
  int pos = binarySearch(upBoard);
  if (pos == 0) {
    return -1;
  }
  std::uniform_int_distribution<> dist(0, pos - 1);
  return dist(gen);
}

void DataManager::loadFile(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Ошибка открытия файла: " + path);
  }

  std::string fileText(
      (std::istreambuf_iterator<char>(file)),
      std::istreambuf_iterator<char>()
  );

  stringParse(fileText);

  file.close();
}

void DataManager::stringParse(std::string input) {
  std::istringstream iss(input);

  int itemsNum;
  iss >> maxCapacity >> populationSize >> itemsNum;

  if (iss.fail()) {
    throw std::runtime_error("Ошибка чтения основных параметров");
  }

  // Цены
  std::vector<double> prices(itemsNum);
  for (int i = 0; i < itemsNum; ++i) {
    if (!(iss >> prices[i])) {
      throw std::runtime_error("Ошибка чтения цен предметов");
    }
  }

  // Веса
  std::vector<double> weights(itemsNum);
  for (int i = 0; i < itemsNum; ++i) {
    if (!(iss >> weights[i])) {
      throw std::runtime_error("Ошибка чтения весов предметов");
    }
  }

  // Проверяем, что все данные считаны корректно
  if (!iss.eof()) {
    std::string remaining;
    std::getline(iss, remaining);
    if (!remaining.empty()) {
      std::cerr << "Предупреждение: лишние данные в конце строки: " << remaining << std::endl;
    }
  }

//  items.resize(itemsNum);
  for (int i = 0; i < itemsNum; ++i) {
    add(prices[i], weights[i]);
  }
}

std::vector<Item> DataManager::getItems() {
  return items;
}

float DataManager::getMaxCapacity() {
  return maxCapacity;
}

int DataManager::getPopulationSize() {
  return populationSize;
}

int DataManager::getItemsNum() {
  return items.size();
}