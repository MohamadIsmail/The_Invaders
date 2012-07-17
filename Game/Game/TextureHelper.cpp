#include "AllIncludes.h"
#include "TextureHelper.h"
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

int LoadFileBMP(char *filename, unsigned char **pixels, int *width, int *height, bool flipvert)
{
	FILE*		file;		
	BITMAPFILEHEADER	*bmfh;			
	BITMAPINFOHEADER	*bmih;			
	BITMAPCOREHEADER	*bmch;			
	RGBTRIPLE			*os2_palette;	
	RGBQUAD				*win_palette;	
	char				*buffer;		
	unsigned char		*ptr;			
	int					bitCount;		
	int					compression;	
	int					row, col, i;	
	int					w, h;			
	file = fopen( filename, "rb" );
	if( file == NULL )
		return 0;
	fseek(file, 0, SEEK_END);
	long flen = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = new char[ flen + 1 ];
	fread(buffer, flen, 1, file);
	char *pBuff = buffer;
	fclose(file);
	bmfh = (BITMAPFILEHEADER *)pBuff;
	pBuff += sizeof( BITMAPFILEHEADER );
	printf("%c", bmfh->bfType);
	if( bmfh->bfType != BITMAP_ID )
	{
		delete [] buffer;
		return 0;
	}
	bmch = (BITMAPCOREHEADER *)pBuff;
	bmih = (BITMAPINFOHEADER *)pBuff;
	if( (bmih->biCompression < 0) || (bmih->biCompression > 3) )
	{
		pBuff += sizeof( BITMAPCOREHEADER );
		bitCount	= bmch->bcBitCount;
		compression	= BI_OS2;
		w = bmch->bcWidth;
		h = bmch->bcHeight;
	}
	else
	{
		pBuff += sizeof( BITMAPINFOHEADER );
		bitCount	= bmih->biBitCount;
		compression	= bmih->biCompression;
		w = bmih->biWidth;
		h = bmih->biHeight;
	}
	if( width )
		*width	= w;
	if( height )
		*height	= h;
	if( !pixels )
	{
		delete [] buffer;
		return (-1);
	}
	if( bitCount <= 8 )
	{
		os2_palette = (RGBTRIPLE *)pBuff;
		win_palette = (RGBQUAD *)pBuff;
		pBuff += (1 << bitCount) * (bitCount >> 3) * sizeof( unsigned char );
	}
	*pixels = new unsigned char[ w * h * 4 ];
	ptr		= &(*pixels)[0];
	pBuff = buffer + (bmfh->bfOffBits * sizeof( char ));
	switch( compression )
	{
		case BI_OS2:
		case BI_RGB:
		{
			for( row = h - 1; row >= 0; row-- )
			{
				if( flipvert )
					ptr = &(*pixels)[ row * w * 4 ];
				switch( bitCount )
				{
					case 1:
					{
						for( col = 0; col < (int)(w / 8); col++ )
						{
							unsigned char color = *((unsigned char *)(pBuff++));
							for( i = 7; i >= 0; i--, ptr += 4 )
							{
								int clrIdx = ((color & (1<<i)) > 0);
								if( compression == BI_OS2 )
								{
									ptr[0] = os2_palette[ clrIdx ].rgbtRed;
									ptr[1] = os2_palette[ clrIdx ].rgbtGreen;
									ptr[2] = os2_palette[ clrIdx ].rgbtBlue;
									ptr[3] = 255;
								}
								else
								{
									ptr[0] = win_palette[ clrIdx ].rgbRed;
									ptr[1] = win_palette[ clrIdx ].rgbGreen;
									ptr[2] = win_palette[ clrIdx ].rgbBlue;
									ptr[3] = 255;
								}
							}
						}

						break;
					}

					case 4:
					{
						for( col = 0; col < (int)(w / 2); col++, ptr += 8 )
						{
							unsigned char color = *((unsigned char *)(pBuff++));
							int clrIdx;
							if( compression == BI_OS2 )
							{
								clrIdx = (color >> 4);
								ptr[0] = os2_palette[ clrIdx ].rgbtRed;
								ptr[1] = os2_palette[ clrIdx ].rgbtGreen;
								ptr[2] = os2_palette[ clrIdx ].rgbtBlue;
								ptr[3] = 255;

								clrIdx = (color & 0x0F);
								ptr[4] = os2_palette[ clrIdx ].rgbtRed;
								ptr[5] = os2_palette[ clrIdx ].rgbtGreen;
								ptr[6] = os2_palette[ clrIdx ].rgbtBlue;
								ptr[7] = 255;
							}
							else
							{
								clrIdx = (color >> 4);
								ptr[0] = win_palette[ clrIdx ].rgbRed;
								ptr[1] = win_palette[ clrIdx ].rgbGreen;
								ptr[2] = win_palette[ clrIdx ].rgbBlue;
								ptr[3] = 255;

								clrIdx = (color & 0x0F);
								ptr[4] = win_palette[ clrIdx ].rgbRed;
								ptr[5] = win_palette[ clrIdx ].rgbGreen;
								ptr[6] = win_palette[ clrIdx ].rgbBlue;
								ptr[7] = 255;
							}
						}

						break;
					}

					case 8:
					{
						for( col = 0; col < w; col++, ptr += 4 )
						{
							unsigned char color = *((unsigned char *)(pBuff++));
							if( compression == BI_OS2 )
							{
								ptr[0] = os2_palette[ color ].rgbtRed;
								ptr[1] = os2_palette[ color ].rgbtGreen;
								ptr[2] = os2_palette[ color ].rgbtBlue;
								ptr[3] = 255;
							}
							else
							{
								ptr[0] = win_palette[ color ].rgbRed;
								ptr[1] = win_palette[ color ].rgbGreen;
								ptr[2] = win_palette[ color ].rgbBlue;
								ptr[3] = 255;
							}
						}

						break;
					}

					case 24:
					{
						for( col = 0; col < w; col++, ptr += 4 )
						{
							RGBTRIPLE *pix = (RGBTRIPLE *)pBuff;
							pBuff += sizeof( RGBTRIPLE );

							ptr[0] = pix->rgbtRed;
							ptr[1] = pix->rgbtGreen;
							ptr[2] = pix->rgbtBlue;
							ptr[3] = 255;
						}

  						break;
					}

					case 32:
					{
						for( col = 0; col < w; col++, ptr += 4 )
						{
							RGBQUAD *pix = (RGBQUAD *)pBuff;
							pBuff += sizeof( RGBQUAD );
							ptr[0] = pix->rgbRed;
							ptr[1] = pix->rgbGreen;
							ptr[2] = pix->rgbBlue;
							ptr[3] = 255;
						}

						break;
					}
				}
			}

			break;
		}

		case BI_RLE8:
		{
			for( row = h - 1; row >= 0; row-- )
			{
				if( flipvert )
					ptr = &(*pixels)[ row * w * 4 ];
				for( col = 0; col < w; /* nothing */ )
				{
					unsigned char byte1 = *((unsigned char *)(pBuff++));
					unsigned char byte2 = *((unsigned char *)(pBuff++));
					if( byte1 == RLE_COMMAND )
					{
						for( i = 0; i < byte2; i++, ptr += 4, col++ )
						{
							unsigned char color = *((unsigned char *)(pBuff++));
							ptr[0] = win_palette[ color ].rgbRed;
							ptr[1] = win_palette[ color ].rgbGreen;
							ptr[2] = win_palette[ color ].rgbBlue;
							ptr[3] = 255;
						}

						if( (byte2 % 2) == 1 )
							pBuff++;
					}
					else
					{
						for( i = 0; i < byte1; i++, ptr += 4, col++ )
						{
							ptr[0] = win_palette[ byte2 ].rgbRed;
							ptr[1] = win_palette[ byte2 ].rgbGreen;
							ptr[2] = win_palette[ byte2 ].rgbBlue;
							ptr[3] = 255;
						}        
					}
				}
			}

			break;
		}

		case BI_RLE4:
		{
			unsigned char color;
			int	bytesRead = 0;
			for( row = h - 1; row >= 0; row-- )
			{
				if( flipvert )
					ptr = &(*pixels)[ row * w * 4 ];

				for( col = 0; col < w; /* nothing */ )
				{
					unsigned char byte1 = *((unsigned char *)(pBuff++));
					unsigned char byte2 = *((unsigned char *)(pBuff++));

					bytesRead += 2;
					if( byte1 == RLE_COMMAND )
					{
						unsigned char databyte;
						for( i = 0; i < byte2; i++, ptr += 4, col++ )
						{
							if( (i % 2) == 0 )
							{
								databyte = *((unsigned char *)(pBuff++));
								bytesRead++;

								color = (databyte >> 4);	
							}
							else
							{
								color = (databyte & 0x0F);	
							}
							ptr[0] = win_palette[ color ].rgbRed;
							ptr[1] = win_palette[ color ].rgbGreen;
							ptr[2] = win_palette[ color ].rgbBlue;
							ptr[3] = 255;
						}
          
						while( (bytesRead % 2) != 0 )
						{
							pBuff++;
							bytesRead++;
						}
					}
					else
					{
						for( i = 0; i < byte1; i++, ptr += 4, col++ )
						{
							if( (i % 2) == 0 )
								color = (byte2 >> 4);	
							else
								color = (byte2 & 0x0F);	
							ptr[0] = win_palette[ color ].rgbRed;
							ptr[1] = win_palette[ color ].rgbGreen;
							ptr[2] = win_palette[ color ].rgbBlue;
							ptr[3] = 255;
						}        
					}
				}
			}

			break;
		}
	}

	delete [] buffer;
	return 1;
}

