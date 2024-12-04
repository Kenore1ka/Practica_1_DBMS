#include "json_parser.h"
#include "json.hpp" // Подключение библиотеки nlohmann JSON

#include <fstream>
#include <iostream>

using json = nlohmann::json;

void JSONParser::loadSchema(const std::string& fileName, 
                            std::string& schemaName, 
                            int& tuplesLimit, 
                            std::unordered_map<std::string, TableSchema>& tables) {
    std::ifstream file(fileName); // Открытие файла
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + fileName);
    }

    // Считывание JSON из файла
    json schema;
    file >> schema;

    // Извлечение имени схемы
    schemaName = schema["name"].get<std::string>();

    // Извлечение ограничения на количество строк в файле
    tuplesLimit = schema["tuples_limit"].get<int>();

    // Извлечение структуры таблиц
    for (const auto& [tableName, columns] : schema["structure"].items()) {
        TableSchema tableSchema;
        tableSchema.name = tableName;

        // Сохранение списка колонок таблицы
        for (const auto& column : columns) {
            tableSchema.columns.push_back(column.get<std::string>());
        }

        // Добавление таблицы в список
        tables[tableName] = tableSchema;
    }

    file.close();
}
