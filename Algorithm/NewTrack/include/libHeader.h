#ifndef __LIB_HEADER_H
	#define __LIB_HEADER_H

	//ͷ�ļ�
	#include <vector>
	#include <algorithm>

	#include <string>
	#include <iostream>
	#include <fstream>

	#include <stdio.h>
	#include <stdlib.h>

	#include <math.h>
	#include <time.h>

#ifndef  LINUX
	#include "opencv2/opencv.hpp"
	#include "opencv2/objdetect/objdetect.hpp" 
	#include "opencv2/features2d/features2d.hpp" 
	#include "opencv2/highgui/highgui.hpp" 
	#include "opencv2/calib3d/calib3d.hpp" 
	#include "opencv2/imgproc/imgproc_c.h" 
	#include "opencv2/imgproc/imgproc.hpp"   
	#include "opencv2/nonfree/features2d.hpp"
	#include "opencv2/legacy/legacy.hpp"
	#include "opencv2/legacy/compat.hpp"

	#include <wtypes.h>
	using namespace cv; 
#else
	#include "cv.h"
	#include "highgui.h"
	#include "cxcore.h"
#endif
	
#ifdef LINUX
	#include <dirent.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>

	#include <sys/time.h>
	#include <sys/timeb.h>
	#include <sys/vfs.h>
	#include <sys/statvfs.h>

	#ifndef CHDIR
		#define CHDIR
		#define _chdir(a) chdir(a)
	#endif
	#ifndef MKDIR
		#define MKDIR
		#define _mkdir(a) mkdir(a, 0777)
	#endif
	#ifndef ACCESS
		#define ACCESS
		#define _access(a, b) access(a, b)
	#endif
#else
	#include <io.h>
	#include <direct.h>
#endif
	using namespace std;

	//����һЩ���õĺ�
	#ifndef MAX
		#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
	#endif

	#ifndef MIN
		#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
	#endif


	//����һЩ2ά������
	struct MvInt2DVector{ vector< vector<int> > m_Int2DVector; };
	struct MvCvPoint2DVector{ vector< vector<CvPoint> > m_CvPoint2DVector; };

#endif  //#ifndef __COM_HEADER_H