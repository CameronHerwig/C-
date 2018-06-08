#include <windows.h>
#include <time.h>
#include "SetOfDice.h"
#include <math.h>

#define PI 3.14159265

using namespace std;

//http://www.winprog.org/tutorial/simple_window.html

const wchar_t g_szClassName[] = L"myWindowClass";

inline std::wstring convert(const std::string& as)
{
	// deal with trivial case of empty string
	if (as.empty())    return std::wstring();

	// determine required length of new string
	size_t reqLength = ::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0);

	// construct new string of required length
	std::wstring ret(reqLength, L'\0');

	// convert old string to new string
	::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());

	// return new string ( compiler should optimize this away )
	return ret;
}

void addAngle(float &angle)
{
	int an = (int)angle;
	an += 1;
	angle = (float)an;
}

void resetAngle(float &angle)
{
	angle = 0.0f;
}

//Credit To Tom Fernandez
string intToString(int x)
{
	string result;
	char temp[256];
	_itoa_s(x, temp, 255, 10);
	result = temp;
	return result;
}

void circlePos1(HDC hDC, double cx, double cy, double r)
{
	cx = cx - (r / 2.0);
	cy = cy - (r / 2.0);
	Ellipse(hDC, (int)(cx - (r / 5.0)), (int)(cy - (r / 5.0)), (int)(cx + (r / 5.0)), (int)(cy + (r / 5.0)));
}

void circlePos2(HDC hDC, double cx, double cy, double r)
{
	cx = cx - (r / 2.0);
	Ellipse(hDC, (int)(cx - (r / 5.0)), (int)(cy - (r / 5.0)), (int)(cx + (r / 5.0)), (int)(cy + (r / 5.0)));
}

void circlePos3(HDC hDC, double cx, double cy, double r)
{
	cx = cx - (r / 2.0);
	cy = cy + (r / 2.0);
	Ellipse(hDC, (int)(cx - (r / 5.0)), (int)(cy - (r / 5.0)), (int)(cx + (r / 5.0)), (int)(cy + (r / 5.0)));
}

void circlePos4(HDC hDC, double cx, double cy, double r)
{
	Ellipse(hDC, (int)(cx - (r / 5.0)), (int)(cy - (r / 5.0)), (int)(cx + (r / 5.0)), (int)(cy + (r / 5.0)));
}

void circlePos5(HDC hDC, double cx, double cy, double r)
{
	cx = cx + (r / 2.0);
	cy = cy - (r / 2.0);
	Ellipse(hDC, (int)(cx - (r / 5.0)), (int)(cy - (r / 5.0)), (int)(cx + (r / 5.0)), (int)(cy + (r / 5.0)));
}

void circlePos6(HDC hDC, double cx, double cy, double r)
{
	cx = cx + (r / 2.0);
	Ellipse(hDC, (int)(cx - (r / 5.0)), (int)(cy - (r / 5.0)), (int)(cx + (r / 5.0)), (int)(cy + (r / 5.0)));
}

void circlePos7(HDC hDC, double cx, double cy, double r)
{
	cx = cx + (r / 2.0);
	cy = cy + (r / 2.0);
	Ellipse(hDC, (int)(cx - (r / 5.0)), (int)(cy - (r / 5.0)), (int)(cx + (r / 5.0)), (int)(cy + (r / 5.0)));
}

void square(HDC hdc, double cx, double cy, double size)
{
	Rectangle(hdc, (int)(cx - size), (int)(cy - size), (int)(cx + size), (int)(cy + size));
}

POINT rotate_pointCounter(float cx, float cy, float rads, POINT &p)
{
	float s = sin((rads*PI) / 180);
	float c = cos((rads*PI) / 180);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c + p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}

POINT rotate_point(float cx, float cy, float rads, POINT &p)
{
	float s = sin((rads*PI) / 180);
	float c = cos((rads*PI) / 180);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}

void drawDie1(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1)
{
	double cx = dx;
	double cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	HPEN hThinRedPen;
	HBRUSH hBlueBrush;
	HBRUSH hOtherBrush;

	hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));
	hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));
	hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));

	SelectObject(hdc, hBlueBrush);
	SelectObject(hdc, hThinRedPen);

	square(hdc, cx, cy, r);

	switch (die1)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

