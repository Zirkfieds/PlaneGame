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
	double data1; //最大护盾 或 武器类别
	double data2; //当前护盾值
	double duration;
}perk;

typedef struct PLAYER {
	double posx;
	double posy;
	int vx;
	int vy;
	int state; //0无道具
	double health;
	double maxhealth;

	int laserdmg;
	int shield;
	int fortify;
	int madness;
	int swiftness;

	perk items[PERK_COUNT];

	blt bullet; //子弹

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
	
	int inposition; //是否就位
	double x;
	double y;
	double tgtx; //目标x坐标
	double tgty; //目标y坐标

	//int dir;

	int moveflag;
	int attackflag;

	double vx;
	double vy;
	int dirx; //vy方向
	int diry; //vx方向

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

bool game(level curlvl);						//游戏主循环

void drawPlr(player plane);						//绘制玩家+玩家血条+玩家效果
void drawEmy(emy lenemy);						//绘制敌人+敌人子弹
void drawBlt(blt lbullet);						//绘制玩家子弹
void drawhpbar(enemy enemies);					//绘制敌人血条
void drawbosshpbar(boss bossemy);				//绘制boss血条
void drawUI(lvl curlvl);						//绘制信息栏
void drawItm(itm items);						//绘制道具
void drawLaser(plr plane);						//绘制激光
void drawBoss(boss bossemy);					//绘制boss
void drawBossBlt(boss bossemy);					//绘制boss子弹

bool updatePlr(plr plane, lvl curlvl);			//更新玩家位置+操作
void updateEmy(emy enemies, plr plane);			//更新敌人位置
void updateBlt(blt bullet, emy enemies);		//更新全部子弹
void updateItm(itm items, plr plane);			//更新道具

void spawnEnemy(emy enemy, int interval);		//生成敌人
void spawnItem(itm items, int iseed);			//生成物品
int genEnemyCount(level curlvl);				//blank

void genEnemy(emy newemy);						//初始化敌人属性

void perks(plr plane);							//处理玩家获得的道具
double dist(int a, int b, int c, int d);		//计算距离
void collision(emy enemies, blt bullet);		//判断玩家子弹是否击中敌人
void laserhit(emy enemies, plr plane);			//判断玩家激光是否命中
void pickup(itm items, plr plane);				//捡起道具
void hitplayer(emy enemies, plr plane);			//敌人的子弹击中玩家

void hitboss(plr plane, bos bossemy);			//判定玩家是否击中boss
void laserhitboss(plr plane, bos bossemy);		//判定玩家激光是否击中boss
void genBoss(bos bossemy);						//初始化boss属性
void spawnBoss(bos bossemy);					//生成boss
void updateBoss(plr plane, bos bossemy);		//更新boss位置+发射子弹
void atkPattern(bos bossemy, int aseed, plr plane);
												//boss发射子弹的方式
void directions(bos bossemy, int dseed);		//生成移动指令
void updateBossBlt(bos bossemy, plr plane);		//更新boss子弹

void init(lvl curlvl);							//初始化关卡
void score();									//分数计算
bool game();									//游戏主体

bool startup(USER* uhead);						//启动界面
												
void writeUser(USER* uhead);					//写用户
void loadUser(USER* uhead);						//读用户
USER* auth(USER* uhead, USER* curuser);			//登陆系统
void sortscore(USER* uhead);					//分数排序
void leaderboards(USER* uhead);					//排行榜

void FreeAll(USER** head);						//free一个列表

double ddist(double a, double b, double c, double d);
												//计算距离(Float)
void soundfx(int songname);						//播放音效
#endif;