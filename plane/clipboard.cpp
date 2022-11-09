/*

#define WIDTH 480
#define HEIGHT 640
#define PLR_SIZE 10
#define BLT_VEL -2

int gametick = 0; //��Ϸ��

typedef struct PLANE {
	int posx;
	int posy;
	int state; //0: move, 1: move+fire
} plane;

typedef struct PROJECTILE {
	int x;
	int y;
	int type;
	int vel; //velocity
	struct PROJECTILE* next;
} proj;

void drawPlane(plane plr) {
	//���Ʒɻ�
	if (!plr.state) {
		setfillcolor(WHITE);
		setlinecolor(WHITE);
	}
	else {
		setfillcolor(RED);
		setlinecolor(RED);
	}
	fillrectangle(plr.posx - PLR_SIZE, plr.posy - PLR_SIZE, plr.posx + PLR_SIZE, plr.posy + PLR_SIZE);
}

void clearPlane(plane plr) {
	//����ɻ��ۼ�
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(plr.posx - PLR_SIZE, plr.posy - PLR_SIZE, plr.posx + PLR_SIZE, plr.posy + PLR_SIZE);
}

void updateBullet(proj* blt) {
	//�����ӵ�λ��
	proj* temp = blt->next;
	proj* d = blt, * del;
	int flag = 0;
	for (temp; temp != NULL; temp = temp->next) {
		temp->y += temp->vel; //�ƶ�ȫ���ӵ�
		if (temp->y < 0) {
			flag++;
		}
	}
	if (flag) {  //����ɳ���Ļ���ӵ�
		while (d->next->y > 0) {
			d = d->next;
		}
		del = d->next;
		d->next = d->next->next;
		free(del);
	}
}

void drawBullet(proj* blt) {
	//�����ӵ�
	proj* temp = blt;
	for (temp; temp != NULL; temp = temp->next) {
		setlinestyle(PS_SOLID, 2);
		setfillcolor(YELLOW);
		setlinecolor(YELLOW);
		line(temp->x - 4, temp->y, temp->x - 4, temp->y - 6);
		line(temp->x + 4, temp->y, temp->x + 4, temp->y - 6);
	}
}

void clearBullet(proj* blt) {
	//����ӵ��ۼ�
	proj* temp = blt;
	for (temp; temp != NULL; temp = temp->next) {
		setlinestyle(PS_SOLID, 2);
		setfillcolor(BLACK);
		setlinecolor(BLACK);
		line(temp->x - 4, temp->y, temp->x - 4, temp->y - 6);
		line(temp->x + 4, temp->y, temp->x + 4, temp->y - 6);
	}
}

void game(plane* plr, proj* blt) {
	MOUSEMSG cur;
	while (1) {
		if (MouseHit()) {
			if (plr->state) {
				cur = GetMouseMsg();
				plr->posx = cur.x;
				plr->posy = cur.y;
				switch (cur.uMsg) {
				case WM_MOUSEMOVE:
					if (gametick % 10 == 0) { //�����ӵ�
						proj* newblt = (proj*)malloc(sizeof(proj));
						newblt->x = cur.x;
						newblt->y = cur.y;
						newblt->vel = BLT_VEL;

						newblt->next = blt->next;
						blt->next = newblt;
					}
					break;
				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
					plr->state = 0;
					break;
				}
			}
			else {
				cur = GetMouseMsg();
				switch (cur.uMsg) {
				case WM_MOUSEMOVE:
					plr->posx = cur.x;
					plr->posy = cur.y;
					break;
				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
					plr->state = 1;
					break;
				}
			}
		}
		else {
			if (plr->state) {
				if (gametick % 25 == 0) { //�����ӵ�
					proj* newblt = (proj*)malloc(sizeof(proj));
					newblt->x = cur.x;
					newblt->y = cur.y;
					newblt->vel = BLT_VEL;

					newblt->next = blt->next;
					blt->next = newblt;
				}
			}

		}
		BeginBatchDraw();
		drawPlane(*plr);
		drawBullet(blt);
		FlushBatchDraw();

		clearBullet(blt);
		clearPlane(*plr);

		Sleep(1);
		updateBullet(blt);
		gametick++;
	}
}

int main() {
	plane plr;
	plr.posx = WIDTH / 2;
	plr.posy = WIDTH / 2;
	plr.state = 0;
	proj* blt = (proj*)malloc(sizeof(proj));
	blt->next = NULL;

	initgraph(WIDTH, HEIGHT);
	game(&plr, blt);
}
*/

//temp = enemies->next;
//for (temp; temp != NULL; temp = temp->next) {
//	if (flag1) { //�ͷų���Ļ�ɻ����ڴ�
//		emy d = enemies;
//		while (d->next != NULL && d->next->y < HEIGHT) {
//			d = d->next;
//		}
//		del = d->next;
//		d->next = d->next->next;
//		free(del);
//	}
//	if (flag2) { //�ͷű��ݻٷɻ����ڴ�
//		emy d = enemies;
//		while (d->next != NULL && d->next->destroyed == 0) {
//			d = d->next;
//		}
//		del = d->next;
//		d->next = d->next->next;
//		free(del);
//	}
//}

//if (flag1) {
//	//�ͷű��ݻٷɻ����ڴ�
//	while (d->next != NULL && d->next->destroyed == 0) {
//		d = d->next;
//	}
//	if (d->next == NULL && d->destroyed == 1) {
//		printf("efreed-end\n");
//		free(d);
//	}
//	else {
//		printf("efreed-normal\n");
//		del = d->next;
//		d->next = d->next->next;
//		free(del);
//	}
//}


		//if (d1->next == NULL && d1->y > HEIGHT) {
		//	printf("bfreed-end\n");
		//	free(d1);
		//}

		//system("cls");
		//printf("+++++++++++++++++++\n");
		//printf("|   ̫ �� �� ʿ   |\n");
		//printf("+++++++++++++++++++\n");
#include<easyx.h>

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// ������ͼ��ʵ�ʳ���
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;		// �������ұ߽�
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;	// �������±߽�
	if (x < 0) { src += -x;				iwidth -= -x;	x = 0; }				// ��������߽�
	if (y < 0) { src += src_width * -y;	iheight -= -y;	y = 0; }				// �������ϱ߽�

	// ������ͼ��ʼλ��
	dst += dst_width * y + x;

	// ʵ��͸����ͼ
	for (int iy = 0; iy < iheight; iy++)
	{
		for (int ix = 0; ix < iwidth; ix++)
		{
			int sa = ((src[ix] & 0xff000000) >> 24);
			int sr = ((src[ix] & 0xff0000) >> 16);	// Դֵ�Ѿ��˹���͸��ϵ��
			int sg = ((src[ix] & 0xff00) >> 8);		// Դֵ�Ѿ��˹���͸��ϵ��
			int sb = src[ix] & 0xff;				// Դֵ�Ѿ��˹���͸��ϵ��
			int dr = ((dst[ix] & 0xff0000) >> 16);
			int dg = ((dst[ix] & 0xff00) >> 8);
			int db = dst[ix] & 0xff;

			dst[ix] = ((sr + dr * (255 - sa) / 255) << 16)
				| ((sg + dg * (255 - sa) / 255) << 8)
				| (sb + db * (255 - sa) / 255);
		}
		dst += dst_width;
		src += src_width;
	}
}