class Particle
{
public:
	bool	rainbow;				// Rainbow Mode?
	char color;
	float	slowdown;				// Slow Down Particles
	float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
	float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)

	GLuint	loop;						// Misc Loop Variable
	GLuint	col;						// Current Color Selection
	GLuint	delay;						// Rainbow Effect Delay
	GLuint	texture;
	int LifeTime;
	bool isfirst;
	int currentTime;
	bool Done;
	Particle(){Done = false; currentTime = 400;LifeTime = 300;yspeed = 10;rainbow = true;slowdown=1.0f;isfirst = true;}
	typedef struct						// Create A Structure For Particle
	{
		bool	active;					// Active (Yes/No)
		float	life;					// Particle Life
		float	fade;					// Fade Speed
		float	r;						// Red Value
		float	g;						// Green Value
		float	b;						// Blue Value
		float	x;						// X Position
		float	y;						// Y Position
		float	z;						// Z Position
		float	xi;						// X Direction
		float	yi;						// Y Direction
		float	zi;						// Z Direction
		float	xg;						// X Gravity
		float	yg;						// Y Gravity
		float	zg;						// Z Gravity
	}
	particles;	
	particles particle[1000];
	void initialize()
	{
		GLfloat colors[3];
		switch(color)
		{
		case 'w':
			colors[0] = 1;
			colors[1] = 1;
			colors[2] = 1;
			break;
		case 'r':
			colors[0] = 1;
			colors[1] = 0;
			colors[2] = 0;
			break;
		case 'b':
			colors[0] = 0;
			colors[1] = 0;
			colors[2] = 1;
			break;
		case 'g':
			colors[0] = 0;
			colors[1] = 1;
			colors[2] = 0;
			break;
		case 'y':
			colors[0] = 1;
			colors[1] = 1;
			colors[2] = 0;
			break;
		}
		texture = LoadGLTexture("images\\particles\\Particle.bmp");							// Disable Depth Testing
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture);
		for (loop=0;loop<1000;loop++)				// Initials All The Textures
		{
			particle[loop].active=true;								// Make All The Particles Active
			particle[loop].life=1.0f;								// Give All The Particles Full Life
			particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
			particle[loop].r=colors[0];	// Select Red Rainbow Color
			particle[loop].g=colors[1];	// Select Red Rainbow Color
			particle[loop].b=colors[2];	// Select Red Rainbow Color
			particle[loop].xi=float((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
			particle[loop].yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
			particle[loop].zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
			particle[loop].xg=0.0f;									// Set Horizontal Pull To Zero
			particle[loop].yg=0.8f;								// Set Vertical Pull Downward
			particle[loop].zg=0.0f;									// Set Pull On Z Axis To Zero
		}
	}
	void StartAgain(char color)
	{
		isfirst = true;
		Done = false;
		currentTime = 0;
		this->color = color;
	}
	void Draw(Vector3 P,float Angle)
	{
		if(currentTime > LifeTime)
		{
			Done = true;
			return;
		}
		currentTime++;
		glLoadIdentity();		
		if(isfirst)
		{
			initialize();
			isfirst = false;
		}
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture);
		GLfloat colors[3];
		switch(color)
		{
		case 'w':
			colors[0] = 1;
			colors[1] = 1;
			colors[2] = 1;
			break;
		case 'r':
			colors[0] = 1;
			colors[1] = 0;
			colors[2] = 0;
			break;
		case 'b':
			colors[0] = 0;
			colors[1] = 0;
			colors[2] = 1;
			break;
		case 'g':
			colors[0] = 0;
			colors[1] = 1;
			colors[2] = 0;
			break;
		case 'y':
			colors[0] = 1;
			colors[1] = 1;
			colors[2] = 0;
			break;
		}
		// Reset The ModelView Matrix
		glTranslatef(P.x,P.y,P.z);
		glRotatef(Angle,0,1,0);
		for (loop=0;loop<1000;loop++)					// Loop Through All The Particles
		{
			if (particle[loop].active)							// If The Particle Is Active
			{
				float x=particle[loop].x;						// Grab Our Particle X Position
				float y=particle[loop].y;						// Grab Our Particle Y Position
				float z=particle[loop].z;					// Particle Z Pos + Zoom

				// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
				glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

				glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
				glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
				glEnd();										// Done Building Triangle Strip

				particle[loop].x+=particle[loop].xi/(slowdown*1000);// Move On The X Axis By X Speed
				particle[loop].y+=particle[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
				particle[loop].z+=particle[loop].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

				particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
				particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
				particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
				particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

				if (particle[loop].life<0.0f)					// If Particle Is Burned Out
				{
					particle[loop].life=1.0f;					// Give It New Life
					particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
					particle[loop].x=0.0f;						// Center On X Axis
					particle[loop].y=0.0f;						// Center On Y Axis
					particle[loop].z=0.0f;						// Center On Z Axis
					particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
					particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
					particle[loop].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
					particle[loop].r=colors[0];			// Select Red From Color Table
					particle[loop].g=colors[1];			// Select Green From Color Table
					particle[loop].b=colors[2];			// Select Blue From Color Table
				}
			}
		}
		glColor3f(1,1,1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
	}
};