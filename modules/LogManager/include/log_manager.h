#ifndef FEDELE7008_LOG_MANAGER_LOG_MANAGER_H_
#define FEDELE7008_LOG_MANAGER_LOG_MANAGER_H_

#include <memory>
#include <string>
#include <filesystem>
#include <optional>

#include <spdlog/spdlog.h>

namespace service {
    using std::shared_ptr;
    using std::string;
    using std::filesystem::path;
    using std::optional;
    using spdlog::logger;

    /**
     * @brief Log management service.
     */
    class LogManager {
    private:
        /**
         * Shared logger pointer.
         */
        shared_ptr<logger> m_logger;

        /**
         * check if logger has been initialized.
         */
        bool m_initialized = false;

        /**
         * logger name.
         */
        string m_logger_name;

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
        LogManager(const LogManager &) = delete;

        /**
         * Disable assignment operator.
         * @brief Disable assignment operator.
         */
        LogManager &operator=(const LogManager &) = delete;

        /**
         * Disable move constructor.
         * @brief Disable move constructor.
         */
        LogManager(LogManager &&) = delete;

        /**
         * Disable move assignment operator.
         * @brief Disable move assignment operator.
         */
        LogManager &operator=(LogManager &&) = delete;

        /**
         * Gets the singleton instance of the LogManager.
         * @brief Returns the singleton instance of the LogManager.
         * @return The singleton instance of the LogManager.
         */
        static LogManager &getInstance() noexcept;

        /**
         * Initializes the log manager that is singleton throughout the program.
         * @brief Initializes the logger.
         * @exception std::runtime_error If the logger is already initialized.
         * @param logPath The path to the log file.
         */
        void initialize(const string &name, const optional<path> &logPath = {});

        /**
         * Un-initializes the log manager instance, uninitialize the log manager
         * at the end of program or end of each test cases.
         * @exception std::runtime_error If the logger is not initialized.
         * @brief Un-initializes the logger.
         */
        void uninitialize();

        /**
         * Gets the logger instance.
         * @brief Gets the logger.
         * @exception std::runtime_error If the logger is not initialized.
         * @return The logger.
         */
        shared_ptr<logger> getLogger();
    };
} // namespace service

#endif // FEDELE7008_LOG_MANAGER_LOG_MANAGER_H_
