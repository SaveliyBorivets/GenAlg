#include "InputMenu.h"

InputMenu::InputMenu(QWidget *parent) : QWidget(parent) {
    // ===== ОКНО ВВОДА =====

    // Размеры
    setMinimumHeight(720);
    setMinimumWidth(1280);

    setupUI();
}

void InputMenu::setupUI() {
    // Макет для вводов
    inputMenuLayout = new QVBoxLayout(this);

    // ======= КНОПКА =======
    // Кнопка случайной генерации
    randomButton = new QPushButton("Случайная генерация");
    randomButton->setFixedSize(200, 70);
    inputMenuLayout->addWidget(randomButton);

    // Кнопка ввода txt
    txtInputButton = new QPushButton("Ввод из txt-файла");
    txtInputButton->setFixedSize(200, 70);
    inputMenuLayout->addWidget(txtInputButton);

    // Ввод для пути к txt-файлу
    txtLineEdit = new QLineEdit();
    txtLineEdit->setPlaceholderText("Введите путь к txt-файлу...");
    inputMenuLayout->addWidget(txtLineEdit);

    // Кнопка ввода GUI
    guiInputButton = new QPushButton("Ввод из GUI");
    guiInputButton->setFixedSize(200, 70);
    inputMenuLayout->addWidget(guiInputButton);

    // Панель ввода данных через GUI
    guiText = new QTextEdit();
    guiText->setPlaceholderText("Формат ввода:\n"
                                "1. Вместимость рюкзака\n"
                                "2. Размер популяции\n"
                                "3. Количество предметов\n"
                                "4. Цены предметов через пробел\n"
                                "5. Веса предметов через пробел\n");
    guiText->setMaximumHeight(300);
    inputMenuLayout->addWidget(guiText);

    statusInputMenu = new QLabel("Статус: ");
    inputMenuLayout->addWidget(statusInputMenu);
    statusInputMenu->setText("Статус: Необходимы данные");

    // ======= АКТИВАЦИЯ КНОПОК ========
    // Окно эксперимента
    toExperimentButton = new QPushButton("К эксперименту");
    inputMenuLayout->addWidget(toExperimentButton);
    connect(toExperimentButton, &QPushButton::clicked, this, &InputMenu::switchToExperiment);

    // Получение пути к txt
    connect(txtInputButton, &QPushButton::clicked, this, &InputMenu::getDataFromTxt);

    // Получение данных из GUI
    connect(guiInputButton, &QPushButton::clicked, this, &InputMenu::getDataFromGui);

    // Случайная генерация
    connect(randomButton, &QPushButton::clicked, this, &InputMenu::generateRandomDataManager);
}

QString InputMenu::getPath() const {
    return txtLineEdit->text();
}

QString InputMenu::getGuiText() const {
    return guiText->toPlainText();
}

void InputMenu::setStatus(std::string newStatus) {
    statusInputMenu->setText(QString::fromStdString("Статус: " + newStatus));
}
