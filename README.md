Overview
This project is a simple implementation of a Candy Crush-like game using C++ and the SFML (Simple and Fast Multimedia Library). The game features a grid of candies that can be swapped to form matches of three or more. The player scores points by forming matches, and the game ends when the target score is reached or when the player runs out of moves.

-Features
Candy Selection: Select candies using the mouse.
Candy Swapping: Swap candies using arrow keys.
Match Detection: Detects and removes matches of 3, 4, and 5 candies in horizontal, vertical, and diagonal directions.
Score and Moves Tracking: Tracks the player's score and remaining moves.
Save and Load Game: Save the game state to a file and load it later.
Penalty Timer: Reduces score and moves every 10 seconds.

-Installation and Setup
Prerequisites
C++ Compiler (e.g., g++)
SFML Library (version 2.5 or later)


-How to Play
Start the Game:
Upon launching the game, you'll be prompted to enter the grid size (6 or 7) and whether to start a new game or load a saved game.
Candy Selection and Swapping:
Select a candy by clicking on it.
Swap candies using the arrow keys (Up, Down, Left, Right).
Form Matches:
Matches of three or more candies will be automatically detected and removed, and the score will be updated.
Save the Game:
Click the "Save" button to save the current game state.
Game End:
The game ends when you reach the target score or run out of moves.
Code Structure
Main Components
Game Initialization:
Initializes the game grid with random candies.
Option to load a saved game state.
Game Loop:
Handles events such as candy selection, swapping, and saving the game.

-Functions:
Select(): Handles candy selection.
SwapCandies(): Swaps candies in the grid.
CheckMatches(): Detects and removes matches.
FillGrid(): Fills empty spaces in the grid with new candies.
SaveGame(): Saves the game state to a file.
LoadGame(): Loads the game state from a file.
Event Handling
Mouse clicks for candy selection and saving the game.
Arrow keys for swapping candies.

-Display
Uses SFML to render the game grid, candies, score, moves, and timer.
Future Enhancements
Add animations for candy swaps and match removals.
Implement more complex match patterns.
Improve the user interface with better graphics and sound effects.
Add more game levels and challenges.
