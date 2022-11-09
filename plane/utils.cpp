#include"plane.h"

double ddist(double a, double b, double c, double d) {
	return sqrt((a - b) * (a - b) + (c - d) * (c - d));
}

double dist(int a, int b, int c, int d) {
	return sqrt((a - b) * (a - b) + (c - d) * (c - d));
}

void FreeAll(USER** head) {
	USER* p = *head;
	if (*head == NULL)
		return;
	while (p->next != NULL)
	{
		USER* q = p->next;
		p->next = p->next->next;
		free(q);
	}
	free(p);
	*head = NULL;
}

void sortscore(USER* uhead) {
	USER* end = NULL;
	while ((uhead->next->next) != end) {
		USER* p = uhead;
		USER* q = uhead->next;
		while (q->next != end) {
			if ((q->highscore) < (q->next->highscore)) {
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			q = q->next;
			p = p->next;
		}
		end = q;
	}
}

void soundfx(int songname) {
	switch (songname) {
	case button:
		PlaySound(TEXT("./sfx/button.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case mute:
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		break;
	case plasmafire:
		PlaySound(TEXT("./sfx/plasma.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case laserfire:
		PlaySound(TEXT("./sfx/laser.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case bulletfire:
		PlaySound(TEXT("./sfx/machinegun.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case shotgunfire:
		PlaySound(TEXT("./sfx/shotgun.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case deathrayfire:
		PlaySound(TEXT("./sfx/deathray.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	}
}

