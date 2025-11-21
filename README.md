# SpdLogExample / Logger Library

This project provides a logger library built on top of `spdlog` and `tinyxml2`. 
It reads the log level from an XML file and exposes a simple C++ API through a shared library (`.so`).

Library binary name: `liblogger.so`  
Public API: `logger` namespace via the `logger.h` header.

## Features
- Log level is read from `config.xml` (`<LogLevel>` element).
- When `config.xml` changes, the log level is updated at runtime.
- Log file name:
  - Default: `hexagon.log` (if `logger::init()` is called without parameters)
  - Or: `<app_name>.log` (if `logger::init("app_name")` is used)
- Fully offline: all required sources and headers are in this repo.

## Project Structure (overview)

```text
SpdLogExample/
├── CMakeLists.txt        # CMake configuration
├── config.xml            # Log level configuration file
├── logger.h              # Public header to include in user code
├── spdlog_xml_lib.h      # Internal implementation header (included by logger.h)
├── spdlog_xml_lib.cpp    # Logger library implementation
├── test_app.cpp          # Example application using the library
└── build/                # CMake build outputs (liblogger.so, test_app, ...)
```

## Build

To build the project:

```bash
cd /workspaces/SpdLogExample   # or your clone path
cmake -B build
cmake --build build
```

This produces:

- Library: `build/liblogger.so`
- Example application: `build/test_app`

## Example Usage (test_app)

`test_app.cpp` is a minimal example:

```cpp
#include "logger.h"

int main() {
    // Without app name: default hexagon.log
    // logger::init();

    // With explicit app name, controls log file name
    logger::init("test_app");  // -> test_app.log

    logger::info("Test application started");
    logger::warn("Warning log");
    logger::error("Error log");
    logger::critical("Critical log");

    return 0;
}
```

Run:

```bash
cd /workspaces/SpdLogExample
LD_LIBRARY_PATH=build ./build/test_app
```

This creates `test_app.log` in the working directory. The log level is filtered according to the `<LogLevel>` value in `config.xml`.

## Using the Library in Your Own Application

To use this logger library in your own application:

1. Copy the following files from this repo into your project:
   - `build/liblogger.so`
   - `logger.h`
   - `spdlog_xml_lib.h`
   - `config.xml`

2. Example project layout:

   ```text
   my_app/
   ├── src/main.cpp
   ├── include/logger.h
   ├── include/spdlog_xml_lib.h
   ├── lib/liblogger.so
   └── config.xml
   ```

3. Use the library in `main.cpp`:

   ```cpp
   #include "logger.h"

   int main() {
       // Use default name (hexagon.log):
       // logger::init();

       // Or define an application-specific log file:
       logger::init("my_app"); // -> my_app.log

       logger::info("Application started");
       logger::warn("Warning message");
       logger::error("Error message");
       logger::critical("Critical error");
       return 0;
   }
   ```

4. Integrate with CMake (recommended):

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

   Build and run:

   ```bash
  cd my_app
   cmake -B build
   cmake --build build

  LD_LIBRARY_PATH=lib ./build/my_app
   ```

## Changing Log Level via XML

In `config.xml`:

```xml
<Config>
    <LogLevel>debug</LogLevel>
</Config>
```

Supported log levels:

- `trace`
- `debug`
- `info`  (default)
- `warn`
- `error`
- `critical`

On each logging call, the library re-reads `config.xml` and updates the logger level if it has changed.

## System Requirements

- **Compiler:** GCC 8.5+ (C++17)
- **CMake:** 3.10+
- **Operating System:** Linux (tested on Ubuntu 24.04 LTS)
- **Dependencies:**
  - `pthread` (system library)

## Libraries

- **spdlog** – Fast C++ logging library (embedded as headers in this project)
- **TinyXML2** – Lightweight XML parser (source code included in this project)

This project is subject to the licenses of these libraries.
