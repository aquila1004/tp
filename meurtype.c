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

const int VELOCIDADE_NAVE = 4;

const int NUM_INIMIGO = 13;
#define MAX_INIMIGO 8




ALLEGRO_COLOR COR_CENARIO;

 typedef struct Nave {
	
	int x, y;
	int vel;
	int dir_x, dir_y;
	int pontos;
	ALLEGRO_COLOR cor;


}Nave;
typedef struct Bloco{
	int x, y;
	ALLEGRO_COLOR cor;
	bool vidas;
	int w, h;
	
	
}Bloco;
typedef struct Tiro{
	int x, y;
	int vel;
	bool ativo;
	ALLEGRO_COLOR cor;
}Tiro;
typedef struct Inimigo{
	int ID;
	int x, y;
	int vel;
	ALLEGRO_COLOR cor;
	int borda_x, borda_y;
	bool ativo;
	int w,h;
	int size;
	bool status;
	

}Inimigo;

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
// criar init tiro
void initTiro(Tiro *tiro, Nave *nave){

	tiro->x = nave->x;
	tiro->y = nave->y;
	//tiro->ativo = false;
	tiro->cor = al_map_rgb(255, 0, 0);
	tiro->vel = 0;


}
// fazer os desnhos para o tiro
void desenhaTiro(Tiro tiro){

	al_draw_filled_circle(tiro.x, tiro.y, 5, al_map_rgb(255,0,0));// está diferente aqui

}
//atualizar tiro e seu movimento
void atualizaTiro(Tiro *tiro, Nave *nave){
	if(tiro->vel != 5){
		tiro->x = nave->x;
		tiro->y = nave->y;
		
	}

	
}
void saiTiro(Tiro *tiro, Nave *nave, Bloco *bloco){

	if(tiro->vel == 5){
		tiro->x += tiro->vel;
	}
	if(tiro->x > SCREEN_W){
		initTiro(tiro, nave);
	}
	if(tiro->x >= bloco->x && tiro->y >= bloco->y && tiro->x <= bloco->x + bloco->w && tiro->y <= bloco->y + bloco->h){
		initTiro(tiro, nave);
	}
	//tiro->ativo = true;
}
// tiro bate no bloco e some com o tiro





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
// --------------INIMIGO-----------------
// criar uma função rand
int random(int n){
	return rand()%n;
}
int randInt(int min, int max){
	return  min + random(max - min + 1);
}
// inimigo
void initInimigo(Inimigo inimigo[], int tamanho){
	for(int i = 0; i < tamanho; i++){
		//inimigo[i].ID = INIMIGOS;
		inimigo[i].vel = 5;
		//inimigo[i].borda_x = 18;
		//inimigo[i].borda_y = 18;
		inimigo[i].size = randInt(22, 40);
		inimigo[i].borda_x= inimigo[i].size-5;
		inimigo[i].borda_y= inimigo[i].size-5;
		inimigo[i].ativo = false;
		inimigo[i].cor = al_map_rgb(rand(), rand(), rand());
	}
	
}
void liberaInimigo(Inimigo inimigo[], int tamanho){
	for(int i = 0; i < tamanho; i++){
		if(!inimigo[i].ativo){
			if(rand() % 500 == 0){
				//garantir que oinimigo fica na tela
				//inimigo[i].x = SCREEN_W + rand()%(SCREEN_W);
				//inimigo[i].y = rand()%(4*SCREEN_H/5);
				inimigo[i].x = SCREEN_W;
				inimigo[i].y = 30 + rand() % (SCREEN_H - 60);
				inimigo[i].ativo = true;
				break;
			}
		}
	}
		
	
}
void atualizarInimigo(Inimigo inimigo[], int tamanho){
	for(int i = 0; i < tamanho; i++){
		if(inimigo[i].ativo){
			inimigo[i].x -= inimigo[i].vel;
			if(inimigo[i].x < 0){
				//inimigo[i].x = SCREEN_W + rand()%(SCREEN_W);
				//inimigo[i].y = rand()%(4*SCREEN_H/5);// mudei o 4 para 10
				//inimigo[i].vel = VELOCIDADE_NAVE;
				//inimigo[i].cor = al_map_rgb(rand(), rand(), rand());
				//inimigo[i].borda_x = rand()%(SCREEN_W);
				//inimigo[i].borda_y = rand()%(SCREEN_H);
				inimigo[i].ativo = false;
			}
		}
	}


	
}
void desenhaInimigo(Inimigo inimigo[], int tamanho){
	for(int i = 0; i < tamanho; i++){
		if(inimigo[i].ativo){
			al_draw_filled_circle(inimigo[i].x, inimigo[i].y, inimigo[i].size, inimigo[i].cor);// mudei o 10 para 20 para 40
		}
	}
}


// --------------COLISÃO DA NAVE COM BLOCO E INIMIGO-----------------

int colisaoNaveBloco(Nave nave, Bloco bloco){
	// == <

	if(nave.x + (NAVE_W/50) > bloco.x && nave.x - NAVE_W < bloco.x + bloco.w && nave.y + (NAVE_H/2) > bloco.y && nave.y - (NAVE_H/2) < bloco.y + bloco.h){
		return 1;
	}
	else	
	
	return 0;
}
//COLISÃO Do tiro COM INIMIGO SEM VETORES

