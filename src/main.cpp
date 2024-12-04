#include "json_parser.h"
#include "table_manager.h"
#include <iostream>
#include <unordered_map>

int main() {
    // Переменные для хранения данных из JSON
    std::string schemaName;
    int tuplesLimit;
    std::unordered_map<std::string, TableSchema> tablesSchema;

    // Шаг 1: Загружаем схему из JSON
    try {
        JSONParser::loadSchema("schema.json", schemaName, tuplesLimit, tablesSchema);
        std::cout << "Схема '" << schemaName << "' загружена успешно!" << std::endl;
        std::cout << "Лимит строк: " << tuplesLimit << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке схемы: " << e.what() << std::endl;
        return 1;
    }

    // Шаг 2: Создание таблиц на основе структуры из JSON
    for (const auto& [tableName, tableSchema] : tablesSchema) {
        Table table;
        table.init(tableSchema.name, tuplesLimit);

        // Добавляем заголовки колонок из структуры таблицы
        std::string headers;
        for (const auto& column : tableSchema.columns) {
            headers += column + ",";
        }
        headers.pop_back(); // Убираем последнюю запятую
        table.addRow(headers);

        // Создаём файл таблицы, если он не существует
        std::string fileName = tableSchema.name + ".csv";
        table.createTableIfNotExists(fileName);

        // Сохраняем таблицу
        table.saveToFile(fileName);

        std::cout << "Таблица '" << tableSchema.name << "' создана и сохранена в файл '" << fileName << "'!" << std::endl;
    }

    return 0;
}
