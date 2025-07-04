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
//    gridLayout->setContentsMargins(15, 15, 15, 15);  // Отступы от краев

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
    printPopulationButton = new QPushButton("Дополнительная информация");
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
    statusExperimentWindow = new QLabel("Статус: Выберите параметры, нажмите на кнопки итераций для отображения графиков");
    statusExperimentWindow->setFixedHeight(30);
    gridLayout->addWidget(statusExperimentWindow, 9, 0, 1, 5);

    informationText = new QTextEdit(this);
    informationText->setText("Необходимо ввести данные");
    gridLayout->addWidget(informationText, 10, 0, 1, 5);

//    std::vector<float> prices = {0f, 22.3f, 18.0f, 9.9f};
//    std::vector<float> weights = {1.1f, 2.4f, 1.7f, 0.8f};
//    std::vector<int> best_solution = {1, 0, 1, 0};
//    std::vector<int> current_best = {1, 0, 0, 1};

    table = new QTableWidget(this);
//    createTable(prices, weights, best_solution, current_best);
    gridLayout->addWidget(table, 11, 0, 1, 5);

    // График
    chart = new QChart();
    chartView = new QChartView(chart);
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
//    connect(printPopulationButton, &QPushButton::clicked, this, &ExperimentWindow::displayInformation);

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

void ExperimentWindow::createTable(std::vector<Item> items,
                                 Backpack best_solution,
                                 std::vector<Backpack> bestSolutions) {
    // Подготовка данных
    std::vector<float> prices, weights;
    for (const auto& item : items) {
        prices.push_back(item.price);
        weights.push_back(item.weight);
    }

    const size_t n = prices.size();
    if (n == 0 || weights.size() != n) {
        qWarning("Векторы items не должны быть пустыми!");
        return;
    }

    // Очищаем таблицу
    table->clear();

    // Устанавливаем размеры (4 строки + строки для решений, n столбцов)
    int row_count = 4 + static_cast<int>(bestSolutions.size());
    table->setRowCount(row_count);
    table->setColumnCount(static_cast<int>(n));

    // Устанавливаем заголовки строк
    QStringList row_labels;
    row_labels << "Цены" << "Веса" << "Наилучшее решение" << "Текущее лучшее";

    // Добавляем заголовки для каждого решения
    for (size_t i = 0; i < bestSolutions.size(); ++i) {
        row_labels << QString("Лучшее в %1").arg(i+1);
    }
    table->setVerticalHeaderLabels(row_labels);

    // Получаем наилучшее решение
    std::vector<int> best_solution_vec = best_solution.getSolution();

    // Заполняем основные данные
    for (size_t col = 0; col < n; ++col) {
        // Цены
        QTableWidgetItem* price_item = new QTableWidgetItem(QString::number(prices[col]));
        table->setItem(0, static_cast<int>(col), price_item);

        // Веса
        QTableWidgetItem* weight_item = new QTableWidgetItem(QString::number(weights[col]));
        table->setItem(1, static_cast<int>(col), weight_item);

        // Наилучшее решение (всегда зеленое)
        QTableWidgetItem* best_item = new QTableWidgetItem(QString::number(best_solution_vec[col]));
        best_item->setBackground(Qt::green);
        table->setItem(2, static_cast<int>(col), best_item);
    }

    // Заполняем решения и сравниваем с наилучшим
    for (size_t row = 0; row < bestSolutions.size(); ++row) {
        std::vector<int> current_solution = bestSolutions[row].getSolution();

        for (size_t col = 0; col < n; ++col) {
            QTableWidgetItem* solution_item = new QTableWidgetItem(
                QString::number(current_solution[col]));

            // Сравниваем с наилучшим решением
            bool is_best = (current_solution[col] == best_solution_vec[col]);
            solution_item->setBackground(is_best ? Qt::green : Qt::white);

            table->setItem(static_cast<int>(row + 3), static_cast<int>(col), solution_item);
        }
    }

    table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);  // Плавная прокрутка
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);  // Фиксируем высоту строк

    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Настройка отображения
    table->resizeColumnsToContents();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ExperimentWindow::statusUpdate(std::string newStatus) {
    statusExperimentWindow->setText(QString::fromStdString("Статус: " + newStatus));
}

#include <iostream>

void ExperimentWindow::displayInfo(std::string dataManagerInfo, std::string genAlgInfo, std::string populationInfo) {
    informationText->setText(QString::fromStdString("Данные задачи\n" + dataManagerInfo + "\nТекущие настройки\n" + genAlgInfo + "\nПопуляция\n" + populationInfo));
}