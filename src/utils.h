#ifndef UTILS_H
#define UTILS_H

// -------------- //
// Data structure //
// -------------- //

enum Direction {     // Elementary directions
    DIRECTION_RIGHT, // Right
    DIRECTION_UP,    // Up direction
    DIRECTION_LEFT,  // Left direction
    DIRECTION_DOWN,  // Down direction
};

struct Point { // Representing a 2D point
    int x;     // The x-coordinate
    int y;     // The y-coordinate
};

struct Position { // Representing a position in the maze
    int row;      // The row number
    int col;      // The column number
};

#endif
