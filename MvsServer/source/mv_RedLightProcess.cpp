// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#include "mv_RedLightProcess.h"


mv_RedLightProcess::mv_RedLightProcess( float fscale )
{
	fScale = fscale;
	VarIniRedH = 5;
	VarIniRedL = 170;
	VarIniGenH = 127;
	VarIniGenL =200;
	//fScale = 1.0f;
}

mv_RedLightProcess::~mv_RedLightProcess()
{

}
/***********rgb to hsl  transforms*******************/
//	 rgb �����rgbֵ
//	 hsl ���ص�hslֵ
void mv_RedLightProcess::mvRGBToHSLnew(RGBCOLOR *rgb, RGBCOLOR *hsl)   
{
	double h,s,l, del_Value, inv_delvalue, inv_rgb;
	double r, g, b, maxcolor, mincolor;

	inv_rgb = 0.003921568627;// 1.0/255.0;

	r =  rgb->rgbRed * inv_rgb; // convert the rgb value to 0 ~ 1
	g = rgb->rgbGreen * inv_rgb;
	b = rgb->rgbBlue *inv_rgb;

	maxcolor = MAX_OF_TWO(r,MAX_OF_TWO(g,b));
	mincolor = MIN_OF_TWO(r,MIN_OF_TWO(g,b));

	del_Value = maxcolor - mincolor;
	l = (maxcolor + mincolor)*0.5;

	inv_delvalue = 1.0/del_Value;

	if ( del_Value == 0 )
	{
		h = 0;
		s = 0;
	}
	else
	{
		if ( l > 0 && l <= 0.5 )
		{
			s = (del_Value)/(2*l);
		}	
		else //if( l> 0.5)
		{
			s= (del_Value)/(2.0 - 2*l);
		}

		if ( r == maxcolor)
		{
			h = (g-b)*inv_delvalue;
		}		
		else if (g == maxcolor)
		{
			h = 2.0 + (b-r)*inv_delvalue;
		}	
		else if( b == maxcolor)
		{
			h = 4.0 + (r-g)*inv_delvalue;
		}					
	}

	if ( h<0 )
	{
		h += 6;
	}
	else if ( h > 6)
	{
		h -= 6;
	}	

	hsl->rgbRed = cvFloor(h*0.1666*255.99); //convert the hsl value to 0 ~ 255
	hsl->rgbGreen = cvFloor(s*255.99);
	hsl->rgbBlue = cvFloor(l*255.99);

}


/***********hsl to rgb transforms******************
*hsl �����hslֵ
* rgb ���ص�rgbֵ
*/
void mv_RedLightProcess::mvHSLToRGB(RGBCOLOR *hsl, RGBCOLOR *rgb)
{

	double h = (hsl->rgbRed)/255.0;
	double s = hsl->rgbGreen/255.0;
	double l = hsl->rgbBlue/255.0;

	double p,q;
	double T[3];
	int i= 0;

	if (s==0)
	{
		rgb->rgbRed = hsl->rgbBlue;
		rgb->rgbGreen = hsl->rgbBlue;
		rgb->rgbBlue = hsl->rgbBlue;
	}
	else
	{
		if (l< .5)
			q = l*(1.0 + s);
		else
			q = l + s - (l * s);

		p = 2.0*l - q;

		T[0] = h + 0.3333333;  //  1/3 = 0.3333333
		T[1] = h;
		T[2]= h - 0.3333333;

		for (i =0;i<3;i++)
		{
			if (T[i] < 0)
				T[i] += 1.0;
			else if(T[i] > 1) 
				T[i] -= 1.0;


			if ((T[i] *6.0) <1)
			{
				T[i] = p + ((q-p)*6.0*T[i]);
			}
			else if((T[i]*2.0) < 1)
			{
				T[i] = q;
			}
			else if ((T[i]*3.0) <2)
			{
				T[i] = p + (q - p)*((2.0/3.0)-T[i])*6.0;
			}
			else
				T[i] = p;

		}
		rgb->rgbRed = cvFloor(T[0]*255.99);
		rgb->rgbGreen = cvFloor(T[1]*255.99); // convert the rgb value to 0 ~ 255
		rgb->rgbBlue = cvFloor(T[2]*255.99);
	}

}

