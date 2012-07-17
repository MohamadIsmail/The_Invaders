#ifndef TEXTHELPER_H_
#define TEXTHELPER_H_

class TextHelper
{
public:

	/* These functions are taken from:
	 * http://www.lighthouse3d.com/tutorials/glut-tutorial/bitmap-fonts/
	 * Valid fonts are:
	 * GLUT_BITMAP_8_BY_13				GLUT_BITMAP_9_BY_15
	 * GLUT_BITMAP_TIMES_ROMAN_10		GLUT_BITMAP_TIMES_ROMAN_24
	 * GLUT_BITMAP_HELVETICA_10		GLUT_BITMAP_HELVETICA_12			GLUT_BITMAP_HELVETICA_18
	 */
	static float MeasureStringWidth(void*, char*);
	static void DrawString(float,float,void*,char*);
	static void DrawStringAnim(float,float,void*,char*);
	static void DrawCenteredString(float,void*,char*);
};

#endif