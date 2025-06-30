# 🎮 Cub3D - A 3D Maze Game using Ray-Casting

![Cub3D Demo](https://img.shields.io/badge/42-Project-blue)
![C](https://img.shields.io/badge/Language-C-brightgreen)
![MinilibX](https://img.shields.io/badge/Graphics-MinilibX-orange)

A **3D first-person perspective maze game** built from scratch using **ray-casting principles** and the **MinilibX graphics library**. This project recreates the classic Wolfenstein 3D-style rendering engine in C.

## 👥 Authors

- **Lucas Inasci** - [@luinasci](https://github.com/luinasci)
- **João Colognesi** - [@jocologne](https://github.com/jocologne)

*Developed as part of the 42 School curriculum*

## 🎯 Project Overview

Cub3D creates a realistic 3D graphical representation of a maze interior using ray-casting techniques. The project implements a complete 3D rendering engine that can display textured walls, handle player movement, and create an immersive first-person experience.

## ✨ Features

### 🎮 Mandatory Features
- **3D Ray-casting Engine**: Real-time 3D maze rendering from a first-person perspective
- **Textured Walls**: Different wall textures based on cardinal directions (North, South, East, West)
- **Player Controls**:
  - `W`, `A`, `S`, `D` - Move through the maze
  - `←`, `→` Arrow keys - Look left and right
  - `ESC` - Exit the game
- **Customizable Colors**: Independent floor and ceiling color configuration
- **Map Parsing**: Support for `.cub` format map files with validation
- **Smooth Window Management**: Proper handling of window events and clean exit

### 🚀 Bonus Features
- **Wall Collisions**: Realistic collision detection system
- **Interactive Minimap**: Real-time overhead view of the maze
- **Animated Doors**: Doors that can be opened and closed (`E` key)
- **Animated Sprites**: Fire sprites with frame-based animation
- **Mouse Look**: Rotate view with mouse movement
- **Enhanced Graphics**: Improved visual effects and rendering

## 🗺️ Map Format

The game uses `.cub` files to define the maze layout and textures:

```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm  
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm
F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111111111011100000010001
11111111111111111111111111111
```

### Map Legend:
- `0` - Empty space
- `1` - Wall
- `N/S/E/W` - Player starting position and orientation
- `D` - Door (bonus feature)

## 🛠️ Installation & Usage

### Prerequisites
- GCC compiler
- Make
- X11 development libraries (Linux)
- MinilibX library

### Building the Project
```bash
# Clone the repository
git clone https://github.com/luinasci/cub3d.git
cd cub3d

# Compile the project
make

# Run with a map file
./cub3D maps/test.cub
```

### Available Make Targets
- `make` - Compile the project
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Recompile everything

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` `→` | Rotate view |
| `E` | Interact with doors |
| `F` | Shoot fireball |
| `ESC` | Exit game |
| `Mouse` | Look around (bonus) |

## 🏗️ Technical Implementation

### Ray-Casting Algorithm
The project implements a **Digital Differential Analyzer (DDA)** algorithm for ray-casting:
1. Cast rays from player position through each screen column
2. Calculate wall intersections using DDA
3. Determine wall height based on distance
4. Apply appropriate wall texture based on hit side
5. Render floor and ceiling with specified colors

### Graphics Pipeline
- **MinilibX Integration**: Low-level graphics library for rendering
- **Texture Mapping**: XPM format textures mapped to wall surfaces
- **Frame Buffer**: Direct pixel manipulation for optimal performance
- **Event Handling**: Keyboard and mouse input processing

### Memory Management
- Comprehensive memory leak prevention
- Proper cleanup of graphics resources
- Valgrind-tested memory safety
- MinilibX resource management

## 📁 Project Structure

```
cub3d/
├── includes/          # Header files
├── src/              # Core source files
│   ├── main.c
│   ├── init.c
│   ├── events.c
│   ├── ray_cast.c
│   ├── texture_loader.c
│   ├── draw.c
│   └── ...
├── utils/            # Utility functions
├── libft/            # Custom C library
├── mlx/              # MinilibX graphics library
├── maps/             # Sample map files
├── textures/         # Game textures
└── Makefile
```

## 🧪 Testing

The project includes comprehensive testing:
- **Map Validation**: Invalid map detection and error handling
- **Memory Testing**: Valgrind leak detection with suppressions
- **Input Validation**: Robust error handling for malformed files
- **Performance Testing**: Smooth 60+ FPS rendering

## 📚 Learning Outcomes

This project provided hands-on experience with:
- **3D Graphics Programming**: Ray-casting algorithms and 3D mathematics
- **Game Development**: Real-time rendering and game loop architecture
- **System Programming**: Low-level graphics APIs and memory management
- **Mathematical Concepts**: Vector mathematics, trigonometry, and linear algebra
- **Optimization**: Performance optimization for real-time graphics

## 🎯 42 School Project Requirements

✅ **Mandatory Part**
- 3D maze representation using ray-casting
- Wall textures varying by direction
- Floor and ceiling color configuration
- Player movement and rotation controls
- Map file parsing with validation
- Clean window management and program exit

✅ **Bonus Part**
- Wall collision detection
- Minimap system
- Interactive doors
- Animated sprites
- Mouse look controls

## 🤝 Contributing

This project was developed as part of the 42 School curriculum. While it's primarily for educational purposes, feedback and suggestions are welcome!

## 📄 License

This project is part of the 42 School curriculum and follows the school's academic guidelines.

---

*"In the world of 3D graphics, ray-casting opened the door to immersive gaming experiences. This project recreates that magic, one ray at a time."*
