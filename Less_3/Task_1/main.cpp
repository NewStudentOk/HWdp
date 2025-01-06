#include <iostream>
#include <fstream>
#include <string>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};


class LogToFileCommand : public LogCommand {
private:
    std::string message;
    std::string filePath;
    std::ofstream file;
public:
    LogToFileCommand(const std::string& msg, const std::string& path) : message(msg), filePath(path) {
        file.open(filePath);
    }

    void print(const std::string& msg) override {
        file << msg << message << std::endl;
    }

    ~LogToFileCommand()
    {
        file.close();
    }
};

class LogPrintCommand : public LogCommand {
private:
    std::string message;
public:
    LogPrintCommand(const std::string& msg) : message(msg) {}
    void print(const std::string& msg) override {
        std::cout << msg << message << std::endl;
    }
};


// Function to execute a command
void print(LogCommand& command) {
    command.print("Log: ");
}



int main() {
    // Create command objects
    LogToFileCommand command_to_file("Log to file","log.txt");
    LogPrintCommand command_out("Log print");

    print(command_to_file);
    print(command_out);

    return 0;
}

