// inicio de variaveis globais

bool debug = true;
const float FPS = 100;  

const int SCREEN_W = 960;
const int SCREEN_H = 540;

ALLEGRO_BITMAP *nave_imagem;
const int NAVE_W = 100;
const int NAVE_H = 100;

const int VELOCIDADE_NAVE = 4;

#define NUM_INIMIGO 13
#define MAX_INIMIGO 8

ALLEGRO_COLOR COR_CENARIO;

int playing;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *size_32;
ALLEGRO_EVENT ev;