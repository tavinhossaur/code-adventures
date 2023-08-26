#include <stdio.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include "utils/headers/dependencies.h"

#define KEY_PRESSED true
#define KEY_RELEASED false

int main()
{
    // testes e debugs
    // int mouseClickPositionX = 0;
    // int mouseClickPositionY = 0;

    // Controle para bloquear e desbloquear o uso das teclas de movimento
    bool blockedKey[MAX_MOVEMENT_KEYS] = {false, false, false, false};

    unsigned char key[ALLEGRO_KEY_MAX];

    al_init();

    // Altera o nome do jogo na janela do windows
    al_set_app_name("CodeAdventure");

    // Inicializando variáveis principais para o funcionamento do jogo
    ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);

    // Instalando addons do Allegro e criando eventos
    if (initializeGame(display, queue, timer)) printf("- Jogo carregado com sucesso.\n");

    // Inicializando variáveis de controle do som do jogo
    ALLEGRO_VOICE* voice = al_create_voice(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_MIXER* mixer = al_create_mixer(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

    // Inicializando variáveis dos recursos utilizados (sprites, musicas, fontes)
    ALLEGRO_BITMAP* background = al_load_bitmap(BACKGROUND_FILE);
    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream(MUSIC_THEME, SONG_BUFFER, SAMPLES);
    ALLEGRO_FONT* font = al_load_ttf_font(TEXT_FONT, FONT_SIZE, 0);

    // Carregando a lista de colisões do mapa
    CollisionBlock *collisions = getCollisionBlocks();

    // Carregando a lista de bitmaps dos movimentos do personagem com base no gênero escolhido
    ALLEGRO_BITMAP **movementList = getCharacterMovementSprites("girl");

    // Criando um personagem
    Character character = {CHARACTER_START_X, CHARACTER_START_Y, S, movementList[STANDBY_DOWN]};

    // Inicializando a música do jogo
    if (initializeMusic(voice, mixer, music)) printf("- Musica carregada com sucesso.\n");

    // Começando timer do jogo
    al_start_timer(timer);
    printf("- Jogo rodando...\n");

    int frameCounter = 0;

    // Loop principal
    while (true)
    {
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
                return 0;
                break;

            /* case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(event.mouse.button & 1) {
                    mouseClickPositionX = event.mouse.x;
                    mouseClickPositionY = event.mouse.y;
                } break; */
        }

        // Lógica em tempo de execução (main runtime script)
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            int i;

            for(i = 0; i < ALLEGRO_KEY_MAX; i++) key[i] &= KEY_PRESSED;

            // Limpa a tela
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Desenha o mapa
            al_draw_bitmap(background, 0, 0, 0);

            // Lógica de detecção de colisões
            runCollisionDetection(collisions, character, blockedKey);

            // Lógica de movimentação com animação baseada na direção e FPS
            updateCharacterMovement(&character, frameCounter, movementList, blockedKey, key);

            // Desenha o personagem
            al_draw_scaled_bitmap(
                character.currentMovementBitmap,
                0, 0,
                al_get_bitmap_width(character.currentMovementBitmap),
                al_get_bitmap_height(character.currentMovementBitmap),
                character.posX - CHARACTER_X_HITBOX_AJUST, character.posY - CHARACTER_Y_HITBOX_AJUST,
                CHARACTER_WIDTH, CHARACTER_HEIGHT, 0);

            // Desenha todas as colisões (não estará na versão final do jogo)
            // drawCollision(collisions);

            // al_draw_filled_circle(character.posX, character.posY, 6, al_map_rgb(10,0,0));
            // al_draw_textf(font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH / 2, 20, 1, "X: %d  /  Y: %d", mouseClickPositionX, mouseClickPositionY);
            // al_draw_textf(font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH / 2, 40, 1, "X: %d  /  Y: %d", character.posX, character.posY);

            al_flip_display();

            frameCounter++;
        }
    }

    // Encerra o jogo limpando as funções que consomem memória
    initializeDestruction(display, font, music, background, character, mixer);
}
