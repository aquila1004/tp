void InimigoColide(Inimigo inimigo[], Bloco bloco, Nave nave);
void colisaoNaveBloco(Nave nave, Bloco bloco);
void TiroColideInimigo(Tiro tiro, Inimigo inimigo[], int tamanho, Nave nave);

// COLISÃO DO INIMIGO COM NAVE
void InimigoColide(Inimigo inimigo[], Bloco bloco, Nave nave)
{
	for(int i = 0; i <NUM_INIMIGO; i++){
		if(inimigo[i].ativo){
			if(inimigo[i].x - inimigo[i].borda_x <= nave.x  &&
			inimigo[i].x + inimigo[i].borda_x  >= nave.x &&
			inimigo[i].y - inimigo[i].borda_y  <= nave.y &&
			inimigo[i].y + inimigo[i].borda_y >= nave.y  ){
				playing = 0;
			}
			if(inimigo[i].x - inimigo[i].borda_x <= nave.x - 100 &&
			inimigo[i].x + inimigo[i].borda_x >= nave.x - 100 &&
			inimigo[i].y - inimigo[i].borda_y <= nave.y - 25  &&
			inimigo[i].y + inimigo[i].borda_y >= nave.y - 25){
				playing = 0;
			}
			if(inimigo[i].x - inimigo[i].borda_x <= nave.x - 100&&
			inimigo[i].x + inimigo[i].borda_x >= nave.x - 100&&
			inimigo[i].y - inimigo[i].borda_y <= nave.y + 25 &&
			inimigo[i].y + inimigo[i].borda_y >= nave.y + 25){
				playing = 0;
			}
			 
		}
	}
	if( nave.x >= bloco.x && nave.x <= bloco.x + bloco.w +98 && nave.y  >=  bloco.y - 29&& nave.y  <= bloco.y + bloco.h + 29){
		playing = 0;
	}
}

// --------------COLISÃO DA NAVE COM BLOCO E INIMIGO-----------------
void colisaoNaveBloco(Nave nave, Bloco bloco)
{
	if(nave.x + (NAVE_W/50) > bloco.x && nave.x - NAVE_W < bloco.x + bloco.w && nave.y + (NAVE_H/2) > bloco.y && nave.y - (NAVE_H/2) < bloco.y + bloco.h){
		playing = 0;
	}
}

//COLISÃO Do tiro COM INIMIGO SEM VETORES

void TiroColideInimigo(Tiro tiro, Inimigo inimigo[], int tamanho, Nave nave)
{
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