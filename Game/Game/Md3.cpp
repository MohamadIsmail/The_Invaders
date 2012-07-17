#include "TextureHelper.h"
#include "Md3.h"



void CQuaternion::CreateMatrix(float *pMatrix)
{
	if(!pMatrix) return;
	
	pMatrix[ 0] = 1.0f - 2.0f * ( y * y + z * z );  
	pMatrix[ 1] = 2.0f * ( x * y - w * z );  
	pMatrix[ 2] = 2.0f * ( x * z + w * y );  
	pMatrix[ 3] = 0.0f;  
	pMatrix[ 4] = 2.0f * ( x * y + w * z );  
	pMatrix[ 5] = 1.0f - 2.0f * ( x * x + z * z );  
	pMatrix[ 6] = 2.0f * ( y * z - w * x );  
	pMatrix[ 7] = 0.0f;  
	pMatrix[ 8] = 2.0f * ( x * z - w * y );  
	pMatrix[ 9] = 2.0f * ( y * z + w * x );  
	pMatrix[10] = 1.0f - 2.0f * ( x * x + y * y );  
	pMatrix[11] = 0.0f;  
	pMatrix[12] = 0;  
	pMatrix[13] = 0;  
	pMatrix[14] = 0;  
	pMatrix[15] = 1.0f;
}

void CQuaternion::CreateFromMatrix(float *pTheMatrix, int rowColumnCount)
{
	if(!pTheMatrix || ((rowColumnCount != 3) && (rowColumnCount != 4))) return;
	float *pMatrix = pTheMatrix;

	float m4x4[16] = {0};

	if(rowColumnCount == 3)
	{
		m4x4[0]  = pTheMatrix[0];	m4x4[1]  = pTheMatrix[1];	m4x4[2]  = pTheMatrix[2];
		m4x4[4]  = pTheMatrix[3];	m4x4[5]  = pTheMatrix[4];	m4x4[6]  = pTheMatrix[5];
		m4x4[8]  = pTheMatrix[6];	m4x4[9]  = pTheMatrix[7];	m4x4[10] = pTheMatrix[8];
		m4x4[15] = 1;
		pMatrix = &m4x4[0];
	}
	float diagonal = pMatrix[0] + pMatrix[5] + pMatrix[10] + 1;
	float scale = 0.0f;
	if(diagonal > 0.00000001)
	{
		scale = float(sqrt(diagonal ) * 2);
		x = ( pMatrix[9] - pMatrix[6] ) / scale;
		y = ( pMatrix[2] - pMatrix[8] ) / scale;
		z = ( pMatrix[4] - pMatrix[1] ) / scale;
		w = 0.25f * scale;
	}
	else 
	{
		if ( pMatrix[0] > pMatrix[5] && pMatrix[0] > pMatrix[10] )  
		{	
			scale  = (float)sqrt( 1.0f + pMatrix[0] - pMatrix[5] - pMatrix[10] ) * 2.0f;
			x = 0.25f * scale;
			y = (pMatrix[4] + pMatrix[1] ) / scale;
			z = (pMatrix[2] + pMatrix[8] ) / scale;
			w = (pMatrix[9] - pMatrix[6] ) / scale;	
		} 
		else if ( pMatrix[5] > pMatrix[10] ) 
		{
			scale  = (float)sqrt( 1.0f + pMatrix[5] - pMatrix[0] - pMatrix[10] ) * 2.0f;
			x = (pMatrix[4] + pMatrix[1] ) / scale;
			y = 0.25f * scale;
			z = (pMatrix[9] + pMatrix[6] ) / scale;
			w = (pMatrix[2] - pMatrix[8] ) / scale;
		} 
		else 
		{	
			scale  = (float)sqrt( 1.0f + pMatrix[10] - pMatrix[0] - pMatrix[5] ) * 2.0f;
			x = (pMatrix[2] + pMatrix[8] ) / scale;
			y = (pMatrix[9] + pMatrix[6] ) / scale;
			z = 0.25f * scale;
			w = (pMatrix[4] - pMatrix[1] ) / scale;
		}
	}
}

