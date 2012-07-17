#ifndef DRAWABLE_H_
#define DRAWABLE_H_


class IDrawable
{
protected:
	GLuint texture;
	virtual void DrawCanvase()= 0;
};

#endif