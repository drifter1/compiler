# compiler

![Compiler Design Steps](/assets/steps_dark.jpg#gh-dark-mode-only)
![Compiler Design Steps](/assets/steps_light.jpg#gh-light-mode-only)

This repository contains the code for a compiler implementation written in the C programming language that relies on the tools Flex and Bison. The target language is a [simple, C-like language](#simple-c-language).

# Prerequisites

- GCC (GNU Compiler Collection)
- Make
- Flex (derivative of Lex)
- Bison (derivative of Yacc)
- Jansson library (for debugging purposes)
- MIPS32 Simulator (for original implementation)


# Basic Installation

## Linux

For Arch-based distributions:
```sh
sudo pacman -Syu
sudo pacman -S --needed base-devel jansson
```

> [!NOTE]
> `base-devel` includes `gcc`, `make`, `flex`, `bison`, and other core development tools. Alternatively, you can install each separately.


For Debian-based distributions:
```sh
sudo apt update
sudo apt install build-essential flex bison libjansson-dev
```

> [!NOTE]
> `build-essential` includes `gcc`, `make`, and other core build tools. Alternatively, you can install each separately.

For Fedora-based distributions:
```sh
sudo dnf makecache
sudo dnf group install development-tools
sudo dnf install flex flex-devel bison bison-devel jansson jansson-devel
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
Next, install a package manager such as Homebrew (`brew`), through which you can then install `flex`, `bison` and `jansson`.

```sh
xcode-select --install
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install flex bison jansson
```


# Getting Started

## Building the compiler from source

Clone the repository and change into the directory:

```sh
git clone https://github.com/drifter1/compiler.git
cd compiler
```

To build the compiler simply type `make` in this directory.

By default, the executable will be located in the subdirectory *bin* and called *compiler*.

>[!NOTE]
> `make` targets the default `make` target which is `all` and has the same effect as `make all`.


## Running the included examples

Examples are included in the *examples* directory.

By default, typing `make run` will compile *example1.c* from the *simple_c_examples* subdirectory using the compiled binary from `make`. It's essentially the same as:

```sh
./bin/compiler examples/simple_c_examples/example1.c
```

>[!NOTE]
> By default, the compiler also prints debugging information to the terminal console and creates debugging files with extensions *.out* and *.json*. Debugging can be disabled by setting the `DEBUG` flag to `0` in *include/compiler.h* or by adding the flag `-DDEBUG=0` to `gcc` compilation in the *Makefile*, which has the same effect.

### Compiler output example

The compiler output and debugging for *example1.c* can be seen [here](/docs/simple-example.md).


## Cleaning up the build files and binaries

To clean the build files and binary executable, you just have to type `make clean`.


## Cleaning up the run files

To clean the debugging files when using the compiler in `DEBUG` mode (the default setting), simply type `make clean-run` after `make run`.


# Advanced Usage

## Compiler Stage Selection

Rather than using the `make` or `make all` commands, the compiler can also be built using other targets that target a specific compilation stage. These are:

- `make lex`: perform only lexical analysis
- `make syntax`: perform up to syntax analysis
- `make semantic`: perform up to semantic analysis
- `make ir`: perform up to intermediate code generation

>[!NOTE]
> Since machine code generation is not yet implemented `make`, `make all` and `make ir` have the same effect.

## Debugging Options

Debugging is active by default.

It can be deactivated by setting the *include/compiler.h* flag `DEBUG` to `0`, or by providing the `-DDEBUG=0` flag to `gcc`.

When debugging is enabled, the header file includes the *include/debug.h* header, which contains all debugging options.

The main options are for disabling lexical analysis, symbol table analysis, abstract syntax tree analysis, scope analysis, context analysis and semantic analysis debugging, respectively.

Further options are available for lexical, symbol table and abstract syntax tree generation:

- By default, lexical analysis debugging disables comment and token output, whilst keeping the generation of the dump file enabled.

- By default, symbol table debugging prints a message on insertion and enables dump file generation.

- Abstract syntax tree debugging prints a message on node creation and enables JSON dump file generation by default.


## Error Handling

The compiler's default behavior is to not stop on the first encountered error.

This behavior can be changed by setting the *include/compiler.h* flag `STOP_ON_ERROR` to `1`.

Default settings permit up to `5` non-internal errors before terminating the compilation procedure. The `ALLOWED_ERRORS` flag can be changed to any desired value.


# Articles

A comprehensive tutorial series is also available, which should cover most aspects of the original implementation.

The complete list of articles can be found [here](/docs/articles.md).

> [!IMPORTANT]
> Please be advised that significant changes have been made to the source code and repository (issue [#5](https://github.com/drifter1/compiler/issues/5)), meaning that the tutorial series and repository are no longer perfectly aligned. The tutorial series has also been discontinued. It is planned for the repository to have helpful, detailed documentation instead. The final commit prior to the major overhaul is [7fbcd3f](https://github.com/drifter1/compiler/tree/7fbcd3f94851b5abfe7b1c7622102a621ca0f971). It should help you work your way through the series more easily, since every single article has its own folder.


# Simple C Language

The programming language is being explained [here](/docs/simple-c-language.md).


# Current Status

- Debugging and comprehensive testing
- Implementation of any overlooked syntax or semantic checks
- Optimizations and enhancements in the compiler's source code

# Next Steps

- Machine code generation (Most likely in RISC-V assembly language, rather than MIPS, which was originally the target)