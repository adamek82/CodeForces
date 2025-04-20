# CodeForces Solutions

This repository contains my solutions to Codeforces problems using C++. It uses CMake for building and follows a modular directory structure.

## Project Structure

```
├── .vscode/              # VSCode workspace settings
├── bin/                  # Compiled binaries
├── build/                # CMake build directory
├── include/              # Header files
│   ├── CodeForces.h
│   ├── FastVersionedMap.h
│   ├── LargestSubmatrix3_407D.h
│   └── ...
├── src/                  # Source files
│   ├── CodeForces.cpp    # Main entry and utilities
│   ├── LargestSubmatrix3_407D.cpp
│   └── ...
├── .gitignore
├── CMakeLists.txt        # CMake configuration
└── CodeForces.code-workspace
```

- **.vscode/**: VSCode workspace and launch configurations.
- **bin/**: Executable outputs.
- **build/**: Directory for CMake to place build artifacts.
- **include/**: Project-wide header files and problem-specific headers.
- **src/**: Implementation of solutions and main runner.
- **CMakeLists.txt**: Defines build targets and include paths.
- **CodeForces.code-workspace**: VSCode workspace file.

## Solved Problems

| Problem | Title                |
|---------|----------------------|
| 407D    | Largest Submatrix 3  |
