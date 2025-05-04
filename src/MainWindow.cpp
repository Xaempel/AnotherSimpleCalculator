#include "include/MainWindow.hpp"

#include "frontend/ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   QObject::connect(ui->num_1,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(1);});
   QObject::connect(ui->num_2,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(2);});
   QObject::connect(ui->num_3,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(3);});
   QObject::connect(ui->num_4,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(4);});
   QObject::connect(ui->num_5,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(5);});
   QObject::connect(ui->num_6,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(6);});
   QObject::connect(ui->num_7,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(7);});
   QObject::connect(ui->num_8,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(8);});
   QObject::connect(ui->num_9,&QPushButton::clicked,this,[this](){emit addNumbertoOperation(9);});

   QObject::connect(ui->addOperation,&QPushButton::clicked,this,[this](){emit aritmeticalOperationWasSelected("+");});
   QObject::connect(ui->minusOperation,&QPushButton::clicked,this,[this](){emit aritmeticalOperationWasSelected("-");});
   QObject::connect(ui->equalOperation,&QPushButton::clicked,this,[this](){emit sumNumbers();});

   QObject::connect(this,&MainWindow::aritmeticalOperationWasSelected,this,[this](QString operation){
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
    });

    QObject::connect(this,&MainWindow::sumNumbers,this,[this](){
        int firstNum = firstNumber.toInt();
        int secondNum = secondNumber.toInt();
        int sumofNumber = 0;
        
        if(mathOperation == "+"){
            sumofNumber = firstNum + secondNum;
        }
        if(mathOperation == "-"){
            sumofNumber = firstNum - secondNum;
        }
        ui->operationMonit->setText(QString::number(sumofNumber) );
    });

   QObject:connect(this,&MainWindow::addNumbertoOperation,this,[this](int numbertoAdd){
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
    });
}