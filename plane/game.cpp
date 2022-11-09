#include"plane.h"
											
int tick = 0;								//��Ϸ��
int eno = 0;								//���˱��
int pscore = 0;								//��ҳɼ�	
int paused = 0;								//�Ƿ���ͣ
int bossfight = 0;							//�Ƿ���bossս״̬
int bossspawned = 0;						//�Ƿ�ˢ��boss
int bgx = 0, bgy = -1920;					//����ͼƬ����
int bossdefeated = 0;						//�Ƿ����boss
int playercrashed = 0;						//����Ƿ񱻻���
int explosiontick = 0;						//��ը����ʱ��

int hscore;

clock_t pstart, pstop;						//��ʱ��
clock_t ppstart = 0, ppstop = 0;

IMAGE tex[128];								//����

void loadtex() {
	loadimage(&tex[tplayer], "./res/player_t.png");
	loadimage(&tex[mplayer], "./res/player_m.png");
	loadimage(&tex[tplayer_fort], "./res/player_t_f.png");

	loadimage(&tex[tblueenemy], "./res/enemy_blue_t.png");
	loadimage(&tex[mblueenemy], "./res/enemy_blue_m.png");

	loadimage(&tex[tgreenenemy], "./res/enemy_green_t.png");
	loadimage(&tex[mgreenenemy], "./res/enemy_green_m.png");

	loadimage(&tex[tyellowenemy], "./res/enemy_yellow_t.png");
	loadimage(&tex[myellowenemy], "./res/enemy_yellow_m.png");

	loadimage(&tex[tpurpleenemy], "./res/enemy_purple_t.png");
	loadimage(&tex[mpurpleenemy], "./res/enemy_purple_m.png");

	loadimage(&tex[tplasma], "./res/plasmaball_t.png");
	loadimage(&tex[mplasma], "./res/plasmaball_m.png");

	loadimage(&tex[thelix], "./res/helixbullet_t.png");
	loadimage(&tex[mhelix], "./res/helixbullet_m.png");

	loadimage(&tex[tshield], "./res/item_shield_t.png");
	loadimage(&tex[mshield], "./res/item_shield_m.png");

	loadimage(&tex[twarning], "./res/warning_t.png");
	loadimage(&tex[mwarning], "./res/warning_m.png");

	loadimage(&tex[tboss], "./res/boss_t.png");
	loadimage(&tex[mboss], "./res/boss_m.png");

	loadimage(&tex[tboss2], "./res/boss2_t.png");
	loadimage(&tex[mboss2], "./res/boss2_m.png");

	loadimage(&tex[tboss2left], "./res/boss2left_t.png");
	loadimage(&tex[mboss2left], "./res/boss2left_m.png");

	loadimage(&tex[tboss2right], "./res/boss2right_t.png");
	loadimage(&tex[mboss2right], "./res/boss2right_m.png");

	loadimage(&tex[tbossleft], "./res/bossleft_t.png");
	loadimage(&tex[mbossleft], "./res/bossleft_m.png");

	loadimage(&tex[tbossright], "./res/bossright_t.png");
	loadimage(&tex[mbossright], "./res/bossright_m.png");

	loadimage(&tex[tbg], "./res/gamebg_t.png");

	loadimage(&tex[tfort], "./res/item_fortify_t.png");
	loadimage(&tex[mfort], "./res/item_fortify_m.png");

	loadimage(&tex[tmedpack], "./res/item_medpack_t.png");
	loadimage(&tex[mmedpack], "./res/item_medpack_m.png");

	loadimage(&tex[tmadness], "./res/item_madness_t.png");
	loadimage(&tex[mmadness], "./res/item_madness_m.png");

	loadimage(&tex[tsidebar], "./res/sidebar_t.png");
	loadimage(&tex[tlogo], "./res/logobg_t.png");

	loadimage(&tex[uishield], "./res/ui_shield_t.png");
	loadimage(&tex[uifort], "./res/ui_fortify_t.png");
	loadimage(&tex[uimadness], "./res/ui_madness_t.png");

	loadimage(&tex[tbossdeath], "./res/boss_death_t.png");
	loadimage(&tex[mbossdeath], "./res/boss_death_m.png");

	loadimage(&tex[tplayerdeath], "./res/player_death_t.png");
	loadimage(&tex[mplayerdeath], "./res/player_death_m.png");

	loadimage(&tex[tcomet], "./res/comet_t.png");
	loadimage(&tex[mcomet], "./res/comet_m.png");

	loadimage(&tex[tcomet2], "./res/comet2_t.png");
	loadimage(&tex[mcomet2], "./res/comet2_m.png");

	loadimage(&tex[thexa], "./res/hexa_t.png");
	loadimage(&tex[mhexa], "./res/hexa_m.png");

	loadimage(&tex[tpaused], "./res/pausedbg_t.png");

	loadimage(&tex[tswiftness], "./res/item_swiftness_t.png");
	loadimage(&tex[mswiftness], "./res/item_swiftness_m.png");
	loadimage(&tex[uiswiftness], "./res/ui_swiftness_t.png");

}

void drawbg() {
	putimage(bgx, bgy, &tex[tbg]);
	if (bgy + 4 == 0) {
		bgy = -1920;
		return;
	}
	bgy += 4;
}

void init(lvl curlvl) { //��ʼ��

	curlvl->user.posx = WIDTH / 2;
	curlvl->user.posy = HEIGHT * 3 / 4;
	curlvl->user.vx = P_VX;
	curlvl->user.vy = P_VY;
	curlvl->user.state = 0;
	curlvl->user.maxhealth = P_HEALTH;
	curlvl->user.health = curlvl->user.maxhealth;
	curlvl->user.laserdmg = 2.0;

	curlvl->user.bullet = (blt)malloc(sizeof(bullet));
	curlvl->user.bullet->btype = 1;
	curlvl->user.bullet->next = NULL; //bullet

	int i;
	for (i = 0; i < PERK_COUNT; i++) {
		curlvl->user.items[i].duration = 0;
		curlvl->user.items[i].data1 = 0;
		curlvl->user.items[i].data2 = 0;
	}

	curlvl->enemy = (emy)malloc(sizeof(enemy));
	curlvl->enemy->next = NULL;
		  
	curlvl->item = (itm)malloc(sizeof(item));
	curlvl->item->next = NULL;
		  
	curlvl->user.shield = 0; //spawnwithshield
	//curlvl->user.items[shield].duration = 9999.0;
	//curlvl->user.items[shield].data1 = 9999.0;
	//curlvl->user.items[shield].data2 = 9999.0;
	curlvl->user.fortify = 0; //spawnwithfortify
	//curlvl->user.items[fortify].duration = 9999.0;
	curlvl->user.madness = 0;
	curlvl->user.swiftness = 0;
		  
	curlvl->lvlno = 0;
	curlvl->score = 0;

	pscore = 0;
	paused = 0;
	bossfight = 0;
	bossspawned = 0;
	bgx = 0, bgy = -1920;
	bossdefeated = 0;
	playercrashed = 0;
	explosiontick = 0;

	return;
}
bool game(level curlvl) { //��Ϸ����
	init(&curlvl);
	loadtex();
	srand(time(NULL));
	pstart = clock();

	int warningtick = 0;
	int bossscorereq = 5000;
	int destroyedtick = 0;

	while (1) {
		pstart = clock();
		if (pscore >= curlvl.highscore) {
			curlvl.highscore = pscore;
			hscore = pscore;
		}
		tick++;
		BeginBatchDraw();
		gametick(10);
		drawbg();
		if (bossfight) {
			if (!bossspawned) {
				bossscorereq += 8000;
				printf("Next Boss at score %d\n", bossscorereq);
				spawnBoss(&curlvl.bossemy);
				bossspawned = 1;
			}
			if (curlvl.bossemy.destroyed) {
				destroyedtick++;
				if (destroyedtick >= 400) {
					warningtick = 0;
					bossspawned = 0;
					bossfight = 0;
					destroyedtick = 0;
				}
			}
		}
		int eseed = random(200, 400);
		spawnEnemy(curlvl.enemy, eseed);

		int iseed;
		if (!bossfight) {
			iseed = random(80, 150); //fastergen
		}
		else {
			iseed = random(100, 200);
		}
		spawnItem(curlvl.item, iseed);

		updateBlt(curlvl.user.bullet, curlvl.enemy);
		if (curlvl.user.bullet->btype == deathray) {
			laserhit(curlvl.enemy, &curlvl.user);
		}

		pstop = clock();
		if (updatePlr(&curlvl.user, &curlvl)) {
			return 0;
		}

		perks(&curlvl.user);

		updateItm(curlvl.item, &curlvl.user);
		updateEmy(curlvl.enemy, &curlvl.user);
		updateBoss(&curlvl.user, &curlvl.bossemy);

		drawBlt(curlvl.user.bullet);
		drawEmy(curlvl.enemy);
		drawBoss(curlvl.bossemy);
		if (curlvl.user.bullet->btype == 5) {
			drawLaser(&curlvl.user);
		}
		drawUI(&curlvl);
		drawPlr(curlvl.user);


		if (curlvl.user.health <= 0) { //ʧ��
			playercrashed = 1;
			soundfx(mute);
			curlvl.score = 0;
			if (playercrashed) {
				if (explosiontick++ < 100) {
					putimage(curlvl.user.posx - 32, curlvl.user.posy - 32, &tex[mplayerdeath], NOTSRCERASE);
					putimage(curlvl.user.posx - 32, curlvl.user.posy - 32, &tex[tplayerdeath], SRCINVERT);
				}
				else {
					bossdefeated = 0;
					explosiontick = 0;
					playercrashed = 0;
					return 0;
				}
			}
		}
		if (curlvl.score >= bossscorereq && bossfight == 0) { //����bossս
				printf("Spawning Boss...\n");
				bossfight = 1;
				bossspawned = 0;
		}
		if (bossdefeated) {
			if (explosiontick++ < 100) {
				putimage(curlvl.bossemy.x - 64, curlvl.bossemy.y - 64, &tex[mbossdeath], NOTSRCERASE);
				putimage(curlvl.bossemy.x - 64, curlvl.bossemy.y - 64, &tex[tbossdeath], SRCINVERT);
			}
			else {
				curlvl.user.health + 100 > P_HEALTH ? curlvl.user.health = P_HEALTH : curlvl.user.health += 100;
				bossdefeated = 0;
				explosiontick = 0;
			}
		}
		

		if (bossfight) { //Ԥ��
			if (warningtick++ < 150) {
				putimage(170, 160, &tex[mwarning], NOTSRCERASE);
				putimage(170, 160, &tex[twarning], SRCINVERT);
			}
		}

		FlushBatchDraw();
		cleardevice();
	}
}