void rotateDie1(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
{
	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;

	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	SelectObject(hdc, whitepen);
	SelectObject(hdc, white);

	int cx = dx;
	int cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	int dumbx = (int)cx - (dsize / 4.0);
	int dumberx = (int)cx + (dsize / 4.0);

	int dumby = (int)cy - (dsize / 4.0);
	int dumbery = (int)cy + (dsize / 4.0);

	square(hdc, cx, cy, r);

	SelectObject(hdc, hThinRedPen);
	SelectObject(hdc, hBlueBrush);

	POINT point[4];

	point[0].x = dumbx;
	point[0].y = dumby;
	point[1].x = dumbx;
	point[1].y = dumbery;
	point[2].x = dumberx;
	point[2].y = dumbery;
	point[3].x = dumberx;
	point[3].y = dumby;

	rotate_point((float)cx, (float)cy, angle, point[0]);
	rotate_point((float)cx, (float)cy, angle, point[1]);
	rotate_point((float)cx, (float)cy, angle, point[2]);
	rotate_point((float)cx, (float)cy, angle, point[3]);

	Polygon(hdc, point, 4);

	switch (die1)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(whitepen);
	DeleteObject(white);
	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

//void rotateCounterDie1(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
//{
//	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
//	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
//	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;
//
//	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
//	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
//
//	SelectObject(hdc, whitepen);
//	SelectObject(hdc, white);
//
//	int cx = dx;
//	int cy = dy - (dsize / 4.0);
//	double r = dsize / 4.0;
//
//	int dumbx = (int)cx - (dsize / 4.0);
//	int dumberx = (int)cx + (dsize / 4.0);
//
//	int dumby = (int)cy - (dsize / 4.0);
//	int dumbery = (int)cy + (dsize / 4.0);
//
//	square(hdc, cx, cy, (int)dsize/3.5);
//
//	SelectObject(hdc, hThinRedPen);
//	SelectObject(hdc, hBlueBrush);
//
//	POINT point[4];
//
//	point[0].x = dumbx;
//	point[0].y = dumby;
//	point[1].x = dumbx;
//	point[1].y = dumbery;
//	point[2].x = dumberx;
//	point[2].y = dumbery;
//	point[3].x = dumberx;
//	point[3].y = dumby;
//
//	rotate_pointCounter((float)cx, (float)cy, angle, point[0]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[1]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[2]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[3]);
//
//	Polygon(hdc, point, 4);
//
//	switch (die1)
//	{
//	case 1:
//		SelectObject(hdc, hOtherBrush);
//		circlePos4(hdc, cx, cy, r);
//		break;
//	case 2:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 3:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 4:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 5:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 6:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos2(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos6(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	}
//
//	DeleteObject(whitepen);
//	DeleteObject(white);
//	DeleteObject(hThinRedPen);
//	DeleteObject(hBlueBrush);
//	DeleteObject(hOtherBrush);
//}

void drawDie2(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die2)
{
	double cx = dx;
	double cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	HPEN hThinRedPen;
	HBRUSH hBlueBrush;
	HBRUSH hOtherBrush;

	hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));
	hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));
	hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));

	SelectObject(hdc, hBlueBrush);
	SelectObject(hdc, hThinRedPen);

	square(hdc, cx, cy, r);

	switch (die2)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

