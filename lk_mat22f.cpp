#include "lk_mat22f.h"

lk_mat22f::lk_mat22f()
{
	a1 = a2 = lk_vec2f(0,0);
}

lk_mat22f::lk_mat22f(float na11, float na12, float na21, float na22)
{
	a1 = lk_vec2f(na11,na12);
	a2 = lk_vec2f(na21,na22);
}

lk_mat22f::lk_mat22f(lk_vec2f na1, lk_vec2f na2)
{
	a1 = na1;
	a2 = na2;
}

lk_mat22f lk_mat22f::operator + (const lk_mat22f & op) const
{
	return lk_mat22f (a1 + op.a1,a2 + op.a2);
}

lk_mat22f lk_mat22f::operator - (const lk_mat22f & op) const
{
	return lk_mat22f (a1 - op.a1,a2 - op.a2);
}

lk_mat22f lk_mat22f::operator * (const lk_mat22f & op) const
{
	return lk_mat22f (op.a1 * a1.x + op.a2 * a1.y, op.a1 * a2.x + op.a2 * a2.y);
}

lk_mat22f lk_mat22f::operator * (const float & op) const
{
	return lk_mat22f ( a1*op, a2*op);
}
lk_mat22f lk_mat22f::operator / (const float & op) const
{
	return lk_mat22f ( a2/op, a2/op);
}

lk_vec2f lk_mat22f::operator * (const lk_vec2f & op) const
{
	return a1 * op.x + a2 * op.y;
}

lk_vec2f & lk_mat22f::operator []( int n)
{
	if ( n == 0) return a1;
	if ( n == 1) return a2;
	return a1;
}

float lk_mat22f::det () const
{
	return a1.x*a2.y - a1.y*a2.x;
}

lk_vec2f lk_mat22f::solve (const lk_vec2f b) const
{
	lk_mat22f d1 (b,a2);
	lk_mat22f d2 (a1,b);
	float adet = det ();
	if (adet < eps) return lk_vec2f (0, 0);
	return lk_vec2f ( d1.det () / adet, d2.det () / adet);
}

void lk_mat22f::add(float a11, float a12, float a21, float a22)
{
	a1.add(a11,a12);
	a2.add(a21,a22);
}
