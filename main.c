#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



#include <allegro5/allegro_primitives.h>//<<<--------------biblioteca para desenhar os quadrados e circulos e alciliar na criaçao da colisao



#define BACKGROUND_FILE "res/sprites/city_background.png"
#define CODE_FONT "res/fonts/Monaco.ttf"
#define MUSIC_THEME "res/audio/tildeath.ogg"

#define DISPLAY_WIDTH 768
#define DISPLAY_HEIGHT 641
#define FPS 60



#define SEEN 1//<<<--------------para funcionar a movimentacao via teclado
#define RELEASED 2//<<<--------------para funcionar a movimentacao via teclado

struct Personagem//<<---no momento um circulo pra testar a colisao
{
    int posX;
    int posY;
    int raio;
    int dir;// w1,d2,s3,a4
};

struct Parede//<<------quadrado que simboliza a colisao
{
    //ponta superior esuqerda
    int UPEposX;
    int UPEposY;
    //ponta inferior direita
    int DOWDposX;
    int DOWDposY;
};





int main()
{



//-----------------------------------------------------------------------------------------------------------------------------
    int mouseClickPositionX = 0;//---variaveis para guardar a posisão do clique do mouse
    int mouseClickPositionY = 0;
    int actW = 0;
    int actA = 0;
    int actS = 0;
    int actD = 0;
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
//-----------------------------------------------------------------------------------------------------------------------------



	al_init();





//-----------------------------------------------------------------------------------------------------------------------------
    al_init_primitives_addon();//biblioteca de formas primitivas

    al_install_keyboard();
    al_install_mouse();
//-----------------------------------------------------------------------------------------------------------------------------




	// Altera o nome do jogo na janela do windows
	al_set_app_name("CodeAdventure");

	// Inicializando ponteiro para as variáveis principais para o funcionamento do jogo
	ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);

	// Instalando addons do Allegro e criando eventos
	if (initializeGame(display, queue, timer)) printf("- Jogo carregado com sucesso.\n");






//-----------------------------------------------------------------------------------------------------------------------------
	al_register_event_source(queue, al_get_mouse_event_source());//provavelmente esse iria pra > initializeGame
//-----------------------------------------------------------------------------------------------------------------------------






	// Inicializando ponteiros para as variáveis de controle audiovisual do jogo
	ALLEGRO_VOICE* voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	ALLEGRO_MIXER* mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

	ALLEGRO_BITMAP* background = al_load_bitmap(BACKGROUND_FILE);
	ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream(MUSIC_THEME, 4, 2048);
	ALLEGRO_FONT* font = al_load_ttf_font(CODE_FONT, 30, 0);






//-----------------------------------------------------------------------------------------------------------------------------
	struct Personagem circulo = {15, 338, 6, 1};


	//-----quadrados que indicam area de colisao----------
	//------------limites (vermelho)----------------------
	struct Parede quadrado1 = {0,0,20,208};//
	struct Parede quadrado2 = {20,0,28,192};//
	struct Parede quadrado3 = {28,0,134,208};//
	struct Parede quadrado4 = {0,250,134,326};//
	struct Parede quadrado5 = {0,364,118,641};//
	struct Parede quadrado6 = {118,556,246,641};//
	struct Parede quadrado7 = {0,506,421,528};//
	struct Parede quadrado8 = {427,506,630,528};//
	struct Parede quadrado9 = {612,317,630,528};//
	struct Parede quadrado10 = {650,317,768,641};//
	struct Parede quadrado11 = {650,177,768,287};//
	struct Parede quadrado12 = {602,115,768,177};//
	struct Parede quadrado13 = {620,0,768,115};//
	struct Parede quadrado14 = {460,0,768,80};//
	struct Parede quadrado15 = {331,0,357,195};//
	struct Parede quadrado16 = {0,0,357,96};//
	struct Parede quadrado17 = {395,0,419,128};//
	struct Parede quadrado18 = {419,0,460,38};//
	struct Parede quadrado19 = {522,556,768,641};//
	struct Parede quadrado20 = {460,0,479,140};//
	//--------------morros(azul)-------------------------
	struct Parede quadrado21 = {170,258,202,275};//
	struct Parede quadrado22 = {405,290,442,308};//
	struct Parede quadrado23 = {509,322,612,340};//
	//--------------casas(verdes)-------------------------
	struct Parede quadrado24 = {134,124,164,195};//
	struct Parede quadrado25 = {172,124,276,195};//
	struct Parede quadrado26 = {284,124,357,195};//
	struct Parede quadrado27 = {164,135,284,177};//
	struct Parede quadrado28 = {202,226,244,288};//
	struct Parede quadrado29 = {252,226,326,288};//
	struct Parede quadrado30 = {244,226,252,273};//
	struct Parede quadrado31 = {315,244,355,320};//
	struct Parede quadrado32 = {363,244,405,320};//
	struct Parede quadrado33 = {355,244,363,305};//
	struct Parede quadrado34 = {442,267,499,349};//
	struct Parede quadrado35 = {509,267,566,349};//
	struct Parede quadrado36 = {499,267,509,338};//
	struct Parede quadrado37 = {442,130,483,193};//
	struct Parede quadrado38 = {492,130,566,193};//
	struct Parede quadrado39 = {483,130,492,180};//
	struct Parede quadrado40 = {186,370,210,465};//
	struct Parede quadrado41 = {241,370,262,465};//
	struct Parede quadrado42 = {210,370,241,455};//
	struct Parede quadrado43 = {330,402,372,464};//
	struct Parede quadrado44 = {380,405,467,464};//
	struct Parede quadrado45 = {475,405,582,464};//
	struct Parede quadrado46 = {372,405,475,454};//
	//------------objetos ex: placa,bike e UMA CERCA DE PLANTA(roxo)----
	struct Parede quadrado47 = {539,193,566,267};//
	struct Parede quadrado48 = {426,323,442,349};//
	struct Parede quadrado49 = {314,394,330,414};//
	struct Parede quadrado50 = {166,394,186,465};//
	struct Parede quadrado51 = {300,556,470,641};//<---------------
	struct Parede quadrado52 = {428,393,502,420};

