#pragma once
#include "item.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
using namespace std;

class SortedSubjectsArray {
    vector<Item> threads; // Набор вещей
    
public:

     // Добавляет новую вещь и сортирует набор по возрастанию
    void add(float cost, float weight) {
        Item something; // Новая вещь
        something.weight = weight; // Назначение веса
        something.value = cost; // Назначение цены
        something.unitPrice = cost / weight;  // Отношение цены к весу

        int pos = binaryPosition(threads, something->weight) // Нахождение нужной позиции длля вставки

        threads.insert(pos, something); // Вставка новой вещи в нужную позицию
    }


    // Взятие рандомной вещи, весом <= заданного, из набора
    Item randomTake(float upBoard) {
        random_device rd;
        mt19937 gen(rd());
        vector<Item> candidates; // Кандидаты на взятие

        // Отбор кандидатов
        for (const auto& item : threads) {
            if (item.weight <= upBoard) {
                candidates.push_back(item);
            }
        }

        // Если кандидатов не оказалось, берём случайный предмет
        if (candidates.empty()) {
            uniform_int_distribution<> dist(0, threads.size() - 1);
            return threads[dist(gen)];
        }

        uniform_int_distribution<> dist(0, candidates.size() - 1); // Выбор случайной вещи нужного веса

        return candidates[dist(gen)];
    }

    // Загрузка данных из файла
    void loadFromFile(string& path) {
        ifstream file(path);

        // Если файл не открылся
        if (!file.is_open()) {
            throw runtime_error("Ошибка открытия файла: " + path);
        }

        string line;

        // Построчная перепись информации из файла в массив
        while (getline(file, line)) {
            istringstream iss(line);
            float cost, weight;

            if (iss >> cost >> weight) {
                add(cost, weight); // Добавляем с сортировкой
            } else {
                cerr << "Некорректная строка: " << line << endl;
            }
        }

        file.close();
    }

    // Взятие набора вещей
    const vector<Item>& getThreads() {
        return threads;
    }

    // Бинарный поиск нужной позиции для вставки нового элемента
    int binaryPosition(const vector<Item>& getThreads, float weight) {
        int left = 0;
        int right = getThreads.size();

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (getThreads[mid].weight < weight) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left; // Позиция вставки
    }

};