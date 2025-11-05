# SpdLogExample

This project demonstrates using the C++ spdlog and TinyXML2 libraries in a fully offline, self-contained way.

## Features
- Log level is read from the `config.xml` file and can be changed at runtime.
- Logs are written to `mylog.txt`.
- The project is prepared to run offline using bundled `.so` and header files inside the `lib/` directory.

## Project layout

- `main.cpp`: Application entry point
- `config.xml`: XML configuration file that contains the `<LogLevel>` element
- `lib/`: Contains bundled `.so` libraries and header files for spdlog and tinyxml2
- `CMakeLists.txt`: Build configuration that links against the bundled libraries

## Build and run

Run the following commands to build and run the example. The LD_LIBRARY_PATH ensures the bundled `.so` files are loaded before any system or conda libraries.

```sh
cmake -B build
cmake --build build
LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:./lib ./build/spdlog_xml_example
```

## Changing log level

Edit the `<LogLevel>` value in `config.xml` (e.g. `info`, `debug`, `error`, `trace`, `warn`, `critical`) and restart the program to apply the new level at runtime.

## Notes

- Ensure `lib/` contains both the shared libraries (`.so`) and the corresponding header files for spdlog and tinyxml2 so the project can be built and run offline.
- When copying this project to another machine, keep the `lib/` directory with the binaries and headers to preserve offline capability.
