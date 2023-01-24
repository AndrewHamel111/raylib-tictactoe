# raylib-tictactoe

A super-duper basic Tic-Tac-Toe in all raylib's pure-C glory!

This repo was created as a resource for my [tutorial](https://youtu.be/ki5l_It9Q9Y) on [Andrew Hamel Codes](https://www.youtube.com/channel/UCETp9EybHuo0AM6tZMzdHxA).

Don't think of this as a game, but instead a minimum-implementation of Tic-Tac-Toe. There isn't much code here whatsoever, so expanding it to add some fancy animations, sound effects, ~~networking~~[^1] could be easy! To get this baseline implementation only took ~45 minutes, and to expand it more wouldn't take much. My [Minesweeper](https://github.com/AndrewHamel111/raylib-minesweeper) project was used as a base, as the grid-implementation and some of the Cell-picking logic felt appropriate to reuse for this. The game could easily be modified to support an arbitrary number of rows / columns for the game logic and display, although there must be a reason that non-3x3 tic-tac-toes don't exist.. [^3]

## Video Notes

### Minor Corrections / Comments

If you're coming from C# and are familiar with out parameters, then it may be good practice in the GameIsOver function to set the value of winner to EMPTY in the false case, as in C# out parameters must always be set before the control leaves the method.

### Win Checking Logic

Part of the reason I imagine that many Computer Science programs will eventually feature a Tic-Tac-Toe assignment[^2] is because of the potentially quite messy win-condition logic. There are many different approaches to optimize for readability, execution time, and reusability, and it's a great chance to watch students *spin their tires*. For our approach, explicitly hardcoding each case gets the job done and is simple enough to understand. To help illustrate the layout of the game board on the code side, I created these diagrams which are featured in the video. If you're just reading this repo, refer to these images when reading the GameIsOver bool function.

![raylib-tictactoe-diagram1](doc-resources\raylib-tictactoe-diagram1.png)

![raylib-tictactoe-diagram1](doc-resources\raylib-tictactoe-diagram2.png)

![raylib-tictactoe-diagram1](doc-resources\raylib-tictactoe-diagram3.png)

![raylib-tictactoe-diagram1](doc-resources\raylib-tictactoe-diagram4.png)

## Footnotes

[^1]: Networking is never simple. Do not be fooled
[^2]: Source: I asked like 3 kids that went to other schools and they had Tic-Tac-Toe assignments. None of them used graphical interfaces, and 3/4 were part of a class explicitly on Java and OOP.
[^3]: Seriously? You couldn't just Google it? https://www.math10.com/en/math-games/tic-tac-toe/tic-tac-toe.html
