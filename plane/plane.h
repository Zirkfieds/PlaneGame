#pragma once

#include<easyx.h>
#include<graphics.h>

#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>

#pragma comment(lib,"winmm.lib")

#ifndef _PLANE_H
#define _PLANE_H

#define PI 3.141593

#define WIDTH 480
#define WWIDTH 640
#define HEIGHT 640

#define P_VX 3
#define P_VY 3
#define P_RAD 16
#define P_HEALTH 240

#define B_VX 0
#define B_VY 6

#define E_RAD 16.0
#define E_VY 1
#define E_DMG 2
#define E_HP 10

#define I_RAD 12

#define BOSS_SIZE 48
#define RAIDER_HEALTH 2600
#define STRIKER_HEALTH 2200

#define PERK_COUNT 6
#define PERK_SHIELD 80
#define PERK_SHIELDDUR 15.0
#define PERK_GODDUR 8.0
#define PERK_MEDPACK 50
#define PERK_RAGEDUR 10.0
#define PERK_SWIFTDUR 15.0

#define BONUS 2500

#define gametick(x) Sleep(x);
#define linefill(x, y) setlinecolor(x); setfillcolor(y);
#define pen(x, y) setlinestyle(x, y);
#define random(x, y) rand()%(y-x)+x;

typedef struct BULLET {
	double x;
	double y;
	double vx;
	double vy;
	int btype;
	int damage;
	int hit;
	int enhanced;

	double initx;
	double inity;

	struct BULLET* next;

} bullet, * blt;

typedef struct ITEM {
	int itype;
	double x;
	double y;
	double vy;
	double vx;
	int pickedup;
	int subtype;
	struct ITEM* next;

} item, * itm;

typedef struct PERK {
	int ptype;
	double data1; //��󻤶� �� �������
	double data2; //��ǰ����ֵ
	double duration;
}perk;

typedef struct PLAYER {
	double posx;
	double posy;
	int vx;
	int vy;
	int state; //0�޵���
	double health;
	double maxhealth;

	int laserdmg;
	int shield;
	int fortify;
	int madness;
	int swiftness;

	perk items[PERK_COUNT];

	blt bullet; //�ӵ�

} player, * plr;

typedef struct ENEMY {
	int no;
	int escore;
	double x;
	double y;
	int etype;
	double vy;
	double health;
	double maxhealth;
	int destroyed;
	int spawntick;

	blt bullet;

	struct ENEMY* next;

} enemy, *emy;

typedef struct BOSS {

	int bosstype;

	double maxhealth;
	double health;
	int damaged;

	int atkpattern;

	int escore;
	
	int inposition; //�Ƿ��λ
	double x;
	double y;
	double tgtx; //Ŀ��x����
	double tgty; //Ŀ��y����

	//int dir;

	int moveflag;
	int attackflag;

	double vx;
	double vy;
	int dirx; //vy����
	int diry; //vx����

	blt btrace1; 
	blt btrace2; 
	blt btrace3; 
	blt btrace4; 
	blt btrace5; 
	blt btrace6; 

	int plasmaphase;
	int plasmareverse;

	int destroyed;

} boss, *bos;

typedef struct LEVEL {
	int lvlno;
	int score;
	int highscore;
	player user;
	emy enemy;
	itm item;
	boss bossemy;

} level, * lvl;

struct USER {
	char name[32];
	char pw[32];
	int highscore;
	level curlvl;

	struct USER* next;
};

enum perklist {
	shield = 0, fortify, medpack, madness, comet, swiftness
};