////////////////////////////////////////////////////////////////////////////////
/**
* 2D linear filter
* \param kernel: convolving matrix, in row format.
* \param Ksize: size of the kernel.
* \param Kfactor: normalization constant.
* \param Koffset: bias.
* \verbatim Example: the "soften" filter uses this kernel:
1 1 1
1 8 1
1 1 1
the function needs: kernel={1,1,1,1,8,1,1,1,1}; Ksize=3; Kfactor=16; Koffset=0; \endverbatim
* \return true if everything is ok
*/
bool mv_RedLightProcess::Filter( IplImage *pimg, CvRect vRect, long* kernel, long Ksize, long Kfactor, long Koffset )
{	

	long k2 = Ksize/2;
	long kmax= Ksize-k2;
	long r,g,b,i;
	RGBCOLOR c;	

	long xmin,xmax,ymin,ymax;
	xmin = vRect.x; xmax = vRect.x + vRect.width;
	ymin = vRect.y; ymax = vRect.y + vRect.height;	

	IplImage *pSmImage = cvCreateImage( cvSize( vRect.width, vRect.height ), 8, 3 );

	for(long y=ymin; y<ymax; y++)
	{		
		for(long x=xmin; x<xmax; x++)
		{
			r=b=g=0;
			for(long j=-k2;j<kmax;j++)
			{
				for(long k=-k2;k<kmax;k++)
				{
					//c=GetPixelColor(x+j,y+k);
					c.rgbRed = (uchar)pimg->imageData[ (y+k)*pimg->widthStep + 3*(x+j)];
					c.rgbGreen = (uchar)pimg->imageData[ (y+k)*pimg->widthStep + 3*(x+j) + 1];
					c.rgbBlue = (uchar)pimg->imageData[ (y+k)*pimg->widthStep + 3*(x+j) + 2];
					i=kernel[(j+k2)+Ksize*(k+k2)];
					r += c.rgbRed * i;
					g += c.rgbGreen * i;
					b += c.rgbBlue * i;
				}
			}
			if (Kfactor==0){
				c.rgbRed   = (uchar)MIN_OF_TWO(255, MAX_OF_TWO(0,(int)(r + Koffset)));
				c.rgbGreen = (uchar)MIN_OF_TWO(255, MAX_OF_TWO(0,(int)(g + Koffset)));
				c.rgbBlue  = (uchar)MIN_OF_TWO(255, MAX_OF_TWO(0,(int)(b + Koffset)));
			} else {
				c.rgbRed   = (uchar)MIN_OF_TWO(255, MAX_OF_TWO(0,(int)(r/Kfactor + Koffset)));
				c.rgbGreen = (uchar)MIN_OF_TWO(255, MAX_OF_TWO(0,(int)(g/Kfactor + Koffset)));
				c.rgbBlue  = (uchar)MIN_OF_TWO(255, MAX_OF_TWO(0,(int)(b/Kfactor + Koffset)));
			}
			pSmImage->imageData[ (y-vRect.y) * pSmImage->widthStep + 3*(x-vRect.x) + 0 ] = (char)c.rgbRed;
			pSmImage->imageData[ (y-vRect.y) * pSmImage->widthStep + 3*(x-vRect.x) + 1 ] = (char)c.rgbGreen;
			pSmImage->imageData[ (y-vRect.y) * pSmImage->widthStep + 3*(x-vRect.x) + 2 ] = (char)c.rgbBlue;
		}
	}

	//cvSaveImage( "1.jpg", pSmImage );

	cvSetImageROI(pimg, vRect);
	cvCopy( pimg, pSmImage );
	cvResetImageROI(pimg);
	cvReleaseImage(&pSmImage);
	return true;
}

/*****************************��������*************************************/
/*
* �������ܣ��Ե�������ɫ��������ʹ�����ɫ������,�̵Ʋ�����
* ���������ImgDataΪͼ�����ݣ�RecLigΪ�Ƶ�����nLghtSort�Ƶ����ࣨ��ơ��̵ƣ�
* ����ֵ ����
*/

