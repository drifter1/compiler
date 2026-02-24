# compiler

![Compiler Design Steps](/assets/steps_dark.jpg#gh-dark-mode-only)
![Compiler Design Steps](/assets/steps_light.jpg#gh-light-mode-only)

This repository contains the code for a compiler implementation for a simple, C-like language that relies on the C tools Flex and Bison.

A comprehensive tutorial series is also available.

The project was unfortunately abandoned for over five years due to the maintainer's time constraints.

Due to the 2020 Steemit dispute, when the project was revitalized the tutorial series resumed on Hive instead.

> [!IMPORTANT]
> A major overhaul of the repository is currently underway (see open issue #5). Although the project had reached the machine code generation stage, improvements to the code base have necessitated a temporary return to the semantical analysis stage.

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

> [!NOTE]
> `base-devel` includes `gcc`, `make`, `flex`, `bison`, and other core development tools. Alternatively, you can install each separately.


For Debian-based distributions
```
sudo apt update
sudo apt install build-essential flex bison
```

> [!NOTE]
> `build-essential` includes `gcc`, `make`, and other core build tools. Alternatively, you can install each separately.

For Fedora-based distributions
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

Regarding MIPS32 simulation, note that there is a Flatpak package for *QtSpim* that appears to work just fine on Arch Linux.

If you are on Microsoft Windows, macOS, or a Debian-based Linux distribution, you should be good to go with one of the [recent releases of QtSpim on SourceForge](https://sourceforge.net/projects/spimsimulator/files/).


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

Examples are included in the *examples* subdirectory.

You can compile *example2.c* in the Simple-C language via:

```
./bin/compiler examples/simple_c_examples/example2.c
```

This will print out parsing debugging information in the terminal console and also create the *symtab_dump.out* and *revisit_dump.out* debugging files.

**terminal output:**
```
Declarations Node with 2 declarations
Declaration Node of data-type 1 for 1 names
Declaration Node of data-type 2 for 2 names
Assignment revisit for res at line 7
Statements Node with 1 statements
For Node with loop counter i
Initialize:
Assign Node of entry i
Assigning:
Constant Node of const-type 1 with value 0
Condition:
Relational Node of operator 1
Increment:
Increment Node of entry i being 0 0
For branch:
Statements Node with 4 statements
Assign Node of entry res
Assigning:
Function Call Node of operation with 2 parameters
Call parameters:
Reference Node of entry val
Reference Node of entry i
Assign Node of entry val
Assigning:
Reference Node of entry res
Function Call Node of print with 1 parameters
Call parameters:
Reference Node of entry res
Function Call Node of print with 1 parameters
Call parameters:
Constant Node of const-type 4 with value "\n"
Successful Parameter Check of operation
Function Declarations Node with 1 function declarations
Function Declaration Node of operation with ret_type 2 and 2 parameters
Parameters:
Parameter value of type 2
Parameter i of type 1
Function declarations:
Declarations Node with 1 declarations
Declaration Node of data-type 2 for 1 names
Function statements:
Statements Node with 1 statements
Assign Node of entry res
Assigning:
Arithmetic Node of operator 0 with result type 2
Return node:
Return Node of ret_type 2
Returning:
Reference Node of entry res
Parsing finished!
```

**symtab_dump.out**
```
------------ -------------- ------ ------------
Name         Type           Scope  Line Numbers
------------ -------------- ------ ------------
i            int              0     3    6    6    6    7    7    8    9 
val          real             0     4    7    8 
res          array of real    0     4    7    8    9 
operation    func ret real    0     7   14 
print        func ret void    0     9   10 
```

**revisit_dump.out**
```
------------ -------------
Identifier   Revisit Type
------------ -------------
```

## Cleaning up the build files and binaries

To clean the build files and binary executable, you just have to type `make clean`.

> [!NOTE]
> The above command does not remove debugging files such as *symtab_dump.out* and *revisit_dump.out*, as well as the assembly outputs (*.s* files), which are created when you use the compiler itself. These files need to be removed manually.

# Articles

The complete list of articles can be found [here](/docs/articles.md).

# Status

- Semantical Analysis pt.2 - Revisit Queue Usage (related to #5)
- Machine Code generation in MIPS Assembly (covered up to issue #5)
- Machine Code generation in MIPS Assembly (remaining cases)
- Optimizations in the compiler's source code
- Fixing errors, bugs, issues, ...