enum texno {
	tplayer = 0, mplayer, tplayer_fort, tblueenemy, mblueenemy, tgreenenemy, mgreenenemy, tyellowenemy, myellowenemy,
	tpurpleenemy, mpurpleenemy, tplasma, mplasma, tshield, mshield, twarning, mwarning, tboss, mboss, tbg, tfort, mfort,
	tmedpack, mmedpack, tmadness, mmadness, tsidebar, uishield, uifort, uimadness, tlogo, tbossdeath, mbossdeath,
	tplayerdeath, mplayerdeath, tcomet, mcomet, tpaused, tswiftness, mswiftness, uiswiftness, tboss2, mboss2, thexa, mhexa,
	thelix, mhelix, tboss2left, mboss2left, tboss2right, mboss2right, tbossright, mbossright, tbossleft, mbossleft, tcomet2, mcomet2
};
	
enum weaponlist {
	machinegun = 1, laserbeam, shotgun, plasmaball, deathray
};

enum bossatks {
	idle = 0, firesuppress, lasershower, plasmastorm, //raider
	helixbullet, hexadrone //striker
};

enum bossnames {
	raider = 1, striker, shocker
};

enum songname {
	button, laserfire, bulletfire, shotgunfire, deathrayfire, mute, plasmafire
};

bool game(level curlvl);						//��Ϸ��ѭ��

void drawPlr(player plane);						//�������+���Ѫ��+���Ч��
void drawEmy(emy lenemy);						//���Ƶ���+�����ӵ�
void drawBlt(blt lbullet);						//��������ӵ�
void drawhpbar(enemy enemies);					//���Ƶ���Ѫ��
void drawbosshpbar(boss bossemy);				//����bossѪ��
void drawUI(lvl curlvl);						//������Ϣ��
void drawItm(itm items);						//���Ƶ���
void drawLaser(plr plane);						//���Ƽ���
void drawBoss(boss bossemy);					//����boss
void drawBossBlt(boss bossemy);					//����boss�ӵ�

bool updatePlr(plr plane, lvl curlvl);			//�������λ��+����
void updateEmy(emy enemies, plr plane);			//���µ���λ��
void updateBlt(blt bullet, emy enemies);		//����ȫ���ӵ�
void updateItm(itm items, plr plane);			//���µ���

void spawnEnemy(emy enemy, int interval);		//���ɵ���
void spawnItem(itm items, int iseed);			//������Ʒ
int genEnemyCount(level curlvl);				//blank

void genEnemy(emy newemy);						//��ʼ����������

void perks(plr plane);							//������һ�õĵ���
double dist(int a, int b, int c, int d);		//�������
void collision(emy enemies, blt bullet);		//�ж�����ӵ��Ƿ���е���
void laserhit(emy enemies, plr plane);			//�ж���Ҽ����Ƿ�����
void pickup(itm items, plr plane);				//�������
void hitplayer(emy enemies, plr plane);			//���˵��ӵ��������

void hitboss(plr plane, bos bossemy);			//�ж�����Ƿ����boss
void laserhitboss(plr plane, bos bossemy);		//�ж���Ҽ����Ƿ����boss
void genBoss(bos bossemy);						//��ʼ��boss����
void spawnBoss(bos bossemy);					//����boss
void updateBoss(plr plane, bos bossemy);		//����bossλ��+�����ӵ�
void atkPattern(bos bossemy, int aseed, plr plane);
												//boss�����ӵ��ķ�ʽ
void directions(bos bossemy, int dseed);		//�����ƶ�ָ��
void updateBossBlt(bos bossemy, plr plane);		//����boss�ӵ�

void init(lvl curlvl);							//��ʼ���ؿ�
void score();									//��������
bool game();									//��Ϸ����

bool startup(USER* uhead);						//��������
												
void writeUser(USER* uhead);					//д�û�
void loadUser(USER* uhead);						//���û�
USER* auth(USER* uhead, USER* curuser);			//��½ϵͳ
void sortscore(USER* uhead);					//��������
void leaderboards(USER* uhead);					//���а�

void FreeAll(USER** head);						//freeһ���б�

double ddist(double a, double b, double c, double d);
												//�������(Float)
void soundfx(int songname);						//������Ч
#endif;