# Maze

Implementation of the Maze project.


## Chapter I

![Maze](misc/images/A1_Maze.JPG)

Eve approached the head's office just as the familiar, muffled scream came from it:

"How... dare you open ...cess to the INTERNET to thes...vers?! And most importantly, why ...ns?!"

Going into the office now was clearly not the best idea, so Eve decided to wait out the obviously unpleasant conversation in the hallway. \
After an unintelligible reply, the boss's outrage continued:

"You clearly don't understand the importance of this project to our... This is... Now go fix all these screw-ups!"

The door opened, and Alice and Charlie rushed out of the office, looking downcast.

"And God help us if anything leaks out!" he yelled after them.

Alice and Charlie ran off in opposite direction, oblivious to Eve standing nearby. She waited a few minutes, then straightened and knocked on the door.

"Come in. Oh, Eve, yes, come in," the boss said. The spacious room with wide windows was filled with various books on algorithms, mathematics, and programming. In the middle of the room was a table with a plastic sign that said "Robert M.".

"Bob, about the experiments for the task..."

"With the mazes, yes, I know. They were testing your developments. They are interesting, but too simple. We sent generation examples to our partners, but their brainchild went through the mazes in an embarrassingly short period of time. And in our case we need something much more complicated. \
Try to reduce the number of correct paths. Browse the Internet again, look in the direction of caves and cellular automata, and then back to testing and experimenting. And remember, the more complicated, the better!"

Eve left the office and walked to her workplace, wondering what other algorithms she could try. On the way, she looked for Alice or Charlie to find out what had happened, but she couldn't find them, so she sat down at her computer and continued working.

## Introduction

In this project you’ll learn about mazes and caves, including the basic algorithms of their handling, such as: generation, rendering, solving.


## Chapter II

## Information

A maze with "thin walls" is a table of _n_ rows by _m_ columns size. There can be "walls" between the cells of a table. The table as a whole is also surrounded by "walls".

The following is an example of such a maze: \
![maze](misc/images/maze.jpg)

The solution to a maze is the shortest path from a given starting point (table cell) to the end point.

When traversing a maze, you can move to neighboring cells that are not separated from the current cell by a "wall" and that are at the top, bottom, right, or left.
A path is considered the shortest if it passes through the least number of cells.

An example of a maze and its solution:  \
![solution](misc/images/solution.jpg)

In this example, the starting point is 10; 1, and the ending point is 6; 10.

## Maze description

The maze can be stored in a file as a number of rows and columns, as well as two matrices containing the positions of the vertical and horizontal walls respectively.

The first matrix shows the wall to the right of each cell, and the second matrix shows the wall at the bottom.

An example of such a file:
```
4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
```

The maze described in this file:  \
![maze4](misc/images/maze4.jpg)

See materials for more examples of maze descriptions.

## Maze flaws

Maze flaws include isolated areas and loops.

An isolated area is a part of the maze with passages that are inaccessible from the rest of the maze. For example: \
![isolated](misc/images/isolated.png)

A loop is a part of the maze with passages that can be walked in "circles". The walls in the loops are not connected to the walls surrounding the maze. For example: \
![loop](misc/images/loop.png)

## Cellular automaton generation

Many games require branching locations, such as caves. These can be created using cellular automaton generation. This kind of generation uses an idea similar to the Game of Life you are already familiar with. The idea of the proposed algorithm consists in implementing only two steps: first, the whole field is randomly filled with walls - i.e. for each cell it is randomly determined whether it will be free or impassable - and then the map state is updated several times according to the conditions, similar to the birth/death ones in the Game of Life.

The rules are simpler than in the Game of Life - there are two special variables, one for the "birth" of "dead" cells (the "birth" limit) and one for the destruction of "live" cells (the "death" limit).
If "live" cells are surrounded by "live" cells whose number is less than the "death" limit, they "die". Similarly, if "dead" cells are surrounded by "live" cells whose number is greater than the "birth" limit, they will become "live".

An example of the algorithm's result (the first image shows only the initialized maze, and the second image shows a maze in which there are no changes in subsequent steps): \
![cave1](misc/images/cave1.jpg)
![cave2](misc/images/cave2.jpg)

## Caves description

A cave that has passed 0 simulation steps (only initialized) can be stored in the file as a number of rows and columns, as well as a matrix containing the positions of "live" and "dead" cells.

An example of such a file:
```
4 4
0 1 0 1
1 0 0 1
0 1 0 0
0 0 1 1
```

The cave described in this file: \
![cave3](misc/images/cave3.jpg)

See materials for more examples of cave descriptions.


## Chapter III

## Part 1. Implementation of the Maze project

You need to implement a Maze program that can generate and render perfect mazes and caves:
- The program must be developed in C++ language of C++17 standard.
- The program code must be located in the src folder.
- When writing code it is necessary to follow the Google style.
- The program must be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests. Installation directory could be arbitrary, except the building one.
- GUI implementation, based on any GUI library with API for C++17: Qt, SFML, GTK+, Nanogui, Nngui, etc.
- The program has a button to load the maze from a file, which is set in the format described [above](#maze-description).
- Maximum size of the maze is:
  50x50.
- The loaded maze must be rendered on the screen in a field of 500x500 pixels.
- "Wall" thickness is 2 pixels.
- The size of the maze cells themselves is calculated so that the maze occupies the entire field allotted to it.

## Part 2. Generation of a perfect maze

Add the ability to automatically generate a perfect maze. \
A maze is considered perfect if it is possible to get from each point to any other point in exactly one way.
- You must generate the maze according to **Eller's algorithm**.
- The generated maze must not have isolations and loops.
- Prepare full coverage of the perfect maze generation module with unit-tests.
- The user enters only the dimensionality of the maze: the number of rows and columns.
- The generated maze must be saved in the file format described [above](#maze-description).
- The created maze should be displayed on the screen as specified in the [first part](#part-1-implementation-of-the-maze-project).

## Part 3. Solving the maze

Add the ability to show the solution to _any_ maze currently shown on the screen:
- The user sets the starting and ending points.
- The route, which is the solution, must be displayed with a line 2 pixel thick, passing through the middle of all the cells in the maze through which the solution runs.
- The color of the solution line must be different from the color of the walls, and the field.
- Prepare full coverage of the maze solving module with unit-tests.

## Part 4. Bonus. Cave Generation

Add cave generation [using a cellular automaton](#generation-using-a-cellular-automaton):
- The user selects the file that describes the cave according to the format described [above](#caves-description).
- Use a separate window or tab in the user interface to display the caves.
- Maximum size of the cave is 50x50.
- The loaded cave must be rendered on the screen in a field of 500x500 pixels.
- The user sets the limits for "birth" and "death" of a cell, as well as the chance for the starting initialization of the cell.
- The "birth" and "death" limits can have values from 0 to 7.
- Cells outside the cave are considered alive.
- There should be a step-by-step mode for rendering the results of the algorithm in two variants:
    - Pressing the next step button will lead to rendering the next iteration of the algorithm;
    - Pressing the automatic work button starts rendering iterations of the algorithm with a frequency of 1 step in `N` milliseconds, where the number of milliseconds `N` is set through a special field in the user interface.
- The size of cells in pixels is calculated so that the cave occupies the entire field allotted to it.
- Prepare full coverage of the cave generation module with unit-tests.

💡 [Tap here](https://forms.yandex.ru/cloud/64181d8ff47e7326ab0fc364/) **to leave your feedback on the project**. Our team really tries to make your educational experience better.
