#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define BACKGROUND_FILE "res/sprites/city_background.png"
#define CODE_FONT "res/fonts/Monaco.ttf"
#define MUSIC_THEME "res/audio/tildeath.ogg"

#define DISPLAY_WIDTH 768
#define DISPLAY_HEIGHT 641
#define FPS 60

int main()
{
	al_init();

	// Altera o nome do jogo na janela do windows
	al_set_app_name("CodeAdventure");

	// Inicializando ponteiro para as variáveis principais para o funcionamento do jogo
	ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);

	// Instalando addons do Allegro e criando eventos
	if (initializeGame(display, queue, timer)) printf("- Jogo carregado com sucesso.\n");

	// Inicializando ponteiros para as variáveis de controle audiovisual do jogo
	ALLEGRO_VOICE* voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	ALLEGRO_MIXER* mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

	ALLEGRO_BITMAP* background = al_load_bitmap(BACKGROUND_FILE);
	ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream(MUSIC_THEME, 4, 2048);
	ALLEGRO_FONT* font = al_load_ttf_font(CODE_FONT, 30, 0);

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
			al_draw_bitmap(background, 0, 0, 0);
			al_flip_display();
		}
	}

	// Encerra o jogo limpando as funções que consomem memória
	initializeDestruction(display, font, music, background, mixer);
}
