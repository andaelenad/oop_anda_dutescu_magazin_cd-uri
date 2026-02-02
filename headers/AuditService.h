#ifndef AUDITSERVICE_H
#define AUDITSERVICE_H

#include <iostream>
#include <fstream>
#include <string>

class AuditService {
private:
    static AuditService* instance;
    std::ofstream logFile;

    AuditService() {
        logFile.open("magazin_audit.log", std::ios::app);
    }

public:
    // Stergem metodele de copiere
    AuditService(const AuditService&) = delete;
    AuditService& operator=(const AuditService&) = delete;

    static AuditService* getInstance() {
        if (instance == nullptr) {
            instance = new AuditService();
        }
        return instance;
    }

    void logAction(const std::string& action) {
        if (logFile.is_open()) {
            logFile << "[LOG]: " << action << std::endl;
        }
    }

    ~AuditService() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

inline AuditService* AuditService::instance = nullptr;

#endif // AUDITSERVICE_H