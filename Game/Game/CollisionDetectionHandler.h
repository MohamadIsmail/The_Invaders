class CollisionDetectionHandler
{
public:
	enum WhoGotHit{NONE,ENEMY,HERO};
	bool CheckCollisionBetweenPlayerAndEnemy(int lvl,NormalEnemy e[],Hero &hero,Boss &boss,FinalBoss &fboss)
	{
		if(hero.weaponNumber != 0)
			return false;
		bool isCollided = false;
		size_t nEnems;
		if(lvl == 1)
			nEnems = 14;
		if(lvl == 2)
			nEnems = 20;
		for(int enemInd = nEnems-1; enemInd>=0; enemInd--) {
			if(e[enemInd].Dead)
				continue;
			AABoundingBox enemBox = e[enemInd].GetAABB();
			if(hero.GetAABB().IntersectsWith(enemBox))
			{
				e[enemInd].PlayerGotHit();
				e[enemInd].HP-= hero.damage;
				isCollided = true;
			}
		}
		AABoundingBox enemBox = boss.GetAABB();
		if(hero.GetAABB().IntersectsWith(enemBox))
		{
			boss.PlayerGotHit();
			boss.HP-= hero.damage;
			isCollided = true;
		}
		enemBox = fboss.GetAABB();
		if(hero.GetAABB().IntersectsWith(enemBox))
		{
			fboss.PlayerGotHit();
			fboss.HP-= hero.damage;
			isCollided = true;
		}
		return isCollided;
	}

	int HandleCollisions(int lvl,NormalEnemy e[],Hero &hero,Boss &boss,FinalBoss &fboss) {
		if(hero.weaponNumber == 0)
		{
			if(CheckCollisionBetweenPlayerAndEnemy(lvl,e,hero,boss,fboss))
				return ENEMY;
			else
				return NONE;
		}
		size_t nEnems;
		if(lvl == 1)
			nEnems = 14;
		if(lvl == 2)
			nEnems = 20;
		for(int enemInd = nEnems-1; enemInd>=0; enemInd--) {
			if(e[enemInd].Dead)
				continue;
			AABoundingBox enemBox = e[enemInd].GetAABB();
			size_t nBulls = hero.Bullets.size();
			for(int bullInd = nBulls-1; bullInd>=0; bullInd--) {
				if(hero.Bullets[bullInd].GetAABB().IntersectsWith(enemBox)) {
					hero.Bullets.erase(hero.Bullets.begin() + bullInd);
					e[enemInd].PlayerGotHit();
					e[enemInd].HP-= hero.damage;
					return ENEMY;
					break;
				}
			}
		}
		if(!boss.Dead)
		{
			AABoundingBox BossBox = boss.GetAABB();
			size_t nBulls = hero.Bullets.size();
				for(int bullInd = nBulls-1; bullInd>=0; bullInd--) {
					if(hero.Bullets[bullInd].GetAABB().IntersectsWith(BossBox)) {
						hero.Bullets.erase(hero.Bullets.begin() + bullInd);
						boss.PlayerGotHit();
						boss.HP-=hero.damage;
						return ENEMY;
						break;
					}
				}
		}
		if(!fboss.Dead)
		{
			AABoundingBox BossBox = fboss.GetAABB();
			size_t nBulls = hero.Bullets.size();
				for(int bullInd = nBulls-1; bullInd>=0; bullInd--) {
					if(hero.Bullets[bullInd].GetAABB().IntersectsWith(BossBox)) {
						hero.Bullets.erase(hero.Bullets.begin() + bullInd);
						fboss.PlayerGotHit();
						fboss.HP-=hero.damage;
						return ENEMY;
						break;
					}
				}
		}
		int en;
		if(lvl == 1)
			en = 14;
		if(lvl == 2)
			en = 20;
		for(int i = 0;i < en ; i++)
		{
			size_t enemyBullCount = e[i].Bullets.size();
			if(hero.IsDead())
				return NONE;
			for(int bInd = enemyBullCount-1; bInd>=0; bInd--) 
				if(e[i].Bullets[bInd].GetAABB().IntersectsWith(hero.GetAABB()))
				{
					hero.HP = max(hero.HP - e[i].damage, 0);
					hero.HealthPointDecreased = ((0.48-0.02)/hero.MaxHP)*(hero.MaxHP-hero.HP);
					hero.PlayerGotHit();
					e[i].Bullets.erase(e[i].Bullets.begin() + bInd);
					return HERO;
				}
		}
		size_t enemyBullCount = boss.Bullets.size();
		for(int bInd = enemyBullCount-1; bInd>=0; bInd--) 
			if(boss.Bullets[bInd].GetAABB().IntersectsWith(hero.GetAABB()))
			{
				hero.HP = max(hero.HP - boss.damage, 0);
				hero.HealthPointDecreased = ((0.48)/hero.MaxHP)*(hero.MaxHP-hero.HP);
				hero.PlayerGotHit();
				boss.Bullets.erase(boss.Bullets.begin() + bInd);
				return HERO;
			}
		enemyBullCount = fboss.Bullets.size();
		for(int bInd = enemyBullCount-1; bInd>=0; bInd--) 
			if(fboss.Bullets[bInd].GetAABB().IntersectsWith(hero.GetAABB()))
			{
				hero.HP = max(hero.HP - fboss.damage, 0);
				hero.HealthPointDecreased = ((0.48)/hero.MaxHP)*(hero.MaxHP-hero.HP);
				hero.PlayerGotHit();
				fboss.Bullets.erase(fboss.Bullets.begin() + bInd);
				return HERO;
			}
		return NONE;
	}
};