CQuaternion CQuaternion::Slerp(CQuaternion &q1, CQuaternion &q2, float t)
{
	CQuaternion qInterpolated;

	if(q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w) 
		return q1;
	float result = (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
	if(result < 0.0f)
	{
		q2 = CQuaternion(-q2.x, -q2.y, -q2.z, -q2.w);
		result = -result;
	}
	float scale0 = 1 - t, scale1 = t;
	if(1 - result > 0.1f)
	{
		float theta = (float)acos(result);
		float sinTheta = (float)sin(theta);
		scale0 = (float)sin( ( 1 - t ) * theta) / sinTheta;
		scale1 = (float)sin( ( t * theta) ) / sinTheta;
	}	

	qInterpolated.x = (scale0 * q1.x) + (scale1 * q2.x);
	qInterpolated.y = (scale0 * q1.y) + (scale1 * q2.y);
	qInterpolated.z = (scale0 * q1.z) + (scale1 * q2.z);
	qInterpolated.w = (scale0 * q1.w) + (scale1 * q2.w);
	return qInterpolated;
}

bool IsInString(string strString, string strSubString)
{
	if(strString.length() <= 0 || strSubString.length() <= 0) return false;

	unsigned int index = strString.find(strSubString);

	if(index >= 0 && index < strString.length())
		return true;

	return false;
}

CModelMD3::CModelMD3()
{
	memset(&m_Head,  0, sizeof(t3DModel));
	memset(&m_Upper, 0, sizeof(t3DModel));
	memset(&m_Lower, 0, sizeof(t3DModel));
	memset(&m_Weapon, 0, sizeof(t3DModel));
}

CModelMD3::~CModelMD3()
{
	DestroyModel(&m_Head);
	DestroyModel(&m_Upper);
	DestroyModel(&m_Lower);
	DestroyModel(&m_Weapon);
}	

void CModelMD3::DestroyModel(t3DModel *pModel)
{
	for(int i = 0; i < pModel->numOfObjects; i++)
	{
		if(pModel->pObject[i].pFaces)		delete [] pModel->pObject[i].pFaces;
		if(pModel->pObject[i].pNormals)		delete [] pModel->pObject[i].pNormals;
		if(pModel->pObject[i].pVerts)		delete [] pModel->pObject[i].pVerts;
		if(pModel->pObject[i].pTexVerts)	delete [] pModel->pObject[i].pTexVerts;
	}

	if(pModel->pTags)		delete [] pModel->pTags;
	if(pModel->pLinks)		free(pModel->pLinks);
}
	
t3DModel *CModelMD3::GetModel(int whichPart)
{
	if(whichPart == kLower) 
		return &m_Lower;
	if(whichPart == kUpper) 
		return &m_Upper;
	if(whichPart == kHead) 
		return &m_Head;
	return &m_Weapon;
}

bool CModelMD3::LoadModel(LPSTR strPath)
{
	char strLowerModel[255] = {0};
	char strUpperModel[255] = {0};
	char strHeadModel[255]  = {0};
	char strLowerSkin[255]  = {0};
	char strUpperSkin[255]  = {0};	
	char strHeadSkin[255]   = {0};	
	CLoadMD3 loadMd3;				
	if(!strPath) return false;
	sprintf(strLowerModel, "%s\\lower.md3", strPath);
	sprintf(strUpperModel, "%s\\upper.md3", strPath);
	sprintf(strHeadModel,  "%s\\head.md3",  strPath);
	sprintf(strLowerSkin, "%s\\lower.skin", strPath);
	sprintf(strUpperSkin, "%s\\upper.skin", strPath);
	sprintf(strHeadSkin,  "%s\\head.skin",  strPath);
	if(!loadMd3.ImportMD3(&m_Head,  strHeadModel))
	{
		MessageBox(NULL, "Unable to load the HEAD model!", "Error", MB_OK);
		return false;
	}

	if(!loadMd3.ImportMD3(&m_Upper, strUpperModel))		
	{
		MessageBox(NULL, "Unable to load the UPPER model!", "Error", MB_OK);
		return false;
	}

	if(!loadMd3.ImportMD3(&m_Lower, strLowerModel))
	{
		MessageBox(NULL, "Unable to load the LOWER model!", "Error", MB_OK);
		return false;
	}

	if(!loadMd3.LoadSkin(&m_Lower, strLowerSkin))
	{
		MessageBox(NULL, "Unable to load the LOWER skin!", "Error", MB_OK);
		return false;
	}

	if(!loadMd3.LoadSkin(&m_Upper, strUpperSkin))
	{
		MessageBox(NULL, "Unable to load the UPPER skin!", "Error", MB_OK);
		return false;
	}

	if(!loadMd3.LoadSkin(&m_Head,  strHeadSkin))
	{
		MessageBox(NULL, "Unable to load the HEAD skin!", "Error", MB_OK);
		return false;
	}

	LoadModelTextures(&m_Lower, strPath);
	LoadModelTextures(&m_Upper, strPath);
	LoadModelTextures(&m_Head,  strPath);
	char strConfigFile[255] = {0};	
	sprintf(strConfigFile,  "%s\\animation.cfg",  strPath);
	if(!LoadAnimations(strConfigFile))
	{
		MessageBox(NULL, "Unable to load the Animation Config File!", "Error", MB_OK);
		return false;
	}
	LinkModel(&m_Lower, &m_Upper, "tag_torso");
	LinkModel(&m_Upper, &m_Head, "tag_head");
	return true;
}

bool CModelMD3::LoadWeapon(LPSTR strPath, LPSTR strModel)
{
	char strWeaponModel[255]  = {0};	
	char strWeaponShader[255] = {0};	
	CLoadMD3 loadMd3;					
	if(!strPath || !strModel) return false;
	sprintf(strWeaponModel, "%s\\%s.md3", strPath, strModel);
	if(!loadMd3.ImportMD3(&m_Weapon,  strWeaponModel))
	{
		MessageBox(NULL, "Unable to load the WEAPON model!", "Error", MB_OK);
		return false;
	}

	sprintf(strWeaponShader, "%s\\%s.shader", strPath, strModel);
	if(!loadMd3.LoadShader(&m_Weapon, strWeaponShader))
	{
		MessageBox(NULL, "Unable to load the SHADER file!", "Error", MB_OK);
		return false;
	}
	LoadModelTextures(&m_Weapon, strPath);
	LinkModel(&m_Upper, &m_Weapon, "tag_weapon");
		
	return true;
}

bool CModelMD3::Load(LPSTR strPath, LPSTR strModel)
{
	char strWeaponModel[255]  = {0};	
	char strWeaponShader[255] = {0};	
	CLoadMD3 loadMd3;					
	if(!strPath || !strModel) return false;
	sprintf(strWeaponModel, "%s\\%s.md3", strPath, strModel);
	if(!loadMd3.ImportMD3(&m_Weapon,  strWeaponModel))
	{
		MessageBox(NULL, "Unable to load the WEAPON model!", "Error", MB_OK);
		return false;
	}

	sprintf(strWeaponShader, "%s\\%s.shader", strPath, strModel);
	if(!loadMd3.LoadShader(&m_Weapon, strWeaponShader))
	{
		MessageBox(NULL, "Unable to load the SHADER file!", "Error", MB_OK);
		return false;
	}
	LoadModelTextures(&m_Weapon, strPath);	
	return true;
}

void CModelMD3::LoadModelTextures(t3DModel *pModel, LPSTR strPath)
{
	for(int i = 0; i < pModel->numOfMaterials; i++)
	{
		if(strlen(pModel->pMaterials[i].strFile) > 0)
		{
			bool bNewTexture = true;
			for(unsigned int j = 0; j < strTextures.size(); j++)
			{
				if(!strcmp(pModel->pMaterials[i].strFile, strTextures[j].c_str()) )
				{
					bNewTexture = false;
					pModel->pMaterials[i].texureId = j;
				}
			}

			if(bNewTexture == false) continue;			
			char strFullPath[255] = {0};
			sprintf(strFullPath, "%s\\%s", strPath, pModel->pMaterials[i].strFile);
			m_Textures[strTextures.size()] = LoadTexture(strFullPath);
			pModel->pMaterials[i].texureId = strTextures.size();
			strTextures.push_back(pModel->pMaterials[i].strFile);
		}
	}
}
bool CModelMD3::LoadAnimations(LPSTR strConfigFile)
{
	tAnimationInfo animations[MAX_ANIMATIONS] = {0};

	ifstream fin(strConfigFile);
	if( fin.fail() )
	{
		return false;
	}

	string strWord = "";				
	string strLine = "";				
	int currentAnim = 0;				
	int torsoOffset = 0;				
	while( fin >> strWord)
	{
		if(!isdigit( strWord[0] ))
		{
			getline(fin, strLine);
			continue;
		}

		int startFrame = atoi(strWord.c_str());
		int numOfFrames = 0, loopingFrames = 0, framesPerSecond = 0;
		fin >> numOfFrames >> loopingFrames >> framesPerSecond;

		animations[currentAnim].startFrame		= startFrame;
		animations[currentAnim].endFrame		= startFrame + numOfFrames;
		animations[currentAnim].loopingFrames	= loopingFrames;
		animations[currentAnim].framesPerSecond = framesPerSecond;

		fin >> strLine >> strLine;
		strcpy(animations[currentAnim].strName, strLine.c_str());

		if(IsInString(strLine, "BOTH"))
		{
			m_Upper.pAnimations.push_back(animations[currentAnim]);
			m_Lower.pAnimations.push_back(animations[currentAnim]);
		}
		else if(IsInString(strLine, "TORSO"))
		{
			m_Upper.pAnimations.push_back(animations[currentAnim]);
		}
		else if(IsInString(strLine, "LEGS"))
		{	
			if(!torsoOffset)
				torsoOffset = animations[LEGS_WALKCR].startFrame - animations[TORSO_GESTURE].startFrame;

			animations[currentAnim].startFrame -= torsoOffset;
			animations[currentAnim].endFrame -= torsoOffset;

			m_Lower.pAnimations.push_back(animations[currentAnim]);
		}
	
		currentAnim++;
	}	

	m_Lower.numOfAnimations = m_Lower.pAnimations.size();
	m_Upper.numOfAnimations = m_Upper.pAnimations.size();
	m_Head.numOfAnimations = m_Head.pAnimations.size();
	m_Weapon.numOfAnimations = m_Head.pAnimations.size();

	return true;
}

void  CModelMD3::LinkModel(t3DModel *pModel, t3DModel *pLink, LPSTR strTagName)
{
	if(!pModel || !pLink || !strTagName) return;

	for(int i = 0; i < pModel->numOfTags; i++)
	{
		if( !_stricmp(pModel->pTags[i].strName, strTagName) )
		{
			pModel->pLinks[i] = pLink;
			return;
		}
	}
}


bool CModelMD3::UpdateModel(t3DModel *pModel,bool loop)
{
	int startFrame = 0;
	int endFrame   = 1;

	tAnimationInfo *pAnim = &(pModel->pAnimations[pModel->currentAnim]);

	if(pModel->numOfAnimations)
	{
		startFrame = pAnim->startFrame;
		endFrame   = pAnim->endFrame;
	}
	
	pModel->nextFrame = (pModel->currentFrame + 1) % endFrame;

	if(pModel->nextFrame == 0)
	{
		pModel->nextFrame =  startFrame;
		if(!loop)
			return true;
	}
	SetCurrentTime(pModel);
	return false;
}

void CModelMD3::DrawModel()
{
	glRotatef(-90, 1, 0, 0);
	DrawLink(&m_Lower);
}
void CModelMD3::Draw()
{
	glRotatef(-90, 1, 0, 0);
	RenderModel(&m_Weapon);
}
bool CModelMD3::UpdateLowerModel()
{
	int Animation = GetLegsCurrentAnimation();
	if(Animation > 5)
		Animation += 7;
	bool loop = false;
	if(Animation == BOTH_DEATH1)
	{
		if(UpdateModel(&m_Lower,loop))
			SetLegsAnimation(BOTH_DEAD1);
		return true;
	}
	if(Animation == LEGS_JUMPB)
	{
		if(UpdateModel(&m_Lower,loop))
			SetLegsAnimation(LEGS_LAND);
		return true;
	}
	if(Animation == LEGS_LAND)
	{
		if(UpdateModel(&m_Lower,loop))
			SetLegsAnimation(LEGS_IDLE);
		return true;
	}
	else
		loop = true;
	return UpdateModel(&m_Lower,loop);
}
bool CModelMD3::UpdateUpperModel()
{
	int Animation = GetTorsoCurrentAnimation();
	bool loop = false;
	if(Animation == BOTH_DEATH1)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			SetTorsoAnimation(BOTH_DEAD1);
		return true;
	}
	if(Animation == TORSO_ATTACK)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			SetTorsoAnimation(TORSO_STAND);
		return true;
	}
	if(Animation == TORSO_DROP)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			SetTorsoAnimation(TORSO_STAND);
		return true;
	}
	if(Animation == TORSO_ATTACK2)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			SetTorsoAnimation(TORSO_STAND2);
		return true;
	}
	else
		loop = true;
	return UpdateModel(&m_Upper,loop);
}
bool CModelMD3::UpdateUpperModel(int weapon)
{
	int Animation = GetTorsoCurrentAnimation();
	bool loop = false;
	if(Animation == BOTH_DEATH1)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			SetTorsoAnimation(BOTH_DEAD1);
		return true;
	}
	if(Animation == TORSO_ATTACK)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			SetTorsoAnimation(TORSO_STAND);
		return true;
	}
	if(Animation == TORSO_DROP)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			if(!weapon)
				SetTorsoAnimation(TORSO_STAND2);
			else
				SetTorsoAnimation(TORSO_STAND);
		return true;
	}
	if(Animation == TORSO_ATTACK2)
	{
		loop = false;
		if(UpdateModel(&m_Upper,loop))
			SetTorsoAnimation(TORSO_STAND2);
		return true;
	}
	else
		loop = true;
	return UpdateModel(&m_Upper,loop);
}

