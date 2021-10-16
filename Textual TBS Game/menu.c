#include "menu.h"

#define LIG 13
#define COL 100

/*  *   *   *   *   *   *   *   *   *   *   */
/*  Au lancement du jeu, Animation du menu  */
/*  *   *   *   *   *   *   *   *   *   *   */
void Intro()
{
	short i, j;
	char tab[LIG][COL] = {
				"",
				"",
				"",
				"",
                "                                 ___________      ___    ___     ________     ___",
                "                                |    ____   \\    |   |  |   |   |        |   |   |",
                "                                |   |    |   |   |   |  |   |   |    ____|   |   |",
                "                                |   |____|   |   |   |__|   |   |   |_       |   |",
                "                                |    _______/    |          |   |     |      |   |",
                "                                |   |            |    __    |   |    _|      |   |",
                "                                |   |            |   |  |   |   |   |____    |   |____",
                "                                |   |            |   |  |   |   |        |   |        |",
                "                                |___|            |___|  |___|   |________|   |________|"
				};

	for(i = 0; i < LIG; i++)
	{
		system("cls");

		for(j = i; j > 0; j--)
		{
			printf("%s\n", &tab[LIG-j][0]);
		}
		Sleep(_intro);
	}
}

/*  *   *   *   *   *   *   *   *   *   *   */
/*          Base du menu                    */
/*  *   *   *   *   *   *   *   *   *   *   */
void Menu()
{
    system("cls");

    printf("\n");
    printf("   / * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * \\\n");
    printf("   |                                                                                                               |\n");
    printf("                                 ___________      ___    ___     ________     ___                                   \n");
    printf("   |                            |    ____   \\    |   |  |   |   |        |   |   |                                 |\n");
    printf("                                |   |    |   |   |   |  |   |   |    ____|   |   |                                  \n");
    printf("   |                            |   |____|   |   |   |__|   |   |   |_       |   |                                 |\n");
    printf("                                |    _______/    |          |   |     |      |   |                                  \n");
    printf("   |                            |   |            |    __    |   |    _|      |   |                                 |\n");
    printf("                                |   |            |   |  |   |   |   |____    |   |____                              \n");
    printf("   |                            |   |            |   |  |   |   |        |   |        |                            |\n");
    printf("                                |___|            |___|  |___|   |________|   |________|                             \n");
    printf("   |                                                                                                               |\n");
    printf("                                                                                                                    \n");
    printf("   |                                                                                                               |\n");
    printf("\n");
    printf("   |                                                                                                               |\n");
}

/*  *   *   *   *   *   *   *   *   *   *   */
/*  Menu si aucun fichier de sauvegarde     */
/*  *   *   *   *   *   *   *   *   *   *   */
void MenuNew()
{
    Menu();

    printf("\n");
    printf("   |                                                                                                               |\n");
    printf("                                                  1. Nouvelle partie\n");
    printf("   |                                                                                                               |\n");
    printf("                                                      2. Options\n");
    printf("   |                                                                                                               |\n");
    printf("                                                      0. Quitter\n");
    printf("   |                                                                                                               |\n");
    printf("\n");
    printf("   |                                                                                                               |\n");
    printf("   \\ * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * /\n");
}