//#define  zhangrugao
void mv_RedLightProcess::LigCorrect(IplImage * ImgData, CvRect RecLig, int nLghtSort)
{	
	//printf("VarIniRedH=%d,VarIniRedL=%d,VarIniGenH=%d,VarIniGenL=%d\n", VarIniRedH,VarIniRedL,VarIniGenH,VarIniGenL);

	//ѭ������
	int i,j;

	//RGB�ռ��HSL�ռ�ת������
	RGBCOLOR MvLigtRGB,MvLigtHSL;

	//ͼ������
	unsigned char * ucImgData;
	unsigned char * uPmData;
	unsigned char * uPcData;




		//����maskͼ��
		IplImage *pMaskImage = cvCreateImage( cvSize( RecLig.width, RecLig.height ), IPL_DEPTH_8U, 1 );
		IplImage *pColorImage = cvCreateImage( cvGetSize( pMaskImage ), IPL_DEPTH_8U, 3 );
		if ( !pMaskImage || !pColorImage )
		{
			return;
		}
		cvZero( pMaskImage );

		//��Ϊ������
		if ( nLghtSort)
		{
			for ( j = RecLig.y; j < RecLig.y + RecLig.height; j++)
			{
				ucImgData = (uchar*)(ImgData->imageData + j * ImgData->widthStep);

				uPmData = (uchar*)(pMaskImage->imageData + (j - RecLig.y) * pMaskImage->widthStep);

				uPcData = (uchar*)(pColorImage->imageData + (j - RecLig.y) * pColorImage->widthStep);


				for (i = RecLig.x; i < RecLig.x + RecLig.width; i++)
				{
					//��ͼ�������ֵ����MvLigtRGB

					MvLigtRGB.rgbRed = ucImgData[i * 3];
					MvLigtRGB.rgbGreen = ucImgData[i * 3 + 1];
					MvLigtRGB.rgbBlue = ucImgData[i * 3 + 2];

					//HSLתRGB����
					mvRGBToHSLnew(&MvLigtRGB, &MvLigtHSL);

					//�������׵ĵ�
					if ( MvLigtHSL.rgbRed > 65 && MvLigtHSL.rgbRed < 230 )/*MvLigtHSL.rgbBlue > 200 && MvLigtHSL.rgbRed > 65 && MvLigtHSL.rgbGreen > 200*/
					{
						//HSLתRGB����
						continue;
					}

					//mask ��ֵ


					//�Ժ����HSL�ռ��H������������˥��(�ֳ�����20~55��3~22������)
					if (MvLigtHSL.rgbRed >= 55 )
					{

						//MvLigtHSL.rgbRed = 5;
						MvLigtHSL.rgbRed = VarIniRedH;
						//uPmData[i - RecLig.x] = 255;
					}

					if ( (MvLigtHSL.rgbRed >= 20) && (MvLigtHSL.rgbRed < 55) )
					{
						//MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 20) * 0.02 + 4.3;

						MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 20) * 0.02 + VarIniRedH - 0.7;

						//uPmData[i - RecLig.x] = 255;

					}

					else if ( (MvLigtHSL.rgbRed >= 3) && (MvLigtHSL.rgbRed < 20) )
					{

						//MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 3) * 0.1 + 2.6; //��ǰд����1.7-��2.4
						MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 3) * 0.1 + VarIniRedH -  2.4;

						//uPmData[i - RecLig.x] = 255;

					}

					//�Ժ����HSL�ռ��L������������˥��
					if ( MvLigtHSL.rgbBlue >= 200 )
					{
						//MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 200) * 0.3 + 170;
						MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 200) * 0.3 + VarIniRedL;

						//uPmData[i - RecLig.x] = 255;

					}
					else if( MvLigtHSL.rgbBlue < 200  &&  MvLigtHSL.rgbBlue > 90 )
					{ 

						//MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 100) * 0.7 + 100;
						MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 100) * 0.7 + VarIniRedL- 70;

						//uPmData[i - RecLig.x] = 255;

					}

					//HSLתRGB����
					mvHSLToRGB(&MvLigtHSL,&MvLigtRGB);

					uPmData[i - RecLig.x] = 255;



					//ucImgData[i * 3 ] = MvLigtRGB.rgbRed ;
					//ucImgData[i * 3 + 1] = MvLigtRGB.rgbGreen;
					//ucImgData[i * 3 + 2] =  MvLigtRGB.rgbBlue ;

					uPcData[(i - RecLig.x) * 3 ] = MvLigtRGB.rgbRed ;
					uPcData[(i - RecLig.x) * 3 + 1] = MvLigtRGB.rgbGreen;
					uPcData[(i - RecLig.x) * 3 + 2] =  MvLigtRGB.rgbBlue ;
				}


			}


		}
		else //�̵ƴ���
		{

			for ( j = RecLig.y ; j < RecLig.y + RecLig.height; j++)
			{
				ucImgData = (uchar*)(ImgData->imageData + j * ImgData->widthStep);

				uPmData = (uchar*)(pMaskImage->imageData + (j - RecLig.y) * pMaskImage->widthStep);

				uPcData = (uchar*)(pColorImage->imageData + (j - RecLig.y) * pColorImage->widthStep);

				for (i = RecLig.x; i < RecLig.x + RecLig.width ; i++)
				{

					MvLigtRGB.rgbRed = ucImgData[i * 3 ];
					MvLigtRGB.rgbGreen= ucImgData[i * 3 + 1];
					MvLigtRGB.rgbBlue = ucImgData[i * 3 + 2];

					//HSLתRGB����
					mvRGBToHSLnew(&MvLigtRGB, &MvLigtHSL);

					if ( MvLigtHSL.rgbBlue > 200 )
					{

						//���̵���HSL�ռ��H������������˥��
						if ( MvLigtHSL.rgbRed > 200)
						{

							//MvLigtHSL.rgbRed =   (MvLigtHSL.rgbRed - 200 ) * 0.2 + 127;
							MvLigtHSL.rgbRed =   (MvLigtHSL.rgbRed - 200 ) * 0.2 + VarIniGenH;

							//uPmData[i - RecLig.x] = 255;

						}

						else if( MvLigtHSL.rgbRed >= 100 && MvLigtHSL.rgbRed < 200 )
						{

							MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 100) * 0.1 + VarIniGenH - 10;

							//uPmData[i - RecLig.x] = 255;
						}

						else
						{
							MvLigtHSL.rgbRed = VarIniGenH;

							//uPmData[i - RecLig.x] = 255;

						}

						//���̵���HSL�ռ��L������������˥��
						if ( MvLigtHSL.rgbBlue >= 200 )
						{ 
							//MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 200) * 0.1 + 200;
							MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 200) * 0.1 + VarIniGenL;

							//uPmData[i - RecLig.x] = 255;

						}
						else if( MvLigtHSL.rgbBlue < 200  &&  MvLigtHSL.rgbBlue > 100 )
						{
							MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 100) * 0.2 + VarIniGenL - 20;

							//uPmData[i - RecLig.x] = 255;

						}

						//�Ա��Ͷȵ���
						int nMinGrenL = VarIniGenL - 20;

						if (MvLigtHSL.rgbGreen < nMinGrenL )
						{
							MvLigtHSL.rgbGreen = MAX_OF_TWO(MvLigtHSL.rgbGreen, nMinGrenL );
							//uPmData[i - RecLig.x] = 255;
						}

						//HSLתRGB����
						mvHSLToRGB(&MvLigtHSL,&MvLigtRGB);

						uPmData[i - RecLig.x] = 255;		

						uPcData[(i - RecLig.x) * 3 ] = MvLigtRGB.rgbRed ;
						uPcData[(i - RecLig.x) * 3 + 1] = MvLigtRGB.rgbGreen;
						uPcData[(i - RecLig.x) * 3 + 2] =  MvLigtRGB.rgbBlue ;
					}	

				}
			}
		}

