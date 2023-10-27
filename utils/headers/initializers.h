bool initializeGame(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer);

bool initializeMusic(ALLEGRO_VOICE* voice, ALLEGRO_MIXER* mixer, ALLEGRO_AUDIO_STREAM* music);

void initializeDestruction(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, ALLEGRO_AUDIO_STREAM* music, ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* menuBackground, ALLEGRO_BITMAP* menuSelectGenderBoy, ALLEGRO_BITMAP* menuSelectGenderGirl, ALLEGRO_BITMAP* pauseBackground, ALLEGRO_BITMAP* character, ALLEGRO_MIXER* mixer, Challenge* challengeList);