//-----------------------------------------------------------------------------------------------------------------------------







	// Inicializando a música do jogo
	if (initializeMusic(voice, mixer, music)) printf("- Musica carregada com sucesso.\n");

	// Começando timer do jogo
	al_start_timer(timer);
	printf("- Jogo rodando...\n");

	// Loop principal
	while (true) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);







//-----------------------------------------------------------------------------------------------------------------------------
		switch (event.type){
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = SEEN | RELEASED;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= RELEASED;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(event.mouse.button & 1){
                    mouseClickPositionX = event.mouse.x;
                    mouseClickPositionY = event.mouse.y;
                }
                break;
        }

        if (event.type == ALLEGRO_EVENT_TIMER){

            for(int i = 0; i<ALLEGRO_KEY_MAX; i++){
                key[i] &=SEEN;
            }

//--------------colisao--------------------------------------------------------------------------------------------------------
            //-------area externa-----------------
            if(circulo.posX <= 1){
                actA = 1;
            }
            if(circulo.posX >= DISPLAY_WIDTH-1){
                actD = 1;
            }
            if(circulo.posY <=1){
                actW = 1;
            }
            if(circulo.posY >= DISPLAY_HEIGHT-1){
                actS = 1;
            }
            //-----------------------------------
            //----------------------------------------------------area vermelha-----------------------------------------------------------
            //-------------quadrado1 = {0,0,20,208}
            if(circulo.posX >=0 && circulo.posY >=0 && circulo.posX <=20 && circulo.posY <= 208){
                if(circulo.posX >= 0-1 && circulo.posX <= 0){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 20+1 && circulo.posX >= 20){
                    actA=1;
                }
                if(circulo.posY <= 208+1 && circulo.posY >= 208){
                    actW=1;
                }
            }
            //-------------quadrado2 = {20,0,28,192}
            if(circulo.posX >=20 && circulo.posY >=0 && circulo.posX <=28 && circulo.posY <=192){
                if(circulo.posX >= 20-1 && circulo.posX <= 20){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 28+1 && circulo.posX >= 28){
                    actA=1;
                }
                if(circulo.posY <= 192+1 && circulo.posY >= 192){
                    actW=1;
                }
            }
            //-------------quadrado3 = {28,0,134,208}
            if(circulo.posX >=28 && circulo.posY >=0 && circulo.posX <=134 && circulo.posY <= 208){
                if(circulo.posX >= 28-1 && circulo.posX <= 28){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 134+1 && circulo.posX >= 134){
                    actA=1;
                }
                if(circulo.posY <= 208+1 && circulo.posY >= 208){
                    actW=1;
                }
            }
            //-------------{0,364,118,641}
            if(circulo.posX <= 134 && circulo.posY <= 326 && circulo.posY >= 250 && circulo.posX >= -2){
                if(circulo.posX <= 134+1 && circulo.posX >= 134){
                    actA=1;
                }
                if(circulo.posY <= 326+1 && circulo.posY >= 326){
                    actW=1;
                }
                if(circulo.posY >= 250-1 && circulo.posY <= 250){
                    actS=1;
                }
                if(circulo.posX >= 0-1 && circulo.posX <= 0){
                    actD=1;
                }
            }
            //-------------{0,364,118,641}
            if(circulo.posX >=0 && circulo.posY >=364 && circulo.posX <=118 && circulo.posY <= 641){
                if(circulo.posX >= 0-1 && circulo.posX <= 0){
                    actD=1;
                }
                if(circulo.posY >= 364-1 && circulo.posY <= 364){
                    actS=1;
                }
                if(circulo.posX <= 118+1 && circulo.posX >= 118){
                    actA=1;
                }
                if(circulo.posY <= 641+1 && circulo.posY >= 641){
                    actW=1;
                }
            }
            //-------------{118,556,246,641}
            if(circulo.posX >=118 && circulo.posY >=556 && circulo.posX <=246 && circulo.posY <= 641){
                if(circulo.posX >= 118-1 && circulo.posX <= 118){
                    actD=1;
                }
                if(circulo.posY >= 556-1 && circulo.posY <= 556){
                    actS=1;
                }
                if(circulo.posX <= 246+1 && circulo.posX >= 246){
                    actA=1;
                }
                if(circulo.posY <= 641+1 && circulo.posY >= 641){
                    actW=1;
                }
            }
            //-------------{0,506,421,528}
            if(circulo.posX >=0 && circulo.posY >=506 && circulo.posX <=421 && circulo.posY <= 528){
                if(circulo.posX >= 0-1 && circulo.posX <= 0){
                    actD=1;
                }
                if(circulo.posY >= 506-1 && circulo.posY <= 506){
                    actS=1;
                }
                if(circulo.posX <= 421+1 && circulo.posX >= 421){
                    actA=1;
                }
                if(circulo.posY <= 528+1 && circulo.posY >= 528){
                    actW=1;
                }
            }
            //-------------quadrado8 = {427,506,630,528}
            if(circulo.posX >=427 && circulo.posY >=506 && circulo.posX <=630 && circulo.posY <= 528){
                if(circulo.posX >= 427-1 && circulo.posX <= 427){
                    actD=1;
                }
                if(circulo.posY >= 506-1 && circulo.posY <= 506){
                    actS=1;
                }
                if(circulo.posX <= 630+1 && circulo.posX >= 630){
                    actA=1;
                }
                if(circulo.posY <= 528+1 && circulo.posY >= 528){
                    actW=1;
                }
            }
            //-------------quadrado9 = {612,317,630,528}
            if(circulo.posX >=612 && circulo.posY >=317 && circulo.posX <=630 && circulo.posY <= 528){
                if(circulo.posX >= 612-1 && circulo.posX <= 612){
                    actD=1;
                }
                if(circulo.posY >= 317-1 && circulo.posY <= 317){
                    actS=1;
                }
                if(circulo.posX <= 630+1 && circulo.posX >= 630){
                    actA=1;
                }
                if(circulo.posY <= 528+1 && circulo.posY >= 528){
                    actW=1;
                }
            }
            //-------------quadrado10 = {650,317,768,641}
            if(circulo.posX >=650 && circulo.posY >=317 && circulo.posX <=768 && circulo.posY <= 641){
                if(circulo.posX >= 650-1 && circulo.posX <= 650){
                    actD=1;
                }
                if(circulo.posY >= 317-1 && circulo.posY <= 317){
                    actS=1;
                }
                if(circulo.posX <= 768+1 && circulo.posX >= 768){
                    actA=1;
                }
                if(circulo.posY <= 641+1 && circulo.posY >= 641){
                    actW=1;
                }
            }
            //-------------quadrado11 = {650,177,768,287}
            if(circulo.posX >=650 && circulo.posY >=177 && circulo.posX <=768 && circulo.posY <= 287){
                if(circulo.posX >= 650-1 && circulo.posX <= 650){
                    actD=1;
                }
                if(circulo.posY >= 177-1 && circulo.posY <= 177){
                    actS=1;
                }
                if(circulo.posX <= 768+1 && circulo.posX >= 768){
                    actA=1;
                }
                if(circulo.posY <= 287+1 && circulo.posY >= 287){
                    actW=1;
                }
            }
            //-------------quadrado12 = {602,115,768,177}
            if(circulo.posX >=602 && circulo.posY >=115 && circulo.posX <=768 && circulo.posY <= 177){
                if(circulo.posX >= 602-1 && circulo.posX <= 602){
                    actD=1;
                }
                if(circulo.posY >= 115-1 && circulo.posY <= 115){
                    actS=1;
                }
                if(circulo.posX <= 768+1 && circulo.posX >= 768){
                    actA=1;
                }
                if(circulo.posY <= 177+1 && circulo.posY >= 177){
                    actW=1;
                }
            }
            //-------------quadrado13 = {620,0,768,115}
            if(circulo.posX >=620 && circulo.posY >=0 && circulo.posX <=768 && circulo.posY <= 115){
                if(circulo.posX >= 620-1 && circulo.posX <= 620){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 768+1 && circulo.posX >= 768){
                    actA=1;
                }
                if(circulo.posY <= 115+1 && circulo.posY >= 115){
                    actW=1;
                }
            }
            //-------------quadrado14 = {460,0,768,80}
            if(circulo.posX >=460 && circulo.posY >=0 && circulo.posX <=768 && circulo.posY <= 80){
                if(circulo.posX >= 460-1 && circulo.posX <= 460){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 768+1 && circulo.posX >= 768){
                    actA=1;
                }
                if(circulo.posY <= 80+1 && circulo.posY >= 80){
                    actW=1;
                }
            }
            //-------------quadrado15 = {331,0,357,195}
            if(circulo.posX >=331 && circulo.posY >=0 && circulo.posX <=357 && circulo.posY <= 195){
                if(circulo.posX >= 331-1 && circulo.posX <= 331){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 357+1 && circulo.posX >= 357){
                    actA=1;
                }
                if(circulo.posY <= 195+1 && circulo.posY >= 195){
                    actW=1;
                }
            }
            //-------------quadrado16 = {0,0,357,96}
            if(circulo.posX >=0 && circulo.posY >=0 && circulo.posX <=357 && circulo.posY <= 96){
                if(circulo.posX >= 0-1 && circulo.posX <= 0){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 357+1 && circulo.posX >= 357){
                    actA=1;
                }
                if(circulo.posY <= 96+1 && circulo.posY >= 96){
                    actW=1;
                }
            }
            //-------------quadrado17 = {395,0,419,128}
            if(circulo.posX >=395 && circulo.posY >=0 && circulo.posX <=419 && circulo.posY <= 128){
                if(circulo.posX >= 395-1 && circulo.posX <= 395){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 419+1 && circulo.posX >= 419){
                    actA=1;
                }
                if(circulo.posY <= 128+1 && circulo.posY >= 128){
                    actW=1;
                }
            }
            //-------------quadrado18 = {419,0,460,38}
            if(circulo.posX >=419 && circulo.posY >=0 && circulo.posX <=460 && circulo.posY <= 38){
                if(circulo.posX >= 419-1 && circulo.posX <= 419){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 460+1 && circulo.posX >= 460){
                    actA=1;
                }
                if(circulo.posY <= 38+1 && circulo.posY >= 38){
                    actW=1;
                }
            }
            //-------------quadrado19 = {522,556,768,641}
            if(circulo.posX >=522 && circulo.posY >=556 && circulo.posX <=768 && circulo.posY <= 641){
                if(circulo.posX >= 522-1 && circulo.posX <= 522){
                    actD=1;
                }
                if(circulo.posY >= 556-1 && circulo.posY <= 556){
                    actS=1;
                }
                if(circulo.posX <= 768+1 && circulo.posX >= 768){
                    actA=1;
                }
                if(circulo.posY <= 641+1 && circulo.posY >= 641){
                    actW=1;
                }
            }
            //-------------quadrado20 = {460,0,479,140}
            if(circulo.posX >=460 && circulo.posY >=0 && circulo.posX <=479 && circulo.posY <= 140){
                if(circulo.posX >= 460-1 && circulo.posX <= 460){
                    actD=1;
                }
                if(circulo.posY >= 0-1 && circulo.posY <= 0){
                    actS=1;
                }
                if(circulo.posX <= 479+1 && circulo.posX >= 479){
                    actA=1;
                }
                if(circulo.posY <= 140+1 && circulo.posY >= 140){
                    actW=1;
                }
            }
            //-------------quadrado21 = {170,258,202,275}
            if(circulo.posX >=170 && circulo.posY >=258 && circulo.posX <=202 && circulo.posY <= 275){
                if(circulo.posX >= 170-1 && circulo.posX <= 170){
                    actD=1;
                }
                if(circulo.posX <= 202+1 && circulo.posX >= 202){
                    actA=1;
                }
                if(circulo.posY <= 275+1 && circulo.posY >= 275){
                    actW=1;
                }
            }
            //-------------quadrado22 = {405,290,442,308}
            if(circulo.posX >=405 && circulo.posY >=290 && circulo.posX <=442 && circulo.posY <= 308){
                if(circulo.posX >= 405-1 && circulo.posX <= 405){
                    actD=1;
                }
                if(circulo.posX <= 442+1 && circulo.posX >= 442){
                    actA=1;
                }
                if(circulo.posY <= 308+1 && circulo.posY >= 308){
                    actW=1;
                }
            }
            //-------------quadrado23 = {509,322,612,340}
            if(circulo.posX >=509 && circulo.posY >=322 && circulo.posX <=612 && circulo.posY <= 340){
                if(circulo.posX >= 509-1 && circulo.posX <= 509){
                    actD=1;
                }
                if(circulo.posX <= 612+1 && circulo.posX >= 612){
                    actA=1;
                }
                if(circulo.posY <= 340+1 && circulo.posY >= 340){
                    actW=1;
                }
            }
            //-------------quadrado24 = {134,124,164,195}
            if(circulo.posX >=134 && circulo.posY >=124 && circulo.posX <=164 && circulo.posY <= 195){
                if(circulo.posX >= 134-1 && circulo.posX <= 134){
                    actD=1;
                }
                if(circulo.posY >= 124-1 && circulo.posY <= 124){
                    actS=1;
                }
                if(circulo.posX <= 164+1 && circulo.posX >= 164){
                    actA=1;
                }
                if(circulo.posY <= 195+1 && circulo.posY >= 195){
                    actW=1;
                }
            }
            //-------------quadrado25 = {172,124,276,195}
            if(circulo.posX >=172 && circulo.posY >=124 && circulo.posX <=286 && circulo.posY <= 195){
                if(circulo.posX >= 172-1 && circulo.posX <= 172){
                    actD=1;
                }
                if(circulo.posY >= 124-1 && circulo.posY <= 124){
                    actS=1;
                }
                if(circulo.posX <= 276+1 && circulo.posX >= 276){
                    actA=1;
                }
                if(circulo.posY <= 195+1 && circulo.posY >= 195 && circulo.posX <=276){
                    actW=1;
                }
            }
            //-------------quadrado26 = {284,124,357,195}
            if(circulo.posX >=284 && circulo.posY >=124 && circulo.posX <=357 && circulo.posY <= 195){
                if(circulo.posX >= 284-1 && circulo.posX <= 284){
                    actD=1;
                }
                if(circulo.posY >= 124-1 && circulo.posY <= 124){
                    actS=1;
                }
                if(circulo.posX <= 357+1 && circulo.posX >= 357){
                    actA=1;
                }
                if(circulo.posY <= 195+1 && circulo.posY >= 195){
                    actW=1;
                }
            }
            //-------------quadrado27 = {164,135,284,177}
            if(circulo.posX >=164 && circulo.posY >=135 && circulo.posX <=284 && circulo.posY <= 177){
                if(circulo.posX >= 164-1 && circulo.posX <= 164){
                    actD=1;
                }
                if(circulo.posY >= 135-1 && circulo.posY <= 135){
                    actS=1;
                }
                if(circulo.posX <= 284+1 && circulo.posX >= 284){
                    actA=1;
                }
                if(circulo.posY <= 177+1 && circulo.posY >= 177){
                    actW=1;
                }
            }
            //-------------quadrado28 = {202,226,244,288}
            if(circulo.posX >=202 && circulo.posY >=226 && circulo.posX <=244 && circulo.posY <= 288){
                if(circulo.posX >= 202-1 && circulo.posX <= 202){
                    actD=1;
                }
                if(circulo.posY >= 226-1 && circulo.posY <= 226){
                    actS=1;
                }
                if(circulo.posX <= 244+1 && circulo.posX >= 244){
                    actA=1;
                }
                if(circulo.posY <= 288+1 && circulo.posY >= 288){
                    actW=1;
                }
            }
            //-------------quadrado29 = {252,226,326,288}
            if(circulo.posX >=252 && circulo.posY >=226 && circulo.posX <=326 && circulo.posY <= 288){
                if(circulo.posX >= 252-1 && circulo.posX <= 252){
                    actD=1;
                }
                if(circulo.posY >= 226-1 && circulo.posY <= 226){
                    actS=1;
                }
                if(circulo.posX <= 326+1 && circulo.posX >= 326){
                    actA=1;
                }
                if(circulo.posY <= 288+1 && circulo.posY >= 288){
                    actW=1;
                }
            }
            //-------------quadrado30 = {244,226,252,273}
            if(circulo.posX >=244 && circulo.posY >=226 && circulo.posX <=252 && circulo.posY <= 273){
                if(circulo.posX >= 244-1 && circulo.posX <= 244){
                    actD=1;
                }
                if(circulo.posY >= 226-1 && circulo.posY <= 226){
                    actS=1;
                }
                if(circulo.posX <= 252+1 && circulo.posX >= 252){
                    actA=1;
                }
                if(circulo.posY <= 273+1 && circulo.posY >= 273){
                    actW=1;
                }
            }
            //-------------quadrado31 = {315,244,355,320}
            if(circulo.posX >=315 && circulo.posY >=244 && circulo.posX <=355 && circulo.posY <= 320){
                if(circulo.posX >= 315-1 && circulo.posX <= 315){
                    actD=1;
                }
                if(circulo.posY >= 244-1 && circulo.posY <= 244){
                    actS=1;
                }
                if(circulo.posX <= 355+1 && circulo.posX >= 355){
                    actA=1;
                }
                if(circulo.posY <= 320+1 && circulo.posY >= 320){
                    actW=1;
                }
            }
            //-------------quadrado32 = {363,244,405,320}
            if(circulo.posX >=363 && circulo.posY >=244 && circulo.posX <=405 && circulo.posY <= 320){
                if(circulo.posX >= 363-1 && circulo.posX <= 363){
                    actD=1;
                }
                if(circulo.posY >= 244-1 && circulo.posY <= 244){
                    actS=1;
                }
                if(circulo.posX <= 405+1 && circulo.posX >= 405){
                    actA=1;
                }
                if(circulo.posY <= 320+1 && circulo.posY >= 320){
                    actW=1;
                }
            }
            //-------------quadrado33 = {355,244,363,305}
            if(circulo.posX >=355 && circulo.posY >=244 && circulo.posX <=363 && circulo.posY <= 305){
                if(circulo.posX >= 355-1 && circulo.posX <= 355){
                    actD=1;
                }
                if(circulo.posY >= 244-1 && circulo.posY <= 244){
                    actS=1;
                }
                if(circulo.posX <= 363+1 && circulo.posX >= 363){
                    actA=1;
                }
                if(circulo.posY <= 305+1 && circulo.posY >= 305){
                    actW=1;
                }
            }
            //-------------quadrado34 = {442,267,499,349}
            if(circulo.posX >=442 && circulo.posY >=267 && circulo.posX <=499 && circulo.posY <= 349){
                if(circulo.posX >= 442-1 && circulo.posX <= 442){
                    actD=1;
                }
                if(circulo.posY >= 267-1 && circulo.posY <= 267){
                    actS=1;
                }
                if(circulo.posX <= 499+1 && circulo.posX >= 499){
                    actA=1;
                }
                if(circulo.posY <= 349+1 && circulo.posY >= 349){
                    actW=1;
                }
            }
            //-------------quadrado35 = {509,267,566,349}
            if(circulo.posX >=509 && circulo.posY >=267 && circulo.posX <=566 && circulo.posY <= 349){
                if(circulo.posX >= 509-1 && circulo.posX <= 509){
                    actD=1;
                }
                if(circulo.posY >= 267-1 && circulo.posY <= 267){
                    actS=1;
                }
                if(circulo.posX <= 566+1 && circulo.posX >= 566){
                    actA=1;
                }
                if(circulo.posY <= 349+1 && circulo.posY >= 349){
                    actW=1;
                }
            }
            //-------------quadrado36 = {499,267,509,338}
            if(circulo.posX >=499 && circulo.posY >=267 && circulo.posX <=509 && circulo.posY <= 338){
                if(circulo.posX >= 499-1 && circulo.posX <= 499){
                    actD=1;
                }
                if(circulo.posY >= 267-1 && circulo.posY <= 267){
                    actS=1;
                }
                if(circulo.posX <= 509+1 && circulo.posX >= 509){
                    actA=1;
                }
                if(circulo.posY <= 338+1 && circulo.posY >= 338){
                    actW=1;
                }
            }
            //-------------quadrado37 = {442,130,483,193}
            if(circulo.posX >=442 && circulo.posY >=130 && circulo.posX <=483 && circulo.posY <= 193){
                if(circulo.posX >= 442-1 && circulo.posX <= 442){
                    actD=1;
                }
                if(circulo.posY >= 130-1 && circulo.posY <= 130){
                    actS=1;
                }
                if(circulo.posX <= 483+1 && circulo.posX >= 483){
                    actA=1;
                }
                if(circulo.posY <= 193+1 && circulo.posY >= 193){
                    actW=1;
                }
            }
            //-------------quadrado38 = {492,130,566,193}
            if(circulo.posX >=492 && circulo.posY >=130 && circulo.posX <=566 && circulo.posY <= 193){
                if(circulo.posX >= 492-1 && circulo.posX <= 492){
                    actD=1;
                }
                if(circulo.posY >= 130-1 && circulo.posY <= 130){
                    actS=1;
                }
                if(circulo.posX <= 566+1 && circulo.posX >= 566){
                    actA=1;
                }
                if(circulo.posY <= 193+1 && circulo.posY >= 193){
                    actW=1;
                }
            }
            //-------------quadrado39 = {483,130,492,180}
            if(circulo.posX >=483 && circulo.posY >=130 && circulo.posX <=492 && circulo.posY <= 180){
                if(circulo.posX >= 483-1 && circulo.posX <= 483){
                    actD=1;
                }
                if(circulo.posY >= 130-1 && circulo.posY <= 130){
                    actS=1;
                }
                if(circulo.posX <= 492+1 && circulo.posX >= 492){
                    actA=1;
                }
                if(circulo.posY <= 180+1 && circulo.posY >= 180){
                    actW=1;
                }
            }
            //-------------quadrado40 = {186,370,210,465}
            if(circulo.posX >=186 && circulo.posY >=370 && circulo.posX <=210 && circulo.posY <= 465){
                if(circulo.posX >= 186-1 && circulo.posX <= 186){
                    actD=1;
                }
                if(circulo.posY >= 370-1 && circulo.posY <= 370){
                    actS=1;
                }
                if(circulo.posX <= 210+1 && circulo.posX >= 210){
                    actA=1;
                }
                if(circulo.posY <= 465+1 && circulo.posY >= 465){
                    actW=1;
                }
            }
            //-------------quadrado41 = {241,370,262,465}
            if(circulo.posX >=241 && circulo.posY >=370 && circulo.posX <=262 && circulo.posY <= 465){
                if(circulo.posX >= 241-1 && circulo.posX <= 241){
                    actD=1;
                }
                if(circulo.posY >= 370-1 && circulo.posY <= 370){
                    actS=1;
                }
                if(circulo.posX <= 262+1 && circulo.posX >= 262){
                    actA=1;
                }
                if(circulo.posY <= 465+1 && circulo.posY >= 465){
                    actW=1;
                }
            }
            //-------------quadrado42 = {210,370,241,455}
            if(circulo.posX >=210 && circulo.posY >=370 && circulo.posX <=241 && circulo.posY <= 455){
                if(circulo.posX >= 210-1 && circulo.posX <= 210){
                    actD=1;
                }
                if(circulo.posY >= 370-1 && circulo.posY <= 370){
                    actS=1;
                }
                if(circulo.posX <= 241+1 && circulo.posX >= 241){
                    actA=1;
                }
                if(circulo.posY <= 455+1 && circulo.posY >= 455){
                    actW=1;
                }
            }
            //-------------quadrado43 = {330,402,372,464}
            if(circulo.posX >=330 && circulo.posY >=402 && circulo.posX <=372 && circulo.posY <= 464){
                if(circulo.posX >= 330-1 && circulo.posX <= 330){
                    actD=1;
                }
                if(circulo.posY >= 402-1 && circulo.posY <= 402){
                    actS=1;
                }
                if(circulo.posX <= 372+1 && circulo.posX >= 372){
                    actA=1;
                }
                if(circulo.posY <= 464+1 && circulo.posY >= 464){
                    actW=1;
                }
            }
            //-------------quadrado44 = {380,405,467,464}
            if(circulo.posX >=380 && circulo.posY >=405 && circulo.posX <=467 && circulo.posY <= 464){
                if(circulo.posX >= 380-1 && circulo.posX <= 380){
                    actD=1;
                }
                if(circulo.posY >= 405-1 && circulo.posY <= 405){
                    actS=1;
                }
                if(circulo.posX <= 467+1 && circulo.posX >= 467){
                    actA=1;
                }
                if(circulo.posY <= 464+1 && circulo.posY >= 464){
                    actW=1;
                }
            }
            //-------------quadrado45 = {475,405,582,464}
            if(circulo.posX >=475 && circulo.posY >=405 && circulo.posX <=582 && circulo.posY <= 464){
                if(circulo.posX >= 475-1 && circulo.posX <= 475){
                    actD=1;
                }
                if(circulo.posY >= 405-1 && circulo.posY <= 405){
                    actS=1;
                }
                if(circulo.posX <= 582+1 && circulo.posX >= 582){
                    actA=1;
                }
                if(circulo.posY <= 464+1 && circulo.posY >= 464){
                    actW=1;
                }
            }
            //-------------quadrado46 = {372,405,475,454}
            if(circulo.posX >=372 && circulo.posY >=405 && circulo.posX <=475 && circulo.posY <= 454){
                if(circulo.posX >= 372-1 && circulo.posX <= 372){
                    actD=1;
                }
                if(circulo.posY >= 405-1 && circulo.posY <= 405){
                    actS=1;
                }
                if(circulo.posX <= 475+1 && circulo.posX >= 475){
                    actA=1;
                }
                if(circulo.posY <= 454+1 && circulo.posY >= 454){
                    actW=1;
                }
            }
            //-------------quadrado47 = {539,193,566,267}
            if(circulo.posX >=539 && circulo.posY >=193 && circulo.posX <=566 && circulo.posY <= 267){
                if(circulo.posX >= 539-1 && circulo.posX <= 539){
                    actD=1;
                }
                if(circulo.posY >= 193-1 && circulo.posY <= 193){
                    actS=1;
                }
                if(circulo.posX <= 566+1 && circulo.posX >= 566){
                    actA=1;
                }
                if(circulo.posY <= 267+1 && circulo.posY >= 267){
                    actW=1;
                }
            }
            //-------------quadrado48 = {426,323,442,349}
            if(circulo.posX >=426 && circulo.posY >=323 && circulo.posX <=442 && circulo.posY <= 349){
                if(circulo.posX >= 426-1 && circulo.posX <= 426){
                    actD=1;
                }
                if(circulo.posY >= 323-1 && circulo.posY <= 323){
                    actS=1;
                }
                if(circulo.posX <= 442+1 && circulo.posX >= 442){
                    actA=1;
                }
                if(circulo.posY <= 349+1 && circulo.posY >= 349){
                    actW=1;
                }
            }
            //-------------quadrado49 = {314,394,330,414}
            if(circulo.posX >=314 && circulo.posY >=394 && circulo.posX <=330 && circulo.posY <= 414){
                if(circulo.posX >= 314-1 && circulo.posX <= 314){
                    actD=1;
                }
                if(circulo.posY >= 394-1 && circulo.posY <= 394){
                    actS=1;
                }
                if(circulo.posX <= 330+1 && circulo.posX >= 330){
                    actA=1;
                }
                if(circulo.posY <= 414+1 && circulo.posY >= 414){
                    actW=1;
                }
            }
            //-------------quadrado50 = {166,394,186,465}
            if(circulo.posX >=166 && circulo.posY >=394 && circulo.posX <=186 && circulo.posY <= 465){
                if(circulo.posX >= 166-1 && circulo.posX <= 166){
                    actD=1;
                }
                if(circulo.posY >= 394-1 && circulo.posY <= 394){
                    actS=1;
                }
                if(circulo.posX <= 186+1 && circulo.posX >= 186){
                    actA=1;
                }
                if(circulo.posY <= 465+1 && circulo.posY >= 465){
                    actW=1;
                }
            }
            //-------------quadrado51 = {300,556,470,641}
            if(circulo.posX >=300 && circulo.posY >=556 && circulo.posX <=470 && circulo.posY <= 641){
                if(circulo.posX >= 300-1 && circulo.posX <= 300){
                    actD=1;
                }
                if(circulo.posY >= 556-1 && circulo.posY <= 556){
                    actS=1;
                }
                if(circulo.posX <= 470+1 && circulo.posX >= 470){
                    actA=1;
                }
                if(circulo.posY <= 641+1 && circulo.posY >= 641){
                    actW=1;
                }
            }
            //-------------quadrado52 = {428,393,502,420}
            if(circulo.posX >=428 && circulo.posY >=393 && circulo.posX <=502 && circulo.posY <= 420){
                if(circulo.posX >= 428-1 && circulo.posX <= 428){
                    actD=1;
                }
                if(circulo.posY >= 393-1 && circulo.posY <= 393){
                    actS=1;
                }
                if(circulo.posX <= 502+1 && circulo.posX >= 502){
                    actA=1;
                }
                if(circulo.posY <= 420+1 && circulo.posY >= 420){
                    actW=1;
                }
            }

            //----------------------------------------------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------------------------------------------------------

            //--------------Movimentação WASD------------
            if(key[ALLEGRO_KEY_W] && actW!=1){
                circulo.posY--;
                circulo.dir = 1;
            }
            if(key[ALLEGRO_KEY_A] && actA!=1){
                circulo.posX--;
                circulo.dir = 4;
            }
            if(key[ALLEGRO_KEY_S] && actS!=1){
                circulo.posY++;
                circulo.dir = 3;
            }
            if(key[ALLEGRO_KEY_D] && actD!=1){
                circulo.posX++;
                circulo.dir = 2;
            }
            actW=0;
            actA=0;
            actS=0;
            actD=0;
            //--------------Fim da Movimentação----------


        }







