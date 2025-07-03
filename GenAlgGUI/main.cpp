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

    // Добавление меню ввода
    InputMenu* inputMenu = new InputMenu;
    switcher->addWidget(inputMenu);

    // Добавление окна эксперимента
    ExperimentWindow* experimentWindow = new ExperimentWindow;
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
        QString qPath = inputMenu->getPath();
        std::string path = qPath.toStdString();
        inputMenu->setStatus(dataManager->loadFile(path));
        geneticAlgorithm = new GeneticAlgorithm(*dataManager);
    });

    QObject::connect(inputMenu, &InputMenu::getDataFromGui, [&]() mutable {
        QString qGuiData = inputMenu->getGuiText();
        std::string guiData = qGuiData.toStdString();
        inputMenu->setStatus(dataManager->stringParse(guiData));
        geneticAlgorithm = new GeneticAlgorithm(*dataManager);
    });

    // === ОКНО ЭКСПЕРИМЕНТА ===

    QObject::connect(experimentWindow, &ExperimentWindow::crossoverTypeSelected,
            [&](int index) {
                switch(index) {
                    case 0: geneticAlgorithm->setCrossoverType(CrossoverType::OnePoint); break;
                    case 1: geneticAlgorithm->setCrossoverType(CrossoverType::TwoPoint); break;
                    case 2: geneticAlgorithm->setCrossoverType(CrossoverType::Uniform); break;
                }
    });

    QObject::connect(experimentWindow, &ExperimentWindow::mutationTypeSelected,
        [&](int index) {
            switch(index) {
                case 0: geneticAlgorithm->setMutationType(MutationType::ADD_REMOVE); break;
                case 1: geneticAlgorithm->setMutationType(MutationType::CHANGE); break;
            }
    });

    QObject::connect(experimentWindow, &ExperimentWindow::selectionTypeSelected,
        [&](int index) {
            switch(index) {
                case 0: geneticAlgorithm->setSelectionType(SelectionType::Tournament); break;
                case 1: geneticAlgorithm->setSelectionType(SelectionType::Roulette); break;
            }
    });

    // Кнопки
    QObject::connect(experimentWindow, &ExperimentWindow::runOneIteration, [&]() {
        geneticAlgorithm->runGeneration();
    });

    // Запуск алгоритма
    QObject::connect(experimentWindow, &ExperimentWindow::runToTheEnd, [&]() {
        geneticAlgorithm->run();
    });

    return app.exec();
}
