#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include "utils/headers/dependencies.h"

#define KEY_PRESSED true
#define KEY_RELEASED false

int main() {
    int mouseClickPositionX = 0;
    int mouseClickPositionY = 0;

    int screen = TITLE_SCREEN;
    int gender = BOY;

    bool nameSelected = true;
    bool isGameAlreadyStarted = false;

    // Controle para bloquear e desbloquear o uso das teclas de movimento
    bool blockedKey[MAX_MOVEMENT_KEYS] = {false, false, false, false};
    unsigned char key[ALLEGRO_KEY_MAX];

    al_init();

    // Altera o nome do jogo na janela do windows
    al_set_app_name("CodeAdventures");

    // Inicializando variáveis principais para o funcionamento do jogo
    ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / MAX_FPS);

    // Instalando addons do Allegro e criando eventos
    if (!initializeGame(display, queue, timer)) return 1;

    // Inicializando variáveis de controle do som do jogo
    ALLEGRO_VOICE* voice = al_create_voice(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_MIXER* mixer = al_create_mixer(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

    // Inicializando variáveis dos recursos utilizados (sprites, musicas, fontes)
    ALLEGRO_BITMAP* background = al_load_bitmap(GAME_BACKGROUND_FILE);
    ALLEGRO_BITMAP* endBackground = al_load_bitmap(END_GAME_BACKGROUND_FILE);
    ALLEGRO_BITMAP* menuBackground = al_load_bitmap(TITLE_BACKGROUND_FILE);
    ALLEGRO_BITMAP* menuBackgroundContinue = al_load_bitmap(TITLE_BACKGROUND_CONTINUE_FILE);
    ALLEGRO_BITMAP* tutorialBackground = al_load_bitmap(TUTORIAL_BACKGROUND_FILE);
    ALLEGRO_BITMAP* menuSelectGenderBoy = al_load_bitmap(MENU_SELECTOR_GENDER_BOY);
    ALLEGRO_BITMAP* menuSelectGenderGirl = al_load_bitmap(MENU_SELECTOR_GENDER_GIRL);
    ALLEGRO_BITMAP* pauseBackground = al_load_bitmap(PAUSE_BACKGROUND);
    ALLEGRO_BITMAP* challengeBackground = NULL;
    ALLEGRO_BITMAP* creditsBackground = al_load_bitmap(CREDITS_BACKGROUND);
    ALLEGRO_BITMAP* dialogBar = al_load_bitmap(DIALOG_BAR);
    ALLEGRO_BITMAP* alertDialog = al_load_bitmap(ALERT_DIALOG);
    ALLEGRO_BITMAP* snorlax = al_load_bitmap(SNORLAX);

    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream(MUSIC_THEME, SONG_BUFFER, SAMPLES);
    ALLEGRO_FONT* font = al_load_ttf_font(TEXT_FONT, FONT_SIZE, 0);
    ALLEGRO_FONT* secondaryFont = al_load_ttf_font(TEXT_FONT, SECONDARY_FONT_SIZE, 0);

    // Objetos do jogo
    CollisionBlock *collisions = NULL;
    HouseDoor *houses = NULL;
    ALLEGRO_BITMAP **movementList = NULL;
    Challenge *challengeList = NULL;
    Character character = { NULL };

    // Inicializando a música do jogo
    if (initializeMusic(voice, mixer, music)) printf("- Musica carregada com sucesso.\n");
    // Começando timer do jogo
    al_start_timer(timer);

    // Contadores utilizados em tempo de execução
    int frameCounter = 0;
    int challengeIndex = 0;
    int currentQuoteIndex = 0;

    char inputText[12] = "";
    int cursorPosition = 0;

    int textX = (DISPLAY_WIDTH / 2);
    int textY = (DISPLAY_HEIGHT / 2) - 30;

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                break;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                if (cursorPosition > 0) {
                    inputText[--cursorPosition] = '\0';
                }
            } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                if (cursorPosition > 0) {
                    cursorPosition--;
                }
            } else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                initializeDestruction(display, font, music, background, menuBackground, menuBackgroundContinue, tutorialBackground, menuSelectGenderBoy, menuSelectGenderGirl, pauseBackground, movementList, mixer, collisions, challengeList);
                return 0;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                if (cursorPosition < strlen(inputText)) {
                    cursorPosition++;
                }
            } else if (event.keyboard.keycode >= ALLEGRO_KEY_A && event.keyboard.keycode <= ALLEGRO_KEY_Z) {
                if (strlen(inputText) < sizeof(inputText) - 1) {
                    memmove(&inputText[cursorPosition + 1], &inputText[cursorPosition], strlen(&inputText[cursorPosition]) + 1);
                    inputText[cursorPosition++] = event.keyboard.keycode + 'a' - ALLEGRO_KEY_A;
                }
            }
        }

        if (strlen(inputText) == 1) inputText[0] = toupper(inputText[0]);

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 255, 255), (DISPLAY_WIDTH / 2) - 200, 10, 0, "Bem-vindo, Jogador! Insira seu nome");
        al_draw_text(font, al_map_rgb(255, 255, 255), 10, DISPLAY_HEIGHT - 30, 0, "Pressione ESC para sair ou enter para continuar");
        al_draw_text(font, al_map_rgb(255, 255, 255), textX - 150, textY, 0, "Treinador(a) ");
        al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY, 0, inputText);

        int cursorX = textX + al_get_text_width(font, inputText);
        if (cursorPosition > 0) {
            cursorX = textX + al_get_text_width(font, inputText) - al_get_text_width(font, &inputText[cursorPosition]);
        }
        al_draw_line(cursorX, textY, cursorX, textY + al_get_font_line_height(font), al_map_rgb(255, 255, 255), 1);

        al_flip_display();
    }

    character.name = strlen(inputText) > 0 ? inputText : "Ash";

    printf("- [GAME_RUNTIME] -> | Nome salvo.\n");
    printf("- [GAME_RUNTIME] -> | Bem-vindo ao Code Adventures, %s!\n", character.name);

    // Loop principal
    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_PRESSED | KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // Encerra o jogo limpando as funções que consomem memória
            initializeDestruction(display, font, music, background, menuBackground, menuBackgroundContinue, tutorialBackground, menuSelectGenderBoy, menuSelectGenderGirl, pauseBackground, movementList, mixer, collisions, challengeList);
            return 0;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if(event.mouse.button & 1) {
                mouseClickPositionX = event.mouse.x;
                mouseClickPositionY = event.mouse.y;
            }
            break;
        }

        // Lógica em tempo de execução
        if (event.type == ALLEGRO_EVENT_TIMER) {
            if(frameCounter > 1000) frameCounter = 0;

            for(int i = 0; i < ALLEGRO_KEY_MAX; i++) key[i] &= KEY_PRESSED;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            switch (screen) {
            case TITLE_SCREEN:

                // Desenha o menu (TITLE_SCREEN)
                if(isGameAlreadyStarted) {
                    al_draw_bitmap(menuBackground, 0, 0, 0);
                } else {
                    al_draw_bitmap(menuBackgroundContinue, 0, 0, 0);
                }

                // Desenha o seletor de genero
                if(gender == BOY) al_draw_bitmap(menuSelectGenderBoy, 450, 280, 0);
                else al_draw_bitmap(menuSelectGenderGirl, 450, 280, 0);

                // Verifica os cliques durante o Title (TITLE_SCREEN)
                if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    al_draw_textf(font, al_map_rgb(245, 197, 66), 594, 247, 1, "%s", character.name);

                    // Se o jogo ainda já iniciou (jogador quer um continuar um jogo já começado)
                    if (mouseClickPositionX >= 128 && mouseClickPositionX <= 330 && mouseClickPositionY >= 314 && mouseClickPositionY <= 357 && isGameAlreadyStarted) {

                        if (nameSelected) {
                            screen = GAME_SCREEN;
                            mouseClickPositionX = 0;
                            mouseClickPositionY = 0;
                        }

                        printf("- [GAME_RUNTIME] -> | Jogo anterior carregado.\n");

                    } else if(mouseClickPositionX >= 128 && mouseClickPositionX <= 330 && mouseClickPositionY >= 248 && mouseClickPositionY <= 292) {

                        if(nameSelected == true) {

                            // Carregando a lista de bitmaps dos movimentos do personagem com base no gênero escolhido
                            movementList = getCharacterMovementSprites(gender);

                            challengeBackground = gender == BOY ? al_load_bitmap(CHALLENGE_BACKGROUND_BOY) : al_load_bitmap(CHALLENGE_BACKGROUND_GIRL);

                            collisions = getCollisionBlocks();
                            challengeList = getChallenges();
                            houses = getHouses();

                            for (int i = 0; i < MAX_HOUSES; i++) houses[i].alreadyEntered = false;

                            // Criando um personagem
                            character.posX = CHARACTER_START_X;
                            character.posY = CHARACTER_START_Y;
                            character.lastDirection = KEY_S;
                            character.isMoving = false;
                            character.currentMovementBitmap = movementList[STANDBY_DOWN];

                            isGameAlreadyStarted = true;
                            currentQuoteIndex = 0;
                            challengeIndex = 0;

                            screen = GAME_SCREEN;
                            mouseClickPositionX = 0;
                            mouseClickPositionY = 0;

                            printf("- [GAME_RUNTIME] -> | Novo jogo carregado.\n");
                        } else {
                            al_draw_textf(font, al_map_rgb(255, 50, 50), 594, 247, 1, "Insira um nome!");
                        }
                    }

                    if(mouseClickPositionX >= 128 && mouseClickPositionX <= 330 && mouseClickPositionY >= 385 && mouseClickPositionY <= 428) {
                        screen = TUTORIAL_SCREEN;
                        mouseClickPositionX = 0;
                        mouseClickPositionY = 0;
                    }

                    if(mouseClickPositionX >= 128 && mouseClickPositionX <= 330 && mouseClickPositionY >= 446 && mouseClickPositionY <= 492) {
                        screen = CREDITS_SCREEN;
                        mouseClickPositionX = 0;
                        mouseClickPositionY = 0;
                    }

                    if(mouseClickPositionX >= 128 && mouseClickPositionX <= 330 && mouseClickPositionY >= 522 && mouseClickPositionY <= 563) {
                        initializeDestruction(display, font, music, background, menuBackground, menuBackgroundContinue, tutorialBackground, menuSelectGenderBoy, menuSelectGenderGirl, pauseBackground, movementList, mixer, collisions, challengeList);
                        return 0;
                    }

                    if(mouseClickPositionX >= 600 && mouseClickPositionX <= 625 && mouseClickPositionY >= 555 && mouseClickPositionY <= 590) {
                        gender = BOY;
                        mouseClickPositionX = 0;
                        mouseClickPositionY = 0;
                    }

                    if(mouseClickPositionX >= 566 && mouseClickPositionX <= 590 && mouseClickPositionY >= 555 && mouseClickPositionY <= 590) {
                        gender = GIRL;
                        mouseClickPositionX = 0;
                        mouseClickPositionY = 0;
                    }
                }
                break;

            case GAME_SCREEN:
                // Desenha o mapa
                al_draw_bitmap(background, 0, 0, 0);

                // Desenha os snorlax de acordo com o desafio
                switch(challengeIndex) {
                case 0:
                    al_draw_bitmap(snorlax, 203, 199, 0);
                    al_draw_bitmap(snorlax, 207, 294, 0);
                    al_draw_bitmap(snorlax, 207, 323, 0);
                    al_draw_bitmap(snorlax, 207, 352, 0);
                    al_draw_bitmap(snorlax, 119, 396, 0);
                    al_draw_bitmap(snorlax, 144, 396, 0);
                    break;

                case 1:
                    al_draw_bitmap(snorlax, 334, 195, 0);
                    al_draw_bitmap(snorlax, 334, 220, 0);
                    al_draw_bitmap(snorlax, 207, 294, 0);
                    al_draw_bitmap(snorlax, 207, 323, 0);
                    al_draw_bitmap(snorlax, 207, 352, 0);
                    al_draw_bitmap(snorlax, 119, 396, 0);
                    al_draw_bitmap(snorlax, 144, 396, 0);
                    break;

                case 2:
                    al_draw_bitmap(snorlax, 364, 22, 0);
                    al_draw_bitmap(snorlax, 207, 294, 0);
                    al_draw_bitmap(snorlax, 207, 323, 0);
                    al_draw_bitmap(snorlax, 207, 352, 0);
                    al_draw_bitmap(snorlax, 119, 396, 0);
                    al_draw_bitmap(snorlax, 144, 396, 0);
                    break;

                case 3:
                    al_draw_bitmap(snorlax, 364, 22, 0);
                    al_draw_bitmap(snorlax, 318, 324, 0);
                    al_draw_bitmap(snorlax, 318, 348, 0);
                    al_draw_bitmap(snorlax, 318, 375, 0);
                    al_draw_bitmap(snorlax, 266, 400, 0);
                    al_draw_bitmap(snorlax, 289, 400, 0);
                    al_draw_bitmap(snorlax, 119, 396, 0);
                    al_draw_bitmap(snorlax, 144, 396, 0);
                    break;

                case 4:
                    al_draw_bitmap(snorlax, 364, 22, 0);
                    al_draw_bitmap(snorlax, 430, 351, 0);
                    al_draw_bitmap(snorlax, 430, 375, 0);
                    al_draw_bitmap(snorlax, 266, 400, 0);
                    al_draw_bitmap(snorlax, 289, 400, 0);
                    al_draw_bitmap(snorlax, 119, 396, 0);
                    al_draw_bitmap(snorlax, 144, 396, 0);
                    break;

                case 5:
                    al_draw_bitmap(snorlax, 364, 22, 0);
                    al_draw_bitmap(snorlax, 586, 430, 0);
                    al_draw_bitmap(snorlax, 119, 396, 0);
                    al_draw_bitmap(snorlax, 144, 396, 0);
                    al_draw_bitmap(snorlax, 266, 400, 0);
                    al_draw_bitmap(snorlax, 289, 400, 0);
                    break;

                case 6:
                    al_draw_bitmap(snorlax, 364, 22, 0);
                    al_draw_bitmap(snorlax, 335, 464, 0);
                    al_draw_bitmap(snorlax, 335, 489, 0);
                    al_draw_bitmap(snorlax, 586, 430, 0);
                    break;

                case 7:
                    al_draw_bitmap(snorlax, 364, 22, 0);
                    al_draw_bitmap(snorlax, 408, 464, 0);
                    al_draw_bitmap(snorlax, 408, 489, 0);
                    al_draw_bitmap(snorlax, 586, 430, 0);
                    break;
                }

                if (challengeList[challengeIndex].isChallengeCompleted == 1) {
                    printf("- [GAME_RUNTIME] -> | Resposta correta! Prossiga para uma casa ainda nao visitada!\n");
                    challengeIndex++;
                } else if (challengeList[challengeIndex].isChallengeCompleted == 0 && challengeIndex != 8) {
                    printf("- [GAME_RUNTIME] -> | Resposta incorreta! Tente novamente.\n");
                    challengeList[challengeIndex].isChallengeCompleted = -1;
                }

                if (challengeIndex == 8) {
                    al_draw_bitmap(endBackground, 0, 0, 0);
                    al_draw_scaled_bitmap(alertDialog, 0, 0, al_get_bitmap_width(alertDialog), al_get_bitmap_height(alertDialog), 10, 10, 550, 60, 0);
                    al_draw_textf(secondaryFont, al_map_rgb(0, 0, 0), 280, 33, 1, "Um enigma de Arceus lhe aguarda na porta da caverna!");
                }

                // Lógica de detecção de colisões
                runCollisionDetection(collisions, character, blockedKey, challengeIndex);

                // Lógica de movimentação com animação baseada na direção e FPS
                updateCharacterMovement(&character, frameCounter, movementList, blockedKey, key);

                // Desenha o personagem
                al_draw_scaled_bitmap(
                    character.currentMovementBitmap,
                    0, 0,
                    al_get_bitmap_width(character.currentMovementBitmap),
                    al_get_bitmap_height(character.currentMovementBitmap),
                    character.posX - CHARACTER_X_HITBOX_ADJUST, character.posY - CHARACTER_Y_HITBOX_ADJUST,
                    CHARACTER_WIDTH, CHARACTER_HEIGHT, 0);

                // Verifica os cliques durante o jogo (GAME_SCREEN)
                if(mouseClickPositionX >= 554 && mouseClickPositionX <= 745 && mouseClickPositionY >= 580 && mouseClickPositionY <= 624) {
                    screen = PAUSE_SCREEN;
                }

                // Verifica se o jogador está tentando entrar em qualquer uma das casas que ele já não acessou anteriormente
                if (key[ALLEGRO_KEY_E]) {
                    for (int i = 0; i < MAX_HOUSES; i++) {
                        if (character.posX >= houses[i].topLeftX && character.posX <= houses[i].bottomRightX && character.posY >= houses[i].topLeftY && character.posY <= houses[i].bottomRightY) {
                            if (houses[i].alreadyEntered) {
                                al_draw_scaled_bitmap(alertDialog, 0, 0, al_get_bitmap_width(alertDialog), al_get_bitmap_height(alertDialog), 10, DISPLAY_HEIGHT - 65, 370, 60, 0);
                                al_draw_textf(secondaryFont, al_map_rgb(0, 0, 0), 198, DISPLAY_HEIGHT - 40, 1, "O desafio dessa casa ja foi completo!");
                                break;
                            }
                            screen = CHALLENGES_SCREEN;
                        }
                    }
                }

                // DEBBUGING

                // Desenha todas as colisões (não estará na versão final do jogo)
                // drawCollision(houses); (COMENTE TODOS OS "FALSES" EM runtime.c -> getHouses() E COMENTE "bool alreadyEntered;" EM dependencies.h -> HouseDoor)
                // drawCollision(collisions);
                // al_draw_textf(font, al_map_rgb(255, 255, 255), 198, DISPLAY_HEIGHT - 40, 1, "x: %d / y: %d", mouseClickPositionX, mouseClickPositionY);

                break;

            case PAUSE_SCREEN:
                // Desenha a tela de Pause
                al_draw_bitmap(pauseBackground, 0, 0, 0);

                // Verifica os cliques durante o Pause (PAUSE_SCREEN)
                if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if(mouseClickPositionX >= 336 && mouseClickPositionX <= 450 && mouseClickPositionY >= 122 && mouseClickPositionY <= 162) {
                        screen = GAME_SCREEN;
                    }
                    if(mouseClickPositionX >= 274 && mouseClickPositionX <= 502 && mouseClickPositionY >= 188 && mouseClickPositionY <= 228) {
                        screen = TITLE_SCREEN;
                    }
                    if(mouseClickPositionX >= 298 && mouseClickPositionX <= 486 && mouseClickPositionY >= 254 && mouseClickPositionY <= 295) {
                        initializeDestruction(display, font, music, background, menuBackground, menuBackgroundContinue, tutorialBackground, menuSelectGenderBoy, menuSelectGenderGirl, pauseBackground, movementList, mixer, collisions, challengeList);
                        return 0;
                    }
                }

                if (key[ALLEGRO_KEY_ESCAPE]) {
                    screen = GAME_SCREEN;
                }

                mouseClickPositionX = 0;
                mouseClickPositionY = 0;

                break;

            case TUTORIAL_SCREEN:
                al_draw_bitmap(tutorialBackground, 0, 0, 0);
                if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH - 130, DISPLAY_HEIGHT - 180, 1, "Clique para sair");
                    if(key[ALLEGRO_KEY_ESCAPE] || mouseClickPositionX >= 1 && mouseClickPositionX <= DISPLAY_WIDTH && mouseClickPositionY >= 0 && mouseClickPositionY <= DISPLAY_HEIGHT) {
                        screen = TITLE_SCREEN;
                    }
                    mouseClickPositionX = 0;
                    mouseClickPositionY = 0;
                }
                break;

            case CREDITS_SCREEN:
                al_draw_bitmap(creditsBackground, 0, 0, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 10, 1, "Clique para sair");
                if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if(key[ALLEGRO_KEY_ESCAPE] || mouseClickPositionX >= 1 && mouseClickPositionX <= DISPLAY_WIDTH && mouseClickPositionY >= 0 && mouseClickPositionY <= DISPLAY_HEIGHT) {
                        screen = TITLE_SCREEN;
                    }
                    mouseClickPositionX = 0;
                    mouseClickPositionY = 0;
                }
                break;

            case CHALLENGES_SCREEN:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(challengeBackground, 0, 0, 0);

                // Botão de sair ou tecla "ESC"
                if (key[ALLEGRO_KEY_ESCAPE] || mouseClickPositionX >= 660 && mouseClickPositionX <= 750 && mouseClickPositionY >= 470 && mouseClickPositionY <= 500) {
                    currentQuoteIndex = 0;
                    challengeList[challengeIndex].isChallengeCompleted = -1;
                    screen = GAME_SCREEN;
                    clearMouseClickPositions(&mouseClickPositionX, &mouseClickPositionY);
                    break;
                }

                // Mostra as alternativas
                int yPosition = 90;
                for (int i = 0; i < MAX_ALTERNATIVES; i++) {

                    if (challengeIndex == 7) {
                        al_draw_textf(font, al_map_rgb(255, 255, 255), 330, yPosition, 0, challengeList[challengeIndex].alternatives[i], strlen(character.name));
                    } else {
                        al_draw_text(font, al_map_rgb(255, 255, 255), 330, yPosition, 0, challengeList[challengeIndex].alternatives[i]);
                    }

                    yPosition += 90;
                }

                char questionText[256];

                snprintf(questionText, sizeof(questionText), challengeList[challengeIndex].questionText[currentQuoteIndex], character.name);

                al_draw_scaled_bitmap(dialogBar, 0, 0, al_get_bitmap_width(dialogBar), al_get_bitmap_height(dialogBar), 0, 516, DISPLAY_WIDTH, 125, 0);

                int textLength = strlen(questionText);

                // Se o texto for muito grande, ele é dividido, caso contrário só é mostrado diretamente
                // o index da parte do texto é resetado à zero se o tamanho do texto for menor que 1 ("")
                if (textLength >= 55) {
                    splitText(textLength, questionText, font);
                } else if (textLength < 1) {
                    currentQuoteIndex = 0;
                } else {
                    al_draw_text(font, al_map_rgb(255, 255, 255), 35, 545, 0, questionText);
                }

                if (frameCounter >= 10 && ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (mouseClickPositionX >= (DISPLAY_WIDTH / 2) && mouseClickPositionX <= DISPLAY_WIDTH && mouseClickPositionY >= 540 && mouseClickPositionY <= DISPLAY_HEIGHT) {
                        if (currentQuoteIndex < MAX_QUESTION_TEXT_LINES - 1) {
                            currentQuoteIndex++;
                            frameCounter = 0;
                        } else if(currentQuoteIndex == MAX_QUESTION_TEXT_LINES - 1) {
                            currentQuoteIndex = 0;
                            frameCounter = 0;
                        }
                        mouseClickPositionX = 0;
                        mouseClickPositionY = 0;
                    } else if (mouseClickPositionX >= 0 && mouseClickPositionX < (DISPLAY_WIDTH / 2) && mouseClickPositionY >= 540 && mouseClickPositionY <= DISPLAY_HEIGHT) {
                        if (currentQuoteIndex < MAX_QUESTION_TEXT_LINES - 1 && currentQuoteIndex > 0) {
                            currentQuoteIndex--;
                            frameCounter = 0;
                        }
                        mouseClickPositionX = 0;
                        mouseClickPositionY = 0;
                    }
                }

                // Selecionando as alternativas e checando a resposta
                if (ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (!isAnswerCorrect(mouseClickPositionX, mouseClickPositionY, challengeList, challengeIndex)) {
                        challengeList[challengeIndex].isChallengeCompleted = 0;
                    } else {
                        challengeList[challengeIndex].isChallengeCompleted = 1;
                        houses[challengeIndex].alreadyEntered = true;
                        currentQuoteIndex = 0;

                        if (challengeIndex == 8) {
                            printf("- [GAME_RUNTIME] -> | Fim de Jogo! Obrigado por jogar, %s!\n", character.name);
                            screen = CREDITS_SCREEN;
                            isGameAlreadyStarted = false;
                        } else {
                            screen = GAME_SCREEN;
                        }
                    }
                }

                mouseClickPositionX = 0;
                mouseClickPositionY = 0;

                break;
            }

            // DEBBUGING
            // al_draw_filled_circle(character.posX, character.posY, 6, al_map_rgb(255,0,0));
            // al_draw_textf(font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH / 2, 20, 1, "X: %d  /  Y: %d", mouseClickPositionX, mouseClickPositionY);
            // al_draw_textf(font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH / 2, 40, 1, "X: %d  /  Y: %d", character.posX, character.posY);

            al_flip_display();

            frameCounter++;
        }
    }

    return 0;
}