#ifdef zhangrugao
		cvSaveImage("mask.bmp",pMaskImage);

		cvConvertImage( pColorImage, pColorImage, CV_CVTIMG_SWAP_RB);
		cvSaveImage("pColorImage.bmp",pColorImage);

		cvConvertImage( pColorImage, pColorImage, CV_CVTIMG_SWAP_RB);
#endif
		//��maskͼ����и�ʴ
		IplImage * pCloneMaskImage = cvCloneImage( pMaskImage );
		cvZero(pCloneMaskImage);
		IplConvKernel* kernel1= cvCreateStructuringElementEx( 3, 3, 1, 1, CV_SHAPE_ELLIPSE, NULL );
		cvDilate(pMaskImage, pCloneMaskImage, kernel1, 1);
		cvDilate(pMaskImage, pCloneMaskImage, kernel1, 1);
		cvErode(pMaskImage, pCloneMaskImage, kernel1, 1);
		cvErode(pMaskImage, pCloneMaskImage, kernel1, 1);
		cvDilate(pMaskImage, pCloneMaskImage, kernel1, 1);

		//����������
		IplImage *pLargeImage = cvCreateImage( cvSize( pCloneMaskImage->width + 2, pCloneMaskImage->height + 2 ), 8, 1 );
		cvSetZero( pLargeImage );
		cvSetImageROI( pLargeImage, cvRect( 1, 1, pCloneMaskImage->width, pCloneMaskImage->height ) );
		cvCopy( pCloneMaskImage, pLargeImage, NULL );
		cvResetImageROI( pLargeImage );

		IplImage *pCloneLargeImage = cvCloneImage( pLargeImage );
