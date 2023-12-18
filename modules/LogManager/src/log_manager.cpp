#include "log_manager.h"

#include <vector>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace service {
    using std::vector;
    using std::runtime_error;
    using spdlog::sink_ptr;
    using spdlog::sinks::stdout_color_sink_mt;
    using spdlog::sinks::basic_file_sink_mt;

    LogManager &LogManager::getInstance() noexcept {
        static LogManager instance;
        return instance;
    }

    void LogManager::initialize(const string &name, const optional<path> &logPath) {
        if (m_initialized)
            throw runtime_error("LogManager already initialized");

        vector<sink_ptr> sinks;
        bool useFileSink = logPath.has_value();

        auto consoleSink = std::make_shared<stdout_color_sink_mt>();
        consoleSink->set_level(spdlog::level::info);
        sinks.push_back(consoleSink);

        if (useFileSink) {
            auto fileSink = std::make_shared<basic_file_sink_mt>(logPath.value().relative_path(), true);
            fileSink->set_level(spdlog::level::trace);
            sinks.push_back(fileSink);
        }

        m_logger_name = name;
        m_logger = std::make_shared<logger>(m_logger_name, sinks.begin(), sinks.end());

        if (useFileSink)
            m_logger->flush_on(spdlog::level::trace);

        spdlog::register_logger(m_logger);
        m_initialized = true;

        m_logger->set_level(spdlog::level::trace);
        m_logger->trace("Log Manager initialized");
    }

    void LogManager::uninitialize() {
        if (!m_initialized)
            throw runtime_error("LogManager not initialized");

        m_logger->trace("Log Manager Uninitialized");
        spdlog::drop(m_logger_name);
        m_logger.reset();
        m_logger_name.clear();
        m_initialized = false;
    }

    shared_ptr<logger> LogManager::getLogger() {
        if (!m_initialized)
            throw runtime_error("LogManager not initialized");

        return m_logger;
    }

} // namespace service
