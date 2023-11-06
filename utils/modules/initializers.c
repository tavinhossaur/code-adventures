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
* Fun��o que inicializa e configura a funcionalidade de reproduzir m�sica no jogo.
*
* returns -> um booleano para que seja poss�vel verificar se a inicializa��o da m�sica foi bem sucedida.
*/
bool initializeMusic(ALLEGRO_VOICE* voice, ALLEGRO_MIXER* mixer, ALLEGRO_AUDIO_STREAM* music)
{

    if(!al_reserve_samples(SAMPLES)
            || !al_attach_mixer_to_voice(mixer, voice)
            || !al_attach_audio_stream_to_mixer(music, mixer)
            || !al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP) // M�sica ficar� em loop
            || !al_set_audio_stream_loop_secs(music, 0, SONG_DURATION)) return false;

    return true;
}

/*
* Func�o que inicializa, instala, configura os addons do Allegro e registra as "fontes de eventos" do jogo.
* No momento, as �nicas fontes s�o o display e o timer do jogo.
*
* returns -> um booleano para que seja poss�vel verificar se a inicializa��o do jogo foi bem sucedida.
*/
bool initializeGame(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer)
{

    printf("    ______          __        ___       __                 __                       \n");
    printf("   / ________  ____/ ___     /   | ____/ _   _____  ____  / /___  __________  _____ \n");
    printf("  / /   / __ \\/ __  / _ \\   / /| |/ __  | | / / _ \\/ __ \\/ __/ / / / ___/ _ \\/ ___/ \n");
    printf(" / /___/ /_/ / /_/ /  __/  / ___ / /_/ /| |/ /  __/ / / / /_/ /_/ / /  /  __(__  )  \n");
    printf(" \\____/\\____/\\____/\\___/  /_/  |_\\____/ |___/\\___/_/ /_/\\__/\\____/_/   \\___/____/   \n");
    printf("                                                                                    \n");

    printf("\n- [INITIALIZING] -> | Inicializando addons do Allegro...");

    if (!al_init_font_addon()
            || !al_init_ttf_addon()
            || !al_init_image_addon()
            || !al_init_primitives_addon()
            || !al_install_keyboard()
            || !al_install_mouse()
            || !al_install_audio()
            || !al_init_acodec_addon()) return false;

    printf("\n- [INITIALIZING] -> | Addons instalados com sucesso.");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    printf("\n- [INITIALIZING] -> | Jogo carregado com sucesso.");
    printf("\n- [INITIALIZING] -> | Jogo rodando...");

    return true;
}

/*
* Fun��o que encerra o jogo por completo, utilizando os m�todos nativos do Allegro para "destruir"
* as vari�veis instanciadas que alocaram mem�ria.
*/
void initializeDestruction(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, ALLEGRO_AUDIO_STREAM* music, ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* menuBackground, ALLEGRO_BITMAP* menuBackgroundContinue, ALLEGRO_BITMAP* tutorialBackground, ALLEGRO_BITMAP* menuSelectGenderBoy, ALLEGRO_BITMAP* menuSelectGenderGirl, ALLEGRO_BITMAP* pauseBackground, ALLEGRO_BITMAP* character, ALLEGRO_MIXER* mixer, Challenge* challengeList)
{
    printf("\n- [INITIALIZING] -> | Destruindo todas as alocacoes de memoria...");

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        for (int j = 0; j < MAX_QUESTION_TEXT_LINES; j++) {
            free(challengeList[i].questionText[j]);
        }
        for (int j = 0; j < MAX_ALTERNATIVES; j++) {
            free(challengeList[i].alternatives[j]);
        }
    }
    free(challengeList);

    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_audio_stream(music);
    al_destroy_mixer(mixer);
    al_destroy_bitmap(background);
    al_destroy_bitmap(menuBackground);
    al_destroy_bitmap(menuBackgroundContinue);
    al_destroy_bitmap(tutorialBackground);
    al_destroy_bitmap(character);
    al_uninstall_keyboard();
    al_uninstall_audio();
    al_uninstall_system();

    printf("\n- [SHUTDOWN] -> | Jogo encerrado com sucesso.");
}
