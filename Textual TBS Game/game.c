#include "game.h"

/*  *   *   *   *   *   */
/*      Menu du jeu     */
/*  *   *   *   *   *   */
void Game(SAVE* save)
{
	short choix, i = 1;

	do{
		system("cls");
		system("color 07");

//Menu
		printf("1. Donjon\n");
		printf("2. Marche - Pas disponible\n");
		printf("3. Maison\n");
		printf("0. Revenir au menu\n");

		do{
			fflush(stdin);
			scanf("%hd", &choix);

			switch(choix)
	        {
//Donjon
	            case 1:
	            	if(save->stats.hpTmp > 0)
	            	{
	            		SlowPrint("Quelle difficulte voulez-vous jouer?\n", _textSpeed);
	            		SlowPrint("1. Facile\n", _textSpeed);
	            		SlowPrint("2. Moyenne\n", _textSpeed);
	            		SlowPrint("3. Difficile\n", _textSpeed);
	            		SlowPrint("4. Cauchemar\n", _textSpeed);
	            		do{
	            			fflush(stdin);
	            			scanf("%hd", &i);
	            			printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	            		}while(i < 1 || 4 < i);

	            		Dungeon(save, i);
	            	}
	            	else
	            		SlowPrint("Vous n'avez pas assez d'energie pour partir a l'aventure..\n", _textSpeed*5);
	                break;
//Marché
	            case 2:
	            	Shop(save);
	                break;
//Maison
	            case 3:
	            	House(save);
	                break;
	            case 0:
	                break;
	            default:
	                printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	        }
        }while(choix < 0 || 3 < choix);
	}while(choix != 0);
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *	*/
/*      Entrer dans un donjon pour voir les monstres à affronter    */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *	*/
//j est la "difficulté" du jeu / le nombre de monstre à combattre
void Dungeon(SAVE* save, short j)
{
	short choix, nbre, size, i;
	ENNEMY mob[4];
	FILE* fp;

	system("cls");

	srand(time(NULL));

	do{
        for(i = 0; i < 4; i++)
            strcpy(mob[i].name, "\0");

		fp = fopen(MOBDAT, "rb");
		if(fp != NULL) //Si existe
    	{
    		printf("\n\t\t\t\t\t   ");
    		if(j == 1)
    			SlowPrint("Vous rencontrez un monstre !\n\n", _textSpeed);
    		else
    			SlowPrint("Vous rencontrez des monstres !\n\n", _textSpeed);

    		fseek(fp, 0, SEEK_END);
    		size = ftell(fp) / sizeof(ENNEMY);

//Sélectionne aléatoirement un monstre dans la liste de monstre en fonction du niveau du joueur
    		for(i = 0; i < j; i++, choix = 0)
				while(choix != -1)
				{
					nbre = rand() % size;
		    		fseek(fp, nbre*sizeof(ENNEMY), SEEK_SET);
		    		fread(&mob[i], sizeof(ENNEMY), 1, fp);
		    		if(mob[i].lvl <= save->lvl)
		    			choix = -1;
				}
    		fclose(fp);

//Affiche les monstres à combattre
    		for(i = 0; i < j; i++)
    		{
	    		printf("\t\t\t\t\t\t");
	    		printf("%s\t%hd Hp\n\n", mob[i].name, mob[i].health);
	    	}
	    	printf("\t\t\t\t\t     ");
    		printf("Que voulez-vous faire?\n");
    		printf("\t\t\t\t\t");
    		printf("1. Combattre\t||\t0. Quitter le donjon\n");

    		do{
    			printf("\n\t\t\t\t\t\t\t");
    			fflush(stdin);
    			scanf("%hd", &choix);

	    		switch(choix)
	    		{
	    			case 1:
	    				Combat(save, mob, j);
	    				break;
	    			case 0:
	    				break;
	    			default:
	    				printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	    		}
    		}while(choix < 0 || 1 < choix);
    	}
    	else
    	{
    		printf("Erreur : Il manque des fichiers au jeu\n");
    		choix == 0;
    	}
	}while(choix != 0 && save->stats.hpTmp > 0);

	printf("\t\t\t\t   ");
	if(save->stats.hpTmp < 0)
		SlowPrint("Vous ne pouvez plus continuer dans cet etat..\n", _textSpeed*5);
}

/*  *   *   *   *   *   *   *   *   *   *   *   */
/*      Menu pour combattre le/les monstre.s    */
/*  *   *   *   *   *   *   *   *   *   *   *   */
void Combat(SAVE* save, ENNEMY* mob, short j)
{
	short nbre, nbreG, nbreX;
	short choix, i, over = j;
	short goldTmp = 0, xpTmp = 0;
	char tmp[69], tmp2[69];
//Initialise un menu vide pour l'affichage
	GUI_ACTION info = {"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   ",
						"                                                                   "};

	sprintf(tmp, "/!\\ Le combat commence /!\\");
	for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
		tmp2[i] = ' ';
	strcpy(tmp2+i, tmp);
	CombatUpdate(*save, mob, &info, tmp2);

//Si le monstre est plus agile que le joueur, il commence à jouer
	if(mob->agility > save->stats.agility)
	{
		sprintf(tmp, "Le monstre vous saute dessus");
		for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
			tmp2[i] = ' ';
		strcpy(tmp2+i, tmp);
		CombatUpdate(*save, mob, &info, tmp2);

//Tant que le joueur est en vie && que tous les monstres sont en vie
		while(save->stats.hpTmp > 0 && over > 0 && choix != -1)
		{
			Monster(save, mob, &info, choix);

			if(save->stats.hpTmp > 0)
			{
				sprintf(tmp, "Faites quelque chose !");
				for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    				tmp2[i] = ' ';
				strcpy(tmp2+i, tmp);
				CombatUpdate(*save, mob, &info, tmp2);
				do{
					fflush(stdin);
	                scanf("%hd", &choix);

					switch(choix)
					{
					case 1:	//Attack
						choix = Attack(save, mob, &info);
						break;
					case 2: //Defense
						sprintf(tmp, "Vous vous protegez");
						for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    						tmp2[i] = ' ';
						strcpy(tmp2+i, tmp);
						CombatUpdate(*save, mob, &info, tmp2);
						break;
					case 3:	//Spells
						Spells(*save, &info);
						break;
					case 4:	//Inventory
						Inventory(save, &info);
						break;
					case 5:	//Flee
						choix = Flee(*save, mob, &info);
						break;
					default:
						printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
	                }
				}while((choix < 1 || 5 < choix) && choix != -1);
            }
            if(choix != -1)
           		for(i = 0, over = j; i < j; i++)
            		if((mob+i)->health <= 0)
            			over--;
		}
	}
//Si le joueur est plus agile que le monstre, le joueur prend la main
	else
	{
		sprintf(tmp, "Vous surprenez le monstre !");
		for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    		tmp2[i] = ' ';
		strcpy(tmp2+i, tmp);
		CombatUpdate(*save, mob, &info, tmp2);

		while(save->stats.hpTmp > 0 && over > 0 && choix != -1)
		{
			sprintf(tmp, "Faites quelque chose !");
			for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    			tmp2[i] = ' ';
			strcpy(tmp2+i, tmp);
			CombatUpdate(*save, mob, &info, tmp2);
			do{
				fflush(stdin);
                scanf("%hd", &choix);

				switch(choix)
				{
//Attaquer
				case 1:
					choix = Attack(save, mob, &info);
					break;
//Se défendre
				case 2:
					sprintf(tmp, "Vous vous protegez");
					for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    					tmp2[i] = ' ';
					strcpy(tmp2+i, tmp);
					CombatUpdate(*save, mob, &info, tmp2);
					break;
//Sorts
				case 3:
					Spells(*save, &info);
					break;
//Inventaire
				case 4:
					Inventory(save, &info);
					break;
//Fuir
				case 5:
					choix = Flee(*save, mob, &info);
					break;
				default:
					printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
				}
			}while((choix < 1 || 5 < choix) && choix != -1);

			if(choix != -1)
				for(i = 0, over = j; i < j; i++)
	            	if((mob+i)->health <= 0)
	            		over--;
			
			if(over != 0)
				Monster(save, mob, &info, choix);
		}
	}

//Si fuite
	if(choix == -1)
	{
		for(i = 0, over = 0; i < j; i++)
			if((mob+i)->health <= 0)
			{
				goldTmp += (mob+i)->gold / 2;
				xpTmp += (mob+i)->xp / 2;
				over++;
			}
		sprintf(tmp, "%hd ennemis tues avant de fuir", over);
		for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    		tmp2[i] = ' ';
		strcpy(tmp2+i, tmp);
		CombatUpdate(*save, mob, &info, tmp2);

		save->gold += goldTmp;
		save->xp += xpTmp;

		sprintf(tmp, "+%hd pieces        +%hd experience", goldTmp, xpTmp);
		for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    		tmp2[i] = ' ';
		strcpy(tmp2+i, tmp);
		CombatUpdate(*save, mob, &info, tmp2);
	}
//Si joueur mort
	else
	{
		if(save->stats.hpTmp <= 0)
		{
			sprintf(tmp, "Vous vous etes fait tuer");
			for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    			tmp2[i] = ' ';
			strcpy(tmp2+i, tmp);
			CombatUpdate(*save, mob, &info, tmp2);

			save->gold -= save->gold / 10;
			save->xp -= save->xp / 10;

			sprintf(tmp, "-%hd pieces        -%hd experience", save->gold/10, save->xp/10);
			for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    			tmp2[i] = ' ';
			strcpy(tmp2+i, tmp);
			CombatUpdate(*save, mob, &info, tmp2);
		}
//Si monstres morts
		else
		{
			for(i = 0; i < j; i++)
			{
				goldTmp += (mob+i)->gold;
				xpTmp += (mob+i)->xp;
			}
			goldTmp *= 100;
			xpTmp *= 100;

			sprintf(tmp, "! Vous avez tuer le monstre !");
			for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    			tmp2[i] = ' ';
			strcpy(tmp2+i, tmp);
			CombatUpdate(*save, mob, &info, tmp2);
//100 / 5 - (100/5) /2 + 100	-> rand 20 - 10 = [-10, 10] + 100	-> [90, 110]
			nbreG = (rand() % (goldTmp / 5)) - (goldTmp / 5 )/2 + goldTmp;
			nbreX = (rand() % (xpTmp / 5) - (xpTmp / 5 )/2 + xpTmp);

			save->gold += nbreG/100;
			save->xp += nbreX/100;

			sprintf(tmp, "+%hd pieces        +%hd experience !", nbreG/100, nbreX/100);
			for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
    			tmp2[i] = ' ';
			strcpy(tmp2+i, tmp);
			CombatUpdate(*save, mob, &info, tmp2);
		}
	}
//Si assez d'expériences pour monter d'un niveau
	if(save->xp >= save->lvl*10 + (save->lvl*10)/4)
	{
		sprintf(tmp, "Un nouveau niveau est disponible !");
		for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
			tmp2[i] = ' ';
		strcpy(tmp2+i, tmp);
		CombatUpdate(*save, mob, &info, tmp2);
	}

	Sleep(1000);
}

/*  *   *   *   *   *   *   *   */
/*      Met à jour le menu      */
/*  *   *   *   *   *   *   *   */
void CombatUpdate(SAVE save, ENNEMY* mob, GUI_ACTION* info, char* action)
{
	short i;
	char tmp[68];
	char gui[5][130] = {
	    "/ -  * - * - * - * - * - \\                                                                   / - * - * - * - * - * - \\\n",
        "|                        |                                                                   |                        |\n",
        "  -  * - * - * - * - * - / - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - \\ - * - * - * - * - * -  \n",
        "|            1. Attaquer          2. Se defendre          3. Sorts          4. Inventaire          5. Fuir            |\n",
        "\\ -  * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - /\n"
        };

//Décale le milieu de chaque ligne à la ligne du dessus
//Ligne 1
    for(i = 0; i < (26 - strlen(save.pseudo)) / 2; i++)
    	info->v1[i] = ' ';
    strcpy(info->v1+i, save.pseudo);
    for(i += strlen(save.pseudo); i < 93; i++)
    	info->v1[i] = ' ';
	strncpy(tmp, info->v2+26, 67);
    strcpy(info->v1+26, tmp);
    for(i = 60; i < 93; i++)
    	if(info->v1[i] == '\0')
    		for(; i < 93; i++)
    			info->v1[i] = ' ';
    if(strcmp(mob->name, "\0") != 0 && mob->health > 0)
    {
	    sprintf(tmp, "1. %s", mob->name);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v1[i] = ' ';
	    strcpy(info->v1+i, tmp);
	    info->v1[i+sizeof(tmp)] = '\0';
	}
	else
		info->v1[93] = '\0';

//Ligne 2
    sprintf(tmp, "lvl. %hd", save.lvl);
    for(i = 0; i < (13 - strlen(tmp)) / 2; i++)
    	info->v2[i] = ' ';
    strcpy(info->v2+i, tmp);
    for(i += strlen(tmp); i < 15; i++)
    	info->v2[i] = ' ';
    sprintf(tmp, "exp. %hd", save.xp);
    for(i = 14; i < 13 + (13 - strlen(tmp)) / 2; i++)
    	info->v2[i] = ' ';
    strcpy(info->v2+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v2[i] = ' ';
	strncpy(tmp, info->v3+26, 67);
    strcpy(info->v2+26, tmp);
    for(i = 60; i < 93; i++)
    	if(info->v2[i] == '\0')
    		for(; i < 93; i++)
    			info->v2[i] = ' ';
    if(strcmp(mob->name, "\0") != 0 && mob->health > 0)
    {
	    sprintf(tmp, "Hp. %hd", mob->health);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v2[i] = ' ';
	    strcpy(info->v2+i, tmp);
	    info->v2[i+sizeof(tmp)] = '\0';
	}
	else
		info->v11[93] = '\0';

//Ligne 3
    sprintf(tmp, "Hp. %hd", save.stats.hpTmp);
    for(i = 0; i < (13 - strlen(tmp)) / 2; i++)
    	info->v3[i] = ' ';
    strcpy(info->v3+i, tmp);
    for(i += strlen(tmp); i < 15; i++)
    	info->v3[i] = ' ';
    sprintf(tmp, "Mp. %hd", save.stats.mpTmp);
    for(i = 14; i < 13 + (13 - strlen(tmp)) / 2; i++)
    	info->v3[i] = ' ';
    strcpy(info->v3+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v3[i] = ' ';
    strncpy(tmp, info->v4+26, 67);
    strcpy(info->v3+26, tmp);
    info->v3[93] = '\0';

//Ligne 4
    sprintf(tmp, "Def. %hd", save.stats.defense);
    for(i = 0; i < (26 - strlen(tmp)) / 2; i++)
    	info->v4[i] = ' ';
    strcpy(info->v4+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v4[i] = ' ';
	strncpy(tmp, info->v5+26, 67);
    strcpy(info->v4+26, tmp);
    for(i = 60; i < 93; i++)
    	if(info->v4[i] == '\0')
    		for(; i < 93; i++)
    			info->v4[i] = ' ';
    if(strcmp((mob+1)->name, "\0") != 0 && (mob+1)->health > 0)
    {
	    sprintf(tmp, "2. %s", (mob+1)->name);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v4[i] = ' ';
	    strcpy(info->v4+i, tmp);
	    info->v4[i+sizeof(tmp)] = '\0';
	}
	else
		info->v4[93] = '\0';

//Ligne 5
    sprintf(tmp, "For. %hd", save.stats.strength);
    for(i = 0; i < (26 - strlen(tmp)) / 2; i++)
    	info->v5[i] = ' ';
    strcpy(info->v5+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v5[i] = ' ';
	strncpy(tmp, info->v6+26, 67);
    strcpy(info->v5+26, tmp);
    for(i = 60; i < 93; i++)
    	if(info->v5[i] == '\0')
    		for(; i < 93; i++)
    			info->v5[i] = ' ';
    if(strcmp((mob+1)->name, "\0") != 0 && (mob+1)->health > 0)
    {
	    sprintf(tmp, "Hp. %hd", (mob+1)->health);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v5[i] = ' ';
	    strcpy(info->v5+i, tmp);
	    info->v5[i+sizeof(tmp)] = '\0';
	}
	else
		info->v5[93] = '\0';

//Ligne 6
    sprintf(tmp, "Agi. %hd", save.stats.agility);
    for(i = 0; i < (26 - strlen(tmp)) / 2; i++)
    	info->v6[i] = ' ';
    strcpy(info->v6+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v6[i] = ' ';
    strncpy(tmp, info->v7+26, 67);
    strcpy(info->v6+26, tmp);
    info->v6[93] = '\0';

//Ligne 7
    sprintf(tmp, "Foi. %hd", save.stats.faith);
    for(i = 0; i < (26 - strlen(tmp)) / 2; i++)
    	info->v7[i] = ' ';
    strcpy(info->v7+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v7[i] = ' ';
	strncpy(tmp, info->v8+26, 67);
    strcpy(info->v7+26, tmp);
    for(i = 60; i < 93; i++)
    	if(info->v7[i] == '\0')
    		for(; i < 93; i++)
    			info->v7[i] = ' ';
    if(strcmp((mob+2)->name, "\0") != 0 && (mob+2)->health > 0)
    {
	    sprintf(tmp, "3. %s", (mob+2)->name);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v7[i] = ' ';
	    strcpy(info->v7+i, tmp);
	    info->v7[i+sizeof(tmp)] = '\0';
	}
	else
		info->v7[93] = '\0';

//Ligne 8
    sprintf(tmp, "Int. %hd", save.stats.knowledge);
    for(i = 0; i < (26 - strlen(tmp)) / 2; i++)
    	info->v8[i] = ' ';
    strcpy(info->v8+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v8[i] = ' ';
	strncpy(tmp, info->v9+26, 67);
    strcpy(info->v8+26, tmp);
    for(i = 60; i < 93; i++)
    	if(info->v8[i] == '\0')
    		for(; i < 93; i++)
    			info->v8[i] = ' ';
    if(strcmp((mob+2)->name, "\0") != 0 && (mob+2)->health > 0)
    {
	    sprintf(tmp, "Hp. %hd", (mob+2)->health);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v8[i] = ' ';
	    strcpy(info->v8+i, tmp);
	    info->v8[i+sizeof(tmp)] = '\0';
	}
	else
		info->v8[93] = '\0';

//Ligne 9
    sprintf(tmp, "Cha. %hd", save.stats.luck);
    for(i = 0; i < (26 - strlen(tmp)) / 2; i++)
    	info->v9[i] = ' ';
    strcpy(info->v9+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v9[i] = ' ';
    strncpy(tmp, info->v10+26, 67);
    strcpy(info->v9+26, tmp);
    info->v9[93] = '\0';

//Ligne 10
    sprintf(tmp, "PO. %hd", save.gold);
    for(i = 0; i < (26 - strlen(tmp)) / 2; i++)
    	info->v10[i] = ' ';
    strcpy(info->v10+i, tmp);
    for(i += strlen(tmp); i < 93; i++)
    	info->v10[i] = ' ';
	strncpy(tmp, info->v11+26, 67);
    strcpy(info->v10+26, tmp);
    for(i = 60; i < 93; i++)
    	if(info->v10[i] == '\0')
    		for(; i < 93; i++)
    			info->v10[i] = ' ';
    if(strcmp((mob+3)->name, "\0") != 0 && (mob+3)->health > 0)
    {
	    sprintf(tmp, "4. %s", (mob+3)->name);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v10[i] = ' ';
	    strcpy(info->v10+i, tmp);
	    info->v10[i+sizeof(tmp)] = '\0';
	}
	else
		info->v10[93] = '\0';

//Ligne 11 - Ajout d'une nouvelle information
    for(i = 0; i < 93; i++)
    	info->v11[i] = ' ';
	strcpy(info->v11+26, action);
    for(i = 60; i < 93; i++)
    	if(info->v11[i] == '\0')
    		for(; i < 93; i++)
    			info->v11[i] = ' ';
    if(strcmp((mob+3)->name, "\0") != 0 && (mob+3)->health > 0)
    {
	    sprintf(tmp, "Hp. %hd", (mob+3)->health);
	    for(i = 93; i < 93 + (26 - strlen(tmp)) / 2; i++)
	    	info->v11[i] = ' ';
	    strcpy(info->v11+i, tmp);
	    info->v11[i+sizeof(tmp)] = '\0';
	}
	else
		info->v11[93] = '\0';

//Affichage
    CombatShow(info, &gui[0][0]);
}

/*  *   *   *   *   *   *   *   *   *   */
/*      Affichage du menu de combat     */
/*  *   *   *   *   *   *   *   *   *   */
void CombatShow(GUI_ACTION *info, char* gui)
{
	system("cls");

    printf("%s", gui);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v1);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v2);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v3);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v4);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v5);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v6);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v7);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v8);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v9);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v10);
    printf("%s", (gui+1*130));
        printf("%s\n", info->v11);
    printf("%s", (gui+1*130));
    printf("%s", (gui+2*130));
    printf("%s", (gui+3*130));
    printf("%s", (gui+4*130));

    Sleep(_textSpeed*5);
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
/*      Centre le texte informatif au milieu de l'écran     */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
char* CenterAction(char* tmp)
{
	short i;
	char tmp2[69];

	for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
		tmp2[i] = ' ';
	strcpy(tmp2+i, tmp);
	for(; i < 69; i++)
		tmp2[i] = ' ';
	tmp2[69] = '\0';

	strcpy(tmp, tmp2);

	return tmp;
}

