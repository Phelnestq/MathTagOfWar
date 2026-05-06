# MathTagOfWar 🧮⚔️

A terminal-based math competition game for children built in C++ using object-oriented programming. Players compete in a tug-of-war by answering math questions — answer correctly and you pull the rope, answer wrong and you get pulled back.

> **Status:** 🚧 In active development — core game logic and question engine are functional. ASCII tug-of-war display and computer opponent AI are planned for upcoming releases.

---

## What it does

MathTagOfWar turns mental arithmetic into a competitive game. Two contestants face off: a math question appears on screen, both players race to answer before the timer runs out. A correct answer adds pulling strength; a wrong answer weakens you. The first player to pull their opponent fully across the line wins.

It is designed to make mathematics engaging and competitive for children from primary school through to university level.

---

## Game modes

| Mode | Description |
|------|-------------|
| **1 Player** | Solo practice mode — answer questions against the clock |
| **2 Players (Local)** | Two human players compete on the same keyboard |
| **Player vs Computer** | Face off against a computer opponent *(coming soon)* |

---

## Difficulty levels

Players select their difficulty before the game starts, based on education level:

| Level | Target audience | Example topics |
|-------|----------------|----------------|
| **Primary Lower** | Ages 6–9 | Addition, subtraction, basic multiplication |
| **Primary Upper** | Ages 10–12 | Long multiplication, division, fractions |
| **Secondary** | Ages 13–18 | Algebra, geometry, percentages, powers |
| **University** | Age 18+ | Calculus, statistics, linear algebra |

---

## Gameplay rules

1. Players choose game mode and difficulty level at startup
2. A math question appears on screen with a countdown timer
3. The **first player to answer correctly** before time runs out gains pulling strength
4. An **incorrect answer** weakens that player and gives the opponent an advantage
5. The tug-of-war position updates after every question
6. The game ends when one player is fully pulled across — or time runs out

---

## C++ concepts demonstrated

This project was built to explore and apply object-oriented programming in C++:

- **Classes and objects** — separate classes for `Player`, `Question`, `GameEngine`, and `DifficultyManager`
- **Inheritance** — `ComputerPlayer` extends the base `Player` class
- **Encapsulation** — game state and player data managed through class methods
- **Polymorphism** — different difficulty levels handled through overriding
- **Timers** — question countdown implemented using `<chrono>`
- **Randomisation** — question generation using `<random>`

---

## Project structure

```
MathTagOfWar/
│
├── README.md
├── main.cpp                  ← Entry point, game loop
│
├── include/
│   ├── Player.h              ← Player class definition
│   ├── ComputerPlayer.h      ← Computer opponent (inherits Player)
│   ├── Question.h            ← Question structure and generation
│   ├── GameEngine.h          ← Core game logic and state
│   └── DifficultyManager.h  ← Difficulty scaling and level definitions
│
└── src/
    ├── Player.cpp
    ├── ComputerPlayer.cpp
    ├── Question.cpp
    ├── GameEngine.cpp
    └── DifficultyManager.cpp
```

---

## How to compile and run

**Requirements:** A C++ compiler supporting C++17 (g++, clang++, or MSVC)

**Compile:**
```bash
g++ -std=c++17 -o MathTagOfWar main.cpp src/*.cpp
```

**Run:**
```bash
./MathTagOfWar
```
On Windows:
```bash
MathTagOfWar.exe
```

---

## Roadmap

- [x] Core game loop and turn logic
- [x] Question generation by difficulty level
- [x] Timed answer mechanic
- [x] Two-player local mode
- [x] Strength/weakness system based on correct/wrong answers
- [x] Class architecture defined for all major components
- [ ] ASCII tug-of-war rope display in terminal *(class skeleton in place, output not yet implemented)*
- [ ] Computer opponent with difficulty-scaled AI *(class skeleton in place, logic not yet implemented)*
- [ ] Score history and session statistics *(class skeleton in place, logic not yet implemented)*
- [ ] Sound effects (terminal beep on timeout)
- [ ] Leaderboard / high score saving

---

## Why I built this

I wanted a hands-on project to apply OOP principles beyond textbook exercises — something that had real structure, real user interaction, and a purpose beyond just compiling. Designing a game for children forced me to think about user experience, difficulty scaling, and clean class architecture in a way that abstract exercises don't.

---

## Author

M.Sc. Computer Simulation student at Bergische Universität Wuppertal  
Interested in scientific computing, data analysis, and building useful tools
