typedef struct Tiro{
	int x, y;
	int vel;
	bool ativo;
	ALLEGRO_COLOR cor;
}Tiro;

void initTiro(Tiro *tiro, Nave *nave);
void desenhaTiro(Tiro tiro);
void atualizaTiro(Tiro *tiro, Nave *nave);
void saiTiro(Tiro *tiro, Nave *nave, Bloco *bloco);

// criar init tiro
void initTiro(Tiro *tiro, Nave *nave)
{
	tiro->x = nave->x;
	tiro->y = nave->y;
	//tiro->ativo = false;
	tiro->cor = al_map_rgb(255, 0, 0);
	tiro->vel = 0;
}

// fazer os desnhos para o tiro
void desenhaTiro(Tiro tiro)
{
	al_draw_filled_circle(tiro.x, tiro.y, 5, al_map_rgb(255,0,0));// está diferente aqui
}

//atualizar tiro e seu movimento
void atualizaTiro(Tiro *tiro, Nave *nave)
{
	if(tiro->vel != 5)
    {
		tiro->x = nave->x;
		tiro->y = nave->y;	
	}
}

void saiTiro(Tiro *tiro, Nave *nave, Bloco *bloco)
{
	if(tiro->vel == 5){
		tiro->x += tiro->vel;
	}
	if(tiro->x > SCREEN_W){
		initTiro(tiro, nave);
	}
	if(tiro->x >= bloco->x && tiro->y >= bloco->y && tiro->x <= bloco->x + bloco->w && tiro->y <= bloco->y + bloco->h){
		initTiro(tiro, nave);
	}
}