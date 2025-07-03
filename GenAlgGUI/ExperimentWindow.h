#ifndef EXPERIMENTWINDOW_H
#define EXPERIMENTWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QChartView>

class ExperimentWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ExperimentWindow(QWidget *parent = nullptr);
    void chartViewUpdate(std::vector<float> bestFitness, std::vector<float> averageFitness);
    void labelsUpdate(float BestFitness, std::vector<float> currentBestFitness, std::vector<float> currentAverageFitness);
    void statusUpdate(std::string newStatus);

signals:
    void switchToInputMenu();
    void fitnessTypeSelected(int index);
    void crossoverTypeSelected(int index);
    void mutationTypeSelected(int index);
    void selectionTypeSelected(int index);
    void runOneIteration();
    void runToTheEnd();

private:
    void setupUI();

    QGridLayout* gridLayout;

    // Выпадающее меню выбора
    QComboBox* comboFitnessFunction;
    QComboBox* comboSelection;
    QComboBox* comboCrossover;
    QComboBox* comboMutation;

    // Кнопки
    QPushButton* printPopulationButton;
    QPushButton* nextStepButton;
    QPushButton* toEndButton;
    QPushButton* toInputMenuButton;

    // Информационные метки
    QLabel* labelBestSolution;
    QLabel* labelBestSolutionCost;
    QLabel* labelAverageCost;
    QLabel* statusExperimentWindow;

    // График
    QChart* chart;
    QChartView* chartView;
};

#endif // EXPERIMENTWINDOW_H
