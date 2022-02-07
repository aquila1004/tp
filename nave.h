typedef struct Nave
{
	int x, y;
	int vel;
	int dir_x, dir_y;
	int pontos;
	ALLEGRO_COLOR cor;

} Nave;

void initNave(Nave *nave);
void desenhaNave(Nave nave);
void atualizaNave(Nave *nave);
void NaveTela(Nave *nave);

void initNave(Nave *nave)
{
	nave->x = 10 + NAVE_W;
	nave->y = SCREEN_H / 2;
	nave->dir_x = 0;
	nave->dir_y = 0;
	nave->cor = al_map_rgb(192 + rand() % 64, 192 + rand() % 64, 192 + rand() % 64);
	nave->vel = VELOCIDADE_NAVE;
}

void desenhaNave(Nave nave)
{
	al_draw_bitmap(nave_imagem, nave.x, nave.y, 0);
}

void atualizaNave(Nave *nave)
{
	nave->y += nave->dir_y * nave->vel;
	nave->x += nave->dir_x * nave->vel;
}
// limitar a tela para nave nao sumir
void NaveTela(Nave *nave)
{
	// verifica se a nave não ultrapassou o limite da tela pela direita
	if (nave->x > SCREEN_W - NAVE_W)
	{
		nave->x = SCREEN_W - NAVE_W;
	}

	// verifica se a nave não ultrapassou o limite da tela pela esquerda
	if (nave->x < 0)
	{
		nave->x = 0;
	}

	// verifica se a nave não ultrapassou o limite da tela por baixo
	if (nave->y > SCREEN_H - NAVE_H)
	{
		nave->y = SCREEN_H - NAVE_H;
	}

	// verifica se a nave não ultrapassou o limite da tela por cima
	if (nave->y < 0)
	{
		nave->y = 0;
	}
}