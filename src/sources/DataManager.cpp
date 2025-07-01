#include "../headers/DataManager.hpp"

#include <fstream>
#include <sstream>
#include <random>
#include <iostream>

int DataManager::binaryPosition(float weight){
  int left = 0;
  int right = itemsNum;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (items[mid].weight < weight) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

void DataManager::add(std::string name, float weight, float price) {
  if (weight <= 0) {
    return;
  }
  Item something;
  something.name = name;
  something.weight = weight;
  something.price = price;
  something.unitPrice = price / weight;
  int pos = binaryPosition(weight);
  items.insert(items.begin() + pos, something);
  itemsNum++;
}

int DataManager::randomTake(float upBoard) {
  std::random_device rd;
  std::mt19937 gen(rd());
  int pos = binaryPosition(upBoard);
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
  std::string line;
  float price, weight;
  std::string name;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    if (iss >> name >> price >> weight) {
      add(name, price, weight); 
    } else {
      std::cerr << "Некорректная строка: " << line << std::endl;
    }
  }
  file.close();
}

std::vector<Item> DataManager::getItems() {
  return items;
}

float DataManager::getMaxWeight() {
  return maxWeight;
}