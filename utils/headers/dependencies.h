#define DISPLAY_WIDTH 768
#define DISPLAY_HEIGHT 641

#define BACKGROUND_FILE "res/sprites/city_background.png"

#define TEXT_FONT "res/fonts/Monaco.ttf"
#define FONT_SIZE 30

// Música do jogo
#define MUSIC_THEME "res/audio/tildeath.ogg"
#define SAMPLES 2048
#define SONG_BUFFER 4
#define FREQUENCY 44100

#define FPS 60
#define MAX_COLLISIONS 52
#define MAX_MOVEMENTS 12
#define MAX_MOVEMENT_KEYS 4

// Personagem
#define CHARACTER_START_X 15
#define CHARACTER_START_Y 338
#define CHARACTER_WIDTH 18
#define CHARACTER_HEIGHT 22
#define CHARACTER_X_HITBOX_AJUST 9
#define CHARACTER_Y_HITBOX_AJUST 18

typedef struct Character
{
    int posX;
    int posY;
    int lastDirection;
    ALLEGRO_BITMAP* currentMovementBitmap;

} Character;

typedef struct CollisionBlock
{
    int topLeftX;
    int topLeftY;
    int bottomRightX;
    int bottomRightY;

} CollisionBlock;

enum Keys { W, A, S, D };

enum Movements
{
    STANDBY_UP, WALKING_UP_1, WALKING_UP_2,
    STANDBY_LEFT, WALKING_LEFT_1, WALKING_LEFT_2,
    STANDBY_DOWN, WALKING_DOWN_1, WALKING_DOWN_2,
    STANDBY_RIGHT, WALKING_RIGHT_1, WALKING_RIGHT_2,
};
