#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(const auto & button : findChildren<QPushButton *>()) {
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked()
{
    static QString strDisplay;

    QString str = ((QPushButton*)sender())->text();

        if (str == "CE") {
            m_stk.clear();
            strDisplay = "";
            ui->lcdNumber->display("0");
            return;
        }
        if (str.contains(QRegExp("[0-9]"))) {
            strDisplay += str;
            ui->lcdNumber->display(strDisplay.toDouble());
        }

        else if (str == ".") {
            strDisplay += str;
            ui->lcdNumber->display(strDisplay);
        }
        else {
            if (m_stk.count() >= 2) {
                m_stk.push(QString().setNum(ui->lcdNumber->value()));
                calculate();
                m_stk.clear();
                m_stk.push(QString().setNum(ui->lcdNumber->value()));
                if (str != "=") {
                    m_stk.push(str);
                }
            }
            else {
                if(str == "=") {
                    return;
                }

                m_stk.push(QString().setNum(ui->lcdNumber->value()));
                m_stk.push(str);

                strDisplay = "";
                ui->lcdNumber->display("0");
            }
                }
}

void MainWindow::calculate()
{
    if(m_stk.isEmpty()) {
        return;
    }

    double dOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    double dOperand1 = m_stk.pop().toDouble();
    double dResult = 0;
    if (strOperation == "+") {
       dResult = dOperand1 + dOperand2;
    }
    if (strOperation == "-") {
       dResult = dOperand1 - dOperand2;
    }
    if (strOperation == "/") {
       dResult = dOperand1 / dOperand2;
    }
    if (strOperation == "*") {
       dResult = dOperand1 * dOperand2;
    }

    ui->lcdNumber->display(dResult);
}