void drawUI(lvl curlvl) {
	putimage(WIDTH, 0, &tex[tsidebar]);
	putimage(WIDTH + 20, 20, &tex[tlogo]);
	curlvl->score = pscore;
	char score[32], guntype[32], weapon[16], highscore[32];
	sprintf_s(score, "Score: %d", curlvl->score);
	sprintf_s(highscore, "Highcore: %d", curlvl->highscore);
	switch (curlvl->user.bullet->btype) {
	case machinegun:
		sprintf_s(weapon, "Machine Gun");
		break;
	case laserbeam:
		sprintf_s(weapon, "Laser Beam");
		break;
	case shotgun:
		sprintf_s(weapon, "Bomb Shotgun");
		break;
	case plasmaball:
		sprintf_s(weapon, "Plasma Ball");
		break;
	case deathray:
		sprintf_s(weapon, "Death Ray");
		break;
	default:
		sprintf_s(weapon, "None");
	}
	sprintf_s(guntype, "Active Weapon:");
	settextstyle(20, 0, _T("Consolas"));
	settextcolor(YELLOW);
	setbkmode(TRANSPARENT);
	outtextxy(WIDTH + 20, 120, guntype);
	outtextxy(WIDTH + 20, 140, weapon);
	if (curlvl->user.shield) {
		settextcolor(LIGHTCYAN);
		char shielddur[64];
		sprintf_s(shielddur, "%.1lfs", curlvl->user.items[shield].duration);
		outtextxy(WIDTH + 20 - 2, 310, shielddur);
		putimage(WIDTH + 20, 280, &tex[mshield], NOTSRCERASE);
		putimage(WIDTH + 20, 280, &tex[tshield], SRCINVERT);
	}
	else {
		//setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 4);
		//linefill(LIGHTBLUE, BLUE);
		//fillrectangle(WIDTH + 20 - 4, 280 - 4, WIDTH + 20 + 36, 280 + 36);
		putimage(WIDTH + 20, 280, &tex[mshield], NOTSRCERASE);
		putimage(WIDTH + 20, 280, &tex[uishield], SRCINVERT);
	}
	if (curlvl->user.fortify) {
		settextcolor(YELLOW);
		char godmodedur[64];
		sprintf_s(godmodedur, "%.1lfs", curlvl->user.items[fortify].duration);
		outtextxy(WIDTH + 82 - 2, 310, godmodedur);
		putimage(WIDTH + 82, 280, &tex[mfort], NOTSRCERASE);
		putimage(WIDTH + 82, 280, &tex[tfort], SRCINVERT);
	}
	else {
		putimage(WIDTH + 82, 280, &tex[mfort], NOTSRCERASE);
		putimage(WIDTH + 82, 280, &tex[uifort], SRCINVERT);
	}
	if (curlvl->user.madness) {
		settextcolor(LIGHTRED);
		char ragedur[64];
		sprintf_s(ragedur, "%.1lfs", curlvl->user.items[madness].duration);
		outtextxy(WIDTH + 82, 370, ragedur);
		putimage(WIDTH + 82, 340, &tex[mmadness], NOTSRCERASE);
		putimage(WIDTH + 82, 340, &tex[tmadness], SRCINVERT);
	}
	else {
		putimage(WIDTH + 82, 340, &tex[mmadness], NOTSRCERASE);
		putimage(WIDTH + 82, 340, &tex[uimadness], SRCINVERT);
	}

	if (curlvl->user.swiftness) {
		settextcolor(WHITE);
		char swiftdur[64];
		sprintf_s(swiftdur, "%.1lfs", curlvl->user.items[swiftness].duration);
		outtextxy(WIDTH + 20, 370, swiftdur);
		putimage(WIDTH + 20, 340, &tex[mswiftness], NOTSRCERASE);
		putimage(WIDTH + 20, 340, &tex[tswiftness], SRCINVERT);
	}
	else {
		putimage(WIDTH + 20, 340, &tex[mswiftness], NOTSRCERASE);
		putimage(WIDTH + 20, 340, &tex[uiswiftness], SRCINVERT);
	}
	char tutorial1[64], tutorial2[64], tutorial3[64];
	sprintf_s(tutorial1, "�����������ƶ��ɻ�");
	sprintf_s(tutorial2, "1-5���л�ָ������");
	sprintf_s(tutorial3, "Esc������ͣ��Ϸ");
	settextstyle(20, 0, _T("΢���ź�"));
	settextcolor(YELLOW);
	setbkmode(TRANSPARENT);
	outtextxy(WIDTH + 10, 440, tutorial1);
	outtextxy(WIDTH + 10, 460, tutorial2);
	outtextxy(WIDTH + 10, 500, tutorial3);

	//char medpackeff[64];
	//settextcolor(LIGHTGREEN);
	//sprintf_s(medpackeff, "+30HP");
	//outtextxy(WIDTH + 20 - 6, 370, medpackeff);
	//putimage(WIDTH + 20, 340, &tex[mmedpack], NOTSRCERASE);
	//putimage(WIDTH + 20, 340, &tex[tmedpack], SRCINVERT);
	settextstyle(20, 0, _T("Consolas"));
	settextcolor(YELLOW);
	outtextxy(WIDTH + 20, 180, score);
	outtextxy(WIDTH + 20 - 2, 200, highscore);
}

void drawPlr(player plane) { //�������
	pen(PS_SOLID | PS_ENDCAP_FLAT, 3);
	if (playercrashed) {
		return;
	}
	if (plane.fortify) {
		putimage(plane.posx - E_RAD, plane.posy - E_RAD, &tex[mplayer], NOTSRCERASE);
		putimage(plane.posx - E_RAD, plane.posy - E_RAD, &tex[tplayer_fort], SRCINVERT);
	}
	else {
		putimage(plane.posx - E_RAD, plane.posy - E_RAD, &tex[mplayer], NOTSRCERASE);
		putimage(plane.posx - E_RAD, plane.posy - E_RAD , &tex[tplayer], SRCINVERT);
	}

	if (plane.shield) {
		double ratio = plane.items[shield].data2 / plane.items[shield].data1;
		double length = ratio * 2 * P_RAD + 2;
		setlinestyle(PS_NULL, 0);
		linefill(TRANSPARENT, LIGHTRED);
		fillrectangle(plane.posx - E_RAD, plane.posy + E_RAD + 23, plane.posx + E_RAD, plane.posy + E_RAD + 30);
		linefill(TRANSPARENT, LIGHTCYAN);
		fillrectangle(plane.posx - E_RAD, plane.posy + E_RAD + 23, plane.posx - E_RAD - 2 + length, plane.posy + E_RAD + 30);
		pen(PS_SOLID | PS_ENDCAP_FLAT, 3);
		linefill(LIGHTCYAN, LIGHTCYAN);
		circle(plane.posx, plane.posy, 2 * E_RAD);
		linefill(TRANSPARENT, LIGHTCYAN);
	}
	else {
		double ratio = plane.health / plane.maxhealth;
		double length = ratio * 2 * P_RAD + 2;
		setlinestyle(PS_NULL, 0);
		linefill(TRANSPARENT, LIGHTRED);
		fillrectangle(plane.posx - E_RAD, plane.posy + E_RAD + 5, plane.posx + E_RAD, plane.posy + E_RAD + 12);
		linefill(TRANSPARENT, LIGHTGREEN);
		fillrectangle(plane.posx - E_RAD, plane.posy + E_RAD + 5, plane.posx - E_RAD - 2 + length, plane.posy + E_RAD + 12);
		pen(PS_SOLID | PS_ENDCAP_FLAT, 3);
	}
}

