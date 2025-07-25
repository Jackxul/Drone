# Grid-Based UAV Path Planning Project

## 📌 Overview

This project implements several grid traversal algorithms (e.g., spiral, zigzag, zamboni, reverse-spiral) for UAV path planning, with energy-aware charging logic integrated. The project is written in **C** and built using **GNU Make**. It supports repeated simulation testing via shell scripting and uses **Git** for version control.

---

## 🛠️ Languages & Tools

- **C** – Main programming language
- **GNU Make** – Build system for compiling the project
- **Git** – Version control tool
- **Shell script** – For running multiple simulations/tests

---

## 🖥️ Supported Platforms

- Ubuntu
- macOS
- Linux distributions

---

## 📦 Installation Requirements

Before building and running the project, ensure the following packages are installed:

### ✅ Required Packages

- `build-essential` – Includes `gcc`, `g++`, `make`, etc.
- `git` – For version control
- `make` – For building the project
- `bash` – To run shell scripts (most Linux/macOS systems have this by default)

### 🐧 Ubuntu / Debian

```bash
sudo apt update
sudo apt install build-essential git make
```

## 🍎 MacOS(with Homebrew)

```bash
brew install git make gcc
```

### 📂 Project Structure
```plaintext
├── include/         # Header files categorized by module
│   ├── charging.h       # Charging-related functions
│   ├── common.h         # Common functions and parameters
│   ├── respiral.h       # Reverse spiral algorithm
│   ├── spiral.h         # Spiral traversal
│   ├── zigzag.h         # Zigzag traversal
│   └── zamboni.h        # Zamboni traversal
│
├── src/             # C source files
│   ├── charging.c       # Charging logic implementation
│   ├── common.c         # Shared utility functions
│   ├── respiral.c       # Reverse spiral logic
│   ├── spiral.c         # Spiral path algorithm
│   ├── zigzag.c         # Zigzag path algorithm
│   ├── zamboni.c        # Zamboni traversal implementation
│   └── main.c           # Main execution logic
│
├── build/           # Object files (.o)
├── exe/             # Executable output files
│
├── Makefile         # GNU Make build script
├── bfile.sh         # Shell script for running tests on all grid sizes
└── README.md        # Project documentation (this file)
```

🚀 Build & Run
To build the project, navigate to the project directory and run:

```bash
make grid="number" # Replace "number" with the grid size (e.g., 10, 20, 30)
make db=1 # This enables debug mode, which includes additional checks.
make clean # This removes executable and object files , but keeps the test data.
make clean_result # This removes all result files and executables file and object files.


```
### 🧩 Module Summary

| File            | Description                         |
| --------------- | ----------------------------------- |
| `charging.c/.h` | Handles charging-related logic      |
| `common.c/.h`   | Defines shared functions/parameters |
| `spiral.c/.h`   | Implements spiral traversal         |
| `respiral.c/.h` | Implements reverse spiral traversal |
| `zigzag.c/.h`   | Implements zigzag traversal         |
| `zamboni.c/.h`  | Implements zamboni-style traversal  |
| `main.c`        | Entry point for UAV simulation      |
| `bfile.sh`      | Shell script for repeated testing   |
| `Makefile`      | Automates build process             |

### 📌 Version Control
To initialize a Git repository, run the following commands in your terminal:

```bash
git init
git add .
git commit -m "Initial commit"
```

###✅ Git Workflow Example

1. Clone the repository

```bash
git clone git@github.com:Jackxul/Drone.git
cd Drone
```

2. Create and switch to a new feature branch

```bash
git checkout -b "new branch name"
```

3. After coding, check status and commit

```bash
git status
git add src/spiral.c
git commit -m "Improve spiral algorithm logic for better coverage"
```
4. Push your branch (⚠️ NOT to main)

```bash
git push origin "new branch name"
```
5. Open a Pull Request
   - Go to your repository on GitHub
   - Click on "Pull requests"
   - Click "New pull request"
   - Select your branch and compare it with `main`
   - Add a title and description, then click "Create pull request"
6. Review and merge the PR
7. After merging, delete the branch if no longer needed

```bash
git branch -d "new branch name"
```
### 📝 License



