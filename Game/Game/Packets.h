class Packet
{
public:
	Vector3 P;
	float Value;
	int texture;
	float Angle;
	bool isTaken;
	Packet(const Vector3 &pos, float Val) {
		P = pos;
		Value = Val;
		Angle = 0;
		isTaken = false;
	}
	void Update()
	{
		Angle += 0.5;
		glLoadIdentity();
		glTranslatef(P.x,P.y,P.z);
		glRotatef(Angle,0,1,0);
		Render();
	}
	void Render() const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
		glScalef(2,2,2);
		glPushMatrix();
		{
			glBegin(GL_POLYGON);
			{
				glTexCoord2d(0,0);
				glVertex3f(0,0,0);
				glTexCoord2d(1,0);
				glVertex3f(1,0,0);
				glTexCoord2d(1,1);
				glVertex3f(1,1,0);
				glTexCoord2d(0,1);
				glVertex3f(0,1,0);
			}
			glEnd();
			glBegin(GL_POLYGON);
			{
				glTexCoord2d(0,0);
				glVertex3f(0,0,1);
				glTexCoord2d(1,0);
				glVertex3f(1,0,1);
				glTexCoord2d(1,1);
				glVertex3f(1,1,1);
				glTexCoord2d(0,1);
				glVertex3f(0,1,1);
			}
			glEnd();
			glBegin(GL_POLYGON);
			{
				glTexCoord2d(0,0);
				glVertex3f(0,0,0);
				glTexCoord2d(1,0);
				glVertex3f(1,0,0);
				glTexCoord2d(1,1);
				glVertex3f(1,0,1);
				glTexCoord2d(0,1);
				glVertex3f(0,0,1);
			}
			glEnd();
			glBegin(GL_POLYGON);
			{
				glTexCoord2d(0,0);
				glVertex3f(0,1,0);
				glTexCoord2d(1,0);
				glVertex3f(1,1,0);
				glTexCoord2d(1,1);
				glVertex3f(1,1,1);
				glTexCoord2d(0,1);
				glVertex3f(0,1,1);
			}
			glEnd();
			glBegin(GL_POLYGON);
			{
				glTexCoord2d(0,0);
				glVertex3f(0,0,0);
				glTexCoord2d(1,0);
				glVertex3f(0,1,0);
				glTexCoord2d(1,1);
				glVertex3f(0,1,1);
				glTexCoord2d(0,1);
				glVertex3f(0,0,1);
			}
			glEnd();
			glBegin(GL_POLYGON);
			{
				glTexCoord2d(0,0);
				glVertex3f(1,0,0);
				glTexCoord2d(1,0);
				glVertex3f(1,1,0);
				glTexCoord2d(1,1);
				glVertex3f(1,1,1);
				glTexCoord2d(0,1);
				glVertex3f(1,0,1);
			}
			glEnd();
		}
		glPopMatrix();
	}

	AABoundingBox GetAABB() const
	{return AABoundingBox(P, Vector3(10, 10, 10));}
};

class HealthPacket : public Packet
{
public:
	HealthPacket(const Vector3 &pos, float Val):Packet(pos,Val){texture = LoadGLTexture("images\\packets\\HealthPack.bmp");}	
};

class ManaPacket : public Packet
{
public:
	ManaPacket(const Vector3 &pos, float Val):Packet(pos,Val){texture = LoadGLTexture("images\\packets\\ManaPack.bmp");}
};

class AmmoPacket : public Packet
{
public:
	AmmoPacket(const Vector3 &pos, float Val):Packet(pos,Val){texture = LoadGLTexture("images\\packets\\AmmoPack.bmp");}
};
