#pragma once

#include <string>
#include <unordered_map>
#include <vector>

// Структура для хранения информации о таблице
struct TableSchema {
    std::string name;                 // Название таблицы
    std::vector<std::string> columns; // Список колонок таблицы
};

// Основной интерфейс для работы с JSON
class JSONParser {
public:
    // Загружает схему базы данных из JSON-файла
    static void loadSchema(const std::string& fileName, 
                           std::string& schemaName, 
                           int& tuplesLimit, 
                           std::unordered_map<std::string, TableSchema>& tables);
};
