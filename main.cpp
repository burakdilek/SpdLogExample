#include <iostream>
#include <thread>
#include <chrono>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <tinyxml2.h>

using namespace tinyxml2;

spdlog::level::level_enum get_log_level_from_xml(const std::string& xml_path) {
    XMLDocument doc;
    if (doc.LoadFile(xml_path.c_str()) != XML_SUCCESS) {
        return spdlog::level::info; // Varsayılan seviye
    }
    XMLElement* root = doc.FirstChildElement("Config");
    if (!root) return spdlog::level::info;
    XMLElement* levelElem = root->FirstChildElement("LogLevel");
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

int main() {
    auto logger = spdlog::basic_logger_mt("file_logger", "mylog.txt");
    std::string config_path = "config.xml";
    spdlog::level::level_enum current_level = get_log_level_from_xml(config_path);
    logger->set_level(current_level);
    logger->info("Başlangıç log seviyesi: {}", spdlog::level::to_string_view(current_level));

    for (int i = 0; i < 20; ++i) {
        // Her 2 saniyede bir log seviyesi güncellenir
        spdlog::level::level_enum new_level = get_log_level_from_xml(config_path);
        if (new_level != current_level) {
            logger->set_level(new_level);
            logger->info("Log seviyesi değişti: {}", spdlog::level::to_string_view(new_level));
            current_level = new_level;
        }
        logger->trace("Trace mesajı {}", i);
        logger->debug("Debug mesajı {}", i);
        logger->info("Info mesajı {}", i);
        logger->warn("Warn mesajı {}", i);
        logger->error("Error mesajı {}", i);
        logger->critical("Critical mesajı {}", i);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    logger->info("Program sonlandı.");
    return 0;
}