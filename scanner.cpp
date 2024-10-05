#include "scanner.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cstdlib>  // для использования функции system()

bool scanCompleted = false; // Определение внешней переменной

void Scanner::printScanStatus(const std::string& status) const {
    std::cout << status << std::endl;
}

void Scanner::generateSummaryReport(const std::string& reportFilename) const {
    std::ofstream summaryReport(reportFilename, std::ios::out | std::ios::trunc);
    if (!summaryReport.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << reportFilename << std::endl;
        return;
    }

    std::ifstream openPortsReport("ports_report.txt");
    std::ifstream vulnerabilitiesReport("vulnerability_scan_report.txt");

    summaryReport << "Сводный отчет о состоянии системы:" << std::endl;

    if (openPortsReport.is_open()) {
        summaryReport << "\nОтчет об открытых портах:\n";
        summaryReport << openPortsReport.rdbuf();
        openPortsReport.close();
    }
    else {
        summaryReport << "\nНе удалось открыть файл ports_report.txt\n";
    }

    if (vulnerabilitiesReport.is_open()) {
        summaryReport << "\nОтчет об уязвимостях:\n";
        summaryReport << vulnerabilitiesReport.rdbuf();
        vulnerabilitiesReport.close();
    }
    else {
        summaryReport << "\nНе удалось открыть файл vulnerability_scan_report.txt\n";
    }

    summaryReport.close();
    std::cout << "Сводный отчет сохранен в " << reportFilename << "." << std::endl;
}

// Реализация методов OpenPortScanner
OpenPortScanner::OpenPortScanner() {
    reportFile1.open("ports_report.txt", std::ios::out | std::ios::trunc);
    if (!reportFile1.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл отчета для сканирования портов." << std::endl;
    }
    std::cout << "Конструктор OpenPortScanner вызван." << std::endl;
}

OpenPortScanner::~OpenPortScanner() {
    if (reportFile1.is_open()) {
        reportFile1.close();
        std::remove("ports_report.txt");
    }
    std::cout << "Деструктор OpenPortScanner вызван." << std::endl;
}

void OpenPortScanner::scan() {
    std::string ipAddress;
    std::cout << "Введите IP-адрес для сканирования (например, localhost, 192.168.56.101): ";
    std::cin >> ipAddress;

    std::string command = "nmap -p- -A -oN ports_report.txt " + ipAddress;

    printScanStatus("Начато сканирование");

    int result = system(command.c_str());

    printScanStatus("Сканирование завершено");

    if (result == 0) {
        std::cout << "Подробности сканирования можно найти в отчете." << std::endl;
        reportFile1 << "Сканирование IP-адреса " << ipAddress << std::endl;
        reportFile1 << "Результаты сканирования портов:" << std::endl;
    }
    else {
        std::cout << "Ошибка при выполнении сканирования." << std::endl;
    }
}

void OpenPortScanner::printScanStatus(const std::string& status) const {
    Scanner::printScanStatus(status);
}

void OpenPortScanner::generateSummaryReport(const std::string& reportFilename) const {
    Scanner::generateSummaryReport(reportFilename);
}

// Реализация методов VulnerabilityScanner
VulnerabilityScanner::VulnerabilityScanner() {
    reportFile2.open("vulnerability_scan_report.txt", std::ios::out | std::ios::trunc);
    if (!reportFile2.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл отчета для сканирования уязвимостей." << std::endl;
    }
    std::cout << "Конструктор VulnerabilityScanner вызван." << std::endl;
}

VulnerabilityScanner::~VulnerabilityScanner() {
    if (reportFile2.is_open()) {
        reportFile2.close();
        std::remove("vulnerability_scan_report.txt");
    }
    std::cout << "Деструктор VulnerabilityScanner вызван." << std::endl;
}

