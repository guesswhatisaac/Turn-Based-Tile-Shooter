Turn-Based Tiled Shooter
========================
A classic turn-based shooter game built in C, where the player must defeat enemies on a grid before they reach the player's zone.

--------------------------------------------------------------------------------

🌟 PROJECT OVERVIEW
------------------

This project is a turn-based tiled shooter game implemented in C. The player controls a ship at the bottom of a 4-column grid and must shoot down enemies advancing from the top. The goal is to score 100 points by eliminating enemies. The game is lost if any enemy reaches the player's row at the bottom of the screen.

The project includes two versions:
  * An original version with core game mechanics.
  * A bonus version that adds a power-up system.

The game elements are represented by characters on the grid:
  * 'P' (Player): Can move left, move right, or fire a laser up its column.
  * 'X' (Enemy): A maximum of 3 enemies are on screen. They follow a set movement pattern ('right -> down -> left -> down') and respawn at the top when defeated.
  * '+' (Power-Up, Bonus Version Only): Spawns every 5 rounds and grants a 2x score multiplier for a limited time when shot.


🎯 MOTIVATION
------------

This project was created as a machine project for a programming course. The primary motivations were to:

  * Apply fundamental C programming concepts in a practical application.
  * Implement core game logic, including turn-based mechanics, scoring, and win/loss conditions.
  * Manage game state using basic data types and program flow control (loops, conditionals).
  * Demonstrate the ability to structure a program logically using functions.
  * Practice creating a complete, testable, and debugged program from a given specification.


🛠️ TECHNOLOGIES USED
-------------------

  * C: The sole programming language used for all game logic.
  * Standard C Libraries: 'stdio.h', 'stdlib.h', and 'time.h' for input/output, memory management, and random number generation.


🚀 GETTING STARTED
-----------------

To compile and run this project on your local machine, you will need a C compiler.

### Prerequisites

  * A C compiler, such as GCC (GNU Compiler Collection).

### Project Structure

The project contains two primary source files:
  * 'Roman, Shooter [ORIGINAL].c': The source code for the original game.
  * 'Roman, Shooter [WITH BONUS].c': The source code for the enhanced game with power-ups.

### Compilation

1.  Open your terminal or command prompt.
2.  Navigate to the directory where you saved the `.c` files.
3.  Use the following commands to compile the desired version. The quotes are important to handle spaces in the filenames.

    To compile the original version:
        gcc "Roman, Shooter [ORIGINAL].c" -o shooter_original

    To compile the bonus version:
        gcc "Roman, Shooter [WITH BONUS].c" -o shooter_bonus


🎮 USAGE
-------

After compiling, you can run the game from your terminal.

To run the original version:
    ./shooter_original

To run the bonus version:
    ./shooter_bonus

### How to Play

The game is turn-based. In each turn, you will be prompted to input an action:
  * [1] Move left: Moves the player 'P' one column to the left.
  * [2] Move right: Moves the player 'P' one column to the right.
  * [3] Fire laser: Shoots a laser up the current column, destroying the first enemy it hits.

After your action, the enemies will move according to their pattern.

**Objective:** Reach a score of 100 to win.
**Losing Condition:** An enemy advances past the final row and reaches the player's zone.