int LoadFilePCX( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert )
{
	FILE*		file;			
	PCXHEADER			*header;
	unsigned char		*data;			
	unsigned char		*ptr;			
	unsigned char		c;				
	char				*buffer;		
	int					idx = 0;		
	int					numRepeat;		
	int					i, j;			
	file = fopen( filename, "rb" );
	if( file == NULL )
		return 0;
	fseek(file, 0, SEEK_END);
	long flen = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = new char[ flen + 1 ];
	fread(buffer, flen, 1, file);
	char *pBuff = buffer;
	fclose(file);
	header = (PCXHEADER *)pBuff;
	if( (header->manufacturer	!= 10)	||
		(header->version		!= 5)	||
		(header->encoding		!= 1)	||
		(header->bitsPerPixel	!= 8) )
	{
		return 0;
	}
	header->width	= header->width	 - header->x + 1;
	header->height	= header->height - header->y + 1;
	if( width )
		*width = header->width;
	if( height )
		*height = header->height;
	if( !pixels )
	{
		delete [] buffer;
		return (-1);
	}
	data = new unsigned char[ header->width * header->height ];
	pBuff = (char *)&buffer[ 128 ];
	while( idx < (header->width * header->height) )
	{
		if( (c = *(pBuff++)) > 0xbf )
		{
			numRepeat = 0x3f & c;
			c = *(pBuff++);

			for( i = 0; i < numRepeat; i++ )
				data[ idx++ ] = c;
		}
		else
			data[ idx++ ] = c;
	}
	pBuff = &buffer[ flen - 769 ];
	if( *(pBuff++) != 12 )
	{
		delete [] buffer;
		delete [] data;
		return 0;
	}
	header->palette = (unsigned char *)pBuff;
	*pixels = new unsigned char[ header->width * header->height * 4 ];
	ptr = &(*pixels)[0];
	for( j = header->height - 1; j > 0; j-- )
	{
		if( flipvert )
			ptr = &(*pixels)[ j * header->width * 4 ];

		for( i = 0; i < header->width; i++, ptr += 4 )
		{
			int color = 3 * data[ j * header->width + i ];

			ptr[0] = (unsigned char)header->palette[ color + 0 ];
			ptr[1] = (unsigned char)header->palette[ color + 1 ];
			ptr[2] = (unsigned char)header->palette[ color + 2 ];
			ptr[3] = (unsigned char)255;
		}
	}
	delete [] data;
	return 1;
}
int LoadFileTGA( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert )
{
	FILE*	file;			
	TGAHEADER		*tgah;	
	RGBTRIPLE		*palette;
	char			*buffer;
	unsigned char	*ptr;	
	int				row, col, i;
	file = fopen( filename, "rb" );
	if( file == NULL )
		return 0;
	fseek(file, 0, SEEK_END);
	long flen = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = new char[ flen + 1 ];
	fread(buffer, flen, 1, file);
	char *pBuff = buffer;
	fclose(file);
	tgah = (TGAHEADER *)pBuff;
	pBuff += sizeof( TGAHEADER );
	if( width )
		*width = tgah->is_width;
	if( height )
		*height = tgah->is_height;
	if( !pixels )
	{
		delete [] buffer;
		return (-1);
	}
	*pixels	= new unsigned char[ tgah->is_width * tgah->is_height * 4 ];
	ptr		= &(*pixels)[0];
	if( tgah->id_lenght )
		pBuff = buffer + (tgah->id_lenght * sizeof( unsigned char ));
	if( tgah->color_map_type )
	{
		palette = (RGBTRIPLE *)pBuff;
		pBuff += tgah->cm_length * (tgah->cm_size >> 3) * sizeof( unsigned char );
	}
	switch( tgah->image_type )
	{
		case 0:
			break;
		case 1:
		case 3:
		{
			for( row = tgah->is_height - 1; row >= 0; row-- )
			{
				if( flipvert )
					ptr = &(*pixels)[ row * tgah->is_width * 4 ];
				for( col = 0; col < tgah->is_width; col++, ptr += 4 )
				{
					unsigned char color = *((unsigned char *)(pBuff++));
					ptr[0] = palette[ color ].rgbtRed;		
					ptr[1] = palette[ color ].rgbtGreen;	
					ptr[2] = palette[ color ].rgbtBlue;		
					ptr[3] = 255;							
				}
			}
			break;
		}
		case 2:
		{
			for( row = tgah->is_height - 1; row >= 0; row-- )
			{
				if( flipvert )
					ptr = &(*pixels)[ row * tgah->is_width * 4 ];
				for( col = 0; col < tgah->is_width; col++, ptr += 4 )
				{
					switch( tgah->is_pixel_depth )
					{
						case 16:
						{
							unsigned short color = *((unsigned short *)pBuff);
							pBuff += sizeof( short );
							ptr[0] = ((color & 0x7C00) >> 10) << 3;	
							ptr[1] = ((color & 0x03E0) >>  5) << 3;	
							ptr[2] = ((color & 0x001F) >>  0) << 3;	
							ptr[3] = 255;							
							break;
						}
						case 24:
						{
							RGBTRIPLE *pix = (RGBTRIPLE *)pBuff;
							pBuff += sizeof( RGBTRIPLE );
							ptr[0] = pix->rgbtRed;
							ptr[1] = pix->rgbtGreen;
							ptr[2] = pix->rgbtBlue;
							ptr[3] = 255;
							break;
						}
						case 32:
						{
							BGRAQUAD *pix = (BGRAQUAD *)pBuff;
							pBuff += sizeof( BGRAQUAD );
							ptr[0] = pix->bgraRed;
							ptr[1] = pix->bgraGreen;
							ptr[2] = pix->bgraBlue;
							ptr[3] = pix->bgraAlpha;
							break;
						}
					}
				}
			}
			break;
		}
		case 9:
		case 11:
		{
			unsigned char	packetHeader, packetSize, i;
			for( row = tgah->is_height - 1; row >= 0; row-- )
			{
				if( flipvert )
					ptr = &(*pixels)[ row * tgah->is_width * 4 ];
				for( col = 0; col < tgah->is_width; /* rien */ )
				{
					packetHeader	= *((unsigned char *)(pBuff++));
					packetSize		= 1 + (packetHeader & 0x7f);
					if( packetHeader & 0x80 )
					{
						unsigned char color = *((unsigned char *)(pBuff++));
						for( i = 0; i < packetSize; i++, ptr += 4, col++ )
						{
							ptr[0] = palette[ color ].rgbtRed;		
							ptr[1] = palette[ color ].rgbtGreen;	
							ptr[2] = palette[ color ].rgbtBlue;		
							ptr[3] = 255;							
						}
					}
					else
					{
						for( i = 0; i < packetSize; i++, ptr += 4, col++ )
						{
							unsigned char color = *((unsigned char *)(pBuff++));
							ptr[0] = palette[ color ].rgbtRed;		
							ptr[1] = palette[ color ].rgbtGreen;	
							ptr[2] = palette[ color ].rgbtBlue;		
							ptr[3] = 255;							
						}
					}
				}
			}

			break;
		}
		case 10:
		{
			unsigned char	packetHeader, packetSize;
			for( row = tgah->is_height - 1; row >= 0; row-- )
			{
				if( flipvert )
					ptr = &(*pixels)[ row * tgah->is_width * 4 ];
				for( col = 0; col < tgah->is_width; /* rien */ )
				{
					packetHeader	= *((unsigned char *)(pBuff++));
					packetSize		= 1 + (packetHeader & 0x7f);
					if( packetHeader & 0x80 )
					{
						switch( tgah->is_pixel_depth )
						{
							case 16:
							{
								unsigned short color = *((unsigned short *)pBuff);
								pBuff += sizeof( short );
								for( i = 0; i < packetSize; i++, ptr += 4, col++ )
								{
									ptr[0] = ((color & 0x7C00) >> 10) << 3;	
									ptr[1] = ((color & 0x03E0) >>  5) << 3;	
									ptr[2] = ((color & 0x001F) >>  0) << 3;	
									ptr[3] = 255;
								}

								break;
							}
							case 24:
							{
								RGBTRIPLE *pix = (RGBTRIPLE *)pBuff;
								pBuff += sizeof( RGBTRIPLE );
								for( i = 0; i < packetSize; i++, ptr += 4, col++ )
								{
									ptr[0] = pix->rgbtRed;
									ptr[1] = pix->rgbtGreen;
									ptr[2] = pix->rgbtBlue;
									ptr[3] = 255;
								}
								break;
							}
							case 32:
							{
								BGRAQUAD *pix = (BGRAQUAD *)pBuff;
								pBuff += sizeof( BGRAQUAD );
								for( i = 0; i < packetSize; i++, ptr += 4, col++ )
								{
									ptr[0] = pix->bgraRed;
									ptr[1] = pix->bgraGreen;
									ptr[2] = pix->bgraBlue;
									ptr[3] = pix->bgraAlpha;
								}
								break;
							}
						}
					}
					else
					{
						for( i = 0; i < packetSize; i++, ptr += 4, col++ )
						{
							switch( tgah->is_pixel_depth )
							{
								case 16:
								{
									unsigned short color = *((unsigned short *)pBuff);
									pBuff += sizeof( short );
									ptr[0] = ((color & 0x7C00) >> 10) << 3;	
									ptr[1] = ((color & 0x03E0) >>  5) << 3;	
									ptr[2] = ((color & 0x001F) >>  0) << 3;	
									ptr[3] = 255;							
									break;
								}
								case 24:
								{
									RGBTRIPLE *pix = (RGBTRIPLE *)pBuff;
									pBuff += sizeof( RGBTRIPLE );
									ptr[0] = pix->rgbtRed;
									ptr[1] = pix->rgbtGreen;
									ptr[2] = pix->rgbtBlue;
									ptr[3] = 255;
									break;
								}
								case 32:
								{
									BGRAQUAD *pix = (BGRAQUAD *)pBuff;
									pBuff += sizeof( BGRAQUAD );
									ptr[0] = pix->bgraRed;
									ptr[1] = pix->bgraGreen;
									ptr[2] = pix->bgraBlue;
									ptr[3] = pix->bgraAlpha;

									break;
								}
							}
						}
					}
				}
			}
			break;
		}
		default:
		{
			delete [] pixels;
			delete [] buffer;
			return 0;
		}
	}
	delete [] buffer;
	return 1;
}
unsigned int LoadGLTexture(char *filename)
{
	unsigned int	id = 0;
	unsigned char	*texels = 0;
	int				width, height;
	int				success = 0;

	if( strstr( filename, ".bmp" ) || strstr( filename, ".BMP" ) )
		success = LoadFileBMP( filename, &texels, &width, &height, true );
	if( strstr( filename, ".tga" ) || strstr( filename, ".TGA" ) )
		success = LoadFileTGA( filename, &texels, &width, &height, true );
	if( strstr( filename, ".pcx" ) || strstr( filename, ".PCX" ) )
		success = LoadFilePCX( filename, &texels, &width, &height, true );
	if( success > 0 )
	{
		glGenTextures( 1, &id );
		glBindTexture( GL_TEXTURE_2D, id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, texels );
	}
	else
	{
		id = NULL;
	}
	if( texels )
		delete [] texels;
	return id;
}
unsigned int LoadTexture(char *fileName)
{
	char filename[256];
	int counter = -1;
	for(int i = 0 ; i < 256 ; i++)
	{
		if(counter != -1)
		{
			filename[counter] = fileName[i];
			counter++;
		}
		if(fileName[i] == ',')
		{
			counter++;
		}
		
	}
	if(counter == -1)
		for(int i = 0 ; i < 256 ; i++)
		{
				filename[i] = fileName[i];
		}
	unsigned int	id = 0;
	unsigned char	*texels = 0;
	int				width, height;
	int				success = 0;

	if( strstr( filename, ".bmp" ) || strstr( filename, ".BMP" ) )
		success = LoadFileBMP( filename, &texels, &width, &height, true );
	if( strstr( filename, ".tga" ) || strstr( filename, ".TGA" ) )
		success = LoadFileTGA( filename, &texels, &width, &height, true );
	if( strstr( filename, ".pcx" ) || strstr( filename, ".PCX" ) )
		success = LoadFilePCX( filename, &texels, &width, &height, true );
	if( success > 0 )
	{
		glGenTextures( 1, &id );
		glBindTexture( GL_TEXTURE_2D, id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, texels );
	}
	else
	{
		id = NULL;
	}
	if( texels )
		delete [] texels;
	return id;
}