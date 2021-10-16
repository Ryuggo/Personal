#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#include "tools.h"

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Le nombre max de caractères             */
/*                                              */
/*  process: Encoder tous les caractères        */
/*                                              */
/*  output: /                                   */
/************************************************/
void ReadString(char* pTab, short max)
{
    short i = 0;

    fflush(stdin);
    do{
        *(pTab+i) = getchar();
        i++;
    }while(i < max && *(pTab+i-1) != '\n');
    *(pTab+i-1) = '\0';
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Le nombre max de caractères             */
/*                                              */
/*  process: Encoder des nom sans chiffre       */
/*                                              */
/*  output: short 					            */
/*      0 = Erreur 				                */
/*      1 = Réussite			                */
/************************************************/
short ReadChar(char* pTab, short max)
{
    short i = 0;

    fflush(stdin);
    do{
        *(pTab+i) = getchar();
        if(('a' <= *(pTab+i) && *(pTab+i) <= 'z') || ('A' <= *(pTab+i) && *(pTab+i) <= 'Z') || *(pTab+i) == '\n')
            i++;
        else
        {
        	*(pTab+i+1) = '\0';
        	printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));
            return 0;
        }
    }while(i < (max) && *(pTab+i-1) != '\n');
    *(pTab+i-1) = '\0';

    return 1;
}

/************************************************/
/*  input: Un pointeur de nombre short          */
/*      Le nombre max de caractères             */
/*                                              */
/*  process: Encoder des nombres entiers        */
/*                                              */
/*  output: L'adresse du tableau                */
/************************************************/
short ReadNumber(char* pTab, short max)
{
    short i = 0;
//    char tab2[max];

    fflush(stdin);

    *(pTab+i) = getchar();
    if(('0' <= *pTab && *pTab <= '9') || *pTab == '-' || *pTab == '.')
    {
        i++;

//00 -> 0
    	while(*pTab == '0')
    	{
    		*(pTab+i) = getchar();
    		if(*(pTab+i) == '\n')
    		{
    			*(pTab+i) = '\0';
    			return *pTab;
    		}

			if(('0' <= *(pTab+1) && *(pTab+1) <= '9') || *(pTab+1) == '.')
    			*pTab = *(pTab+1);
    		else
    		{
    			*(pTab+i+1) = '\0';
    			printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));
    			return *pTab;
    		}
    	}

//.x -> 0.x
		if(*pTab == '.')
        {
            *pTab = '0';
            *(pTab+1) = '.';
            i++;

            while(i < max)
        	{
        		*(pTab+i) = getchar();
        		if(*(pTab+i) == '\n')
	    		{
	    			*(pTab+i) = '\0';
	    			return *pTab;
	    		}

                if('0' <= *(pTab+i) && *(pTab+i) <= '9')
                    i++;
                else
                {
                	*(pTab+i+1) = '\0';
                	printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));
                    return *pTab;
                }
        	}
        	*(pTab+i-1) = '\0';
        	printf("Erreur : Le mot %s est trop grand\n", *pTab);
        	return *pTab;
        }

