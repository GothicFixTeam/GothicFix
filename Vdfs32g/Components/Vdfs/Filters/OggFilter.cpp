#include "PreCompiled.h"

OggFilter* OggFilter::GetFreeStream(void)
{
	for(uInt i = 0; i < Streams.Size(); i++)
	{
		if(!Streams[i]->Source)
			return Streams[i];
	}
	return Streams.Add(new OggFilter());
}

IfsFilter* OggFilter::Open(IFS* src)
{
	TString Ext(src->GetName());
	if(!Ext.TruncateBeforeLast(_T(".")) || (!Ext.Compare(_T("WAV")) && !Ext.Compare(_T("OGG"))))
		return NULL;

	src->SetOffset(0);

	uChar Buffer[4];
	if((src->GetData(Buffer, 4) == 4) && !memcmp(Buffer, "OggS", 4))
	{
		src->SetOffset(0);
		OggFilter* Res = GetFreeStream();
		if(Res->Attach(src))
			return Res;
	}

	src->SetOffset(0);
	return NULL;
}

bool OggFilter::Attach(IFS* src)
{
	if(!ov_open_callbacks((void*)src, &Vorbis, NULL, 0, Callbacks) && (ov_streams(&Vorbis) == 1))
	{
		Source = src;

		vorbis_info* info = ov_info(&Vorbis, -1);

		Wave.Format.Channels = info->channels;
		Wave.Format.SamplesPerSec = info->rate;
		Wave.Format.BlockAlign = Wave.Format.Channels * Wave.Format.BitsPerSample / 8;
		Wave.Format.AvgBytesPerSec = Wave.Format.SamplesPerSec * Wave.Format.BlockAlign;
		Wave.dataChunk.ChunkSize = (uInt)ov_pcm_total(&Vorbis, -1) * Wave.Format.BlockAlign;
		Wave.Header.RiffSize = Wave.dataChunk.ChunkSize + sizeof(WaveFile) - 8;

		Offset = 0;
		return true;
	}
	Close();
	return false;
}

uLong OggFilter::GetFileSize(void) const
{
	return Wave.Header.RiffSize + 8;
}

uLong OggFilter::GetOffset(void) const
{
	return Offset;
}

bool OggFilter::SetOffset(uLong offset)
{
	if(offset > GetFileSize())
		return false;
	Offset = offset;
	return true;
}

uLong OggFilter::GetData(void* buffer, uLong size)
{
	char* Buffer = (char*)buffer;
	uLong Size = size;
	if(Offset < sizeof(WaveFile))
	{
		size_t ToRead = sizeof(WaveFile) - Offset;
		if(size < ToRead)
			ToRead = size;

		memcpy(buffer, &Wave, ToRead);

		Buffer += ToRead;
		Size -= ToRead;
		Offset += ToRead;
	}

	if(Size)
	{
		uInt Part = (Offset - sizeof(WaveFile)) % Wave.Format.BlockAlign;
		if(Part)
		{
			Buffer = new char[size + Part];
			Offset -= Part;
			Size += Part;
		}

		if(ov_pcm_seek(&Vorbis, (Offset - sizeof(WaveFile)) / Wave.Format.BlockAlign))
		{
			if(Part)
				delete[] Buffer;
			return 0;
		}

		int default_stream = -1;

		uInt Readed = 0;
		while(Readed < Size)
		{
			int res = ov_read(&Vorbis, &Buffer[Readed], Size - Readed, 0, 2, 1, &default_stream);
			if(res <= 0)
			{
				if(Part)
				{
					memcpy(buffer, &Buffer[Part], Readed - Part);
					delete[] Buffer;
				}
				return (size - (Size - Part)) + Readed;
			}
			Readed += res;
			Offset += res;
		}

		if(Part)
		{
			memcpy(&((uChar*)buffer)[size - Size], &Buffer[Part], size);
			delete[] Buffer;
		}
	}
	return size;
}

void OggFilter::Close(void)
{
	if(Vorbis.datasource)
		ov_clear(&Vorbis);
	memset(&Vorbis, 0, sizeof(OggVorbis_File));

	if(Source)
	{
		Source->Close();
		Source = NULL;
	}
}

size_t vorbis_read(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	IFS* FS = (IFS*)datasource;
	size_t ActualSize = size * nmemb;

	size_t MaxReadSize = (size_t)(FS->GetFileSize() - FS->GetOffset());
	if(ActualSize > MaxReadSize)
	{
		nmemb = MaxReadSize / size;
		ActualSize = size * nmemb;
	}

	if(FS->GetData(ptr, ActualSize) == ActualSize)
		return nmemb;

	return 0;
}

int vorbis_seek(void* datasource, ogg_int64_t offset, int whence)
{
	IFS* FS = (IFS*)datasource;
	switch(whence)
	{
    case SEEK_SET:
		FS->SetOffset((uLong)offset);
		break;
    case SEEK_CUR:
		FS->SetOffset((long)FS->GetOffset() + (long)offset);
		break;
    case SEEK_END:
		FS->SetOffset((long)FS->GetFileSize() + (long)offset);
		break;
	}
	return (int)FS->GetOffset();
}

int vorbis_close(void* datasource)
{
	return 0;
}

long vorbis_tell(void* datasource)
{
	IFS* FS = (IFS*)datasource;
	return (long)FS->GetOffset();
}

OggFilter::OggFilter(void)
{
	Source = NULL;
	memset(&Vorbis, 0, sizeof(OggVorbis_File));
	Callbacks.read_func = vorbis_read;
	Callbacks.close_func = vorbis_close;
	Callbacks.tell_func = vorbis_tell;
	Callbacks.seek_func = vorbis_seek;

	memset(&Wave, 0, sizeof(WaveFile));
	memcpy(&Wave.Header.RIFF_SIG, "RIFF", 4);
	memcpy(&Wave.Header.WAVE_SIG, "WAVE", 4);
	memcpy(&Wave.fmtChunk.CHUNK_NAME, "fmt ", 4);
	Wave.fmtChunk.ChunkSize = sizeof(WaveFormatEx);
	Wave.Format.FormatTag = 1;
	Wave.Format.BitsPerSample = 16;
	memcpy(&Wave.dataChunk.CHUNK_NAME, "data", 4);

	Offset = 0;
}