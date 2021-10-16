/************************************************/
/* Auteur : FRANCOIS Hugo                       */
/* Application : Simulation de rpg textuel		*/
/*                                              */
/* Date de la dernière m-à-j : 06/03/2020       */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>

#define SAVEDAT "Save\\"
#define MOBDAT "Data\\Mobs.dat"

#include "main.h"
#include "menu.c"
#include "game.c"

int main()
{
	short choix, i;
    DIR* d;
    struct dirent *dir;

//Initialise les paramètres enregistrés
    SetsIni();

//Animation d'introduction si le paramètre n'est pas mis à 0
    if(_intro != 0)
    {
        system("color 03");
        Intro();
    }

	do{
        system("cls");
        system("color 03");

        d = opendir("Save");
        if(d)
        {
//Détection du nombre de fichiers présents dans le dossier 'Save'
            for(i = 0; (dir = readdir(d)) != NULL; i++) {}  //Les 2 premiers fichiers sont inutiles ('.' && '..')

//S'il n'y a aucune sauvegarde, afficher le menu "simple"
            if(i == 2)  //(2 car '.' & '..')
            {
                MenuNew();

                do{
                    scanf("%hd", &choix);
                    printf("Nombre incorrect, veuillez recommencer\n");
                }while(choix < 0 || 2 < choix);

                switch(choix)
                {
                    case 1:
                        New();
                        break;
                    case 2:
                        Settings();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Mauvais choix, veuillez re-choisir\n");
                }
            }
            else
            {
//Si au moins 1 sauvegarde détectée, afficher le menu "complet"
                MenuContinue();

                do{
                    scanf("%hd", &choix);
                    printf("Nombre incorrect, veuillez recommencer\n");
                }while(choix < 0 || 4 < choix);

                switch(choix)
                {
                    case 1:
                        Recent();
                        break;
                    case 2:
                        New();
                        break;
                    case 3:
                        MenuSave();
                        break;
                    case 4:
                        Settings();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Nombre incorrect, veuillez recommencer\n");
                }
            }
        }
    }while(choix != 0);

	return 0;
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
/*  Initialisation des paramètres avec le fichier Settings.ini  */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
void SetsIni()
{
    short i, j = 0;
    char sets[45], tmp[25];
    FILE* fp;

    fp = fopen("Data\\Settings.ini", "rt");
    if(fp != NULL)
    {
        fseek(fp, 0, SEEK_SET);
        fread(sets, sizeof(sets), 1, fp);

//Premier paramètre (Durée de l'introduction)
        for(i = 1; sets[i] != '\0' && sets[i] != '#'; i++)
            for(; '0' <= sets[i] && sets[i] <= '9'; i++, j++)
                tmp[j] = sets[i];
        tmp[j] = '\0';
        _intro = CharToShort(tmp);

//Deuxième paramètre (Vitesse d'affichage des textes)
        j = 0;
        for(; sets[i] != '\0' && sets[i] != ';'; i++)
            for(; '0' <= sets[i] && sets[i] <= '9'; i++, j++)
                tmp[j] = sets[i];
        tmp[j] = '\0';
        _textSpeed = CharToShort(tmp);

        fclose(fp);
    }

}