#ifdef zhangrugao
		cvSaveImage("pLargeImage.bmp",pLargeImage);	
#endif
		CvSeq *pconters, *contour, *vcontours;
		CvSeq *fillseq;
		CvMemStorage *storage = cvCreateMemStorage( 0 );
		cvFindContours( pLargeImage, storage, &fillseq, sizeof(CvContour),CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cvPoint(0,0) );

		float fMaxAreas = 0;
		for ( contour = fillseq; contour != NULL; contour = contour->h_next )
		{
			float farea = fabs(cvContourArea( contour ));
			if ( farea > fMaxAreas )
			{
				fMaxAreas = farea;
				//cvDrawContours( pImage, contour,cvScalarAll(0),cvScalarAll(0),0,CV_FILLED,8);			
			}
			//cvDrawContours( pImage, contour,cvScalarAll(255),cvScalarAll(255),0,CV_FILLED,8);
		}
		for ( contour = fillseq; contour != NULL; contour = contour->h_next )
		{
			float farea = fabs(cvContourArea( contour ));
			if ( farea < fMaxAreas )
			{			
				cvDrawContours( pCloneLargeImage, contour,cvScalarAll(0),cvScalarAll(0),0,CV_FILLED,8);			
			}
			else
			{
				cvDrawContours( pCloneLargeImage, contour,cvScalarAll(255),cvScalarAll(255),0,CV_FILLED,8);		
			}

		}
#ifdef zhangrugao
		cvSaveImage("pCloneLargeImage.bmp",pCloneLargeImage);	
#endif
		cvSetZero( pCloneMaskImage );
		cvSetImageROI( pCloneLargeImage, cvRect( 1, 1, pCloneMaskImage->width, pCloneMaskImage->height ) );
		cvCopy( pCloneLargeImage, pCloneMaskImage, NULL );
		cvResetImageROI( pCloneLargeImage );
#ifdef zhangrugao
		cvSaveImage("pCloneMaskImage.bmp",pCloneMaskImage);	
