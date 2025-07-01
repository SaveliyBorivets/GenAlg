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
                                "3. Максимальная вместимость рюкзака\n"
                                "4. Количество предметов\n"
                                "5. Цены предметов через пробел\n"
                                "6. Веса предметов через пробел\n");
    guiText->setMaximumHeight(300);
    inputMenuLayout->addWidget(guiText);

    statusInputMenu = new QLabel("Статус: ");
    inputMenuLayout->addWidget(statusInputMenu);

    toExperimentButton = new QPushButton("К эксперименту");
    inputMenuLayout->addWidget(toExperimentButton);
    connect(toExperimentButton, &QPushButton::clicked,
            this, &InputMenu::switchToExperiment);
}
