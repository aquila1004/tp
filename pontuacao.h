void adicionapontos();
void recorde();
void adicionapontos()
{
	pontos += 10;
}

void pontuacao(ALLEGRO_FONT *size_32)
{

	al_draw_textf(size_32, al_map_rgb(255, 255, 255), 0, 0, 0, "Pontos: %d", pontos);
}

void recorde()
{
	if (colisao_nave == true)
	{
		playing = 0;
		int nu_pontos = (pontuacao == 0);
		int nu_recorde = leInteiroArquivo("record.txt");

		if (pontos > nu_recorde)
		{
			escreveInteiroArquivo("record.txt", pontos);
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(size_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 2.5 * SCREEN_H / 8, ALLEGRO_ALIGN_CENTRE, "Pontos: %d", pontos);
		if (pontos <= nu_recorde)
		{
			al_draw_textf(size_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 3.5 * SCREEN_H / 8, ALLEGRO_ALIGN_CENTRE, "Recorde: %d", nu_recorde);
		}
		else
		{
			al_draw_textf(size_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 3.5 * SCREEN_H / 8, ALLEGRO_ALIGN_CENTRE, "Novo Recorde: %d", pontos);
		}

		al_flip_display();
		al_rest(3);
		playing = 0;
	}
}
