#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// Protótipos das funções
bool gameInitialization(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer);
bool initializeMusic(ALLEGRO_VOICE* voice, ALLEGRO_MIXER* mixer, ALLEGRO_AUDIO_STREAM* music);
void gameDestruction(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, ALLEGRO_AUDIO_STREAM* music, ALLEGRO_MIXER* mixer);

int main()
{
	al_init();

	// Altera o nome do jogo na janela do windows
	al_set_app_name("CodeAdventure");

	// Inicializando ponteiro para as variáveis principais para o funcionamento do jogo
	ALLEGRO_DISPLAY* display = al_create_display(1600, 900);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60); // 60fps

	// Instalando addons do Allegro e criando eventos
	if (gameInitialization(display, queue, timer)) printf("- Jogo carregado com sucesso.\n");

	// Inicializando ponteiros para as variáveis de controle audiovisual do jogo
	ALLEGRO_VOICE* voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	ALLEGRO_MIXER* mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream("res/audio/tildeath.ogg", 4, 2048);
	ALLEGRO_FONT* font = al_load_ttf_font("res/fonts/Monaco.ttf", 30, 0);

	// Inicializando a música do jogo
	if (initializeMusic(voice, mixer, music)) printf("- Musica carregada com sucesso.\n");

	// Começando timer do jogo
	al_start_timer(timer);
	printf("- Jogo rodando...\n");

	// Loop principal
	while (true) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		// Encerra o loop quando o usuário clicar em fechar
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

		// Para cada "tick" do timer, a tela será desenhada novamente
		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 700, 400, 0, "Hello World()");
			al_flip_display();
		}
	}

	// Encerra o jogo limpando as funções que consomem memória
	gameDestruction(display, font, music, mixer);
}

/*
* Função que inicializa e configura a funcionalidade de reproduzir música no jogo.
*
* returns -> um booleano para que seja possível verificar se a inicialização da música foi bem sucedida.
*/
bool initializeMusic(ALLEGRO_VOICE* voice, ALLEGRO_MIXER* mixer, ALLEGRO_AUDIO_STREAM* music) {
	if(!al_reserve_samples(16)
    || !al_attach_mixer_to_voice(mixer, voice)
    || !al_attach_audio_stream_to_mixer(music, mixer)
	|| !al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP) // Música ficará em loop
    || !al_set_audio_stream_loop_secs(music, 0, 208)) return false; ; // 2 minutos e 48 segundos de música

	return true;
}

/*
* Funcão que inicializa, instala, configura os addons do Allegro e registra as "fontes de eventos" do jogo.
* No momento, as únicas fontes são o display e o timer do jogo.
*
* returns -> um booleano para que seja possível verificar se a inicialização do jogo foi bem sucedida.
*/
bool gameInitialization(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer) {

	printf("============================= CodeAdventure =============================");
	printf("\n\n- Inicializando addons do Allegro...");

	if (!al_init_font_addon() || !al_init_ttf_addon() || !al_install_keyboard() || !al_install_audio() || !al_init_acodec_addon()) return false;
	printf("\n- Addons instalados com sucesso.\n");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	return true;
}

/*
* Função que encerra o jogo por completo, utilizando os métodos nativos do Allegro para "destruir"
* as variáveis instanciadas que alocaram memória.
*/
void gameDestruction(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, ALLEGRO_AUDIO_STREAM* music, ALLEGRO_MIXER* mixer) {
	printf("- Destruindo todas as alocacoes de memoria...\n");

	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_audio_stream(music);
	al_destroy_mixer(mixer);
	al_uninstall_keyboard();

	printf("\nJogo finalizado com sucesso.\n");
}
