#include "sql_parser.h"
#include <sstream>   // Для обработки строки запроса
#include <iostream>  // Для вывода ошибок и отладки

void SQLQuery::init() {
    columns.init(10); // Инициализация массива для колонок
    values.init(10);  // Инициализация массива для значений
}

void SQLQuery::destroy() {
    columns.destroy(); // Освобождение памяти из массива колонок
    values.destroy();  // Освобождение памяти из массива значений
}

SQLQuery SQLParser::parse(const std::string& query) {
    SQLQuery sqlQuery;
    sqlQuery.init();

    // Преобразуем запрос в верхний регистр для унификации
    std::string upperQuery = query;
    for (char& c : upperQuery) {
        c = toupper(c);  // Переводим все символы в верхний регистр
    }

    // Проверяем, начинается ли запрос с ключевого слова
    if (upperQuery.rfind("SELECT", 0) == 0) {
        // Парсим SELECT column1, column2 FROM table_name WHERE condition
        size_t fromPos = upperQuery.find(" FROM ");
        if (fromPos == std::string::npos) {
            std::cerr << "Ошибка: отсутствует ключевое слово FROM в запросе SELECT." << std::endl;
            sqlQuery.destroy();
            return sqlQuery;
        }

        // Извлекаем колонки
        std::string columnsPart = query.substr(7, fromPos - 7); // "SELECT " = 7 символов
        size_t pos = 0;
        while ((pos = columnsPart.find(',')) != std::string::npos) {
            sqlQuery.columns.add(columnsPart.substr(0, pos));
            columnsPart = columnsPart.substr(pos + 1);
        }
        sqlQuery.columns.add(columnsPart); // Добавляем последнюю колонку

        // Извлекаем имя таблицы
        size_t wherePos = upperQuery.find(" WHERE ", fromPos);
        if (wherePos == std::string::npos) {
            sqlQuery.tableName = query.substr(fromPos + 6); // " FROM " = 6 символов
        } else {
            sqlQuery.tableName = query.substr(fromPos + 6, wherePos - (fromPos + 6));
        }

        // Извлекаем условие
        if (wherePos != std::string::npos) {
            sqlQuery.condition = query.substr(wherePos + 7); // " WHERE " = 7 символов
        }

    } else if (upperQuery.rfind("INSERT", 0) == 0) {
        // Парсим INSERT INTO table_name VALUES (value1, value2, ...)
        size_t intoPos = upperQuery.find(" INTO ");
        size_t valuesPos = upperQuery.find(" VALUES ");
        if (intoPos == std::string::npos || valuesPos == std::string::npos) {
            std::cerr << "Ошибка: некорректный синтаксис команды INSERT." << std::endl;
            sqlQuery.destroy();
            return sqlQuery;
        }

        // Извлекаем имя таблицы
        sqlQuery.tableName = query.substr(intoPos + 6, valuesPos - (intoPos + 6));

        // Извлекаем значения
        size_t startValues = query.find('(', valuesPos);
        size_t endValues = query.find(')', startValues);
        if (startValues == std::string::npos || endValues == std::string::npos) {
            std::cerr << "Ошибка: значения INSERT должны быть в скобках." << std::endl;
            sqlQuery.destroy();
            return sqlQuery;
        }

        std::string valuesPart = query.substr(startValues + 1, endValues - (startValues + 1));
        size_t pos = 0;
        while ((pos = valuesPart.find(',')) != std::string::npos) {
            sqlQuery.values.add(valuesPart.substr(0, pos));
            valuesPart = valuesPart.substr(pos + 1);
        }
        sqlQuery.values.add(valuesPart); // Добавляем последнее значение

    } else if (upperQuery.rfind("DELETE", 0) == 0) {
        // Парсим DELETE FROM table_name WHERE condition
        size_t fromPos = upperQuery.find(" FROM ");
        if (fromPos == std::string::npos) {
            std::cerr << "Ошибка: отсутствует ключевое слово FROM в запросе DELETE." << std::endl;
            sqlQuery.destroy();
            return sqlQuery;
        }

        // Извлекаем имя таблицы
        size_t wherePos = upperQuery.find(" WHERE ", fromPos);
        if (wherePos == std::string::npos) {
            sqlQuery.tableName = query.substr(fromPos + 6);
        } else {
            sqlQuery.tableName = query.substr(fromPos + 6, wherePos - (fromPos + 6));
        }

        // Извлекаем условие
        if (wherePos != std::string::npos) {
            sqlQuery.condition = query.substr(wherePos + 7);
        }

    } else {
        // Если команда не поддерживается
        std::cerr << "Ошибка: неизвестная команда '" << sqlQuery.command << "'." << std::endl;
        sqlQuery.destroy();
    }

    return sqlQuery;
}

