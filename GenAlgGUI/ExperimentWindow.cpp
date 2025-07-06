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

    // Вероятности
    crossoverSpinBox = new QDoubleSpinBox();
    crossoverSpinBox->setRange(0.0, 1.0);   // Диапазон значений
    crossoverSpinBox->setDecimals(2);       // 2 знака после запятой
    crossoverSpinBox->setPrefix("Вероятность скрещивания: ");
    crossoverSpinBox->setValue(0.7);        // Значение по умолчанию
    crossoverSpinBox->setFixedWidth(250);

    gridLayout->addWidget(crossoverSpinBox, 0, 4);

	mutationSpinBox = new QDoubleSpinBox();
    mutationSpinBox->setRange(0.0, 1.0);   // Диапазон значений
    mutationSpinBox->setDecimals(2);       // 2 знака после запятой
    mutationSpinBox->setPrefix("Вероятность мутации: ");
    mutationSpinBox->setValue(0.01);        // Значение по умолчанию
    mutationSpinBox->setFixedWidth(250);

    gridLayout->addWidget(mutationSpinBox, 1, 4);

    // === Кнопки ===
    // Вывод популяции
    probsButton = new QPushButton("Обновить вероятностей");
    probsButton->setFixedSize(250, 70);
    gridLayout->addWidget(probsButton, 2, 4);

    // Следующая итерация
    nextStepButton = new QPushButton("Следующий шаг");
    nextStepButton->setFixedSize(250, 70);
    gridLayout->addWidget(nextStepButton, 3, 4);

    // До конца
    toEndButton = new QPushButton("Выполнить до конца");
    toEndButton->setFixedSize(250, 70);
    gridLayout->addWidget(toEndButton, 4, 4);

    // Переход на меню ввода
    toInputMenuButton = new QPushButton("Обновить исходные данные");
    toInputMenuButton->setFixedSize(250, 70);
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

    table = new QTableWidget(this);
    gridLayout->addWidget(table, 11, 0, 1, 5);

    // График
    chart = new QChart();
    chartView = new QChartView(chart);
    gridLayout->addWidget(chartView, 2, 0, 4, 4);

    // ======= АКТИВАЦИЯ КНОПОК ========
    // Переход к меню ввода
    connect(probsButton, &QPushButton::clicked, this, &ExperimentWindow::updateProbs);

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
        qCritical() << "График не инициализирован.";
        return;
    }

    // Проверка входных данных
    if (bestFitness.empty() || averageFitness.empty() || bestFitness.size() != averageFitness.size()) {
        qWarning() << "График: На текущий момент данных нет.";
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
    // Проверка инициализации таблицы
    if (!table) {
        qCritical("Таблица не инициализирована!");
        return;
    }

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

    // Проверка решений
    std::vector<int> best_solution_vec = best_solution.getSolution();
    if (best_solution_vec.size() != n) {
        qWarning("Размер best_solution не совпадает с количеством предметов!");
        return;
    }

    for (const auto& solution : bestSolutions) {
        if (solution.getSolution().size() != n) {
            qWarning("Одно из решений имеет неверный размер!");
            return;
        }
    }

    // Очищаем таблицу
    table->clear();

    // Устанавливаем размеры
    int row_count = 4 + static_cast<int>(bestSolutions.size());
    table->setRowCount(row_count);
    table->setColumnCount(static_cast<int>(n));

    // Заполняем заголовки
    QStringList row_labels;
    row_labels << "Цены" << "Веса" << "Наилучшее решение" << "Текущее лучшее";
    for (size_t i = 0; i < bestSolutions.size(); ++i) {
        row_labels << QString("Лучшее в %1").arg(i+1);
    }
    table->setVerticalHeaderLabels(row_labels);

    // Заполняем данные
    for (size_t col = 0; col < n; ++col) {
        // Цены
        auto price_item = new QTableWidgetItem(QString::number(prices[col]));
        table->setItem(0, static_cast<int>(col), price_item);

        // Веса
        auto weight_item = new QTableWidgetItem(QString::number(weights[col]));
        table->setItem(1, static_cast<int>(col), weight_item);

        // Наилучшее решение
        auto best_item = new QTableWidgetItem(QString::number(best_solution_vec[col]));
        best_item->setBackground(Qt::green);
        table->setItem(2, static_cast<int>(col), best_item);
    }

    // Заполняем решения
    for (size_t row = 0; row < bestSolutions.size(); ++row) {
        std::vector<int> current_solution = bestSolutions[row].getSolution();

        for (size_t col = 0; col < n; ++col) {
            auto solution_item = new QTableWidgetItem(QString::number(current_solution[col]));
            solution_item->setBackground(current_solution[col] == best_solution_vec[col] ? Qt::green : Qt::white);
            table->setItem(static_cast<int>(row + 3), static_cast<int>(col), solution_item);
        }
    }

    // Настройки таблицы
    table->resizeColumnsToContents();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void ExperimentWindow::statusUpdate(std::string newStatus) {
    statusExperimentWindow->setText(QString::fromStdString("Статус: " + newStatus));
}

void ExperimentWindow::displayInfo(std::string dataManagerInfo, std::string genAlgInfo, std::string populationInfo) {
    informationText->setText(QString::fromStdString("Данные задачи\n" + dataManagerInfo + "\nТекущие настройки\n" + genAlgInfo + "\nПопуляция\n" + populationInfo));
}

std::pair<float, float> ExperimentWindow::getProbs() {
    return {crossoverSpinBox->value(), mutationSpinBox->value()};
}