void rotateDie2(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
{
	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;

	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	SelectObject(hdc, whitepen);
	SelectObject(hdc, white);

	int cx = dx;
	int cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	int dumbx = (int)cx - (dsize / 4.0);
	int dumberx = (int)cx + (dsize / 4.0);

	int dumby = (int)cy - (dsize / 4.0);
	int dumbery = (int)cy + (dsize / 4.0);

	square(hdc, cx, cy, r);

	SelectObject(hdc, hThinRedPen);
	SelectObject(hdc, hBlueBrush);

	POINT point[4];

	point[0].x = dumbx;
	point[0].y = dumby;
	point[1].x = dumbx;
	point[1].y = dumbery;
	point[2].x = dumberx;
	point[2].y = dumbery;
	point[3].x = dumberx;
	point[3].y = dumby;

	rotate_point((float)cx, (float)cy, angle, point[0]);
	rotate_point((float)cx, (float)cy, angle, point[1]);
	rotate_point((float)cx, (float)cy, angle, point[2]);
	rotate_point((float)cx, (float)cy, angle, point[3]);

	Polygon(hdc, point, 4);

	switch (die1)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(whitepen);
	DeleteObject(white);
	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

//void rotateCounterDie2(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
//{
//	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
//	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
//	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;
//
//	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
//	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
//
//	SelectObject(hdc, whitepen);
//	SelectObject(hdc, white);
//
//	int cx = dx;
//	int cy = dy - (dsize / 4.0);
//	double r = dsize / 4.0;
//
//	int dumbx = (int)cx - (dsize / 4.0);
//	int dumberx = (int)cx + (dsize / 4.0);
//
//	int dumby = (int)cy - (dsize / 4.0);
//	int dumbery = (int)cy + (dsize / 4.0);
//
//	square(hdc, cx, cy, (int)dsize / 3.5);
//
//	SelectObject(hdc, hThinRedPen);
//	SelectObject(hdc, hBlueBrush);
//
//	POINT point[4];
//
//	point[0].x = dumbx;
//	point[0].y = dumby;
//	point[1].x = dumbx;
//	point[1].y = dumbery;
//	point[2].x = dumberx;
//	point[2].y = dumbery;
//	point[3].x = dumberx;
//	point[3].y = dumby;
//
//	rotate_pointCounter((float)cx, (float)cy, angle, point[0]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[1]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[2]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[3]);
//
//	Polygon(hdc, point, 4);
//
//	switch (die1)
//	{
//	case 1:
//		SelectObject(hdc, hOtherBrush);
//		circlePos4(hdc, cx, cy, r);
//		break;
//	case 2:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 3:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 4:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 5:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 6:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos2(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos6(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	}
//
//	DeleteObject(whitepen);
//	DeleteObject(white);
//	DeleteObject(hThinRedPen);
//	DeleteObject(hBlueBrush);
//	DeleteObject(hOtherBrush);
//}

void drawDie3(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die3)
{
	double cx = dx;
	double cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	HPEN hThinRedPen;
	HBRUSH hBlueBrush;
	HBRUSH hOtherBrush;

	hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));
	hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));
	hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));

	SelectObject(hdc, hBlueBrush);
	SelectObject(hdc, hThinRedPen);

	square(hdc, cx, cy, r);

	switch (die3)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

void rotateDie3(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
{
	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;

	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	SelectObject(hdc, whitepen);
	SelectObject(hdc, white);

	int cx = dx;
	int cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	int dumbx = (int)cx - (dsize / 4.0);
	int dumberx = (int)cx + (dsize / 4.0);

	int dumby = (int)cy - (dsize / 4.0);
	int dumbery = (int)cy + (dsize / 4.0);

	square(hdc, cx, cy, r);

	SelectObject(hdc, hThinRedPen);
	SelectObject(hdc, hBlueBrush);

	POINT point[4];

	point[0].x = dumbx;
	point[0].y = dumby;
	point[1].x = dumbx;
	point[1].y = dumbery;
	point[2].x = dumberx;
	point[2].y = dumbery;
	point[3].x = dumberx;
	point[3].y = dumby;

	rotate_point((float)cx, (float)cy, angle, point[0]);
	rotate_point((float)cx, (float)cy, angle, point[1]);
	rotate_point((float)cx, (float)cy, angle, point[2]);
	rotate_point((float)cx, (float)cy, angle, point[3]);

	Polygon(hdc, point, 4);

	switch (die1)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(whitepen);
	DeleteObject(white);
	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

//void rotateCounterDie3(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
//{
//	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
//	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
//	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;
//
//	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
//	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
//
//	SelectObject(hdc, whitepen);
//	SelectObject(hdc, white);
//
//	int cx = dx;
//	int cy = dy - (dsize / 4.0);
//	double r = dsize / 4.0;
//
//	int dumbx = (int)cx - (dsize / 4.0);
//	int dumberx = (int)cx + (dsize / 4.0);
//
//	int dumby = (int)cy - (dsize / 4.0);
//	int dumbery = (int)cy + (dsize / 4.0);
//
//	square(hdc, cx, cy, (int)dsize / 3.5);
//
//	SelectObject(hdc, hThinRedPen);
//	SelectObject(hdc, hBlueBrush);
//
//	POINT point[4];
//
//	point[0].x = dumbx;
//	point[0].y = dumby;
//	point[1].x = dumbx;
//	point[1].y = dumbery;
//	point[2].x = dumberx;
//	point[2].y = dumbery;
//	point[3].x = dumberx;
//	point[3].y = dumby;
//
//	rotate_pointCounter((float)cx, (float)cy, angle, point[0]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[1]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[2]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[3]);
//
//	Polygon(hdc, point, 4);
//
//	switch (die1)
//	{
//	case 1:
//		SelectObject(hdc, hOtherBrush);
//		circlePos4(hdc, cx, cy, r);
//		break;
//	case 2:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 3:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 4:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 5:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 6:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos2(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos6(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	}
//
//	DeleteObject(whitepen);
//	DeleteObject(white);
//	DeleteObject(hThinRedPen);
//	DeleteObject(hBlueBrush);
//	DeleteObject(hOtherBrush);
//}

void drawDie4(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die4)
{
	double cx = dx;
	double cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	HPEN hThinRedPen;
	HBRUSH hBlueBrush;
	HBRUSH hOtherBrush;

	hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));
	hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));
	hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));

	SelectObject(hdc, hBlueBrush);
	SelectObject(hdc, hThinRedPen);

	square(hdc, cx, cy, r);

	switch (die4)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

