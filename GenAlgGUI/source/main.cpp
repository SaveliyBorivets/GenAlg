#include <QApplication>
#include <QStackedWidget>

#include "InputMenu.h"
#include "ExperimentWindow.h"

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

    return app.exec();
}
