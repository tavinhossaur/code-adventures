#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "../headers/dependencies.h"

#define SONG_DURATION 208
#define SAMPLES 16

/*
* Função que inicializa e configura a funcionalidade de reproduzir música no jogo.
*
* returns -> um booleano para que seja possível verificar se a inicialização da música foi bem sucedida.
*/
bool initializeMusic(ALLEGRO_VOICE* voice, ALLEGRO_MIXER* mixer, ALLEGRO_AUDIO_STREAM* music) {

    if(!al_reserve_samples(SAMPLES)
            || !al_attach_mixer_to_voice(mixer, voice)
            || !al_attach_audio_stream_to_mixer(music, mixer)
            || !al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP) // Música ficará em loop
            || !al_set_audio_stream_loop_secs(music, 0, SONG_DURATION)) return false;

    return true;
}

/*
* Funcão que inicializa, instala, configura os addons do Allegro e registra as "fontes de eventos" do jogo.
* No momento, as únicas fontes são o display e o timer do jogo.
*
* returns -> um booleano para que seja possível verificar se a inicialização do jogo foi bem sucedida.
*/
bool initializeGame(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer) {

    printf("    ______          __        ___       __                 __                       \n");
    printf("   / ________  ____/ ___     /   | ____/ _   _____  ____  / /___  __________  _____ \n");
    printf("  / /   / __ \\/ __  / _ \\   / /| |/ __  | | / / _ \\/ __ \\/ __/ / / / ___/ _ \\/ ___/ \n");
    printf(" / /___/ /_/ / /_/ /  __/  / ___ / /_/ /| |/ /  __/ / / / /_/ /_/ / /  /  __(__  )  \n");
    printf(" \\____/\\____/\\____/\\___/  /_/  |_\\____/ |___/\\___/_/ /_/\\__/\\____/_/   \\___/____/   \n\n");
    printf("- release v1.0 - Novembro de 2023                                                   \n");
    printf("                                                                                  \n\n");

    printf("- [WARNING]      -> | Nao encerre esse terminal! Algumas informacoes do jogo sao exibidas aqui.\n");
    printf("- [INITIALIZING] -> | Inicializando addons do Allegro...\n");

    if (!al_init_font_addon()
            || !al_init_ttf_addon()
            || !al_init_image_addon()
            || !al_init_primitives_addon()
            || !al_install_keyboard()
            || !al_install_mouse()
            || !al_install_audio()
            || !al_init_acodec_addon()) return false;

    printf("- [INITIALIZING] -> | Addons instalados com sucesso.\n");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    printf("- [INITIALIZING] -> | Jogo carregado com sucesso.\n");
    printf("- [INITIALIZING] -> | Jogo rodando...\n");

    return true;
}

/*
* Função que encerra o jogo por completo, utilizando os métodos nativos do Allegro para "destruir"
* as variáveis instanciadas que alocaram memória.
*/
void initializeDestruction(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, ALLEGRO_AUDIO_STREAM* music, ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* menuBackground, ALLEGRO_BITMAP* menuBackgroundContinue, ALLEGRO_BITMAP* tutorialBackground, ALLEGRO_BITMAP* menuSelectGenderBoy, ALLEGRO_BITMAP* menuSelectGenderGirl, ALLEGRO_BITMAP* pauseBackground, ALLEGRO_BITMAP** movementList, ALLEGRO_MIXER* mixer, Challenge* challengeList, ALLEGRO_BITMAP* snorlax, ALLEGRO_BITMAP* snorlaxBridge) {
    printf("- [SHUTDOWN]     -> | Destruindo todas as alocacoes de memoria...\n");

    if (challengeList != NULL && sizeof(challengeList) == MAX_QUESTIONS) {
        for (int i = 0; i < MAX_QUESTIONS; i++) {
            for (int j = 0; j < MAX_QUESTION_TEXT_LINES; j++) {
                free(challengeList[i].questionText[j]);
            }
            for (int j = 0; j < MAX_ALTERNATIVES; j++) {
                free(challengeList[i].alternatives[j]);
            }
        }
        free(challengeList);
    }

    if (movementList != NULL && sizeof(movementList) == MAX_MOVEMENTS) {
        for (int i = 0; i < MAX_MOVEMENTS; i++) {
            al_destroy_bitmap(i);
        }
    }

    if (display != NULL) al_destroy_display(display);
    if (font != NULL) al_destroy_font(font);
    if (music != NULL) al_destroy_audio_stream(music);
    if (mixer != NULL) al_destroy_mixer(mixer);
    if (background != NULL) al_destroy_bitmap(background);
    if (menuBackground != NULL) al_destroy_bitmap(menuBackground);
    if (menuBackgroundContinue != NULL) al_destroy_bitmap(menuBackgroundContinue);
    if (tutorialBackground != tutorialBackground) al_destroy_bitmap(tutorialBackground);

    if (snorlax != NULL) al_destroy_bitmap(snorlax);

    al_uninstall_keyboard();
    al_uninstall_audio();
    al_uninstall_system();

    printf("- [SHUTDOWN]     -> | Jogo encerrado com sucesso.\n");
}
