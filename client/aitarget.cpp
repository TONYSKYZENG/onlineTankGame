#include "mainwindow.h"
void Guitank::attackTargetAi()//ai实现自动打击
{
	int adx, ady;
	adx = ady = 0;
	//  int arange=range*2/3;
	if (this->aiTarget->hp <= 0)
	{

		return;
	}
	int trange = range * 2 / 3;
	if (this->x() - aiTarget->x() > -trange && this->x() - aiTarget->x() < trange)// |this->x()-aiTarget->x()|<trange
	{
		if (this->y() - aiTarget->y() > -v && this->y() - aiTarget->y() < v)// |this->y() - aiTarget->y()|<v
		{
			if (this->x() < aiTarget->x())
			{
				setRotate(0);
			}
			else {
				setRotate(2);
			}
			fireShell();//开火
			setDest(this->x(), this->y());//设置坐标
			return;
		}

	}
	if (this->y() - aiTarget->y() > -trange && this->y() - aiTarget->y() < trange)// |this->x()-aiTarget->x()|<trange
	{
		if (this->x() - aiTarget->x() > -v && this->x() - aiTarget->x() < v)// |this->y() - aiTarget->y()|<v
		{
			if (this->y() < aiTarget->y())
			{
				setRotate(1);
			}
			else {
				setRotate(3);
			}
			fireShell();
			setDest(this->x(), this->y());
			return;
		}
	}
	switch (policy) {
	case 2:attackP3(); break;
	case 1:attackP2(); break;
	default:attackP1(); break;
	}
	//this->setRotate(aiTarget->angle);
  //  setDest(adx,ady);
}
void Guitank::attackP1()//attack tail
{
	int adx, ady;
	adx = ady = 0;
	int trange = range * 2 / 3;
	switch (aiTarget->angle) {
	case 0:adx = aiTarget->destX - trange + v; ady = aiTarget->destY; break;
	case 1:adx = aiTarget->destX; ady = aiTarget->destY - trange + v; break;
	case 2:adx = aiTarget->destX + trange - v; ady = aiTarget->destY; break;
	case 3:adx = aiTarget->destX; ady = aiTarget->destY + trange - v; break;
	}
	// this->setRotate(aiTarget->angle);
	setDest(adx, ady);
}

void Guitank::attackP2()
{
	int adx, ady;
	adx = ady = 0;
	int trange = range * 2 / 3;
	switch (aiTarget->angle) {
	case 1:adx = aiTarget->destX - trange + v; ady = aiTarget->destY; break;
	case 0:adx = aiTarget->destX; ady = aiTarget->destY - trange + v; break;
	case 3:adx = aiTarget->destX + trange - v; ady = aiTarget->destY; break;
	case 2:adx = aiTarget->destX; ady = aiTarget->destY + trange - v; break;
	}
	// this->setRotate(aiTarget->angle);
	setDest(adx, ady);
}

void Guitank::attackP3()
{
	int adx, ady;
	adx = ady = 0;
	int trange = range * 2 / 3;
	switch (aiTarget->angle) {
	case 3:adx = aiTarget->destX - trange + v; ady = aiTarget->destY; break;
	case 2:adx = aiTarget->destX; ady = aiTarget->destY - trange + v; break;
	case 1:adx = aiTarget->destX + trange - v; ady = aiTarget->destY; break;
	case 0:adx = aiTarget->destX; ady = aiTarget->destY + trange - v; break;
	}
	// this->setRotate(aiTarget->angle);
	setDest(adx, ady);
}
