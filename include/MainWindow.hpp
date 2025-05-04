/*******************************************************************************
**                                                                            **
**  Copyright (C) [2025] [Xaempel]                                            **
**                                                                            **
**  This file is part of [AnotherSimpleCalculator].                           **
**  [AnotherSimpleCalculator] is free software: you can redistribute it and/or**
**  modify it under the terms of the GNU General Public License as published  **
**  by the Free Software Foundation, either version 2 of the License, or any  **
**  later version.                                                            **
**                                                                            **
**  [AnotherSimpleCalculator] is distributed in the hope that it will be      **
**  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of    **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             **
**  GNU General Public License for more details.                              **
**                                                                            **
**  You should have received a copy of the GNU General Public License along   **
**  with [AnotherSimpleCalculator].  If not, see <https://www.gnu.org/licenses/>.*
**                                                                            **
**  This project uses the Qt framework, which is licensed under the GNU       **
**  General Public License (GPL) version 2 or later. The full text of the     **
**  GPL license can be found in the LICENSE file.                             **
**                                                                            **
**  Qt is a cross-platform application framework maintained by The Qt Company.**
**  You can find more information about Qt and its licensing at               **
**  https://www.qt.io/.                                                       **
**                                                                            **
*******************************************************************************/


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
   class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
   Q_OBJECT

   public:
   explicit MainWindow(QWidget* parent = nullptr);

   signals:
   void addNumbertoOperation(int number);
   void aritmeticalOperationWasSelected(QString operation);
   void sumNumbers();

   private:
   Ui::MainWindow* ui {nullptr};

   bool operationWasSelected {false};
   
   QString firstNumber {"0"};
   QString secondNumber {"0"};
   QString mathOperation {""};
};