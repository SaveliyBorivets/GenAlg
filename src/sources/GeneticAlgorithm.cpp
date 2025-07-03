#include "../headers/GeneticAlgorithm.hpp"

// Конструктор
GeneticAlgorithm::GeneticAlgorithm(DataManager data) : Data(data), crossover(1, CrossoverType::Uniform), mutation(0.01, MutationType::ADD_REMOVE) {
    std::random_device rd;
    gen.seed(rd());
    selectionMethod = SelectionType::Tournament;
    generationCount = 0;
    // maxGenerations = 50;
    for (int i = 0; i < Data.getPopulationSize(); ++i) {
        Backpack randomBackpack(data);
        population.emplace_back(randomBackpack);
    }
}

// Отбор пары родителей
std::pair<Backpack, Backpack> GeneticAlgorithm::selectParents() {
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
        fitnesses.push_back(indiv.getFitnessValue(Data.getFitness(), Data));
    }
}

// Отбор турниром. Раунд для двоих
// Backpack GeneticAlgorithm::tournamentSelection() {
//     // Выбор случайных особей
//     std::uniform_int_distribution<int> dist(0, population.size() - 1);
//     int index1 = dist(gen);
//     int index2 = dist(gen);
//     while (index1 == index2) {
//         index2 = dist(gen);
//     }
//     Backpack a = population[index1];
//     Backpack b = population[index2];
//     if (a.getFitnessValue(Data.getFitness(), Data) > b.getFitnessValue(Data.getFitness(), Data)) {
//         return a;
//     }
//     return b;
// }

Backpack GeneticAlgorithm::tournamentSelection() {
    std::uniform_int_distribution<int> dist(0, population.size() - 1);
    size_t n = 4;
    // Выбираем n уникальных случайных индекса
    std::vector<int> indices;
    while (indices.size() < n) {
        int idx = dist(gen);
        if (std::find(indices.begin(), indices.end(), idx) == indices.end()) {
            indices.push_back(idx);
        }
    }
    // Находим особь с максимальной приспособленностью
    Backpack* best = &population[indices[0]];
    for (size_t i = 1; i < n; ++i) {
        if (population[indices[i]].getFitnessValue(Data.getFitness(), Data) > best->getFitnessValue(Data.getFitness(), Data)) {
            best = &population[indices[i]];
        }
    }
    return *best;
}

// Отбор рулеткой
Backpack GeneticAlgorithm::rouletteSelection() {
    // Общая приспособленность
    float totalFitness = 0;
    for (auto& b : population){
        totalFitness += b.getFitnessValue(Data.getFitness(), Data);
    } 
    // Взятие случайной длины
    std::uniform_real_distribution<float> dist(0, totalFitness);
    float pick = dist(gen);
    float current = 0;
    // Выбор особи
    for (auto& b : population) {
        current += b.getFitnessValue(Data.getFitness(), Data);
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
        sum += b.getFitnessValue(Data.getFitness(), Data);
    return sum / population.size();
}

// Получение лучшей приспособленности
float GeneticAlgorithm::BestFitness() {
    float best = 0;
    for (auto& b : population)
        best = std::max(best, b.getFitnessValue(Data.getFitness(), Data));
    return best;
}

// Передача текущей итерации
int GeneticAlgorithm::getGenCount() {
    return generationCount;
}

// Передача средней приспособленности
std::vector<float> GeneticAlgorithm::getAverageFitness() {
    return averageFitnessHistory;
}

// Передача лучшей приспособленности
std::vector<float> GeneticAlgorithm::getBestFitness() {
    return bestFitnessHistory;
}

//Алгоритм
void GeneticAlgorithm::runGeneration() {
    // Считаем приспособленность
    evaluateFitness();
    averageFitnessHistory.push_back(AverageFitness());
    bestFitnessHistory.push_back(BestFitness());

    // Новое поколение
    std::vector<Backpack> newPopulation;
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
    population = std::move(newPopulation); // Смена поколений
    std::cout << "Лучший: " << bestFitnessHistory.back() << " Средний: " << averageFitnessHistory.back() << std::endl;
    for (int i = 0; i < 15; ++i) {
        std::cout << population[i].getFitnessValue(Data.getFitness(), Data) << ' ';
    }
    std::cout << std::endl;
    generationCount++;
}

// Запуск алгоритма
void GeneticAlgorithm::run() {
    int count = 0;
    float previousFitness;
    runGeneration(); 
    while (count != 15) {
        previousFitness = bestFitnessHistory.back();
        runGeneration(); 
        if (previousFitness == bestFitnessHistory.back()) {
            count++;
        } else {
            count = 0;
        }
    }
    std::cout << "Прогресс среднего: " << averageFitnessHistory.back() - averageFitnessHistory[0]
        << " Прогрес лучшего: " << bestFitnessHistory.back() - bestFitnessHistory[0] << std::endl;
}

std::vector<float> GeneticAlgorithm::getAverageFitnessHistory() {
    return averageFitnessHistory;
}

std::vector<float> GeneticAlgorithm::getBestFitnessHistory() {
    return bestFitnessHistory;
}

void GeneticAlgorithm::setCrossoverType(CrossoverType t) {
  crossover.setType(t);
}

void GeneticAlgorithm::setMutationType(MutationType t) {
    mutation.setType(t);
}

void GeneticAlgorithm::setSelectionType(SelectionType t) {
    selectionMethod = t;
}