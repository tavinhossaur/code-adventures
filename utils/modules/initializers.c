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
bool initializeMusic(ALLEGRO_VOICE* voice, ALLEGRO_MIXER* mixer, ALLEGRO_AUDIO_STREAM* music)
{

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
bool initializeGame(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer)
{

    printf("============================= CodeAdventure =============================");
    printf("\n\n- Inicializando addons do Allegro...");

    if (!al_init_font_addon()
            || !al_init_ttf_addon()
            || !al_init_image_addon()
            || !al_init_primitives_addon()
            || !al_install_keyboard()
            || !al_install_mouse()
            || !al_install_audio()
            || !al_init_acodec_addon()) return false;

    printf("\n- Addons instalados com sucesso.\n");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    return true;
}

/*
* Função que encerra o jogo por completo, utilizando os métodos nativos do Allegro para "destruir"
* as variáveis instanciadas que alocaram memória.
*/
void initializeDestruction(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, ALLEGRO_AUDIO_STREAM* music, ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* character, ALLEGRO_MIXER* mixer)
{
    printf("- Destruindo todas as alocacoes de memoria...\n");

    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_audio_stream(music);
    al_destroy_mixer(mixer);
    al_destroy_bitmap(background);
    al_destroy_bitmap(character);
    al_uninstall_keyboard();
    al_uninstall_audio();
    al_uninstall_system();

    printf("\nJogo finalizado com sucesso.\n");
}
