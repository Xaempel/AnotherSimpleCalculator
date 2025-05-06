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
#pragma once

#include <QString>
#include <sqlite3.h>
#include <QStringList>
#include <exception>

class DatabaseModel{
    public:
    static void initDb(){
        const char* dbFile = "AppDb.db";

        int rc {0};

        rc = sqlite3_open(dbFile, &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("In initating of db was someting went wrong ");
        }

        const char* createTablequeary = "CREATE TABLE IF NOT EXISTS mathematical_operations(id INTEGER PRIMARY KEY AUTOINCREMENT, operations TEXT NOT NULL)";
        rc = sqlite3_exec(db, createTablequeary, nullptr, nullptr, nullptr);

        if(rc != SQLITE_OK){
            throw std::runtime_error("When table was creating someting went wrong");
        }
        sqlite3_close(db);
    }

    static void addMathematicalOperations(QString mathematicalOperations) {
        int rc = sqlite3_open("AppDb.db", &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("When db was opening something went wrong");
        }
    
        sqlite3_stmt *stmt = nullptr; 
        const char *query = "INSERT INTO mathematical_operations (operations) VALUES (?);";
    
        rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            throw std::runtime_error("When queary was preparing something went wrong");
        }
    
        QByteArray utf8Data = mathematicalOperations.toUtf8();
        const char *operationCStr = utf8Data.constData();
    
        rc = sqlite3_bind_text(stmt, 1, operationCStr, -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("Error of binding for parameter");
        }
    
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("Error of running query");
        }
    
        rc = sqlite3_finalize(stmt);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            throw std::runtime_error("Error of finalize query");
        }
    
        rc = sqlite3_close(db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("When db was closing something went wrong");
        }
    }

    static QStringList getMathematicalOperations() {
        QStringList operationsList {};
    
        sqlite3_open("AppDb.db", &db);
    
        sqlite3_stmt *stmt = nullptr;
        const char *query = "SELECT operations FROM mathematical_operations"; 
        sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *text = sqlite3_column_text(stmt, 0); 
            if (text) {
                operationsList.append(QString((const char *)text));
            }
        }
    
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return operationsList;
    }

    private:
    static sqlite3 *db;
};