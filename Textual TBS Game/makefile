.SILENT:

OBJ	= main.o tools.o menu.o game.o

BASE	= D:\Code\RPG - Texte\

GPP		= g++ -m64 -Wall -I $(BASE) #-D DEV

main : main.c $(OBJ)
	echo Création de main
	$(GPP) -o main main.c $(OBJ)
	
main.o : $(BASE)/main.c $(BASE)/main.h
	echo Création de main.o
	$(GPP) -c $(BASE)/main.c

tools.o : $(BASE)/tools.c $(BASE)/tools.h
	echo Création de tools.o
	$(GPP) -c $(BASE)/tools.c

menu.o : $(BASE)/menu.c $(BASE)/menu.h
	echo Création de menu.o
	$(GPP) -c $(BASE)/menu.c

game.o : $(BASE)/game.c $(BASE)/game.h
	echo Création de game.o
	$(GPP) -c $(BASE)/game.c