void rotateDie4(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
{
	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;

	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	SelectObject(hdc, whitepen);
	SelectObject(hdc, white);

	int cx = dx;
	int cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	int dumbx = (int)cx - (dsize / 4.0);
	int dumberx = (int)cx + (dsize / 4.0);

	int dumby = (int)cy - (dsize / 4.0);
	int dumbery = (int)cy + (dsize / 4.0);

	square(hdc, cx, cy, r);

	SelectObject(hdc, hThinRedPen);
	SelectObject(hdc, hBlueBrush);

	POINT point[4];

	point[0].x = dumbx;
	point[0].y = dumby;
	point[1].x = dumbx;
	point[1].y = dumbery;
	point[2].x = dumberx;
	point[2].y = dumbery;
	point[3].x = dumberx;
	point[3].y = dumby;

	rotate_point((float)cx, (float)cy, angle, point[0]);
	rotate_point((float)cx, (float)cy, angle, point[1]);
	rotate_point((float)cx, (float)cy, angle, point[2]);
	rotate_point((float)cx, (float)cy, angle, point[3]);

	Polygon(hdc, point, 4);

	switch (die1)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(whitepen);
	DeleteObject(white);
	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

//void rotateCounterDie4(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
//{
//	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
//	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
//	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;
//
//	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
//	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
//
//	SelectObject(hdc, whitepen);
//	SelectObject(hdc, white);
//
//	int cx = dx;
//	int cy = dy - (dsize / 4.0);
//	double r = dsize / 4.0;
//
//	int dumbx = (int)cx - (dsize / 4.0);
//	int dumberx = (int)cx + (dsize / 4.0);
//
//	int dumby = (int)cy - (dsize / 4.0);
//	int dumbery = (int)cy + (dsize / 4.0);
//
//	square(hdc, cx, cy, (int)dsize / 3.5);
//
//	SelectObject(hdc, hThinRedPen);
//	SelectObject(hdc, hBlueBrush);
//
//	POINT point[4];
//
//	point[0].x = dumbx;
//	point[0].y = dumby;
//	point[1].x = dumbx;
//	point[1].y = dumbery;
//	point[2].x = dumberx;
//	point[2].y = dumbery;
//	point[3].x = dumberx;
//	point[3].y = dumby;
//
//	rotate_pointCounter((float)cx, (float)cy, angle, point[0]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[1]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[2]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[3]);
//
//	Polygon(hdc, point, 4);
//
//	switch (die1)
//	{
//	case 1:
//		SelectObject(hdc, hOtherBrush);
//		circlePos4(hdc, cx, cy, r);
//		break;
//	case 2:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 3:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 4:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 5:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 6:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos2(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos6(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	}
//
//	DeleteObject(whitepen);
//	DeleteObject(white);
//	DeleteObject(hThinRedPen);
//	DeleteObject(hBlueBrush);
//	DeleteObject(hOtherBrush);
//}

void drawDie5(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die5)
{
	double cx = dx;
	double cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	HPEN hThinRedPen;
	HBRUSH hBlueBrush;
	HBRUSH hOtherBrush;

	hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));
	hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));
	hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));

	SelectObject(hdc, hBlueBrush);
	SelectObject(hdc, hThinRedPen);

	square(hdc, cx, cy, r);

	switch (die5)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

