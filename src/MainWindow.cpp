#include "include/MainWindow.hpp"

#include "frontend/ui_MainWindow.h"

#include "../include/models/DatabaseModel.hpp"

#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   DatabaseModel::initDb();

   QObject::connect(ui->num_1,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(1);});
   QObject::connect(ui->num_2,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(2);});
   QObject::connect(ui->num_3,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(3);});
   QObject::connect(ui->num_4,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(4);});
   QObject::connect(ui->num_5,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(5);});
   QObject::connect(ui->num_6,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(6);});
   QObject::connect(ui->num_7,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(7);});
   QObject::connect(ui->num_8,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(8);});
   QObject::connect(ui->num_9,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(9);});
   QObject::connect(ui->num_0,&QPushButton::clicked,this,[this](){emit actionAddNumbertoOperation(0);});

   QObject::connect(ui->addOperation,&QPushButton::clicked,this,[this](){emit actionAritmeticalOperationSelected("+");});
   QObject::connect(ui->minusOperation,&QPushButton::clicked,this,[this](){emit actionAritmeticalOperationSelected("-");});
   QObject::connect(ui->divisionOperation,&QPushButton::clicked,this,[this](){emit actionAritmeticalOperationSelected("/");});
   QObject::connect(ui->multiOperation,&QPushButton::clicked,this,[this](){emit actionAritmeticalOperationSelected("*");});
   QObject::connect(ui->ExponentiationButton,&QPushButton::clicked,this,[this](){emit actionAritmeticalOperationSelected("^");});
   QObject::connect(ui->squarerootButton,&QPushButton::clicked,this,[this](){emit actionAritmeticalOperationSelected("sqrt(X)");});

   QObject::connect(ui->equalOperation,&QPushButton::clicked,this,&MainWindow::sumNumbers);
   QObject::connect(ui->clearButton,&QPushButton::clicked,this,&MainWindow::clearOperations);
   QObject::connect(ui->undoActionButton,&QPushButton::clicked,this,&MainWindow::undoOperation);

   QObject::connect(this,&MainWindow::actionAritmeticalOperationSelected,this,&MainWindow::aritmeticalOperationSelected);

   QObject:connect(this,&MainWindow::actionAddNumbertoOperation,this,&MainWindow::addNumbertoOperation);
   QObject::connect(ui->LastOperationsRecords,&QPushButton::clicked,this,[this](){
        mathOperationsRecordsWidget = new MathOperationsRecordsWidget(nullptr);
        this->mathOperationsRecordsWidget->show();
    });
}

void MainWindow::sumNumbers(){
    operationWasSelected = false;

    float firstNum = firstNumber.toInt();
    float secondNum = secondNumber.toInt();
    float sumofNumbers = 0;

    if(mathOperation == "+"){
        sumofNumbers = firstNum + secondNum;
    }
    else if(mathOperation == "-"){
        sumofNumbers = firstNum - secondNum;
    }
    else if(mathOperation == "*"){
        sumofNumbers = firstNum * secondNum;
    }
    else if(mathOperation == "/"){
        if(secondNum == 0){
            QMessageBox::warning(nullptr,"Divide Error","Bro! Why you're wanna create a black hole in universe");
        }
        else{
            sumofNumbers = firstNum / secondNum;
        }
    }
    else if(mathOperation == "^"){
        sumofNumbers = pow(firstNum,secondNum);
    }

    else if(mathOperation == "sqrt(X)"){
        if(firstNum >= 0){
            sumofNumbers = sqrt(firstNum);
        } 
        else{
            QMessageBox::warning(nullptr,"Square Root Error","Bro why you're trying a square root from negative number in real numbers? This is not that the system");
        }
    }
    ui->operationMonit->setText(QString::number(sumofNumbers) );
    
    QString operation = firstNumber + mathOperation + secondNumber + "=" + QString::number(sumofNumbers);  
    DatabaseModel::addMathematicalOperations(operation);
    
    firstNumber = QString::number(sumofNumbers);
    secondNumber = "0";
}

void MainWindow::addNumbertoOperation(int numbertoAdd){
    QString currentOperation = ui->operationMonit->text();
    currentOperation += QString::number(numbertoAdd);
    ui->operationMonit->setText(currentOperation);

    if(operationWasSelected == false){
        if(firstNumber == "0"){
            firstNumber = "";
        }
        firstNumber += QString::number(numbertoAdd); 
    }
    else{
        if(secondNumber == "0"){
            secondNumber = "";
        }
        secondNumber += QString::number(numbertoAdd);
    }
}

void MainWindow::aritmeticalOperationSelected(QString operation){
    if(operationWasSelected == false){
        QString currentOperation = ui->operationMonit->text();
        currentOperation += operation;
        ui->operationMonit->setText(currentOperation);
        operationWasSelected = true;
        mathOperation = operation;
    } 
    else{
        return;
    }
}

void MainWindow::clearOperations(){
    firstNumber = "0";
    secondNumber = "0";
    ui->operationMonit->setText("");
}

void MainWindow::undoOperation(){
    if(firstNumber.size() > 0 ){
        if(operationWasSelected == false){
            int lastIndex = firstNumber.size() - 1; 
            QString newNumber = firstNumber; 
            newNumber.remove(lastIndex, 1);
            ui->operationMonit->setText(newNumber);
            firstNumber = newNumber; 
        }
        else{
            if(secondNumber.size() > 0){
                int lastIndex = secondNumber.size() - 1; 
                QString newNumber = secondNumber; 
                newNumber.remove(lastIndex, 1);
                QString stringToset = firstNumber + mathOperation + newNumber;
                ui->operationMonit->setText(stringToset);
                secondNumber = newNumber;
            } 
            else{
                mathOperation = "";
                ui->operationMonit->setText(firstNumber);
                operationWasSelected = false;
            }
        }
    }
}