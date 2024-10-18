#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

json json_read () {
    // Имя файла
    string filename = "schema.json";

    // Открываем файл
    ifstream file(filename);

    // Проверяем, открыт ли файл
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    // Считываем содержимое файла в JSON-объект
    json j;
    try {
        file >> j;
    } catch (const json::parse_error& e) {
        cerr << "Ошибка: не удалось разобрать JSON-файл " << filename << endl;
        return 1;
    }
    // Заменить вывод в консоли на создание директорий -------------------------------------
    // Выводим содержимое JSON-объекта
    cout << "Имя схемы: " << j["name"] << endl;
    cout << "Лимит кортежей: " << j["tuples_limit"] << endl;

    // Выводим структуру таблиц
    cout << "Структура таблиц:" << endl;
    for (const auto& table : j["structure"].items()) {
        cout << "  Таблица: " << table.key() << endl;
        for (const auto& column : table.value()) {
            cout << "    Колонка: " << column << endl;
        }
    }

    // Закрываем файл
    file.close();

    return 0;
}