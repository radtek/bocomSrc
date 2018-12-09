
#include "MvDspMaxSize.h"

/************************************************************************/
/*                ���캯����ʼ��                                        */
/************************************************************************/
MvDspMaxSize::MvDspMaxSize()
{
	m_wldx_image = NULL;
	m_wldy_image = NULL;
	m_carwidth_image  = NULL;
	m_carheight_image = NULL;
	memset( m_homographyMatrix, 0, sizeof(double)*3*3 );
}

/************************************************************************/
/*                ���������ͷ��ڴ�                                      */
/************************************************************************/
MvDspMaxSize::~MvDspMaxSize()
{
	if( m_wldx_image )
	{
		cvReleaseImage( &m_wldx_image );
	}
	if( m_wldy_image )
	{
		cvReleaseImage( &m_wldy_image );
	}
	if( m_carwidth_image )
	{
		cvReleaseImage( &m_carwidth_image );
	}
	if( m_carheight_image )
	{
		cvReleaseImage( &m_carheight_image );
	}
}

/************************************************************************/
/*           ��ȡ�������ĵ�����������ͼ���г����Ŀ�Ⱥ͸߶�           */
/************************************************************************/
void MvDspMaxSize::GetWorldCoordinateAndCarSize()
{
	CvSize imgSize = cvSize( m_nWidth, m_nHeight );

	m_wldx_image      = cvCreateImage( imgSize, IPL_DEPTH_64F, 1 );
	m_wldy_image      = cvCreateImage( imgSize, IPL_DEPTH_64F, 1 );
	m_carwidth_image  = cvCreateImage( imgSize, IPL_DEPTH_16U, 1 );
	m_carheight_image = cvCreateImage( imgSize, IPL_DEPTH_16U, 1 );

	memcpy( m_pCalib.m_image_coordinate, m_image_coordinate, sizeof(double)*2*4 );  //ͼ��������4����
	memcpy( m_pCalib.m_world_coordinate, m_world_coordinate, sizeof(double)*2*4 );  //����������4����
	m_pCalib.FindHomography();  //�����ͼ�����굽���������ת������

	CvPoint image_center;  //ͼ�������г��������ĵ�
	CvPoint image_left;    //ͼ�����������ĵ�����
	CvPoint image_right;   //ͼ�����������ĵ���ҵ�
	CvPoint image_up;      //ͼ�����������ĵ���ϵ�
	CvPoint image_down;    //ͼ�����������ĵ���µ�
	CvPoint2D64f world_center;  //���������г��������ĵ�
	CvPoint2D64f world_left;    //�������������ĵ�����
	CvPoint2D64f world_right;   //�������������ĵ���ҵ�
	CvPoint2D64f world_up;      //�������������ĵ���ϵ�
	CvPoint2D64f world_down;    //�������������ĵ���µ�
	double car_width_world = 1.9;   //��������ϵ�г����Ŀ��
	double car_height_world = 6.0;
	//double car_height_world = 4.3;  //��������ϵ�г����ĸ߶�
	int car_width_image, car_height_image;  //ͼ�������г����Ŀ�Ⱥ͸߶�

	int row, col;
	for( row = 0; row < m_nHeight; row++ )
	{
		for( col = 0; col < m_nWidth; col++ )
		{
			image_center = cvPoint( col, row );
			world_center = m_pCalib.GetWorldCoordinate( image_center );  //��ȡͼ�����ĵ����������

			//��ȡ��������ϵ�г�������㡢�ҵ㡢�ϵ㡢�µ�
			world_left  = cvPoint2D64f( world_center.x - car_width_world/2, world_center.y );
			world_right = cvPoint2D64f( world_center.x + car_width_world/2, world_center.y );
			world_up    = cvPoint2D64f( world_center.x, world_center.y - car_height_world/2 );
			world_down  = cvPoint2D64f( world_center.x, world_center.y + car_height_world/2 );

			//������������ϵ�г�������㡢�ҵ㡢�ϵ㡢�µ���ȡͼ������ϵ�г�������㡢�ҵ㡢�ϵ㡢�µ�
			image_left  = m_pCalib.GetImageCoordinate( world_left );
			image_right = m_pCalib.GetImageCoordinate( world_right );
			image_up    = m_pCalib.GetImageCoordinate( world_up );
			image_down  = m_pCalib.GetImageCoordinate( world_down );

			//����ͼ������ϵ�г����Ŀ�Ⱥ͸߶�
			car_width_image  = cvFloor( sqrt( (double)(image_right.x - image_left.x) * (image_right.x - image_left.x) 
				                            + (double)(image_right.y - image_left.y) * (image_right.y - image_left.y) ) );
			car_height_image = cvFloor( sqrt( (double)(image_down.x - image_up.x) * (image_down.x - image_up.x)
				                            + (double)(image_down.y - image_up.y) * (image_down.y - image_up.y) ) );

			((double*)(m_wldx_image->imageData + m_wldx_image->widthStep * row))[col] = world_center.x;
			((double*)(m_wldy_image->imageData + m_wldy_image->widthStep * row))[col] = world_center.y;
			((ushort*)(m_carwidth_image->imageData + m_carwidth_image->widthStep * row))[col] = car_width_image;
			((ushort*)(m_carheight_image->imageData + m_carheight_image->widthStep * row))[col] = car_height_image;
		}
	}
}