void TiroColideInimigo(Tiro tiro, Inimigo inimigo[], int tamanho, Nave nave){
	// tiro clide com inimigo quando a cordenada do tiro for diferente da cordenada da nave
	for(int i = 0; i < tamanho; i++){
		if(inimigo[i].ativo){
			if(tiro.x  > inimigo[i].x - inimigo[i].borda_x && tiro.x < inimigo[i].x + inimigo[i].borda_x && tiro.y  > inimigo[i].y - inimigo[i].borda_y&& tiro.y < inimigo[i].y + inimigo[i].borda_y){
				inimigo[i].ativo = false;
				tiro.ativo = true;
				nave.pontos++;
			}
		}
	}

}
	


			
		
	
	

// COLISÃO DO INIMIGO COM NAVE
int InimigoColide(Inimigo inimigo[], Bloco bloco, Nave nave){
	for(int i = 0; i <NUM_INIMIGO; i++){
		if(inimigo[i].ativo){
			if(inimigo[i].x - inimigo[i].borda_x <= nave.x  &&
			inimigo[i].x + inimigo[i].borda_x  >= nave.x &&
			inimigo[i].y - inimigo[i].borda_y  <= nave.y &&
			inimigo[i].y + inimigo[i].borda_y >= nave.y  ){
				return 1;
			}
			if(inimigo[i].x - inimigo[i].borda_x <= nave.x - 100 &&
			inimigo[i].x + inimigo[i].borda_x >= nave.x - 100 &&
			inimigo[i].y - inimigo[i].borda_y <= nave.y - 25  &&
			inimigo[i].y + inimigo[i].borda_y >= nave.y - 25){
				return 1;
			}
			if(inimigo[i].x - inimigo[i].borda_x <= nave.x - 100&&
			inimigo[i].x + inimigo[i].borda_x >= nave.x - 100&&
			inimigo[i].y - inimigo[i].borda_y <= nave.y + 25 &&
			inimigo[i].y + inimigo[i].borda_y >= nave.y + 25){
				return 1;
			}
			 
		}
	}
	if( nave.x >= bloco.x && nave.x <= bloco.x + bloco.w +98 && nave.y  >=  bloco.y - 29&& nave.y  <= bloco.y + bloco.h + 29){
		return 1;
	}
	else
	return 0;
}
/*void Pontuacao(Nave nave){
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "Pontos: %d", nave.pontos);
}
*/
int pontuacao(Inimigo inimigo[]){
	int pontos =0;
	for(int i=0; i < NUM_INIMIGO; i++){
		if(inimigo[i].ativo){
			pontos += (inimigo[i].size*2);
			//pontos += 10;


			return pontos;
		}
	}
}
void pontos(ALLEGRO_FONT *size_32){
	int pontos = 0;
	Tiro tiro;
	Inimigo inimigo[NUM_INIMIGO];
	pontos = pontuacao(inimigo);
	al_draw_textf(size_32, al_map_rgb(255, 255, 255), 0, 0, 0, "Pontos: %d", pontos);
}



 
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
	al_init_ttf_addon();

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
	//
	


	intGlobais();

	Nave nave;
	initNave(&nave);
	

	Bloco bloco;
	intBloco(&bloco);

	Tiro tiro;
	initTiro(&tiro, &nave);

	Inimigo inimigo[NUM_INIMIGO];
	initInimigo(inimigo, NUM_INIMIGO);
	
	//

	




	

	
	

   
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
			//Pontos(size_32);

			atualizaBloco(&bloco);

			desenhaBloco(bloco);

			atualizaNave(&nave);

			desenhaNave(nave);

		    NaveTela(&nave);

		    //colisaoNaveBloco(nave, bloco);
			
			//desenhaTiro(tiros);

			atualizaTiro(&tiro, &nave);

			desenhaTiro(tiro);
            pontos(size_32);
			//Pontuacao(nave);

			//atualizaInimigo(inimigo);

			//desenhaInimigo(inimigo);
			atualizarInimigo(inimigo, NUM_INIMIGO);
			
			desenhaInimigo(inimigo, NUM_INIMIGO);
			
			liberaInimigo(inimigo, NUM_INIMIGO);
			
			TiroColideInimigo(tiro, inimigo, NUM_INIMIGO, nave);
			
						 
			//atiraTiro(tiros, nave);
			
			
			
			//colisaoTiroBloco(tiros, bloco);
			saiTiro(&tiro, &nave, &bloco);
			
			//playing = !InimigoColide(inimigo, 10, nave);
			if(InimigoColide(inimigo, bloco , nave)==1){
				printf("osteorpoer");
				playing = 0;
			}
			
		    //playing = !InimigoColide(inimigo, NUM_INIMIGO, nave);


			if(colisaoNaveBloco(nave, bloco)==1){
				printf("osteorpoer");
				playing = 0;
			}			
			//playing = !colisaoNaveBloco(nave, bloco);
			//printf("dasdasd %d ",  InimigoColide(inimigo, 10, nave));
			

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
		
		}//fim do if do game over
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
				tiro.vel=5;
					

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