void CModelMD3::DrawLink(t3DModel *pModel)
{
	RenderModel(pModel);
	CQuaternion qQuat, qNextQuat, qInterpolatedQuat;
	float *pMatrix, *pNextMatrix;
	float finalMatrix[16] = {0};

	for(int i = 0; i < pModel->numOfTags; i++)
	{
		t3DModel *pLink = pModel->pLinks[i];

		if(pLink)
		{			
			CVector3 vPosition = pModel->pTags[pModel->currentFrame * pModel->numOfTags + i].vPosition;
			CVector3 vNextPosition = pModel->pTags[pModel->nextFrame * pModel->numOfTags + i].vPosition;
			vPosition.x = vPosition.x + pModel->t * (vNextPosition.x - vPosition.x),
			vPosition.y	= vPosition.y + pModel->t * (vNextPosition.y - vPosition.y),
			vPosition.z	= vPosition.z + pModel->t * (vNextPosition.z - vPosition.z);			
			pMatrix = &pModel->pTags[pModel->currentFrame * pModel->numOfTags + i].rotation[0][0];
			pNextMatrix = &pModel->pTags[pModel->nextFrame * pModel->numOfTags + i].rotation[0][0];
			qQuat.CreateFromMatrix( pMatrix, 3);
			qNextQuat.CreateFromMatrix( pNextMatrix, 3 );
			qInterpolatedQuat = qQuat.Slerp(qQuat, qNextQuat, pModel->t);
			qInterpolatedQuat.CreateMatrix( finalMatrix );
			finalMatrix[12] = vPosition.x;
			finalMatrix[13] = vPosition.y;
			finalMatrix[14] = vPosition.z;

			glPushMatrix();
			glMultMatrixf( finalMatrix );

			DrawLink(pLink);
			glPopMatrix();
		}
	}

}

