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
    QString getPath() const;
    QString getGuiText() const;
    void setStatus(std::string newStatus);
    void displayInfo(std::string dataManagerInfo);

signals:
    void switchToExperiment();
    void getDataFromTxt();
    void getDataFromGui();
    void generateRandomDataManager();

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
    QTextEdit* informationText;
};

#endif // INPUTMENU_H
