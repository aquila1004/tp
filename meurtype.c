#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <time.h>

// inicio de variaveis globais

bool debug = true;
const float FPS = 100;  

const int SCREEN_W = 960;
const int SCREEN_H = 540;

const int NAVE_W = 100;
const int NAVE_H = 50;

const int VELOCIDADE_NAVE = 3;


ALLEGRO_COLOR COR_CENARIO;
 typedef struct Nave {
	
	int x, y;
	int vel;
	int dir_x, dir_y;
	ALLEGRO_COLOR cor;


}Nave;
typedef struct Bloco{
	int x, y;
	ALLEGRO_COLOR cor;
	int w, h;
	
}Bloco;
typedef struct Tiro{
	int x;
	int y;
	int speed;
	ALLEGRO_COLOR cor;
	bool vida;
}Tiro;


// chamar a função uma única vez
void intGlobais() {

	COR_CENARIO = al_map_rgb(rand()%64, rand()%64, rand()%64);

}

void intBloco(Bloco *bloco) {

	bloco->x = SCREEN_W + rand()%(SCREEN_W);
	bloco->y = rand()%(4*SCREEN_H/5);
	bloco->w = SCREEN_W + rand()%(SCREEN_W);
	bloco->h = SCREEN_H/5 + rand()%(2*SCREEN_H/5);
	bloco->cor = al_map_rgb(rand(), rand(), rand());
	//bloco->cor = al_map_rgb(255, 0, 0);
	printf("\n%d %d %d %d ", bloco->x, bloco->y, bloco->w, bloco->h);

}

void initNave(Nave *nave){

	nave->x = 10 + NAVE_W;
	nave->y = SCREEN_H/2;
	nave->dir_x = 0;
	nave->dir_y = 0;
	nave->cor =  al_map_rgb(192 + rand()%64, 192 + rand()%64, 192 + rand()%64);
	nave->vel = VELOCIDADE_NAVE;


}





void desenhaCenario(){

    // colocar uma variável global
	al_clear_to_color(COR_CENARIO);
 }
 void desenhaNave(Nave nave) {

	al_draw_filled_triangle(nave.x, nave.y, nave.x - NAVE_W, nave.y - NAVE_H/2,  nave.x - NAVE_W, nave.y + NAVE_H/2, nave.cor);

}
void desenhaBloco(Bloco bloco) {

	al_draw_filled_rectangle(bloco.x, bloco.y, bloco.x + bloco.w, bloco.y + bloco.h, bloco.cor);

}

void atualizaBloco(Bloco *bloco) {	

	bloco->x -= 1;
	if(bloco->x + bloco->w < 0)
	intBloco(bloco);
}

void atualizaNave(Nave *nave) {
	nave->y += nave->dir_y * nave->vel;
	nave->x += nave->dir_x * nave->vel;
}
//limitar a tela para nave nao sumir
void NaveTela (Nave *nave){		
	if (nave->x > SCREEN_W){
		nave->x = SCREEN_W ;
		}
	
	if (nave->x - NAVE_W < 0){
		nave->x = 0 + NAVE_W;
    }
	if (nave->y + (NAVE_H/2) > SCREEN_H){
		nave->y = SCREEN_H -(NAVE_H/2);
		}
	
	if (nave->y - (NAVE_H/2)< 0){
		nave->y = 0 + (NAVE_H)/2;
    }




}
void intTiro(Tiro *tiro){
	tiro->x = 0;
	tiro->y = 0;
	tiro->speed = 3;
}
void initTiro(Tiro tiro[]){
	for(int i = 0; i < 5; i++){
		tiro[i].speed = 4;
	}
}
void desenhaTiro(Tiro tiro[]){
	for( int i = 0; i < 5; i++){
		//if(tiro[i].vida ){
		
			al_draw_filled_circle(tiro[i].x, tiro[i].y, 5, al_map_rgb(255, 0, 0));
		
		//al_draw_filled_circle(tiro[i].x, tiro[i].y, 4, al_map_rgb(255, 255, 255));
	
}
}
void TiroNave(Tiro tiro[],Nave nave){
	for(int i = 0; i < 5; i++){
		
			tiro[i].x = nave.x;
			tiro[i].y = nave.y;
			
			break;
	}
}


void atualizaTiro(Tiro tiro[]){
	for(int i = 0; i < 5; i++)
	{
		
		tiro[i].x += tiro[i].speed;
		//tiro[i].x += tiro[i].speed;
	}	
}
// colisao entre tiro e bloco
int colisaoTiroBloco(Tiro tiro[], Bloco bloco){
	// == <
	for(int i = 0; i < 1; i++){
		if(tiro[i].x  > bloco.x && tiro[i].x-4 < bloco.x + bloco.w && tiro[i].y+4 > bloco.y && tiro[i].y-4 < bloco.y + bloco.h){	
			tiro[i].vida = false;
			printf("tiro %d", tiro[i].vida);
			return 1;
		}
	else	
	
	return 0;		
	}
}



// um tiro só pode ser atirado uma vez



int colisaoNaveBloco(Nave nave, Bloco bloco){
	// == <

	if(nave.x + (NAVE_W/50) > bloco.x && nave.x - NAVE_W < bloco.x + bloco.w && nave.y + (NAVE_H/2) > bloco.y && nave.y - (NAVE_H/2) < bloco.y + bloco.h){
		return 1;
	}
	else	
	
	return 0;
}
// colisao do tiro com o bloco e o tiro some e continua o jogo 

 
int main(int argc, char **argv){

	srand(time(NULL));
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}
   
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
    //inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("arial.ttf", 32, 1);   
	if(size_32 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   


	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	intGlobais();

	Nave nave;
	initNave(&nave);
	
	Tiro tiros[5];
	initTiro(tiros);

	Bloco bloco;
	intBloco(&bloco);

	
	;

   



	
	


	//inicia o temporizador
	al_start_timer(timer);
	
	int playing = 1;
	while(playing) {
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {

			desenhaCenario();

			atualizaBloco(&bloco);

			desenhaBloco(bloco);

			atualizaNave(&nave);

			desenhaNave(nave);

		    NaveTela(&nave);

		    //colisaoNaveBloco(nave, bloco);
			
			desenhaTiro(tiros);

			atualizaTiro(tiros);

			//colisaoTiroBloco(tiros, bloco);
			
			//atiraTiro(tiros, nave);
			
			colisaoTiroBloco(tiros, bloco);
			


			playing = !colisaoNaveBloco(nave, bloco);


			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}

		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_W:
					nave.dir_y--;
					break;

				case ALLEGRO_KEY_S:
					nave.dir_y++;
					break;

				case ALLEGRO_KEY_A:
					nave.dir_x--;
					break;

				case ALLEGRO_KEY_D:
					nave.dir_x++;

					break;
				case ALLEGRO_KEY_SPACE:
					TiroNave(tiros, nave);

					break;			
			}
		}
		
		
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){

			
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_W:
			nave.dir_y++;
			break;

		case ALLEGRO_KEY_S:

		    nave.dir_y--;
   			break;
		
		case ALLEGRO_KEY_A:
			nave.dir_x++;
			break;

		case ALLEGRO_KEY_D:
		    nave.dir_x--;
   			break;
		
		}
		
		
		}

	} //fim do while
     
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
   
 
	return 0;
}