void CModelMD3::SetCurrentTime(t3DModel *pModel)
{
	float elapsedTime   = 0.0f;

	if(!pModel->pAnimations.size()) return;

	float time = (float)GetTickCount();

	elapsedTime = time - pModel->lastTime;

	int animationSpeed = pModel->pAnimations[pModel->currentAnim].framesPerSecond;

	float t = elapsedTime / (1000.0f / animationSpeed);
	if (elapsedTime >= (1000.0f / animationSpeed) )
	{
		pModel->currentFrame = pModel->nextFrame;
		pModel->lastTime = time;
	}

	pModel->t = t;
}



void CModelMD3::RenderModel(t3DModel *pModel)
{
	if(pModel->pObject.size() <= 0) return;
	for(int i = 0; i < pModel->numOfObjects; i++)
	{
		t3DObject *pObject = &pModel->pObject[i];
		int currentIndex = pModel->currentFrame * pObject->numOfVerts; 
		int nextIndex = pModel->nextFrame * pObject->numOfVerts; 
		if(pObject->bHasTexture)
		{
			glEnable(GL_TEXTURE_2D);
			int textureID = pModel->pMaterials[pObject->materialID].texureId;
			glBindTexture(GL_TEXTURE_2D, m_Textures[textureID]);
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
		}
		glBegin(GL_TRIANGLES);
		for(int j = 0; j < pObject->numOfFaces; j++)
		{
			for(int whichVertex = 0; whichVertex < 3; whichVertex++)
			{
				int index = pObject->pFaces[j].vertIndex[whichVertex];
				if(pObject->pTexVerts) 
				{
					glTexCoord2f(pObject->pTexVerts[ index ].x, 
						pObject->pTexVerts[ index ].y);
				}
				CVector3 vPoint1 = pObject->pVerts[ currentIndex + index ];
				CVector3 vPoint2 = pObject->pVerts[ nextIndex + index];

				glVertex3f(vPoint1.x + pModel->t * (vPoint2.x - vPoint1.x),
					vPoint1.y + pModel->t * (vPoint2.y - vPoint1.y),
					vPoint1.z + pModel->t * (vPoint2.z - vPoint1.z));
			}
		}
		glEnd();
	}
}

