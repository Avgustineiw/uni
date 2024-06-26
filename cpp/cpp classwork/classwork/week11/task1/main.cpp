#include <chrono>
#include <ctime>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

/*
Design a logging system in C++ that allows for messages of different severity levels to be
 recorded to a file. Your task involves creating a `Logger` class that supports logging messages
 with varying levels of importance, namely ERROR, WARNING, INFO, and DEBUG. The `Logger` class
 should be implemented as a singleton to ensure that only one instance can exist throughout the application.
 It must provide a method to set the logging level and another to log messages, which includes the message's timestamp,
 its level, and the text. The logger should append messages to a log file, with the ability to
 specify the file's name when accessing the logger instance for the first time. Additionally,
 the logger should ignore messages that are below the current logging level.

Implement a demonstration of using this logging system by creating a simple function that performs an
 operation (e.g., summing two integers) and logs messages at different levels based on the operation's
 progression. The main function should adjust the logging level to demonstrate filtering based on the
 level and ensure that the logging output includes relevant timestamps and message levels.
*/

class Logger {
 public:
  enum class Level {
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG,
  };

 private:
  std::ofstream logFile;
  Level currentLevel;

  Logger(const std::string &filename, Level level = Level::INFO) : currentLevel(level) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
      throw std::runtime_error("Failed to open log file");
    }
  }

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

 public:
  ~Logger() {
    logFile.close();
  }
  static Logger &getInstance(const std::string &filename = "logfile.txt") {
    static Logger instance(filename);
    return instance;
  }

  void setLevel(Level level) {
    this->currentLevel = level;
  }

  void log(const std::string &message, Level level = Level::INFO) {
    if (currentLevel >= level) {
      auto t = std::chrono::system_clock::now();
      std::time_t time = std::chrono::system_clock::to_time_t(t);
      logFile << std::ctime(&time) << " " << levelToString(level) << ": " << message << '\n';
      std::cout << std::ctime(&time) << " " << levelToString(level) << ": " << message << '\n';
    }
  }

 private:
  std::string levelToString(Level level) {
    switch (level) {
      case Level::DEBUG:
        return "DEBUG";
        break;
      case Level::INFO:
        return "INFO";
        break;
      case Level::ERROR:
        return "ERROR";
        break;
      case Level::WARNING:
        return "WARNING";
        break;
    }
  }
};

auto &logger = Logger::getInstance();

int sum(int a, int b) {
  logger.log("Зашли в метод sum.", Logger::Level::DEBUG);
  int res = a + b;
  logger.log("Суммируем числа " + std::to_string(a) + " "
                 + std::to_string(b) + ", res = " + std::to_string(res) + '.',
             Logger::Level::INFO);
  return a + b;
}  

int main() {
  logger.setLevel(Logger::Level::DEBUG);
  sum(10, 30);
  return 0;
}
