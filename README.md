# Visual A* Pathfinding Implementation using C++ & SFML

### Introduction & Description
While beginning to learn about intelligent algorithms one of the first I looked at was the A\* algorithm. From that came this project that I intend to actively develope over the next few months. In it's current state, I have only implemented the A\* algorithm but I intend to add other algorithms as well.

This application will generate a square 2D grid, choosing a percentage to be walls. Then, given a start and end point it performs the A\* pathfinding algorithm. All nodes of the grid are weighted equally and movement is allowed in all eight directions. More information on this algorithm can be found [here](https://en.wikipedia.org/wiki/A*_search_algorithm "Wikipedia").

### Getting Started
![initial menu](https://github.com/ronhuff/pathfinding/blob/master/img/menu.png)

Select the algorithm you wish to use here. While only one is supported at the moment, look for others to be added in the future.

![default or custom](https://github.com/ronhuff/pathfinding/blob/master/img/chooseSettings.png)

In order to view a quick demonstration, simply choose the default settings, otherwise you may configure some basic parameters.

![custom settings](https://github.com/ronhuff/pathfinding/blob/master/img/settings2.png)

These include grid size, start & end positions as well as the distance heuristic. I would like to allow for further configuration in the future such as tweaking the heuristic's output.

![demonstration run](https://github.com/ronhuff/pathfinding/blob/master/img/demo.png)

Here we can see the where the application has successfully executed the algorithm with the above settings.

### Future Features & Additions
- Other algorithms such as Dijkstra's.
- The ability to compare different algorithms & heuristics on the same grid/wall configuration.
- Move some of the user input to the GUI using the mouse.
- Statistical output alongside the grid.

##### [Difficulty building?](https://github.com/ronhuff/pathfinding/wiki/Visual-Studio-Project-Settings)
