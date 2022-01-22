typedef struct Nave {
	int x, y;
	int vel;
	int dir_x, dir_y;
	int pontos;
	ALLEGRO_COLOR cor;
}Nave;

void initNave(Nave *nave);
void desenhaNave(Nave nave);
void atualizaNave(Nave *nave);
void NaveTela (Nave *nave);

void initNave(Nave *nave)
{
	nave->x = 10 + NAVE_W;
	nave->y = SCREEN_H/2;
	nave->dir_x = 0;
	nave->dir_y = 0;
	nave->cor =  al_map_rgb(192 + rand()%64, 192 + rand()%64, 192 + rand()%64);
	nave->vel = VELOCIDADE_NAVE;
}

void desenhaNave(Nave nave)
{
	al_draw_filled_triangle(nave.x, nave.y, nave.x - NAVE_W, nave.y - NAVE_H/2,  nave.x - NAVE_W, nave.y + NAVE_H/2, nave.cor);
}

void atualizaNave(Nave *nave)
{
	nave->y += nave->dir_y * nave->vel;
	nave->x += nave->dir_x * nave->vel;
}
//limitar a tela para nave nao sumir
void NaveTela (Nave *nave)
{		
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