# MazeSolver
This is my solution to the maze solving problem presented in Computerphile's maze solving video. You can find it here: https://www.youtube.com/watch?v=rop0W4QDOUI

This project uses an open source maze generator called daedalus. You can find out more here: https://www.astrolog.org/labyrnth/daedalus.htm
This project uses wxWidgets. To compile, you may need to download the wxWidgets library.

To generate a maze:
1. Find and run daedalus.exe inside the MazeGenerator folder
2. Select Edit -> Set Colors
3. Set the Passage color to White.
4. Set the Wall color to black.
5. Set the maze size in Maze -> Maze Size
6. Generate a new maze with Create -> Perfect. Alternatively, you can do Create -> Braid.
7. Save the image as a bitmap with File -> Save Bitmap...

Alternatively, you can use one of the examples provided in the ExampleMaze folder.

To solve the maze
1. Run my program
2. Select the image of the maze
3. Select a location to save the solved version of the maze.
