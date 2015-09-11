#ifndef _OGG_FILTER_
#define _OGG_FILTER_

#pragma pack(push, 1)

struct WaveFileHeader
{
	uChar	RIFF_SIG[4];
	uLong	RiffSize;
	uChar	WAVE_SIG[4];
};

struct RiffChunk
{
	uChar	CHUNK_NAME[4];
	uLong	ChunkSize;
};

struct WaveFormatEx
{
	uShort	FormatTag;
	uShort	Channels;
	uInt	SamplesPerSec;
	uInt	AvgBytesPerSec;
	uShort	BlockAlign;
	uShort	BitsPerSample;
};

struct WaveFile
{
WaveFileHeader	Header;
RiffChunk		fmtChunk;
WaveFormatEx	Format;
RiffChunk		dataChunk;
};

#pragma pack(pop)

class OggFilter : public IfsFilter
{
protected:
	ObjectArray<AutoPtr<OggFilter>> Streams;

protected:
	OggFilter* GetFreeStream(void);

public:
	virtual IfsFilter*	Open(IFS* src);

protected:
	IFS*			Source;
	OggVorbis_File	Vorbis;
	ov_callbacks	Callbacks;
	WaveFile		Wave;
	uLong			Offset;

protected:
	bool Attach(IFS* src);

public:
	virtual uLong		GetFileSize(void) const;
	virtual uLong		GetOffset(void) const;
	virtual bool		SetOffset(uLong offset);
	virtual uLong		GetData(void* buffer, uLong size);
	virtual void		Close(void);

public:
	OggFilter(void);
	virtual ~OggFilter(void)
	{
		Close();
	}
};

#endif