void drawhpbar(enemy enemies) {
	if (!enemies.destroyed) {
		double ratio = enemies.health / enemies.maxhealth;
		//printf("%lf\n", ratio);
		double length = ratio * 2 * E_RAD + 2;
		setlinestyle(PS_NULL, 0);
		linefill(TRANSPARENT, LIGHTRED);
		fillrectangle(enemies.x - E_RAD, enemies.y + E_RAD + 5, enemies.x + E_RAD, enemies.y + E_RAD + 12);
		linefill(TRANSPARENT, LIGHTGREEN);
		fillrectangle(enemies.x - E_RAD, enemies.y + E_RAD + 5, enemies.x - E_RAD - 2 + length, enemies.y + E_RAD + 12);
		pen(PS_SOLID | PS_ENDCAP_FLAT, 3);
	}
}

bool updatePlr(plr plane, lvl curlvl) { //�������
	int songno = 0;
	if (playercrashed) {
		return 0;
	}
	double mul = 1.0;
	if (plane->swiftness) {
		mul = 1.25;
	}
	if (_kbhit()) { //���ܲ���
		//�ƶ�
		if (GetAsyncKeyState(VK_DOWN)) {
			if (plane->posy + P_VY * mul < HEIGHT - P_RAD) {
				plane->posy += P_VY * mul;
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			if (plane->posy - P_VY * mul > P_RAD) {
				plane->posy -= P_VY * mul;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			if (plane->posx - P_VX * mul > P_RAD) {
				plane->posx -= P_VX * mul;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			if (plane->posx + P_VX * mul < WIDTH - P_RAD) {
				plane->posx += P_VX * mul;
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			paused = 1;
			soundfx(button);
			while (1) {
				gametick(10);
				drawUI(curlvl);
				char pausestr1[64], pausestr2[64], pausestr3[64];
				sprintf_s(pausestr1, "PAUSED");
				sprintf_s(pausestr2, "Press space to continue");
				sprintf_s(pausestr3, "Press q to exit the game");
				settextstyle(40, 0, _T("Consolas"));
				settextcolor(LIGHTRED);
				setbkmode(TRANSPARENT);
				outtextxy(240 - 60, 280, pausestr1);
				settextstyle(20, 0, _T("Consolas"));
				outtextxy(240 - 100, 320, pausestr2);
				outtextxy(240 - 104, 340, pausestr3);
				FlushBatchDraw();
				if (GetAsyncKeyState(VK_SPACE)) {
					switch (plane->bullet->btype) {
					case laserbeam:
						soundfx(laserfire);
						break;
					case deathray:
						soundfx(deathrayfire);
						break;
					}
					paused = 0;
					fflush(stdin);
					break;
				}
				else {
					char op = _getch();
					if (op == 'q') {
						soundfx(button);
						curlvl->highscore > pscore ? curlvl->highscore : curlvl->highscore = pscore;
						return 1;
					}
				}
			}
		}
		//�ӵ������л�
		else {
			/*if (plane->madness) {
				if (_kbhit()) {
					_getch();
				}
				plane->bullet->btype = random(machinegun, deathray);
			}*/
			char op = _getch();
			switch (op) {
			case '1':
				plane->bullet->btype = machinegun;
				break;
			case '2':
				plane->bullet->btype = laserbeam;
				songno = laserfire;
				soundfx(songno);
				break;
			case '3':
				plane->bullet->btype = shotgun;
				soundfx(mute);
				break;
			case '4':
				plane->bullet->btype = plasmaball;
				soundfx(mute);
				break;
			case '5':
				plane->bullet->btype = deathray;
				songno = deathrayfire;
				soundfx(songno);
				break;
			default:
				fflush(stdin);
			}
		}
	}
	//�ӵ����Գ�ʼ��
	int bfreq = 100, bdamage = 0, bvy = 10, rflag = 0;
	if (plane->madness) {
		rflag = 1;
	}
	switch (plane->bullet->btype) {
	case 1:
		if (rflag) {
			bfreq = 25; bdamage = 50;
			bvy = 10;
		}
		else {
			bfreq = 20; bdamage = 30;
			bvy = 7;
		}
		songno = bulletfire;
		break;
	case 2:
		if (rflag) {
			bfreq = 10; bdamage = 25;
			bvy = 12;
		}
		else {
			bfreq = 10; bdamage = 15;
			bvy = 8;
		}
		break;
	case 3:
		if (rflag) {
			bfreq = 50; bdamage = 90;
			bvy = 9;
		}
		else {
			bfreq = 40; bdamage = 70;
			bvy = 7;
		}
		songno = shotgunfire;
		break;
	case 4:
		
		if (rflag) {
			bfreq = 100; bdamage = 180; 
			bvy = 12;
		}
		else {
			bfreq = 100; bdamage = 100;
			bvy = 10;
		}
		songno = plasmafire;
		break;
	}
	//�����ӵ�
	if (tick % bfreq == 0 && plane->bullet->btype != deathray) {

		if (plane->bullet->btype != laserbeam) {
			soundfx(songno);
		}
		blt temp = plane->bullet;
		blt newblt = (blt)malloc(sizeof(bullet));

		if (plane->madness) {
			newblt->enhanced = 1;
		}
		else {
			newblt->enhanced = 0;
		}
		newblt->btype = plane->bullet->btype;
		newblt->x = plane->posx;
		newblt->y = plane->posy;
		newblt->vy = bvy;
		newblt->vx = B_VX;
		newblt->damage = bdamage;
		newblt->hit = 0;
		newblt->initx = 0;
		newblt->inity = 0;

		newblt->next = NULL;

		newblt->next = temp->next;
		temp->next = newblt;
	}
	return 0;
}

void updateBlt(blt bullet, emy enemies) { //�����ӵ�
	blt temp = bullet->next;
	blt d1 = bullet;
	blt d2 = bullet;
	int flag1 = 0, flag2 = 0;
	//�ƶ��ӵ�
	for (temp; temp != NULL; temp = temp->next) {
		temp->y -= temp->vy;
		collision(enemies, temp);
		if (temp->y <= 0) {
			flag1 = 1;
		}
		if (temp->hit) {
			flag2 = 1;
		}
	}
	//����ӵ�
	if (flag1) { //����ɳ���Ļ���ӵ�
		while (d1->next != NULL && d1->next->y > 0) {
			d1 = d1->next;
		}
		blt del;
		//printf("freed-normal\n");
		del = d1->next;
		d1->next = d1->next->next;
		free(del);

	}
	if (flag2) { //������зɻ����ӵ�
		while (d2->next != NULL && d2->next->hit == 0) {
			d2 = d2->next;
		}
		blt del;
		del = d2->next;
		d2->next = d2->next->next;
		free(del);
	}
}

void updateEmyBlt(blt bullet) { //�����ӵ�
	blt temp = bullet->next;
	blt d1 = bullet;
	blt d2 = bullet;
	int flag1 = 0;
	//�ƶ��ӵ�
	for (temp; temp != NULL; temp = temp->next) {
		temp->y += temp->vy;
		if (temp->y > HEIGHT) {
			flag1 = 1;
		}
	}
	//����ӵ�
	if (flag1) { //����ɳ���Ļ�ĵл��ӵ�
		while (d1->next != NULL && d1->next->y < HEIGHT) {
			d1 = d1->next;
		}
		blt del;
		del = d1->next;
		d1->next = d1->next->next;
		free(del);
	}
}

void collision(emy enemies, blt bullet) {
	emy etemp = enemies->next;
	for (etemp; etemp != NULL; etemp = etemp->next) {
		if (!etemp->destroyed && bullet->y > E_RAD) { //�ж��ӵ���ɻ��Ӵ�
			if (dist(etemp->x, bullet->x, etemp->y, bullet->y) < 32.0) {
				etemp->health -= bullet->damage;
				if (etemp->health <= 0) {
					etemp->destroyed = 1;
					pscore += etemp->escore;
					pscore += BONUS; //instaboss
					break;
				}
				bullet->hit = 1;
			}
		}
	}
}

void laserhit(emy enemies, plr plane) {
	emy etemp = enemies->next;
	if (playercrashed) {
		return;
	}
	if (plane->madness) {
		plane->laserdmg = 3.0;
	}
	else {
		plane->laserdmg = 2.0;
	}
	for (etemp; etemp != NULL; etemp = etemp->next) {
		if (!etemp->destroyed && etemp->y > 0) {
			if (etemp->x < plane->posx + 12 && etemp->x > plane->posx - 12) {
				etemp->health -= plane->laserdmg;
				if (etemp->health <= 0) {
					etemp->destroyed = 1;
					pscore += etemp->escore;
					pscore += BONUS; //instaboss
					break;
				}
			}
		}
	}
}

void hitplayer(emy enemies, plr plane) {
	blt btemp = enemies->bullet;
	blt d = enemies->bullet;
	for (btemp; btemp != NULL; btemp = btemp->next) {
		if (dist(btemp->x, plane->posx, btemp->y, plane->posy) <= 20.0 && !btemp->hit) {
			btemp->hit = 1;
			if (plane->fortify) {
				continue;
			}
			else if (plane->shield) {
				if (plane->items[shield].data2 - btemp->damage > 0) {
					plane->items[shield].data2 -= btemp->damage;
				}
				else {
					plane->shield = 0;
					plane->items[shield].duration = 0;
				}
			}
			if (!plane->fortify && !plane->shield) {
				plane->health -= btemp->damage;
			}
		}
	}
}

void drawLaser(plr plane) {
	plr temp = plane;
	if (playercrashed) {
		return;
	}
	if (plane->madness) {
		linefill(LIGHTMAGENTA, TRANSPARENT);
		pen(PS_SOLID | PS_ENDCAP_SQUARE, 20);
		line(temp->posx, temp->posy - P_RAD, temp->posx, -P_RAD);
		linefill(WHITE, TRANSPARENT);
		pen(PS_SOLID | PS_ENDCAP_SQUARE, 12);
		line(temp->posx, temp->posy - P_RAD, temp->posx, -P_RAD);
	}
	else {
		linefill(LIGHTMAGENTA, TRANSPARENT);
		pen(PS_SOLID | PS_ENDCAP_SQUARE, 14);
		line(temp->posx, temp->posy - P_RAD, temp->posx, -P_RAD);
		linefill(WHITE, TRANSPARENT);
		pen(PS_SOLID | PS_ENDCAP_SQUARE, 6);
		line(temp->posx, temp->posy - P_RAD, temp->posx, -P_RAD);
	}
}

void drawBlt(blt lbullet) { //�����ӵ�
	blt temp = lbullet;
	//�����ӵ�
	for (temp; temp != NULL; temp = temp->next) {
		if (!temp->hit) {
			switch (temp->btype) {
			case machinegun:
				if (temp->enhanced) {
					linefill(YELLOW, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 6);
					line(temp->x - 6, temp->y - 2, temp->x - 6, temp->y - 14);
					line(temp->x + 6, temp->y - 2, temp->x + 6, temp->y - 14);
				}
				else {
					linefill(YELLOW, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 4);
					line(temp->x - 4, temp->y - 2, temp->x - 4, temp->y - 12);
					line(temp->x + 4, temp->y - 2, temp->x + 4, temp->y - 12);
				}

				break;
			case laserbeam:
				if (temp->enhanced) {
					linefill(LIGHTCYAN, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 12);
					line(temp->x, temp->y - 2, temp->x, temp->y - 20);
					linefill(WHITE, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 8);
					line(temp->x, temp->y - 2, temp->x, temp->y - 20);
				}
				else {
					linefill(LIGHTCYAN, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 8);
					line(temp->x, temp->y - 2, temp->x, temp->y - 20);
				}

				break;
			case shotgun:
				if (temp->enhanced) {
					linefill(RED, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 10);
					line(temp->x - 18, temp->y - 2, temp->x - 18, temp->y - 10);
					line(temp->x, temp->y - 2, temp->x, temp->y - 8);
					line(temp->x + 18, temp->y - 2, temp->x + 18, temp->y - 10);
					linefill(LIGHTRED, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 6);
					line(temp->x - 18, temp->y - 2, temp->x - 18, temp->y - 10);
					line(temp->x, temp->y - 2, temp->x, temp->y - 8);
					line(temp->x + 18, temp->y - 2, temp->x + 18, temp->y - 10);
				}
				else {
					linefill(LIGHTRED, TRANSPARENT);
					pen(PS_SOLID | PS_ENDCAP_SQUARE, 6);
					line(temp->x - 18, temp->y - 2, temp->x - 18, temp->y - 8);
					line(temp->x, temp->y - 2, temp->x, temp->y - 8);
					line(temp->x + 18, temp->y - 2, temp->x + 18, temp->y - 8);
				}

				break;
			case plasmaball:
				if (temp->enhanced) {
					setlinestyle(PS_SOLID, 6);
					linefill(LIGHTGREEN, TRANSPARENT);
					fillcircle(temp->x, temp->y, 20);
					putimage(temp->x - 16, temp->y - 16, &tex[mplasma], NOTSRCERASE);
					putimage(temp->x - 16, temp->y - 16, &tex[tplasma], SRCINVERT);
					break;
				}
				else {
					putimage(temp->x - 16, temp->y - 16, &tex[mplasma], NOTSRCERASE);
					putimage(temp->x - 16, temp->y - 16, &tex[tplasma], SRCINVERT);
					break;
				}
			}
		}
	}
}

int genEnemyCount(level curlvl) {
	return curlvl.lvlno * 5 + 12;
}

void genEnemy(emy newemy) {
	int eseed = rand() % 12;
	if (eseed < 3) { //3
		newemy->etype = 3;
	}
	else if (eseed > 2 && eseed < 7) { //4
		newemy->etype = 2;
	}
	else if (eseed > 6 && eseed < 8) { //1
		newemy->etype = 4;
	}
	else { //4
		newemy->etype = 1;
	}
	newemy->bullet = (blt)malloc(sizeof(bullet));
	newemy->x = random(20, 460);
	newemy->no = eno++;
	newemy->y = 0 - E_RAD * 10;
	newemy->next = NULL;
	newemy->bullet->next = NULL;

	bossfight ? newemy->destroyed = 1 : newemy->destroyed = 0; //destroyed

	switch (newemy->etype) { //��ʼ����������
	case 1:
		newemy->escore = 40;
		newemy->maxhealth = 100;
		newemy->vy = 1.6;
		newemy->bullet->btype = machinegun;
		newemy->bullet->damage = 10;
		break;
	case 2:
		newemy->escore = 60;
		newemy->maxhealth = 80;
		newemy->vy = 1.0;
		newemy->bullet->btype = machinegun;
		newemy->bullet->damage = 10;
		break;
	case 3:
		newemy->escore = 80;
		newemy->maxhealth = 120;
		newemy->vy = 0.6;
		newemy->bullet->btype = shotgun;
		newemy->bullet->damage = 20;
		break;
	case 4:
		newemy->escore = 60;
		newemy->maxhealth = 80;
		newemy->vy = 1.2;
		newemy->bullet->btype = laserbeam;
		newemy->bullet->damage = 40;
	}
	newemy->health = newemy->maxhealth;
}

void spawnEnemy(emy enemies, int interval) { //���ɵ���
	emy temp = enemies;
	if (tick % interval == 0 || tick % 200 == 0) {
		emy newemy = (emy)malloc(sizeof(enemy));
		genEnemy(newemy); //���ɵ���
		newemy->spawntick = tick;
		newemy->next = temp->next;
		temp->next = newemy;
	}
}


void drawEmy(emy enemies) {
	pen(PS_SOLID | PS_ENDCAP_FLAT, 3);
	emy temp = enemies;
	for (temp; temp != NULL; temp = temp->next) {
		if (!temp->destroyed) {
			switch (temp->etype) { //���Ƶ���
			case 1:
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[mblueenemy], NOTSRCERASE);
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[tblueenemy], SRCINVERT);
				break;
			case 2:
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[mgreenenemy], NOTSRCERASE);
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[tgreenenemy], SRCINVERT);
				break;
			case 3:
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[myellowenemy], NOTSRCERASE);
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[tyellowenemy], SRCINVERT);
				break;
			case 4:
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[mpurpleenemy], NOTSRCERASE);
				putimage(temp->x - E_RAD, temp->y - E_RAD, &tex[tpurpleenemy], SRCINVERT);
				break;
			}
		}
		drawhpbar(*temp);
	}
}

