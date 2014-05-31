#include <QImage>
#include <qmath.h>
#include <src/lk_utils.h>
#include <src/lk_conv.h>
#include <src/lk_vec2f.h>
#include <src/lk_vec2i.h>
#include <src/lk_mat22f.h>
#include <QTime>
#include <iostream>
//#include <omp.h>

int main(int argc, char *argv[])
{
	QTime timer1;
	timer1.start();
	QImage imgLeft,imgRight,imgLs,imgRs,imgM;
	if (argc < 3) {
		std::cout << "input two filenames" << std::endl;
		exit (-1);
	}
	if (!imgLs.load (QString (argv[1]))) {
		std::cout << "Cannot load first picture\n";
		exit(-1);
	}
	if (!imgRs.load (QString (argv[2]))) {
		std::cout << "Cannot load second picture\n";
		exit(-1);
	}
	if (!imgM.load (QString (argv[8]))) {
		std::cout << "Cannot load first picture\n";
		exit(-1);
	}
	bool ok;
	int __LK_PYRAMIDE_LEVELS = QByteArray(argv[3]).toInt(&ok,10);//!< Количество уровней гауссовой пирамиды
	int __LK_WINDOW_HALF_SIZE_X = QByteArray(argv[4]).toInt(&ok,10); //!< Половина размера окна поиска по горизонтали
	int __LK_WINDOW_HALF_SIZE_Y = QByteArray(argv[5]).toInt(&ok,10) ;//!< Половина размера окна поиска по вертикали
	int __LK_ITERATIONS_COUNT = QByteArray(argv[6]).toInt(&ok,10)   ;//!< Количество итераций для уточнения положения


	imgLs  =  imgLs.convertToFormat(QImage::Format_ARGB32);
	imgRs = imgRs.convertToFormat(QImage::Format_ARGB32);
	imgM = imgM.convertToFormat(QImage::Format_ARGB32);
	lk_conv gconv = lk_utils::gaussian_conv_kernel (5);

	//    imgLeft.save ("l.png");
	//    imgRight.save ("r.png");
	imgLeft = gconv*imgLs;
	imgRight= gconv*imgRs;
	//    lk_conv hedge(5,1),vedge(1,5);
	//    hedge[0][0] =  -1;
	//    hedge[1][0] =  8;
	//    hedge[2][0] =  0;
	//    hedge[3][0] =  -8;
	//    hedge[4][0] =  1;
	//    vedge[0][0] =  -1;
	//    vedge[0][1] =  8;
	//    vedge[0][2] =  0;
	//    vedge[0][3] =  -8;
	//    vedge[0][4] =  1;
	//    hedge.mult (1.0f/12.0f);
	//    vedge.mult (1.0f/12.0f);
	lk_conv hedge(3,1),vedge(1,3);
	hedge[0][0] =  -0.5;
	hedge[1][0] =  0;
	hedge[2][0] =  0.5;
	vedge[0][0] =  -0.5;
	vedge[0][1] =  0;
	vedge[0][2] =  0.5;

	if (imgLeft.size () != imgRight.size ()) {
		exit (-2);
	}

	QImage * leftP   = new QImage [__LK_PYRAMIDE_LEVELS];
	QImage * rightP  = new QImage [__LK_PYRAMIDE_LEVELS];
	QImage * leftDX  = new QImage [__LK_PYRAMIDE_LEVELS];
	QImage * leftDY  = new QImage [__LK_PYRAMIDE_LEVELS];

	int curtime = timer1.elapsed();
	int difftime = timer1.elapsed ();
	std::cout << "Images loaded" << 0.001f * difftime << " (" << 0.001f * curtime<< ")" << " seconds\n";
	leftP[0] = imgLeft.copy();
	rightP[0] = imgRight.copy();
	leftDX[0] = hedge%leftP[0];
	leftDY[0] = vedge%leftP[0];
	for (int i = 1; i < __LK_PYRAMIDE_LEVELS; ++i)
	{
		leftP[i]  = lk_utils::pyramide (leftP [i-1]);
		rightP[i] = lk_utils::pyramide (rightP[i-1]);
		leftDX[i] = hedge%leftP[i];
		leftDY[i] = vedge%leftP[i];
	}
	difftime = timer1.elapsed () - curtime;
	curtime = timer1.elapsed();
    std::cout << "Images converted " << 0.001f * difftime << " (" << 0.001f * curtime << ")" << " seconds\n";
	QImage hsv_result_image = imgLeft.copy ();
	QImage diff_result_image = imgLeft.copy ();
	QImage warp_result_image = imgLeft.copy ();
	hsv_result_image.fill (0x00000000);
	diff_result_image.fill (0xff000000);
	warp_result_image.fill (0x00ff0000);
	QRgb * hsv_data = (QRgb *)hsv_result_image.bits();
	QRgb * diff_data = (QRgb *)diff_result_image.bits();
	QRgb * warp_data = (QRgb *)warp_result_image.bits();


    int mainwidth = warp_result_image.width(),
            mainheight = warp_result_image.height(),
            width,
            ix,
            iy,
            ik,
            tx,
            ty,
            ux,
            uy,
            wx,
            wy,
            level,
            k;
	bool invalid, invalidshift;
	const QRgb * imageGradXwindow, * imageGradYwindow,* rightJL,* leftJL;
	lk_vec2f iterativeLK,res_disparity,*g,*d,*u,*b,*n,u0;
	lk_vec2i *iu,int_disparity;
	lk_mat22f Gradient_Matrix;
	QRgb lValue,rValue,diff;
	float magnitute, amplitude;
	int rx,ry;
	float perc=0;
	float barrier=-1;
	int curp = 0;
	int all = mainheight*mainwidth;

	difftime = timer1.elapsed () - curtime;
	curtime = timer1.elapsed();
    std::cout << "Constructors " << 0.001f * difftime << " (" << 0.001f * curtime << ")" << " seconds\n";

	//#pragma omp parallel for firstprivate(leftP,rightP,leftDX,leftDY, hsv_data, diff_data, warp_data,mainheight,mainwidth) private(g,d,u,iu,ix,iy,ik,b,n,iterativeLK,Gradient_Matrix,res_disparity,int_disparity,magnitute,amplitude,rValue,lValue,diff,imageGradXwindow,imageGradYwindow,invalid,invalidshift,width,rightJL,leftJL,wx,wy,k,level,tx,ty) private (uy,ux,u0,rx,ry)

	for (ux = 0; ux < mainwidth; ++ux)
	{
		g = (lk_vec2f*) malloc(sizeof(lk_vec2f)*__LK_PYRAMIDE_LEVELS);
		d = (lk_vec2f*) malloc(sizeof(lk_vec2f)*__LK_PYRAMIDE_LEVELS);
		u = (lk_vec2f*) malloc(sizeof(lk_vec2f)*__LK_PYRAMIDE_LEVELS);
		iu= (lk_vec2i*) malloc(sizeof(lk_vec2f)*__LK_PYRAMIDE_LEVELS);
		b = (lk_vec2f*) malloc(sizeof(lk_vec2f)*__LK_ITERATIONS_COUNT);
		n = (lk_vec2f*) malloc(sizeof(lk_vec2f)*__LK_ITERATIONS_COUNT);

		for ( uy = 0; uy < mainheight; ++uy)
		{
			u0 = lk_vec2f(ux,uy);
			g[__LK_PYRAMIDE_LEVELS - 1] = lk_vec2f(0,0);
			for ( level = __LK_PYRAMIDE_LEVELS - 1; level >= 0; --level)
			{
                u[level] = u0 / powf (2,level);     //!< Положение точки u на текущем уровне
                iu[level] = u[level].round ();      //!< Округленное значение
				d[level] = lk_vec2f(0,0);
				imageGradXwindow = (const QRgb *) leftDX[level].bits ();
				imageGradYwindow = (const QRgb *) leftDY[level].bits ();
				Gradient_Matrix = lk_mat22f(0,0,0,0);
				for (wx = iu[level].x - __LK_WINDOW_HALF_SIZE_X; wx <= iu[level].x + __LK_WINDOW_HALF_SIZE_X; ++wx)
				{
					for (wy = iu[level].y - __LK_WINDOW_HALF_SIZE_Y; wy <= iu[level].y + __LK_WINDOW_HALF_SIZE_Y; ++wy)
					{
						width = leftDX[level].width ();
						invalid = !leftDY[level].valid (wx,wy);
						ix = invalid ? 0 : (qGray(imageGradXwindow[wx+wy*width]) - 127);
						iy = invalid ? 0 : (qGray(imageGradYwindow[wx+wy*width]) - 127);
						Gradient_Matrix.add (
						ix*ix,ix*iy,ix*iy,iy*iy
						);
					}//
				}//End of Gradient Matrix
				iterativeLK = lk_vec2f(0,0); //!< Результат смещения
				rightJL = (const QRgb *) rightP[level].bits ();
				leftJL = (const QRgb *) leftP[level].bits ();
				for (k = 0; k < __LK_ITERATIONS_COUNT; ++k)
				{
					b[k] = lk_vec2f(0,0);
					n[k] = lk_vec2f(0,0);
					for (wx = iu[level].x - __LK_WINDOW_HALF_SIZE_X ; wx <= iu[level].x + __LK_WINDOW_HALF_SIZE_X ; ++wx)
					{
						for (wy = iu[level].y - __LK_WINDOW_HALF_SIZE_Y ; wy <= iu[level].y + __LK_WINDOW_HALF_SIZE_Y; ++wy)
						{
							tx  = wx + g[level].x + iterativeLK.x;
							ty  = wy + g[level].y + iterativeLK.y;
							width = leftDX[level].width ();
							invalid = !leftDY[level].valid (wx,wy);
							invalidshift = !leftDY[level].valid (tx,ty);
							ix =  invalid ? 0 : (qGray(imageGradXwindow [wx + wy*width]) - 127);
							iy =  invalid ? 0 : (qGray(imageGradYwindow [wx + wy*width]) - 127);
							ik = ((invalid ? 0 : qGray(		 leftJL [wx + wy*width])) -
							(invalidshift  ? 0 : qGray(		rightJL [tx + ty*width])));
							b[k].add(ix*ik,iy*ik);
						}//
					}// End of image mismatch vector calc
					n[k] = Gradient_Matrix.solve (b[k]);
					iterativeLK = iterativeLK + n[k];
					if (n[k].x < 1 && n[k].y < 1) break;
				}// End of iterative LK
				d[level] = iterativeLK;
				if (level != 0 ) g[level-1] = (g[level] + d[level])*2;
			}// End of levels Loop
			res_disparity = (g[0]+d[0])*0.5;
			//res_disparity = lk_vec2f(0,0);
			int_disparity = res_disparity.round ();
			lValue = imgLs.pixel (ux,uy);
			rx = ux + int_disparity.x;
			ry = uy + int_disparity.y;
			if (imgM.valid(rx,ry))
			{
				rValue =
				imgM.pixel (rx,ry);
				diff = qRgb (
				qAbs(qRed  (rValue) - qRed  (lValue)),
				qAbs(qGreen(rValue) - qGreen(lValue)),
				qAbs(qBlue (rValue) - qBlue (lValue))
				);//rValue;
				warp_data[rx + mainwidth*ry] = lValue;
				diff_data[rx + mainwidth*ry] = diff;
			}
			magnitute = lk_utils::vec2angf (res_disparity);
			amplitude = lk_utils::vec2ampf (res_disparity);
			hsv_data[ux + mainwidth*uy] = lk_utils::hsv2rgb(magnitute,255,10*amplitude); //!< Картинка направлений смещения
			curp++;
			perc = float(curp)/all;
			if (perc > barrier)
			{
                difftime = timer1.elapsed () - curtime;
                curtime = timer1.elapsed();
                //std::cout <<  "" << perc*100 <<  "%\n";
                std::cout << "Progress " << perc*100 << "% \t\t"<< 0.001f * difftime << " (" << 0.001f * curtime << ")" << " seconds\n";
				barrier = perc + 0.1;
			}
		}//
		//	free(g);
		//	free(d);
		//	free(u);
		//	free(iu);
		//	free(b);
		//	free(n);
	}//End of each point
	std::cout << "Time for picture " << mainwidth << "x" << mainheight << " is " << 0.001f * timer1.elapsed() << " seconds\n";
    //QString nameHsvOutFile;
    //nameHsvOutFile = "HSV_MAP " + QString (argv[3]) + ".png";
    //QString nameDiffOutFile = "DIFF_MAP .png";

    QString nameHsvOutFile = ("HSV_MAP" + QString (argv[3]) + " " + QString (argv[4]) + " " + QString (argv[5])  + " " + QString (argv[6])  + " " + QString (argv[7])  + ".png");
    QString nameDiffOutFile = ("DIFF_MAP" + QString (argv[3]) + " " + QString (argv[4]) + " " + QString (argv[5])  + " " + QString (argv[6])  + " " + QString (argv[7])  + ".png");

    QImage((uchar*)hsv_data,mainwidth,mainheight,QImage::Format_ARGB32).save(nameHsvOutFile);
    QImage((uchar*)diff_data,mainwidth,mainheight,QImage::Format_ARGB32).save(nameDiffOutFile);
	QImage((uchar*)warp_data,mainwidth,mainheight,QImage::Format_ARGB32).save(argv[7]);

	delete [] leftP ;
	delete [] rightP;
	delete [] leftDX;
	delete [] leftDY;

	std::cout << "Done\n";
}//End of Main