//-----------------------------------------------------------------------------------------------------------------------------







		// Encerra o loop quando o usuário clicar em fechar
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

		// Para cada "tick" do timer, a tela será desenhada novamente
		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_draw_bitmap(background, 0, 0, 0);


//-----------------------------------------------------------------------------------------------------------------------------
			/*al_draw_filled_rectangle(quadrado1.UPEposX, quadrado1.UPEposY, quadrado1.DOWDposX, quadrado1.DOWDposY, al_map_rgb(101,111,1));//barrado
			al_draw_filled_rectangle(quadrado2.UPEposX, quadrado2.UPEposY, quadrado2.DOWDposX, quadrado2.DOWDposY, al_map_rgb(102,112,2));//barrado
			al_draw_filled_rectangle(quadrado3.UPEposX, quadrado3.UPEposY, quadrado3.DOWDposX, quadrado3.DOWDposY, al_map_rgb(103,113,3));//barrado
			al_draw_filled_rectangle(quadrado4.UPEposX, quadrado4.UPEposY, quadrado4.DOWDposX, quadrado4.DOWDposY, al_map_rgb(104,114,4));//barrado
			al_draw_filled_rectangle(quadrado5.UPEposX, quadrado5.UPEposY, quadrado5.DOWDposX, quadrado5.DOWDposY, al_map_rgb(105,115,5));//barrado
			al_draw_filled_rectangle(quadrado6.UPEposX, quadrado6.UPEposY, quadrado6.DOWDposX, quadrado6.DOWDposY, al_map_rgb(106,116,6));//barrado
			al_draw_filled_rectangle(quadrado7.UPEposX, quadrado7.UPEposY, quadrado7.DOWDposX, quadrado7.DOWDposY, al_map_rgb(107,117,7));//barrado
			al_draw_filled_rectangle(quadrado8.UPEposX, quadrado8.UPEposY, quadrado8.DOWDposX, quadrado8.DOWDposY, al_map_rgb(108,118,8));//barrado
			al_draw_filled_rectangle(quadrado9.UPEposX, quadrado9.UPEposY, quadrado9.DOWDposX, quadrado9.DOWDposY, al_map_rgb(109,119,9));//barrado
			al_draw_filled_rectangle(quadrado10.UPEposX, quadrado10.UPEposY, quadrado10.DOWDposX, quadrado10.DOWDposY, al_map_rgb(110,110,10));//barrado
			al_draw_filled_rectangle(quadrado11.UPEposX, quadrado11.UPEposY, quadrado11.DOWDposX, quadrado11.DOWDposY, al_map_rgb(111,111,11));//barrado
			al_draw_filled_rectangle(quadrado12.UPEposX, quadrado12.UPEposY, quadrado12.DOWDposX, quadrado12.DOWDposY, al_map_rgb(112,112,12));//barrado
			al_draw_filled_rectangle(quadrado13.UPEposX, quadrado13.UPEposY, quadrado13.DOWDposX, quadrado13.DOWDposY, al_map_rgb(113,113,13));//barrado
			al_draw_filled_rectangle(quadrado14.UPEposX, quadrado14.UPEposY, quadrado14.DOWDposX, quadrado14.DOWDposY, al_map_rgb(114,114,14));//barrado
			al_draw_filled_rectangle(quadrado15.UPEposX, quadrado15.UPEposY, quadrado15.DOWDposX, quadrado15.DOWDposY, al_map_rgb(113,113,13));//barrado
			al_draw_filled_rectangle(quadrado16.UPEposX, quadrado16.UPEposY, quadrado16.DOWDposX, quadrado16.DOWDposY, al_map_rgb(114,114,14));//barrado
			al_draw_filled_rectangle(quadrado17.UPEposX, quadrado17.UPEposY, quadrado17.DOWDposX, quadrado17.DOWDposY, al_map_rgb(113,113,13));//barrado
			al_draw_filled_rectangle(quadrado18.UPEposX, quadrado18.UPEposY, quadrado18.DOWDposX, quadrado18.DOWDposY, al_map_rgb(114,114,14));//barrado
			al_draw_filled_rectangle(quadrado19.UPEposX, quadrado19.UPEposY, quadrado19.DOWDposX, quadrado19.DOWDposY, al_map_rgb(113,113,13));//barrado
			al_draw_filled_rectangle(quadrado20.UPEposX, quadrado20.UPEposY, quadrado20.DOWDposX, quadrado20.DOWDposY, al_map_rgb(113,113,13));//barrado

			al_draw_filled_rectangle(quadrado21.UPEposX, quadrado21.UPEposY, quadrado21.DOWDposX, quadrado21.DOWDposY, al_map_rgb(14,114,114));//barrado
			al_draw_filled_rectangle(quadrado22.UPEposX, quadrado22.UPEposY, quadrado22.DOWDposX, quadrado22.DOWDposY, al_map_rgb(13,113,113));//barrado
            al_draw_filled_rectangle(quadrado23.UPEposX, quadrado23.UPEposY, quadrado23.DOWDposX, quadrado23.DOWDposY, al_map_rgb(14,114,114));//barrado

			al_draw_filled_rectangle(quadrado24.UPEposX, quadrado24.UPEposY, quadrado24.DOWDposX, quadrado24.DOWDposY, al_map_rgb(13,113,213));//barrado
			al_draw_filled_rectangle(quadrado25.UPEposX, quadrado25.UPEposY, quadrado25.DOWDposX, quadrado25.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado26.UPEposX, quadrado26.UPEposY, quadrado26.DOWDposX, quadrado26.DOWDposY, al_map_rgb(13,113,213));//barrado
			al_draw_filled_rectangle(quadrado27.UPEposX, quadrado27.UPEposY, quadrado27.DOWDposX, quadrado27.DOWDposY, al_map_rgb(14,214,214));//barrado
			al_draw_filled_rectangle(quadrado28.UPEposX, quadrado28.UPEposY, quadrado28.DOWDposX, quadrado28.DOWDposY, al_map_rgb(13,113,213));//barrado
			al_draw_filled_rectangle(quadrado29.UPEposX, quadrado29.UPEposY, quadrado29.DOWDposX, quadrado29.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado30.UPEposX, quadrado30.UPEposY, quadrado30.DOWDposX, quadrado30.DOWDposY, al_map_rgb(13,213,213));//barrado
			al_draw_filled_rectangle(quadrado31.UPEposX, quadrado31.UPEposY, quadrado31.DOWDposX, quadrado31.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado32.UPEposX, quadrado32.UPEposY, quadrado32.DOWDposX, quadrado32.DOWDposY, al_map_rgb(13,113,213));//barrado
			al_draw_filled_rectangle(quadrado33.UPEposX, quadrado33.UPEposY, quadrado33.DOWDposX, quadrado33.DOWDposY, al_map_rgb(14,214,214));//barrado
			al_draw_filled_rectangle(quadrado34.UPEposX, quadrado34.UPEposY, quadrado34.DOWDposX, quadrado34.DOWDposY, al_map_rgb(13,113,213));//barrado
			al_draw_filled_rectangle(quadrado35.UPEposX, quadrado35.UPEposY, quadrado35.DOWDposX, quadrado35.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado36.UPEposX, quadrado36.UPEposY, quadrado36.DOWDposX, quadrado36.DOWDposY, al_map_rgb(13,213,213));//barrado
			al_draw_filled_rectangle(quadrado37.UPEposX, quadrado37.UPEposY, quadrado37.DOWDposX, quadrado37.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado38.UPEposX, quadrado38.UPEposY, quadrado38.DOWDposX, quadrado38.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado39.UPEposX, quadrado39.UPEposY, quadrado39.DOWDposX, quadrado39.DOWDposY, al_map_rgb(14,214,214));//barrado
			al_draw_filled_rectangle(quadrado40.UPEposX, quadrado40.UPEposY, quadrado40.DOWDposX, quadrado40.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado41.UPEposX, quadrado41.UPEposY, quadrado41.DOWDposX, quadrado41.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado42.UPEposX, quadrado42.UPEposY, quadrado42.DOWDposX, quadrado42.DOWDposY, al_map_rgb(14,214,214));//barrado
			al_draw_filled_rectangle(quadrado43.UPEposX, quadrado43.UPEposY, quadrado43.DOWDposX, quadrado43.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado44.UPEposX, quadrado44.UPEposY, quadrado44.DOWDposX, quadrado44.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado45.UPEposX, quadrado45.UPEposY, quadrado45.DOWDposX, quadrado45.DOWDposY, al_map_rgb(14,114,214));//barrado
			al_draw_filled_rectangle(quadrado46.UPEposX, quadrado46.UPEposY, quadrado46.DOWDposX, quadrado46.DOWDposY, al_map_rgb(14,214,214));//barrado

			al_draw_filled_rectangle(quadrado47.UPEposX, quadrado47.UPEposY, quadrado47.DOWDposX, quadrado47.DOWDposY, al_map_rgb(154,214,114));//barrado
			al_draw_filled_rectangle(quadrado48.UPEposX, quadrado48.UPEposY, quadrado48.DOWDposX, quadrado48.DOWDposY, al_map_rgb(154,214,114));//barrado
			al_draw_filled_rectangle(quadrado49.UPEposX, quadrado49.UPEposY, quadrado49.DOWDposX, quadrado49.DOWDposY, al_map_rgb(154,214,114));//barrado
            al_draw_filled_rectangle(quadrado50.UPEposX, quadrado50.UPEposY, quadrado50.DOWDposX, quadrado50.DOWDposY, al_map_rgb(154,214,114));//barrado
            al_draw_filled_rectangle(quadrado51.UPEposX, quadrado51.UPEposY, quadrado51.DOWDposX, quadrado51.DOWDposY, al_map_rgb(154,214,114));//barrado
            al_draw_filled_rectangle(quadrado52.UPEposX, quadrado52.UPEposY, quadrado52.DOWDposX, quadrado52.DOWDposY, al_map_rgb(154,214,114));//barrado
            */

			al_draw_filled_circle(circulo.posX, circulo.posY, circulo.raio, al_map_rgb(10,0,0));


            al_draw_textf(font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH/2, 20, 1, "X: %d  /  Y: %d", mouseClickPositionX, mouseClickPositionY);
            al_draw_textf(font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH/2, 40, 1, "X: %d  /  Y: %d", circulo.posX, circulo.posY);
//-----------------------------------------------------------------------------------------------------------------------------


			al_flip_display();
		}
	}

	// Encerra o jogo limpando as funções que consomem memória
	initializeDestruction(display, font, music, background, mixer);
}
