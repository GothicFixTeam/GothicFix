#ifndef _VDF_STRUCT_
#define _VDF_STRUCT_

typedef unsigned int uInt;

#pragma pack(push,1)

struct VdfTime  
{
	unsigned Sec   : 5; /* *2 */  
	unsigned Min   : 6;   
	unsigned Hour  : 5;  
	unsigned Day   : 5;   
	unsigned Month : 4;   
	unsigned Year  : 7; /* 1980+ */
};

struct VdfHeader
{
char Comment[256];
char Signature[16];
uInt NumEntries;
uInt NumFiles;
VdfTime Timestamp;
uInt DataSize;
uInt RootCatOffset;
uInt Version; // ~Always = 0x50, may be a version
};

#define VDF_SIGNATURE_G1 "PSVDSC_V2.00\r\n\r\n"
#define VDF_SIGNATURE_G2 "PSVDSC_V2.00\n\r\n\r"

#define VDF_ENTRY_DIR 0x80000000
#define VDF_ENTRY_LAST 0x40000000

struct VdfEntryInfo
{
char Name[64];
uInt JumpTo; // Dirs = child entry's number, Files = data offset
uInt Size;
uInt Type; // = 0x00000000 for files or VDFS_ENTRY_DIR, may be bitmasked by VDFS_ENTRY_LAST
uInt Attrib; // 20 = A;
};

#pragma pack(pop)

#endif