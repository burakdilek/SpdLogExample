#include "logger.h"

int main() {
    // Uygulama adını doğrudan ver
    logger::init("test_app");

    logger::info("Test uygulaması başlatıldı");
    logger::warn("Uyarı logu");
    logger::error("Hata logu");
    logger::critical("Kritik log");

    return 0;
}
