typedef struct Bloco
{
	int x, y;
	ALLEGRO_COLOR cor;
	bool vidas;
	int w, h;
} Bloco;

void intBloco(Bloco *bloco);
void desenhaBloco(Bloco bloco);
void atualizaBloco(Bloco *bloco);

void intBloco(Bloco *bloco)
{
	bloco->x = SCREEN_W + rand() % (SCREEN_W);
	bloco->y = rand() % (4 * SCREEN_H / 5);
	bloco->w = SCREEN_W + rand() % (SCREEN_W);
	bloco->h = SCREEN_H / 5 + rand() % (2 * SCREEN_H / 5);
	bloco->cor = al_map_rgb(rand(), rand(), rand());
}

void desenhaBloco(Bloco bloco)
{
	al_draw_filled_rectangle(bloco.x, bloco.y, bloco.x + bloco.w, bloco.y + bloco.h, bloco.cor);
}

void atualizaBloco(Bloco *bloco)
{
	bloco->x -= 1;
	if (bloco->x + bloco->w < 0)
		intBloco(bloco);
}