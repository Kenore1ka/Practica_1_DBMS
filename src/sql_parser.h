#pragma once

#include <string>
#include "array.h"

// Структура для хранения данных SQL-запроса
struct SQLQuery {
    std::string command;         // Тип команды (SELECT, INSERT, DELETE)
    std::string tableName;       // Имя таблицы
    DynamicArray columns;        // Колонки (только для SELECT)
    DynamicArray values;         // Значения (только для INSERT)
    std::string condition;       // Условие WHERE (для SELECT и DELETE)
    
    void init();                 // Инициализация структуры
    void destroy();              // Освобождение ресурсов
};

// Класс SQL-парсера
class SQLParser {
public:
    static SQLQuery parse(const std::string& query); // Парсинг SQL-запроса
};