void updateEmy(emy enemies, plr plane) {  //ˢ�µ���
	emy temp = enemies->next;
	int flag1 = 0;
	emy d;
	for (temp; temp != NULL; temp = temp->next) { //�ƶ��ɻ�
		temp->y += temp->vy;
		if (temp->y >= HEIGHT) {
			flag1 = 1;
		}
	}
	temp = enemies->next;
	d = temp;
	if (flag1) {
		//�ͷű��ݻٷɻ����ڴ�
		while (d->next != NULL && d->next->y < HEIGHT) {
			d = d->next;
		}
		emy del;
		del = d->next;
		d->next = d->next->next;
		free(del);
	}
	temp = enemies->next;
	for (temp; temp != NULL; temp = temp->next) {
		if ((tick-temp->spawntick) % 150 == 0 && !temp->destroyed && temp->y <= HEIGHT - 40 && temp->y >= 40) {

			blt btemp = temp->bullet;
			blt newblt = (blt)malloc(sizeof(bullet));

			newblt->btype = temp->bullet->btype;
			newblt->x = temp->x;
			newblt->y = temp->y;
			switch (temp->etype) {
			case 4:
				newblt->vy = B_VY;
				break;
			default:
				newblt->vy = B_VY;
			}
			newblt->enhanced = 0;
			newblt->vx = B_VX;
			newblt->damage = temp->bullet->damage;
			newblt->next = NULL;
			newblt->hit = 0;
			newblt->initx = 0;
			newblt->inity = 0;

			newblt->next = btemp->next;
			newblt->next = btemp->next;
			btemp->next = newblt;
		}
	}
	temp = enemies->next;
	for (temp; temp != NULL; temp = temp->next) {
		hitplayer(temp, plane);
		drawBlt(temp->bullet);
		updateEmyBlt(temp->bullet);
	}
}

