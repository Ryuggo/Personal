#ifndef _GAME_H_
#define _GAME_H_

typedef struct{
    char v1[130];
    char v2[130];
    char v3[130];
    char v4[130];
    char v5[130];
    char v6[130];
    char v7[130];
    char v8[130];
    char v9[130];
    char v10[130];
    char v11[130];
}GUI_ACTION;

void Game(SAVE*);

void Dungeon(SAVE*, short);
void Combat(SAVE*, ENNEMY*, short);
void CombatUpdate(SAVE, ENNEMY*, GUI_ACTION*, char*);
void CombatShow(GUI_ACTION*, char*);

char* CenterAction(char*);

short Attack(SAVE*, ENNEMY*, GUI_ACTION*);
void Spells(SAVE, GUI_ACTION*);
void Inventory(SAVE*, GUI_ACTION*);
short Flee(SAVE, ENNEMY*, GUI_ACTION*);
void Monster(SAVE*, ENNEMY*, GUI_ACTION*, short);

void Shop(SAVE*);

void House(SAVE*);

#endif // _GAME_H_
