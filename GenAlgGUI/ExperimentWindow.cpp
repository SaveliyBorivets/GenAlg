#include "ExperimentWindow.h"
#include <QtCharts>

ExperimentWindow::ExperimentWindow(QWidget *parent) : QWidget(parent) {
    // ===== ОКНО ЭКСПЕРИМЕНТА =====
    setStyleSheet("background-color: #c8e1f9;");
    setupUI();
}

void ExperimentWindow::setupUI() {
    // Макет-сетка
    gridLayout = new QGridLayout(this);

    // Настройка отступов и интервалов
    gridLayout->setSpacing(0);  // Расстояние между ячейками
    gridLayout->setContentsMargins(15, 15, 15, 15);  // Отступы от краев

    // Функция пригодности
    QLabel* labelFitnessFunction = new QLabel(QString("Функция пригодности"));
    labelFitnessFunction->setFixedSize(200, 70);
    comboFitnessFunction = new QComboBox();
    comboFitnessFunction->addItems({"Бракующая", "Пока можно положить"});
    gridLayout->addWidget(labelFitnessFunction, 0, 0);
    gridLayout->addWidget(comboFitnessFunction, 1, 0);

    // Отбор
    QLabel* labelSelection = new QLabel(QString("Метод отбора"));
    labelSelection->setFixedSize(200, 70);
    comboSelection = new QComboBox();
    comboSelection->addItems({"Турнирный метод", "Рулетка"});
    gridLayout->addWidget(labelSelection, 0, 1);
    gridLayout->addWidget(comboSelection, 1, 1);

    // Скрещивание
    QLabel* labelCrossover = new QLabel(QString("Метод скрещивания"));
    labelCrossover->setFixedSize(200, 70);
    comboCrossover = new QComboBox();
    comboCrossover->addItems({"Одноточечное скрещивание", "Двухточечное скрещивание", "Равномерное скрещивание"});
    gridLayout->addWidget(labelCrossover, 0, 2);
    gridLayout->addWidget(comboCrossover, 1, 2);

    // Мутации
    QLabel* labelMutation = new QLabel(QString("Мутация"));
    labelMutation->setFixedSize(200, 70);
    comboMutation = new QComboBox();
    comboMutation->addItems({"Случайное удаление/добавление", "Обмен предметов"});
    gridLayout->addWidget(labelMutation, 0, 3);
    gridLayout->addWidget(comboMutation, 1, 3);

    // === Кнопки ===
    // Вывод популяции
    printPopulationButton = new QPushButton("Популяция в txt-файл");
    printPopulationButton->setFixedSize(200, 70);
    gridLayout->addWidget(printPopulationButton, 2, 4);

    // Следующая итерация
    nextStepButton = new QPushButton("Следующий шаг");
    nextStepButton->setFixedSize(200, 70);
    gridLayout->addWidget(nextStepButton, 3, 4);

    // До конца
    toEndButton = new QPushButton("Выполнить до конца");
    toEndButton->setFixedSize(200, 70);
    gridLayout->addWidget(toEndButton, 4, 4);

    // Переход на меню ввода
    toInputMenuButton = new QPushButton("Обновить исходные данные");
    toInputMenuButton->setFixedSize(200, 70);
    gridLayout->addWidget(toInputMenuButton, 5, 4);

    // Информация о лучшем решении
    labelBestSolution = new QLabel(QString("Наилучшее решение: "));
    labelBestSolution->setFixedHeight(30);
    gridLayout->addWidget(labelBestSolution, 6, 0, 1, 5);

    // Информация о стоимости лучшего решения
    labelBestSolutionCost = new QLabel(QString("Стоимость лучшего решения: "));
    labelBestSolutionCost->setFixedHeight(30);
    gridLayout->addWidget(labelBestSolutionCost, 7, 0, 1, 5);

    // Информация о средней цене
    labelAverageCost = new QLabel(QString("Средняя стоимость: "));
    labelAverageCost->setFixedHeight(30);
    gridLayout->addWidget(labelAverageCost, 8, 0, 1, 5);

    // Пример графика
    QVector<double> xData = {1, 2, 3, 4, 5};    // Ось X
    QVector<double> yData = {2, 4, 1, 6, 3};    // Ось Y

    // 2. Создаем серию данных
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < xData.size(); ++i) {
        series->append(xData[i], yData[i]);
    }

    // 3. Создаем график и добавляем серию
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("График по массивам данных");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(500);

    gridLayout->addWidget(chartView, 2, 0, 4, 4);

    connect(toInputMenuButton, &QPushButton::clicked, this, &ExperimentWindow::switchToInputMenu);
}
