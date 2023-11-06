// Resolução
#define DISPLAY_WIDTH 768
#define DISPLAY_HEIGHT 641

// Sprites
#define BACKGROUND_FILE "res/sprites/game_background.png"
#define TITLE_BACKGROUND_FILE "res/sprites/title_background1.png"
#define TITLE_BACKGROUND_CONTINUE_FILE "res/sprites/title_background2.png"
#define TUTORIAL_BACKGROUND_FILE "res/sprites/tutorial_background.png"
#define MENU_SELECTOR_GENDER_GIRL "res/sprites/menu_gender_selection_girl.png"
#define MENU_SELECTOR_GENDER_BOY "res/sprites/menu_gender_selection_boy.png"
#define PAUSE_BACKGROUND "res/sprites/pause_background.png"
#define CHALLENGE_BACKGROUND "res/sprites/challenges_background.png"
#define DIALOG_BAR "res/sprites/interface/dialog_bar.png"

// Fonte
#define TEXT_FONT "res/fonts/Monaco.ttf"
#define FONT_SIZE 20

// Música do jogo
#define MUSIC_THEME "res/audio/tildeath.ogg"
#define SAMPLES 2048
#define SONG_BUFFER 4
#define FREQUENCY 44100

// Limitadores
#define MAX_FPS 60
#define MAX_COLLISIONS 36
#define MAX_HOUSES 10
#define MAX_MOVEMENTS 12
#define MAX_MOVEMENT_KEYS 4
#define MAX_ALTERNATIVES 4
#define MAX_QUESTIONS 10
#define MAX_QUESTION_TEXT_LINES 8

// Personagem
#define CHARACTER_START_X 15
#define CHARACTER_START_Y 338
#define CHARACTER_WIDTH 18
#define CHARACTER_HEIGHT 22
#define CHARACTER_X_HITBOX_ADJUST 9
#define CHARACTER_Y_HITBOX_ADJUST 18

typedef struct Character
{
    char* name;
    int posX;
    int posY;
    int lastDirection;
    bool isMoving;
    ALLEGRO_BITMAP* currentMovementBitmap;

} Character;

typedef struct CollisionBlock
{
    int topLeftX, topLeftY, bottomRightX, bottomRightY;

} CollisionBlock;

typedef struct HouseDoor
{
    int topLeftX, topLeftY, bottomRightX, bottomRightY;
    bool alreadyEntered;

} HouseDoor;

typedef struct Challenge
{
    char *alternatives[MAX_ALTERNATIVES];
    char *questionText[MAX_QUESTION_TEXT_LINES];
    int correctAnswer;
    bool isChallengeCompleted;

} Challenge;

enum Keys { KEY_W, KEY_A, KEY_S, KEY_D };
enum Screens { TITLE_SCREEN, GAME_SCREEN, PAUSE_SCREEN, TUTORIAL_SCREEN, CREDITS_SCREEN, CHALLENGES_SCREEN };
enum Genders { BOY, GIRL };
enum Alternatives { A, B, C, D };

enum Movements
{
    STANDBY_UP, WALKING_UP_1, WALKING_UP_2,
    STANDBY_LEFT, WALKING_LEFT_1, WALKING_LEFT_2,
    STANDBY_DOWN, WALKING_DOWN_1, WALKING_DOWN_2,
    STANDBY_RIGHT, WALKING_RIGHT_1, WALKING_RIGHT_2
};
