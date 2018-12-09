#ifndef AVI_FILE_H
#define AVI_FILE_H

#include "inttypes.h"
#include <stdio.h>

#ifndef AVIIF_KEYFRAME
#define AVIIF_KEYFRAME      0x00000010L // this frame is a key frame.
#endif

typedef struct
{
	int i_data;
	int i_data_max;
	uint8_t *p_data;
} vbuf_t;

#ifndef avi_t
typedef struct
{
	FILE *f;

	float f_fps;
	char  fcc[4];

	int   i_width;
	int   i_height;

	int64_t i_movi;
	int64_t i_movi_end;
	int64_t i_riff;

	int      i_frame;
	int      i_idx_max;
	uint32_t *idx;
} avi_t;
#endif

class CAviFile
{
public:
	CAviFile();
    ~CAviFile();

public:
	//avi file info
	void vbuf_init( vbuf_t * ); //�����ʼ��
	void vbuf_add( vbuf_t *, int i_data, void *p_data ); //���һ֡��ת��h264/mpeg4����
	void vbuf_reset( vbuf_t * ); //���軺����
	void avi_init( avi_t *, FILE *, float, char fcc[4] , int iWidth, int iHeight); //��ʼ��avi�ļ�
	void avi_write( avi_t *, vbuf_t *, int  ); //д��avi�ļ�
	void avi_end( avi_t * ); //��ֹд��avi�ļ�

private:
	void avi_write_uint16( avi_t *a, uint16_t w );
	void avi_write_uint32( avi_t *a, uint32_t dw );
	void avi_write_fourcc( avi_t *a, char fcc[4] );
	void avi_write_header( avi_t *a );
	void avi_write_idx( avi_t *a );
	void avi_set_dw( void *_p, uint32_t dw );

public:
	//avi 
	vbuf_t  vb; //buffer struct
	avi_t   avi; //avi file format
};
#endif
