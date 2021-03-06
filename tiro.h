typedef struct Tiro{
	int x, y;
	int vel;
	float raio;
	float aumentaraio;
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
	tiro->x = nave->x + NAVE_W;
	tiro->y = nave->y + NAVE_H/2;
    tiro->raio = 4.0;// aqui eu coloquei o raio do tiro
	tiro->cor = al_map_rgb(255, 0, 0);
	tiro->vel = 0;
	tiro->ativo = false;
	tiro->aumentaraio = 0;
}

// fazer os desnhos para o tiro
void desenhaTiro(Tiro tiro)
{
	al_draw_filled_circle(tiro.x, tiro.y, tiro.raio, al_map_rgb(255,0,0));// está diferente aqui
}

//atualizar tiro e seu movimento
void atualizaTiro(Tiro *tiro, Nave *nave)
{
	if(tiro->vel != 5)
    {
		tiro->x = nave->x + NAVE_W;
		tiro->y = nave->y + NAVE_H/2;
		if(tiro->aumentaraio == 0.5 && tiro->raio < 25.0)
		{
			tiro->raio += tiro->aumentaraio;
		}	
	}
}

void saiTiro(Tiro *tiro, Nave *nave, Bloco *bloco)
{

	// se a velocidade do tiro for 5
	if(tiro->vel == 5)
	{
		tiro->ativo = true;
		tiro->x += tiro->vel;
	}

	// se o tiro não estiver na tela
	if(tiro->x > SCREEN_W)
	{
		initTiro(tiro, nave);
	}

	// se o colidiu com um bloco
	if(tiro->x >= bloco->x && tiro->y >= bloco->y && tiro->x <= bloco->x + bloco->w && tiro->y <= bloco->y + bloco->h)
	{
		initTiro(tiro, nave);
	}
}