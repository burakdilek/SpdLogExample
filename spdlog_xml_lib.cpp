#include "spdlog_xml_lib.h"

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <tinyxml2.h>

using namespace tinyxml2;

namespace {

// Hard-coded config path
constexpr const char *CONFIG_PATH = "config.xml";

std::shared_ptr<spdlog::logger> g_logger;
std::mutex g_logger_mutex;
std::string g_log_file_name = "hexagon.log";

spdlog::level::level_enum get_log_level_from_xml(const std::string &xml_path) {
    XMLDocument doc;
    if (doc.LoadFile(xml_path.c_str()) != XML_SUCCESS) {
        return spdlog::level::info; // Varsayılan seviye
    }
    XMLElement *root = doc.FirstChildElement("Config");
    if (!root) return spdlog::level::info;
    XMLElement *levelElem = root->FirstChildElement("LogLevel");
    if (!levelElem) return spdlog::level::info;
    std::string level = levelElem->GetText() ? levelElem->GetText() : "info";
    if (level == "trace") return spdlog::level::trace;
    if (level == "debug") return spdlog::level::debug;
    if (level == "info") return spdlog::level::info;
    if (level == "warn") return spdlog::level::warn;
    if (level == "error") return spdlog::level::err;
    if (level == "critical") return spdlog::level::critical;
    return spdlog::level::info;
}

void ensure_logger_initialized() {
    std::lock_guard<std::mutex> lock(g_logger_mutex);
    if (!g_logger) {
        auto logger = spdlog::basic_logger_mt("file_logger", g_log_file_name);
        auto level = get_log_level_from_xml(CONFIG_PATH);
        logger->set_level(level);
        logger->info("Logger initialized with level: {}",
                     spdlog::level::to_string_view(level));
        g_logger = std::move(logger);
    } else {
        // Her çağrıda konfigürasyonu güncelle
        auto level = get_log_level_from_xml(CONFIG_PATH);
        if (level != g_logger->level()) {
            g_logger->set_level(level);
            g_logger->info("Log level changed to: {}",
                           spdlog::level::to_string_view(level));
        }
    }
}

} // namespace

namespace logger {

void init(const std::string &app_name) {
    {
        std::lock_guard<std::mutex> lock(g_logger_mutex);
        if (!app_name.empty()) {
            g_log_file_name = app_name + ".log";
        }
    }
    ensure_logger_initialized();
}

void trace(const std::string &msg) {
    ensure_logger_initialized();
    g_logger->trace(msg);
}

void debug(const std::string &msg) {
    ensure_logger_initialized();
    g_logger->debug(msg);
}

void info(const std::string &msg) {
    ensure_logger_initialized();
    g_logger->info(msg);
}

void warn(const std::string &msg) {
    ensure_logger_initialized();
    g_logger->warn(msg);
}

void error(const std::string &msg) {
    ensure_logger_initialized();
    g_logger->error(msg);
}

void critical(const std::string &msg) {
    ensure_logger_initialized();
    g_logger->critical(msg);
}

} // namespace logger