void VulnerabilityScanner::scan() {
    std::string ipAddress;
    std::cout << "Введите IP-адрес для сканирования (например, localhost, 192.168.56.101): ";
    std::cin >> ipAddress;

    std::string command = "nmap -A --script vulners -oN vulnerability_scan_report.txt " + ipAddress;

    printScanStatus("Начато сканирование");

    int result = system(command.c_str());

    printScanStatus("Сканирование завершено");

    if (result == 0) {
        std::cout << "Отчет сохранен в vulnerability_scan_report.txt." << std::endl;
        scanCompleted = true;
        reportFile2 << "Сканирование IP-адреса " << ipAddress << std::endl;
        reportFile2 << "Результаты сканирования уязвимостей:" << std::endl;
    }
    else {
        std::cout << "Ошибка при выполнении сканирования." << std::endl;
    }
}

void VulnerabilityScanner::printScanStatus(const std::string& status) const {
    Scanner::printScanStatus(status);
}

void VulnerabilityScanner::generateSummaryReport(const std::string& reportFilename) const {
    Scanner::generateSummaryReport(reportFilename);
}

// Реализация function3
void function3() {
    std::string ipAddress;
    std::cout << "Введите IP-адрес для сканирования (например, localhost, 192.168.56.101): ";
    std::cin >> ipAddress;
    std::string port;
    std::cout << "Введите номер порта для проверки: ";
    std::cin >> port;

    std::string command = "nmap -A -p " + port + " --script vulners " + ipAddress;
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Порт " << port << " проверен." << std::endl;
    }
    else {
        std::cout << "Ошибка при проверке порта." << std::endl;
    }
}

// Реализация function4
void function4(const std::string& portsReportFilename, const std::string& vulnerabilitiesReportFilename) {
    std::ifstream srcPorts("ports_report.txt", std::ios::binary);
    std::ofstream destPorts(portsReportFilename, std::ios::binary);

    if (srcPorts && destPorts) {
        destPorts << srcPorts.rdbuf();
        std::cout << "Отчет об открытых портах сохранен в " << portsReportFilename << std::endl;
    }
    else {
        std::cout << "Ошибка при сохранении отчета об открытых портах." << std::endl;
    }

    std::ifstream srcVulnerabilities("vulnerability_scan_report.txt", std::ios::binary);
    std::ofstream destVulnerabilities(vulnerabilitiesReportFilename, std::ios::binary);

    if (srcVulnerabilities && destVulnerabilities) {
        destVulnerabilities << srcVulnerabilities.rdbuf();
        std::cout << "Отчет о найденных уязвимостях сохранен в " << vulnerabilitiesReportFilename << std::endl;
    }
    else {
        std::cout << "Ошибка при сохранении отчета о найденных уязвимостях." << std::endl;
    }
}

// Реализация function5
void function5() {
    std::ifstream openPortsReport("ports_report.txt"); // Открытие файла отчета о портах
    std::ifstream vulnerabilitiesReport("vulnerability_scan_report.txt"); // Открытие файла отчета об уязвимостях

    int openPortsCount = 0; // Счетчик открытых портов
    int vulnerablePortsCount = 0; // Счетчик уязвимых портов
    std::vector<std::string> openPorts; // Вектор для хранения открытых портов
    std::vector<std::string> vulnerablePorts; // Вектор для хранения уязвимых портов
    std::string line;
    std::string prevLine; // Строка две строки выше

    // Подсчет открытых портов
    while (std::getline(openPortsReport, line)) {
        if (line.find("open") != std::string::npos && line.find("closed") == std::string::npos) {
            ++openPortsCount;
            openPorts.push_back(line);
        }
    }

    // Подсчет уязвимых портов
    while (std::getline(vulnerabilitiesReport, line)) {
        if (line.find("vulners:") != std::string::npos) {
            ++vulnerablePortsCount;
            vulnerablePorts.push_back(prevLine); // Добавляем строку, которая на две выше, т.е. описание порта
            vulnerablePorts.push_back(line);
        }
        prevLine = line; // Сохраняем текущую строку для использования на следующей итерации
    }

    std::cout << "Количество открытых портов: " << openPortsCount << std::endl;
    for (const auto& port : openPorts) {
        std::cout << "Порт: " << port << std::endl;
    }

    std::cout << "Количество уязвимых портов: " << vulnerablePortsCount << std::endl;
    for (size_t i = 0; i < vulnerablePorts.size(); i += 2) { 
        std::cout << "Уязвимый порт: " << vulnerablePorts[i] << std::endl;
    }
}



