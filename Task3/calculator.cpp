#include "calculator.h"
#include <QMessageBox>
#include <cmath>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Custom Styled Calculator");
    setFixedSize(300, 300);

    input = new QLineEdit();
    input->setReadOnly(true);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(buttons[0][0] = new QPushButton("1"), 1, 0);
    layout->addWidget(buttons[0][1] = new QPushButton("2"), 1, 1);
    layout->addWidget(buttons[0][2] = new QPushButton("3"), 1, 2);
    layout->addWidget(buttons[0][3] = new QPushButton("+"), 1, 3);

    layout->addWidget(buttons[1][0] = new QPushButton("4"), 2, 0);
    layout->addWidget(buttons[1][1] = new QPushButton("5"), 2, 1);
    layout->addWidget(buttons[1][2] = new QPushButton("6"), 2, 2);
    layout->addWidget(buttons[1][3] = new QPushButton("-"), 2, 3);

    layout->addWidget(buttons[2][0] = new QPushButton("7"), 3, 0);
    layout->addWidget(buttons[2][1] = new QPushButton("8"), 3, 1);
    layout->addWidget(buttons[2][2] = new QPushButton("9"), 3, 2);
    layout->addWidget(buttons[2][3] = new QPushButton("x"), 3, 3);

    layout->addWidget(buttons[3][0] = new QPushButton("%"), 4, 0);
    layout->addWidget(buttons[3][1] = new QPushButton("0"), 4, 1);
    layout->addWidget(buttons[3][2] = new QPushButton("/"), 4, 2);
    layout->addWidget(buttons[3][3] = new QPushButton("="), 4, 3);
    layout->addWidget(clearButton = new QPushButton("C"), 0, 0, 1, 1);
    layout->addWidget(input, 0, 1, 1, 4);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearDisplay);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            connect(buttons[i][j], &QPushButton::clicked, this, &Calculator::handleButtonClick);
        }
    }

    setFocusPolicy(Qt::StrongFocus);
}

void Calculator::clearDisplay() {
    input->clear();
}

void Calculator::handleButtonClick() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        QString text = btn->text();
        if (text == "=") {
            QString expr = input->text();
            QStringList operands;
            double num1, num2;
            QString op;
            bool opFound = false;
            for (int i = 0; i < expr.size(); ++i) {
                if (expr[i] == '+' || expr[i] == '-' || expr[i] == 'x' || expr[i] == '/' || expr[i] == '%') {
                    op = expr[i];
                    operands = expr.split(op);
                    if (operands.size() == 2) {
                        num1 = operands[0].toDouble();
                        num2 = operands[1].toDouble();
                        opFound = true;
                        break;
                    }
                }
            }
            if (!opFound) {
                QMessageBox::warning(this, "Error", "Invalid expression");
                return;
            }
            double res = 0;
            if (op == "+") {
                res = num1 + num2;
            } else if (op == "-") {
                res = num1 - num2;
            } else if (op == "x") {
                res = num1 * num2;
            } else if (op == "/") {
                if (num2 != 0) {
                    res = num1 / num2;
                } else {
                    QMessageBox::warning(this, "Error", "You cannot divide by zero");
                    return;
                }
            } else if (op == "%") {
                res = fmod(num1, num2);
            }
            input->setText(QString::number(res));
        } else {
            input->setText(input->text() + text);
        }
    }
}

void Calculator::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
    case Qt::Key_Plus:
    case Qt::Key_Minus:
    case Qt::Key_Asterisk:
    case Qt::Key_Slash:
    case Qt::Key_Percent:
        emitKeyPress(event->text());
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        handleButtonClick();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}



void Calculator::emitKeyPress(const QString &text) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (buttons[i][j]->text() == text) {
                buttons[i][j]->click();
                return;
            }
        }
    }
    if (text == "C") {
        clearButton->click();
    }
}
