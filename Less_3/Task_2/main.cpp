#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


class Observer {
public:
    virtual void onWarning(const std::string &message) {}

    virtual void onError(const std::string &message) {}

    virtual void onFatalError(const std::string &message) {}
};

class Observed {
public:

    void AddObserver(Observer *observer) {
        observers_.push_back(observer);
    }

    void RemoveObserver(Observer *observer) {
        auto it = std::remove(observers_.begin(), observers_.end(), observer);
        observers_.erase(it, observers_.end());
    }

    void warning(const std::string &message) const {
        for (const auto &observer : observers_) {
            observer->onWarning(message);
        }
    }

    void error(const std::string &message) const {
        for (const auto &observer : observers_) {
            observer->onError(message);
        }
    }

    void fatalError(const std::string &message) const {
        for (const auto &observer : observers_) {
            observer->onFatalError(message);
        }
    }

private:
    std::vector<Observer *> observers_;
};


// Оповещение в консоль
class WarningObserver : public Observer {
public:
    void onWarning(const std::string &message) override {
        std::cout << "Предупреждение: " << message << std::endl;
    }
};

// Запись ошибок в файл
class ErrorObserver : public Observer {
public:
    ErrorObserver(const std::string file_name) {
        file_.open(file_name, std::ios::app);
    }

    ~ErrorObserver() {
        file_.close();
    }

    void onError(const std::string &message) override {
        if (file_.is_open()) {
            file_ << "Ошибка: " << message << std::endl;
        }
    }

private:
    std::ofstream file_;
};


// Вывод критических ошибок и запись в файл
class FatalErrorObserver : public Observer {
public:
    FatalErrorObserver(const std::string file_name) {
        file_.open(file_name, std::ios::app);
    }

    ~FatalErrorObserver() {
        file_.close();
    }

    void onFatalError(const std::string &message) override {
        if (file_.is_open()) {
            file_ << "Критическая ошибка: " << message << std::endl;
        }
        std::cout << "Критическая ошибка: " << message << std::endl;
    }

private:
    std::ofstream file_;
};


int main() {

    Observed obj;

    WarningObserver warning;
    ErrorObserver error("error.txt");
    FatalErrorObserver fatal_err("fatal_error.txt");

    obj.AddObserver(&warning);
    obj.AddObserver(&error);
    obj.AddObserver(&fatal_err);


    obj.warning("ВНИМАНИЕ!");
    obj.error("Ошибка 1");
    obj.fatalError("Критическая ошибка 123");


    return 0;

}