/*  *   *   *   *   *   *   *   */
/*      Attaquer un monstre     */
/*  *   *   *   *   *   *   *   */
short Attack(SAVE* save, ENNEMY* mob, GUI_ACTION* info)
{
	short i, choix, nbre;
	char tmp[69], tmp2[69];

	for(nbre = 0; nbre < 4 && strcmp((mob+nbre)->name, "\0") != 0; nbre++);

//Choix du monstre à attaquer
	SlowPrint("Quel monstre voulez-vous attaquer? (0.Retour)\n", _textSpeed);
	do{
		fflush(stdin);
		scanf("%hd", &choix);
		choix--;

		if(0 <= choix && choix < nbre)
		{
			nbre = rand() % 100 + 1;
//Chance que le monstre esquive l'attaque
			if(nbre < (mob+choix)->agility)
		    {
		        sprintf(tmp, "%hd. %s esquive votre attaque", choix+1, (mob+choix)->name);
				for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
					tmp2[i] = ' ';
				strcpy(tmp2+i, tmp);
		        CombatUpdate(*save, mob, info, tmp2);
		    }
//Donner un coup et monstre + changer la valeur en fonction de sa défense
			else
			{
				nbre = (mob+choix)->defense / save->stats.strength;
				if(nbre == 0)
					nbre++;
				(mob+choix)->health -= save->stats.strength / nbre;

				sprintf(tmp, "%hd. %s subit des degats        -%hd Hp", choix+1, (mob+choix)->name, save->stats.strength / nbre);
				for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
					tmp2[i] = ' ';
				strcpy(tmp2+i, tmp);
				CombatUpdate(*save, mob, info, tmp2);
			}
		}
		else
		{
			if(choix == -1)
			{
				printf("Que voulez-vous faire?\t");
				return 0;
			}
			else
				printf("Mauvais choix, veuillez re-choisir\n");
		}
	}while(choix < 0 || nbre < choix);
	return 1;
}

