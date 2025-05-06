#include "../include/MathOperationsRecordsWidget.hpp"

#include "frontend/ui_MathOperationsRecordsWidget.h"
#include "../include/models/DatabaseModel.hpp"

#include <QLabel>

MathOperationsRecordsWidget::MathOperationsRecordsWidget(QWidget * parent) 
    : QFrame(parent), 
    ui(new Ui::MathOperationsRecordsWidget)
{
   ui->setupUi(this);

   QStringList operations = DatabaseModel::getMathematicalOperations();

   QLabel *RecordLabel {nullptr};
   for(auto i : operations){
    RecordLabel = new QLabel();
    RecordLabel->setText(i);
    ui->OperaionsRecords->addWidget(RecordLabel);
   }
}