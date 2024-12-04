#include "table_manager.h"
#include <fstream>
#include <iostream>

void Table::init(const std::string& tableName, int limit) {
    name = tableName;
    tupleLimit = limit;
    rows.init(10); // Инициализация массива с начальной ёмкостью
}

void Table::createTableIfNotExists(const std::string& fileName) {
    // Проверяем, существует ли файл
    std::ifstream file(fileName);
    if (file.good()) {
        // Если файл уже существует, ничего не делаем
        std::cout << "Файл таблицы уже существует: " << fileName << std::endl;
        file.close();
        return;
    }
    file.close();

    // Если файл не существует, создаём его
    std::ofstream newFile(fileName);
    if (!newFile.is_open()) {
        std::cerr << "Не удалось создать файл таблицы: " << fileName << std::endl;
        return;
    }

    // Если массив строк (rows) содержит заголовки, записываем их в файл
    if (rows.length() > 0) {
        for (int i = 0; i < rows.length(); i++) {
            newFile << rows.get(i); // Записываем строку
            if (i < rows.length() - 1) {
                newFile << ","; // Добавляем запятую, если это не последняя строка
            }
        }
        newFile << std::endl;
    } else {
        std::cerr << "Предупреждение: таблица создаётся без заголовков!" << std::endl;
    }

    newFile.close();
    std::cout << "Создан новый файл таблицы: " << fileName << std::endl;
}

void Table::loadFromFile(const std::string& fileName) {
    // Загружаем данные из файла
    rows.loadFromFile(fileName);
    std::cout << "Данные загружены из файла: " << fileName << std::endl;
}

void Table::saveToFile(const std::string& fileName) {
    // Сохраняем данные в файл
    rows.saveToFile(fileName);
    std::cout << "Данные сохранены в файл: " << fileName << std::endl;
}

void Table::addRow(const std::string& row) {
    // Проверяем лимит строк
    if (rows.length() >= tupleLimit) {
        std::cerr << "Ошибка: достигнут лимит строк в таблице (" << tupleLimit << ")!" << std::endl;
        return;
    }
    // Добавление строки в таблицу
    rows.add(row);
    std::cout << "Добавлена строка: " << row << std::endl;
}

void Table::deleteRow(int rowIndex) {
    // Удаление строки по индексу
    if (rowIndex < 0 || rowIndex >= rows.length()) {
        std::cerr << "Ошибка: индекс строки " << rowIndex << " за пределами таблицы!" << std::endl;
        return;
    }
    rows.remove(rowIndex);
    std::cout << "Удалена строка с индексом: " << rowIndex << std::endl;
}
