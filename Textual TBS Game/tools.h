#ifndef _TOOLS_H_
#define _TOOLS_H_

typedef struct{
    short dd;
    short mm;
    short yy;
}MYDATE;

typedef struct{
    short hh;
    short mm;
    short ss;
}MYHOUR;

void ReadString(char*, short);
short ReadChar(char*, short);
short ReadNumber(char*, short);
short ReadName(char*, short);

short ReadDate(short*, short*, short*);
void CheckDate(short*, short*, short*);
short DateCmp(MYDATE, MYDATE);

short ReadHours(short*, short*, short*);
short HourCmp(MYHOUR, MYHOUR);
int HourToSec(MYHOUR);
MYHOUR SecToHour(int);

short ReadMail(char*, short);
short ReadPhone(char*);

short CharToShort(char*);

void SlowPrint(char*, short);

void Heapsort();
void TriEpi(int*, int);
void Paterner(int*, int, int);



#endif // _TOOLS_H_
