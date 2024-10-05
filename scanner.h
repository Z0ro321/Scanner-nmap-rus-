#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>

extern bool scanCompleted; // Объявление внешней переменной

class Scanner {
public:
    virtual ~Scanner() {}
    virtual void scan() = 0;
    virtual void printScanStatus(const std::string& status) const;
    virtual void generateSummaryReport(const std::string& reportFilename) const;
};

class OpenPortScanner : public Scanner {
public:
    OpenPortScanner();
    ~OpenPortScanner();
    void scan() override;
    void printScanStatus(const std::string& status) const override;
    void generateSummaryReport(const std::string& reportFilename) const override;

private:
    std::ofstream reportFile1;
};

class VulnerabilityScanner : public Scanner {
public:
    VulnerabilityScanner();
    ~VulnerabilityScanner();
    void scan() override;
    void printScanStatus(const std::string& status) const override;
    void generateSummaryReport(const std::string& reportFilename) const override;

private:
    std::ofstream reportFile2;
};

void function3();
void function4(const std::string& portsReportFilename, const std::string& vulnerabilitiesReportFilename);
void function5();

#endif // SCANNER_H
