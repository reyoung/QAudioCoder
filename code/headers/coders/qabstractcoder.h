#ifndef QABSTRACTCODER_H
#define QABSTRACTCODER_H

#include <QQueue>
#include <QByteArray>
#include <QStringList>
#include <QLibrary>
#include <qaudio.h>
#include <qextendedaudioformat.h>
#include <qaudioinfo.h>
#include <qsamplearray.h>
#include <qsharedbuffer.h>

class QAbstractCoder : public QObject
{

	Q_OBJECT

	signals:

		void decoded(QSampleArray *array);
		void encoded(QSampleArray *array);
		void formatChanged(QExtendedAudioFormat format);

	public:

		enum Error
		{
			NoError = 0,

			PathError = 1,	//File does not exist
			FileError = 2,	//File exists, but is not a library
			LibraryError = 3,	//File exists and is a library, but not the required library
			VersionError = 4,	//File exists and is the required library, but the version is not supported

			InitializationError = 5,
			EncoderError = 6,
			DecoderError = 7,
			BufferError = 8,

			SampleSizeError = 9,
			SampleTypeError = 10,
			SampleRateError = 11,
			NumberOfChannelsError = 12
		};

		QAbstractCoder();
		~QAbstractCoder();

		const QList<QAudioCodec*> supportedCodecs() const;
		virtual QAudioCodec* detectCodec(const QByteArray &data) = 0;
		virtual QByteArray& header(){}

		virtual bool initializeDecode() = 0;
		virtual bool finalizeDecode() = 0;
		virtual void decode(const void *input, int size) = 0;

		virtual bool initializeEncode() = 0;
		virtual bool finalizeEncode() = 0;
		virtual void encode(const void *input, int samples) = 0;
		
		virtual QAbstractCoder::Error load();
		virtual QAbstractCoder::Error load(QString filePath);
		virtual bool unload();

		QString filePath() const;
		void setFilePath(QString filePath);

		QExtendedAudioFormat format(QAudio::Mode mode) const;
		void setFormat(QAudio::Mode mode, QExtendedAudioFormat format);

		QString name() const;
		QString version() const;
		QStringList fileNames() const;
		QStringList fileExtensions() const;
		void addFileName(QString name);
		void addFileExtension(QString extension);

		QAbstractCoder::Error error() const;

		bool operator == (const QAbstractCoder &other) const;
		bool operator != (const QAbstractCoder &other) const;

	protected:

		virtual QAbstractCoder::Error initializeLibrary() = 0;

	protected:

		QLibrary mLibrary;

		QString mName;
		QString mVersion;
		QStringList mFileNames;
		QStringList mFileExtensions;
		int mHeaderSize;

		QByteArray mHeader;

		QList<QAudioCodec*> mSupportedCodecs;

		QAbstractCoder::Error mError;

		QExtendedAudioFormat mInputFormat;
		QExtendedAudioFormat mOutputFormat;

};

#endif