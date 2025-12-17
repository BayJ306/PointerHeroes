# Hero Squad Manager & Battle Simulator

**A C-based RPG management system for the Kingdom of C-land**

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [File Format](#file-format)
- [Usage Guide](#usage-guide)
- [Tips and Tricks](#tips-and-tricks)
- [Credits](#credits)
- [Learning Outcomes](#learning-outcomes)

---

## Overview

The Hero Squad Manager is a turn-based RPG system that allows you to:
- Manage a squad of up to 100(you can add more heroes) heroes
- Calculate power scores based on character stats
- Simulate exciting 1v1 battles
- Search, sort, and filter your hero roster
- Save and load hero data from files

Built entirely in C using structs, arrays, and modular functions.

---

## Features

### Core Functionality
- **Hero Management**: Add, remove, view, search heroes
- **Power Calculation**: Automatic scoring system
- **Battle Simulation**: Turn-based combat with damage formulas
- **Sorting**: Rank heroes by power
- **Filtering**: View heroes by class
- **File I/O**: Load and save hero data

---

## Installation

### Prerequisites
- GCC compiler (or any C compiler)
- Terminal/Command Prompt
- Text editor (optional, for creating hero files)

### Compilation

**Linux/Mac:**
```bash
gcc -o main main.c -lm
```

**Windows (MinGW):**
```bash
gcc -o main.exe main.c -lm
```

**Alternative (without math library):**
```bash
gcc -o main main.c
```

### Running the Program

**Linux/Mac:**
```bash
./main
```

**Windows:**
```bash
main.exe
```

---

## Quick Start

### Option 1: Using Pre-made Heroes

1. Create a file named `heroes.txt` with the following content(probaly i already included it on the project.):
```
5
Thor Warrior 10 450 85 70 60
Merlin Mage 12 280 95 30 75
Artemis Archer 9 320 78 45 80
Astra Healer 8 350 40 60 50
Ragnar Warrior 11 480 90 75 55
```

2. Run the program
3. Select option **1** (Load from file)
4. Enter filename: `heroes.txt`
5. Select option **3** to view your squad
6. Select option **7** to simulate a battle!

### Option 2: Manual Hero Creation

1. Run the program
2. Select option **2** (Add new hero)
3. Enter hero details when prompted
4. Repeat to add more heroes
5. Select option **7** to battle!

---

## File Format

### Input/Output File Structure

**Format:**
```
N
name1 class1 level1 hp1 attack1 defense1 luck1
name2 class2 level2 hp2 attack2 defense2 luck2
...
nameN classN levelN hpN attackN defenseN luckN
```

**Example:**
```
3
Thor Warrior 10 450 85 70 60
Merlin Mage 12 280 95 30 75
Artemis Archer 9 320 78 45 80
```

### Field Specifications

| Field | Type | Range | Notes |
|-------|------|-------|-------|
| name | string | max 50 chars | No spaces (use underscores) |
| class | string | max 20 chars | Warrior, Mage, Healer, Archer, etc. |
| level | int | 1-20 typical | Affects power score |
| hp | int | 1-500 | Hit points |
| attack | int | 1-100 | Offensive power |
| defense | int | 0-100 | Damage reduction |
| luck | int | 0-100 | Random bonus in battles |

---

## Usage Guide

### Main Menu Options

```
1. Load heroes from file    - Import heroes from text file
2. Add a new hero           - Manually create a new hero
3. Remove a hero            - Delete hero from squad (by name or index)
4. Show all heroes          - Display complete roster table
5. Search hero by name      - Find specific hero (case-insensitive)
6. Show heroes by class     - Filter by class type
7. Sort heroes by power     - Rank from strongest to weakest
8. Simulate a battle        - Fight 1v1 between two heroes
9. Save heroes to file      - Export roster to text file
0. Exit                     - Quit the program
```

### Power Score Formula

```
power = level × 0.5 + attack/2 + defense/3 + hp/20
```

**Example:**
- Thor (Level 10, HP 450, Attack 85, Defense 70)
- Power = 10×0.5 + 85/2 + 70/3 + 450/20
- Power = 5 + 42.5 + 23.33 + 22.5 = **93.33**

### Battle Damage Formula

```
damage = max(1, attack - defense/2) + luckBonus
```

Where `luckBonus = random(0, luck/10)`

**Example:**
- Attacker: Attack 85, Luck 60
- Defender: Defense 30
- Base damage = 85 - 30/2 = 70
- Luck bonus = 0-6 (random)
- Total damage = 70-76

---

## Tips and Tricks

### Creating Balanced Heroes

**Warrior:** High HP and Defense, moderate Attack
```
Ragnar Warrior 11 480 90 75 55
```

**Mage:** High Attack, low Defense, moderate HP
```
Merlin Mage 12 280 95 30 75
```

**Archer:** Balanced stats, high Luck
```
Artemis Archer 9 320 78 45 80
```

**Healer:** High HP and Defense, low Attack
```
Astra Healer 8 350 40 60 50
```

### Battle Strategy

- **High Power ≠ Guaranteed Win** - Luck can create upsets!
- **Defense matters** - Reduces incoming damage significantly
- **HP is crucial** - Allows heroes to survive longer
- **Luck adds excitement** - Can swing battles either way

### File Management

- Keep backup hero files (e.g., `heroes_backup.txt`)
- Use descriptive filenames (e.g., `warrior_squad.txt`)
- Test with small files first (3-5 heroes)
- Validate file format before loading

---

## Credits

**Developed by:** PointerHeroes

**Team Members:**
- Võ Gia Bảo - ITCSIU24010

**Course:** C/C++ Programming Lab
**Institution:** International University - VNU-HCM
**Date:** December 2025

## License

This project is created for educational purposes as part of a C/C++ programming lab course.
Feel free to use and modify for learning purposes.

---

## Learning Outcomes

Through this project, you will master:
- Struct design and usage
- Array manipulation
- Function decomposition
- File I/O operations
- Control flow (loops, conditionals)
- Algorithm implementation (search, sort)
- Error handling strategies
- User interface design
- Software testing methodologies

---

**May your heroes defend C-land from segmentation faults and memory leaks! **

*Version 1.0 - December 2025*
