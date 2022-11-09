#include"plane.h"

#define LBSIZE 10

extern int hscore;

IMAGE lbbg;
IMAGE titlebg;

void writeUser(USER* uhead) {
	FILE* pf;
	fopen_s(&pf, "players.dat", "w");
	USER* utemp = uhead->next;
	for (; utemp != NULL; utemp = utemp->next) {
		fprintf(pf, "%s %s %d\n", utemp->name, utemp->pw, utemp->highscore);
	}
	fclose(pf);
}

void loadUser(USER* uhead) {
	int ucount = 0;
	FILE* pf;
	fopen_s(&pf, "players.dat", "r+");
	while (1) {
		if (feof(pf)) {
			fclose(pf);
			uhead->highscore = ucount;
			return;
		}
		USER* newuser = (USER*)malloc(sizeof(USER));
		if (fscanf_s(pf, "%s %s %d\n", newuser->name, 16, newuser->pw, 16, &newuser->highscore) == 3) {
			ucount++;
		}
		newuser->next = uhead->next;
		uhead->next = newuser;
	}
}

void leaderboards(USER* uhead) {
	int i = 0, height = 1;
	USER* utemp = uhead->next;
	char lbbuf[10][128];
	int lcap;
	uhead->highscore >= 10 ? lcap = 10 : lcap = uhead->highscore;
	settextstyle(30, 0, _T("Consolas"));
	for (i = 0; i < lcap; i++, utemp = utemp->next) {
		sprintf_s(lbbuf[i], "Name: %s     Score: %d", utemp->name, utemp->highscore);
	}
	putimage(0, 0, &lbbg);
	setbkmode(TRANSPARENT);
	for (i = 0; i < 10; i++) {
		switch (i) {
		case 0:
			settextcolor(YELLOW);
			break;
		case 1:
		case 2:
			settextcolor(WHITE);
			break;
		default:
			settextcolor(LIGHTGRAY);
			break;
		}
		outtextxy(120, i * 30 + 100, lbbuf[i]);
	}
}

USER* auth(USER* uhead) {
	USER* utemp = uhead->next;
	char namebuf[32];
	bool pwflag = 0;
	if (!InputBox(namebuf, 32, "Please input your name", "Auth system", "username", 0, 0, false)) {
		return NULL;
	}//取消用户名输入
	for (utemp; utemp != NULL; utemp = utemp->next) {
		if (!strcmp(namebuf, utemp->name)) {
			char pwbuf[32];
			do {
				if (!InputBox(pwbuf, 32, "Please input your name", "Auth system - Found Player", "password", 0, 0, false)) {
					return NULL;
				}//取消密码输入
			} while (strcmp(pwbuf, utemp->pw));
			return utemp;
		}
	}
	USER* newuser = (USER*)malloc(sizeof(USER));
	char pwbuf[32];
	strcpy_s(newuser->name, namebuf);
	if (!InputBox(pwbuf, 32, "Please input your password", "Auth system - New Player", "password", 0, 0, false)) {
		return NULL;
	}//取消密码输入
	strcpy_s(newuser->pw, pwbuf);
	newuser->highscore = 0;

	newuser->next = uhead->next;
	uhead->next = newuser;

	writeUser(uhead);
	return newuser;
}

bool startup(USER* uhead) {

	while (1) {
		putimage(0, 0, &titlebg);
		MOUSEMSG cur;
		cur = GetMouseMsg();
		if (cur.x >= 50 && cur.x <= 300 && cur.y >= 300 && cur.y <= 450) {
			if (cur.uMsg == WM_LBUTTONDOWN) {
				soundfx(button);
				USER* curuser = auth(uhead);

				if (curuser != NULL) {
					curuser->curlvl.highscore = curuser->highscore;
					hscore = curuser->highscore;

					if (!game(curuser->curlvl)) {

						curuser->highscore = hscore;
						writeUser(uhead);
						return -1;
					}
				}
				else {
					return 0;
				}
			}	
		}
		if (cur.x >= 50 && cur.x <= 300 && cur.y > 450 && cur.y <= 600) {
			if (cur.uMsg == WM_LBUTTONDOWN) {
				soundfx(button);
				Sleep(10);
				exit(1);
			}
		}
		if (cur.x >= 318 && cur.x <= 398 && cur.y >= 339 && cur.y <= 419) {
			leaderboards(uhead);
		}
		FlushBatchDraw();
	}
}

int main() {
	initgraph(WWIDTH, HEIGHT);	
	soundfx(mute);

	//mciSendString("open bkmusic.mp3 alias bgm", NULL, 0, NULL);
	//mciSendString("play bgm repeat", NULL, 0, NULL);

	BeginBatchDraw();
	while (1) {
		USER* uhead = (USER*)malloc(sizeof(USER));
		uhead->next = NULL;
		loadUser(uhead);
		sortscore(uhead);

		loadimage(&titlebg, "./res/titlebg_t.png");
		loadimage(&lbbg, "./res/lbbg_t.png");

		FlushBatchDraw();
		startup(uhead);

		FreeAll(&uhead);
	}
}
