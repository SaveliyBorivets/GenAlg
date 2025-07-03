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

    // Статус
    statusExperimentWindow = new QLabel("Статус: ");
    statusExperimentWindow->setFixedHeight(30);
    gridLayout->addWidget(statusExperimentWindow, 9, 0, 1, 5);
    statusExperimentWindow->setText("Статус: Выберите параметры, нажмите на кнопки итераций для отображения графиков");

    // 3. Создаем график и добавляем серию
    QChart *chart = new QChart();
    chart->createDefaultAxes();
    chart->setTitle("График по массивам данных");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(500);

    gridLayout->addWidget(chartView, 2, 0, 4, 4);

    // ======= АКТИВАЦИЯ КНОПОК ========
    // Переход к меню ввода
    connect(toInputMenuButton, &QPushButton::clicked, this, &ExperimentWindow::switchToInputMenu);

    // Коннект выпадающих меню
    connect(comboFitnessFunction, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ExperimentWindow::fitnessTypeSelected);

    connect(comboCrossover, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ExperimentWindow::crossoverTypeSelected);

    connect(comboMutation, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ExperimentWindow::mutationTypeSelected);

    connect(comboSelection, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ExperimentWindow::selectionTypeSelected);

    // Кнопки
    connect(nextStepButton, &QPushButton::clicked, this, &ExperimentWindow::runOneIteration);

    connect(toEndButton, &QPushButton::clicked, this, &ExperimentWindow::runToTheEnd);
}

void ExperimentWindow::chartViewUpdate(std::vector<float> bestFitness, std::vector<float> averageFitness)
{
    delete chart;
    chart = new QChart();
    chart->createDefaultAxes();
    chart->setTitle("График по массивам данных");

    delete chartView;
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(500);

    gridLayout->addWidget(chartView, 2, 0, 4, 4);

    // Проверка инициализации
    if (!chart || !chartView) {
        qCritical() << "Chart not initialized!";
        return;
    }

    // Проверка входных данных
    if (bestFitness.empty() || averageFitness.empty() || bestFitness.size() != averageFitness.size()) {
        qWarning() << "Invalid input data sizes";
        return;
    }

    // Подготовка данных
    QVector<double> xData;
    for (size_t i = 0; i < bestFitness.size(); i++) {
        xData.push_back(i);
    }

    // Создание серий
    QLineSeries *bestSeries = new QLineSeries();
    bestSeries->setName("Лучшая приспособленность");

    QLineSeries *avgSeries = new QLineSeries();
    avgSeries->setName("Средняя приспособленность");

    // Заполнение данными
    for (int i = 0; i < xData.size(); ++i) {
        bestSeries->append(xData[i], bestFitness[i]);
        avgSeries->append(xData[i], averageFitness[i]);
    }

    // Очистка предыдущих данных
    chart->removeAllSeries();

    // Добавление серий
    chart->addSeries(bestSeries);
    chart->addSeries(avgSeries);

    // Настройка осей (если они еще не созданы)
    if (!chart->axisX()) {
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("Поколение");
        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Приспособленность");
        chart->addAxis(axisY, Qt::AlignLeft);
    }

    // Привязка серий к осям
    bestSeries->attachAxis(chart->axisX());
    bestSeries->attachAxis(chart->axisY());
    avgSeries->attachAxis(chart->axisX());
    avgSeries->attachAxis(chart->axisY());

    // Автомасштабирование
    chart->axisX()->setRange(0, xData.size()-1);

    double minY = qMin(*std::min_element(bestFitness.begin(), bestFitness.end()),
           *std::min_element(averageFitness.begin(), averageFitness.end()));
    double maxY = qMax(*std::max_element(bestFitness.begin(), bestFitness.end()),
           *std::max_element(averageFitness.begin(), averageFitness.end()));

    chart->axisY()->setRange(minY * 0.95, maxY * 1.05);

    // Обновление отображения
    chartView->repaint();
}

void ExperimentWindow::labelsUpdate(float bestFitness, std::vector<float> currentBestFitness, std::vector<float> currentAverageFitness) {
    labelBestSolution->setText(QString::fromStdString("Наилучшее решение за эксперимент: " + std::to_string(bestFitness)));

    float best = 0, average = 0;
    if (!currentBestFitness.empty()) {
        best = currentBestFitness[currentBestFitness.size() - 1];
    }
    if (!currentAverageFitness.empty()) {
        average = currentAverageFitness[currentAverageFitness.size() - 1];
    }
    labelBestSolutionCost->setText(QString::fromStdString("Лучшее решение в текущей популяции: " + std::to_string(best)));
    labelAverageCost->setText(QString::fromStdString("Среднее текущей популяции: " + std::to_string(average)));
    statusExperimentWindow->setText(QString::fromStdString("Статус: Результаты обновлены"));
}

void ExperimentWindow::statusUpdate(std::string newStatus) {
    statusExperimentWindow->setText(QString::fromStdString("Статус: " + newStatus));
}