#include "scanner.h"
#include <iostream>
#include <string>

using namespace std;

// Количество пользователей в системе
const int NUM_USERS = 4;

// Структура, представляющая пользователя с логином и паролем
struct User {
    string login;
    string password;
};

// Массив пользователей с предопределёнными логинами и паролями
User users[NUM_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"user3", "password3"},
    {"admin", "adminpass"}
};

// Двумерный массив учётных данных (логин/пароль)
const char* credentials[NUM_USERS][2] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"user3", "password3"},
    {"admin", "adminpass"}
};

// Функция для проверки соответствия логина и пароля в массиве credentials
bool checkPassword(const char* (*credentials)[2], int numUsers, const string& login, const string& password) {
    for (int i = 0; i < numUsers; ++i) {
        if (credentials[i][0] == login && credentials[i][1] == password) {
            return true;
        }
    }
    return false;
}

// Функция аутентификации пользователя
bool authenticate(const char* (*credentials)[2], int numUsers, string& login) {
    string password;
    cout << "Введите логин (или 'exit' для выхода): ";
    cin >> login;
    if (login == "exit") return false;
    cout << "Введите пароль: ";
    cin >> password;

    return checkPassword(credentials, numUsers, login, password);
}

// Функция для отображения меню
void ShowMenu(const string& login) {
    cout << "Меню:" << endl;
    cout << "1. Сканировать порты" << endl;
    cout << "2. Сканировать открытые порты на уязвимость" << endl;
    cout << "3. Проверить введёный порт" << endl;
    cout << "4. Сохранить отчеты" << endl;
    cout << "5. Вывести количество открытых и открытых уязвимых портов" << endl;
    cout << "6. Сгенерировать сводный отчет" << endl;
    cout << "7. Выход" << endl;
}

// Функция для выполнения выбранной опции меню
void ExecuteOption(int option, OpenPortScanner& openPortScanner, VulnerabilityScanner& vulnerabilityScanner) {
    switch (option) {
    case 1:
        openPortScanner.scan();
        break;
    case 2:
        vulnerabilityScanner.scan();
        break;
    case 3:
        function3();
        break;
    case 4: {
        std::string portsReportFilename, vulnerabilitiesReportFilename;
        std::cout << "Введите имя файла для сохранения отчета об портах: ";
        std::cin >> portsReportFilename;
        std::cout << "Введите имя файла для сохранения отчета об уязвимостях: ";
        std::cin >> vulnerabilitiesReportFilename;
        function4(portsReportFilename, vulnerabilitiesReportFilename);
        break;
    }
    case 5:
        function5();
        break;
    case 6: {
        std::string reportFilename;
        std::cout << "Введите имя файла для сохранения сводного отчета: ";
        std::cin >> reportFilename;
        vulnerabilityScanner.generateSummaryReport(reportFilename);
        break;
    }
    case 7:
        cout << "Выход..." << endl;
        break;
    default:
        cout << "Неверный ввод. Попробуйте снова." << endl;
        break;
    }
}

// Главная функция, с которой начинается выполнение программы
int main() {
    setlocale(0, "rus");
    string login;
    bool authenticated = false;

    // Цикл аутентификации пользователей, пока не будет введено "exit"
    while (true) {
        authenticated = authenticate(credentials, NUM_USERS, login);
        if (!authenticated && login != "exit") {
            cout << "Неверный логин или пароль. Попробуйте снова." << endl;
            continue;  // Продолжаем запрашивать логин и пароль
        }
        else if (login == "exit") {
            cout << "Выход..." << endl;
            break;  // Выход из программы при вводе "exit"
        }

        int option = 0;
        OpenPortScanner openPortScanner;
        VulnerabilityScanner vulnerabilityScanner;

        // Цикл отображения меню, получения выбора пользователя и выполнения действия
        do {
            ShowMenu(login);
            cout << "Введите пункт меню: ";
            cin >> option;
            ExecuteOption(option, openPortScanner, vulnerabilityScanner);
        } while (option != 7); // Выход при выборе пункта 7

        // После выхода из цикла меню можно вернуться к аутентификации
    }

    cout << "Программа завершена." << endl;
    return 0;
}
