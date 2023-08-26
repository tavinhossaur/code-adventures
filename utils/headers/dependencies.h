#define DISPLAY_WIDTH 768
#define DISPLAY_HEIGHT 641

#define BACKGROUND_FILE "res/sprites/city_background.png"
#define TEXT_FONT "res/fonts/Monaco.ttf"
#define MUSIC_THEME "res/audio/tildeath.ogg"

#define FPS 60

#define MAX_COLLISIONS 52
#define MAX_MOVEMENTS 12

typedef struct Character // Personagem jogável
{
    int posX;
    int posY;
    ALLEGRO_BITMAP* currentMovementBitmap;

} Character;

typedef struct CollisionBlock // Bloco para gerar as colisões no mapa
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
