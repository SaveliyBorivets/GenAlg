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

void DataManager::randomLoad() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> capacityDist(50, 1000);
  maxCapacity = capacityDist(gen);
  std::uniform_int_distribution<> populationDist(50, 300);
  populationSize = populationDist(gen);
  std::uniform_int_distribution<> count(4, 15);
  int numItems = count(gen);

  std::uniform_real_distribution<> weightDist(1.0, 20.0);
  std::uniform_real_distribution<> priceDist(1.0, 50.0);
  float price, weight;
  for (int i = 0; i < numItems; ++i) {
    price = priceDist(gen);
    weight = weightDist(gen);
    add(price, weight);
  }
}

std::string DataManager::loadFile(std::string path) {
  if (path.empty()) return "Введите путь до txt файла";

  std::ifstream file(path);
  if (!file.is_open()) {
    return "Ошибка: Файл " + path + " не получилось открыть";
  }

  std::string fileText(
      (std::istreambuf_iterator<char>(file)),
      std::istreambuf_iterator<char>()
  );

  std::string parseStatus = stringParse(fileText);

  file.close();

  return parseStatus;
}

std::string DataManager::stringParse(std::string input) {
  if (input.empty()) return "Пустой файл/окно ввода";

  std::istringstream iss(input);

  int itemsNum;
  iss >> maxCapacity >> populationSize >> itemsNum;

  if (iss.fail()) {
    return "Ошибка: Основные параметры не прочитаны";
  }

  // Цены
  std::vector<double> prices(itemsNum);
  for (int i = 0; i < itemsNum; ++i) {
    if (!(iss >> prices[i])) {
      return "Ошибка: Некорректные цены";
    }
  }

  // Веса
  std::vector<double> weights(itemsNum);
  for (int i = 0; i < itemsNum; ++i) {
    if (!(iss >> weights[i])) {
      return "Ошибка: Некорректные веса";
    }
  }

  // Проверяем, что все данные считаны корректно
  if (!iss.eof()) {
    std::string remaining;
    std::getline(iss, remaining);
    if (!remaining.empty()) {
      return "Предупреждение: лишние данные в конце строки: " + remaining;
    }
  }

//  items.resize(itemsNum);
  for (int i = 0; i < itemsNum; ++i) {
    add(prices[i], weights[i]);
  }

  return "Данные успешно считаны";
}

void DataManager::setFitness(FitnessType fit) {
  fitness = fit;
}

FitnessType DataManager::getFitness() {
  return fitness;
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