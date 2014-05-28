#include "lk_conv.h"

void lk_conv::mult (float val)
{
	for ( int cx = 0; cx < __width; ++cx)
	for (int cy = 0; cy < __height; ++cy)
	kernel[cx][cy] *= val;
}

lk_conv::lk_conv()
{
	QVector < QVector < float > > newkernel;
	QVector < float > nullrow;
	nullrow.append (1);
	newkernel.append (nullrow);
	kernel = newkernel;
	__width = 1;
	__height = 1;
}

lk_conv::lk_conv(int w, int h)
{
	QVector < QVector < float > > newkernel;
	QVector < float > nullrow;
	nullrow.fill (0,h);
	newkernel.fill (nullrow,w);
	kernel = newkernel;
	__width = w;
	__height = h;
}

QImage lk_conv::conv (const QImage & src) const
{
	QImage result = src.copy ();
	for (int x = 0; x < src.width (); ++x)
	{
		for (int y = 0; y < src.height (); ++y)
		{
			QImage pattern = src.copy (x - __width/2, y - __height/2, __width, __height );
			long R = 0, G = 0, B = 0;
			for ( int cx = 0; cx < __width; ++cx)
			{
				for (int cy = 0; cy < __height; ++cy)
				{
					QRgb curpix = pattern.pixel (cx,cy);
					R += ((0x00ff0000 & curpix) >> 16)*kernel[cx][cy];
					G += ((0x0000ff00 & curpix) >> 8)*kernel[cx][cy];
					B += ((0x000000ff & curpix))*kernel[cx][cy];
				}
			}
			result.setPixel (x,y,qRgb (R,G,B));
		}
	}
	return result;
}

QImage lk_conv::operator * (const QImage & src) const
{
	return conv(src);
}


QImage lk_conv::zeroconv (const QImage & src) const
{
	QImage result = src.copy ();
	for (int x = 0; x < src.width (); ++x)
	{
		for (int y = 0; y < src.height (); ++y)
		{
			QImage pattern = src.copy (x - __width/2, y - __height/2, __width, __height );
			long R = 0, G = 0, B = 0;
			for ( int cx = 0; cx < __width; ++cx)
			{
				for (int cy = 0; cy < __height; ++cy)
				{
					QRgb curpix = pattern.pixel (cx,cy);
					R += ((0x00ff0000 & curpix) >> 16)*kernel[cx][cy];
					G += ((0x0000ff00 & curpix) >> 8)*kernel[cx][cy];
					B += ((0x000000ff & curpix))*kernel[cx][cy];
				}
			}
			result.setPixel (x,y,qRgb (127+R,127+G,127+B));
		}
	}
	return result;


	//    int **resultimage;
	//    const int *data = (int *) src.bits ();
	//    resultimage = (int **) malloc (src.width()*sizeof(int*));
	//    for (int i=0; i<src.width (); ++i) resultimage[i] = (int *) malloc (src.height ()*sizeof(int));
	//    long R = 0, G = 0, B = 0;
	//    for (int x = 0; x < src.width (); ++x)
	//    {
	//	for (int y = 0; y < src.height (); ++y)
	//	{
	//	    R=0;
	//	    G=0;
	//	    B=0;
	//	    for ( int cx = 0; cx < __width; ++cx)
	//	    {
	//		for (int cy = 0; cy < __height; ++cy)
	//		{
	//		    int wx = x+cx-__width/2;
	//		    int wy = y+cy-__height/2;
	//		    int curpix;
	//		    if ( src.valid (wx,wy))
	//			curpix = data[ wx + wy * src.width ()];
	//		    else
	//			curpix = 0;
	//		    R += ((0x00ff0000 & curpix) >> 16) * kernel[cx][cy];
	//		    G += ((0x0000ff00 & curpix) >> 8) * kernel[cx][cy];
	//		    B += ((0x000000ff & curpix)) * kernel[cx][cy];
	//		}
	//	    }
	//	    resultimage[x][y] = 0x00ffffff & ((int(127+0.5f*R)<<16) | (int(127+0.5f*2)<<8) | int(127+0.5f*2));
	//	}
	//    }
	//    return QImage((uchar*)resultimage,src.width (),src.height (),QImage::Format_RGB888);
}

QImage lk_conv::operator % (const QImage & src) const
{
	return zeroconv (src);
}

QVector <float> & lk_conv::operator [] (int i)
{
	return kernel[i];
}

void lk_conv::normalize ()
{
	long sum = 0;
	for (int x = 0; x < __width; ++x)
	{
		for (int y = 0; y < __height; ++y)
		{
			sum += kernel[x][y];
		}
	}
	if (sum == 0) return;
	for (int x = 0; x < __width; ++x)
	{
		for (int y = 0; y < __height; ++y)
		{
			kernel[x][y] /= sum;
		}
	}
}