void rotateDie5(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
{
	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;

	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	SelectObject(hdc, whitepen);
	SelectObject(hdc, white);

	int cx = dx;
	int cy = dy - (dsize / 4.0);
	double r = dsize / 4.0;

	int dumbx = (int)cx - (dsize / 4.0);
	int dumberx = (int)cx + (dsize / 4.0);

	int dumby = (int)cy - (dsize / 4.0);
	int dumbery = (int)cy + (dsize / 4.0);

	square(hdc, cx, cy, r);

	SelectObject(hdc, hThinRedPen);
	SelectObject(hdc, hBlueBrush);

	POINT point[4];

	point[0].x = dumbx;
	point[0].y = dumby;
	point[1].x = dumbx;
	point[1].y = dumbery;
	point[2].x = dumberx;
	point[2].y = dumbery;
	point[3].x = dumberx;
	point[3].y = dumby;

	rotate_point((float)cx, (float)cy, angle, point[0]);
	rotate_point((float)cx, (float)cy, angle, point[1]);
	rotate_point((float)cx, (float)cy, angle, point[2]);
	rotate_point((float)cx, (float)cy, angle, point[3]);

	Polygon(hdc, point, 4);

	switch (die1)
	{
	case 1:
		SelectObject(hdc, hOtherBrush);
		circlePos4(hdc, cx, cy, r);
		break;
	case 2:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 3:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 4:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 5:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos4(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	case 6:
		SelectObject(hdc, hOtherBrush);
		circlePos1(hdc, cx, cy, r);
		circlePos2(hdc, cx, cy, r);
		circlePos3(hdc, cx, cy, r);
		circlePos5(hdc, cx, cy, r);
		circlePos6(hdc, cx, cy, r);
		circlePos7(hdc, cx, cy, r);
		break;
	}

	DeleteObject(whitepen);
	DeleteObject(white);
	DeleteObject(hThinRedPen);
	DeleteObject(hBlueBrush);
	DeleteObject(hOtherBrush);
}

//void rotateCounterDie5(HDC hdc, double dx, double dy, double dsize, int sqred, int sqgreen, int sqblue, int sqred2, int sqgreen2, int sqblue2, int cred, int cgreen, int cblue, int die1, float angle)
//{
//	HPEN hThinRedPen = CreatePen(PS_SOLID, 1, RGB(sqred2, sqgreen2, sqblue2));;
//	HBRUSH hBlueBrush = CreateSolidBrush(RGB(sqred, sqgreen, sqblue));;
//	HBRUSH hOtherBrush = CreateSolidBrush(RGB(cred, cgreen, cblue));;
//
//	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
//	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
//
//	SelectObject(hdc, whitepen);
//	SelectObject(hdc, white);
//
//	int cx = dx;
//	int cy = dy - (dsize / 4.0);
//	double r = dsize / 4.0;
//
//	int dumbx = (int)cx - (dsize / 4.0);
//	int dumberx = (int)cx + (dsize / 4.0);
//
//	int dumby = (int)cy - (dsize / 4.0);
//	int dumbery = (int)cy + (dsize / 4.0);
//
//	square(hdc, cx, cy, (int)dsize / 3.5);
//
//	SelectObject(hdc, hThinRedPen);
//	SelectObject(hdc, hBlueBrush);
//
//	POINT point[4];
//
//	point[0].x = dumbx;
//	point[0].y = dumby;
//	point[1].x = dumbx;
//	point[1].y = dumbery;
//	point[2].x = dumberx;
//	point[2].y = dumbery;
//	point[3].x = dumberx;
//	point[3].y = dumby;
//
//	rotate_pointCounter((float)cx, (float)cy, angle, point[0]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[1]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[2]);
//	rotate_pointCounter((float)cx, (float)cy, angle, point[3]);
//
//	Polygon(hdc, point, 4);
//
//	switch (die1)
//	{
//	case 1:
//		SelectObject(hdc, hOtherBrush);
//		circlePos4(hdc, cx, cy, r);
//		break;
//	case 2:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 3:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 4:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 5:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos4(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	case 6:
//		SelectObject(hdc, hOtherBrush);
//		circlePos1(hdc, cx, cy, r);
//		circlePos2(hdc, cx, cy, r);
//		circlePos3(hdc, cx, cy, r);
//		circlePos5(hdc, cx, cy, r);
//		circlePos6(hdc, cx, cy, r);
//		circlePos7(hdc, cx, cy, r);
//		break;
//	}
//
//	DeleteObject(whitepen);
//	DeleteObject(white);
//	DeleteObject(hThinRedPen);
//	DeleteObject(hBlueBrush);
//	DeleteObject(hOtherBrush);
//}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	srand((unsigned int)time(NULL));

	static int diesize = 150;

	static bool rotation = false;
	static bool thirddimension = false;

	static int d1x = 150;
	static int d1y = 150;

	static int d2x = 400;
	static int d2y = 150;

	static int d3x = 650;
	static int d3y = 150;

	static int d4x = 275;
	static int d4y = 300;

	static int d5x = 525;
	static int d5y = 300;

	static int d1sqred = 0;
	static int d1sqgreen = 0;
	static int d1sqblue = 155;
	static int d1cred = 155;
	static int d1cgreen = 0;
	static int d1cblue = 0;
	static int d1sqred2 = 155;
	static int d1sqgreen2 = 0;
	static int d1sqblue2 = 0;

	static int d2sqred = d1sqred;
	static int d2sqgreen = d1sqgreen;
	static int d2sqblue = d1sqblue;
	static int d2cred = d1cred;
	static int d2cgreen = d1cgreen;
	static int d2cblue = d1cblue;
	static int d2sqred2 = d1sqred2;
	static int d2sqgreen2 = d1sqgreen2;
	static int d2sqblue2 = d1sqblue2;

	static int d3sqred = d1sqred;
	static int d3sqgreen = d1sqgreen;
	static int d3sqblue = d1sqblue;
	static int d3cred = d1cred;
	static int d3cgreen = d1cgreen;
	static int d3cblue = d1cblue;
	static int d3sqred2 = d1sqred2;
	static int d3sqgreen2 = d1sqgreen2;
	static int d3sqblue2 = d1sqblue2;

	static int d4sqred = d1sqred;
	static int d4sqgreen = d1sqgreen;
	static int d4sqblue = d1sqblue;
	static int d4cred = d1cred;
	static int d4cgreen = d1cgreen;
	static int d4cblue = d1cblue;
	static int d4sqred2 = d1sqred2;
	static int d4sqgreen2 = d1sqgreen2;
	static int d4sqblue2 = d1sqblue2;

	static int d5sqred = d1sqred;
	static int d5sqgreen = d1sqgreen;
	static int d5sqblue = d1sqblue;
	static int d5cred = d1cred;
	static int d5cgreen = d1cgreen;
	static int d5cblue = d1cblue;
	static int d5sqred2 = d1sqred2;
	static int d5sqgreen2 = d1sqgreen2;
	static int d5sqblue2 = d1sqblue2;

	static float angle = 0.0f;

	string dvalues = "Number of Even Die:";

	PAINTSTRUCT ps;
	HDC hdc;

	HFONT hFont;

	static SetOfDice setofdice;
	setofdice.roll();
	static int die1 = setofdice.getDie1Value();
	static int die2 = setofdice.getDie2Value();
	static int die3 = setofdice.getDie3Value();
	static int die4 = setofdice.getDie4Value();
	static int die5 = setofdice.getDie5Value();

	vector<int> val;
	val.push_back(die1);
	val.push_back(die2);
	val.push_back(die3);
	val.push_back(die4);
	val.push_back(die5);

	int numofeven = 0;
	for (int i = 0; i < val.size(); i++)
	{
		if ((val[i] % 2) == 0)
		{
			numofeven++;
		}
	}

	dvalues += intToString(numofeven);

	switch (msg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		if (rotation)
		{
			rotateDie1(hdc, d1x, d1y, diesize, d1sqred, d1sqgreen, d1sqblue, d1sqred2, d1sqgreen2, d1sqblue2, d1cred, d1cgreen, d1cblue, die1, angle);
			rotateDie2(hdc, d2x, d2y, diesize, d2sqred, d2sqgreen, d2sqblue, d2sqred2, d2sqgreen2, d2sqblue2, d2cred, d2cgreen, d2cblue, die2, angle);
			rotateDie3(hdc, d3x, d3y, diesize, d3sqred, d3sqgreen, d3sqblue, d3sqred2, d3sqgreen2, d3sqblue2, d3cred, d3cgreen, d3cblue, die3, angle);
			rotateDie4(hdc, d4x, d4y, diesize, d4sqred, d4sqgreen, d4sqblue, d4sqred2, d4sqgreen2, d4sqblue2, d4cred, d4cgreen, d4cblue, die4, angle);
			rotateDie5(hdc, d5x, d5y, diesize, d5sqred, d5sqgreen, d5sqblue, d5sqred2, d5sqgreen2, d5sqblue2, d5cred, d5cgreen, d5cblue, die5, angle);
		}
		else
		{
			drawDie1(hdc, d1x, d1y, diesize, d1sqred, d1sqgreen, d1sqblue, d1sqred2, d1sqgreen2, d1sqblue2, d1cred, d1cgreen, d1cblue, die1);
			drawDie2(hdc, d2x, d2y, diesize, d2sqred, d2sqgreen, d2sqblue, d2sqred2, d2sqgreen2, d2sqblue2, d2cred, d2cgreen, d2cblue, die2);
			drawDie3(hdc, d3x, d3y, diesize, d3sqred, d3sqgreen, d3sqblue, d3sqred2, d3sqgreen2, d3sqblue2, d3cred, d3cgreen, d3cblue, die3);
			drawDie4(hdc, d4x, d4y, diesize, d4sqred, d4sqgreen, d4sqblue, d4sqred2, d4sqgreen2, d4sqblue2, d4cred, d4cgreen, d4cblue, die4);
			drawDie5(hdc, d5x, d5y, diesize, d5sqred, d5sqgreen, d5sqblue, d5sqred2, d5sqgreen2, d5sqblue2, d5cred, d5cgreen, d5cblue, die5);
		}
		/*if (thirddimension)
		{
		rotateCounterDie1(hdc, d1x, d1y, diesize, d1sqred, d1sqgreen, d1sqblue, d1sqred2, d1sqgreen2, d1sqblue2, d1cred, d1cgreen, d1cblue, die1, angle);
		rotateCounterDie2(hdc, d2x, d2y, diesize, d2sqred, d2sqgreen, d2sqblue, d2sqred2, d2sqgreen2, d2sqblue2, d2cred, d2cgreen, d2cblue, die2, angle);
		rotateCounterDie3(hdc, d3x, d3y, diesize, d3sqred, d3sqgreen, d3sqblue, d3sqred2, d3sqgreen2, d3sqblue2, d3cred, d3cgreen, d3cblue, die3, angle);
		rotateCounterDie4(hdc, d4x, d4y, diesize, d4sqred, d4sqgreen, d4sqblue, d4sqred2, d4sqgreen2, d4sqblue2, d4cred, d4cgreen, d4cblue, die4, angle);
		rotateCounterDie5(hdc, d5x, d5y, diesize, d5sqred, d5sqgreen, d5sqblue, d5sqred2, d5sqgreen2, d5sqblue2, d5cred, d5cgreen, d5cblue, die5, angle);
		}*/

		hFont = CreateFont(32, 0, 0, 0, 0, FALSE, 1, 0, 0, 0, 0, 0, 0, L"Arial");

		RECT rect;
		rect.left = 300;
		rect.top = 500;
		rect.right = 500;
		rect.bottom = 700;

		wstring dvalue = convert(dvalues);

		std::wstring stemp = std::wstring(dvalue.begin(), dvalue.end());
		LPCWSTR sw = stemp.c_str();

		DrawText(hdc, sw, -1, &rect, DT_WORDBREAK | DT_CENTER);

		DeleteObject(hFont);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_CHAR:
	{
		if (wParam == 'c')
		{
			d1sqred = rand() % 256;
			d1sqgreen = rand() % 256;
			d1sqblue = rand() % 256;
			d1cred = rand() % 256;
			d1cgreen = rand() % 256;
			d1cblue = rand() % 256;
			d1sqred2 = rand() % 256;
			d1sqgreen2 = rand() % 256;
			d1sqblue2 = rand() % 256;

			d2sqred = rand() % 256;
			d2sqgreen = rand() % 256;
			d2sqblue = rand() % 256;
			d2cred = rand() % 256;
			d2cgreen = rand() % 256;
			d2cblue = rand() % 256;
			d2sqred2 = rand() % 256;
			d2sqgreen2 = rand() % 256;
			d2sqblue2 = rand() % 256;

			d3sqred = rand() % 256;
			d3sqgreen = rand() % 256;
			d3sqblue = rand() % 256;
			d3cred = rand() % 256;
			d3cgreen = rand() % 256;
			d3cblue = rand() % 256;
			d3sqred2 = rand() % 256;
			d3sqgreen2 = rand() % 256;
			d3sqblue2 = rand() % 256;

			d4sqred = rand() % 256;
			d4sqgreen = rand() % 256;
			d4sqblue = rand() % 256;
			d4cred = rand() % 256;
			d4cgreen = rand() % 256;
			d4cblue = rand() % 256;
			d4sqred2 = rand() % 256;
			d4sqgreen2 = rand() % 256;
			d4sqblue2 = rand() % 256;

			d5sqred = rand() % 256;
			d5sqgreen = rand() % 256;
			d5sqblue = rand() % 256;
			d5cred = rand() % 256;
			d5cgreen = rand() % 256;
			d5cblue = rand() % 256;
			d5sqred2 = rand() % 256;
			d5sqgreen2 = rand() % 256;
			d5sqblue2 = rand() % 256;
		}
		else if (wParam == 'r')
		{
			rotation = true;
			//thirddimension = false;
			addAngle(angle);
		}
		/*else if (wParam == 't')
		{
		thirddimension = true;
		rotation = false;
		addAngle(angle);
		}*/
		InvalidateRect(hwnd, NULL, true);
		break;
	}
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{
			d1x += 3;
			d2x += 3;
			d3x += 3;
			d4x += 3;
			d5x += 3;
		}
		else if (wParam == VK_LEFT)
		{
			d1x -= 3;
			d2x -= 3;
			d3x -= 3;
			d4x -= 3;
			d5x -= 3;
		}
		else if (wParam == VK_UP)
		{
			d1y -= 3;
			d2y -= 3;
			d3y -= 3;
			d4y -= 3;
			d5y -= 3;
		}
		else if (wParam == VK_DOWN)
		{
			d1y += 3;
			d2y += 3;
			d3y += 3;
			d4y += 3;
			d5y += 3;
		}
		else if (wParam == VK_PRIOR)
		{
			diesize *= 1.05;
		}
		else if (wParam == VK_NEXT)
		{
			diesize /= 1.05;
		}
		else if (wParam == VK_SPACE)
		{
			setofdice.roll();
			die1 = setofdice.getDie1Value();
			die2 = setofdice.getDie2Value();
			die3 = setofdice.getDie3Value();
			die4 = setofdice.getDie4Value();
			die5 = setofdice.getDie5Value();

			vector<int> val;
			val.push_back(die1);
			val.push_back(die2);
			val.push_back(die3);
			val.push_back(die4);
			val.push_back(die5);

			int numofeven = 0;
			for (int i = 0; i < val.size(); i++)
			{
				if ((val[i] % 2) == 0)
				{
					numofeven++;
				}
			}
			dvalues += intToString(numofeven);

			rotation = false;
			//thirddimension = false;
			resetAngle(angle);
		}
		InvalidateRect(hwnd, NULL, true);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"Cameron Herwig",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 750,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}