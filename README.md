# QT Study

A simple Qt6 application with the following components:
- Main frame
- Menu bar
- Toolbar
- Tree view docked on the left side
- Drawing view as main content

## Building the Application

### Prerequisites
- Qt6 development libraries
- CMake 3.16 or higher
- C++ compiler with C++17 support

### Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running

After building, you can run the application:

```bash
./QTStudy
```

## Features

1. **Main Frame**: Standard application window with title "QT Study"
2. **Menu Bar**: Contains File, Edit, View, and Help menus
3. **Toolbar**: Contains common actions like New, Open, Cut, Copy, Paste
4. **Tree View Dock**: Docked on the left side showing a hierarchical navigation structure
5. **Drawing View**: Central area where you can draw by clicking and dragging the mouse

## Usage

- Click and drag in the main drawing area to draw
- Use the menus and toolbar for common actions
- The tree view on the left provides navigation (currently static sample data)