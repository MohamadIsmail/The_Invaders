#ifndef _MD3_H
#define _MD3_H

#include"main.h"

#define LegConvertor 7
#define kLower	0			
#define kUpper	1			
#define kHead	2			
#define kWeapon	3

enum TORSO
{
	BOTH_DEATH1 = 0,		
	BOTH_DEAD1,				
	BOTH_DEATH2,			
	BOTH_DEAD2,				
	BOTH_DEATH3,			
	BOTH_DEAD3,			
	TORSO_GESTURE,			
	TORSO_ATTACK,			
	TORSO_ATTACK2,			
	TORSO_DROP,				
	TORSO_RAISE,			
	TORSO_STAND,			
	TORSO_STAND2,
	LEGS_WALKCR,
	LEGS_WALK,				
	LEGS_RUN,				
	LEGS_BACK,				
	LEGS_SWIM,				
	LEGS_JUMP,				
	LEGS_LAND,				
	LEGS_JUMPB,				
	LEGS_LANDB,				
	LEGS_IDLE,				
	LEGS_IDLECR,			
	LEGS_TURN,				
	MAX_ANIMATIONS			
} ;
//6 walkcr
//7 walk
//8 run
//enum LEGS
//{
//	LEGS_DEATH1 = 0,		
//	LEGS_DEAD1,				
//	LEGS_DEATH2,			
//	LEGS_DEAD2,				
//	LEGS_DEATH3,			
//	LEGS_DEAD3,			
//	LEGS_WALKCR
//};
struct tMd3Header
{ 
	char	fileID[4];					
	int		version;					
	char	strFile[68];				
	int		numFrames;					
	int		numTags;					
	int		numMeshes;					
	int		numMaxSkins;				
	int		headerSize;					
	int		tagStart;					
	int		tagEnd;						
	int		fileSize;					
};
struct tMd3MeshInfo
{
	char	meshID[4];					
	char	strName[68];				
	int		numMeshFrames;				
	int		numSkins;					
	int     numVertices;				
	int		numTriangles;				
	int		triStart;					
	int		headerSize;					
	int     uvStart;					
	int		vertexStart;				
	int		meshSize;					
};

struct tMd3Tag
{
	char		strName[64];			
	CVector3	vPosition;				
	float		rotation[3][3];			
};
struct tMd3Bone
{
	float	mins[3];					
	float	maxs[3];					
	float	position[3];				
	float	scale;						
	char	creator[16];				
};

struct tMd3Triangle
{
   signed short	 vertex[3];				
   unsigned char normal[2];				
};


struct tMd3Face
{
   int vertexIndices[3];				
};


struct tMd3TexCoord
{
   float textureCoord[2];
};

struct tMd3Skin 
{
	char strName[68];
};

class CLoadMD3
{

public:

	CLoadMD3();								
	bool ImportMD3(t3DModel *pModel, char *strFileName);
	bool LoadSkin(t3DModel *pModel, LPSTR strSkin);
	bool LoadShader(t3DModel *pModel, LPSTR strShader);

private:


	void ReadMD3Data(t3DModel *pModel);
	void ConvertDataStructures(t3DModel *pModel, tMd3MeshInfo meshHeader);
	void CleanUp();
	FILE *m_FilePointer;

	tMd3Header				m_Header;			

	tMd3Skin				*m_pSkins;			
	tMd3TexCoord			*m_pTexCoords;		
	tMd3Face				*m_pTriangles;		
	tMd3Triangle			*m_pVertices;		
	tMd3Bone				*m_pBones;			
};
class CModelMD3
{

public:

	CModelMD3();
	~CModelMD3();
	bool LoadModel(LPSTR strPath);

	bool LoadWeapon(LPSTR strPath, LPSTR strModel);
	bool Load(LPSTR strPath, LPSTR strModel);

	void LinkModel(t3DModel *pModel, t3DModel *pLink, LPSTR strTagName);


	void SetTorsoAnimation(LPSTR strAnimation);
	void SetTorsoAnimation(int AnimationNumber);
	void SetLegsAnimation(LPSTR strAnimation);
	void SetLegsAnimation(int AnimationNumber);
	void DrawModel();
	void Draw();

	void DestroyModel(t3DModel *pModel);
	bool UpdateLowerModel();
	bool UpdateUpperModel();
	bool UpdateUpperModel(int);
	int GetTorsoCurrentAnimation();
	int GetLegsCurrentAnimation();

	t3DModel *GetModel(int whichPart);
	
private:
	void LoadModelTextures(t3DModel *pModel, LPSTR strPath);

	bool LoadAnimations(LPSTR strConfigFile);

	bool UpdateModel(t3DModel *pModel,bool loop);
	void SetCurrentTime(t3DModel *pModel);

	void DrawLink(t3DModel *pModel);
	void RenderModel(t3DModel *pModel);
	UINT m_Textures[MAX_TEXTURES];	

	vector<string> strTextures;
	t3DModel m_Head;
	t3DModel m_Upper;
	t3DModel m_Lower;
	t3DModel m_Weapon;
};


class CQuaternion 
{

public:

	CQuaternion() { x = y = z = 0.0f;   w = 1.0f;  }
	CQuaternion(float X, float Y, float Z, float W) 
	{ 
		x = X;		y = Y;		z = Z;		w = W;
	}

	void CreateMatrix(float *pMatrix);
	void CreateFromMatrix(float *pMatrix, int rowColumnCount);

	CQuaternion Slerp(CQuaternion &q1, CQuaternion &q2, float t);

private:

	float x, y, z, w;
};


#endif
