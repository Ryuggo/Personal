#ifndef _MAIN_H_
#define _MAIN_H_

#include "tools.c"

#define BAG_MAX 51
#define SPELL_MAX 20
#define QUEST_MAX 20

#define NOP {system("cls");SlowPrint("Partie pas encore faite\n", _textSpeed*5);fflush(stdin);getchar();}

typedef struct{
	short health;
	short hpTmp;
	short mana;
	short mpTmp;
	short defense;
	short strength;
	short agility;
	short faith;
	short knowledge;
	short luck;
}STATS;

typedef struct{
	short id;
	char name[20];
	char desc[100];
	short cost;
}ITEM;

typedef struct{
	short id;
	char name[20];
	char desc[100];
	short cost;
	short damage;
	short mp;
}SPELL;

typedef struct{
	MYHOUR total;
	MYHOUR lastT;
	MYDATE lastD;
}TIME;

typedef struct{
	char pseudo[15];
	short lvl;
	short xp;
	STATS stats;
	int gold;
	short bag[BAG_MAX];
	short gear[5];
	short spells[SPELL_MAX];
	TIME time;
}SAVE;

typedef struct{
	char name[20];
	short lvl;
	short health;
	short defense;
	short strength;
	short agility;
	short gold;
	short xp;
}ENNEMY;

short _intro;
short _textSpeed;
void SetsIni();

#endif // _MAIN_H_