#endif

		//��pCloneMaskImage����Ŀն��������
		mvFillHoleImage( pCloneMaskImage );

		//���㸳ֵ��ԭͼ����
		unsigned char *pCloneData;
		for ( j = RecLig.y ; j < RecLig.y + RecLig.height; j++)
		{
			ucImgData = (uchar*)(ImgData->imageData + j * ImgData->widthStep);

			uPmData = (uchar*)(pMaskImage->imageData + (j - RecLig.y) * pMaskImage->widthStep);

			uPcData = (uchar*)(pColorImage->imageData + (j - RecLig.y) * pColorImage->widthStep);

			pCloneData = (uchar*)(pCloneMaskImage->imageData + (j - RecLig.y) * pCloneMaskImage->widthStep);

			for (i = RecLig.x; i < RecLig.x + RecLig.width ; i++)
			{
				if ( (255 == uPmData[i - RecLig.x]) && (255 == pCloneData[ i - RecLig.x]) )
				{

					ucImgData[i * 3 ] = uPcData[(i - RecLig.x) * 3 ] * fScale + (1-fScale) * ucImgData[i * 3 ];//MvLigtRGB.rgbRed ;
					ucImgData[i * 3 + 1] = uPcData[(i - RecLig.x) * 3 + 1] * fScale + (1-fScale) * ucImgData[i * 3 + 1];//MvLigtRGB.rgbGreen;
					ucImgData[i * 3 + 2] = uPcData[(i - RecLig.x) * 3 + 2] * fScale + (1-fScale) * ucImgData[i * 3 + 2];//MvLigtRGB.rgbBlue;				
				}
				else if ( (0 == uPmData[i - RecLig.x]) && (255 == pCloneData[ i - RecLig.x]) )
				{
					if ( nLghtSort)
					{
						//��ͼ�������ֵ����MvLigtRGB
						MvLigtRGB.rgbRed = ucImgData[i * 3];
						MvLigtRGB.rgbGreen = ucImgData[i * 3 + 1];
						MvLigtRGB.rgbBlue = ucImgData[i * 3 + 2];
						//HSLתRGB����
						mvRGBToHSLnew(&MvLigtRGB, &MvLigtHSL);	
						//�Ժ����HSL�ռ��H������������˥��(�ֳ�����20~55��3~22������)
						if (MvLigtHSL.rgbRed >= 55 )
						{					
							MvLigtHSL.rgbRed = VarIniRedH;						
						}

						if ( (MvLigtHSL.rgbRed >= 20) && (MvLigtHSL.rgbRed < 55) )
						{
							MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 20) * 0.02 + VarIniRedH - 0.7;						
						}
						else if ( (MvLigtHSL.rgbRed >= 3) && (MvLigtHSL.rgbRed < 20) )
						{						
							MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 3) * 0.1 + VarIniRedH -  2.4;
						}
						//�Ժ����HSL�ռ��L������������˥��
						if ( MvLigtHSL.rgbBlue >= 200 )
						{					
							MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 200) * 0.3 + VarIniRedL;
						}
						else if( MvLigtHSL.rgbBlue < 200  &&  MvLigtHSL.rgbBlue > 90 )
						{ 						
							MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 100) * 0.7 + VarIniRedL- 70;
						}
						//HSLתRGB����
						mvHSLToRGB(&MvLigtHSL,&MvLigtRGB);
						ucImgData[i * 3 ] = MvLigtRGB.rgbRed * fScale + (1-fScale) * ucImgData[i * 3 ] ;
						ucImgData[i * 3 + 1] = MvLigtRGB.rgbGreen * fScale + (1-fScale) * ucImgData[i * 3 + 1];
						ucImgData[i * 3 + 2] =  MvLigtRGB.rgbBlue * fScale + (1-fScale) * ucImgData[i * 3 + 2];
					}
					else
					{
						MvLigtRGB.rgbRed = ucImgData[i * 3 ];
						MvLigtRGB.rgbGreen= ucImgData[i * 3 + 1];
						MvLigtRGB.rgbBlue = ucImgData[i * 3 + 2];
						//HSLתRGB����
						mvRGBToHSLnew(&MvLigtRGB, &MvLigtHSL);
						//���̵���HSL�ռ��H������������˥��
						if ( MvLigtHSL.rgbRed > 200)
						{						
							MvLigtHSL.rgbRed =   (MvLigtHSL.rgbRed - 200 ) * 0.2 + VarIniGenH;
						}
						else if( MvLigtHSL.rgbRed >= 100 && MvLigtHSL.rgbRed < 200 )
						{
							MvLigtHSL.rgbRed = (MvLigtHSL.rgbRed - 100) * 0.1 + VarIniGenH - 10;						
						}
						else
						{
							MvLigtHSL.rgbRed = VarIniGenH;
						}
						//���̵���HSL�ռ��L������������˥��
						if ( MvLigtHSL.rgbBlue >= 200 )
						{ 					
							MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 200) * 0.1 + VarIniGenL;
						}
						else if( MvLigtHSL.rgbBlue < 200  &&  MvLigtHSL.rgbBlue > 100 )
						{
							MvLigtHSL.rgbBlue =  (MvLigtHSL.rgbBlue - 100) * 0.2 + VarIniGenL - 20;
						}
						//�Ա��Ͷȵ���
						int nMinGrenL = VarIniGenL - 20;
						if (MvLigtHSL.rgbGreen < nMinGrenL )
						{
							MvLigtHSL.rgbGreen = MAX_OF_TWO(MvLigtHSL.rgbGreen, nMinGrenL );						
						}
						//HSLתRGB����
						mvHSLToRGB(&MvLigtHSL,&MvLigtRGB);
						ucImgData[i * 3 ] = MvLigtRGB.rgbRed * fScale + (1-fScale) * ucImgData[i * 3 ] ;
						ucImgData[i * 3 + 1] = MvLigtRGB.rgbGreen * fScale + (1-fScale) * ucImgData[i * 3 + 1];
						ucImgData[i * 3 + 2] =  MvLigtRGB.rgbBlue * fScale + (1-fScale) * ucImgData[i * 3 + 2];
					}
				}
			}
		}

		RecLig.x = MAX_OF_TWO( RecLig.x - 20, 0 );
		RecLig.y = MAX_OF_TWO( RecLig.y - 20, 0 );
		RecLig.width = RecLig.x + RecLig.width + 40 > ImgData->width ? ImgData->width - RecLig.x : RecLig.width + 40;
		RecLig.height = RecLig.y + RecLig.height + 40 > ImgData->height ? ImgData->height - RecLig.y : RecLig.height + 40;
		//cvSetImageROI( ImgData, RecLig );
		//cvSmooth( ImgData, ImgData );
		//cvResetImageROI( ImgData );

		long kernel[]={1,1,1,1,8,1,1,1,1};

		Filter( ImgData, RecLig, kernel,3, 16, 0 );


		cvReleaseMemStorage(&storage);
		cvReleaseImage(&pCloneLargeImage);
		cvReleaseImage(&pLargeImage);
		cvReleaseStructuringElement(&kernel1);
		cvReleaseImage(&pCloneMaskImage);
		cvReleaseImage(&pMaskImage);
		cvReleaseImage(&pColorImage);
	return ;
}


