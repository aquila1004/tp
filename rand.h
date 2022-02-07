int random(int n);
int randInt(int min, int max);

int random(int n)
{
	return rand() % n;
}

int randInt(int min, int max)
{
	return min + random(max - min + 1);
}