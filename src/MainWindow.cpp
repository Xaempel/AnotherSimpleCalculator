#include "include/MainWindow.hpp"

#include "frontend/ui_MainWindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

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
   
   QObject::connect(ui->equalOperation,&QPushButton::clicked,this,&MainWindow::sumNumbers);
   QObject::connect(ui->clearButton,&QPushButton::clicked,this,&MainWindow::clearOperations);

   QObject::connect(this,&MainWindow::actionAritmeticalOperationSelected,this,&MainWindow::aritmeticalOperationSelected);

   QObject:connect(this,&MainWindow::actionAddNumbertoOperation,this,&MainWindow::addNumbertoOperation);
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
    ui->operationMonit->setText(QString::number(sumofNumbers) );
    
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