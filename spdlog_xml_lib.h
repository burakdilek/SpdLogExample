#pragma once

#include <string>

namespace logger {

// Kütüphaneyi başlatır, konfigürasyon XML dosyasının yolu hard-coded olacaktır
// app_name parametresi verilmezse varsayılan "hexagon.log" kullanılır.
void init(const std::string &app_name = "hexagon");

// Log fonksiyonları - underlying spdlog logger'a delegasyon yapar
void trace(const std::string &msg);
void debug(const std::string &msg);
void info(const std::string &msg);
void warn(const std::string &msg);
void error(const std::string &msg);
void critical(const std::string &msg);

}
