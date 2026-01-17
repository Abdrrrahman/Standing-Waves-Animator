# Standing Waves Animator

A real-time physics simulation of standing waves written in C using raylib. This project visualizes wave interference patterns through superposition, demonstrating fundamental wave physics concepts.

Watch the full development process: [Video](https://youtu.be/16pRHwdSqeE?si=wQxhkm2gZd8hZeIQ)

## About

This simulator demonstrates **standing wave formation** through the interference of two traveling waves moving in opposite directions. The visualization shows:

* Wave superposition in real-time
* Nodes and antinodes formation
* Configurable wave parameters (amplitude, frequency, tension)
* Smooth 60+ FPS rendering

![Image](https://github.com/user-attachments/assets/03f604bf-5f98-43e2-b3d7-0aace9691f6c)

![gif](https://github.com/user-attachments/assets/e9718293-3930-4289-930f-f236b85cae1e)

![gif](./attachments/standing_gif3.gif)

### Physics Background

Standing waves occur when two identical waves traveling in opposite directions interfere. The simulator uses the wave equation:

```
y(x,t) = 2A × sin(kx) × cos(ωt)
```

Where:
* `A` = amplitude (200 pixels, amplified by 5.5×)
* `k` = wave number (2π/λ)
* `ω` = angular frequency (2πf)
* `x` = position along string
* `t` = time (GetTime())

The wave velocity is calculated using: `v = √(T/μ)` where T is tension and μ is linear density.

## Requirements

All platforms need:
* **CMake 3.25+**
* **C compiler** (GCC, Clang, or MSVC)
* **Git** (for cloning with submodules)

Raylib is included as a submodule and built automatically from source.

## Getting Started

### Clone the Repository

**Important:** This project uses raylib as a git submodule. You must clone with submodules:

```bash
git clone --recurse-submodules https://github.com/Abdrrrahman/Standing-Waves.git
cd Standing-Waves
```

**If you already cloned without `--recurse-submodules`:**

```bash
cd Standing-Waves
git submodule update --init --recursive
```

## Building and Running

### Windows (Visual Studio or MinGW)

#### Prerequisites

Install one of the following:

**Option A: Visual Studio**
* Download and install [Visual Studio 2019+](https://visualstudio.microsoft.com/downloads/)
* During installation, select "Desktop development with C++" workload
* Install [CMake](https://cmake.org/download/) and check "Add CMake to system PATH"

**Option B: MinGW**
* Download MinGW-w64 from [winlibs.com](https://winlibs.com/)
* Extract and add to PATH
* Install [CMake](https://cmake.org/download/) and check "Add CMake to system PATH"

#### Build

**Using Visual Studio:**

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

**Using MinGW:**

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

#### Run

```bash
# In the build directory
.\Release\standing_waves.exe

# or for MinGW:
.\standing_waves.exe
```

**No external DLLs required** - everything is statically linked!

### macOS

#### Prerequisites

```bash
# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install CMake
brew install cmake

# Install Xcode Command Line Tools
xcode-select --install
```

#### Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

#### Run

```bash
./standing_waves
```

If you get a permissions error:

```bash
chmod +x standing_waves
./standing_waves
```

### Linux (Ubuntu / Debian / Fedora / Arch)

#### Prerequisites

**Ubuntu/Debian:**

```bash
sudo apt update
sudo apt install build-essential cmake git
```

**Fedora/RHEL:**

```bash
sudo dnf install gcc gcc-c++ cmake make git
```

**Arch:**

```bash
sudo pacman -S base-devel cmake git
```

#### Build

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)  # Uses all CPU cores for faster build
```

#### Run

```bash
./standing_waves
```

## Usage

The simulation runs automatically when launched. Current parameters are defined in the code:

* **Window Size**: 1280×720 pixels
* **Target FPS**: 60 (smooth animation)
* **String Length**: 800 pixels
* **String Density**: 0.00013 kg/m
* **Tension**: 275 N
* **Amplitude**: 200 pixels
* **Visual Amplifier**: 5.5× (for better visibility)
* **Number of Loops**: 2 (second harmonic)
* **Point Step**: 0.25 pixels (very smooth rendering)

### Modifying Parameters

Edit `src/main.c` in the `GetInputs()` and `InitString()` functions:

```c
void InitString(struct String *p_string)
{
    p_string->length = 800;        // String length in pixels
    p_string->density = 0.00013;   // Linear density (kg/m)
}

void GetInputs(struct PropagatingWave *p_pWave)
{
    p_pWave->amplitude = 200;      // Base amplitude
    p_pWave->num_loops = 2;        // Harmonic number (1=fundamental, 2=2nd harmonic, etc.)
    p_pWave->tension = 275;        // String tension in Newtons
}
```

You can also adjust in `main()`:

```c
SetTargetFPS(60);                  // Frame rate (60, 120, 144)
double pointStep = 0.25;           // Point density (lower = smoother but slower)
double amplifier = 5.5;            // Visual amplification factor
```

Rebuild after changes:

```bash
cd build
cmake --build .
```

## How It Works

1. **Initialization**:
   * `InitString()` sets up the virtual string with physical properties (length, density)
   * `GetInputs()` configures wave parameters (amplitude, harmonics, tension)
   * `CalculateDerives()` computes derived values (velocity, frequency, wavelength, wave number)

2. **Wave Physics**:
   * Velocity: `v = √(T/μ)` where T = tension, μ = linear density
   * Frequency: `f = (n/2L) × v` where n = harmonic number, L = string length
   * Wavelength: `λ = 2L/n`
   * Wave number: `k = 2π/λ`
   * Angular frequency: `ω = 2πf`

3. **Rendering Loop**:
   * Samples the wave at points every `pointStep` pixels (0.25 by default)
   * Calculates amplitude at each point: `new_amp = 2A × sin(kx)`
   * Applies time-based oscillation: `y = new_amp × cos(ωt) × amplifier`
   * Draws lines between consecutive points for smooth curves
   * Runs at 60 FPS for smooth, consistent motion

4. **Visualization**:
   * Dark gray horizontal line represents the string at rest
   * White wave shows the standing wave pattern
   * The wave oscillates vertically while nodes remain stationary

### Key Functions

* `InitString()` — Configures string physical properties and screen boundaries
* `GetInputs()` — Sets wave parameters (amplitude, harmonics, tension)
* `CalculateDerives()` — Computes frequency, wavelength, angular frequency, and wave number using physics formulas
* Main loop — Renders wave in real-time using `GetTime()` for smooth animation

## Project Structure

```
Standing-Waves/
├── external/
│   └── raylib/              # raylib library (git submodule)
├── src/
│   └── main.c               # Main simulation code
├── build/                   # Build directory (generated)
├── CMakeLists.txt           # Build configuration
├── LICENSE.txt              # MIT License
└── README.md                # This file
```

## Troubleshooting

### Build Issues

**"CMake not found"**
* Make sure CMake is installed and added to PATH
* Restart your terminal after installation
* Verify: `cmake --version`

**"Compiler not found"** (Windows)
* Verify Visual Studio or MinGW is properly installed
* For VS: Run from "Developer Command Prompt for VS"
* For MinGW: Ensure MinGW bin folder is in PATH

**"raylib not found" or "CMakeLists.txt missing in external/raylib"**
* You forgot to clone with `--recurse-submodules`
* Fix it: `git submodule update --init --recursive`

**Linker errors**
* Try cleaning the build: `rm -rf build/` then rebuild
* Ensure CMake version is 3.25 or higher: `cmake --version`

### Runtime Issues

**Window doesn't appear**
* Check if another instance is running
* Try running from command line to see error messages
* On Linux, ensure X11 libraries are installed

**Low framerate**
* The target is 60 FPS for smooth animation across all systems
* Lower `pointStep` value creates more points (smoother but slower)
* Increase `pointStep` from 0.25 to 0.5 or 1.0 for better performance on older hardware
* You can increase FPS for high-refresh displays: change `SetTargetFPS(60)` to `SetTargetFPS(120)` or `SetTargetFPS(144)`

## Educational Purpose

This project demonstrates:

* **Physics**: Standing wave formation, wave superposition, harmonics
* **Mathematics**: Trigonometric functions, wave equations
* **Programming**: Real-time graphics, data structures, build systems
* **Graphics**: Line rendering, coordinate systems, frame timing

Perfect for:
* Physics students learning wave mechanics
* Programmers learning graphics programming
* Understanding CMake project structure
* Cross-platform C development

## Contributing

Contributions are welcome! Ideas:

* Add UI controls (sliders) for real-time parameter adjustment
* Implement harmonic selection (n=1,2,3...) without recompilation
* Add different boundary conditions (free end vs fixed end)
* Display wave properties on-screen (frequency, wavelength, velocity)
* Add color gradients to visualize amplitude
* Export wave data to CSV for analysis
* Implement sound generation matching the frequency
* Add multiple strings with different properties

## License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.

## Acknowledgments

* **raylib** by Ramon Santamaria - Excellent graphics library for educational projects
* **Professor Hassan Ramadan, Dr. Mahmoud Mouneer, Dr. Mohamed Ismail** - For teaching the fundamental physics concepts, wave mechanics and their support
* **All Teaching Assistants** - For their support and encouragement
* Inspired by Physics II coursework in the Faculty of Computer and Information Sciences at Ain Shams University

---

*Developed as part of Physics II coursework - learning wave mechanics and applying programming to visualize physical phenomena.*