void spawnItem(itm items, int iseed) {
	itm itemp = items;
	if (tick % iseed == 0) {
		itm newitem = (itm)malloc(sizeof(item));

		newitem->pickedup = 0;
		newitem->x = random(20, 460);
		newitem->y = 0.0;
		newitem->vx = 0;
		int itemtype;
		switch (rand() % 48 + 1) {
		case 1:
		case 2:
			itemtype = shield;
			break;
		case 4:
		case 5:
			itemtype = fortify;
			break;
		case 7:
		case 8:
		case 9:
			itemtype = madness;
			break;
		case 10:
		case 11:
		case 12:
			itemtype = medpack;
			break;
		case 13:
		case 14:
		case 15:
			itemtype = swiftness;
			break;
		default:
			itemtype = comet;
			break;
		}
		newitem->itype = itemtype;
		if (newitem->itype == comet) {
			newitem->subtype = rand() % 2;
			newitem->vy = 4 + rand() % 6;
		}
		else {
			newitem->subtype = 0;
			newitem->vy = 2.0;
		}
		newitem->next = itemp->next;
		itemp->next = newitem;
	}
}

void drawItm(itm items) {
	if (items->pickedup) {
		return;
	}
	setlinestyle(PS_SOLID, 3);
	switch (items->itype) {
	case shield:
		linefill(LIGHTBLUE, LIGHTBLUE);
		fillcircle(items->x, items->y, 16);
		putimage(items->x - 16, items->y - 16, &tex[mshield], NOTSRCERASE);
		putimage(items->x - 16, items->y - 16, &tex[tshield], SRCINVERT);
		break;
	case fortify:
		linefill(YELLOW, YELLOW);
		fillcircle(items->x, items->y, 16);
		putimage(items->x - 16, items->y - 16, &tex[mfort], NOTSRCERASE);
		putimage(items->x - 16, items->y - 16, &tex[tfort], SRCINVERT);
		break;
	case medpack:
		linefill(LIGHTGREEN , LIGHTGREEN);
		fillcircle(items->x, items->y, 16);
		putimage(items->x - 16, items->y - 16, &tex[mmedpack], NOTSRCERASE);
		putimage(items->x - 16, items->y - 16, &tex[tmedpack], SRCINVERT);
		break;
	case madness:
		linefill(LIGHTRED, LIGHTRED);
		fillcircle(items->x, items->y, 16);
		putimage(items->x - 16, items->y - 16, &tex[mmadness], NOTSRCERASE);
		putimage(items->x - 16, items->y - 16, &tex[tmadness], SRCINVERT);
		break;
	case comet:
		switch (items->subtype) {
		case 1:
			putimage(items->x - 24, items->y - 24, &tex[mcomet2], NOTSRCERASE);
			putimage(items->x - 24, items->y - 24, &tex[tcomet2], SRCINVERT);
			break;
		default:
			putimage(items->x - 24, items->y - 24, &tex[mcomet], NOTSRCERASE);
			putimage(items->x - 24, items->y - 24, &tex[tcomet], SRCINVERT);
			break;
		}
		break;
	case swiftness:
		linefill(WHITE, WHITE);
		fillcircle(items->x, items->y, 16);
		putimage(items->x - 16, items->y - 16, &tex[mswiftness], NOTSRCERASE);
		putimage(items->x - 16, items->y - 16, &tex[tswiftness], SRCINVERT);
	}
}

void pickup(itm items, plr plane) {
	itm itemp = items;
	if (itemp->pickedup == 0) { //�жϷɻ�����Ʒ�Ӵ�
		if (dist(itemp->x, plane->posx, itemp->y, plane->posy) < 2 * I_RAD) {
			switch (itemp->itype) {
			case shield:
				plane->items[shield].duration += PERK_SHIELDDUR;
				plane->items[shield].data1 = PERK_SHIELD; //��󻤶�
				plane->items[shield].data2 = PERK_SHIELD; //ʣ�໤��
				plane->shield = 1;
				break;
			case fortify:
				plane->items[fortify].duration += PERK_GODDUR;
				plane->fortify = 1;
				break;
			case medpack:
				if (plane->health + PERK_MEDPACK >= P_HEALTH) {
					plane->health = P_HEALTH;
				}
				else {
					plane->health += PERK_MEDPACK;
				}
				break;
			case madness:
				plane->items[madness].duration += PERK_RAGEDUR;
				plane->items[madness].data1 = plane->bullet->btype;
				plane->madness = 1;
				break;
			case comet:
				if (plane->health - 40 > 0) {
					plane->health -= 60;
				}
				else {
					plane->health = 0;
				}
				if (plane->health <= 0) {
					playercrashed = 1;
					soundfx(mute);
				}
				break;
			case swiftness:
				plane->items[swiftness].duration += PERK_SWIFTDUR;
				plane->swiftness = 1;
				break;

			}
			itemp->pickedup = 1;
		}
	}
}

void perks(plr plane) {
	double lastcycle = (double)(pstop - pstart) * 1.5 / CLK_TCK;
	int i;
	/*double pcompensation = 0;*/
	for (i = 0; i < PERK_COUNT; i++) {
		if (plane->items[i].duration != 0) {
			plane->items[i].duration -= lastcycle;
		}
		if (plane->items[i].duration < 0) {
			plane->items[i].duration = 0;
			if (i == shield) {
				plane->shield = 0;
			}
			else if (i == fortify) {
				plane->fortify = 0;
			}
			else if (i == madness) {
				plane->bullet->btype = plane->items[madness].data1;
				switch (plane->bullet->btype) {
				case laserbeam:
					soundfx(laserfire);
					break;
				case deathray:
					soundfx(deathrayfire);
					break;
				}
				plane->madness = 0;
			}
			else if (i == swiftness) {
				plane->swiftness = 0;
			}
		}
	}
}

void updateItm(itm items, plr plane) {
	itm itemp = items->next;
	int flag1 = 0;
	for (itemp; itemp != NULL; itemp = itemp->next) {
		itemp->y += itemp->vy;
		pickup(itemp, plane);
		drawItm(itemp);
		if (itemp->pickedup) {
			flag1 = 1;
		}
	}
	itm d1 = items;
	if (flag1) { //����ɳ���Ļ����Ʒ
		while (d1->next != NULL && d1->next->y < HEIGHT && d1->next->pickedup == 0) {
			d1 = d1->next;
		}
		itm del;
		del = d1->next;
		d1->next = d1->next->next;
		free(del);
	}
}

