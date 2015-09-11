#ifndef _MSS_
#define _MSS_

typedef int HTIMER;

struct M3D_OBJECT
{
	uInt junk;
};

typedef M3D_OBJECT* M3D_SAMPLE;

typedef uInt M3D_PROVIDER;
typedef uInt M3D_ATTRIB;
typedef int M3D_RESULT;

#ifdef _GOTHIC2
#define G32 float
#define G32_SCALE 1.0f
#else
#define G32 int
#define G32_SCALE 127.0f
#endif

enum M3D_ENTRY_TYPE
{
   M3D_FUNCTION = 0,
   M3D_ATTRIBUTE = 1,
   M3D_PREFERENCE = 2
};

enum M3D_DATA_SUBTYPE
{
   M3D_NONE = 0, 
   M3D_CUSTOM,
   M3D_DEC,
   M3D_HEX,
   M3D_FLOAT,
   M3D_PERCENT,
   M3D_BOOL,
   M3D_STRING
};

struct M3D_INTERFACE_ENTRY
{
   M3D_ENTRY_TYPE   type;
   const char*		entry_name;
   uInt             token;
   M3D_DATA_SUBTYPE subtype;
};

struct M3D_SOUNDINFO 
{
  int format;
  void const* data_ptr;
  uInt data_len;
  uInt rate;
  int bits;
  int channels;
  uInt samples;
  uInt block_size;
  void const* initial_ptr;
};

typedef void (__stdcall* MSS_TIMER_CALLBACK) (uInt user);
typedef void (__stdcall* MSS_SAMPLE_CALLBACK)(M3D_SAMPLE sample);

M3D_PROVIDER __stdcall RIB_alloc_provider_handle(uInt module);
M3D_PROVIDER __stdcall RIB_provider_library_handle(void);
M3D_RESULT __stdcall RIB_register_interface(M3D_PROVIDER provider, const char* interface_name, int entry_count, const M3D_INTERFACE_ENTRY* rlist);
M3D_RESULT __stdcall RIB_unregister_interface(M3D_PROVIDER provider, const char* interface_name, int entry_count, const M3D_INTERFACE_ENTRY* rlist);
HTIMER  __stdcall  AIL_register_timer(MSS_TIMER_CALLBACK cb);
uInt __stdcall AIL_set_timer_user(HTIMER timer, uInt user);
void __stdcall AIL_set_timer_frequency(HTIMER timer, uInt hertz);
void __stdcall AIL_start_timer(HTIMER timer);
void __stdcall AIL_stop_timer(HTIMER timer);
void __stdcall AIL_release_timer_handle(HTIMER timer);
int __stdcall AIL_get_preference(uInt number);

#define PROVIDER_NAME    (-100)
#define PROVIDER_VERSION (-101)

#define SMP_FREE			0x0001
#define SMP_DONE			0x0002
#define SMP_PLAYING			0x0004
#define SMP_STOPPED			0x0008

#define M3D_NOERR			0
#define M3D_ALREADY_STARTED	2
#define M3D_NOT_INIT		8

#endif