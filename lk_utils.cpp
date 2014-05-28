#include "lk_utils.h"
#include <qmath.h>
#include <iostream>
lk_conv lk_utils::gaussian_conv_kernel (int s)
{
    float sum=0;
    float sigma2 = qPow((s/3.0f),2);
    lk_conv result(s,s);
    for (int x=0; x<s; x++)
    {
	for (int y=0; y<s; y++)
	{
	    float mx = (x - s/2);
	    float my = (y - s/2);
	    result[x][y] = (1.0f/ (2.0f*lk_utils::pi*(sigma2))) *
			   qExp ( -( mx*mx + my*my) / (2.0f*sigma2) );
	    sum += result[x][y];
	}
    }
    result.mult (1/sum);
    return result;
}


QImage lk_utils::pyramide (QImage src)
{
    return src.scaled (0.5 * src.size (),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}

QRgb lk_utils::hsv2rgb(float H, float S, float V)
{
//    int Hi = qFloor(H*6);
//    float f = H - Hi;
//    float p =  V * ( 1 - S);
//    float q =  V * ( 1 - f*S);
//    float t =  V * ( 1 - ( 1 - f) * S);
//    switch (Hi)
//    {
//    case 0: return qRgb(V,t,p);
//    case 1: return qRgb(q,V,p);
//    case 2: return qRgb(p,V,t);
//    case 3: return qRgb(p,q,V);
//    case 4: return qRgb(t,p,V);
//    case 5: return qRgb(V,p,q);
//    case 6: return qRgb(V,t,p);
//    }
//    return qRgb(0,0,0);

    //TColor HSVtoRGB(int i_hue,int sat,int val)
    int i_hue = (H*59);
    int sat = S;
    int val = V;
    int r=0,g=0,b=0,ii=0;

     double fr, hue;
     unsigned int c1, c2, c3;
     if (!sat)
       r = g = b = val;
     else
       {
	 while (i_hue >= 360)
	 i_hue -= 360;
	 hue = i_hue;
	 ii = (int)(hue /= 60.0);
	 fr = hue - ii;
	 c1 = (val * (255 - sat)) / 255;
	 c2 = (val * (255 - sat * fr)) / 255;
	 c3 = (val * (255 - sat * (1.0 - fr))) / 255;
	 switch (ii)
	   {
	     case 0: r = val; g = c3; b = c1; break;
	     case 1: r = c2; g = val; b = c1; break;
	     case 2: r = c1; g = val; b = c3; break;
	     case 3: r = c1; g = c2; b = val; break;
	     case 4: r = c3; g = c1; b = val; break;
	     case 5: r = val; g = c1; b = c2; break;
	   }
       }
    return qRgb(r,g,b);
}

QRgb lk_utils::hsv2rgb(QRgb color)
{
    int H = qRed (color);
    int S = qGreen (color);
    int V = qBlue (color);
    int Hi = qFloor((H/255)*6) % 6;
    float f = H/60;
    float p =  V * ( 1 - S);
    float q =  V * ( 1 - f*S);
    float t =  V * ( 1 - ( 1 - f) * S);
    switch (Hi)
    {
    case 0: return qRgb(V,t,p);
    case 1: return qRgb(q,V,p);
    case 2: return qRgb(p,V,t);
    case 3: return qRgb(p,q,V);
    case 4: return qRgb(t,p,V);
    case 5: return qRgb(V,p,q);
    }
    return qRgb(0,0,0);
}

QRgb lk_utils::rgb2hsv(QRgb)
{
    return qRgb(0,0,0);
}


float lk_utils::vec2angf (lk_vec2f vect)
{
    if (vect.x >= 0 && vect.y >= 0)
	return qAtan2(vect.x,vect.y);
    if (vect.x >= 0 && vect.y <= 0)
	return qAtan2(vect.x,vect.y);
    if (vect.x <= 0 && vect.y >= 0)
	return qAtan2(vect.x,vect.y) + 2*pi;
    if (vect.x <= 0 && vect.y <= 0)
	return qAtan2(vect.x,vect.y) + 2*pi;
    return 0;
}


int lk_utils::vec2ang (lk_vec2f vect)
{
    float at = qAtan2 (vect.x,vect.y)/pi + 0.5;
    if (vect.x < 0) at = at + 1;
    at = 0.5f*at;
    return int (255*at);
}

int lk_utils::vec2amp (lk_vec2f vect)
{
    float amp = qSqrt (vect.x*vect.x + vect.y*vect.y);
    return int(amp);
}

float lk_utils::vec2ampf (lk_vec2f vect)
{
    float amp = qSqrt (vect.x*vect.x + vect.y*vect.y);
    return amp;
}
