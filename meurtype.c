#include "includes.h"

int main(int argc, char **argv){
	
	iniciaJogo();

	while(playing) {

		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			desenhaCenario();
			atualizaBloco(&bloco);
			desenhaBloco(bloco);
			atualizaNave(&nave);
			desenhaNave(nave);
		    NaveTela(&nave);
			atualizaTiro(&tiro, &nave);
			desenhaTiro(tiro);
            pontos(size_32);
			atualizarInimigo(inimigo, NUM_INIMIGO);
			desenhaInimigo(inimigo, NUM_INIMIGO);	
			liberaInimigo(inimigo, NUM_INIMIGO);
			TiroColideInimigo(tiro, inimigo, NUM_INIMIGO, nave);
			saiTiro(&tiro, &nave, &bloco);

			// colisoes
			InimigoColide(inimigo, bloco, nave);
			colisaoNaveBloco(nave, bloco);		

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
		}
		//fim do if do game over
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
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
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

	}
     
	
	
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}