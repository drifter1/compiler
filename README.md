# compiler

![Compiler Design Steps](/assets/steps_dark.jpg#gh-dark-mode-only)
![Compiler Design Steps](/assets/steps_light.jpg#gh-light-mode-only)

This repository contains the code for a compiler implementation written in the C programming language that relies on the tools Flex and Bison. The target language is a [simple, C-like language](#simple-c-language).

# Prerequisites

- GCC (GNU Compiler Collection)
- Make
- Flex (derivative of Lex)
- Bison (derivative of Yacc)
- QtSpim (or any other MIPS32 Simulator)


# Basic Installation

## Linux

For Arch-based distributions:
```
sudo pacman -Syu
sudo pacman -S --needed base-devel
```

> [!NOTE]
> `base-devel` includes `gcc`, `make`, `flex`, `bison`, and other core development tools. Alternatively, you can install each separately.


For Debian-based distributions:
```
sudo apt update
sudo apt install build-essential flex bison
```

> [!NOTE]
> `build-essential` includes `gcc`, `make`, and other core build tools. Alternatively, you can install each separately.

For Fedora-based distributions:
```
sudo dnf makecache
sudo dnf group install development-tools
sudo dnf install flex flex-devel bison bison-devel
```

> [!NOTE]
> `development-tools` group includes `gcc`, `make`, and other core build tools. Alternatively, you can install each separately.


## Microsoft Windows

It is highly recommended that you use a Linux distribution instead, through any method you prefer.

Options include:

- Windows Subsystem for Linux (WSL), preferably version 2
- Docker or Podman containers
- Virtual Machines

## macOS

I am not very familiar with Macintosh systems.
However, it seems that you first need to install Apple's command-line developer tools, which will provide you with `make`, `clang` and `gcc` (via clang), as well as other development tools.
Next, install a package manager such as Homebrew (`brew`), through which you can then install `flex` and `bison`.

```
xcode-select --install
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install flex bison
```

## MIPS32 Emulation (QtSpim)

If you are on Microsoft Windows, macOS, or a Debian-based Linux distribution, you should be good to go with one of the [recent releases of QtSpim on SourceForge](https://sourceforge.net/projects/spimsimulator/files/).

For other Linux distributions, it is possible to install a version of QtSpim via Flatpak, which is sadly no longer under active maintenance, or consider using a container or virtual machine instead.


# Getting Started

## Building the compiler from source

Clone the repository and change into the directory:

```
git clone https://github.com/drifter1/compiler.git
cd compiler
```

To build the compiler simply type `make` in this directory.

By default, the executable will be located in the subdirectory *bin* and called *compiler*.


## Running the included examples

Examples are included in the *examples* directory.

By default, typing `make run` will compile *example1.c* from the *simple_c_examples* subdirectory using the compiled binary from `make`. It's essentially the same as:

```
./bin/compiler examples/simple_c_examples/example1.c
```

The execution of the compiler prints out parsing debugging information in the terminal console and also creates the *symtab_dump.out* and *revisit_dump.out* debugging files.


## Cleaning up the build files and binaries

To clean the build files and binary executable, you just have to type `make clean`.


## Cleaning up the run files

To clean the debugging files (with *.out* extension) after usage of the compiler with `make run` you just have to type `make clean-run`.


# Articles

A comprehensive tutorial series is also available, which covers most aspects of implementation.

The complete list of articles can be found [here](/docs/articles.md).

> [!IMPORTANT]
> Please be advised that significant changes have been made to the source code and repository (issue [#5](https://github.com/drifter1/compiler/issues/5)), meaning that the tutorial series and repository are no longer perfectly aligned. The tutorial series has also been discontinued. The final commit prior to the major overhaul is [7fbcd3f](https://github.com/drifter1/compiler/tree/7fbcd3f94851b5abfe7b1c7622102a621ca0f971). It should help you work your way through the series more easily, since every single article has its own folder.


# Simple C Language

The programming language is being explained [here](/docs/simple-c-language.md).

> [!NOTE]
> Please be advised that this text is still a work in progress.


# Status

- Machine Code generation in MIPS Assembly
- Optimizations in the compiler's source code
- Fixing errors, bugs, issues, ...