//xxx
    	while(i < max)
    	{
    		*(pTab+i) = getchar();
    		if(*(pTab+i) == '\n')
    		{
    			*(pTab+i) = '\0';
    			return *pTab;
    		}

        	if('0' <= *(pTab+i) && *(pTab+i) <= '9')
        		i++;
        	else
        	{
//xx.xx
        		if(*(pTab+i) == '.')
        		{
        			i++;
        			while(i < max)
    				{
    					*(pTab+i) = getchar();
    					if(*(pTab+i) == '\n')
		        		{
		        			*(pTab+i) = '\0';
		        			return *pTab;
		        		}

			        	if('0' <= *(pTab+i) && *(pTab+i) <= '9')
			        		i++;
			        	else
		        		{
		        			*(pTab+i+1) = '\0';
		        			printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));
		        			return *pTab;
		        		}
    				}
        		}
        		else
        		{
        			*(pTab+i+1) = '\0';
        			printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));
        			return *pTab;
        		}
        	}
    	}
    	*(pTab+i+1) = '\0';
    	printf("Erreur : Le mot %s est trop grand\n", *pTab);
	    return *pTab;
	}
	*(pTab+i+1) = '\0';
	printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));

	return *pTab;
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Le nombre max de caractères             */
/*                                              */
/*  process: Encoder des nom propres            */
/*          Mettre des majuscules au début      */
/*                                              */
/*  output: L'adresse du tableau                */
/************************************************/
short ReadName(char* pTab, short max)
{
    short i = 0;

    fflush(stdin);

    *(pTab+i) = getchar();
    if(('a' <= *pTab && *pTab <= 'z') || ('A' <= *pTab && *pTab <= 'Z') || *pTab == ' ' || *pTab == '-')
    {
    	i++;
// x
//-x
    	while(*pTab == ' ' || *pTab == '-')
    	{
    		*(pTab+i) = getchar();
    		if(*(pTab+i) == '\n')
    		{
    			if(*(pTab+i-1) == ' ' || *(pTab+i-1) == '-')
    				*(pTab+i-1) = '\0';
    			*(pTab+i) = '\0';
    			return *pTab;
    		}

			if(('a' <= *(pTab+1) && *(pTab+1) <= 'z') || ('A' <= *(pTab+1) && *(pTab+1) <= 'Z') || *(pTab+1) == ' ' || *(pTab+1) == '-')
    			*pTab = *(pTab+1);
    		else
    		{
    			*(pTab+i+1) = '\0';
    			printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));
    			return *pTab;
    		}
    	}

    	*pTab = toupper(*pTab);

    	while(i < max)
    	{
    		*(pTab+i) = getchar();
    		if(*(pTab+i) == '\n')
    		{
    			if(*(pTab+i-1) == ' ' || *(pTab+i-1) == '-')
    				*(pTab+i-1) = '\0';
    			*(pTab+i) = '\0';
    			return *pTab;
    		}

    		if(('a' <= *(pTab+i) && *(pTab+i) <= 'z') || ('A' <= *(pTab+i) && *(pTab+i) <= 'Z') || *(pTab+i) == ' ' || *(pTab+i) == '-')
    		{
    			if((*(pTab+i-1) == ' ' && *(pTab+i) == ' ') || (*(pTab+i-1) == '-' && *(pTab+i) == '-') || (*(pTab+i-1) == '-' && *(pTab+i) == ' ') || (*(pTab+i-1) == ' ' && *(pTab+i) == '-')) {}
    			else
    			{
    				if(*(pTab+i-1) == ' ' || *(pTab+i-1) == '-')
    					*(pTab+i) = toupper(*(pTab+i));
    				else
    					*(pTab+i) = tolower(*(pTab+i));
    				i++;
    			}
    		}
    		else
    		{
    			*(pTab+i+1) = '\0';
    			printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));
    			return *pTab;
    		}
    	}
    	*(pTab+i+1) = '\0';
    	printf("Erreur : Le mot %s est trop grand\n", *pTab);
	    return *pTab;
    }
	*(pTab+i+1) = '\0';
	printf("Erreur : Le mot %s contient un mauvais caractere : %c\n", *pTab, *(pTab+strlen(pTab)-1));

	return *pTab;
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Les 3 nombres pour la date (j, m, a)    */
/*                                              */
/*  process: Encoder une date au un bon format  */
/*          jj/mm/aaaa                          */
/*                                              */
/*  output: Un numéro d'erreur (0 = ok)         */
/************************************************/
short ReadDate(short* jour, short* mois, short* annee)
{
    short i, j, error = 0;
    char tab[11];

    ReadString(tab, 11);

    for(i = 0, j = 0; tab[i] != '\0' && i < 6 && error == 0; j++)
    {
        while(tab[i] != '\0' && i != 2 && i != 5 && error == 0)
        {
            if(('0' <= tab[i] && tab[i] <= '9'))
                i++;
            else
                error = j;
        }
        while(tab[i] != '\0' && i != 3 && i != 6 && error == 0)
        {
            if(tab[i] == '/')
                    i++;
            else
                error = 3;
        }
    }
    while(tab[i] != '\0' && error == 0)
    {
        if(('0' <= tab[i] && tab[i] <= '9') || tab[i] == '\0')
            i++;
        else
            error = 4;
    }

    if(error == 0)
    {
        *jour = CharToShort(tab);
        *mois = CharToShort(&tab[3]);
        *annee = CharToShort(&tab[6]);
    }
    else
    {
        if(error == 1)
            printf("Date invalide, probleme avec les jours\n");
        else
        {
            if(error == 2)
                printf("Date invalide, probleme avec les mois\n");
            else
            {
                if(error == 3)
                    printf("Date invalide, probleme avec les separations : '/'\n");
                else
                    if(error == 4)
                        printf("Date invalide, probleme avec les annees\n");
            }
        }
        tab[0] = '\0';
    }
    return error;
}