void CModelMD3::SetTorsoAnimation(LPSTR strAnimation)
{
	for(int i = 0; i < m_Upper.numOfAnimations; i++)
	{
		if( !_stricmp(m_Upper.pAnimations[i].strName, strAnimation) )
		{
			m_Upper.currentAnim = i;
			m_Upper.currentFrame = m_Upper.pAnimations[m_Upper.currentAnim].startFrame;
			return;
		}
	}
}
void CModelMD3::SetTorsoAnimation(int AnimationNumber)
{
	m_Upper.currentAnim = AnimationNumber;
	m_Upper.currentFrame = m_Upper.pAnimations[m_Upper.currentAnim].startFrame;
}
int CModelMD3::GetTorsoCurrentAnimation()
{
	return m_Upper.currentAnim;
}
int CModelMD3::GetLegsCurrentAnimation()
{
	return m_Lower.currentAnim;
}

void CModelMD3::SetLegsAnimation(LPSTR strAnimation)
{
	for(int i = 0; i < m_Lower.numOfAnimations; i++)
	{
		if( !_stricmp(m_Lower.pAnimations[i].strName, strAnimation) )
		{
			m_Lower.currentAnim = i;
			m_Lower.currentFrame = m_Lower.pAnimations[m_Lower.currentAnim].startFrame;
			return;
		}
	}
}
void CModelMD3::SetLegsAnimation(int AnimationNumber)
{
	if(AnimationNumber > 5)
		m_Lower.currentAnim = AnimationNumber - LegConvertor;
	else
		m_Lower.currentAnim = AnimationNumber;
	m_Lower.currentFrame = m_Lower.pAnimations[m_Lower.currentAnim].startFrame;
}
CLoadMD3::CLoadMD3()
{
	memset(&m_Header, 0, sizeof(tMd3Header));

	// Set the pointers to null
	m_pSkins=NULL;
	m_pTexCoords=NULL;
	m_pTriangles=NULL;
	m_pBones=NULL;
}