//��pCloneMaskImage����Ŀն��������
void mv_RedLightProcess::mvFillHoleImage( IplImage *pImage )
{
	//cvSaveImage( "image.bmp",pImage );
	int i, j, k;
	uchar *pData;
	for ( j = 0; j < pImage->height; j++ )
	{
		pData = (uchar*)( pImage->imageData + j * pImage->widthStep );
		for ( i = 0 ; i < pImage->width - 1; i++ )
		{
			if ( 255 == pData[i] && 0 == pData[i+1] )
			{
				for ( k = i+1; k < pImage->width - 1; k++ )
				{
					if ( 0 == pData[k] && 255 == pData[k+1] )
					{
						memset( &pData[i+1], 255, (k-i)* sizeof(uchar) );
						i = k;
						break;
					}
				}
			}
		}
	}
	//cvSaveImage( "image0.bmp",pImage );
	pData = (uchar*)( pImage->imageData );
	for ( i = 0; i < pImage->width; i++ )
	{		
		for ( j = 0 ; j < pImage->height - 1; j++ )
		{
			if ( 255 == pData[j * pImage->widthStep + i] && 0 == pData[(j+1) * pImage->widthStep + i] )
			{
				for ( k = j+1; k < pImage->height - 1; k++ )
				{
					if ( 0 == pData[k * pImage->widthStep + i] && 255 == pData[(k+1) * pImage->widthStep + i] )
					{
						for ( int t = j+1; t < k+1; t++ )
						{
							pData[t * pImage->widthStep + i] = 255;
						}
						//memset( &pData[j+1], 255, (k-j)* sizeof(uchar) );
						j = k;
						break;
					}
				}
			}
		}
	}
	//cvSaveImage( "image1.bmp",pImage );
}

