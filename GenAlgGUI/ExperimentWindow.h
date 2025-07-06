#ifndef EXPERIMENTWINDOW_H
#define EXPERIMENTWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QChartView>
#include <QTextEdit>
#include <QDoubleSpinBox>

// Для таблицы
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QColor>
#include "../src/headers/Item.hpp"
#include "../src/headers/Backpack.hpp"

class ExperimentWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ExperimentWindow(QWidget *parent = nullptr);
    void chartViewUpdate(std::vector<float> bestFitness, std::vector<float> averageFitness);
    void labelsUpdate(float BestFitness, std::vector<float> currentBestFitness, std::vector<float> currentAverageFitness);
    void statusUpdate(std::string newStatus);
    void displayInfo(std::string dataManagerInfo, std::string genAlgInfo, std::string populationInfo);
    void createTable(std::vector<Item> items, Backpack best_solution, std::vector<Backpack> bestSolutions); // Визуализация решения
    std::pair<float, float> getProbs();

signals:
    void switchToInputMenu();
    void fitnessTypeSelected(int index);
    void crossoverTypeSelected(int index);
    void mutationTypeSelected(int index);
    void selectionTypeSelected(int index);
    void runOneIteration();
    void runToTheEnd();
    void updateProbs();

private:
    void setupUI();

    QGridLayout* gridLayout;

    // Выпадающее меню выбора
    QComboBox* comboFitnessFunction;
    QComboBox* comboSelection;
    QComboBox* comboCrossover;
    QComboBox* comboMutation;

    QDoubleSpinBox* mutationSpinBox;
    QDoubleSpinBox* crossoverSpinBox;

    // Кнопки
    QPushButton* probsButton;
    QPushButton* nextStepButton;
    QPushButton* toEndButton;
    QPushButton* toInputMenuButton;

    // Информационные метки
    QLabel* labelBestSolution;
    QLabel* labelBestSolutionCost;
    QLabel* labelAverageCost;
    QLabel* statusExperimentWindow;
    QTextEdit* informationText;

    // График
    QChart* chart;
    QChartView* chartView;

    QTableWidget* table;
};

#endif // EXPERIMENTWINDOW_H
