#ifndef FEDELE7008_LOG_MANAGER_LOG_MANAGER_H_
#define FEDELE7008_LOG_MANAGER_LOG_MANAGER_H_

#include <memory>
#include <string>
#include <filesystem>

#include <spdlog/spdlog.h>

namespace service {
using std::shared_ptr;
using std::string;
using std::filesystem::path;
using spdlog::logger;

/**
 * @brief Log management service.
 */
class LogManager {
private:
    /**
     * Shared logger pointer.
     */
    static shared_ptr<logger> m_logger;

    /**
     * Private constructor to prevent instantiation.
     * @brief private constructor.
     */
    explicit LogManager() = default;

public:
    /**
     * Public destructor with default implementation.
     * @brief Default destructor.
     */
    virtual ~LogManager() = default;

    /**
     * Disable copy constructor.
     * @brief Disable copy constructor.
     */
    LogManager(const LogManager&) = delete;

    /**
     * Disable assignment operator.
     * @brief Disable assignment operator.
     */
    LogManager& operator=(const LogManager&) = delete;

    /**
     * Disable move constructor.
     * @brief Disable move constructor.
     */
    LogManager(LogManager&&) = delete;

    /**
     * Disable move assignment operator.
     * @brief Disable move assignment operator.
     */
    LogManager& operator=(LogManager&&) = delete;

    /**
     * Gets the singleton instance of the LogManager.
     * @brief Returns the singleton instance of the LogManager.
     * @return The singleton instance of the LogManager.
     */
    static LogManager& getInstance();

    /**
     * Initializes the logger.
     * @brief Initializes the logger.
     * @param logPath The path to the log file.
     */
    void initialize(path &logPath);

};
} // namespace service

#endif // FEDELE7008_LOG_MANAGER_LOG_MANAGER_H_
