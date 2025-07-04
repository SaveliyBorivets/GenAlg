#include "../headers/GeneticAlgorithm.hpp"

// Конструктор
GeneticAlgorithm::GeneticAlgorithm(DataManager data) : Data(data), crossover(1, CrossoverType::Uniform), mutation(0.01, MutationType::ADD_REMOVE) {
    std::random_device rd;
    gen.seed(rd());
    selectionMethod = SelectionType::Tournament;
    generationCount = 0;
    bestCostOfAllTime = 0;
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
Backpack GeneticAlgorithm::BestFitness() {
    Backpack best(std::vector<int>(Data.getItems().size(), 0));
    float fit = 0;
    for (auto& b : population)
        if (best.getFitnessValue(Data.getFitness(), Data) < b.getFitnessValue(Data.getFitness(), Data)) {
            best = b;
        }
    if (best.getFitnessValue(Data.getFitness(), Data) > bestCostOfAllTime) {
      bestCostOfAllTime = best.getFitnessValue(Data.getFitness(), Data);
      bestOfAllIndivids = best;
    }
    return best;
}

Backpack GeneticAlgorithm::rewriteSolution(Backpack backpack){
    float weight = 0;
    for (int i = 0; i < Data.getItems().size(); ++i) {
        if (weight + Data.getItems()[i].weight * backpack.getSolution()[i] > Data.getMaxCapacity()) {
            backpack.editSolution(i, 0);
        } else {
            weight += Data.getItems()[i].weight * backpack.getSolution()[i];
        }
    }
    return backpack;
}

Backpack GeneticAlgorithm::getBestOfAllIndivids() {
    float weight = 0;
    if (Data.getFitness() == FitnessType::Gentle) {
        bestOfAllIndivids = rewriteSolution(bestOfAllIndivids);
    }
    return bestOfAllIndivids;
}

std::vector<Backpack> GeneticAlgorithm::getBestIndivids() {

}

std::string GeneticAlgorithm::getCurrentPopulation() {
    std::string info;
    int n = population.size(), m = Data.getItems().size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            info += std::to_string(population[i].getSolution()[j]) + ' ';
        }
        info += '\n';
    }
    return info;
}


std::string GeneticAlgorithm::getInfo() {
    std::string info;
    switch (crossover.getType())
    {
    case CrossoverType::OnePoint:
        info += "OnePoint\n";
        break;
    case CrossoverType::TwoPoint:
        info += "TwoPoint\n";
        break;
    case CrossoverType::Uniform:
        info += "Uniform\n";
        break;
    default:
        break;
    }
    switch (mutation.getType())
    {
    case MutationType::CHANGE:
        info += "Change\n";
        break;
    case MutationType::ADD_REMOVE:
        info += "Add_remove\n";
        break;
    default:
        break;
    }
    switch (selectionMethod)
    {
    case SelectionType::Tournament:
        info += "Tournament\n";
        break;
    case SelectionType::Roulette:
        info += "Roulette\n";
        break;
    default:
        break;
    }
    return info;
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

float GeneticAlgorithm::getBestCostOfAllTime() {
    return bestCostOfAllTime;
}

//Алгоритм
void GeneticAlgorithm::runGeneration() {
    // Считаем приспособленность
    evaluateFitness();
    averageFitnessHistory.push_back(AverageFitness());
    Backpack best = BestFitness();
    bestFitnessHistory.push_back(best.getFitnessValue(Data.getFitness(), Data));
    bestIndivids.push_back(best);

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
    while (count != 50) {
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

void GeneticAlgorithm::restart(DataManager data) {
    fitnesses.clear();
    averageFitnessHistory.clear();
    bestFitnessHistory.clear();
    generationCount = 0;
    for (int i = 0; i < Data.getPopulationSize(); ++i) {
        Backpack randomBackpack(data);
        population.emplace_back(randomBackpack);
    }
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