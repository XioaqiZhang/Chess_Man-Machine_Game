## Build and Run (Ubuntu)

Dependencies:
- Qt5 Widgets
- CMake >= 3.10
- A C++ compiler (g++/clang++)

Install deps:

```bash
sudo apt update
sudo apt install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools cmake build-essential
```

Configure and build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build -j
```

Run the app:

```bash
./build/chess_app
```

# Chess_Man-Machine_Game
一款象棋游戏