void Spells(SAVE save, GUI_ACTION* info)
{
	NOP;
}

void Inventory(SAVE* save, GUI_ACTION* info)
{
	NOP;
}

/*  *   *   *   *   *   *   */
/*      Prendre la fuite    */
/*  *   *   *   *   *   *   */
short Flee(SAVE save, ENNEMY* mob, GUI_ACTION* info)
{
	short nbre = 0, i;
	char tmp[69], tmp2[69];

//Additionne l'agilité des monstres à combattre
	for(i = 0; i < 4 && strcmp((mob+i)->name, "\0") != 0; i++)
		if((mob+i)->health > 0)
			nbre += rand() % (mob+i)->agility;

//Chance de pouvoir esquiver
	if(nbre < save.stats.agility)
    {
    	sprintf(tmp, "Vous prenez la fuite");
    	for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
			tmp2[i] = ' ';
		strcpy(tmp2+i, tmp);
        CombatUpdate(save, mob, info, tmp2);
        return -1;
    }
//Esquive ratée
	else
	{
		sprintf(tmp, "Le monstre vous empeche de partir");
		for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
			tmp2[i] = ' ';
		strcpy(tmp2+i, tmp);
		CombatUpdate(save, mob, info, tmp2);
	}
    return 1;
}

/*  *   *   *   *   *   *   *   *	*	*/
/*      Action des monstres = Attaquer  */
/*  *   *   *   *   *   *   *   *	*	*/
void Monster(SAVE* save, ENNEMY* mob, GUI_ACTION* info, short choix)
{
	short nbre, i, j, def;
	char tmp[69], tmp2[69];

	sprintf(tmp, "Le monstre agit !");
	for(i = 0; i < (69 - strlen(tmp)) / 2; i++)
		tmp2[i] = ' ';
	strcpy(tmp2+i, tmp);
	CombatUpdate(*save, mob, info, tmp2);

//Si le joueur à choisit de se défendre
	if(choix == 2)
		def = save->stats.defense * 2;
    else
        def = save->stats.defense;

	for(i = 0; i < 4 && strcmp((mob+i)->name, "\0") != 0; i++)
	{
//Si le monstre est vivant il peut agir
		if((mob+i)->health > 0)
		{
			nbre = rand() % 100 + 1;

//Chance d'esquiver l'attaque du monstre
			if(nbre < save->stats.agility && choix != 2)
            {
                sprintf(tmp, "Vous esquivez l'attaque de %hd. %s", i+1, (mob+i)->name);
                for(j = 0; j < (69 - strlen(tmp)) / 2; j++)
					tmp2[j] = ' ';
				strcpy(tmp2+j, tmp);
                CombatUpdate(*save, mob, info, tmp2);
            }
//Se prendre un coup
			else
			{
				nbre = def / (mob+i)->strength;
				if(nbre == 0)
					nbre++;
				save->stats.hpTmp -= (mob+i)->strength / nbre;

				sprintf(tmp, "%hd. %s vous attaque        -%hd Hp", i+1, (mob+i)->name, (mob+i)->strength / nbre);
				for(j = 0; j < (69 - strlen(tmp)) / 2; j++)
					tmp2[j] = ' ';
				strcpy(tmp2+j, tmp);
				CombatUpdate(*save, mob, info, tmp2);
			}
		}
	}
}

