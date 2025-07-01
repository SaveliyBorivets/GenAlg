#ifndef INPUTMENU_H
#define INPUTMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class InputMenu : public QWidget
{
    Q_OBJECT
public:
    explicit InputMenu(QWidget *parent = nullptr);

signals:
    void switchToExperiment();

private:
    void setupUI();

    // Элементы интерфейса
    QVBoxLayout* inputMenuLayout; // Макет
    QPushButton* randomButton;
    QPushButton* txtInputButton;
    QLineEdit* txtLineEdit;
    QPushButton* guiInputButton;
    QTextEdit* guiText;
    QLabel* statusInputMenu;
    QPushButton* toExperimentButton;
};

#endif // INPUTMENU_H
