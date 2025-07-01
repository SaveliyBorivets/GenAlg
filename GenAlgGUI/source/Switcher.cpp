#include "Switcher.h"
#include "InputMenu.h"
#include "ExperimentWindow.h"

Switcher::Switcher(QWidget *parent) : QStackedWidget(parent)
{
    // ===== ОКНО ПЕРЕКЛЮЧАТЕЛЯ =====
    setWindowTitle("GenAlg GUI");

    InputMenu inputMenu = new InputMenu(this);
    ExperimentWindow experimentWindow = new ExperimentWindow(this);

    addWidget(inputMenu);
    addWidget(experimentWindow);

    // Подключение кнопок (перемещено в соответствующие классы)
    connect(inputMenu, &InputMenu::switchToExperiment, [this]() {
        setCurrentIndex(1); // К окну эксперимента
    });

    connect(experimentWindow, &ExperimentWindow::switchToInput, [this]() {
        setCurrentIndex(0); // К окну ввода
    });
}
