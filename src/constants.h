// General constants
#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT (900 * 4 / 5)

// Menu constants
#define TITLE_FILENAME "../assets/maze.png"
#define TITLE_WIDTH 800
#define TITLE_X ((SCREEN_WIDTH - TITLE_WIDTH) / 2)
#define TITLE_Y 0
#define PLAY_FILENAME "../assets/play.png"
#define PLAY_WIDTH 400
#define PLAY_X ((SCREEN_WIDTH - PLAY_WIDTH) / 2)
#define PLAY_Y 300
#define QUIT_FILENAME "../assets/quit.png"
#define QUIT_WIDTH 400
#define QUIT_X ((SCREEN_WIDTH - QUIT_WIDTH) / 2)
#define QUIT_Y 400

// Maze
#define MAZE_FILENAME "../assets/level1.tmx"
#define MAZE_INITIAL_X 0
#define MAZE_INITIAL_Y 0
#define MAZE_NUM_ROWS 8
#define MAZE_NUM_COLS 10

// Character
#define CHARACTER_SPRITESHEET "../assets/character/walking.png"
#define CHARACTER_SCALE ((SCREEN_WIDTH) / 2560.0)
#define MOVE_DURATION 200
#define CHARACTER_WALKING_UP_ROW 0
#define CHARACTER_WALKING_LEFT_ROW 1
#define CHARACTER_WALKING_DOWN_ROW 2
#define CHARACTER_WALKING_RIGHT_ROW 3
#define CHARACTER_BETWEEN_FRAME (MOVE_DURATION / 20)
#define CHARACTER_HORIZONTAL_STEP (SCREEN_WIDTH / 10)
#define CHARACTER_VERTICAL_STEP (SCREEN_HEIGHT / 8)