void hitboss(plr plane, bos bossemy) {
	blt btemp = plane->bullet->next;
	if (bossemy->destroyed) {
		return;
	}
	for (btemp; btemp != NULL; btemp = btemp->next) {
		if (ddist(btemp->x, bossemy->x, btemp->y, bossemy->y) <= BOSS_SIZE) {
			if (!btemp->hit) {
				if (bossemy->health - btemp->damage > 0) {
					bossemy->health -= btemp->damage;
				}
				else {
					bossemy->destroyed = 1;
					pscore += bossemy->escore;
					bossdefeated = 1;
					printf("Boss Defeated!\n");
				}
				btemp->hit = 1;
			}
		}
	}
}

void drawbosshpbar(boss bossemy) {
	double ratio = bossemy.health / bossemy.maxhealth;
	double length = ratio * 2 * BOSS_SIZE + 2;
	setlinestyle(PS_NULL, 0);
	linefill(TRANSPARENT, LIGHTRED);
	fillrectangle(bossemy.x - BOSS_SIZE, bossemy.y + BOSS_SIZE + 5, bossemy.x + BOSS_SIZE, bossemy.y + BOSS_SIZE + 12);
	linefill(TRANSPARENT, LIGHTGREEN);
	fillrectangle(bossemy.x - BOSS_SIZE, bossemy.y + BOSS_SIZE + 5, bossemy.x - BOSS_SIZE - 2 + length, bossemy.y + BOSS_SIZE + 12);
	pen(PS_SOLID | PS_ENDCAP_FLAT, 3);
}

void laserhitboss(plr plane, bos bossemy) {
	if (bossemy->destroyed) {
		return;
	}
	if (playercrashed) {
		return;
	}
	if (plane->madness) {
		plane->laserdmg = 3.0;
	}
	else {
		plane->laserdmg = 2.0;
	}
	if (plane->bullet->btype == deathray) {
		if (bossemy->x > plane->posx - BOSS_SIZE && bossemy->x < plane->posx + BOSS_SIZE) {
			if (bossemy->health - plane->laserdmg * 0.8 > 0) {
				bossemy->health -= plane->laserdmg * 0.8;
			}
			else {
				bossemy->destroyed = 1;
				bossdefeated = 1;
				pscore += bossemy->escore;
				printf("Boss Defeated!\n");
			}
		}
	}
}

void genBoss(bos bossemy) {
	bossemy->bosstype = rand() % 2 + 1; //specifyboss
	//bossemy->bosstype = striker;
	switch (bossemy->bosstype) {
	case raider:
		bossemy->maxhealth = RAIDER_HEALTH;
		bossemy->health = RAIDER_HEALTH;
		break;
	case striker:
		bossemy->maxhealth = STRIKER_HEALTH;
		bossemy->health = STRIKER_HEALTH;
	}
	bossemy->damaged = 0;
	bossemy->atkpattern = 0;
	bossemy->escore = 3000;
	bossemy->x = WIDTH / 2;
	bossemy->y = -BOSS_SIZE;
	bossemy->vx = 2;
	bossemy->vy = 2;
	bossemy->tgtx = WIDTH / 2;
	bossemy->tgty = -BOSS_SIZE;
	bossemy->moveflag = 0;
	bossemy->inposition = 0;
	bossemy->btrace1 = (blt)malloc(sizeof(bullet));
	bossemy->btrace2 = (blt)malloc(sizeof(bullet));
	bossemy->btrace3 = (blt)malloc(sizeof(bullet));
	bossemy->btrace4 = (blt)malloc(sizeof(bullet));
	bossemy->btrace5 = (blt)malloc(sizeof(bullet));
	bossemy->btrace6 = (blt)malloc(sizeof(bullet));
	bossemy->btrace1->next = NULL;
	bossemy->btrace2->next = NULL;
	bossemy->btrace3->next = NULL;
	bossemy->btrace4->next = NULL;
	bossemy->btrace5->next = NULL;
	bossemy->btrace6->next = NULL;
	bossemy->dirx = 0;
	bossemy->diry = 0;
	bossemy->destroyed = 0;
	bossemy->plasmaphase = 1;
	bossemy->plasmareverse = 0;
	bossemy->attackflag = 1;
}

void spawnBoss(bos bossemy) {
	genBoss(bossemy);
}

void updateBoss(plr plane, bos bossemy) {
	if (!bossfight) {
		return;
	}
	if (ddist(plane->posx, bossemy->x, plane->posy, bossemy->y) <= BOSS_SIZE) {
		plane->health -= 2;
	}
	if (!bossemy->inposition) { //�Ƿ��λ
		bossemy->y += bossemy->vy;
		if (bossemy->y + bossemy->vy > 200) {
			bossemy->y = 200;
			bossemy->inposition = 1;
		}
		return;
	}
	int dseed = 0;
	if (!bossemy->destroyed) {
		switch (bossemy->bosstype) {
		case raider:
			if (plane->posx > bossemy->x - 48 && plane->posx < bossemy->x + 48) {
				dseed = random(50, 60);
			}
			else {
				dseed = random(50, 100);
			}
			break;
		case striker:
			if (plane->posx > bossemy->x - 48 && plane->posx < bossemy->x + 48) {
				dseed = random(30, 80);
			}
			else {
				dseed = random(50, 150);
			}
			break;
		}
		directions(bossemy, dseed);
	}
	if (bossemy->moveflag && !bossemy->destroyed) { //�ƶ�
		if (dist(bossemy->x, bossemy->tgtx, bossemy->y, bossemy->tgty) > 20) {
			bossemy->x += (bossemy->vx * bossemy->dirx);
			bossemy->y += (bossemy->vy * bossemy->diry);
		}
		else {
			bossemy->moveflag = 0;
			bossemy->dirx = 0;
			bossemy->diry = 0;
		}
	}
	hitboss(plane, bossemy);
	laserhitboss(plane, bossemy);
	int aseed = random(100, 150);
	atkPattern(bossemy, aseed, plane);
	updateBossBlt(bossemy, plane);
	drawBossBlt(*bossemy);
}

void directions(bos bossemy, int dseed) {
	if (!bossemy->moveflag && tick % dseed == 0) {
		double tx, ty;
		do {
			tx = random(60, 420);
			ty = random(50, 280);
		} while (ddist(tx, bossemy->x, ty, bossemy->y) <= 140 && fabs(tx - bossemy->x) < 120);
		bossemy->tgtx = tx;
		bossemy->tgty = ty;

		bossemy->vx = fabs(tx - bossemy->x) / 90;
		bossemy->vy = fabs(ty - bossemy->y) / 90;

		bossemy->tgtx > bossemy->x ? bossemy->dirx = 1 : bossemy->dirx = -1;
		bossemy->tgty > bossemy->y ? bossemy->diry = 1 : bossemy->diry = -1;
		bossemy->moveflag = 1;
	}
	else {
		return;
	}
}

void drawBoss(boss bossemy) {
	if (bossemy.destroyed) {
		return;
	}
	switch (bossemy.bosstype) {
	case raider:
		switch (bossemy.dirx) {
		case 1:
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[mbossright], NOTSRCERASE);
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[tbossright], SRCINVERT);
			break;
		case -1:
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[mbossleft], NOTSRCERASE);
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[tbossleft], SRCINVERT);
			break;
		default:
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[mboss], NOTSRCERASE);
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[tboss], SRCINVERT);
			break;
		}
		break;
	case striker:
		switch (bossemy.dirx) {
		case 1:
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[mboss2right], NOTSRCERASE);
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[tboss2right], SRCINVERT);
			break;
		case -1:
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[mboss2left], NOTSRCERASE);
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[tboss2left], SRCINVERT);
			break;
		default:
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[mboss2], NOTSRCERASE);
			putimage(bossemy.x - BOSS_SIZE, bossemy.y - BOSS_SIZE, &tex[tboss2], SRCINVERT);
			break;
		}
		break;

	}
	drawbosshpbar(bossemy);
}

