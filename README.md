# My Awesome Snake Game (myawesomesnakegame)

A simple clone of the classic Snake game, built in C using the Raylib library.

## Requirements

To build and run this project, you will need:

* **macOS:** (Tested on Apple Silicon with Homebrew)
* **C Compiler:** Such as Clang (usually included with Xcode Command Line Tools).
* **CMake:** Version 3.15 or higher (`brew install cmake`).
* **Raylib Library:** Installed via Homebrew (`brew install raylib`).

## Building

Follow these steps in your terminal to compile the game:

1.  **Clone the repository** (if you haven't already):
    ```bash
    git clone https://github.com/proferret/myawesomesnakegame
    cd myawesomesnakegame
    ```

2.  **Create and navigate to the build directory**:
    ```bash
    mkdir build && cd build
    ```

3.  **Configure the project using CMake**:
    ```bash
    cmake ..
    ```
    *(Note: This project's `CMakeLists.txt` is configured to use Raylib paths installed by Homebrew at `/opt/homebrew`. If you have a different setup, you might need to adjust `CMakeLists.txt` or use `-DCMAKE_PREFIX_PATH` when running `cmake`.)*

4.  **Compile the project**:
    ```bash
    cmake --build .
    ```

## Running

After a successful build, the executable `myawesomesnakegame` will be located inside the `build` directory. To run it:

```bash
./myawesomesnakegame
