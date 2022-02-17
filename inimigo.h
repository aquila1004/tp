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

Inimigo inimigo[NUM_INIMIGO];

void initInimigo(Inimigo inimigo[], int tamanho);
void liberaInimigo(Inimigo inimigo[], int tamanho);
void atualizarInimigo(Inimigo inimigo[], int tamanho);
void desenhaInimigo(Inimigo inimigo[], int tamanho);

void initInimigo(Inimigo inimigo[], int tamanho)
{
	for(int i = 0; i < tamanho; i++)
    {
		inimigo[i].vel = 6;
		inimigo[i].size = randInt(22, 40);
		inimigo[i].borda_x= inimigo[i].size-5;
		inimigo[i].borda_y= inimigo[i].size-5;
		inimigo[i].ativo = false;
		inimigo[i].cor = al_map_rgb(rand(), rand(), rand());
	}
	
}

void liberaInimigo(Inimigo inimigo[], int tamanho)
{
	for(int i = 0; i < tamanho; i++)
    {
		if(!inimigo[i].ativo)
        {
			if(rand() % 500 == 0)
            {
				inimigo[i].x = SCREEN_W;
				inimigo[i].y = 30 + rand() % (SCREEN_H - 60);
				inimigo[i].ativo = true;
				break;
			}
		}
	}
		
	
}

void atualizarInimigo(Inimigo inimigo[], int tamanho)
{
	for(int i = 0; i < tamanho; i++)
    {
		if(inimigo[i].ativo)
        {
			inimigo[i].x -= inimigo[i].vel;
			if(inimigo[i].x < 0)
            {
				inimigo[i].ativo = false;
			}
		}
	}
}

void desenhaInimigo(Inimigo inimigo[], int tamanho)
{
	for(int i = 0; i < tamanho; i++)
    {
		if(inimigo[i].ativo)
        {
			al_draw_filled_circle(inimigo[i].x, inimigo[i].y, inimigo[i].size, inimigo[i].cor);// mudei o 10 para 20 para 40
		}
	}
}