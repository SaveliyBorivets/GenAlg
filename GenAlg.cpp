#include "GenAlg.hpp"
using namespace std;

// Конструктор
GeneticAlgorithm::GeneticAlgorithm(int popSize, int maxGen, Crossover cros, Mutations mut, SelectionType selType, DataManager data)
    : crossover(cros), mutation(mut), maxGenerations(maxGen), selectionMethod(selType), Data(data){
    
    random_device rd;
    gen.seed(rd());

    for (int i = 0; i < popSize; ++i) {
        population.emplace_back(data);
    }
}

// Отбор пары родителей
pair<Backpack, Backpack> GeneticAlgorithm::selectParents() {
    if (selectionMethod == SelectionType::Tournament) {
        return {tournamentSelection(), tournamentSelection()}; // Методом турнира
    } else {
        return {rouletteSelection(), rouletteSelection()}; // Методом рулетки
    }
}

// Вычисление пригодностей
void GeneticAlgorithm::evaluateFitness() {
    fitnesses.clear();
    for (auto& indiv : population) {
        fitnesses.push_back(indiv.getValueV1(Data));
    }
}

// Отбор турниром
Backpack GeneticAlgorithm::tournamentSelection() {
    // Выбор случайных особей
    uniform_int_distribution<int> dist(0, population.size() - 1);
    int index1 = dist(gen);
    int index2 = dist(gen);
    while (index1 == index2) {
        index2 = dist(gen);
    }
    Backpack a = population[index1];
    Backpack b = population[index2];

    // Схватка
    if (a.getValueV1(Data) > b.getValueV1(Data)) {
        return a;
    }
    return b;
}

// Отбор рулеткой
Backpack GeneticAlgorithm::rouletteSelection() {
    // Общая приспособленность
    float totalFitness = 0;
    for (auto& b : population){
        totalFitness += b.getValueV1(Data);
    } 
    // Взятие случайной длины
    uniform_real_distribution<float> dist(0, totalFitness);
    float pick = dist(gen);
    float current = 0;
    // Выбор особи
    for (auto& b : population) {
        current += b.getValueV1(Data);
        if (current >= pick){
            return b;
        }
    }
    return population.back(); // Если особь не была выбрана
}

// Получение средней приспособленности
float GeneticAlgorithm::AverageFitness() {
    float sum = 0;
    for (auto& b : population)
        sum += b.getValueV1(Data);
    return sum / population.size();
}

// Получение лучшей приспособленности
float GeneticAlgorithm::BestFitness() {
    float best = 0;
    for (auto& b : population)
        best = max(best, b.getValueV1(Data));
    return best;
}

// Передача текущей итерации
int GeneticAlgorithm::get_genCount() {
    return generationCount;
}

// Передача средней приспособленности
vector<float> GeneticAlgorithm::get_averageFitness() {
    return averageFitnessHistory;
}

// Передача лучшей приспособленности
vector<float> GeneticAlgorithm::get_bestFitness() {
    return bestFitnessHistory;
}

//Алгоритм
void GeneticAlgorithm::runGeneration() {
    // Считаем приспособленность
    evaluateFitness();
    averageFitnessHistory.push_back(AverageFitness());
    bestFitnessHistory.push_back(BestFitness());
    
    // Новое поколение
    vector<Backpack> newPopulation;
    while (newPopulation.size() < population.size()) {
        // Выбор родителей и их скрещивание
        auto [p1, p2] = selectParents();
        auto [c1, c2] = crossover.cross(p1, p2);
        // Получение мутаций
        mutation.getMutation(c1);
        mutation.getMutation(c2);
        // Добавление детей в новое поколение
        newPopulation.push_back(c1);
        if (newPopulation.size() < population.size()){
            newPopulation.push_back(c2);
        }
            
    }
    population = move(newPopulation); // Смена поколений
    generationCount++;
}

// Запуск алгоритма
void GeneticAlgorithm::run() {
    while (generationCount < maxGenerations) {
        runGeneration();
    }
}