void Shop(SAVE* save)
{
	NOP;
}

/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
/*      Menu de la maison pour monter de niveau et se soigner   */
/*  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
void House(SAVE* save)
{
	short choix;

	system("cls");

//Soins
	save->stats.hpTmp = save->stats.health;
	save->stats.mpTmp = save->stats.mana;
	SlowPrint("La vie et la magie ont ete regenerees\n", _textSpeed*5);

//Niveau supérieur disponible
	if(save->xp >= save->lvl*10 + (save->lvl*10)/4)
	{
		SlowPrint("Vous avez gagne un niveau !\n", _textSpeed);
		SlowPrint("Selectionner la statistique a augmenter\n", _textSpeed);

		printf("1. Vie\t\t[ %hd ]\n", save->stats.health);
		printf("2. Magie\t[ %hd ]\n", save->stats.mana);
		printf("3. Force\t[ %hd ]\n", save->stats.strength);
		printf("4. Agilite\t[ %hd ]\n", save->stats.agility);
		printf("5. Foi\t\t[ %hd ]\n", save->stats.faith);
		printf("6. Intelligence\t[ %hd ]\n", save->stats.knowledge);
		printf("7. Chance\t[ %hd ]\n", save->stats.luck);
		printf("8. Defense\t[ %hd ]\n", save->stats.defense);
		printf("0. Ne pas monter de niveau maintenant\n");

		do{
			fflush(stdin);
			scanf("%hd", &choix);

//Statistiques à augmenter
			switch(choix)
			{
			case 1:
				save->stats.health += 5;
				save->stats.hpTmp = save->stats.health;
				break;
			case 2:
				save->stats.mana += 5;
				save->stats.mpTmp = save->stats.mana;
				break;
			case 3:
				save->stats.strength += 2;
				break;
			case 4:
				save->stats.agility += 2;
				break;
			case 5:
				save->stats.faith += 2;
				break;
			case 6:
				save->stats.knowledge += 2;
				break;
			case 7:
				save->stats.luck += 2;
				break;
			case 8:
				save->stats.defense += 2;
				break;
			case 0:
				break;
			default:
				printf("\t\t\t\t\tMauvais choix, veuillez re-choisir\n");
			}
		}while(choix < 0 || 8 < choix);

//Réduction du nombre d'expérience pour passer le niveau
		if(choix != 0)
		{
			save->xp -= save->lvl*10 + (save->lvl*10)/4;
			save->lvl += 1;

			Save(*save, 1);
		}
	}
	else
	{
		printf("Apuyez sur une touche pour revenir en arriere\n");
		fflush(stdin);
		getchar();
	}
}
