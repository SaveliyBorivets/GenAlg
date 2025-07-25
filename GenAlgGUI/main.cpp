#include <QApplication>
#include <QStackedWidget>
#include <iostream>

#include "InputMenu.h"
#include "ExperimentWindow.h"

#include "../src/headers/DataManager.hpp"
#include "../src/headers/GeneticAlgorithm.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Цвет фона у всего приложения
    app.setStyleSheet("QWidget { background-color: #c8e1f9; }");

    // Объявления стека виджетов
    QStackedWidget* switcher = new QStackedWidget;
    switcher->setWindowTitle("GenAlg GUI");
    switcher->setMinimumHeight(1000);
    switcher->setMinimumWidth(1340);

    // Добавление меню ввода
    InputMenu* inputMenu = new InputMenu;
    switcher->addWidget(inputMenu);

    // Добавление окна эксперимента
    ExperimentWindow* experimentWindow = new ExperimentWindow();
    switcher->addWidget(experimentWindow);

    // Обработка сигналов c кнопок
    QObject::connect(inputMenu, &InputMenu::switchToExperiment, [switcher]() {
        switcher->setCurrentIndex(1);
    });
    QObject::connect(experimentWindow, &ExperimentWindow::switchToInputMenu, [switcher]() {
        switcher->setCurrentIndex(0);
    });

    switcher->show();

    // ======= РАБОТА С АЛГОРИТМОМ =======
    // === МЕНЮ ВВОДА ===
    DataManager* dataManager = new DataManager;
    GeneticAlgorithm* geneticAlgorithm = new GeneticAlgorithm(*dataManager);

    QObject::connect(inputMenu, &InputMenu::getDataFromTxt, [&]() mutable {
        delete dataManager;
        dataManager = new DataManager;
        QString qPath = inputMenu->getPath();
        std::string path = qPath.toStdString();
        std::string readStatus = dataManager->loadFile(path);
        inputMenu->setStatus(readStatus);
        if (readStatus == "Данные успешно считаны") {
        	inputMenu->displayInfo(dataManager->getInfo());
            geneticAlgorithm->restart(*dataManager);
            experimentWindow->chartViewUpdate(geneticAlgorithm->getBestFitness(), geneticAlgorithm->getAverageFitness());
           	experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
        	experimentWindow->createTable(dataManager->getItems(), geneticAlgorithm->getBestOfAllIndivids(), geneticAlgorithm->getBestIndivids());
            inputMenu->enableExperiment(true);
        } else {
          	inputMenu->displayInfo(readStatus);
            inputMenu->enableExperiment(false);
        }
    });

    QObject::connect(inputMenu, &InputMenu::getDataFromGui, [&]() mutable {
        delete dataManager;
        dataManager = new DataManager;
        QString qGuiData = inputMenu->getGuiText();
        std::string guiData = qGuiData.toStdString();
        std::string readStatus = dataManager->stringParse(guiData);
        inputMenu->setStatus(readStatus);
        if (readStatus == "Данные успешно считаны") {
        	inputMenu->displayInfo(dataManager->getInfo());
            geneticAlgorithm->restart(*dataManager);
            experimentWindow->chartViewUpdate(geneticAlgorithm->getBestFitness(), geneticAlgorithm->getAverageFitness());
           	experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
        	experimentWindow->createTable(dataManager->getItems(), geneticAlgorithm->getBestOfAllIndivids(), geneticAlgorithm->getBestIndivids());
            inputMenu->enableExperiment(true);
        } else {
          	inputMenu->displayInfo(readStatus);
            inputMenu->enableExperiment(false);
        }
    });

    QObject::connect(inputMenu, &InputMenu::generateRandomDataManager, [&]() mutable {
        delete dataManager;
        dataManager = new DataManager;
        dataManager->randomLoad();
        inputMenu->setStatus("Случайные данные сгенерированы");
        inputMenu->displayInfo(dataManager->getInfo());
        geneticAlgorithm->restart(*dataManager);
        experimentWindow->chartViewUpdate(geneticAlgorithm->getBestFitness(), geneticAlgorithm->getAverageFitness());
        experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
        experimentWindow->createTable(dataManager->getItems(), geneticAlgorithm->getBestOfAllIndivids(), geneticAlgorithm->getBestIndivids());
        inputMenu->enableExperiment(true);
    });

    // === ОКНО ЭКСПЕРИМЕНТА ===

    QObject::connect(experimentWindow, &ExperimentWindow::fitnessTypeSelected,
        [&](int index) {
            switch(index) {
                case 0: dataManager->setFitness(FitnessType::Cutting); break;
                case 1: dataManager->setFitness(FitnessType::Gentle); break;
            }
            experimentWindow->statusUpdate("Смена функции пригодности");
            experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
    });


    QObject::connect(experimentWindow, &ExperimentWindow::crossoverTypeSelected,
            [&](int index) {
                switch(index) {
                    case 0: geneticAlgorithm->setCrossoverType(CrossoverType::OnePoint); break;
                    case 1: geneticAlgorithm->setCrossoverType(CrossoverType::TwoPoint); break;
                    case 2: geneticAlgorithm->setCrossoverType(CrossoverType::Uniform); break;
                }
                experimentWindow->statusUpdate("Смена скрещивания");
                experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
    });

    QObject::connect(experimentWindow, &ExperimentWindow::mutationTypeSelected,
        [&](int index) {
            switch(index) {
                case 0: geneticAlgorithm->setMutationType(MutationType::ADD_REMOVE); break;
                case 1: geneticAlgorithm->setMutationType(MutationType::CHANGE); break;
            }
            experimentWindow->statusUpdate("Смена мутации");
            experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
    });

    QObject::connect(experimentWindow, &ExperimentWindow::selectionTypeSelected,
        [&](int index) {
            switch(index) {
                case 0: geneticAlgorithm->setSelectionType(SelectionType::Tournament); break;
                case 1: geneticAlgorithm->setSelectionType(SelectionType::Roulette); break;
            }
            experimentWindow->statusUpdate("Смена метода отбора");
            experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
    });

    QObject::connect(experimentWindow, &ExperimentWindow::updateProbs, [&]() {
        std::pair<float, float> probs = experimentWindow->getProbs();
        experimentWindow->statusUpdate("Обновление вероятностей");
        geneticAlgorithm->setProbabilities(probs.first, probs.second);
        experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
    });

    // Кнопки
    QObject::connect(experimentWindow, &ExperimentWindow::runOneIteration, [&]() {
        geneticAlgorithm->runGeneration();
        experimentWindow->chartViewUpdate(geneticAlgorithm->getBestFitness(), geneticAlgorithm->getAverageFitness());
        experimentWindow->labelsUpdate(geneticAlgorithm->getBestCostOfAllTime(), geneticAlgorithm->getBestFitness(), geneticAlgorithm->getAverageFitness());
        experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
        experimentWindow->createTable(dataManager->getItems(), geneticAlgorithm->getBestOfAllIndivids(), geneticAlgorithm->getBestIndivids());
    });

    // Запуск алгоритма
    QObject::connect(experimentWindow, &ExperimentWindow::runToTheEnd, [&]() {
        geneticAlgorithm->run();
        experimentWindow->chartViewUpdate(geneticAlgorithm->getBestFitness(), geneticAlgorithm->getAverageFitness());
        experimentWindow->labelsUpdate(geneticAlgorithm->getBestCostOfAllTime(), geneticAlgorithm->getBestFitness(), geneticAlgorithm->getAverageFitness());
        experimentWindow->displayInfo(dataManager->getInfo(), geneticAlgorithm->getInfo(), geneticAlgorithm->getCurrentPopulation());
        experimentWindow->createTable(dataManager->getItems(), geneticAlgorithm->getBestOfAllIndivids(), geneticAlgorithm->getBestIndivids());
    });

    return app.exec();
}
