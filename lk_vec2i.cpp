#include "lk_vec2i.h"

lk_vec2i::lk_vec2i()
{
	x = 0;
	y = 0;
}

lk_vec2i::lk_vec2i(int nx, int ny)
{
	x = nx;
	y = ny;
}

lk_vec2i lk_vec2i::operator + (const lk_vec2i & op) const
{
	return lk_vec2i(x+op.x,y+op.y);
}

lk_vec2i lk_vec2i::operator - (const lk_vec2i & op) const
{
	return lk_vec2i(x-op.x,y-op.y);
}

lk_vec2i lk_vec2i::operator * (const lk_vec2i & op) const
{
	return lk_vec2i(x*op.x,y*op.y);
}


lk_vec2i lk_vec2i::operator * (const int & op) const
{
	return lk_vec2i(x*op,y*op);
}


lk_vec2i lk_vec2i::operator / (const int & op) const
{
	return lk_vec2i(x/op,y/op);
}

int & lk_vec2i::operator [] (int n)
{
	if ( n == 0) return x;
	if ( n == 1) return y;
	return x;
}
