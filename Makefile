ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=C:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
INCLUDE_ALLEGRO=\include

meurtype.exe: meurtype.o
	gcc -o meurtype.exe meurtype.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

meurtype.o: meurtype.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c meurtype.c

clean:
	del meurtype.o
	del meurtype.exe