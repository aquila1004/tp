void colisoesNave(Inimigo inimigo[], Bloco bloco, Nave nave);
void TiroColideInimigo(Tiro tiro, Inimigo inimigo[], int tamanho, Nave nave);
void colideInimigoBloco(Inimigo inimigo[], Bloco bloco);
void colideInimigo(Inimigo inimigo[], int tamanho);

// COLISÃO DO INIMIGO COM NAVE
void colisoesNave(Inimigo inimigo[], Bloco bloco, Nave nave)
{
	for(int i = 0; i <NUM_INIMIGO; i++)
	{
		if(inimigo[i].ativo)
		{
			if(inimigo[i].x + inimigo[i].size >= nave.x && inimigo[i].x <= nave.x + NAVE_W)
			{
				if(inimigo[i].y + inimigo[i].size >= nave.y && inimigo[i].y <= nave.y + NAVE_H)
				{
					//se a nave colidiu com um inimigo, atualiza o valor do jogo
					//playing = 0;
					colisao_nave = true;
				}
			}			 
		}
	}

	//verifica se a nave colidiu com algum bloco
	if(nave.x < bloco.x + bloco.w && nave.x + NAVE_W > bloco.x && nave.y < bloco.y + bloco.h && nave.y + NAVE_H > bloco.y)
	{
		//se a nave colidiu com um bloco, atualiza o valor do jogo
		//playing = 0;
		colisao_nave = true;
	}
}

//COLISÃO Do tiro COM INIMIGO SEM VETORES

void TiroColideInimigo(Tiro tiro, Inimigo inimigo[], int tamanho, Nave nave)
{
	// tiro clide com inimigo quando a cordenada do tiro for diferente da cordenada da nave
	for(int i = 0; i < tamanho; i++)
	{
		if(inimigo[i].ativo && tiro.ativo)
		{
			if(tiro.x  > inimigo[i].x - inimigo[i].borda_x && tiro.x < inimigo[i].x + inimigo[i].borda_x && tiro.y  > inimigo[i].y - inimigo[i].borda_y&& tiro.y < inimigo[i].y + inimigo[i].borda_y)
			{
				inimigo[i].ativo = false;
				tiro.ativo = false;// era true
				adicionapontos(); // antes era nave.pontos++;
			}
		}
	}
}
void colideInimigoBloco(Inimigo inimigo[], Bloco bloco){
	// verifica se algum inimigo colidiu com um bloco
	for(int i = 0; i < NUM_INIMIGO; i++)
	{
		if(inimigo[i].ativo)
		{
			if (inimigo[i].x + inimigo[i].size > bloco.x - bloco.w &&
				inimigo[i].x - inimigo[i].size < bloco.x + bloco.w &&
				inimigo[i].y + inimigo[i].size > bloco.y - bloco.h &&
				inimigo[i].y - inimigo[i].size < bloco.y + bloco.h)
			{
				inimigo[i].ativo = false;
			}		 
		}
	}
}
void colideInimigo(Inimigo inimigo[], int tamanho){
	// verifica se um inimigo colidiu com outro inimigo considerando apenas os inimigos ativos
	for (int i = 0; i < tamanho; i++)
	{
		if (inimigo[i].ativo)
		{
			for (int j = 0; j < tamanho; j++)
			{
				if (inimigo[j].ativo)
				{
					if (i != j)
					{
						if (inimigo[i].x + inimigo[i].size > inimigo[j].x - inimigo[j].size &&
							inimigo[i].x - inimigo[i].size < inimigo[j].x + inimigo[j].size &&
							inimigo[i].y + inimigo[i].size > inimigo[j].y - inimigo[j].size &&
							inimigo[i].y - inimigo[i].size < inimigo[j].y + inimigo[j].size)
						{
							inimigo[i].ativo = false;
							inimigo[j].ativo = false;
						}
					}
				}
			}
		}
	}
}