void mv_RedLightProcess::ProcessSinglePic_ForDsp( IplImage* img0, bool bTurnLeft, bool bFoward, bool bTurnRight,
												 CvRect roiLeftLight_red, CvRect roiLeftLight_green,
												 CvRect roiMidLight_red, CvRect roiMidLight_green,
												 CvRect roiRightLight_red, CvRect roiRightLight_green, CvPoint m_affparams )
{
	bool bSingnal = false;

	CvRect temprect;

	//printf("image width = %d, height = %d\n", img0->width,img0->height );
	//printf("m_affparams.dx = %f, m_affparams.dy = %f\n",m_affparams.dx, m_affparams.dy);
	//printf("roiLeftLight_red.x=%d, roiLeftLight_red.y = %d,roiLeftLight_red.width=%d, roiLeftLight_red.height=%d\n",roiLeftLight_red.x,roiLeftLight_red.y,roiLeftLight_red.width,roiLeftLight_red.height);


	//printf("roiMidLight_red.x=%d, roiMidLight_red.y = %d,roiMidLight_red.width=%d, roiMidLight_red.height=%d\n",roiMidLight_red.x,roiMidLight_red.y,roiMidLight_red.width,roiMidLight_red.height);

	//printf("roiRightLight_red.x=%d, roiRightLight_red.y = %d,roiRightLight_red.width=%d, roiRightLight_red.height=%d\n",roiRightLight_red.x,roiRightLight_red.y,roiRightLight_red.width,roiRightLight_red.height);

	//���ж�һ�´�������ĸ�������
	//���ж�һ�´�������ĸ�������
	if ( roiLeftLight_red.width > 0 )
	{
		bSingnal = bTurnLeft;
	}
	else if ( roiMidLight_red.width > 0 )
	{
		bSingnal = bFoward;
	}
	else if ( roiRightLight_red.width > 0 )
	{
		bSingnal = bTurnRight;
	}
	else
	{
		return;
	}
	//printf("enter LigCorrect!\n");
	//fflush(stdout);

	if ( bSingnal )
	{
		if ( roiLeftLight_red.width > 0 )
		{
			temprect = roiLeftLight_red;
			roiLeftLight_red.x = MAX_OF_TWO(0,roiLeftLight_red.x + m_affparams.x);
			roiLeftLight_red.y = MAX_OF_TWO(0,roiLeftLight_red.y + m_affparams.y);
			LigCorrect( img0, roiLeftLight_red, 1 );
			roiLeftLight_red = temprect;
		}			
		if ( roiMidLight_red.width > 0 )
		{
			//printf("enter roiMidLight_red!\n");
			//fflush(stdout);
			temprect = roiMidLight_red;
			roiMidLight_red.x = MAX_OF_TWO(0,roiMidLight_red.x + m_affparams.x);
			roiMidLight_red.y = MAX_OF_TWO(0,roiMidLight_red.y + m_affparams.y);
			LigCorrect( img0, roiMidLight_red, 1 );
			roiMidLight_red = temprect;
		}
		if ( roiRightLight_red.width > 0 )
		{
			temprect = roiRightLight_red;
			roiRightLight_red.x = MAX_OF_TWO(0,roiRightLight_red.x + m_affparams.x);
			roiRightLight_red.y = MAX_OF_TWO(0,roiRightLight_red.y + m_affparams.y);
			LigCorrect( img0, roiRightLight_red, 1 );
			roiRightLight_red = temprect;
		}
		//			mvImageProcessRedLight(img0, roiLeftLight, nDay, 1);
		//			mvImageProcessRedLight(img0, roiTurnAroundLight, nDay, 1);
	}
	else
	{
		if ( roiLeftLight_green.width > 0 )
		{
			temprect = roiLeftLight_green;
			roiLeftLight_green.x = MAX_OF_TWO(0,roiLeftLight_green.x + m_affparams.x);
			roiLeftLight_green.y = MAX_OF_TWO(0,roiLeftLight_green.y + m_affparams.y);
			LigCorrect( img0, roiLeftLight_green, 0 );
			roiLeftLight_green = temprect;
		}
		if ( roiMidLight_green.width > 0 ) 
		{			
			temprect = roiMidLight_green;
			roiMidLight_green.x = MAX_OF_TWO(0,roiMidLight_green.x + m_affparams.x);
			roiMidLight_green.y = MAX_OF_TWO(0,roiMidLight_green.y + m_affparams.y);
			LigCorrect( img0, roiMidLight_green, 0 );
			roiMidLight_green = temprect;
		}
		if ( roiRightLight_green.width > 0 )
		{
			temprect = roiRightLight_green;
			roiRightLight_green.x = MAX_OF_TWO(0,roiRightLight_green.x + m_affparams.x);
			roiRightLight_green.y = MAX_OF_TWO(0,roiRightLight_green.y + m_affparams.y);
			LigCorrect( img0, roiRightLight_green, 0 );
			roiRightLight_green = temprect;
		}			
	}		
	
}