bool CLoadMD3::ImportMD3(t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};

	m_FilePointer = fopen(strFileName, "rb");
	if(!m_FilePointer) 
	{
		sprintf(strMessage, "Unable to find the file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}
	fread(&m_Header, 1, sizeof(tMd3Header), m_FilePointer);
	char *ID = m_Header.fileID;
	if((ID[0] != 'I' || ID[1] != 'D' || ID[2] != 'P' || ID[3] != '3') || m_Header.version != 15)
	{
		sprintf(strMessage, "Invalid file format (Version not 15): %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}
	ReadMD3Data(pModel);
	CleanUp();
	return true;
}

void CLoadMD3::ReadMD3Data(t3DModel *pModel)
{
	int i = 0;

		m_pBones = new tMd3Bone [m_Header.numFrames];
	fread(m_pBones, sizeof(tMd3Bone), m_Header.numFrames, m_FilePointer);
	delete [] m_pBones;
	pModel->pTags = new tMd3Tag [m_Header.numFrames * m_Header.numTags];
	fread(pModel->pTags, sizeof(tMd3Tag), m_Header.numFrames * m_Header.numTags, m_FilePointer);
	pModel->numOfTags = m_Header.numTags;
	
	pModel->pLinks = (t3DModel **) malloc(sizeof(t3DModel) * m_Header.numTags);
	
	for (i = 0; i < m_Header.numTags; i++)
		pModel->pLinks[i] = NULL;

	long meshOffset = ftell(m_FilePointer);

	tMd3MeshInfo meshHeader;

	for (i = 0; i < m_Header.numMeshes; i++)
	{
		fseek(m_FilePointer, meshOffset, SEEK_SET);
		fread(&meshHeader, sizeof(tMd3MeshInfo), 1, m_FilePointer);

		m_pSkins     = new tMd3Skin [meshHeader.numSkins];
		m_pTexCoords = new tMd3TexCoord [meshHeader.numVertices];
		m_pTriangles = new tMd3Face [meshHeader.numTriangles];
		m_pVertices  = new tMd3Triangle [meshHeader.numVertices * meshHeader.numMeshFrames];

		fread(m_pSkins, sizeof(tMd3Skin), meshHeader.numSkins, m_FilePointer);
		
		fseek(m_FilePointer, meshOffset + meshHeader.triStart, SEEK_SET);
		fread(m_pTriangles, sizeof(tMd3Face), meshHeader.numTriangles, m_FilePointer);

		fseek(m_FilePointer, meshOffset + meshHeader.uvStart, SEEK_SET);
		fread(m_pTexCoords, sizeof(tMd3TexCoord), meshHeader.numVertices, m_FilePointer);

		fseek(m_FilePointer, meshOffset + meshHeader.vertexStart, SEEK_SET);
		fread(m_pVertices, sizeof(tMd3Triangle), meshHeader.numMeshFrames * meshHeader.numVertices, m_FilePointer);
		ConvertDataStructures(pModel, meshHeader);

		delete [] m_pSkins;    
		delete [] m_pTexCoords;
		delete [] m_pTriangles;
		delete [] m_pVertices;   

		meshOffset += meshHeader.meshSize;
	}
}


void CLoadMD3::ConvertDataStructures(t3DModel *pModel, tMd3MeshInfo meshHeader)
{
	int i = 0;
	pModel->numOfObjects++;
	t3DObject currentMesh = {0};
	strcpy(currentMesh.strName, meshHeader.strName);

	currentMesh.numOfVerts   = meshHeader.numVertices;
	currentMesh.numTexVertex = meshHeader.numVertices;
	currentMesh.numOfFaces   = meshHeader.numTriangles;
	currentMesh.pVerts    = new CVector3 [currentMesh.numOfVerts * meshHeader.numMeshFrames];
	currentMesh.pTexVerts = new CVector2 [currentMesh.numOfVerts];
	currentMesh.pFaces    = new tFace [currentMesh.numOfFaces];
	for (i=0; i < currentMesh.numOfVerts * meshHeader.numMeshFrames; i++)
	{
		currentMesh.pVerts[i].x =  m_pVertices[i].vertex[0] / 64.0f;
		currentMesh.pVerts[i].y =  m_pVertices[i].vertex[1] / 64.0f;
		currentMesh.pVerts[i].z =  m_pVertices[i].vertex[2] / 64.0f;
	}

	for (i=0; i < currentMesh.numTexVertex; i++)
	{
		currentMesh.pTexVerts[i].x =  m_pTexCoords[i].textureCoord[0];
		currentMesh.pTexVerts[i].y = -m_pTexCoords[i].textureCoord[1];
	}
	for(i=0; i < currentMesh.numOfFaces; i++)
	{
		currentMesh.pFaces[i].vertIndex[0] = m_pTriangles[i].vertexIndices[0];
		currentMesh.pFaces[i].vertIndex[1] = m_pTriangles[i].vertexIndices[1];
		currentMesh.pFaces[i].vertIndex[2] = m_pTriangles[i].vertexIndices[2];
		currentMesh.pFaces[i].coordIndex[0] = m_pTriangles[i].vertexIndices[0];
		currentMesh.pFaces[i].coordIndex[1] = m_pTriangles[i].vertexIndices[1];
		currentMesh.pFaces[i].coordIndex[2] = m_pTriangles[i].vertexIndices[2];
	}
	pModel->pObject.push_back(currentMesh);
}

bool CLoadMD3::LoadSkin(t3DModel *pModel, LPSTR strSkin)
{
	if(!pModel || !strSkin) return false;

	ifstream fin(strSkin);

	if(fin.fail())
	{
		MessageBox(NULL, "Unable to load skin!", "Error", MB_OK);
		return false;
	}

	string strLine = "";
	int textureNameStart = 0;

	while(getline(fin, strLine))
	{
		for(int i = 0; i < pModel->numOfObjects; i++)
		{
			if( IsInString(strLine, pModel->pObject[i].strName) )			
			{			
				for(int j = strLine.length() - 1; j > 0; j--)
				{
					if(strLine[j] == '/')
					{
						textureNameStart = j + 1;
						break;
					}	
				}
				tMaterialInfo texture;
				strcpy(texture.strFile, &strLine[textureNameStart]);
				texture.uTile = texture.uTile = 1;
				pModel->pObject[i].materialID = pModel->numOfMaterials;
				pModel->pObject[i].bHasTexture = true;
				pModel->numOfMaterials++;
				pModel->pMaterials.push_back(texture);
			}
		}
	}

	fin.close();
	return true;
}

bool CLoadMD3::LoadShader(t3DModel *pModel, LPSTR strShader)
{
	if(!pModel || !strShader) return false;

	ifstream fin(strShader);

	if(fin.fail())
	{
		MessageBox(NULL, "Unable to load shader!", "Error", MB_OK);
		return false;
	}

	string strLine = "";
	int currentIndex = 0;
	
	while(getline(fin, strLine))
	{
		tMaterialInfo texture;

		strcpy(texture.strFile, strLine.c_str());
				
		texture.uTile = texture.uTile = 1;

		pModel->pObject[currentIndex].materialID = pModel->numOfMaterials;
		pModel->pObject[currentIndex].bHasTexture = true;

		pModel->numOfMaterials++;

		pModel->pMaterials.push_back(texture);

		currentIndex++;
	}

	fin.close();
	return true;
}

void CLoadMD3::CleanUp()
{
	fclose(m_FilePointer);						
}