#ifndef QCOMMON_H
#define QCOMMON_H

#include <QtGlobal>
#include <QAudioFormat>
#include <qaudio.h>
#include <string.h>
#include <math.h>

#define ROUND(x) (x<0?ceil((x)-0.5):floor((x)+0.5))

typedef unsigned char qbyte8u;
typedef unsigned short qbyte16u;
typedef unsigned int qbyte32u;
typedef qbyte8u qbyteu;

typedef signed char qbyte8s;
typedef signed short qbyte16s;
typedef signed int qbyte32s;
typedef qbyte8s qbytes;

typedef qbyte8u qbyte8;
typedef qbyte16u qbyte16;
typedef qbyte32u qbyte32;
typedef qbyte8 qbyte;

typedef float qfloat;

namespace QAudio
{

	enum SampleType
	{
		Unknown = 0,
		SignedInt = 1,
		UnSignedInt = 2,
		Float = 3,
		Double = 4,
		Real = Double
	};

	QAudioFormat::SampleType toFormatSampleType(QAudio::SampleType type);
	QAudio::SampleType toAudioSampleType(QAudioFormat::SampleType type);

}

#endif