void updateBossBlt(bos bossemy, plr plane) {
	blt btemp1 = bossemy->btrace1->next;
	blt btemp2 = bossemy->btrace2->next;
	blt btemp3 = bossemy->btrace3->next;
	blt btemp4 = bossemy->btrace4->next;
	blt btemp5 = bossemy->btrace5->next;
	blt btemp6 = bossemy->btrace6->next;
	int btflag1 = 0, btflag2 = 0, btflag3 = 0, btflag4 = 0, btflag5 = 0, btflag6 = 0;
	for (; btemp1 != NULL; btemp1 = btemp1->next) {
		btemp1->y += btemp1->vy;
		if (ddist(btemp1->x, plane->posx, btemp1->y, plane->posy) < P_RAD) {
			if (!btemp1->hit) {
				if (plane->fortify) {
					btemp1->hit = 1;
					continue;
				}
				if (plane->shield) {
					if (plane->items[shield].data2 - btemp1->damage >= 0) {
						plane->items[shield].data2 -= btemp1->damage;
					}
					else {
						plane->items[shield].data2 = 0;
						plane->shield = 0;
						plane->items[shield].duration = 0;
					}
				}
				else {
					plane->health -= btemp1->damage;
				}
				btemp1->hit = 1;
			}
		}
		if (btemp1->y > HEIGHT) {
			btflag1 = 1;
		}
	}
	for (; btemp2 != NULL; btemp2 = btemp2->next) {
		btemp2->y += btemp2->vy;
		if (ddist(btemp2->x, plane->posx, btemp2->y, plane->posy) < P_RAD) {
			if (!btemp2->hit) {
				if (plane->fortify) {
					btemp2->hit = 1;
					continue;
				}
				if (plane->shield) {
					if (plane->items[shield].data2 - btemp2->damage >= 0) {
						plane->items[shield].data2 -= btemp2->damage;
					}
					else {
						plane->items[shield].data2 = 0;
						plane->shield = 0;
						plane->items[shield].duration = 0;
					}
				}
				else {
					plane->health -= btemp2->damage;
				}
				btemp2->hit = 1;
			}
		}
		if (btemp2->y > HEIGHT) {
			btflag2 = 1;
		}
	}
	for (; btemp3 != NULL; btemp3 = btemp3->next) {
		btemp3->y += btemp3->vy;
		btemp3->x += btemp3->vx;
		if (ddist(btemp3->x, plane->posx, btemp3->y, plane->posy) < P_RAD) {
			if (!btemp3->hit) {
				if (plane->fortify) {
					btemp3->hit = 1;
					continue;
				}
				if (plane->shield) {
					if (plane->items[shield].data2 - btemp3->damage >= 0) {
						plane->items[shield].data2 -= btemp3->damage;
					}
					else {
						plane->items[shield].data2 = 0;
						plane->shield = 0;
						plane->items[shield].duration = 0;
					}
				}
				else {
					plane->health -= btemp3->damage;
				}
				btemp3->hit = 1;
			}
		}
		if (btemp3->y > HEIGHT) {
			btflag3 = 1;
		}
	}
	for (; btemp4 != NULL; btemp4 = btemp4->next) {
		btemp4->vx = sin(PI / 180 * ((btemp4->y - btemp4->inity) / 40) * 30 - PI / 2) * 6;
		btemp4->y += btemp4->vy;
		btemp4->x += btemp4->vx;
		if (ddist(btemp4->x, plane->posx, btemp4->y, plane->posy) < P_RAD) {
			if (!btemp4->hit) {
				if (plane->fortify) {
					btemp4->hit = 1;
					continue;
				}
				if (plane->shield) {
					if (plane->items[shield].data2 - btemp4->damage >= 0) {
						plane->items[shield].data2 -= btemp4->damage;
					}
					else {
						plane->items[shield].data2 = 0;
						plane->shield = 0;
						plane->items[shield].duration = 0;
					}
				}
				else {
					plane->health -= btemp4->damage;
				}
				btemp4->hit = 1;
			}
		}
		if (btemp4->y > HEIGHT) {
			btflag4 = 1;
		}
	}
	for (; btemp5 != NULL; btemp5 = btemp5->next) {
		btemp5->vx = -sin(PI / 180 * ((btemp5->y - btemp5->inity) / 40) * 30 - PI / 2) * 6;
		btemp5->y += btemp5->vy;
		btemp5->x += btemp5->vx;
		if (ddist(btemp5->x, plane->posx, btemp5->y, plane->posy) < P_RAD) {
			if (!btemp5->hit) {
				if (plane->fortify) {
					btemp5->hit = 1;
					continue;
				}
				if (plane->shield) {
					if (plane->items[shield].data2 - btemp5->damage >= 0) {
						plane->items[shield].data2 -= btemp5->damage;
					}
					else {
						plane->items[shield].data2 = 0;
						plane->shield = 0;
						plane->items[shield].duration = 0;
					}
				}
				else {
					plane->health -= btemp5->damage;
				}
				btemp5->hit = 1;
			}
		}
		if (btemp5->y > HEIGHT) {
			btflag5 = 1;
		}
	}
	for (; btemp6 != NULL; btemp6 = btemp6->next) {
		btemp6->y += btemp6->vy;
		btemp6->x += btemp6->vx;
		if (ddist(btemp6->x, plane->posx, btemp6->y, plane->posy) < P_RAD) {
			if (!btemp6->hit) {
				if (plane->fortify) {
					btemp6->hit = 1;
					continue;
				}
				if (plane->shield) {
					if (plane->items[shield].data2 - btemp6->damage >= 0) {
						plane->items[shield].data2 -= btemp6->damage;
					}
					else {
						plane->items[shield].data2 = 0;
						plane->shield = 0;
						plane->items[shield].duration = 0;
					}
				}
				else {
					plane->health -= btemp6->damage;
				}
				btemp6->hit = 1;
			}
		}
		if (btemp6->y > HEIGHT || btemp6->x < 0 || btemp6->y < 0 || btemp6->x > WIDTH) {
			btflag6 = 1;
		}
	}

	blt d1 = bossemy->btrace1;
	blt d2 = bossemy->btrace2;
	blt d3 = bossemy->btrace3;
	blt d4 = bossemy->btrace4;
	blt d5 = bossemy->btrace5;
	blt d6 = bossemy->btrace6;

	if (btflag1) { //����ɳ���Ļ�ĵл��ӵ�1
		while (d1->next != NULL && d1->next->y < HEIGHT) {
			d1 = d1->next;
		}
		blt del;
		del = d1->next;
		d1->next = d1->next->next;
		free(del);
	}
	if (btflag2) { //����ɳ���Ļ�ĵл��ӵ�2
		while (d2->next != NULL && d2->next->y < HEIGHT) {
			d2 = d2->next;
		}
		blt del;
		del = d2->next;
		d2->next = d2->next->next;
		free(del);
	}
	if (btflag3) { //����ɳ���Ļ�ĵл��ӵ�3
		while (d3->next != NULL && d3->next->y < HEIGHT) {
			d3 = d3->next;
		}
		blt del;
		del = d3->next;
		d3->next = d3->next->next;
		free(del);
	}
	if (btflag4) { //����ɳ���Ļ�ĵл��ӵ�4
		while (d4->next != NULL && d4->next->y < HEIGHT) {
			d4 = d4->next;
		}
		blt del;
		del = d4->next;
		d4->next = d4->next->next;
		free(del);
	}
	if (btflag5) { //����ɳ���Ļ�ĵл��ӵ�5
		while (d5->next != NULL && d5->next->y < HEIGHT) {
			d5 = d5->next;
		}
		blt del;
		del = d5->next;
		d5->next = d5->next->next;
		free(del);
	}
	if (btflag6) { //����ɳ���Ļ�ĵл��ӵ�6
		while (d6->next != NULL && (d6->next->y < HEIGHT && d6->next->x > 0 && d6->next->y > 0 && d6->next->x < WIDTH)) {
			d6 = d6->next;
		}
		blt del;
		del = d6->next;
		d6->next = d6->next->next;
		free(del);
	}
}

