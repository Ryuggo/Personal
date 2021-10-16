#ifndef _MENU_H_
#define _MENU_H_

void Intro();

void Menu();
void MenuNew();
void MenuContinue();

void Recent();
void New();
void MenuSave();
void Load(short);
void Settings();

//-1 = Nouveau personnage -> Ecrasement de fichier
//1 = Normal -> Ecrasement du même perso
short Save(SAVE, short);

void EditSettings();
void AdminSettings();

void MobsList();
//-1 = Ajout d'un mob à la fin
//x = Modification d'un mob précis
void AddMob(short);
void DeleteMob(short, short);

#endif // _MENU_H_
