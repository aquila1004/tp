int pontuacao(Inimigo inimigo[]);
void pontos(ALLEGRO_FONT *size_32);

int pontuacao(Inimigo inimigo[])
{
	int pontos =0;
	for(int i=0; i < NUM_INIMIGO; i++){
		if(inimigo[i].ativo){
			pontos += (inimigo[i].size*2);
			//pontos += 10;


			return pontos;
		}
	}
}

void pontos(ALLEGRO_FONT *size_32)
{
	int pontos = 0;
	Tiro tiro;
	pontos = pontuacao(inimigo);
	al_draw_textf(size_32, al_map_rgb(255, 255, 255), 0, 0, 0, "Pontos: %d", pontos);
}