void atkPattern(bos bossemy, int aseed, plr plane) {
	blt btemp1 = bossemy->btrace1;
	blt btemp2 = bossemy->btrace2;
	blt btemp3 = bossemy->btrace3;
	blt btemp4 = bossemy->btrace4;
	blt btemp5 = bossemy->btrace5;
	blt btemp6 = bossemy->btrace6;

	int pstormcd = 80;

	if (bossemy->destroyed) {
		return;
	}

	if (tick % aseed == 0 && bossemy->attackflag == 1) {
		int prioratk = bossemy->atkpattern;
		switch (bossemy->bosstype) {
		case raider:
			bossemy->atkpattern = rand() % 3 + 1;
			break;
		case striker:
			do {
				bossemy->atkpattern = rand() % 3 + 3;
			} while (bossemy->atkpattern == prioratk);
			//bossemy->atkpattern = hexadrone;
			break;
		}
	}
	switch (bossemy->atkpattern) {
	case firesuppress:
		if (tick % 30 == 0) {
			blt newbt1 = (blt)malloc(sizeof(bullet));
			newbt1->damage = 10;
			newbt1->btype = shotgun;
			newbt1->x = bossemy->x - 40;
			newbt1->y = bossemy->y - 10;
			newbt1->vy = 8;
			newbt1->vx = 0;
			newbt1->hit = 0;
			newbt1->enhanced = 0;
			newbt1->next = btemp1->next;
			btemp1->next = newbt1;

			blt newbt2 = (blt)malloc(sizeof(bullet));
			newbt2->damage = 10;
			newbt2->btype = shotgun;
			newbt2->x = bossemy->x + 40;
			newbt2->y = bossemy->y - 10;
			newbt2->vy = 8;
			newbt2->vx = 0;
			newbt2->hit = 0;

			newbt2->next = btemp2->next;
			btemp2->next = newbt2;
		}
		break;
	case lasershower:
		if (tick % 10 == 0) {
			blt newbt3 = (blt)malloc(sizeof(bullet));
			newbt3->damage = 8;
			newbt3->btype = laserbeam;
			newbt3->x = bossemy->x - 48 + random(0, 96);
			newbt3->y = bossemy->y - 10;
			newbt3->vy = 8;
			newbt3->vx = 0;
			newbt3->hit = 0;
			newbt3->enhanced = 0;

			newbt3->next = btemp3->next;
			btemp3->next = newbt3;
		}
		break;
	case plasmastorm:
		if (bossemy->plasmaphase % 6 == 5 || bossemy->plasmaphase % 6 == 1) {
			pstormcd = 50;
			if (rand() % 2) {
				bossemy->plasmaphase = 5;
				bossemy->plasmareverse = 1;
				bossemy->attackflag = 1;
			}
			else {
				bossemy->plasmaphase = 1;
				bossemy->plasmareverse = 0;
				bossemy->attackflag = 1;
			}
		}
		else {
			bossemy->attackflag = 0;
			pstormcd = 8;
		}
		if (tick % pstormcd == 0) {
			blt newbt3 = (blt)malloc(sizeof(bullet));
			newbt3->damage = 16;
			newbt3->btype = plasmaball;
			newbt3->x = bossemy->x;
			newbt3->y = bossemy->y;
			newbt3->hit = 0;
			newbt3->enhanced = 0;

			newbt3->vx = sin(PI / 180 * ((bossemy->plasmaphase) % 6) * 30 - PI / 2) * 5;
			newbt3->vy = cos(PI / 180 * ((bossemy->plasmaphase) % 6) * 30 - PI / 2) * 5;

			bossemy->plasmareverse > 0 ? bossemy->plasmaphase-- : bossemy->plasmaphase++;

			newbt3->next = btemp3->next;
			btemp3->next = newbt3;
		}
		break;
	case helixbullet:
		if (tick % 20 == 0) {
			blt newbt4 = (blt)malloc(sizeof(bullet));
			newbt4->damage = 10;
			newbt4->btype = helixbullet;
			newbt4->x = bossemy->x;
			newbt4->y = bossemy->y;
			newbt4->vy = 4;
			newbt4->vx = 0;
			newbt4->hit = 0;
			newbt4->enhanced = 0;
			newbt4->initx = newbt4->x;
			newbt4->inity = newbt4->y;
			newbt4->next = btemp4->next;
			btemp4->next = newbt4;

			blt newbt5 = (blt)malloc(sizeof(bullet));
			newbt5->damage = 10;
			newbt5->btype = helixbullet;
			newbt5->x = bossemy->x;
			newbt5->y = bossemy->y;
			newbt5->vy = 4;
			newbt5->vx = 0;
			newbt5->hit = 0;
			newbt5->enhanced = 0;
			newbt5->initx = newbt5->x;
			newbt5->inity = newbt5->y;
			newbt5->next = btemp5->next;
			btemp5->next = newbt5;
		}
		break;
	case hexadrone:
		if (tick % 15 == 0) {
			blt newbt6 = (blt)malloc(sizeof(bullet));
			newbt6->damage = 10;
			newbt6->btype = hexadrone;
			newbt6->x = bossemy->x - 24 + rand() % 48;
			newbt6->y = bossemy->y;

			double normx = (plane->posx - bossemy->x) / ddist(plane->posx, bossemy->x, plane->posy, bossemy->y);
			double normy = (plane->posy - bossemy->y) / ddist(plane->posx, bossemy->x, plane->posy, bossemy->y);
			newbt6->vx = normx * 6;
			newbt6->vy = normy * 6;

			newbt6->hit = 0;
			newbt6->enhanced = 0;
			newbt6->initx = newbt6->x;
			newbt6->inity = newbt6->y;

			newbt6->next = btemp6->next;
			btemp6->next = newbt6;
		}
		break;
	}
}

void drawBossBlt(boss bossemy) {
	blt btemp1 = bossemy.btrace1->next;
	blt btemp2 = bossemy.btrace2->next;
	blt btemp3 = bossemy.btrace3->next;
	blt btemp4 = bossemy.btrace4->next;
	blt btemp5 = bossemy.btrace5->next;
	blt btemp6 = bossemy.btrace6->next;

	for (btemp1; btemp1 != NULL; btemp1 = btemp1->next) {
		if (!btemp1->hit) {
			switch (btemp1->btype) {
			case shotgun:
				linefill(YELLOW, TRANSPARENT);
				pen(PS_SOLID | PS_ENDCAP_SQUARE, 6);
				line(btemp1->x - 10, btemp1->y - 2, btemp1->x - 10, btemp1->y - 12);
				line(btemp1->x, btemp1->y - 2, btemp1->x, btemp1->y - 12);
				line(btemp1->x + 10, btemp1->y - 2, btemp1->x + 10, btemp1->y - 12);
				break;
			case helixbullet:
				putimage(btemp4->x - 8, btemp4->y - 8, &tex[mhelix], NOTSRCERASE);
				putimage(btemp4->x - 8, btemp4->y - 8, &tex[thelix], SRCINVERT);
				break;
			}
		}
	}
	for (btemp2; btemp2 != NULL; btemp2 = btemp2->next) {
		if (!btemp2->hit) {
			switch (btemp2->btype) {
			case shotgun:
				linefill(YELLOW, TRANSPARENT);
				pen(PS_SOLID | PS_ENDCAP_SQUARE, 6);
				line(btemp2->x - 10, btemp2->y - 2, btemp2->x - 10, btemp2->y - 12);
				line(btemp2->x, btemp2->y - 2, btemp2->x, btemp2->y - 12);
				line(btemp2->x + 10, btemp2->y - 2, btemp2->x + 10, btemp2->y - 12);
				break;
			}
		}
	}
	for (btemp3; btemp3 != NULL; btemp3 = btemp3->next) {
		if (!btemp3->hit) {
			switch (btemp3->btype) {
			case laserbeam:
				linefill(LIGHTMAGENTA, TRANSPARENT);
				pen(PS_SOLID | PS_ENDCAP_SQUARE, 10);
				line(btemp3->x, btemp3->y - 2, btemp3->x, btemp3->y - 24);
				linefill(WHITE, TRANSPARENT);
				pen(PS_SOLID | PS_ENDCAP_SQUARE, 6);
				line(btemp3->x, btemp3->y - 2, btemp3->x, btemp3->y - 24);
				break;
			case plasmaball:
				putimage(btemp3->x - 16, btemp3->y - 16, &tex[mplasma], NOTSRCERASE);
				putimage(btemp3->x - 16, btemp3->y - 16, &tex[tplasma], SRCINVERT);
				break;
			}
		}
	}
	for (btemp4; btemp4 != NULL; btemp4 = btemp4->next) {
		if (!btemp4->hit) {
			switch (btemp4->btype) {
			case helixbullet:
				putimage(btemp4->x - 12, btemp4->y - 12, &tex[mhelix], NOTSRCERASE);
				putimage(btemp4->x - 12, btemp4->y - 12, &tex[thelix], SRCINVERT);
				break;
			}
		}
	}
	for (btemp5; btemp5 != NULL; btemp5 = btemp5->next) {
		if (!btemp5->hit) {
			switch (btemp5->btype) {
			case helixbullet:
				putimage(btemp5->x - 12, btemp5->y - 12, &tex[mhelix], NOTSRCERASE);
				putimage(btemp5->x - 12, btemp5->y - 12, &tex[thelix], SRCINVERT);
				break;
			}
		}
	}
	for (btemp6; btemp6 != NULL; btemp6 = btemp6->next) {
		if (!btemp6->hit) {
			switch (btemp6->btype) {
			case hexadrone:
				putimage(btemp6->x - 12, btemp6->y - 12, &tex[mhexa], NOTSRCERASE);
				putimage(btemp6->x - 12, btemp6->y - 12, &tex[thexa], SRCINVERT);
				break;
			}
		}
	}
}