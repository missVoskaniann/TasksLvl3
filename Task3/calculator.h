#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QKeyEvent>

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void handleButtonClick();
    void clearDisplay();
    void keyPressEvent(QKeyEvent *event);

private:
    QPushButton *buttons[4][4];
    QPushButton *clearButton;
    QLineEdit* input;

    void emitKeyPress(const QString &text);
};

#endif // CALCULATOR_H
