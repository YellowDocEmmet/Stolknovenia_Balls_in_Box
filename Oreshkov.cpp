#include "TXLib.h"

struct Ball
{
  int x, y, r;
  double a, b;
  COLORREF color;
};
struct Box
{
  int a, b, c, d;
  COLORREF color;
};

void colliede(Ball*one, Ball*two);
struct Box box(struct Box num);
struct Ball ball(struct Ball num, struct Box bnum);

int main()
{
    txBegin();
    struct Ball one={200, 200, 100,3, 5, TX_MAGENTA};
    struct Ball two={500, 100, 60, 6, 1, TX_PINK};
    struct Ball tri={600, 200, 30, 5, 2, RGB (204,153,255)};
    struct Box odi={30, 30, 700, 500, TX_CYAN};

    txCreateWindow(1200,700);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txClear();
        odi=box(odi);
        one=ball(one, odi);
        two=ball(two, odi);
        tri=ball(tri, odi);
        colliede(&one, &two);
        colliede(&one, &tri);
        colliede(&two, &tri);
        txSleep (20);
        txSetFillColor(TX_BLACK);
    }
    txEnd();
    return 0;
}

struct Box box(struct Box bnum)
{
    txSetColor(bnum.color, 1);
    txRectangle(bnum.a, bnum.b, bnum.c, bnum.d);
    return bnum;
}

struct Ball ball(struct Ball num, struct Box bnum)
{
    num.x+=num.a;
    num.y+=num.b;
    if(num.x<=bnum.a+num.r)
    {
        num.a=-num.a;
        num.x=num.x-(2*(num.x-bnum.a-num.r));
    }
    if(num.x>=bnum.c-num.r)
    {
        num.a=-num.a;
        num.x=num.x-(2*(num.x-bnum.c+num.r));
    }
    if(num.y<=bnum.b+num.r)
    {
        num.b=-num.b;
        num.y=num.y-(2*(num.y-bnum.b-num.r));
    }
    if(num.y>=bnum.d-num.r)
    {
        num.b*=-1;
        num.y=num.y-(2*(num.y-bnum.d+num.r));
    }
    txSetColor(num.color);
    txSetFillColor(num.color);
    txCircle(num.x, num.y, num.r);
    return num;
}
void colliede(Ball*one, Ball*two)
{
    double tmp;
    if((one->x-two->x)*(one->x-two->x)+(one->y-two->y)*(one->y-two->y)<=(one->r+two->r)*(one->r+two->r))
    {
        tmp=one->a;
        one->a=two->a;
        two->a=tmp;
        tmp=one->b;
        one->b=two->b;
        two->b=tmp;
    }
}
