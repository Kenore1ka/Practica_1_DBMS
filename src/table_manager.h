#pragma once

#include <string>
#include <unordered_map>
#include "array.h" // Для работы с динамическим массивом

// Структура для представления таблицы
struct Table {
    std::string name;             // Название таблицы
    DynamicArray rows;            // Динамический массив для хранения строк таблицы
    int tupleLimit;               // Лимит строк в таблице
    std::unordered_map<std::string, int> primaryKeySequence; // Последовательность для первичных ключей
    
    void createTableIfNotExists(const std::string& fileName);
    void init(const std::string& tableName, int limit);
    void loadFromFile(const std::string& fileName);
    void saveToFile(const std::string& fileName);
    void addRow(const std::string& row);
    void deleteRow(int rowIndex);
};
