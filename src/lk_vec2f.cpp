#include "lk_vec2f.h"
#include <qmath.h>

lk_vec2f::lk_vec2f()
{
	x = 0;
	y = 0;
}

lk_vec2f::lk_vec2f(float nx, float ny)
{
	x = nx;
	y = ny;
}

lk_vec2f lk_vec2f::operator + (const lk_vec2f & op) const
{
	return lk_vec2f(x+op.x,y+op.y);
}

lk_vec2f lk_vec2f::operator - (const lk_vec2f & op) const
{
	return lk_vec2f(x-op.x,y-op.y);
}

lk_vec2f lk_vec2f::operator * (const lk_vec2f & op) const
{
	return lk_vec2f(x*op.x,y*op.y);
}


lk_vec2f lk_vec2f::operator * (const float & op) const
{
	return lk_vec2f(x*op,y*op);
}


lk_vec2f lk_vec2f::operator / (const float & op) const
{
	return lk_vec2f(x/op,y/op);
}

float & lk_vec2f::operator [] (int n)
{
	if ( n == 0) return x;
	if ( n == 1) return y;
	return x;
}

lk_vec2i lk_vec2f::round () const
{
	return lk_vec2i(qRound (x), qRound (y));
}

void lk_vec2f::add (float ax, float ay)
{
    x += ax;
    y += ay;
}
