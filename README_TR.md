# SpdLogExample / Logger Kütüphanesi

Bu proje, `spdlog` ve `tinyxml2` kullanarak **XML'den log seviyesi okuyan** ve **tek bir paylaşımlı kütüphane (.so)** olarak kullanılabilen bir logger kütüphanesi sunar.

Kütüphanenin adı: `liblogger.so`  
Kullanıcı tarafında görünen API: `logger` namespace'i ve `logger.h` header'ı.

## Özellikler
- Log seviyesi `config.xml` içindeki `<LogLevel>` alanından okunur.
- `config.xml` değiştirilince log seviyesi runtime'da güncellenir.
- Log dosyası adı:
  - Varsayılan: `hexagon.log` ( `logger::init()` parametresiz çağrılırsa )
  - Veya: `<app_name>.log` ( `logger::init("app_name")` çağrılırsa )
Bu kütüphaneyi kullanmak için ihtiyacın olan her şey bu repoda yer alır.

## Proje Yapısı (özet)

```text
SpdLogExample/
├── CMakeLists.txt        # CMake yapılandırması
├── config.xml            # Log seviyesi konfigürasyon dosyası
├── logger.h              # Kullanıcıların include edeceği header
├── spdlog_xml_lib.h      # İç implementasyon header'ı (logger.h bunu include eder)
├── spdlog_xml_lib.cpp    # logger kütüphanesinin implementasyonu
├── test_app.cpp          # Kütüphaneyi kullanan örnek uygulama
└── build/                # CMake build çıktıları (liblogger.so, test_app vb.)
```

## Derleme

Projeyi derlemek için:

```bash
cd /workspaces/SpdLogExample   # veya kendi klonladığın dizin
cmake -B build
cmake --build build
```

Bunun sonucunda:

- Kütüphane: `build/liblogger.so`
- Örnek uygulama: `build/test_app`

oluşur.

## Örnek Kullanım (test_app)

`test_app.cpp` içeriği basitçe:

```cpp
#include "logger.h"

int main() {
    // Uygulama adını vermezsen: hexagon.log
    // logger::init();

    // Uygulama adını açıkça vererek log dosyası ismini belirle
    logger::init("test_app");  // -> test_app.log

    logger::info("Test uygulaması başlatıldı");
    logger::warn("Uyarı logu");
    logger::error("Hata logu");
    logger::critical("Kritik log");

    return 0;
}
```

Çalıştırma:

```bash
cd /workspaces/SpdLogExample
LD_LIBRARY_PATH=build ./build/test_app
```

Çalışma dizininde `test_app.log` dosyası oluşur. Log seviyesi `config.xml`'deki `<LogLevel>` değerine göre filtrelenir.

## Kendi Uygulamalarında Kullanım

Kendi uygulamanda bu kütüphaneyi kullanmak için şu adımları izle:

1. Bu repodan şu dosyaları kendi projenine kopyala:
   - `build/liblogger.so`
   - `logger.h`
   - `spdlog_xml_lib.h`
   - `config.xml`

2. Kendi proje yapını örneğin şöyle ayarla:

   ```text
   my_app/
   ├── src/main.cpp
   ├── include/logger.h
   ├── include/spdlog_xml_lib.h
   ├── lib/liblogger.so
   └── config.xml
   ```

3. `main.cpp` içinde kütüphaneyi kullan:

   ```cpp
   #include "logger.h"

   int main() {
       // Varsayılan isim (hexagon.log) için:
       // logger::init();

       // Uygulama adına göre log dosyası:
       logger::init("benim_uygulamam"); // -> benim_uygulamam.log

       logger::info("Uygulama başladı");
       logger::warn("Uyarı mesajı");
       logger::error("Hata mesajı");
       logger::critical("Kritik hata");
       return 0;
   }
   ```

4. CMake ile entegre et (önerilen):

   ```cmake
   cmake_minimum_required(VERSION 3.10)
  project(MyApp)

   set(CMAKE_CXX_STANDARD 17)

   include_directories(${CMAKE_SOURCE_DIR}/include)
   link_directories(${CMAKE_SOURCE_DIR}/lib)

  add_executable(my_app src/main.cpp)

  target_link_libraries(my_app
       PRIVATE
           logger
   )
   ```

   Derleme ve çalışma:

   ```bash
   cd my_app
   cmake -B build
   cmake --build build

  LD_LIBRARY_PATH=lib ./build/my_app
   ```

## Log Seviyesini XML'den Değiştirme

`config.xml` dosyasında:

```xml
<Config>
    <LogLevel>debug</LogLevel>
</Config>
```

Desteklenen log seviyeleri:

- `trace`
- `debug`
- `info`  (varsayılan)
- `warn`
- `error`
- `critical`

Kütüphane, her log çağrısında `config.xml`'i okuyup seviye değiştiyse logger seviyesini günceller.

## Sistem Gereksinimleri

- **Derleyici:** GCC 8.5+ (C++17)
- **CMake:** 3.10+
- **İşletim Sistemi:** Linux (Ubuntu 24.04 LTS üzerinde test edildi)
- **Bağımlılıklar:**
  - `pthread` (sistem kütüphanesi)

## Kütüphaneler

- **spdlog** - Hızlı C++ log kütüphanesi (proje içinde header olarak gömülü)
- **TinyXML2** - Hafif XML parse kütüphanesi (kaynak kod proje içinde)

Bu proje, bu kütüphanelerin lisanslarına tabidir.
