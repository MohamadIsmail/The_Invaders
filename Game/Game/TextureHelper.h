#pragma once
#ifndef		__TEXTURES_H_
#define		__TEXTURES_H_


#define			BITMAP_ID			('B' + ('M'<<8))
#define			RLE_COMMAND			0
#define			RLE_ENDOFLINE		0
#define			RLE_ENDOFBITMAP		1
#define			RLE_DELTA			2

#define			BI_OS2				-1

int LoadFileBMP(char *filename, unsigned char **pixels, int *width, int *height, bool flipvert);
#pragma warning( disable : 4103 ) 
#pragma pack(1)
typedef 


struct tagPCXHEADER
{
	unsigned char	manufacturer;		
	unsigned char	version;			
	unsigned char	encoding;			
	unsigned char	bitsPerPixel;		

	unsigned short	x, y;				
	unsigned short	width, height;		
	unsigned short	horzRes, vertRes;	

	unsigned char	*palette;			
	unsigned char	reserved;			
	unsigned char	numColorPlanes;		

	unsigned short	bytesPerScanLine;	
	unsigned short	paletteType;		
	unsigned short	horzSize, vertSize;	

	unsigned char	padding[54];		

} PCXHEADER, *PPCXHEADER;

#pragma pack(4)
int LoadFilePCX( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert );

#pragma warning( disable : 4103 ) 
#pragma pack(1)
typedef struct tagTGAHEADER
{
	unsigned char	id_lenght;			
	unsigned char	color_map_type;		
	unsigned char	image_type;			

	short int		cm_first_entry;		
	short int		cm_length;			
	unsigned char	cm_size;			

	short int		is_xorigin;			
	short int		is_yorigin;			

	short int		is_width;			
	short int		is_height;			

	unsigned char	is_pixel_depth;		
	unsigned char	is_image_descriptor;
} TGAHEADER, *PTGAHEADER;
#pragma pack(4)
typedef struct tagBGRAQUAD			
{
	unsigned char	bgraBlue;		
	unsigned char	bgraGreen;		
	unsigned char	bgraRed;		
	unsigned char	bgraAlpha;		

} BGRAQUAD, *PBGRAQUAD;
int LoadFileTGA( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert );
unsigned int LoadTexture(char *filename);
unsigned int LoadGLTexture(char *filename);

#endif 