/************************************************/
/*  input: Les 3 nombres pour la date (j, m, a) */
/*                                              */
/*  process: Vérifier si la date est valide par */
/*      rapport à celle d'aujourd'hui           */
/*                                              */
/*  output: /                                   */
/************************************************/
void CheckDate(short* jour, short* mois, short* annee)
{
    short calendrier[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    time_t secondes;
    struct tm date;

    time(&secondes);
    date=*localtime(&secondes);

    if(*mois == 2)
        if((*annee % 4 == 0) && (*annee % 100 != 0 || *annee % 400 == 00))
            calendrier[2] = 29;

    if((0 < *jour && *jour <= calendrier[(*mois)-1]) && (0 < *mois && *mois <= 12))
    {
        if(*annee > 1900+date.tm_year)
        {
            printf("L'annee depasse l'annee actuelle\n");
            *jour = 0;
            *mois = 0;
            *annee = 0;
        }
        else
        {
           if(*annee == 1900+date.tm_year && *mois > date.tm_mon+1)
           {
                printf("Le mois depasse le mois actuel\n");
                *jour = 0;
                *mois = 0;
                *annee = 0;
           }
            else
            {
                if(*annee == 1900+date.tm_year && *mois == date.tm_mon+1 && *jour > date.tm_yday)
                {
                    printf("Le jour depasse la date actuelle\n");
                    *jour = 0;
                    *mois = 0;
                    *annee = 0;
                }
            }
        }
    }
    else
    {
        printf("Le jour encode n'est pas valide \n");
        *jour = 0;
        *mois = 0;
        *annee = 0;
    }
}

/************************************************/
/*  input: 2 structures de Date                 */
/*                                              */
/*  process: Comparer deux dates ensemble       */
/*                                              */
/*  output: 0 =  Dates égales                   */
/*          -1 = date1 < date2                  */
/*          1 =  date1 > date2                  */
/************************************************/
short DateCmp(MYDATE date1, MYDATE date2)
{
    if(date1.yy == date2.yy && date1.mm == date2.mm && date1.dd == date2.dd)
        return 0;

    if(date1.yy > date2.yy || (date1.yy == date2.yy && date1.mm > date2.mm) || (date1.yy == date2.yy && date1.mm == date2.mm && date1.dd > date2.dd))
        return 1;
    else
        return -1;
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Les 2 nombre pour l'heure (h, min)      */
/*                                              */
/*  process: Encoder une heure au un bon format */
/*          hh:mm                               */
/*          Vérifier si l'heure est valide      */
/*                                              */
/*  output: Un numéro d'erreur (0 = ok)         */
/************************************************/
short ReadHours(short* hh, short* mm, short* ss)
{
    short i = 0, error = 0;
    char tab[9];

    ReadString(tab, 9);

    while(i != 2 && error == 0)
    {
        if(('0' <= tab[i] && tab[i] <= '9'))
            i++;
        else
            error = 1;
    }
    while(i != 3 && error == 0)
    {
        if(tab[i] == ':')
                i++;
        else
            error = 2;
    }
    while(i != 5 && error == 0)
    {
        if('0' <= tab[i] && tab[i] <= '9')
            i++;
        else
            error = 3;
    }
    while(i != 6 && error == 0)
    {
        if(tab[i] == ':')
                i++;
        else
            error = 2;
    }
    while(tab[i] != '\0' && error == 0)
    {
        if(('0' <= tab[i] && tab[i] <= '9') || tab[i] == '\0')
            i++;
        else
            error = 4;
    }
    if(error == 0)
    {
        *hh = CharToShort(tab);
        *mm = CharToShort(tab+3);
        *ss = CharToShort(tab+6);

        if(*hh > 23)
            error = 5;
        if(*mm > 59)
            error = 6;
        if(*ss > 59)
            error = 7;
    }
    else
    {
        if(error == 1)
            printf("Heure invalide, probleme avec les heures\n");
        else
        {
            if(error == 2)
                printf("Heure invalide, probleme avec la séparation ':'\n");
            else
            {
                if(error == 3)
                    printf("Heure invalide, probleme avec les minutes\n");
                else
                    if(error == 4)
                     printf("Heure invalide, probleme avec les secondes\n");
            }
        }
        tab[0] = '\0';
    }
    if(error == 5)
    {
        printf("Heure invalide, nombre d'heures trop grand\n");
        *hh = 0;
        *mm = 0;
        *ss = 0;
    }
    else
    {
        if(error == 6)
        {
            printf("Heure invalide, nombre de minutes trop grand\n");
            *hh = 0;
            *mm = 0;
            *ss = 0;
        }
        else
            if(error == 7)
            {
                printf("Heure invalide, nombre de secondes trop grand\n");
                *hh = 0;
                *mm = 0;
                *ss = 0;
            }
    }
    return error;
}

/************************************************/
/*  input: 2 structures d'Heure                 */
/*                                              */
/*  process: Comparer deux heures ensemble      */
/*                                              */
/*  output: 0 =  Heures égales                  */
/*          -1 = hour1 < hour2                  */
/*          1 =  hour1 > hour2                  */
/************************************************/
short HourCmp(MYHOUR hour1, MYHOUR hour2)
{
    if(hour1.hh == hour2.hh && hour1.mm == hour2.mm && hour1.ss == hour2.ss)
        return 0;

    if(hour1.hh > hour2.hh || (hour1.hh == hour2.hh && hour1.mm > hour2.mm) || (hour1.hh == hour2.hh && hour1.mm == hour2.mm && hour1.ss > hour2.ss))
        return 1;
    else
        return -1;
}

/************************************************/
/*  input: Un pointeur d'une structure MYHOUR   */
/*                                              */
/*  process: Convertir des hh-mm-ss en secondes */
/*                                              */
/*  output: int de secondes                     */
/************************************************/
int HourToSec(MYHOUR hour)
{
    int sec = hour.ss + (hour.mm * 60) + (hour.hh * 3600);

    return sec;
}

/************************************************/
/*  input: Un int de secondes                   */
/*                                              */
/*  process: Convertir des secondes en hh-mm-ss */
/*                                              */
/*  output: structure de MYHOUR                 */
/************************************************/
MYHOUR SecToHour(int sec)
{
    MYHOUR hour;

    hour.hh = sec / 3600;
    hour.mm = (sec % 3600) / 60;
    hour.ss = sec - (hour.hh * 3600) - (hour.mm * 60);

    return hour;
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Le nombre max de caractères             */
/*                                              */
/*  process: Encoder un mail au bon format      */
/*          ___@___.___com                      */
/*                                              */
/*  output: Un numéro d'erreur (0 = ok)         */
/************************************************/
short ReadMail(char* pTab, short max)
{
    short i, error = 2;

    ReadString(pTab, max);
    max = strlen(pTab);

    for(i = 0; *(pTab+i) != '\0' && *(pTab+i-1) != '@' && i < max; i++)
    {
        if(*(pTab+i) == '@')
            error--;
    }
    for( ; *(pTab+i) != '\0' && *(pTab+i-1) != '.' && i < max && error == 1; i++)
    {
        if(*(pTab+i) == '.')
            error--;
        if(*(pTab+i) == '@')
            error = 3;
    }

    if(*(pTab+i) == '\0')
        error = 5;

    for( ; *(pTab+i) != '\0' && i < max && error == 0; i++)
        if((*(pTab+i) <= 'A' || 'Z' <= *(pTab+i)) && (*(pTab+i) <= 'a' || 'z' <= *(pTab+i)))
            error = 4;

    if(error == 0)
        return 0;

    if(error == 1)
        printf("Mail invalide, il manque le '.'\n");
    else
    {
        if(error == 2)
            printf("Mail invalide, il manque le '@'\n");
        else
        {
            if(error == 3)
                printf("Mail invalide, il y a trop de '@'\n");
            else
            {
                if(error == 4)
                    printf("Mail invalide, la fin contient des caracteres speciaux\n");
                else
                    if(error == 5)
                        printf("Mail invalide, fin du mail inexistant\n");
            }
        }
    }
    *pTab = '\0';

    return error;
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Le nombre max de caractères             */
/*                                              */
/*  process: Encoder un numéro de téléphone     */
/*          xxx/xx.xx.xxx                       */
/*          xx/xxx.xx.xx                        */
/*                                              */
/*  output: Un numéro d'erreur (0 = ok)         */
/************************************************/
short ReadPhone(char* pTab)
{
    short i = 0, error = 0;

    ReadString(pTab, 14);

//xxx/xx.xx.xxx
    while(i < 4 && error == 0)
    {
        while(i != 3 && error == 0)
        {
            if(('0' <= *(pTab+i) && *(pTab+i) <= '9'))
                i++;
            else
                error = 1;
        }
        while(i != 4 && error == 0)
        {
            if(*(pTab+i) == '/')
                    i++;
            else
                error = 2;
        }
    }
    while(i < 12 && error == 0)
    {
        while(i != 6 && i != 9 && i < 12 && error == 0)
        {
            if(('0' <= *(pTab+i) && *(pTab+i) <= '9') || *(pTab+i) == '\0')
                i++;
            else
                error = 1;
        }
        while(i != 7 && i != 10 && i < 12 && error == 0)
        {
            if(*(pTab+i) == '.')
                    i++;
            else
                error = 3;
        }
    }

//xx/xxx.xx.xx
    if(error != 0)
    {
        error = 0;

        while(i < 3 && error == 0)
        {
            while(i != 2 && error == 0)
            {
                if(('0' <= *(pTab+i) && *(pTab+i) <= '9'))
                    i++;
                else
                    error = 1;
            }
            while(i != 3 && error == 0)
            {
                if(*(pTab+i) == '/')
                        i++;
                else
                    error = 2;
            }
        }
        while(i < 12 && error == 0)
        {
            while(i != 6 && i != 9 && i < 12 && error == 0)
            {
                if(('0' <= *(pTab+i) && *(pTab+i) <= '9') || *(pTab+i) == '\0')
                    i++;
                else
                    error = 1;
            }
            while(i != 7 && i != 10 && i < 12 && error == 0)
            {
                if(*(pTab+i) == '.')
                        i++;
                else
                    error = 3;
            }
        }
    }

    if(error == 0)
        return 0;

    if(error == 1)
        printf("Telephone invalide, probleme avec les chiffres\n");
    else
    {
        if(error == 2)
            printf("Telephone invalide, probleme avec le '/'\n");
        else
            if(error == 3)
                printf("Telephone invalide, probleme avec le(s) '.'\n");
    }
    *pTab = '\0';

    return error;
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      Le short pour stocker une valeur entière*/
/*                                              */
/*  process: Convertir des char en short        */
/*                                              */
/*  output: Le short                            */
/************************************************/
short CharToShort(char* pTab)
{
    short nbre, i = 0;

    if(*pTab == '-')
        i = 1;

    for(nbre = 0; *(pTab+i) != '\0' && ('0' <= *(pTab+i) && *(pTab+i) <= '9'); i++)
        nbre = (nbre * 10) + (*(pTab+i) - 48);

    if(*pTab == '-')
        nbre *= -1;

    return nbre;
}

/************************************************/
/*  input: Un pointeur de tableau char          */
/*      La vitesse d'affichage (1000 = 1sec)    */
/*                                              */
/*  process: Convertir des char en short        */
/*                                              */
/*  output: /                                   */
/************************************************/
void SlowPrint(char* pTab, short speed)
{
    short size, i;

    size = strlen(pTab);

    for(i = 0; i < size; i++)
    {
        printf("%c", *(pTab+i));
        Sleep(speed);
    }
}

/************************************************/
/*  input:           */
/*                                              */
/*  process: Trier un vecteur de nombres        */
/*                                              */
/*  output: /                                   */
/************************************************/
void Heapsort()
{
    int v[50];
    int n, i;

    srand(time(NULL));
    fflush(stdin);

    do{
        printf("Taille du vecteur :\n");
        scanf("%d", &n);
    }while(n < 1 || n > 50);

    for(i = 0; i < n; i++)
    {
        v[i] = rand()%101;
        printf("%d  ", v[i]);
    }
    printf("\n\n");

    TriEpi(&v[0], n);
}

void TriEpi(int *v, int n)
{
    int i, j, tmp;
                                //phase 1
    for(i = n/2 - 1; i >= 0; i--)
        Paterner(&v[0], i, n);

    for(j = 0; j < n; j++)
        printf("%d  ", v[j]);
    printf("\n\n");
                                //phase 2
    for(i = n-1; i > 1; i--)
    {
        tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;

        Paterner(&v[0], i, i-1);

        for(j = 0; j < n; j++)
            printf("%d  ", v[j]);
        printf("\n");
    }
    printf("\n\n");
    printf("Final\n");

    for(j = 0; j < n; j++)
        printf("%d  ", v[j]);
}

void Paterner(int *v, int i, int n)
{
    int tmp;
    int j = (i+1) * 2 - 1;

    while(j < n)
    {
        if(v[j] < v[j+1])
            j++;

        if(v[i] < v[j])
        {
            tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;

            i = j;
            j = i * 2;
        }
        else
            j = n + 1;
    }
}
