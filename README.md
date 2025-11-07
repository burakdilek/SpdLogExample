# SpdLogExample

This project demonstrates using the C++ spdlog and TinyXML2 libraries in a fully offline, self-contained way.

## Features
- Log level is read from `config.xml` and can be changed at runtime
- Logs are written to `mylog.txt`
- Project runs offline using bundled `.so` and header files in the `lib/` directory
- Compiled and tested with GCC 8.5

## Project Structure

```
SpdLogExample/
├── main.cpp              # Application entry point
├── config.xml            # Log level configuration file
├── CMakeLists.txt        # CMake build configuration
├── lib/                  # Bundled libraries
│   ├── libtinyxml2.so    # TinyXML2 shared library
│   ├── libspdlog.so.*    # Spdlog shared libraries (optional for header-only usage)
│   ├── spdlog/           # Spdlog header files
│   └── tinyxml2.h        # TinyXML2 header file
└── build/                # Build output directory
```

## Build and Run

### 1. Building the Project

```bash
# Create build directory and configure with cmake
mkdir -p build && cd build
cmake ..
make

# Or with a single command:
cmake -B build && cmake --build build
```

### 2. Running the Application

```bash
# From build directory:
cd build
./spdlog_xml_example

# Or from project root:
./build/spdlog_xml_example
```

**Note:** Thanks to RPATH settings, there's no need to define `LD_LIBRARY_PATH`. The application automatically finds `.so` files in the `lib/` directory.

## Changing Log Level

You can dynamically update the log level while the program is running by editing the `<LogLevel>` value in `config.xml`:

```xml
<Config>
    <LogLevel>debug</LogLevel>
</Config>
```

**Supported log levels:**
- `trace`: Most detailed log level
- `debug`: Debugging information
- `info`: General informational messages (default)
- `warn`: Warning messages
- `error`: Error messages
- `critical`: Critical error messages

The program checks config.xml every 2 seconds and automatically updates the log level if changed.

## System Requirements

- **Compiler:** GCC 8.5 or higher (C++17 support required)
- **CMake:** 3.10 or higher
- **Operating System:** Linux (tested on Ubuntu 24.04 LTS)
- **Dependencies:** pthread (available as system library)

## Deploying to Another System

To deploy this project to another computer with GCC 8.5+:

1. **Copy the entire project folder** (especially include the `lib/` directory)
2. Follow the build steps above on the target system
3. No additional library installation needed (all dependencies are in `lib/`)

### Portability Notes

- **libtinyxml2.so**: Included in `lib/` directory, automatically found via RPATH
- **spdlog**: Used as header-only library, compiled into code during build
- **pthread**: Comes standard with Linux systems
- **Standard C++ libraries**: Included with GCC 8.5

## Libraries

- **[spdlog](https://github.com/gabime/spdlog)** - Fast C++ logging library (v1.11.0)
- **[TinyXML2](https://github.com/leethomason/tinyxml2)** - Lightweight XML parser

## License

This project is for demonstration/educational purposes. The included libraries are subject to their own licenses.
