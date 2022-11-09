/*

#define WIDTH 480
#define HEIGHT 640
#define PLR_SIZE 10
#define BLT_VEL -2

int gametick = 0; //游戏刻

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
	//绘制飞机
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
	//清除飞机痕迹
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(plr.posx - PLR_SIZE, plr.posy - PLR_SIZE, plr.posx + PLR_SIZE, plr.posy + PLR_SIZE);
}

void updateBullet(proj* blt) {
	//处理子弹位置
	proj* temp = blt->next;
	proj* d = blt, * del;
	int flag = 0;
	for (temp; temp != NULL; temp = temp->next) {
		temp->y += temp->vel; //移动全部子弹
		if (temp->y < 0) {
			flag++;
		}
	}
	if (flag) {  //清除飞出屏幕的子弹
		while (d->next->y > 0) {
			d = d->next;
		}
		del = d->next;
		d->next = d->next->next;
		free(del);
	}
}

void drawBullet(proj* blt) {
	//绘制子弹
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
	//清除子弹痕迹
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
					if (gametick % 10 == 0) { //发射子弹
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
				if (gametick % 25 == 0) { //发射子弹
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
//	if (flag1) { //释放出屏幕飞机的内存
//		emy d = enemies;
//		while (d->next != NULL && d->next->y < HEIGHT) {
//			d = d->next;
//		}
//		del = d->next;
//		d->next = d->next->next;
//		free(del);
//	}
//	if (flag2) { //释放被摧毁飞机的内存
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
//	//释放被摧毁飞机的内存
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
		//printf("|   太 空 卫 士   |\n");
		//printf("+++++++++++++++++++\n");
#include<easyx.h>

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// 计算贴图的实际长宽
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;		// 处理超出右边界
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;	// 处理超出下边界
	if (x < 0) { src += -x;				iwidth -= -x;	x = 0; }				// 处理超出左边界
	if (y < 0) { src += src_width * -y;	iheight -= -y;	y = 0; }				// 处理超出上边界

	// 修正贴图起始位置
	dst += dst_width * y + x;

	// 实现透明贴图
	for (int iy = 0; iy < iheight; iy++)
	{
		for (int ix = 0; ix < iwidth; ix++)
		{
			int sa = ((src[ix] & 0xff000000) >> 24);
			int sr = ((src[ix] & 0xff0000) >> 16);	// 源值已经乘过了透明系数
			int sg = ((src[ix] & 0xff00) >> 8);		// 源值已经乘过了透明系数
			int sb = src[ix] & 0xff;				// 源值已经乘过了透明系数
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