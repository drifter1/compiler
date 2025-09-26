# compiler

![Compiler Design Steps](/assets/steps_dark.jpg#gh-dark-mode-only)
![Compiler Design Steps](/assets/steps_light.jpg#gh-light-mode-only)

This repository contains the code for a compiler implementation for a simple, C-like language that relies on the C tools Flex and Bison.

A comprehensive tutorial series is also available.

The project was unfortunately abandoned for over five years due to the maintainer's time constraints.

Due to the 2020 Steemit dispute, when the project was revitalized the tutorial series resumed on Hive instead.

# Prerequisites

- GCC (GNU Compiler Collection)
- Make
- Flex (derivative of Lex)
- Bison (derivative of Yacc)
- QtSpim (MIPS32 Simulator)


# Basic Installation

## Linux

For Arch-based distributions:
```
sudo pacman -Syu
sudo pacman -S --needed base-devel
```

**Note**: `base-devel` includes `gcc`, `make`, `flex`, `bison`, and other core development tools. Alternatively, you can install each separately.

For Debian-based distributions
```
sudo apt update
sudo apt install build-essential flex bison
```

**Note**: `build-essential` includes `gcc`, `make`, and other core build tools. Alternatively, you can install each separately.

For Fedora-based distributions
```
sudo dnf makecache
sudo dnf group install development-tools
sudo dnf install flex flex-devel bison bison-devel
```

**Note**: `development-tools` group includes `gcc`, `make`, and other core build tools. Alternatively, you can install each separately.

## Windows

It is highly recommended that you use a Linux distribution instead, through any method you prefer.

Options include:

- Windows Subsystem for Linux (WSL), preferably version 2
- Docker or Podman containers
- Virtual Machines

## MacOS

I am not very familiar with Macintosh systems.
However, it seems that you first need to install Apple's command-line developer tools, which will provide you with `make`, `clang` and `gcc` (via clang), as well as other development tools.
Next, install a package manager such as Homebrew (`brew`), through which you can then install `flex` and `bison`.

```
xcode-select --install
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install flex bison
```


# Articles

The complete list of articles can be found [here](/docs/articles.md).


# Next Up

- Machine Code generation in MIPS Assembly (remaining cases)
- Optimizations in the compiler's source code
