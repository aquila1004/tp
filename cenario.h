void intGlobais();
void desenhaCenario();

void intGlobais()
{
	COR_CENARIO = al_map_rgb(rand() % 64, rand() % 64, rand() % 64);
}

void desenhaCenario()
{
	al_clear_to_color(COR_CENARIO);
}