/*  *   *   *   *   *   *   *   *   *   *   */
/*      Menu si sauvegarde détectée         */
/*  *   *   *   *   *   *   *   *   *   *   */
void MenuContinue()
{
    Menu();

    printf("                                                     1. Continuer\n");
    printf("   |                                                                                                               |\n");
    printf("                                                  2. Nouvelle partie\n");
    printf("   |                                                                                                               |\n");
    printf("                                                      3. Charger\n");
    printf("   |                                                                                                               |\n");
    printf("                                                      4. Options\n");
    printf("   |                                                                                                               |\n");
    printf("                                                      0. Quitter\n");
    printf("   |                                                                                                               |\n");
    printf("   \\ * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * /\n");
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
/*  Détection de la sauvegarde la plus récente et lancer le jeu avec        */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
void Recent()
{
	short i, j;
	char saveName[31];
    SAVE save, save2;
    FILE *fp;

    DIR* d;
    struct dirent *dir;

    system("cls");

    d = opendir("Save");
    if(d)
    {
        for(i = 0, j = 2; (dir = readdir(d)) != NULL; i++)
        {
//Récupérer les valeurs de la première sauvegarde
            if(i == 2)
            {
                sprintf(saveName, "%s%s", SAVEDAT, dir->d_name);

                fp = fopen(saveName, "rb");
                if(fp != NULL) //Si existe
                {
                    fread(&save, sizeof(SAVE), 1, fp);

                    fclose(fp);
                }
            }

//Prendre les sauvegardes 1 par 1
            sprintf(saveName, "%s%s", SAVEDAT, dir->d_name);

            fp = fopen(saveName, "rb");
            if(fp != NULL) //Si existe
            {
                fread(&save2, sizeof(SAVE), 1, fp);

                fclose(fp);
            }

//Comparer 2 sauvegardes pour voir laquelle a été utilisée en dernier
            if(DateCmp(save.time.lastD, save2.time.lastD) < 0)
            {
                save = save2;
                j = i + 1;
            }
            if(DateCmp(save.time.lastD, save2.time.lastD) == 0)
                if(HourCmp(save.time.lastT, save2.time.lastT) <= 0)
                {
                    save = save2;
                    j = i + 1;
                }
        }
        closedir(d);
    }
	Load(j);
}

/*  *   *   *   *   *   *   *   *   *   *   */
/*      Création d'un personnage            */
/*  *   *   *   *   *   *   *   *   *   *   */
void New()
{
    char name[15];
    short classe, choix = 0, i, sec;
    SAVE save;

//Statistiques de chaque classe
    short vie[4] = {20, 10, 7, 15};
    short mana[4] = {0, 10, 13, 5};
    short str[4] = {8, 3, 3, 5};
    short agi[4] = {5, 3, 5, 8};
    short fai[4] = {3, 8, 3, 3};
    short kno[4] = {3 ,5 ,8, 3};
    short luc[4] = {8, 3, 5, 8};

//Savoir la date et l'heure du jour
    time_t secondes;
    struct tm date;
    time(&secondes);
    date=*localtime(&secondes);

//Affichage du menu
    system("cls");

    printf("\t\t\t\t/ * - * - * - * - * - * - * - * - * - * - * - * \\\n");
    printf("\t\t\t\t|   \t    \t    \t    \t  \t  \t|\n");
    printf("\t\t\t\t|\tCreation d'un nouveau personnage\t|\n");
    printf("\t\t\t\t|   \t    \t    \t    \t  \t  \t|\n");
    printf("\t\t\t\t\\ * - * - * - * - * - * - * - * - * - * - * - * /\n");

    SlowPrint("\n\t\t\t\t\tPseudo [15 char max] :   ", _textSpeed);
    do{
        ReadString(name, 15);
    }while(name[0] == '\0');

    printf("\n\t\t\t\t\t\t     Classe :\n");

    printf("\t\t\t     1. Barbare  \t2. Clerc\t3. Sorcier\t4. Voleur\n");
    printf("\t\t     Vie\t[ %hd ]   \t [ %hd ]  \t  [ %hd ] \t  [ %hd ]\n\n", vie[0], vie[1], vie[2], vie[3]);
    printf("\t\t     Mana\t[ %hd ]   \t [ %hd ]  \t  [ %hd ] \t  [ %hd ]\n\n", mana[0], mana[1], mana[2], mana[3]);
    printf("\t\t     Force\t[ %hd ]   \t [ %hd ]  \t  [ %hd ] \t  [ %hd ]\n\n", str[0], str[1], str[2], str[3]);
    printf("\t\t     Agilite\t[ %hd ]   \t [ %hd ]  \t  [ %hd ] \t  [ %hd ]\n\n", agi[0], agi[1], agi[2], agi[3]);
    printf("\t\t     Foi\t[ %hd ]   \t [ %hd ]  \t  [ %hd ] \t  [ %hd ]\n\n", fai[0], fai[1], fai[2], fai[3]);
    printf("\t\t     Savoir\t[ %hd ]   \t [ %hd ]  \t  [ %hd ] \t  [ %hd ]\n\n", kno[0], kno[1], kno[2], kno[3]);
    printf("\t\t     Chance\t[ %hd ]   \t [ %hd ]  \t  [ %hd ] \t  [ %hd ]\n\n", luc[0], luc[1], luc[2], luc[3]);

    printf("\t\t\t\t\tChoisissez une classe [1 - 4]");
    do{
        printf("\n\t\t\t\t\t\t\t");
        fflush(stdin);
        scanf("%hd", &classe);
    
	    switch(classe)
	    {
		case 1:
			printf("\n\t\t\t\t");
	    	SlowPrint("Vous allez commencer votre aventure en tant que\n", _textSpeed);

			printf("\n\t\t\t\t\t\t");
	        SlowPrint(name, _textSpeed);
	        SlowPrint(" le Barbare\n", _textSpeed);
	    	break;
		case 2:
			printf("\n\t\t\t\t");
	    	SlowPrint("Vous allez commencer votre aventure en tant que\n", _textSpeed);

			printf("\n\t\t");
	        SlowPrint(name, _textSpeed);
	        SlowPrint(" le Clerc\n", _textSpeed);
	    	break;
		case 3:
			printf("\n\t\t\t\t");
	    	SlowPrint("Vous allez commencer votre aventure en tant que\n", _textSpeed);

			printf("\n\t\t");
	        SlowPrint(name, _textSpeed);
	        SlowPrint(" le Sorcier\n", _textSpeed);
	    	break;
		case 4:
			printf("\n\t\t\t\t");
	    	SlowPrint("Vous allez commencer votre aventure en tant que\n", _textSpeed);

			printf("\n\t\t");
	        SlowPrint(name, _textSpeed);
	        SlowPrint(" le Voleur\n", _textSpeed);
	    	break;
		default:
			printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	    }
    }while(classe < 1 || 4 < classe);

    classe--;
//save récupère la valeur des statistiques
    save.stats.health = vie[classe];
    save.stats.hpTmp = vie[classe];
    save.stats.mana = mana[classe];
    save.stats.mpTmp = mana[classe];
    save.stats.defense = 0;
    save.stats.strength = str[classe];
    save.stats.agility = agi[classe];
    save.stats.faith = fai[classe];
    save.stats.knowledge = kno[classe];
    save.stats.luck = luc[classe];

    printf("\n\t\t\t\t     ");
    SlowPrint("Appuyez sur une touche pour continuer", _textSpeed);
    printf("\n\t\t\t\t\t\t\t");
    fflush(stdin);
    getchar();

//Sauvegarde du personnage dans le fichier
    strcpy(save.pseudo, name);
    save.lvl = 1;
    save.xp = 0;
    save.gold = 0;
    for(i = 0; i < BAG_MAX; i++)
        save.bag[i] = 0;
    for(i = 0; i < 5; i++)
   		save.gear[i] = 0;
    for(i = 0; i < SPELL_MAX; i++)
        save.spells[i] = 0;
    save.time.total.hh = 0;
    save.time.total.mm = 0;
    save.time.total.ss = 0;
//Date et heure actuelles
    save.time.lastT.hh = date.tm_hour;
    save.time.lastT.mm = date.tm_min;
    save.time.lastT.ss = date.tm_sec;
    save.time.lastD.yy = date.tm_year + 1900;
    save.time.lastD.mm = date.tm_mon + 1;
    save.time.lastD.dd = date.tm_mday;

    printf("\n\t\t\t\t\t");
    SlowPrint("Sauvegarde du personnage en cours\n", _textSpeed*5);
    choix = Save(save, -1);

    if(choix != 0)
    {
        time_t begin = time(NULL);

        Game(&save);

        time_t end = time(NULL);
        sec = difftime(end, begin);
        save.time.total = SecToHour((HourToSec(save.time.total) + sec));

        Save(save, 1);
    }
}

/*  *   *   *   *   *   *   *   *   *   *   */
/*      Liste des sauvegardes créées        */
/*  *   *   *   *   *   *   *   *   *   *   */
void MenuSave()
{
    short i, choix, choixB;
    char saveName[31];
    SAVE save;
    FILE *fp;

    DIR* d;
    struct dirent *dir;

    do{
        system("cls");

        d = opendir("Save");
        if(d)
        {
            printf("\n");

            i = 0;
            for(; (dir = readdir(d)) != NULL; i++)
                if(i > 1)
                {
//Récupérer le nom des fichiers de sauvegarde
                    sprintf(saveName, "%s%s", SAVEDAT, dir->d_name);

//Ouvrir le dossier portant le nom récupérer pour afficher son contenu
                    fp = fopen(saveName, "rb");
                    if(fp != NULL) //Si existe
                    {
                        fread(&save, sizeof(SAVE), 1, fp);

                        printf("\t\t\t\t/ * - * - * - * - * - * - * - * - * - * - * - * \\\n");
                        printf("\t\t\t\t|   \t    \t    \t    \t  \t  \t|\n");
                        printf("\t\t\t\t|  %hd. %s\t\tlvl %hd\t\t\t|\n", i-1, save.pseudo, save.lvl);
                        printf("\t\t\t\t|  Argent %hd\t\ttemps de jeu %hd:%hd:%hd\t|\n", save.gold, save.time.total.hh, save.time.total.mm, save.time.total.ss);
                        printf("\t\t\t\t|   \t    \t    \t    \t  \t  \t|\n");
                        printf("\t\t\t\t\\ * - * - * - * - * - * - * - * - * - * - * - * /\n");

                        fclose(fp);
                    }
                }
            closedir(d);
        }

//Détecte s'il y a des fichiers de sauvegarde, sinon retourne en arrière
        if(i > 2)
        {
            printf("\n\t\t\t\t ");
            SlowPrint("<- * - * - 0 pour revenir en arriere - * - * ->", _textSpeed);
            printf("\n\n\t\t\t\t\t    ");
            SlowPrint("Selectionner un personnage", _textSpeed);
            do{
                printf("\n\t\t\t\t\t\t\t");
                fflush(stdin);
                scanf("%hd", &choix);

//Jouer ou Supprimer
                if(0 < choix && choix < (i-1))
                {
                    printf("\n\t\t\t\t\t     ");
                    SlowPrint("Que voulez-vous faire?", _textSpeed);
                    printf("\n\t\t\t\t\t     ");
                    SlowPrint("1. Jouer\t9. Supprimer", _textSpeed);
                    printf("\n\t\t\t\t ");
                    SlowPrint("<- * - * - 0 pour revenir en arriere - * - * ->", _textSpeed);
                    do{
                        printf("\n\t\t\t\t\t\t\t");
                        fflush(stdin);
                        scanf("%hd", &choixB);

                        switch(choixB)
                        {
//Jouer
                        case 1:
                            Load(choix+2);
                            choix = 0;
                            break;
//Supprimer
                        case 9:
                            system("color 04");

                            printf("\n\t\t\t\t  ");
                            SlowPrint("Voulez-vous vraiment supprimer ce personnage?", _textSpeed*5);
                            printf("\n\t\t\t\t\t\t");
                            SlowPrint("0. Non || 1. Oui", _textSpeed*5);
                            do{
                                printf("\n\t\t\t\t\t\t\t");
                                fflush(stdin);
                                scanf("%hd", &choixB);

                                switch(choixB)
                                {
                                case 1:
                                    printf("\n\t\t\t\t\t     ");
                                    SlowPrint("Suppression en cours.......\n", _textSpeed*25);

                                    d = opendir("Save");
                                    if(d)
                                    {
                                        for(i = 0; i <= choix+2; i++, dir = readdir(d))
                                            if(i == choix+2)
                                            {
                                                sprintf(saveName, "%s%s", SAVEDAT, dir->d_name);

                                                remove(saveName);
                                            }
                                    }
                                    closedir(d);
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
                                }
                            }while(choixB < 0 || 1 < choixB);

                            system("color 03");
                            break;
                        case 0:
                            break;
                        default:
                            printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
                        }
                    }while(choixB != 1 && choixB != 9);
                }
                else
                    if(choix != 0)
                        printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
            }while(choix < 0 || (i-1) < choix);
        }
        else
            choix = 0;
    }while(choix != 0);
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
/*      Charge les données d'une sauvegarde et lance le jeu     */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
void Load(short ordreSave)
{
    short i, sec;
    char saveName[31];
    SAVE save;
    FILE *fp;

    DIR* d;
    struct dirent *dir;

    d = opendir("Save");
    if(d)
    {
        for(i = 0; i <= ordreSave; i++, dir = readdir(d))
            if(i == ordreSave)
            {
                sprintf(saveName, "%s%s", SAVEDAT, dir->d_name);

                fp = fopen(saveName, "rb");

                if(fp != NULL) //Si existe
                {
                    fread(&save, sizeof(SAVE), 1, fp);

                    fclose(fp);
                }
            }
        closedir(d);
    }

    time_t begin = time(NULL);

    Game(&save);

//Mettre à jour le nombre de temps passé à jouer
    time_t end = time(NULL);
    sec = difftime(end, begin);
    save.time.total = SecToHour(HourToSec(save.time.total) + sec);

    Save(save, 1);
}

/*  *   *   *   *   *   *   *   *   *   */
/*      Affiche les paramètres du jeu   */
/*  *   *   *   *   *   *   *   *   *   */
void Settings()
{
    short choix;

    do{
        system("cls");

        printf("\n\t\t\t\t\t\t   ");
        printf("1. Affichage\n");
        printf("\t\t\t\t\t   ");
        printf("0. Revenir au menu principal\n");
        do{
            printf("\n\t\t\t\t\t\t\t");
            fflush(stdin);
            scanf("%hd", &choix);

	        switch(choix)
	        {
	            case 1:
	                EditSettings();
	                break;
//Paramètre particulier pour le "gérant"
	            case 1234:
	                AdminSettings();
	                break;
	            case 0:
	                break;
	            default:
	                printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	        }
        }while((choix < 0 || 1 < choix) && choix != 1234);
    }while(choix != 0);
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
/*      Enregistre les données du personnage dans un fichier portant son nom    */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
//choix détermine la façon d'enregistrer le personnage
short Save(SAVE save, short choix)
{
    char saveName[31];
    FILE* fp;

    time_t secondes;
    struct tm date;
    time(&secondes);
    date=*localtime(&secondes);

    sprintf(saveName, "%s%s", SAVEDAT, save.pseudo);

    fp = fopen(saveName, "rb");

    if(fp == NULL)
        fclose(fp);
    else
    {
//Lors de la création d'un personnage, si un personnage du même nom existe, vérifie si le joueur veut vraiment le remplacer
        if(choix == -1)
        {
            printf("\n\t\t\t\t   ");
            SlowPrint("Un personnage du meme pseudo existe deja", _textSpeed);
            printf("\n\t\t\t  ");
            SlowPrint("1. Continuer et effacer l'ancien\t||\t0. Annuler", _textSpeed);
            printf("\n\t\t\t\t\t\t\t");
            while(choix == -1 || (choix != 0 && choix != 1))
                scanf("%hd", &choix);
        }
        if(choix == 0)
            return 0;

        fclose(fp);
    }

//Enregistre les données
    fp = fopen(saveName, "wb");

    save.time.lastT.hh = date.tm_hour;
    save.time.lastT.mm = date.tm_min;
    save.time.lastT.ss = date.tm_sec;
    save.time.lastD.yy = date.tm_year + 1900;
    save.time.lastD.mm = date.tm_mon + 1;
    save.time.lastD.dd = date.tm_mday;

    fwrite(&save, sizeof(SAVE), 1, fp);

    fclose(fp);

    return 1;
}

/*  *   *   *   *   *   *   *   *   *   */
/*      Change les paramètres du jeu    */
/*  *   *   *   *   *   *   *   *   *   */
void EditSettings()
{
    short choix;
    char tmp[50];
    FILE* fp;

    do{
        system("cls");

        printf("\n\t\t\t\t\t\t");
        printf("1. Duree de l'intro\n");
        printf("\t\t\t\t\t       ");
        printf("2. Vitesse des textes\n");
        printf("\t\t\t\t ");
        printf("<- * - * - 0 pour revenir en arriere - * - * ->\n");
        do{
            printf("\n\t\t\t\t\t\t\t");
            fflush(stdin);
            scanf("%hd", &choix);

	        switch(choix)
	        {
//Durée de l'intro
	        case 1:
	        	printf("\t\t\t\t\t ");
	            printf("Duree actuelle :\t%hd\n", _intro);
	            printf("\t\t\t\t  ");
	            printf("Encodez 0 pour passer l'intro au demarrage\n");
	            printf("\t\t\t\t\t ");
	            printf("Nouvelle duree (400 de base) :\n");
	            printf("\n\t\t\t\t\t\t\t");
	            scanf("%hd", &_intro);
	            break;
//Vitesse d'affichage des textes
	        case 2:
	        	printf("\t\t\t\t\t   ");
	            printf("Vitesse actuelle :\t%hd\n", _textSpeed);
	            printf("\t\t\t\t\t ");
	            printf("Nouvelle vitesse (10 de base) :\n");
	            printf("\n\t\t\t\t\t\t\t");
	            scanf("%hd", &_textSpeed);
	            break;
	        case 0:
	            break;
	        default:
	            printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	        }
        }while(choix < 0 || 2 < choix);
    }while(choix != 0);

//Enregistre les paramètres dans le fichier
    fp = fopen("Data\\Settings.ini", "wt");
    if(fp != NULL)
    {
        sprintf(tmp, "#define INTRO %hd;\n#define TEXTSPEED %hd;", _intro, _textSpeed);
        fseek(fp, 0, SEEK_SET);
        fprintf(fp, tmp);

        fclose(fp);
    }
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   */
/*      Les paramètres cachés pour "gérer" le jeu   */
/*  *   *   *   *   *   *   *   *   *   *   *   *   */
void AdminSettings()
{
    short choix;

    system("color 02");

    do{
        system("cls");

        printf("");
        printf("1. Gerer les monstres\n");
        printf("");
        printf("0. Revenir aux parametres\n");
        do{
            printf("\n\t\t\t\t\t\t\t");
            fflush(stdin);
            scanf("%hd", &choix);

	        switch(choix)
	        {
	            case 1:
	                MobsList();
	                break;
	            case 0:
	                break;
	            default:
	                printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	        }
        }while(choix < 0 || 1 < choix);
    }while(choix != 0);
    system("color 03");
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
/*      Affiche les monstres du jeu et permet de les modifier   */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
void MobsList()
{
    short i, choix, choixB, size;
    FILE* fp;
    FILE* fpp;
    ENNEMY mob;

    do{
        system("cls");

//Affichage
        fp = fopen(MOBDAT, "a+b");
        if(fp != NULL) //Si existe
        {
            i = 0;
            for(; fread(&mob, sizeof(ENNEMY), 1, fp) != 0; i++)
            {
                printf("%hd. %s\n", i+1, mob.name);
                printf("Lvl %hd\n", mob.lvl);
                printf("Hp %hd\tDef %hd\n", mob.health, mob.defense);
                printf("Str %hd\tAgi %hd\n", mob.strength, mob.agility);
                printf("Gold %hd\tExp %hd\n", mob.gold, mob.xp);
                printf("===================\n\n");
            }
            printf("%hd. NOUVEAU MONSTRE\n", i+1);
            fclose(fp);
        }

        if(i != 0)
        {
            printf("\n\t\t\t\t ");
            SlowPrint("<- * - * - 0 pour revenir en arriere - * - * ->", _textSpeed);
            printf("\n\n\t\t\t\t\t     ");
            SlowPrint("Selectionner un monstre", _textSpeed);
            do{
                printf("\n\t\t\t\t\t\t\t");
                fflush(stdin);
                scanf("%hd", &choix);

//Gestion d'un monstre
                if(0 < choix && choix < i+1)
                {
                    printf("\n\t\t\t\t\t     ");
                    SlowPrint("Que voulez-vous faire?", _textSpeed);
                    printf("\n\t\t\t\t\t   ");
                    SlowPrint("1. Modifier\t9. Supprimer", _textSpeed);
                    printf("\n\t\t\t\t ");
               		SlowPrint("<- * - * - 0 pour revenir en arriere - * - * ->", _textSpeed);
                    do{
                        printf("\n\t\t\t\t\t\t\t");
                        fflush(stdin);
                        scanf("%hd", &choixB);

                        switch(choixB)
                        {
//Modification
                    	case 1:
    	                	system("cls");

    	                    fp = fopen(MOBDAT, "rb");
    	                    if(fp != NULL) //Si existe
    	                    {
    	                        fseek(fp, (choix-1)*sizeof(ENNEMY), SEEK_SET);
    	                        fread(&mob, sizeof(ENNEMY), 1, fp);

    	                        printf("Lvl %hd. %s\n", mob.lvl, mob.name);
    	                        printf("Hp %hd\tDef %hd\n", mob.health, mob.defense);
    	                        printf("Str %hd\tAgi %hd\n", mob.strength, mob.agility);
    	                        printf("Gold %hd\tExp %hd\n", mob.gold, mob.xp);
    	                        printf("===================\n\n");

    	                        fclose(fp);
    	                    }

    	                    AddMob(choix-1);
                        	break;
//Suppression
                    	case 9:
                    		system("color 04");

                            printf("\n\t\t\t\t  ");
                            SlowPrint("Voulez-vous vraiment supprimer ce monstre?", _textSpeed*5);
                            printf("\n\t\t\t\t\t\t");
                            SlowPrint("0. Non || 1. Oui", _textSpeed*5);
                            printf("\n\t\t\t\t\t\t\t");
                            do{
                                scanf("%hd", &choixB);
                            }while(choixB < 0 || 1 < choixB);

                            if(choixB == 1)
                            {
                                printf("\n\t\t\t\t\t     ");
                                SlowPrint("Suppression en cours.......\n", _textSpeed*25);

                                fp = fopen(MOBDAT, "rb");
                                if(fp != NULL) //Si existe
                                {
                                    fseek(fp, 0, SEEK_END);
                                    size = ftell(fp)/sizeof(ENNEMY);
                                    DeleteMob(choix, size);

                                    fpp = fopen("Data\\MobsTmp.dat", "wb");
                                    if(fp != NULL) //Si existe
                                    {
                                        fseek(fp, 0, SEEK_SET);
                                        for(i = 0; i < size-1; i++)
                                        {
                                            fread(&mob, sizeof(ENNEMY), 1, fp);
                                            fwrite(&mob, sizeof(ENNEMY), 1, fpp);
                                        }
                                        fclose(fpp);
                                    }
                                    fclose(fp);

                                    remove(MOBDAT);
                                    rename("Data\\MobsTmp.dat", MOBDAT);
                                }
                            }
                            system("color 03");
                        	break;
                        case 0:
                        	break;
                    	default:
                    		printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
                        }
                    }while((choixB < 0 || 1 < choixB) && choixB != 9);
                }
                else
                {
                    if(choix == i+1)
                    {
                        system("cls");

                        AddMob(choix-1);
                    }
                }
            }while(choix < 0 || i+1 < choix);
        }
        else
            choix = 0;
    }while(choix != 0);
}

/*  *   *   *   *   *   *   *   */
/*      Ajouter un monstre      */
/*  *   *   *   *   *   *   *   */
void AddMob(short open)
{
    FILE* fp;
    ENNEMY mob;

    if(open == -1)
        fp = fopen(MOBDAT, "a+b");
    else
    {
        fp = fopen(MOBDAT, "r+b");
        fseek(fp, open*sizeof(ENNEMY), SEEK_SET);
    }
    if(fp != NULL) //Si existe
    {
        printf("Nom :\t\t");
        ReadName(mob.name, 20);

        printf("Niveau :\t");
        scanf("%hd", &mob.lvl);

        printf("Vie :\t\t");
        scanf("%hd", &mob.health);

        printf("Defense :\t");
        scanf("%hd", &mob.defense);

        printf("Force :\t\t");
        scanf("%hd", &mob.strength);

        printf("Agilite :\t");
        scanf("%hd", &mob.agility);

        printf("Argent :\t");
        scanf("%hd", &mob.gold);

        printf("Experience :\t");
        scanf("%hd", &mob.xp);

        fwrite(&mob, sizeof(ENNEMY), 1, fp);

        fclose(fp);
    }
}

/*  *   *   *   *   *   *   *   */
/*      Supprimer un monstre    */
/*  *   *   *   *   *   *   *   */
void DeleteMob(short choix, short size)
{
    FILE* fp;
    ENNEMY mobTmp;

    fp = fopen(MOBDAT, "r+b");
    if(fp != NULL) //Si existe
    {
        fseek(fp, choix*sizeof(ENNEMY), SEEK_SET);

        if(choix < size)
        {
            fread(&mobTmp, sizeof(ENNEMY), 1, fp);
            fseek(fp, (choix-1)*sizeof(ENNEMY), SEEK_SET);
            fwrite(&mobTmp, sizeof(ENNEMY), 1, fp);

            DeleteMob(choix+1, size);
        }
        fclose(fp);
    }
}
